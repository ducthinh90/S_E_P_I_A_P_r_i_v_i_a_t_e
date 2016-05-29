/****************************************************************/
// Author:npthinh
// Date:
// Desc: basic setup project for SEPIA
/****************************************************************/

#include "alldefs.h" // all defines
#include "handleButtons.h"
#include "gpio.h"
//#include "system_stm32f2xx.h"
#include "fwDefs.h"
#include "flashmem.h"
#include "text.h"
#include "sysUtils.h"
#include "fwUpdate.h"
#include "textUtils.h"
#include "sysCtrl.h"
#include "sonarCmd.h"

extern const tChar myriad_bold_9[];
extern const tChar myriad_bold_10[];
extern const tChar myriad_bold_13[];
extern const tChar myriad_bold_14[];
extern const tChar myriad_bold_15[];
extern const tChar myriad_bold_16[];
extern const tChar myriad_bold_17[];
extern const tChar myriad_bold_18[];
extern const tChar myriad_bold_19[];
extern const tChar myriad_bold_20[];
extern const tChar myriad_bold_22[];
extern const tChar myriad_bold_23[];
extern const tChar myriad_bold_28[];
extern const tChar myriad_bold_30[];
extern const tChar myriad_bold_32[];
extern const tChar myriad_bold_35[];
extern const tChar myriad_bold_40[];
extern const tChar myriad_bold_42[];
extern const tChar myriad_bold_45[];
extern const tChar myriad_bold_50[];
extern const tChar myriad_bold_57[];
extern const tChar DinCondense_Bold_57[];
extern const uint16_t BMP_Menu_Top[21][320];
volatile u8 ST_ready_get_data;
volatile uint8_t PROCESS_FLAGS;
u8 check;
u8 preOpcode=0;
uint8_t FREQUENCY;
uint8_t FREQUENCY_NOM;
uint8_t FREQUENCY_HIGH;
uint8_t FREQUENCY_CTR;
uint8_t FREQUENCY_OVERFLOW;
uint16_t PLL_M;
uint16_t PLL_N;
uint16_t PLL_P;
u32 PLL_Q;
extern const tChar *FontSet ;
uint16_t SCREEN_MODE;
uint16_t tickCount;
uint16_t lastTickCount;

volatile u8 Decode_flat = 0;
// for TI/ST communication
// 0 = no op, busy flag low, waiting for data, or waiting for TI not busy
// 1 = receieved strobe interrupt, busy flag high, gathering data
// 2 = done gathering, processing data, busy flag high
//
// 11 = sent strobe, busy flag high, sending data
// 12 = done sending data
volatile uint8_t ST_TI_STATE=0;
volatile uint8_t ST_TI_FLAGS;

uint8_t in_buf[MAX_BUFFER_SIZE];
uint8_t out_buf[MAX_BUFFER_SIZE];

//extern const tChar myriad_bold_12[];
extern uint16_t TextColor;
extern uint16_t BackColor;
void lcd_start_procedure(void);
extern const uint16_t BMP_W1A_X36Y83[108][165];
u8 display_debug = 1;
u8 PreOP = 0;
uint8_t buf_debug[11];


#define FLASH_TEST
#ifdef FLASH_TEST
extern void flashTest(void);
#endif
void textDisplayInit(void);
extern char dBuf[];
extern U8 csFail;
//extern void sendACK_FWVer(U8 fwVer);
extern void fwUpdateInit(void);
extern U32 stFwStartAddr;
extern u8 Fw_version;
extern volatile u8 button;


/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: doSetPLL
/****************************************************************/
void doSetPLL(void)
{
#ifdef USE_FREQ_SWITCH
    // setup for running at 2 frequencies
    PLL_Q = 5;
    FREQUENCY_NOM = 4;
    FREQUENCY = FREQUENCY_NOM;
    FREQUENCY_HIGH = 120;
    setPLL();
#else
    PLL_Q = 5;
    FREQUENCY_NOM = 120;
    FREQUENCY = FREQUENCY_NOM;
    FREQUENCY_HIGH = 120;
    setPLL();
#endif
}

