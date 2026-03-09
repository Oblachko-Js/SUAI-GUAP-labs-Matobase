/*messages.h*/
#ifndef MESSAGES_h
#define MESSAGES_h

#define MAX_MESSAGES 		8

#define MSG_UART_RX			0 // сообщение о приёме пакета UART
#define MSG_TM1STRT			1 // сообщение о запуске машины тьюринга 1
#define MSG_TM2STRT			2	// сообщение о запуске машины тьюринга 2
#define MSG_TM3STRT			3	// сообщение о запуске машины тьюринга 2
#define MSG_TM1STOP			4	// сообщение о прерывании машины тьюринга 1
#define MSG_TM2STOP			5	// сообщение о прерывании машины тьюринга 2
#define MSG_TM3STOP			6	// сообщение о прерывании машины тьюринга 2
#define MSG_KEYPRESSED	    7 // сообщение о нажатии кнопок

void ProcessMessages(void);
void InitMessages(void);
void SendMessage(int Msg, void *ParamPtr);
char GetMessage(int Msg, void *ParamPtr);
#endif
