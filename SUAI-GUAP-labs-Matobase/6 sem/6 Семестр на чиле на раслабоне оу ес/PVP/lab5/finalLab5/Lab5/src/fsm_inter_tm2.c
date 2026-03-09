/*fsm_inter_tm2.c*/
#include "fsm_inter_tm2.h"
#include "fsm_tm2.h"
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
static char fsm2statectrl = MTCTRL_PROC; 

static char isRunningTM2 = 0;
int steptm2;
void ProcessFsmInterTm2 (void)
{
    uint8_t* pRxbuf=0;
    static uint8_t aTrbuf[32];
    switch (fsm2statectrl)
    {
        case MTCTRL_UARTTR:
            if(GetTimer(TM2_TIMER) > 500) // 500 msec
			{ // ожидаем время итерации
				lenfsm = strlen((char*)aTrbuf);
				if( uart_transmit(aTrbuf,lenfsm) == 0 )
				{ // передаём результат итерации в терминал 
					ResetTimer(TM2_TIMER);
                    fsm2statectrl = MTCTRL_PROC;
				}
			}
            break;
        case MTCTRL_PROC:
            if (GetMessage(MSG_TM2STOP, (void*)&pRxbuf))
            {
                if (steptm2 > 0)
                {
                    sprintf((char*)aTrbuf,"TM2 > interrupted. step = %d\n", steptm2-1);    
                    fsm2statectrl = MTCTRL_UARTTR;
                }
            }
            else
            {
                steptm2 = ProcessFsmTm2();
                isRunningTM2 = (steptm2 > 0);
            }
            break;
    }        
   
}