/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: set PLL
/****************************************************************/
void setPLL(void)
{
    // HSE_VALUE is constant in h file, 25 Mhz, needs to match xtal
    // HSI_VALUE is constant in h file, 16 Mhz, internal
    /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N */
    /* SYSCLK = PLL_VCO / PLL_P */
    /* USB OTG FS, SDIO and RNG Clock =  PLL_VCO / PLLQ */
    switch(FREQUENCY)
    {
    case 4: // 4.23Mhz
        RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
        PLL_M = 63; /* 2-63 */
        PLL_N = 64; /* 64-432 */
        PLL_P = 6; /* 2,4,6,8 */
        break;
    case 120:
        RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
        PLL_M = 25;
        PLL_N = 240;
        PLL_P = 2;
        break;
    default:
        RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
        PLL_M = 25;
        PLL_N = 240;
        PLL_P = 2;
        break;
    }

    SystemInit();
}


/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: initialize variables for program
// INPUTs: n/a
// OUTPUTs: n/a
// HW DEPEDANCIES: 25MHz xtal on board, ST STM32F207ZG
// SW DEPENDENCIEs: n/a
/****************************************************************/
void initVars(void)
{
    SCREEN_MODE = 0x00;
    tickCount = 0;
    lastTickCount = 0;
}

/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: main function
// INPUTs: n/a
// OUTPUTs: n/a
// HW DEPEDANCIES: 25MHz xtal on board, ST STM32F207ZG
// SW DEPENDENCIEs: n/a
/****************************************************************/
int main( void )
{
    //int i;
    initVars();
    /* Check that the system was resumed from StandBy mode */
    if(PWR_GetFlagStatus(PWR_FLAG_SB) != RESET)
    {
        /* Clear SB Flag */
        PWR_ClearFlag(PWR_FLAG_SB);
    }
    /* Set the Vector Table base address at 0x08000000 */
    NVIC_SetVectorTable( NVIC_VectTab_FLASH, 0x0 );
    NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
    prvSetupHardware();

    CLEAR_PROCESS_FLAGS;

    // NOT SURE WHY PB4 WORKS HERE >>> MUST BE WRONG HARDWARE CONNECTIONS!!
    BKL_OFF;                                                                                                         // PB0 / BKL_CTRL

    SysTick_Config(SystemCoreClock / 1000);
    flashMemCfg();
    fwUpdateInit();
    lcd_start_procedure();
    //LCD_DrawBMP(220, 40, (ptImage)&HistoryIconLarge, 0);

#ifdef USE_FREQ_SWITCH
    FREQUENCY = FREQUENCY_HIGH;
    setPLL();
#endif


    // delayUntilMS(500);
    LCD_Clear(Black);
    FontSet = (ptChar)(&myriad_bold_57);
    LCD_SetColors(Grey, Black);
    LCD_DisplayStringLine_Center(20, 300, 0, "25");
    LCD_SetColors(Blue, Black);
    LCD_DisplayStringLine_Center(20, 300, 120, "355");
    //LCD_DrawBMP(0, 0, (ptImage)myriad_bold_57[5].image, 0);
    // LCD_DisplayStringLine_Center(20, 300, 120, "    BEN PHAI");
    //LCD_DisplayStringLine_Center(20, 300, 240, "    BEN PHAI");
    // LCD_DisplayStringLine_Center(20, 300, 0, "    BEN PHAI");



    //LCD_DisplayStringLine_As_Left(50,320,50, "    BEN TRAI ");
    // LCD_DisplayStringLine(160,50, "O GIUA");


    //Percent_bar_left(ASSEMBLE_RGB(230,64,30),TL_per);

    //Percent_bar_left(ASSEMBLE_RGB(235,122,31),TL_per);
    //LCD_SetBackColor(ASSEMBLE_RGB(230,64,30));
    //LCD_DrawFullRect(0, 0, LCD_PIXEL_WIDTH, 160);

//        LCD_SetBackColor(LCD_COLOR_OGANGE);
//        LCD_DrawFullRect(0, 160, LCD_PIXEL_WIDTH, 160);
//Draw_C1A();
    // Draw_H1();
    //Test_Fonts();
//#ifdef TEST
    //  Draw_H1();
//redrawScreenSection(218, 0,250, 20, (uint16_t const *)&BMP_Menu_Top, 21,320,0,0);
    //Text_SO18();
    //Select_SonarNavMode(0x00);
//Draw_SO10();
//Text_SO10();
//Draw_SonarMain();





#if 0
    Draw_SO10();
    Text_SO10();
    //Select_SetNavMode(0x03);
    //UnSelect_SetNavMode(0x00);
    //Select_SetNavMode(0x01);
    // UnSelect_SetNavMode(0x01);
    //Select_SetNavMode(0x02);
    // UnSelect_SetNavMode(0x02);
    // Select_SetNavMode(0x03);
    //UnSelect_SetNavMode(0x03);

    while(1);

#endif



#if 1
    __enable_interrupt();
    // Init Sonar System Control
    sysInit();
#endif

    while(1)
    {

        if(TST_ST_DTA_RX_FLAG)
        {
            if(in_buf[2] == 0x00 && in_buf[3] == 0x00)
            {
                // process screen data
                //ST_ready_get_data = 0;
                if(ST_ready_get_data ==1)
                {
                    //if (sonarCmdHandler(in_buf) != DISPLAY_SHOWN)
                    //{
                    sendACK(R_ACK);
                    //decode();
                    if(in_buf[4]!=preOpcode) {
                        preOpcode=in_buf[4];
                        check++;
                    }
                    switch(check) {
                    case 0:
                        break;
                    default:
                        break;
                    }
                    //}
                }
                //ST_ready_get_data =1;

                CLR_ST_DTA_RX_FLAG; // clear flag

            }
            else
            {
                //LCD_FillScreen(White);
                //FontSet = &(myriad_bold_22);
                //LCD_SetTextColor(BLACK);
                //LCD_DisplayStringLine_Center(68, 180, 107, "WRONG CODE");
            }

            if (csFail)
            {
                csFail = 0;
                delayWait(6);
                sendACK(R_NACK);
                sprintf(dBuf, "CSF Failed!");
                dS(dBuf);
            }

            if(TST_PROCESS_BTNLOG)
            {
                task_btnLog();
                CLR_PROCESS_BTNLOG;
            }
            if(TST_PROCESS_500MS_UPDT)
            {
                task_update_lcd();
                delayUntilMS(500);
            }
            else if(TST_PROCESS_LCD)
            {
                task_update_lcd();
                CLR_PROCESS_LCD;
            }

            if(!TST_PROCESS_500MS_UPDT)
            {
                // __WFI();
                lastTickCount = tickCount;
            }
        }
    }
    //return 0;
}

