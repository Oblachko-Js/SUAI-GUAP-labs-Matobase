/*fsm_inter_tm3.c*/
#include "fsm_inter_tm3.h"
#include "fsm_tm3.h"
#include "fsm_main.h"
#include "timers.h"
#include "messages.h"
#include "i2cFram.h"
#include "uart.h"
#include "main.h"

/*состояния автомата*/

#define MTCTRL_RXMSG	0 // ожидание команды прерывания
#define MTCTRL_PROC		1 // работа МТ
#define MTCTRL_RDFRAM	2 // чтение FRAM
#define MTCTRL_WRFRAM	3 // запись FRAM
#define MTCTRL_UARTTR	4 // передача UART

// переменная состояния автомата контроля МТ
static char fsm3statectrl = MTCTRL_PROC; 

static char isRunningTM3 = 0;
int steptm3;
void ProcessFsmInterTm3 (void)
{
    uint8_t* pRxbuf=0;
    static uint8_t aTrbuf[32];
    switch (fsm3statectrl)
    {
        case MTCTRL_UARTTR:
            if(GetTimer(TM3_TIMER) > 1000) // 1000 msec
			{ // ожидаем время итерации
				lenfsm = strlen((char*)aTrbuf);
				if( uart_transmit(aTrbuf,lenfsm) == 0 )
				{ // передаём результат итерации в терминал 
					ResetTimer(TM3_TIMER);
					fsm3statectrl = MTCTRL_PROC;
				}
			}
            break;
        case MTCTRL_PROC:
            if (GetMessage(MSG_TM3STOP, (void*)&pRxbuf))
            {
                if (steptm3 > 0)
                {
                    sprintf((char*)aTrbuf,"TM3 > interrupted. step = %d\n", steptm3-1);    
                    fsm3statectrl = MTCTRL_UARTTR;
                }
            }
            else
            {
                steptm3 = ProcessFsmTm3();
                isRunningTM3 = (steptm3 > 0);
            }
            break;
    }        
   
}