/*keypad.c*/
#include "timers.h"
#include "messages.h"
#include "keypad.h"
#include "main.h"

/*состояния автомата*/
// ожидание нажатия
#define FSMST_IDLE			0

// ожидание истечении времени дребезга (DEBOUNCE)
#define FSMST_DEBOUNCE		1

// контроль состояния кнопки после истечения времени дребезга
// формируется сообщение MSG_KEY_PRESSED, если кнопка нажата
// возврат в состояние FSMST_IDLE, если кнопка отпущена
#define FSMST_KEYDOWN		2

// контроль состояния кнопки при первом удержании (FIRST_DELAY), по истечению,
// формируется повторное сообщение MSG_KEY_PRESSED, если кнопка нажата,
// возврат в состояние FSMST_IDLE, если кнопка отпущена
#define FSMST_KEYDOWNHOLD	3

// контроль состояния кнопки при дальнейшем удержании (AUTO_REPEAT), по истечению,
// формируется сообщение MSG_KEY_PRESSED, если кнопка нажата,
// возврат в состояние FSMST_IDLE, если кнопка отпущена
#define FSMST_HOLDAUTO		4


static char fsmstate = FSMST_IDLE;   // переменная состояния автомата
uint16_t scankeypad(void);

uint16_t scankeypad(void)
{
	uint16_t key_code=0;
	uint8_t tmpbuf=0;
	int i;
	for(i=0; i<4; i++) 
	{
		LL_GPIO_ResetOutputPin(GPIOC,1<<(4+i));
		__NOP(); __NOP(); __NOP(); __NOP();
		tmpbuf= (uint8_t)LL_GPIO_ReadInputPort(GPIOC);
		tmpbuf= ~tmpbuf & 0x0F;
		key_code |=tmpbuf<<(4*i);
		LL_GPIO_SetOutputPin(GPIOC,1<<(4+i));
	}
	return key_code;
}

void InitKpd4(void) 
{
	fsmstate=FSMST_IDLE;
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);//GPIOC
	//PC0,PC1,PC2,PC3 In
	LL_GPIO_InitTypeDef gpio_initstruct;
	gpio_initstruct.Pin  = LL_GPIO_PIN_0|LL_GPIO_PIN_1|LL_GPIO_PIN_2|LL_GPIO_PIN_3;
	gpio_initstruct.Mode = LL_GPIO_MODE_INPUT;
	gpio_initstruct.Pull = LL_GPIO_PULL_UP;
	if (LL_GPIO_Init(GPIOC, &gpio_initstruct) != SUCCESS)
		while (1){} 		/* Initialization Error */
	
	//PC4,PC5,PC6,PC7 Out
	gpio_initstruct.Pin  = LL_GPIO_PIN_4|LL_GPIO_PIN_5|LL_GPIO_PIN_6|LL_GPIO_PIN_7;
	gpio_initstruct.Mode = LL_GPIO_MODE_OUTPUT;
	gpio_initstruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	gpio_initstruct.Pull = LL_GPIO_PULL_UP;
	if (LL_GPIO_Init(GPIOC, &gpio_initstruct) != SUCCESS)
		while (1){} 		/* Initialization Error */
	LL_GPIO_SetOutputPin (GPIOC, LL_GPIO_PIN_4|LL_GPIO_PIN_5|LL_GPIO_PIN_6|LL_GPIO_PIN_7);
	printf("\nKeypad init\n");
}

// Добавляем обработку специальных кнопок
char GetKeyPressed(uint8_t key_num) {
    static uint16_t prev_keys = 0;
    static uint8_t k1_debounce = 0;
    static uint8_t k2_debounce = 0;
    
    uint16_t current_keys = scankeypad();
    
    // Обработка K1
    if(key_num == K1_KEYNUM) {
        if(current_keys & (1 << K1_KEYNUM)) {
            if(++k1_debounce >= DEBOUNCE/5) { // 5ms период вызова
                k1_debounce = 0;
                return 1;
            }
        } else {
            k1_debounce = 0;
        }
        return 0;
    }
    
    // Обработка K2
    if(key_num == K2_KEYNUM) {
        if(current_keys & (1 << K2_KEYNUM)) {
            if(++k2_debounce >= DEBOUNCE/5) {
                k2_debounce = 0;
                return 1;
            }
        } else {
            k2_debounce = 0;
        }
        return 0;
    }
    
    return 0;
}

// Модифицированная ProcessKeyKpd4
void ProcessKeyKpd4(void) {
    static uint16_t prev_key_code = 0;
    
    if(GetTimer(KPD4_TIMER) >= 5) { // Каждые 5 мс
        ResetTimer(KPD4_TIMER);
        uint16_t key_code = scankeypad();
        
        // Обработка K1
        if(GetKeyPressed(K1_KEYNUM)) {
            SendMessage(MSG_TM1_STOP, NULL);
        }
        
        // Обработка K2
        if(GetKeyPressed(K2_KEYNUM)) {
            SendMessage(MSG_TM2_STOP, NULL);
        }
        
        // Оригинальная логика обработки клавиатуры
        if(key_code != prev_key_code) {
            // ... существующий код ...
        }
        prev_key_code = key_code;
    }
}