/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: helper function
/****************************************************************/
void prvSetupHardwareHelper(void)
{
    SystemInit();
    doSetPLL();
    /* Configure HCLK clock as SysTick clock source. */
    SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK );
    SystemCoreClockUpdate();
}

/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: setup hardware function called from main
/****************************************************************/
static void prvSetupHardware( void )
{

    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStruct;
    RCC_ClocksTypeDef RCC_ClockFreq;

    prvSetupHardwareHelper();

    /* This function fills the RCC_ClockFreq structure with the current
    frequencies of different on chip clocks (for debug purpose) **************/

    RCC_GetClocksFreq(&RCC_ClockFreq);

#if 0 // David.
    //__disable_interrupt();
    __enable_interrupt();
//#else
    // MikroC-specific
    EnableInterrupts();                 // Enables the processor interrupt.
#endif

#ifdef ADD_MORE
    // MikroC-specific
    NVIC_IntEnable(IVT_INT_SysTick);
#endif

    initGPIO(&GPIO_InitStructure);
    initButtons(&GPIO_InitStructure, &EXTI_InitStructure, &NVIC_InitStruct);
    Timer2_Init();

}
/*-----------------------------------------------------------*/

/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: Inserts a delay time.
// nTime: specifies the delay time length, in milliseconds.
/****************************************************************/
void delayMS(__IO uint32_t nTime)
{
    TimingDelay = (tickCount + nTime)%1000;
    while(tickCount < TimingDelay);
}


/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: Inserts a delay time starting from the last saved time.
// nTime: specifies the delay time length, in milliseconds.
/****************************************************************/
void delayUntilMS(__IO uint32_t nTime)
{
    TimingDelay = (lastTickCount + nTime)%1000;
    while(TimingDelay != tickCount);
}

/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: This function handles SysTick Handler.
/****************************************************************/
void SysTick_Handler() //iv IVT_INT_SysTick ics ICS_OFF
{
    tickCount += 1;
    if(tickCount == 1000)
    {
        tickCount = 0;
    }
}

