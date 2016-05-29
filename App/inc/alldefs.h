/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: defines and includes
/****************************************************************/

#ifndef __ALLDEFS_h
#define __ALLDEFS_h

// ------------------------------------------------------------------------
// high level defines
// ------------------------------------------------------------------------
// development boards
// type 1 is the large development board
// type 2 is the smaller 1st production board
// type 3 will be the final prod board
#define BOARD_TYPE_1
//#define BOARD_TYPE_2
//#define BOARD_TYPE_3
#define ANTIALIASING // Antialiasing font text
//#define REMOVE_BITMAPS
//#define RUN_LCD_TESTS
//#define TEST_READWRITE
//#define TEST_ONLY_MCOOUT
//#define SEE_LED
//#define TIMING_PIN
//#define TEST
#define  second 6000
// ------------------------------------------------------------------------
// TI<-->ST communication
// ------------------------------------------------------------------------
#define TI_ST_CONNECTION
#ifdef TI_ST_CONNECTION
#define TI_ST_WAIT_TIME 1
#define ST_LOOPBACK_FLAG BIT1
#define ST_DTA_RX_FLAG BIT2
#define TST_ST_DTA_RX_FLAG ((ST_TI_FLAGS & ST_DTA_RX_FLAG) == ST_DTA_RX_FLAG)
#define SET_ST_DTA_RX_FLAG (ST_TI_FLAGS |= ST_DTA_RX_FLAG)
#define CLR_ST_DTA_RX_FLAG (ST_TI_FLAGS &= ~ST_DTA_RX_FLAG)
#define TEST_TI_ST_BUSY (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_11) == Bit_SET)
#define ST_TI_STROBE_H GPIO_SetBits(GPIOF, GPIO_Pin_8)
#define ST_TI_STROBE_L GPIO_ResetBits(GPIOF, GPIO_Pin_8)
#define ST_TI_BUSY_H GPIO_SetBits(GPIOF, GPIO_Pin_9)
#define ST_TI_BUSY_L GPIO_ResetBits(GPIOF, GPIO_Pin_9)
// uncomment to send back to TI when recieve
//#define TEST_LOOPBACK
//#define TEST_MIRROR
#endif

// if you use internal PWM for testing, then you cannot use STOP mode, use sleep in main loop
// real application should use external PWM
#ifdef BOARD_TYPE_1
#define USE_INTERNAL_PWM
#endif

// http://www.freertos.org/FreeRTOS_Support_Forum_Archive/July_2010/freertos_Dynamic_clock_frequency_3778272.html
// check running frequency, if at higher rate that nominal, need to adjust things
//#define USE_FREQ_SWITCH
#define PER_SECOND 32
#define OCX_DISPLAY
//#define SEPIA_DISPLAY
// ------------------------------------------------------------------------
// INCLUDES
// ------------------------------------------------------------------------

/* Standard includes. */
#include <stdio.h>
#include <stdint.h>
#include <cstring>  //For the string functions
#include <stdlib.h>
#include <string.h>

/* library includes. */
#include "stm32f2xx_conf.h"
#include "stm32f2xx_gpio.h"
#include "stm32f2xx_tim.h"
#include "stm32f2xx_it.h"
#include "stm32f2xx_rcc.h"
#include "stm32f2xx_rtc.h"
#include "stm32f2xx_pwr.h"
#include "stm32f2xx_fsmc.h"
#include "misc.h"
#include "fonts.h"
#include "stm32f2xx_spi.h"
#include "stm32f2xx_iwdg.h"

/* LCD includes */
#include "stm322xg_eval_lcd.h"
#include "gpio.h"
#include "stm32f2xx_pwr.h"
#include "backgrounds.h"
#include "handleButtons.h"
#include "system_stm32f2xx.h"
#include "typedefs.h"
#include "textUtils.h"
#include "OCSepia.h"
#include "hpiMsg.h"
#include "sonarCtrl.h"
#include "errors.h"

// ------------------------------------------------------------------------
// general
// ------------------------------------------------------------------------
enum {sel_col, view_col,none};

#define BIT0 (0x0001 << 0)
#define BIT1 (0x0001 << 1)
#define BIT2 (0x0001 << 2)
#define BIT3 (0x0001 << 3)
#define BIT4 (0x0001 << 4)
#define BIT5 (0x0001 << 5)
#define BIT6 (0x0001 << 6)
#define BIT7 (0x0001 << 7)
#define BIT8 (0x0001 << 8)
#define BIT9 (0x0001 << 9)
#define BIT10 (0x0001 << 10)
#define BIT11 (0x0001 << 11)
#define BIT12 (0x0001 << 12)
#define BIT13 (0x0001 << 13)
#define BIT14 (0x0001 << 14)
#define BIT15 (0x0001 << 15)

