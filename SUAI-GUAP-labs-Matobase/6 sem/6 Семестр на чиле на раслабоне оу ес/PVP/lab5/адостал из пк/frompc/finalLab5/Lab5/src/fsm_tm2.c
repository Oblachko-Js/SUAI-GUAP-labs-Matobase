/*fsm_tm2.c*/
#include "fsm_tm2.h"
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
#define FSMST_QZ		5 // останов МТ

static uint32_t curraddrtm=0; // текущее положение каретки
static uint32_t nextaddrtm=0; // следущее положение каретки
int ProcTm2(uint8_t rsymb, uint8_t* wrsymb, int* steps); // итерация автомата МТ

// переменная состояния автомата контроля МТ
static char mtstatectrl = MTCTRL_RXCMD;   
// переменная состояния автомата МТ
static char fsmstate = FSMST_Q1;

int ProcessFsmTm2(void)
{
	static int steptm; 
	static uint8_t rdsymbol;
	static uint8_t wrsymbol;
	static uint8_t aTrbuf[32];
	uint8_t* pRxbuf=0;
	int curstep=0;
	static int steps2 = -1;
	switch (mtstatectrl)
	{
		case MTCTRL_RXCMD: // ожидание и анализ команды
			if(GetMessage(MSG_TM2STRT,(void*)&pRxbuf))
			{
				pRxbuf[lenfsm]=0;
				nextaddrtm=-1;
				steptm=-1;
				sscanf((char*)pRxbuf,"%x:%x",&nextaddrtm,&steptm);
				if(nextaddrtm>=0 && nextaddrtm<=0x7FF && steptm > 0)
				{// запуск МТ
					mtstatectrl = MTCTRL_RDFRAM;
					fsmstate = FSMST_Q0;
					ResetTimer(TM2_TIMER);
				}
				else
				{// синтаксическая ошибка в команде
					strcpy((char*)aTrbuf,"Err> cmd error\n");
					mtstatectrl = MTCTRL_UARTTR;
					steptm = -1;
					steps2 = -1;
				}
			}
			break;
		case MTCTRL_PROC:
			curstep=ProcTm2(rdsymbol,&wrsymbol, &steps2);
			if(curstep==-1 || curstep == steptm)
			{// остановка по стоп(-1) или количеству шагов
				sprintf((char*)aTrbuf,"TM2>stop addr=%03X sym='%c'\n",curraddrtm,wrsymbol);
				steptm = -1;
				steps2 = -1;
			}
			else
				sprintf((char*)aTrbuf,"TM2>step=%d addr=%03X sym='%c'\n",steps2,curraddrtm,wrsymbol);
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
			if(GetTimer(TM2_TIMER) > 1000) // 1000 msec
			{ // ожидаем время итерации
				lenfsm = strlen((char*)aTrbuf);
				if( uart_transmit(aTrbuf,lenfsm) == 0 )
				{ // передаём результат итерации в терминал 
					ResetTimer(TM2_TIMER);
					if(steptm == -1)
						mtstatectrl = MTCTRL_RXCMD;
					else
						mtstatectrl = MTCTRL_RDFRAM;
				}
			}
			break;
	}
    return steps2;
}

int ProcTm2(uint8_t rsymb,uint8_t* wrsymb, int* steps)
{
	static int stepcnt=0;
	*wrsymb=rsymb;
	stepcnt++;
	switch (fsmstate)
	{
		case FSMST_Q0:
			stepcnt=0;
		case FSMST_Q1:
			if (rsymb == '(')
			{
				nextaddrtm = curraddrtm + 1;
				fsmstate = FSMST_Q2;
			}
			else if (rsymb == '_' || rsymb == 'x' || rsymb == ')')
            {
				nextaddrtm = curraddrtm + 1;
                fsmstate = FSMST_Q1;
            }
			break;
		case FSMST_Q2:
			if (rsymb == ')')
			{
				*wrsymb = 'x';
				nextaddrtm = curraddrtm - 1;
				fsmstate = FSMST_Q3;
			}
			else if (rsymb == 'x' || rsymb == '(')
				nextaddrtm = curraddrtm + 1;
            else if (rsymb == '_')
				fsmstate = FSMST_QZ;
			break;
		case FSMST_Q3:
			if (rsymb == '_')
			{
				nextaddrtm = curraddrtm + 1;
				fsmstate = FSMST_Q4;
			}
			else if (rsymb == 'x' || rsymb == '(' || rsymb == ')')
				nextaddrtm = curraddrtm - 1;
			break;
		case FSMST_Q4:
			if (rsymb == '(')
			{
				*wrsymb = 'x';
				nextaddrtm = curraddrtm + 1;
				fsmstate = FSMST_Q1;
			}
			else if (rsymb == '_' || rsymb == 'x' || rsymb == ')')
				nextaddrtm = curraddrtm + 1;
			break;
		case FSMST_QZ:
			stepcnt = -1;
			break;
	}
    *steps = stepcnt;
	return stepcnt;
}