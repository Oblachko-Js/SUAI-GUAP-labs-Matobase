/*fsm_tm1.c*/
#include "fsm_tm1.h"
#include "fsm_main.h"
#include "timers.h"
#include "messages.h"
#include "i2cFram.h"
#include "uart.h"
#include "main.h"

/*состояния автомата*/

#define MTCTRL_RXCMD	0 // ожидание команды запуска
#define MTCTRL_PROC		1 // работа МТ
#define MTCTRL_RDFRAM	2 // чтение FRAM
#define MTCTRL_WRFRAM	3 // запись FRAM
#define MTCTRL_UARTTR	4 // передача UART

#define FSMST_Q0		0 // запуск МТ
#define FSMST_Q1		1 
#define FSMST_Q2		2
#define FSMST_Q3		3  
#define FSMST_Q4		4
#define FSMST_Q5		5
#define FSMST_Q6		6
#define FSMST_Q7		7
#define FSMST_Q8		8
#define FSMST_Q9		9
#define FSMST_Q10		10
#define FSMST_Q11		11
#define FSMST_QZ		12 // останов МТ

static uint32_t curraddrtm=0; // текущее положение каретки
static uint32_t nextaddrtm=0; // следущее положение каретки
int ProcTm1(uint8_t rsymb, uint8_t* wrsymb, int* steps); // итерация автомата МТ

// переменная состояния автомата контроля МТ
static char mtstatectrl = MTCTRL_RXCMD;   
// переменная состояния автомата МТ
static char fsmstate = FSMST_Q1;

int ProcessFsmTm1(void)
{
	static int steptm; 
	static uint8_t rdsymbol;
	static uint8_t wrsymbol;
	static uint8_t aTrbuf[32];
	uint8_t* pRxbuf=0;
	int curstep=0;
	static int steps1 = -1;
	switch (mtstatectrl)
	{
		case MTCTRL_RXCMD: // ожидание и анализ команды
			if(GetMessage(MSG_TM1STRT,(void*)&pRxbuf))
			{
				pRxbuf[lenfsm]=0;
				nextaddrtm=-1;
				steptm=-1;
				sscanf((char*)pRxbuf,"%x:%x",&nextaddrtm,&steptm);
				if(nextaddrtm>=0 && nextaddrtm<=0x7FF && steptm > 0)
				{// запуск МТ
					mtstatectrl = MTCTRL_RDFRAM;
					fsmstate = FSMST_Q0;
					ResetTimer(TM1_TIMER);
				}
				else
				{// синтаксическая ошибка в команде
					strcpy((char*)aTrbuf,"Err> cmd error\n");
					mtstatectrl = MTCTRL_UARTTR;
					steptm = -1;
					steps1 = -1;
				}
			}
			break;
		case MTCTRL_PROC:
            curstep=ProcTm1(rdsymbol,&wrsymbol, &steps1);
			if(curstep==-1 || curstep == steptm)
			{// остановка по стоп(-1) или количеству шагов
				sprintf((char*)aTrbuf,"TM1>stop addr=%03X sym='%c'\n",curraddrtm,wrsymbol);
				steptm = -1;
				steps1 = -1;
			}
			else
				sprintf((char*)aTrbuf,"TM1>step=%d addr=%03X sym='%c'\n",steps1,curraddrtm,wrsymbol);
			if(wrsymbol == rdsymbol) // если символы совпадают то запись пропускаем
				mtstatectrl = MTCTRL_UARTTR;
			else 
				mtstatectrl = MTCTRL_WRFRAM;
			break;
		case MTCTRL_RDFRAM:  
			curraddrtm=nextaddrtm; // переводим каретку 
			pRxbuf = (uint8_t*)i2cFRAM_rd(curraddrtm,1);
			if( (uint32_t)pRxbuf > 0)
			{//читаем один байт под кареткой
				rdsymbol=pRxbuf[0];
				mtstatectrl = MTCTRL_PROC;
			}
			break;
		case MTCTRL_WRFRAM: //пишем один байт
			if((uint32_t)i2cFRAM_wr(curraddrtm,&wrsymbol,1) > 0)
				mtstatectrl = MTCTRL_UARTTR;
			break;
		case MTCTRL_UARTTR:
			if(GetTimer(TM1_TIMER) > 1000) // 1000 msec
			{ // ожидаем время итерации
				lenfsm = strlen((char*)aTrbuf);
				if( uart_transmit(aTrbuf,lenfsm) == 0 )
				{ // передаём результат итерации в терминал 
					ResetTimer(TM1_TIMER);
					if(steptm == -1)
						mtstatectrl = MTCTRL_RXCMD;
					else
						mtstatectrl = MTCTRL_RDFRAM;
				}
			}
			break;
	}
    return steps1;
}

