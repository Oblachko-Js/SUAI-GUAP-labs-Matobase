/* fsm_tm.c */
#include "fsm_tm.h"
#include "fsm_main.h"
#include "timers.h"
#include "messages.h"
#include "i2cFram.h"
#include "uart.h"
#include "main.h"
#include "keypad.h"

/* ????????? ???????? ?????????? */
#define MTCTRL_RXCMD    0  // ???????? ??????? ???????
#define MTCTRL_PROC     1  // ?????? ??
#define MTCTRL_RDFRAM   2  // ?????? FRAM
#define MTCTRL_WRFRAM   3  // ?????? FRAM
#define MTCTRL_UARTTR   4  // ???????? UART

/* ????????? ???????? ???????? ??? ???????? ???? 'a' */
#define FSMST_Q0        0
#define FSMST_Q1        1
#define FSMST_Q2        2
#define FSMST_Q3        3

/* ????????? ???????? ???????? ??? ???????? ?????? ?????? */
#define FSMST_BR_Q0     10
#define FSMST_BR_Q1     11
#define FSMST_BR_Q2     12
#define FSMST_BR_Q3     13

/* ????????? ??? ???????? ????????? ?? */
typedef struct {
    uint32_t curr_addr;
    uint32_t next_addr;
    char mt_state;
    char ctrl_state;
    int step_count;
    uint8_t rd_symbol;
    uint8_t wr_symbol;
    uint8_t buffer[32];
    int is_active;
} TM_Instance;

static TM_Instance tm1; // ??? ?????? ?? (???????? 'a')
static TM_Instance tm2; // ??? ?????? ?? (???????? ??????)

// ????????? ???????
int ProcTm1(uint8_t rsymb, uint8_t* wrsymb);
int ProcTm2(uint8_t rsymb, uint8_t* wrsymb);
void ProcessTmInstance(TM_Instance* tm, int tm_num);

void InitTuringMachines(void) {
    memset(&tm1, 0, sizeof(TM_Instance));
    memset(&tm2, 0, sizeof(TM_Instance));
    tm1.ctrl_state = MTCTRL_RXCMD;
    tm2.ctrl_state = MTCTRL_RXCMD;
}

int ProcTm1(uint8_t rsymb, uint8_t* wrsymb) {
    static int a_count = 0;
    *wrsymb = rsymb;
    
    switch(tm1.mt_state) {
        case FSMST_Q0:  // ?????????????
            tm1.step_count = 1;
            tm1.next_addr = 0;
            a_count = 0;
            tm1.mt_state = FSMST_Q1;
            break;
            
        case FSMST_Q1:  // ????? ????? ??????
            if(rsymb == 0 || rsymb == 0xFF) {
                tm1.next_addr = tm1.curr_addr - 1;
                tm1.mt_state = FSMST_Q2;
            } else {
                tm1.next_addr = tm1.curr_addr + 1;
            }
            break;
            
        case FSMST_Q2:  // ???????? ???? 'a'
            if(rsymb == 'a' && a_count < 2) {
                *wrsymb = '_';
                a_count++;
                if(a_count >= 2) {
                    tm1.mt_state = FSMST_Q3;
                }
            }
            tm1.next_addr = tm1.curr_addr - 1;
            break;
            
        case FSMST_Q3:  // ??????????
            tm1.step_count = -1;
            break;
    }
    
    if(tm1.step_count != -1) {
        tm1.step_count++;
    }
    return tm1.step_count;
}

int ProcTm2(uint8_t rsymb, uint8_t* wrsymb) {
    static int stack_ptr = 0;
    *wrsymb = rsymb;
    
    switch(tm2.mt_state) {
        case FSMST_BR_Q0:  // ?????????????
            tm2.step_count = 1;
            tm2.next_addr = 0;
            stack_ptr = 0;
            tm2.mt_state = FSMST_BR_Q1;
            break;
            
        case FSMST_BR_Q1:  // ????? ?????? ??????
            if(rsymb == '(') {
                stack_ptr++;
                tm2.next_addr = tm2.curr_addr + 1;
            } 
            else if(rsymb == ')') {
                if(stack_ptr > 0) {
                    *wrsymb = 'x';  // ???????? ?????? ??????
                    stack_ptr--;
                }
                tm2.next_addr = tm2.curr_addr + 1;
            }
            else if(rsymb == 0 || rsymb == 0xFF) {
                tm2.mt_state = FSMST_BR_Q2;
            }
            else {
                tm2.next_addr = tm2.curr_addr + 1;
            }
            break;
            
        case FSMST_BR_Q2:  // ??????????
            tm2.step_count = -1;
            break;
    }
    
    if(tm2.step_count != -1) {
        tm2.step_count++;
    }
    return tm2.step_count;
}

