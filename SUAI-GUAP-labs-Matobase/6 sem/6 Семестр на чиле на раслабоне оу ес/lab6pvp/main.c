#include "RTE_Components.h"
#include <stdio.h>
#include <math.h>
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_rcc.h"
#include "stm32f3xx_ll_system.h"
#include "stm32f3xx_ll_gpio.h"
#include "stm32f3xx_ll_tim.h"
#include "stm32f3xx_ll_dma.h"

#define PI (4*atan(1))
#define FS 125874  // ??????? ????????????? ??? TIM3
#define Fsin 15734 // ??????? ?????????
#define TIM3_ARR 285 // ???????? ???????? ????-???????????? TIM3
#define SIZE 24    // ?????? ??????? ??? ????????? ???????

typedef struct {
    uint16_t m_sgnlVal[20]; // ?????? ???????? ??????? (?? ?????? 20)
    uint16_t cntsgnl;       // ??????? ???????? ???????
    uint16_t szsgnl;        // ???-?? ???????? ? ???????
} st_sgnlparam;

__IO st_sgnlparam t_sgnl; // ?????? ???????? ??? ???????
__IO uint32_t uwPeriodVal[SIZE]; // ?????? ???????? ??? ????????? ???????
__IO uint32_t uwCntPeriod = 0;   // ??????? ???????? ??????? ??? ?????????

