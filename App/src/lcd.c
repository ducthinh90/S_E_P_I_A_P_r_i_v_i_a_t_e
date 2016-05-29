/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: handle lcd operations for Blanview HX8347
/****************************************************************/

#include "alldefs.h" // all defines
#include "stm322xg_eval_lcd.h"
#include "./static_images.c"
#include "backgrounds.h"



uint8_t LCD_STATE;
extern uint16_t SCREEN_MODE;
extern void setupPWMTimer(unsigned char duty);
extern void setPLL(void);
extern uint8_t FREQUENCY;
extern volatile uint8_t PROCESS_FLAGS;
extern uint8_t FREQUENCY_HIGH;
extern uint8_t FREQUENCY_NOM;
extern uint16_t BKL_CCR_Val_1, BKL_CCR_Val_2 , BKL_CCR_Val_3, BKL_CCR_Val_4 ;
extern  uint16_t TextColor  ;
extern  uint16_t  BackColor;
const tChar *FontSet ;

// LCD variables to use globally in LCD functions
uint16_t row = 0;
uint16_t col = 0;
static uint16_t red = 0;
#define ROW_COL_ZERO { row = 0; col = 0; }
static uint16_t green = 0;
static uint16_t blue = 0;
static __IO uint16_t tmpColor;
#define RGB_ZERO { red=0; green=0; blue=0; }


/*extern  bitmap slice here....*/

// max number of characters to be displayed depends on font, but
// max is 240/(8+1) if w=8 font with space of 1
uint8_t *sBuf;
//static uint8_t BCD4, BCD3, BCD2, BCD1;
volatile u8 screenCod = BLACK;

extern void Delay_ms(uint32_t time_ms);


void setupPWMTimer(unsigned char duty);

/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: setup PWM timer on port PB0 timer 3 channel 3
// INPUTs: duty is value out of 100
// OUTPUTs: n/a
/****************************************************************/
void setupPWMTimer(unsigned char duty)
{
#if 0 // David
    // simple just turn on 100% with IO
#define backlightFrequency 1000
    unsigned int ratio = PWM_TIM3_Init(backlightFrequency);

// GPIO_Config(&GPIOB_BASE, _GPIO_PINMASK_0, _GPIO_CFG_MODE_ALT_FUNCTION);
    PWM_TIM3_Set_Duty((int)((float)ratio*(float)duty/100.0f),_PWM_NON_INVERTED, _PWM_CHANNEL3);
    PWM_TIM3_Start(_PWM_CHANNEL3, &_GPIO_MODULE_TIM3_CH3_PB0);
#endif
}


/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: process SCREEN_MODE
/****************************************************************/
void processMode(void)
{
#if 0
    switch(SCREEN_MODE)
    {
    case 0x0010:
        LCD_SetBackColor(Black);
        LCD_SetTextColor(White);
        LCD_DrawFullRect(0, 0, 240, 320);



        break;
    case 0x0020:



        break;
    case 0x0030:



        break;


    default:


        SCREEN_MODE = 0x00;
        break;
    }
#endif


}

/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: write image
/****************************************************************/
void writeBMP(uint16_t const *bmpPtr)
{

    uint32_t tmpCtr1 = 0;
    //uint32_t tmpword;

    *LCD_REG = HX8347_R06H;
    *LCD_RAM =0;

    // assumes 240 cols, 320 rows, each element in array is 16-bit rgb color
    for(row = 0; row < 320; row += 1)
    {
        tmpCtr1 =(u32)(row)*(MAX_COLS);
        for(col = 0; col < 240; col += 1)
        {
            LCD_SetCursor((int16_t)col, (int16_t)row); //0.18s
            LCD_WriteRAM_Prepare(); /* Prepare to write GRAM *///20ms
            LCD_WriteRAM(*(bmpPtr + tmpCtr1 + col));//34ms
            /*
                        *LCD_REG = HX8347_R03H;
                        *LCD_RAM = col & 0xff;

                        if(row>0xff) {
                            *LCD_REG = HX8347_R06H;
                            *LCD_RAM = (row & 0xff00) >>8;
                        }
                        *LCD_REG = HX8347_R07H;
                        *LCD_RAM = row & 0xff;

                        *LCD_REG = HX8347_R22H;
                        *LCD_RAM = *(bmpPtr + tmpCtr1 + col);
            */
        }
    }

}


