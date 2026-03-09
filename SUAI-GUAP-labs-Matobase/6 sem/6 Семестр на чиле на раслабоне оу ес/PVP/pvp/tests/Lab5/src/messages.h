/*messages.h*/
#ifndef MESSAGES_h
#define MESSAGES_h

#define MAX_MESSAGES 		4

#define MSG_UART_RX			0 // сообщение о приёме пакета UART
#define MSG_TM1STRT			1 // сообщение о запуске машины тьюринга
#define MSG_TM2STRT     2  // ????????? ??? ??????? ?????? ??
#define MSG_KEYPRESSED		3 // сообщение о нажатии кнопок

void ProcessMessages(void);
void InitMessages(void);
void SendMessage(int Msg, void *ParamPtr);
char GetMessage(int Msg, void *ParamPtr);
#endif
