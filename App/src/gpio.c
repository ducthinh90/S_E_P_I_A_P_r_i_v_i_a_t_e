/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: handle button interrupts
/****************************************************************/

#include "alldefs.h" // all defines
#include "gpio.h"
#include "flashmem.h"

uint16_t BKL_CCR_Val_1 = 0, BKL_CCR_Val_2 = 0, BKL_CCR_Val_3 = 0, BKL_CCR_Val_4 = 0;
/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: helper function, set as spi, no pullups
// INPUTs:
// OUTPUTs:
// HW DEPEDANCIES:
/****************************************************************/
void setIOasSPI(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOx, GPIO_Pin); // default low
}

/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: helper function, set as output, no pullups
// INPUTs:
// OUTPUTs:
// HW DEPEDANCIES:
/****************************************************************/
void setIOasOUTPUT(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOx, GPIO_Pin); // default low
}

/**
  * E.Pataky - BKL_CTRL in schematic is pin PB0, = TIM3 CH3
  * @brief  Configure the TIM3 Ouput Channels.
  * @param  None
  * @retval None
  */
void TIM_Config(void)
{
    uint16_t TimerPeriod;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    GPIO_InitTypeDef GPIO_InitStructure;

    /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    /* GPIOC clock enable */
    //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    GPIO_StructInit(&GPIO_InitStructure);

    /* GPIOC Configuration: TIM3 CH3 (PB0) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Connect TIM3 pins to PB0 */
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3);

    /* TIM1 Configuration ---------------------------------------------------
            Generate PWM signals with duty cycles:
            TIM1 input clock (TIM1CLK) is set to 2 * APB2 clock (PCLK2), since APB2
            prescaler is different from 1.
            TIM1CLK = 2 * PCLK2
            PCLK2 = HCLK / 2
            => TIM1CLK = 2 * (HCLK / 2) = HCLK = SystemCoreClock
            TIM1CLK = SystemCoreClock, Prescaler = 0, TIM1 counter clock = SystemCoreClock
            SystemCoreClock is set to 120 MHz for STM32F2xx devices

            The objective is to generate PWM signal at 10 KHz:
             - TIM1_Period = (SystemCoreClock / 10240) - 1
             - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100

            Note:
            SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
            Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
            function to update SystemCoreClock variable value. Otherwise, any configuration
            based on this variable will be incorrect.
    ----------------------------------------------------------------------- */
    /* Compute the value to be set in ARR regiter to generate signal frequency at 10 Khz */
    //uint16_t TimerPeriod = ((SystemCoreClock / 5000) / 200 ) - 1; // 100 Hz - measured 50hz on scope

    // use this one with 4Mhz system core clock
    TimerPeriod = ((SystemCoreClock / 50) / 200 ) - 1; // 100 Hz - measured on scope

    /* Compute CCR1 value to generate a duty cycle at X% for channel 1 and 1N */
    BKL_CCR_Val_1 = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 100);
    BKL_CCR_Val_2 = (uint16_t) (((uint32_t) 10 * (TimerPeriod - 1)) / 100);
    BKL_CCR_Val_3 = (uint16_t) (((uint32_t) 15 * (TimerPeriod - 1)) / 100);
    BKL_CCR_Val_4 = (uint16_t) (((uint32_t) 50 * (TimerPeriod - 1)) / 100);

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
    TIM_TimeBaseStructure.TIM_Prescaler = 50;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /* PWM2 Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse = BKL_CCR_Val_4;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    /* TIM3 enable counter */
    TIM_Cmd(TIM3, ENABLE);
    /* TIM1 Main Output Enable */
    TIM_CtrlPWMOutputs(TIM3, ENABLE);
}


/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: helper function, set as output, with pullups
// INPUTs:
// OUTPUTs:
// HW DEPEDANCIES:
/****************************************************************/
void setIOasINPUT(GPIO_InitTypeDef *GPIO_InitStructure, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_StructInit(GPIO_InitStructure);
    GPIO_InitStructure->GPIO_Pin = GPIO_Pin;
    GPIO_InitStructure->GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure->GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure->GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOx, GPIO_InitStructure);
}

/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: turn on/off peripheral clocks
// INPUTs: ON: 1=on, 0=off
// OUTPUTs:
// HW DEPEDANCIES:
/****************************************************************/
void peripheralClocksOnOff(uint8_t ON)
{
    if(ON == 1)
    {
        /* Enable GPIO clocks needed */
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    }
    else
    {
        /* Enable GPIO clocks needed */
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, DISABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, DISABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, DISABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, DISABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, DISABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, DISABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, DISABLE);
    }
}