int ProcTm1(uint8_t rsymb,uint8_t* wrsymb, int* steps)
{
	static int stepcnt=0;
	*wrsymb=rsymb;
	stepcnt++;
	switch (fsmstate)
	{
		case FSMST_Q0:
			stepcnt=1;
		case FSMST_Q1: // q1
			if(rsymb == '_' || rsymb == 'a' || rsymb == 'b') {
				// _,_,R
                // a,a,R
                // b,b,R
				nextaddrtm = curraddrtm + 1;
				fsmstate = FSMST_Q2;
			}
			break;
		case FSMST_Q2: // q2
			if(rsymb == 'a' || rsymb == 'b') {
				// a,a,R
                // b,b,R
				nextaddrtm = curraddrtm + 1;
			} else if(rsymb == '_') {
                // _,_,L
				nextaddrtm = curraddrtm - 1;
				fsmstate = FSMST_Q3;
			}
			break;
		case FSMST_Q3: // q3
			if(rsymb == 'b') {
				nextaddrtm = curraddrtm - 1;
			} else if(rsymb == 'a') {
				*wrsymb = '*'; // a,*,L
				nextaddrtm = curraddrtm - 1;
				fsmstate = FSMST_Q4;
			} else if(rsymb == '_') {
				// _,_,S
				fsmstate = FSMST_QZ;
			}
			break;
		case FSMST_Q4: // q4
			if(rsymb == 'b') {
				nextaddrtm = curraddrtm - 1;
			} else if(rsymb == 'a') {
				*wrsymb = '*'; // a,*,R
				nextaddrtm = curraddrtm + 1;
				fsmstate = FSMST_Q5;
			} else if(rsymb == '_') {
                // _,_,R
				nextaddrtm = curraddrtm + 1;
				fsmstate = FSMST_Q5;
			}
			break;
		case FSMST_Q5: // q5
			if(rsymb == 'b' || rsymb == '*') {
				// b,b,R
				nextaddrtm = curraddrtm + 1;
			} else if(rsymb == '_') {
				*wrsymb = '>'; // _,>,L
				nextaddrtm = curraddrtm - 1;
				fsmstate = FSMST_Q6;
			}
			break;
		case FSMST_Q6: // q6
			if(rsymb == 'a' || rsymb == 'b' || rsymb == '*') {
				// a,a,L
                // b,b,L
                // *,*,L
				nextaddrtm = curraddrtm - 1;
			} else if(rsymb == '_') {
				// _,_,R
				nextaddrtm = curraddrtm + 1;
                fsmstate = FSMST_Q7;
			}
			break;
		case FSMST_Q7: // q7
			if(rsymb == '*') {
				*wrsymb = '_'; // *,_,R
                nextaddrtm = curraddrtm + 1;
			} else if(rsymb == 'a') {
				*wrsymb = '_'; // a,_,R
				nextaddrtm = curraddrtm + 1;
				fsmstate = FSMST_Q8;
			} else if(rsymb == 'b') {
				*wrsymb = '_'; // b,_,R
				nextaddrtm = curraddrtm + 1;
				fsmstate = FSMST_Q10;
			} else if(rsymb == '>') {
				*wrsymb = '_'; // >,_,S
				fsmstate = FSMST_QZ;
			}
			break;
		case FSMST_Q8: // q8
			if(rsymb == 'a' || rsymb == 'b' || rsymb == '*' || rsymb == '>') {
				// a,a,R
                // b,b,R
                // *,*,R
                // >,>,R
				nextaddrtm = curraddrtm + 1;
			} else if(rsymb == '_') {
				*wrsymb = 'a'; // _,a,L
				nextaddrtm = curraddrtm - 1;
				fsmstate = FSMST_Q9;
			}
			break;
		case FSMST_Q9: // q9
			if(rsymb == 'a' || rsymb == 'b') {
				// a,a,L
                // b,b,L
				nextaddrtm = curraddrtm - 1;
			} else if(rsymb == '>') {
				// >,>,L
				nextaddrtm = curraddrtm - 1;
				fsmstate = FSMST_Q6;
			}
			break;
		case FSMST_Q10: // q10
			if(rsymb == 'a' || rsymb == 'b' || rsymb == '*' || rsymb == '>') {
				// a,a,R
                // b,b,R
                // *,*,R
                // >,>,R
				nextaddrtm = curraddrtm + 1;
			} else if(rsymb == '_') {
				*wrsymb = 'b'; // _,b,L
				nextaddrtm = curraddrtm - 1;
				fsmstate = FSMST_Q11;
			}
			break;
		case FSMST_Q11: // q11
			if(rsymb == 'a' || rsymb == 'b') {
				// a,a,L
                // b,b,L
				nextaddrtm = curraddrtm - 1;
			} else if(rsymb == '>') {
				// >,>,L
				nextaddrtm = curraddrtm - 1;
				fsmstate = FSMST_Q6;
			}
			break;
		case FSMST_QZ: // qz (final state)
			stepcnt = -1; // Halt
			break;
	}
    *steps = stepcnt;
	return stepcnt;
}