#define DEBOUNCE delayMS(50)
//#define DEBOUNCE delayMSCtr(5000)

// ------------------------------------------------------------------------
// PROTOTYPES
// ------------------------------------------------------------------------
static void prvSetupHardware( void );
void delayMS(__IO uint32_t nTime);
void delayUntilMS(__IO uint32_t nTime);
void delayMSCtr(uint32_t t);
void task_btnLog(void);
//void LCD_SetFont(sFONT *fonts);
void task_update_lcd( void);
void TIM_Config(void);
void peripheralClocksOnOff(uint8_t ON);
void setPLL();
extern void SetSysClock();
void beginSTOPMode();
void endSTOPMode();
void prvSetupHardwareHelper();
void writeBMP(uint16_t const *bmpPtr);
extern void btnHelper();

// ------------------------------------------------------------------------
// VARIABLES
// ------------------------------------------------------------------------

extern volatile uint8_t PROCESS_FLAGS;
extern volatile uint8_t ST_TI_FLAGS;
static __IO uint32_t TimingDelay;

extern volatile uint8_t ST_TI_STATE;

#define  MAX_BUFFER_SIZE		300
extern uint8_t in_buf[];
extern uint8_t out_buf[];

extern uint8_t FREQUENCY;
extern uint8_t FREQUENCY;
extern uint8_t FREQUENCY_NOM;
extern uint8_t FREQUENCY_HIGH;

#define numBytesExpected (in_buf[0]+in_buf[1]*256)

#define CLEAR_PROCESS_FLAGS (PROCESS_FLAGS = 0x00)
// --
#define SET_PROCESS_BTNLOG (PROCESS_FLAGS |= BIT0)
#define CLR_PROCESS_BTNLOG (PROCESS_FLAGS &= ~BIT0)
#define TST_PROCESS_BTNLOG ((PROCESS_FLAGS & BIT0) == BIT0)
#define SET_PROCESS_BTNLOG_IN_PROG (PROCESS_FLAGS |= BIT3)
#define CLR_PROCESS_BTNLOG_IN_PROG (PROCESS_FLAGS &= ~BIT3)
#define TST_PROCESS_BTNLOG_IN_PROG ((PROCESS_FLAGS & BIT3) == BIT3)
// --
#define SET_PROCESS_LCD (PROCESS_FLAGS |= BIT1)
#define CLR_PROCESS_LCD (PROCESS_FLAGS &= ~BIT1)
#define TST_PROCESS_LCD ((PROCESS_FLAGS & BIT1) == BIT1)
// --
#define SET_PROCESS_500MS_UPDT (PROCESS_FLAGS |= BIT2)
#define CLR_PROCESS_500MS_UPDT (PROCESS_FLAGS &= ~BIT2)
#define TST_PROCESS_500MS_UPDT ((PROCESS_FLAGS & BIT2) == BIT2)



// ------------------------------------------------------------------------
// LCD general
// ------------------------------------------------------------------------
#define USE_LCD

// 5-6-5 bits for r-g-b
#define RED_MASK 0xf800
#define GREEN_MASK 0x07E0
#define BLUE_MASK 0x001F
#define RGB_ASSEMBLE(r,g,b) ((r << 11)&RED_MASK)|((g << 5)&GREEN_MASK)|(b&BLUE_MASK)

#define MAX_ROWS 320  //Horizontal
#define MAX_COLS 240


#define MAX_RED 0x001F // 5 bits
#define MAX_GREEN 0x003F // 6 bits
#define MAX_BLUE 0x001F // 5 bits

#define LCD_CHAR_SPACE 0

/// HX8347 ID code
#define HX8347_HIMAXID_CODE    0x47

