

/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: handle button interrupts
/****************************************************************/

#include "alldefs.h" // all defines
#include "typedefs.h"
#include "sysUtils.h"

extern uint8_t LCD_STATE;
extern uint16_t LCD_STATE2;
extern uint16_t SCREEN_MODE;
extern volatile u8 screenCod;
extern volatile u8 Decode_flat;
extern u8 main_menu;
volatile u8 screenCodnext ;


//volatile uint16_t crc, crcCheck;

// button bits
#define PRESSED 1
#define UNPRESSED 0
volatile struct btn_bits
{
    unsigned char BTN_1 : 1;
    unsigned char BTN_2 : 1;
    unsigned char BTN_3 : 1;
} btnLogBits;



/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: initializes buttons for input and interrupt
// INPUTs:
// OUTPUTs:
// HW DEPEDANCIES:
/****************************************************************/
void initButtons(GPIO_InitTypeDef *GPIO_InitStructure, EXTI_InitTypeDef *EXTI_InitStructure, NVIC_InitTypeDef *NVIC_InitStructure)
{
    // initialize variables
    btnLogBits.BTN_1 = UNPRESSED;
    btnLogBits.BTN_2 = UNPRESSED;
    btnLogBits.BTN_3 = UNPRESSED;

    /* Enable SYSCFG clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    /* Connect EXTI Line0 to pin */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource13);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource14);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource15);

    /* Configure EXTI Line */
    EXTI_InitStructure->EXTI_Line = EXTI_Line15|EXTI_Line14;
    EXTI_InitStructure->EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure->EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure->EXTI_LineCmd = ENABLE;

    EXTI_ClearITPendingBit(EXTI_Line13);
    EXTI_ClearITPendingBit(EXTI_Line14);
    EXTI_ClearITPendingBit(EXTI_Line15);
    EXTI_Init(EXTI_InitStructure);

    /* Enable and set EXTI Line0 Interrupt to priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure->NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure->NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure->NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure->NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(NVIC_InitStructure);


#ifdef TI_ST_CONNECTION

    /* Connect EXTI Line0 to pin */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

    // PA0 for TI_ST_STROBE interrupt
    /* Configure EXTI Line */
    EXTI_InitStructure->EXTI_Line = EXTI_Line0;
    EXTI_InitStructure->EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure->EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure->EXTI_LineCmd = ENABLE;
    EXTI_ClearITPendingBit(EXTI_Line0);
    EXTI_Init(EXTI_InitStructure);

    /* Enable and set EXTI Line0 Interrupt to priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure->NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure->NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure->NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure->NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(NVIC_InitStructure);
#endif

    ST_TI_FLAGS = 0;
    ST_TI_STATE = 0;
}

//*****************************************
// Author: E.Pataky
// Date: 8/21/13
// DESC: ISR for the I/O interrupt, call LCD function
// INPUTs:
// OUTPUTs:
// HW DEPEDANCIES:
//*****************************************
volatile u8 button = 0;
void EXTI15_10_IRQHandler() //iv IVT_INT_EXTI15_10 ics ICS_AUTO
{
#if 0 // David
    EXTI_PR.B15 = 1;                     // clear flag
#else
    EXTI_ClearITPendingBit(EXTI_Line15);
#endif

    //if(GPIOF_IDR.B15 == 0)
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_15) == Bit_RESET)
    {
        btnLogBits.BTN_3 = PRESSED;
        SET_PROCESS_BTNLOG;
        button  = 1;
    }
    else
    {
        btnLogBits.BTN_3 = UNPRESSED;
        button = 0;
    }
///*
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_14) == Bit_RESET)
    {
        btnLogBits.BTN_2 = PRESSED;
        SET_PROCESS_BTNLOG;
    }
    else
    {
        btnLogBits.BTN_2= UNPRESSED;
    }
    /*
        if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_13) == Bit_RESET)
        {
            btnLogBits.BTN_1 = PRESSED;
            SET_PROCESS_BTNLOG;
        }
        else
        {
            btnLogBits.BTN_1= UNPRESSED;
        }
       */
//*/

}


/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: handler task to process button presses
// INPUTs:
// OUTPUTs:
// HW DEPEDANCIES:
/****************************************************************/
void task_btnLog( void)
{

    //int i;

    if(!TST_PROCESS_BTNLOG_IN_PROG)
    {
        SET_PROCESS_BTNLOG_IN_PROG;
        /* To get here the event must have occurred.  Process the event (in this
        case we just print out a message). */

        // process buttons - debounce and make sure still pressed
        DEBOUNCE;
        if(btnLogBits.BTN_1 == PRESSED && GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_13) == 0)
        {
            screenCod = screenCodnext;
            if(screenCod >MAX_BG_DISPLAY) {
                screenCod = 1;
            }
            SET_PROCESS_LCD;
        }
        if(btnLogBits.BTN_2 == PRESSED && GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_14) == 0)
        {
            screenCod = screenCodnext;
            if(screenCod >MAX_BG_DISPLAY) {
                screenCod = 1;
            }
            SET_PROCESS_LCD;
        }

        if(btnLogBits.BTN_3 == PRESSED && GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_15) == Bit_RESET)
        {

            //screenCod++;
            screenCod = screenCodnext;
            if(screenCod >MAX_BG_DISPLAY) {
                screenCod = 1;
            }
            SET_PROCESS_LCD;
        }

        // clear all
        btnLogBits.BTN_1 = UNPRESSED;
        btnLogBits.BTN_2 = UNPRESSED;
        btnLogBits.BTN_3 = UNPRESSED;
        CLR_PROCESS_BTNLOG_IN_PROG;
    }
}

void Timer2_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    /* TIM2 clocks enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    //TIM_TimeBaseStructure.TIM_Prescaler = 1000;  /*100ms*/

    TIM_TimeBaseStructure.TIM_Prescaler = 5000;           /*500ms*/

    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 5000;/*0.1 ms for each couter*/
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
#if 0 // David
    NVIC_IntEnable(IVT_INT_TIM2); // Enable timer interrupt
#endif
}

void Timer2_Start(void)
{
    TIM_Cmd(TIM2, ENABLE);
}

void Timer2_Stop(void)
{
    TIM_Cmd(TIM2, DISABLE);
}
void Timer2_interrupt() //iv IVT_INT_TIM2
{
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    GPIO_ToggleBits(GPIOF, GPIO_Pin_14);

    // data_update();
}
