/*fsm_tm3.c*/
#include "fsm_tm3.h"
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
#define FSMST_QZ		10 // останов МТ

static uint32_t curraddrtm=0; // текущее положение каретки
static uint32_t nextaddrtm=0; // следущее положение каретки
int ProcTm3(uint8_t rsymb, uint8_t* wrsymb, int* steps); // итерация автомата МТ

// переменная состояния автомата контроля МТ
static char mtstatectrl = MTCTRL_RXCMD;   
// переменная состояния автомата МТ
static char fsmstate = FSMST_Q1;
	
int ProcessFsmTm3(void)
{
	static int steptm; 
	static uint8_t rdsymbol;
	static uint8_t wrsymbol;
	static uint8_t aTrbuf[32];
	uint8_t* pRxbuf=0;
	int curstep=0;
	static int steps3 = -1;
	switch (mtstatectrl)
	{
		case MTCTRL_RXCMD: // ожидание и анализ команды
			if(GetMessage(MSG_TM3STRT,(void*)&pRxbuf))
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
					steps3 = -1;
				}
			}
			break;
		case MTCTRL_PROC:
			curstep=ProcTm3(rdsymbol,&wrsymbol, &steps3);
			if(curstep==-1 || curstep == steptm)
			{// остановка по стоп(-1) или количеству шагов
				sprintf((char*)aTrbuf,"TM3>stop addr=%03X sym='%c'\n",curraddrtm,wrsymbol);
				steptm = -1;
				steps3 = -1;
			}
			else
				sprintf((char*)aTrbuf,"TM3>step=%d addr=%03X sym='%c'\n",steps3,curraddrtm,wrsymbol);
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
			if(GetTimer(TM3_TIMER) > 1000) // 1000 msec
			{ // ожидаем время итерации
				lenfsm = strlen((char*)aTrbuf);
				if( uart_transmit(aTrbuf,lenfsm) == 0 )
				{ // передаём результат итерации в терминал 
					ResetTimer(TM3_TIMER);
					if(steptm == -1)
						mtstatectrl = MTCTRL_RXCMD;
					else
						mtstatectrl = MTCTRL_RDFRAM;
				}
			}
			break;
	}
	return steps3;
}

int ProcTm3(uint8_t rsymb,uint8_t* wrsymb, int* steps)
{
	static int stepcnt=0;
	*wrsymb=rsymb;
	stepcnt++;
	switch (fsmstate)
	{
		case FSMST_Q0:
			stepcnt=1;
		case FSMST_Q1:
			if (rsymb == 'a' || rsymb == 'b' || rsymb == 'c')
			{
				nextaddrtm = curraddrtm + 1;
			}
			else 
			{
				nextaddrtm = curraddrtm - 1;
				fsmstate = FSMST_Q2;
			}
			break;
		case FSMST_Q2:
			if (rsymb == 'b' == rsymb == 'c')
			{
				nextaddrtm = curraddrtm - 1;
			}
			else if (rsymb == '_')
			{
				fsmstate = FSMST_QZ;
			}
			else if (rsymb == 'a')
			{
				nextaddrtm = curraddrtm + 1;
				fsmstate = FSMST_Q3;
			}
			break;
		case FSMST_Q3:
			if (rsymb == 'b')
			{
				*wrsymb = '_';
				nextaddrtm = curraddrtm + 1;
				fsmstate = FSMST_Q4;
			}
			else if (rsymb == 'c')
			{
				*wrsymb = '_';
				nextaddrtm = curraddrtm + 1;
				fsmstate = FSMST_Q5;
			}
			else if (rsymb == '_')
			{
				*wrsymb = 'b';
				nextaddrtm = curraddrtm - 1;
				fsmstate = FSMST_Q9;
			}
			break;
		case FSMST_Q4:
			if (rsymb == 'b')
			{
				nextaddrtm = curraddrtm + 1;
			}
			else if (rsymb == 'c')
			{
				*wrsymb = 'b';
				nextaddrtm = curraddrtm + 1;
				fsmstate = FSMST_Q6;
			}
			else if (rsymb == '_')
			{
				*wrsymb = 'b';
				nextaddrtm = curraddrtm - 1;
				fsmstate = FSMST_Q8;
			}
			break;
		case FSMST_Q5:
			if (rsymb == 'c')
			{
				nextaddrtm = curraddrtm + 1;
			}
			else if (rsymb == 'b')
			{
				*wrsymb = 'c';
				nextaddrtm = curraddrtm + 1;
				fsmstate = FSMST_Q7;
			}
			else if (rsymb == '_')
			{
				*wrsymb = 'c';
				nextaddrtm = curraddrtm - 1;
				fsmstate = FSMST_Q8;
			}
			break;
		case FSMST_Q6:
			if (rsymb == 'c')
			{
				nextaddrtm = curraddrtm + 1;
			}
			else if (rsymb == '_')
			{
				*wrsymb = 'c';
				nextaddrtm = curraddrtm - 1;
				fsmstate = FSMST_Q8;
			}
			else if (rsymb == 'b')
			{
				*wrsymb = 'c';
				nextaddrtm = curraddrtm + 1;
				fsmstate = FSMST_Q4;
			}
			break;
		case FSMST_Q7:
			if (rsymb == 'b')
			{
				nextaddrtm = curraddrtm + 1;
			}
			else if (rsymb == '_')
			{
				*wrsymb = 'b';
				nextaddrtm = curraddrtm - 1;
				fsmstate = FSMST_Q8;
			}
			else if (rsymb == 'c')
			{
				*wrsymb = 'b';
				nextaddrtm = curraddrtm + 1;
				fsmstate = FSMST_Q5;
			}
			break;
		case FSMST_Q8:
			if (rsymb == 'c' || rsymb == 'b')
			{
				nextaddrtm = curraddrtm - 1;
			}
			else if (rsymb == '_')
			{
				*wrsymb = 'b';
				nextaddrtm = curraddrtm - 1;
				fsmstate = FSMST_Q9;
			}
			break;
		case FSMST_Q9:
			if (rsymb == 'a')
			{
				*wrsymb = 'b';
				fsmstate = FSMST_QZ;
			}
			break;
		case FSMST_QZ:
			stepcnt = -1;
			break;
	}
	*steps = stepcnt;
	return stepcnt;
}