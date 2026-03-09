/*fsm_inter_tm1.c*/
#include "fsm_inter_tm1.h"
#include "fsm_tm1.h"
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
static char fsm1statectrl = MTCTRL_PROC; 

static char isRunningTM1 = 0;
int steptm1;
void ProcessFsmInterTm1 (void)
{
    uint8_t* pRxbuf=0;
    static uint8_t aTrbuf[32];
    switch (fsm1statectrl)
    {
        case MTCTRL_UARTTR:
            if(GetTimer(TM1_TIMER) > 1000) // 1000 msec
			{ // ожидаем время итерации
				lenfsm = strlen((char*)aTrbuf);
				if( uart_transmit(aTrbuf,lenfsm) == 0 )
				{ // передаём результат итерации в терминал 
					ResetTimer(TM1_TIMER);
                    fsm1statectrl = MTCTRL_PROC;
				}
			}
            break;
        case MTCTRL_PROC:
            if (GetMessage(MSG_TM1STOP, (void*)&pRxbuf))
            {
                if (steptm1 > 0)
                {
                    sprintf((char*)aTrbuf,"TM1 > interrupted. step = %d\n", steptm1-1);    
                    fsm1statectrl = MTCTRL_UARTTR;
                }
            }
            else
            {
                steptm1 = ProcessFsmTm1();
                isRunningTM1 = (steptm1 > 0);
            }
            break;
    }        
   
}