/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: setup all gpio
// INPUTs:
// OUTPUTs:
// HW DEPEDANCIES:
/****************************************************************/
void initGPIO(GPIO_InitTypeDef *GPIO_InitStructure)
{
    peripheralClocksOnOff(1);

    // LEDs on board LED1-4, DEMO BOARD ONLY
#ifdef SEE_LED
    //setIOasOUTPUT( GPIOA, GPIO_Pin_4);
    // GPIO_ResetBits(GPIOA, GPIO_Pin_4);
#endif
    //setIOasOUTPUT( GPIOA, GPIO_Pin_5);
    //setIOasOUTPUT( GPIOA, GPIO_Pin_6);
    //setIOasOUTPUT( GPIOA, GPIO_Pin_7);

#ifdef TIMING_PIN
    setIOasOUTPUT( GPIOA, GPIO_Pin_7);
    GPIO_ResetBits(GPIOA, GPIO_Pin_7);
#endif

#ifdef USE_LCD
    // setup IOs as outputs- ST MICRO PIN / SCHEMATIC LABEL

    setIOasOUTPUT( GPIOF, GPIO_Pin_12);       // PF12 / BS0
    LCD_BS0_L; // always low for 16-bit

    setIOasOUTPUT( GPIOF, GPIO_Pin_13);       // PF13 / BS1
    LCD_BS1_L; // always low for 16-bit

    setIOasOUTPUT( GPIOE, GPIO_Pin_2);       // PE2 / LCD_RST
    LCD_RST_H;

    //setIOasINPUT(GPIO_InitStructure, GPIOF, GPIO_Pin_13);                 // button 1
    //setIOasINPUT(GPIO_InitStructure, GPIOF, GPIO_Pin_14);                 // button 2
    setIOasINPUT(GPIO_InitStructure, GPIOF, GPIO_Pin_15);                 // button 3
#endif

#ifdef TEST_ONLY_MCOOUT
    /* Output HSE clock on MCO2 pin(PC9) ****************************************/
    /* Enable the GPIOC peripheral */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    /* Configure MCO1 pin(PA8) in alternate function */
    GPIO_StructInit(GPIO_InitStructure);
    GPIO_InitStructure->GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure->GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure->GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure->GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure->GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, GPIO_InitStructure);

    /* HSE clock selected to output on MCO2 pin(PC9)*/
    RCC_MCO2Config(RCC_MCO2Source_SYSCLK, RCC_MCO2Div_1);
#endif

    setIOasOUTPUT( GPIOC, GPIO_Pin_3); // test timer
    setIOasOUTPUT( GPIOD, GPIO_Pin_5); // test timer

    //flashMemCfg();

#ifdef TI_ST_CONNECTION
    //        TI and ST connected by parallel interface:
    //    TI_ST_D0 - TI_ST_D7 are PG0 to PG7 (input)
    setIOasINPUT(GPIO_InitStructure, GPIOG, GPIO_Pin_0);
    setIOasINPUT(GPIO_InitStructure, GPIOG, GPIO_Pin_1);
    setIOasINPUT(GPIO_InitStructure, GPIOG, GPIO_Pin_2);
    setIOasINPUT(GPIO_InitStructure, GPIOG, GPIO_Pin_3);
    setIOasINPUT(GPIO_InitStructure, GPIOG, GPIO_Pin_4);
    setIOasINPUT(GPIO_InitStructure, GPIOG, GPIO_Pin_5);
    setIOasINPUT(GPIO_InitStructure, GPIOG, GPIO_Pin_6);
    setIOasINPUT(GPIO_InitStructure, GPIOG, GPIO_Pin_7);

    //    TI_ST_STROBE is PA0 (input, interrupt enabled)
    setIOasINPUT(GPIO_InitStructure, GPIOA, GPIO_Pin_0);
    // INT
    //    TI_ST_BUSY is PF11 (input)
    setIOasINPUT(GPIO_InitStructure, GPIOF, GPIO_Pin_11);
    //    ST_TI_D0 - ST_TI_D7 are PG8 to PG15 (output)
    setIOasOUTPUT(GPIOG, GPIO_Pin_8);
    setIOasOUTPUT(GPIOG, GPIO_Pin_9);
    setIOasOUTPUT(GPIOG, GPIO_Pin_10);
    setIOasOUTPUT(GPIOG, GPIO_Pin_11);
    setIOasOUTPUT(GPIOG, GPIO_Pin_12);
    setIOasOUTPUT(GPIOG, GPIO_Pin_13);
    setIOasOUTPUT(GPIOG, GPIO_Pin_14);
    setIOasOUTPUT(GPIOG, GPIO_Pin_15);
    //    ST_TI_STROBE is PF8 (output)
    setIOasOUTPUT(GPIOF, GPIO_Pin_8);
    ST_TI_STROBE_L;
    //    ST_TI_BUSY is PF9 (outpu)
    setIOasOUTPUT(GPIOF, GPIO_Pin_9);
    ST_TI_BUSY_L;

#endif

#ifndef BOARD_TYPE_2
    // recharge circuit setup
    setIOasINPUT(GPIO_InitStructure, GPIOD, GPIO_Pin_12);
    setIOasINPUT(GPIO_InitStructure, GPIOD, GPIO_Pin_13);
    setIOasOUTPUT( GPIOB, GPIO_Pin_1);
    GPIO_SetBits(GPIOB, GPIO_Pin_1);
    setIOasOUTPUT( GPIOB, GPIO_Pin_2);
    GPIO_SetBits(GPIOB, GPIO_Pin_2);


#endif

}