void ProcessTmInstance(TM_Instance* tm, int tm_num) {
    uint8_t* pRxbuf = 0;
    int start_msg = (tm_num == 1) ? MSG_TM1STRT : MSG_TM2STRT;
    int timer_id = (tm_num == 1) ? TM1_TIMER : TM2_TIMER;
    
    switch (tm->ctrl_state) {
        case MTCTRL_RXCMD:
            if(GetMessage(start_msg, (void*)&pRxbuf)) {
                tm->next_addr = (tm_num == 1) ? 0 : 0x800; // ?????? ??????? FRAM
                tm->ctrl_state = MTCTRL_RDFRAM;
                tm->mt_state = (tm_num == 1) ? FSMST_Q0 : FSMST_BR_Q0;
                tm->is_active = 1;
                ResetTimer(timer_id);
            }
            break;
            
        case MTCTRL_PROC:
            if(GetTimer(timer_id) >= 1000) {
                ResetTimer(timer_id);
                int curstep = (tm_num == 1) ? 
                    ProcTm1(tm->rd_symbol, &tm->wr_symbol) :
                    ProcTm2(tm->rd_symbol, &tm->wr_symbol);
                
                if(curstep == -1) {
                    sprintf((char*)tm->buffer, "MT%d: Done. Steps: %d\n", 
                           tm_num, tm->step_count);
                    tm->ctrl_state = MTCTRL_UARTTR;
                    tm->is_active = 0;
                } 
                else if(tm->wr_symbol == tm->rd_symbol) {
                    tm->ctrl_state = MTCTRL_RDFRAM;
                } 
                else {
                    tm->ctrl_state = MTCTRL_WRFRAM;
                }
            }
            break;
            
        case MTCTRL_RDFRAM:
            pRxbuf = (uint8_t*)i2cFRAM_rd(tm->next_addr, 1);
            if((uint32_t)pRxbuf > 0) {
                tm->rd_symbol = pRxbuf[0];
                tm->curr_addr = tm->next_addr;
                tm->ctrl_state = MTCTRL_PROC;
            }
            break;
            
        case MTCTRL_WRFRAM:
            if((uint32_t)i2cFRAM_wr(tm->curr_addr, &tm->wr_symbol, 1) > 0) {
                tm->ctrl_state = MTCTRL_RDFRAM;
            }
            break;
            
        case MTCTRL_UARTTR:
            if(uart_transmit(tm->buffer, strlen((char*)tm->buffer)) == 0) {
                tm->ctrl_state = MTCTRL_RXCMD;
            }
            break;
    }
}

void ProcessFsmTm(void) {
    // ????????? ?????????? ????????
    void* param;
    
    if(GetMessage(MSG_TM1_STOP, &param) && tm1.is_active) {
        sprintf((char*)tm1.buffer, "MT1: Stopped by K1. Steps: %d\n", tm1.step_count);
        tm1.ctrl_state = MTCTRL_UARTTR;
        tm1.is_active = 0;
    }
    
    if(GetMessage(MSG_TM2_STOP, &param) && tm2.is_active) {
        sprintf((char*)tm2.buffer, "MT2: Stopped by K2. Steps: %d\n", tm2.step_count);
        tm2.ctrl_state = MTCTRL_UARTTR;
        tm2.is_active = 0;
    }
    
    // ????????? ????? ??
    if(tm1.is_active) ProcessTmInstance(&tm1, 1);
    if(tm2.is_active) ProcessTmInstance(&tm2, 2);
}