/****************************************************************/
// Author: Phu Thinh
// Date: 4/3/14
// Desc: write image n times
/****************************************************************/

void writeBMP_nTimes(uint16_t     const *bmpPtr, int16_t height,  int16_t width, uint16_t X_offset, uint16_t Y_offset, int16_t nTimes ) {
    int8_t i = 0;
    uint32_t tmpCtr1;

    for(i = 0; i<nTimes; i++)
    {
        //*LCD_REG = HX8347_R06H;
        //*LCD_RAM =0;
        for(row = 0; row < height; row ++)
        {
            tmpCtr1 =(u32)(row)*(width);
            for(col = 0; col < width; col ++)
            {
                //if(col +X_offset>= 0xff) {
                *LCD_REG = HX8347_R02H;
                *LCD_RAM = ((col + i*width + X_offset) & 0xff00) >> 8;
                //}
                *LCD_REG = HX8347_R03H;
                *LCD_RAM = (col + i*width + X_offset) & 0xff;
                if(row +Y_offset>= 0xff) {
                    *LCD_REG = HX8347_R06H;
                    *LCD_RAM = ((row +Y_offset) & 0xff00) >>8;
                }
                *LCD_REG = HX8347_R07H;
                *LCD_RAM = (row +Y_offset) & 0xff;

                *LCD_REG = HX8347_R22H;
                *LCD_RAM = *(bmpPtr + tmpCtr1 + col);
            }
        }
    }
}



void writeBMP_nTimes1(uint16_t const *bmpPtr,int16_t height,  int16_t width, uint16_t X_offset, uint16_t Y_offset, int16_t nTimes )/*OK*/
{
    int8_t i = 0;
    uint32_t tmpCtr1;
    //145,187  height = 320

    for(i = 0; i<nTimes; i++)
    {
        *LCD_REG = HX8347_R06H;
        *LCD_RAM =0;
        for(col = 240; col > 240 - height; col --)
        {
            tmpCtr1 =(u32)(240 -col)*(width);
            for(row = 0; row < width; row ++)
            {

                //*LCD_REG = HX8347_R03H;
                //*LCD_RAM = (col + i*width + X_offset) & 0xff;

                //if(row +Y_offset>= 0xff) {
                //    *LCD_REG = HX8347_R06H;
                //   *LCD_RAM = ((row +Y_offset) & 0xff00) >>8;
                // }

                // *LCD_REG = HX8347_R07H;
                // *LCD_RAM = (row +Y_offset) & 0xff;

                *LCD_REG = HX8347_R03H;
                *LCD_RAM = (col - Y_offset) & 0xff;

                *LCD_REG = HX8347_R06H;
                *LCD_RAM = ((row+ i*width  +X_offset)  & 0xff00) >>8;

                *LCD_REG = HX8347_R07H;
                *LCD_RAM = (row + i*width +X_offset)  & 0xff;

                *LCD_REG = HX8347_R22H;
                *LCD_RAM = *(bmpPtr + tmpCtr1 + row);

                //LCD_SetCursor((int16_t)col, (int16_t)row); //0.18s
                //LCD_WriteRAM_Prepare(); /* Prepare to write GRAM *///20ms
                //LCD_WriteRAM(*(bmpPtr + tmpCtr1 + row));//34ms
            }
        }
    }

}




/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: convert 8-bit int to BCD4:3:2:1
/****************************************************************/
void intToBCD4321(uint8_t in)
{
#if 0
    BCD4 = (in/1000);
    in = in - (in/1000)*1000;
    BCD3 = (in/100);
    in = in - (in/100)*100;
    BCD2 = (in/10);
    in = in - (in/10)*10;
    BCD1 = in;
#endif
}