/// HX8347 LCD Registers
#define HX8347_R00H        0x00
#define HX8347_R01H        0x01
#define HX8347_R02H        0x02
#define HX8347_R03H        0x03
#define HX8347_R04H        0x04
#define HX8347_R05H        0x05
#define HX8347_R06H        0x06
#define HX8347_R07H        0x07
#define HX8347_R08H        0x08
#define HX8347_R09H        0x09
#define HX8347_R0AH        0x0A
#define HX8347_R0CH        0x0C
#define HX8347_R0DH        0x0D
#define HX8347_R0EH        0x0E
#define HX8347_R0FH        0x0F
#define HX8347_R10H        0x10
#define HX8347_R11H        0x11
#define HX8347_R12H        0x12
#define HX8347_R13H        0x13
#define HX8347_R14H        0x14
#define HX8347_R15H        0x15
#define HX8347_R16H        0x16
#define HX8347_R18H        0x18
#define HX8347_R19H        0x19
#define HX8347_R1AH        0x1A
#define HX8347_R1BH        0x1B
#define HX8347_R1CH        0x1C
#define HX8347_R1DH        0x1D
#define HX8347_R1EH        0x1E
#define HX8347_R1FH        0x1F
#define HX8347_R20H        0x20
#define HX8347_R21H        0x21
#define HX8347_R22H        0x22
#define HX8347_R23H        0x23
#define HX8347_R24H        0x24
#define HX8347_R25H        0x25
#define HX8347_R26H        0x26
#define HX8347_R27H        0x27
#define HX8347_R28H        0x28
#define HX8347_R29H        0x29
#define HX8347_R2AH        0x2A
#define HX8347_R2BH        0x2B
#define HX8347_R2CH        0x2C
#define HX8347_R2DH        0x2D
#define HX8347_R35H        0x35
#define HX8347_R36H        0x36
#define HX8347_R37H        0x37
#define HX8347_R38H        0x38
#define HX8347_R39H        0x39
#define HX8347_R3AH        0x3A
#define HX8347_R3BH        0x3B
#define HX8347_R3CH        0x3C
#define HX8347_R3DH        0x3D
#define HX8347_R3EH        0x3E
#define HX8347_R40H        0x40
#define HX8347_R41H        0x41
#define HX8347_R42H        0x42
#define HX8347_R43H        0x43
#define HX8347_R44H        0x44
#define HX8347_R45H        0x45
#define HX8347_R46H        0x46
#define HX8347_R47H        0x47
#define HX8347_R48H        0x48
#define HX8347_R49H        0x49
#define HX8347_R4AH        0x4A
#define HX8347_R4BH        0x4B
#define HX8347_R4CH        0x4C
#define HX8347_R4DH        0x4D
#define HX8347_R4EH        0x4E
#define HX8347_R4FH        0x4F
#define HX8347_R50H        0x50
#define HX8347_R51H        0x51
#define HX8347_R64H        0x64
#define HX8347_R65H        0x65
#define HX8347_R66H        0x66
#define HX8347_R67H        0x67
#define HX8347_R70H        0x70
#define HX8347_R72H        0x72
#define HX8347_R90H        0x90
#define HX8347_R91H        0x91
#define HX8347_R93H        0x93
#define HX8347_R94H        0x94
#define HX8347_R95H        0x95

// ------------------------------------------------------------------------
// LCD GPIO lines
// ------------------------------------------------------------------------

#define LCD_BS0_H GPIO_SetBits(GPIOF, GPIO_Pin_12);
#define LCD_BS0_L GPIO_ResetBits(GPIOF, GPIO_Pin_12);

#define LCD_BS1_H GPIO_SetBits(GPIOF, GPIO_Pin_13);
#define LCD_BS1_L GPIO_ResetBits(GPIOF, GPIO_Pin_13);

#define LCD_RST_H GPIO_SetBits(GPIOE, GPIO_Pin_2);
#define LCD_RST_L GPIO_ResetBits(GPIOE, GPIO_Pin_2);
#define LCD_RST_SEQUENCE LCD_RST_H; LCD_RST_L; LCD_RST_L; LCD_RST_H;

// ------------------------------------------------------------------------
// backlight
// ------------------------------------------------------------------------
// E.Pataky - BKL_CTRL in schematic is pin PB0, = TIM3 CH3
#ifdef USE_INTERNAL_PWM
#define BKL_ON TIM_Config(); SetTIM3Duty(BKL_CCR_Val_3);
#define BKL_OFF TIM_Cmd(TIM3, DISABLE); setIOasOUTPUT( GPIOB, GPIO_Pin_0); GPIO_ResetBits(GPIOB, GPIO_Pin_0);
// Set duty cycle when using TIM3 as a PWM output.
#define SetTIM3Duty( val )    TIM3->CCR3 = val;
#else
#define BKL_ON setIOasOUTPUT( GPIOB, GPIO_Pin_0); GPIO_ResetBits(GPIOB, GPIO_Pin_0);
#define BKL_OFF setIOasOUTPUT( GPIOB, GPIO_Pin_0); GPIO_ResetBits(GPIOB, GPIO_Pin_0);
// Set duty cycle when using TIM3 as a PWM output.
#define SetTIM3Duty( val ) setIOasOUTPUT( GPIOB, GPIO_Pin_0); GPIO_ResetBits(GPIOB, GPIO_Pin_0);
#endif

// ------------------------------------------------------------------------
// LCD register stuff
// ------------------------------------------------------------------------

#define LCD_SET_REG_BIT(reg, bit) LCD_WriteReg(reg, LCD_ReadReg(reg) | bit);
#define LCD_CLR_REG_BIT(reg, bit) LCD_WriteReg(reg, LCD_ReadReg(reg) & ~bit);