int main(void) {
    /**** ????????? ????????? ??????? = 36 MHz ****/
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
    while (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_1) {}
    LL_RCC_HSE_EnableBypass();
    LL_RCC_HSE_Enable();
    while (LL_RCC_HSE_IsReady() != 1) {}
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_2); // AHB Prescaler = 2 (72 MHz / 2 = 36 MHz)
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1); // APB1 Prescaler = 1
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1); // APB2 Prescaler = 1
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {}
    SystemCoreClockUpdate();
    printf("Set SysClk=%d Hz\n", SystemCoreClock);

    /**** ????????? ???????? ????????? ??? TIM3 ****/
    t_sgnl.szsgnl = FS / Fsin; // ?????????? ???????? (????? 8)
    float sgnlAmpltd = TIM3_ARR / 2; // ????????? ?????????
    t_sgnl.cntsgnl = 0;
    for (t_sgnl.cntsgnl = 0; t_sgnl.cntsgnl < t_sgnl.szsgnl; t_sgnl.cntsgnl++) {
        t_sgnl.m_sgnlVal[t_sgnl.cntsgnl] = (uint16_t)(sgnlAmpltd * (1.0 + sin(2 * PI * Fsin * (float)(t_sgnl.cntsgnl) / FS)));
    }
    t_sgnl.cntsgnl = 0;

    /**** ???????? ??? ????? PA2 (TIM15_CH1), PB0 (TIM3_CH1), PE13 (TIM1_CH4) ****/
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA | LL_AHB1_GRP1_PERIPH_GPIOB | LL_AHB1_GRP1_PERIPH_GPIOE);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);

    // GPIO PA2 -> TIM15_CH1
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_2, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_2, LL_GPIO_AF_9);

    // GPIO PB0 -> TIM3_CH1
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_0, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_0, LL_GPIO_AF_2);

    // GPIO PE13 -> TIM1_CH4 (???? ??? ???????)
    LL_GPIO_SetPinMode(GPIOE, LL_GPIO_PIN_13, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_8_15(GPIOE, LL_GPIO_PIN_13, LL_GPIO_AF_2);
    LL_GPIO_SetPinSpeed(GPIOE, LL_GPIO_PIN_13, LL_GPIO_SPEED_FREQ_HIGH);

    /**** ????????? TIM15 (Master) ****/
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM15);
    LL_TIM_SetAutoReload(TIM15, 27480); // TIM15_ARR = 27480 (??? 1310 ??)
    LL_TIM_OC_SetMode(TIM15, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
    LL_TIM_OC_SetCompareCH1(TIM15, 4122); // ??????????? ?????????? 0.15 * TIM15_ARR
    LL_TIM_EnableAutomaticOutput(TIM15);
    LL_TIM_CC_EnableChannel(TIM15, LL_TIM_CHANNEL_CH1);
    LL_TIM_SetTriggerOutput(TIM15, LL_TIM_TRGO_UPDATE); // TRGO ?? ??????????

    /**** ????????? TIM3 (Slave) ? DMA ****/
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
    LL_TIM_SetAutoReload(TIM3, TIM3_ARR); // TIM3_ARR = 285
    LL_TIM_OC_SetMode(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
    LL_TIM_OC_SetCompareCH1(TIM3, t_sgnl.m_sgnlVal[0]);
    LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH1);
    LL_TIM_EnableAutomaticOutput(TIM3);
    LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH1);
    LL_TIM_SetTriggerInput(TIM3, LL_TIM_TS_ITR2); // TIM15_TRGO -> TIM3_ITR2
    LL_TIM_SetSlaveMode(TIM3, LL_TIM_SLAVEMODE_TRIGGER);

    // ????????? DMA ??? TIM3
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
    LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_3, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
    LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_3, LL_DMA_MODE_CIRCULAR);
    LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_3, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_3, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_3, LL_DMA_PDATAALIGN_HALFWORD);
    LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_3, LL_DMA_MDATAALIGN_HALFWORD);
    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_3, (uint32_t)&TIM3->CCR1);
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_3, (uint32_t)t_sgnl.m_sgnlVal);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, t_sgnl.szsgnl);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);
    LL_TIM_EnableDMAReq_UPDATE(TIM3);

    /**** ????????? TIM1 ??? ??????? (PE13) ****/
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
    NVIC_EnableIRQ(TIM1_CC_IRQn);
    LL_TIM_SetPrescaler(TIM1, 0); // TIM1_PSC = 0 (36 MHz)
    LL_TIM_SetAutoReload(TIM1, 0xFFFF); // TIM1_ARR = 65535
    LL_TIM_IC_SetActiveInput(TIM1, LL_TIM_CHANNEL_CH4, LL_TIM_ACTIVEINPUT_DIRECTTI);
    LL_TIM_IC_SetPrescaler(TIM1, LL_TIM_CHANNEL_CH4, LL_TIM_ICPSC_DIV1);
    LL_TIM_SetClockDivision(TIM1, LL_TIM_CLOCKDIVISION_DIV1);
    LL_TIM_IC_SetFilter(TIM1, LL_TIM_CHANNEL_CH4, LL_TIM_IC_FILTER_FDIV1); // ??? ???????
    LL_TIM_IC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH4, LL_TIM_IC_POLARITY_RISING);
    LL_TIM_EnableIT_CC4(TIM1);
    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH4);
    LL_TIM_GenerateEvent_UPDATE(TIM1);
    LL_TIM_EnableCounter(TIM1);

    /**** ?????? ???????? ****/
    LL_TIM_EnableCounter(TIM15); // ????????? Master ??????

    /**** ????????? ? ????? ??????????? ****/
    uint32_t PSC = 0, IC1PSC = 0, uwMeasuredFrequency = 0;
    int i;
    while (1) {
        if (uwCntPeriod == SIZE) {
            LL_TIM_DisableCounter(TIM15);
            PSC = LL_TIM_GetPrescaler(TIM1);
            IC1PSC = __LL_TIM_GET_ICPSC_RATIO(LL_TIM_IC_GetPrescaler(TIM1, LL_TIM_CHANNEL_CH4));
            printf("start\n");
            for (i = 0; i < SIZE; i++) {
                if (uwPeriodVal[i] > 0) {
                    uwMeasuredFrequency = (SystemCoreClock * IC1PSC) / (uwPeriodVal[i] * (PSC + 1));
                    printf("%7d # %7d\n", uwPeriodVal[i], uwMeasuredFrequency);
                } else {
                    printf("%7d # measurement limit\n", uwPeriodVal[i]);
                }
                uwPeriodVal[i] = 0;
            }
            printf("end\n");
            uwCntPeriod = 0;
            NVIC_EnableIRQ(TIM1_CC_IRQn);
            LL_TIM_EnableCounter(TIM15);
        }
    }
}

void TIM1_CC_IRQHandler(void) {
    static uint32_t uwICValue1 = 0;
    uint32_t uwICValue2 = 0, uwDiffCapture = 0;
    if (LL_TIM_IsActiveFlag_CC4(TIM1) == 1) {
        LL_TIM_ClearFlag_CC4(TIM1);
        uwICValue2 = LL_TIM_IC_GetCaptureCH4(TIM1);
        if (uwICValue2 > uwICValue1) {
            uwDiffCapture = (uwICValue2 - uwICValue1);
        } else if (uwICValue2 < uwICValue1) {
            uwDiffCapture = ((0xFFFF - uwICValue1) + uwICValue2) + 1;
        } else {
            uwDiffCapture = 0;
        }
        uwPeriodVal[uwCntPeriod++] = uwDiffCapture;
        uwICValue1 = uwICValue2;
        if (uwCntPeriod == SIZE) {
            NVIC_DisableIRQ(TIM1_CC_IRQn);
        }
    }
}