/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: initialize LCD
/****************************************************************/
void lcd_start_procedure(void)
{
    // --------------------------------------------------
    // de-initialize the display
    // turns it off, put GPIO back to normal (stops FSMC)
    // turns off backlight
    // --------------------------------------------------
    LCD_DISPLAY_OFF;
    LCD_DeInit();
    BKL_OFF;

    // --------------------------------------------------
    // initialize display, clear it, set default colors,
    // backlight on, clear row, col, and rgb values
    // --------------------------------------------------
    STM322xG_LCD_Init();
    LCD_Clear(Black);
    LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
    BKL_ON;
    setupPWMTimer(50);
    //BKL_ON; SetTIM3Duty(100);

    // message
    LCD_Clear(White);
    LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
    //LCD_SetFont(&Font8x12); sBuf = "SCREEN INITIALIZED";

    // LCD_DisplayStringLine(LCD_LINE_1, (uint8_t *)sBuf);

    ROW_COL_ZERO;
    RGB_ZERO;


}

/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: update LCD when xBinarySemaphore_LCD is given
/****************************************************************/
void task_update_lcd(void)
{
#ifdef TIMING_PIN
    GPIO_SetBits(GPIOA, GPIO_Pin_7);
#endif

#ifdef USE_FREQ_SWITCH
    FREQUENCY = FREQUENCY_HIGH;
    setPLL();
#endif

    switch(LCD_STATE)
    {
    case NOLCD:
        // --------------------------------------------------
        // de-initialize the display
        // turns it off, put GPIO back to normal (stops FSMC)
        // turns off backlight
        // --------------------------------------------------
        LCD_DISPLAY_OFF;
        LCD_DeInit();
        BKL_OFF;
        LCD_STATE++;
        break;
    case LCDSTART:
        // initialize the display
        lcd_start_procedure();
        break;
    case TEST_BKL1:
        // message
        LCD_Clear(LCD_COLOR_BLACK);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        // LCD_SetFont(&Font16x24); sBuf = "BKLT 5%";
        // LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);
        //BKL_ON; SetTIM3Duty(BKL_CCR_Val_1);
        BKL_ON;
        setupPWMTimer(5);

        break;
    case TEST_BKL2:
        // message
        LCD_Clear(LCD_COLOR_BLACK);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        //sLCD_SetFont(&Font16x24); sBuf = "BKLT 10%";
        //   LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);
        //BKL_ON; SetTIM3Duty(BKL_CCR_Val_2);
        BKL_ON;
        setupPWMTimer(10);
        break;
    case TEST_BKL3:
        // message
        LCD_Clear(LCD_COLOR_BLACK);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        //LCD_SetFont(&Font16x24); sBuf = "BKLT 15%";
        //  LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);
        //BKL_ON; SetTIM3Duty(BKL_CCR_Val_3);
        BKL_ON;
        setupPWMTimer(15);
        break;
    case TEST_BKL4:
        // message
        LCD_Clear(LCD_COLOR_BLACK);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        //  LCD_SetFont(&Font16x24); sBuf = "BKLT 50%";
        //  LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);
        //BKL_ON; SetTIM3Duty(BKL_CCR_Val_4);
        BKL_ON;
        setupPWMTimer(50);
        break;
    case TEST_FONTS:
        // --------------------------------------------------
        // try different fonts, sizes, numbers, letters, symbols
        // --------------------------------------------------

        // message
        //BKL_ON; SetTIM3Duty(BKL_CCR_Val_1);
        BKL_ON;
        setupPWMTimer(15);
        LCD_Clear(LCD_COLOR_BLACK);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        //  LCD_SetFont(&Font16x24); sBuf = "TESTING FONTS";
        // LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);
        break;

    case TEST_FONTS+1:

        LCD_Clear(LCD_COLOR_BLACK);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);

        //LCD_SetFont(&Font8x8);
        sBuf = "8x8 Pelagic";
        // LCD_DisplayStringLine(LCD_LINE_1, (uint8_t *)sBuf);

        //LCD_SetFont(&Font8x12);
        sBuf = "8x12 Pelagic";
        //  LCD_DisplayStringLine(LCD_LINE_3, (uint8_t *)sBuf);

        // LCD_SetFont(&Font12x12);
        sBuf = "12x12 Pelagic";
        //  LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);

        //LCD_SetFont(&Font16x24);
        sBuf = "16x24 Pelagic";
        //LCD_DisplayStringLine(LCD_LINE_7, (uint8_t *)sBuf);

        break;
    case TEST_RED:
        // --------------------------------------------------
        // flat color test
        // make R G B colors 5-6-5 (bits)
        // use 5 levels of color for each color, 2s between each
        // --------------------------------------------------

        // message
        LCD_Clear(LCD_COLOR_BLACK);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        //LCD_SetFont(&Font16x24); sBuf = "RED TEST";
        // LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);
        RGB_ZERO;
        break;
    case TEST_RED+1:
    case TEST_RED+2:
    case TEST_RED+3:
    case TEST_RED+4:
    case TEST_RED+5:
    case TEST_RED+6:
    case TEST_RED+7:
    case TEST_RED+8:
    case TEST_RED+9:
    case TEST_RED+10:

        if(red <= MAX_RED)
        {
            red = (LCD_STATE-TEST_RED)*MAX_RED/10;
            tmpColor = RGB_ASSEMBLE(red, green, blue);
            LCD_Clear(tmpColor);

            // step label
            intToBCD4321(LCD_STATE-TEST_RED);
            LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
            //LCD_SetFont(&Font16x24); LCD_DisplayChar(0, LCD_LINE_1, (char)(48+BCD2)); LCD_DisplayChar(17, LCD_LINE_1, (char)(48+BCD1));
        }
        else
        {
            red = MAX_RED;
            LCD_Clear(RGB_ASSEMBLE(red, green, blue));
            intToBCD4321(LCD_STATE-TEST_RED);
            LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
            //LCD_SetFont(&Font16x24); LCD_DisplayChar(0, LCD_LINE_1, (char)(48+BCD2)); LCD_DisplayChar(17, LCD_LINE_1, (char)(48+BCD1));
        }

        break;
    case TEST_GREEN:

        // message
        LCD_Clear(LCD_COLOR_BLACK);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        //LCD_SetFont(&Font16x24); sBuf = "GREEN TEST";
        // LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);
        RGB_ZERO;
        break;
    case TEST_GREEN+1:
    case TEST_GREEN+2:
    case TEST_GREEN+3:
    case TEST_GREEN+4:
    case TEST_GREEN+5:
    case TEST_GREEN+6:
    case TEST_GREEN+7:
    case TEST_GREEN+8:
    case TEST_GREEN+9:
    case TEST_GREEN+10:

        if(green <= MAX_GREEN)
        {
            green = (LCD_STATE-TEST_GREEN)*MAX_GREEN/10;
            LCD_Clear(RGB_ASSEMBLE(red, green, blue));

            intToBCD4321(LCD_STATE-TEST_GREEN);
            LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
            //  LCD_SetFont(&Font16x24); LCD_DisplayChar(0, LCD_LINE_1, (char)(48+BCD2)); LCD_DisplayChar(17, LCD_LINE_1, (char)(48+BCD1));
        }
        else
        {
            green = MAX_GREEN;
            LCD_Clear(RGB_ASSEMBLE(red, green, blue));
            intToBCD4321(LCD_STATE-TEST_GREEN);
            LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
            //LCD_SetFont(&Font16x24); LCD_DisplayChar(0, LCD_LINE_1, (char)(48+BCD2)); LCD_DisplayChar(17, LCD_LINE_1, (char)(48+BCD1));
        }

        break;
    case TEST_BLUE:
        // message
        LCD_Clear(LCD_COLOR_BLACK);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        //  LCD_SetFont(&Font16x24); sBuf = "BLUE TEST";
        // LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);
        RGB_ZERO;
        break;
    case TEST_BLUE+1:
    case TEST_BLUE+2:
    case TEST_BLUE+3:
    case TEST_BLUE+4:
    case TEST_BLUE+5:
    case TEST_BLUE+6:
    case TEST_BLUE+7:
    case TEST_BLUE+8:
    case TEST_BLUE+9:
    case TEST_BLUE+10:
        if(blue <= MAX_BLUE)
        {
            blue = (LCD_STATE-TEST_BLUE)*MAX_BLUE/10;
            LCD_Clear(RGB_ASSEMBLE(red, green, blue));
            intToBCD4321(LCD_STATE-TEST_BLUE);
            LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
            // LCD_SetFont(&Font16x24); LCD_DisplayChar(0, LCD_LINE_1, (char)(48+BCD2)); LCD_DisplayChar(17, LCD_LINE_1, (char)(48+BCD1));

        }
        else
        {
            blue = MAX_BLUE;
            LCD_Clear(RGB_ASSEMBLE(red, green, blue));
            intToBCD4321(LCD_STATE-TEST_BLUE);
            LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
            //LCD_SetFont(&Font16x24); LCD_DisplayChar(0, LCD_LINE_1, (char)(48+BCD2)); LCD_DisplayChar(17, LCD_LINE_1, (char)(48+BCD1));
        }

        break;
    case TEST_BLACK:
        // message
        LCD_Clear(LCD_COLOR_BLACK);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        //LCD_SetFont(&Font16x24); sBuf = "TESTING BLACK";
        //   LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);

        break;
    case TEST_WHITE:
        // message
        LCD_Clear(LCD_COLOR_WHITE);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        // LCD_SetFont(&Font16x24); sBuf = "TESTING WHITE";
        // LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);

        break;
    case TEST_GRADIENT:
        // message
        LCD_Clear(LCD_COLOR_BLACK);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        //   LCD_SetFont(&Font16x24); sBuf = "GRADIENT";
        //  LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);
        ROW_COL_ZERO;
        RGB_ZERO;
        break;
    case TEST_GRADIENT+1:

        // --------------------------------------------------
        // gradient test
        // make gradient color 5-6-5 (bits)
        // have red go across rows, green across columns, blue distributed from rows and cols
        // --------------------------------------------------
        while(row < 320)
        {
            red = row*MAX_RED/MAX_ROWS;
            while(col < 240)
            {
                green = col*MAX_GREEN/MAX_COLS;
                blue = row*MAX_BLUE/MAX_ROWS*col*MAX_BLUE/MAX_COLS;

                LCD_SetTextColor(RGB_ASSEMBLE(red, green, blue));
                PutPixel((int16_t)col++, (int16_t)row);
            }

            row++;
            col = 0;

            if(row == 320)
            {
                break;
            }
        }

        break;
    case TEST_BITMAP:
        // --------------------------------------------------
        // show bitmap
        // --------------------------------------------------
        // message
        LCD_Clear(LCD_COLOR_BLACK);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        // LCD_SetFont(&Font16x24); sBuf = "BITMAP";
        //LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);
        break;
    case TEST_BITMAP2:
        LCD_Clear(LCD_COLOR_BLACK);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        //writeBMP((uint16_t const *)&BMP_DIVE);
        break;
    case TEST_BITMAP3:
        LCD_Clear(LCD_COLOR_BLACK);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        //writeBMP((uint16_t const *)&BMP_COLORS);
        break;
    case TEST_POWER:
        // --------------------------------------------------
        // power modes
        // --------------------------------------------------
        // message
        LCD_Clear(LCD_COLOR_BLACK);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        //     LCD_SetFont(&Font16x24); sBuf = "STANDBY in 2s";
        // LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);
        Delay_ms(2000);
        LCD_STANDBY_MODE_ON;
        BKL_OFF;
        break;
    case TEST_POWER+1:
        // message
        LCD_Clear(LCD_COLOR_BLACK);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        //    LCD_SetFont(&Font16x24); sBuf = "STANDBY OFF";
        LCD_STANDBY_MODE_OFF;
        BKL_ON;
        // LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);
        Delay_ms(2000);
        break;
    case TEST_TYPICAL:
        LCD_Clear(LCD_COLOR_BLACK);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        //writeBMP((uint16_t const *)&BMP_COLORS);
        //SetTIM3Duty(BKL_CCR_Val_1);
        setupPWMTimer(15);

        LCD_STATE++;
        SET_PROCESS_500MS_UPDT; // start 500ms update
        break;
    case TEST_TYPICAL+1:

        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        // update a couple lines of text
        //   LCD_SetFont(&Font16x24); sBuf = "SOME TEXT 1";
        // LCD_DisplayStringLine(LCD_LINE_1, (uint8_t *)sBuf);
        //   LCD_SetFont(&Font16x24); sBuf = "SOME TEXT 2";
        //   LCD_DisplayStringLine(LCD_LINE_2, (uint8_t *)sBuf);

        break;
    case TEST_TYPICAL+2:

        //writeBMP((uint16_t const *)&BMP_COLORS);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        // update a couple lines of text
        //    LCD_SetFont(&Font16x24); sBuf = "SOME TEXT 3";
        //   LCD_DisplayStringLine(LCD_LINE_1, (uint8_t *)sBuf);
        //    LCD_SetFont(&Font16x24); sBuf = "SOME TEXT 4";
        //    LCD_DisplayStringLine(LCD_LINE_2, (uint8_t *)sBuf);

        break;

    case TEST_BKL1_2:
        //writeBMP((uint16_t const *)&BMP_ERROR);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        // LCD_SetFont(&Font16x24); sBuf = "BKLT 5%";
        //  LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);
        //BKL_ON; SetTIM3Duty(BKL_CCR_Val_1);
        setupPWMTimer(5);
        break;
    case TEST_BKL2_2:
        //writeBMP((uint16_t const *)&BMP_ERROR);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        //    LCD_SetFont(&Font16x24); sBuf = "BKLT 10%";
        //LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);
        //BKL_ON; SetTIM3Duty(BKL_CCR_Val_2);
        setupPWMTimer(10);
        break;
    case TEST_BKL3_2:
        //writeBMP((uint16_t const *)&BMP_ERROR);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        //      LCD_SetFont(&Font16x24); sBuf = "BKLT 15%";
        //   LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);
        //BKL_ON; SetTIM3Duty(BKL_CCR_Val_3);
        setupPWMTimer(15);
        break;
    case TEST_BKL4_2:
        //writeBMP((uint16_t const *)&BMP_ERROR);
        LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
        //    LCD_SetFont(&Font16x24); sBuf = "BKLT 50%";
        // LCD_DisplayStringLine(LCD_LINE_5, (uint8_t *)sBuf);
        //BKL_ON; SetTIM3Duty(BKL_CCR_Val_4);
        setupPWMTimer(50);
        break;
    case TEST_BKL4_2+1:
        CLR_PROCESS_500MS_UPDT; // stop 500ms update
        LCD_STATE = NOLCD;
        lcd_start_procedure();
        break;
    case PROCESS_MODE:
        processMode();
        //SET_PROCESS_500MS_UPDT; // start 500ms update

        break;
    default:
        break;
    }

#ifdef USE_FREQ_SWITCH
    FREQUENCY = FREQUENCY_NOM;
    setPLL();
#endif

#ifdef TIMING_PIN
    GPIO_ResetBits(GPIOA, GPIO_Pin_7);
#endif
}








//SEPIA
