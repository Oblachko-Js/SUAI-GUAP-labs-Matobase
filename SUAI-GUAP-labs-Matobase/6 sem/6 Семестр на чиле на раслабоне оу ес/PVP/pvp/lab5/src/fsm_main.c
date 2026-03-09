/* fsm_main.c */
#include "timers.h"
#include "messages.h"
#include "fsm_main.h"
#include "uart.h"
#include "i2cFram.h"
#include "main.h"

/* ?????? ?????? */
#define CMD_READ    "rd"
#define CMD_WRITE   "wr"
#define CMD_TM1     "tm1"
#define CMD_TM2     "tm2"
#define CMD_STOP1   "stop1"
#define CMD_STOP2   "stop2"

/* ????????? ???????? */
#define FSMST_UARTRX    0  // ???????? ?????? ?????? ?? UART
#define FSMST_UARTTR    1  // ???????? ?????? ?????? ?? UART
#define FSMST_RDFRAM    2  // ?????? ?????? ?????? ?? FRAM
#define FSMST_WRFRAM    3  // ?????? ?????? ?????? ? FRAM

/* ????????? ??????? ??? ?? */
#define MT1_START_ADDR  0x000
#define MT1_END_ADDR    0x7FF
#define MT2_START_ADDR  0x800
#define MT2_END_ADDR    0xFFF

int lenfsm;
static int addrfsm;
static uint8_t aRecvbuf[255];
static char fsmstate = FSMST_UARTRX;

void ProcessFsmMain(void) {
    uint8_t* pRxbuf = 0;
    
    switch (fsmstate) {
        case FSMST_UARTRX:
            if(GetMessage(MSG_UART_RX, (void*)&pRxbuf)) {
                /* ????????? ?????? ????????? */
                if(strncmp((char*)pRxbuf, CMD_STOP1, strlen(CMD_STOP1)) == 0) {
                    SendMessage(MSG_TM1_STOP, NULL);
                    strcpy((char*)aRecvbuf, "MT1 stop command sent\n");
                    lenfsm = strlen((char*)aRecvbuf);
                    fsmstate = FSMST_UARTTR;
                    break;
                }
                else if(strncmp((char*)pRxbuf, CMD_STOP2, strlen(CMD_STOP2)) == 0) {
                    SendMessage(MSG_TM2_STOP, NULL);
                    strcpy((char*)aRecvbuf, "MT2 stop command sent\n");
                    lenfsm = strlen((char*)aRecvbuf);
                    fsmstate = FSMST_UARTTR;
                    break;
                }
                
                /* ??????? ???????? ?????? */
                if(lenuart > 6) {
                    addrfsm = -1;
                    lenfsm = -1;
                    sscanf((char*)&(pRxbuf[2]), "<%x:%x>", &addrfsm, &lenfsm);
                    
                    if(addrfsm >= 0 && lenfsm > 0 && lenfsm <= IICBUFSZ) {
                        /* ??????????? ???? ??????? */
                        if(strncmp((char*)pRxbuf, CMD_READ, 2) == 0) {
                            fsmstate = FSMST_RDFRAM;
                            break;
                        }
                        else if(strncmp((char*)pRxbuf, CMD_WRITE, 2) == 0) {
                            char* pbuf = strchr((char*)pRxbuf, '>');
                            if(pbuf != NULL && lenfsm <= (lenuart - (pbuf - (char*)pRxbuf + 1))) {
                                memcpy(aRecvbuf, pbuf + 1, lenfsm);
                                fsmstate = FSMST_WRFRAM;
                                break;
                            }
                        }
                        else if(strncmp((char*)pRxbuf, CMD_TM1, 3) == 0) {
                            if(addrfsm >= MT1_START_ADDR && addrfsm <= MT1_END_ADDR) {
                                SendMessage(MSG_TM1STRT, (void*)&aRecvbuf);
                                break;
                            }
                        }
                        else if(strncmp((char*)pRxbuf, CMD_TM2, 3) == 0) {
                            if(addrfsm >= MT2_START_ADDR && addrfsm <= MT2_END_ADDR) {
                                SendMessage(MSG_TM2STRT, (void*)&aRecvbuf);
                                break;
                            }
                        }
                    }
                }
                
                /* ?????? ? ??????? */
                strcpy((char*)aRecvbuf, "Err> cmd error\n");
                lenfsm = strlen((char*)aRecvbuf);
                fsmstate = FSMST_UARTTR;
            }
            break;
            
        case FSMST_RDFRAM:
            pRxbuf = (uint8_t*)i2cFRAM_rd(addrfsm, lenfsm);
            if((uint32_t)pRxbuf > 0) {
                lenfsm = leni2c;
                aRecvbuf[lenfsm] = '\n';
                lenfsm++;
                memcpy(aRecvbuf, pRxbuf, leni2c);
                fsmstate = FSMST_UARTTR;
            }
            break;
            
        case FSMST_WRFRAM:
            if((uint32_t)i2cFRAM_wr(addrfsm, aRecvbuf, lenfsm) > 0) {
                strcpy((char*)aRecvbuf, "wr> ok\n");
                lenfsm = strlen((char*)aRecvbuf);
                fsmstate = FSMST_UARTTR;
            }
            break;
            
        case FSMST_UARTTR:
            if(uart_transmit(aRecvbuf, lenfsm) == 0) {
                fsmstate = FSMST_UARTRX;
            }
            break;
    }
}