// display mode reg 0x01
#define LCD_INVERT_ON                         LCD_SET_REG_BIT(HX8347_R01H, BIT2);
#define LCD_INVERT_OFF                         LCD_CLR_REG_BIT(HX8347_R01H, BIT2);
#define LCD_NRML_ON                         LCD_SET_REG_BIT(HX8347_R01H, BIT1);
#define LCD_NRML_OFF                         LCD_CLR_REG_BIT(HX8347_R01H, BIT1);
#define LCD_PARTIAL_ON                         LCD_SET_REG_BIT(HX8347_R01H, BIT0);
#define LCD_PARTIAL_OFF                        LCD_CLR_REG_BIT(HX8347_R01H, BIT0);

// RAM access
#define LCD_RAM_MIRROR_X_ON         LCD_SET_REG_BIT(HX8347_R16H, BIT6);
#define LCD_RAM_MIRROR_X_OFF         LCD_CLR_REG_BIT(HX8347_R16H, BIT6);
#define LCD_RAM_MIRROR_Y_ON         LCD_SET_REG_BIT(HX8347_R16H, BIT7);
#define LCD_RAM_MIRROR_Y_OFF         LCD_CLR_REG_BIT(HX8347_R16H, BIT7);
#define LCD_RAM_XCHG_XY_ON                 LCD_SET_REG_BIT(HX8347_R16H, BIT5);
#define LCD_RAM_XCHG_XY_OFF         LCD_CLR_REG_BIT(HX8347_R16H, BIT5);

// standby mode
#define LCD_STANDBY_MODE_ON         LCD_SET_REG_BIT(HX8347_R1BH, BIT0);
#define LCD_STANDBY_MODE_OFF         LCD_CLR_REG_BIT(HX8347_R1BH, BIT0);

#define LCD_DISPLAY_OFF { LCD_WriteReg(HX8347_R26H, 0x00); /* GON=0, DTE=0, D=00 */ LCD_WriteReg(HX8347_R90H, 0x00); /* SAP=0000 0000 */ }
#define LCD_DISPLAY_ON LCD_DisplayOn();
//Status
#define No 0
#define Yes 1

// ------------------------------------------------------------------------
// LCD states used with task_update_lcd
// ------------------------------------------------------------------------

#define NOLCD 1
#define LCDSTART 3
#define TEST_BKL1 4
#define TEST_BKL2 (TEST_BKL1+1)
#define TEST_BKL3 (TEST_BKL2+1)
#define TEST_BKL4 (TEST_BKL3+1)
#define TEST_FONTS (TEST_BKL4+1)
#define TEST_RED (TEST_FONTS+2)
#define TEST_GREEN (TEST_RED+11)
#define TEST_BLUE (TEST_GREEN+11)
#define TEST_BLACK (TEST_BLUE+11)
#define TEST_WHITE (TEST_BLACK+1)
#define TEST_GRADIENT (TEST_WHITE+1)
#define TEST_BITMAP (TEST_GRADIENT+2)
#define TEST_BITMAP2 (TEST_BITMAP+1)
#define TEST_BITMAP3 (TEST_BITMAP2+1)
#define TEST_POWER (TEST_BITMAP3+1)
#define TEST_TYPICAL (TEST_POWER+2)
#define TEST_BKL1_2 (TEST_TYPICAL+3)
#define TEST_BKL2_2 (TEST_BKL1_2+1)
#define TEST_BKL3_2 (TEST_BKL2_2+1)
#define TEST_BKL4_2 (TEST_BKL3_2+1)
#define PROCESS_MODE (TEST_BKL4_2+2)
#define BIT_0 (0x01 << 0)
#define BIT_1 (0x01 << 1)
#define BIT_2 (0x01 << 2)
#define BIT_3 (0x01 << 3)
#define BIT_4 (0x01 << 4)
#define BIT_5 (0x01 << 5)
#define BIT_6 (0x01 << 6)
#define BIT_7 (0x01 << 7)

// ------------------------------------------------------------------------
// custom fonts
// ------------------------------------------------------------------------
//        typedef struct {
//                const uint16_t *data;
//                uint16_t width;
//                uint16_t height;
//        } tImage;

//typedef struct
//{
//   const uint16_t *bmpPtr;
//   uint16_t width;
//    uint16_t height;
//    uint16_t X_offet;
//    uint16_t Y_offet;

//} tImage_Slice;

extern void stopwatch_delay(uint32_t ticks);

#define __WFI() asm {\
            WFI\
    }

#define __WFE() asm {\
        WFE\
    }
#endif
