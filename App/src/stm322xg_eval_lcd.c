/**
  ******************************************************************************
  * @file    stm322xg_eval_lcd.c
  * @author  MCD Application Team
  * @version V4.6.1
  * @date    18-April-2011
  * @brief   This file includes the LCD driver for AM-240320L8TNQW00H (LCD_ILI9320)
  *          and AM240320D5TOQW01H (LCD_ILI9325) Liquid Crystal Display Modules
  *          of STM322xG-EVAL evaluation board(MB786) RevA and RevB.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "alldefs.h"
#include "stm322xg_eval_lcd.h"
//#include "fonts.c"
#include "flashmem.h"
/** @defgroup STM322xG_EVAL_LCD_Private_Defines
  * @{
  */


#define MAX_POLY_CORNERS   200
#define POLY_Y(Z)          ((int32_t)((Points + Z)->X))
#define POLY_X(Z)          ((int32_t)((Points + Z)->Y))
/**
  * @}
  */

/** @defgroup STM322xG_EVAL_LCD_Private_Macros
  * @{
  */
//#define ABS(X)  ((X) > 0 ? (X) : -(X))
/**
  * @}
  */

/** @defgroup STM322xG_EVAL_LCD_Private_Variables
  * @{
  */
extern const tImage *CurrentChar;
/* Global variables to set the written text color */
//static __IO uint16_t TextColor = 0x0000, BackColor = 0xFFFF;
uint16_t TextColor;
uint16_t BackColor;
uint16_t LenWord[100];
uint16_t SpaceLeft[100];
uint16_t HeightNow = 0;
extern const tChar Font_array[];
extern const tChar *FontSet;
//extern stopwatch_delay();
extern void Delay_ms(uint32_t time_ms);
uint8_t ColumnNum;//Return the numbers of column

/**
  * @}
  */


/** @defgroup STM322xG_EVAL_LCD_Private_FunctionPrototypes
  * @{
  */
#if 0
#ifndef USE_Delay
static void delay(__IO uint32_t nCount);
#endif /* USE_Delay*/
#endif
//static void PutPixel(int16_t x, int16_t y);




/**
  * @brief  Writes to the selected LCD register.
  * @param  LCD_Reg: address of the selected register.
  * @param  LCD_RegValue: value to write to the selected register.
  * @retval None
  */


void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
{

    /* Write 16-bit Index, then Write Reg */
    *LCD_REG = LCD_Reg;
    /* Write 16-bit Reg */
    *LCD_RAM = LCD_RegValue;
    /*
        #ifdef TEST_READWRITE
        uint16_t rr = LCD_ReadReg(LCD_Reg);
        if(rr != LCD_RegValue)
        {
            // break here
            __asm("nop");
        }
        #endif
      */
}



/**
  * @brief  Reads the selected LCD Register.
  * @param  LCD_Reg: address of the selected register.
  * @retval LCD Register Value.
  */
uint16_t LCD_ReadReg(uint8_t LCD_Reg)
{
    /* Write 16-bit Index (then Read Reg) */
    *LCD_REG = LCD_Reg;
    /* Read 16-bit Reg */
    return (*LCD_RAM);
}

/**
  * @brief  DeInitializes the LCD.
  * @param  None
  * @retval None
  */
void LCD_DeInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*!< LCD Display Off */
    LCD_DISPLAY_OFF;

    //  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
    FSMC_NORSRAMDeInit(FSMC_Bank1_NORSRAM1);

    /*-- GPIO Configuration ------------------------------------------------------*/
    /* SRAM Data lines configuration */
    /* E.Pataky modified for BLANVIEW - checked all good */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |
                                  GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                  GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //GPIO_AF_MCO;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_MCO);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_MCO);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_MCO);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_MCO);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_MCO);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_MCO);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_MCO);


    /* E.Pataky modified for BLANVIEW - checked all good */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
                                  GPIO_Pin_15;

    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_MCO);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_MCO);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_MCO);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_MCO);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_MCO);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_MCO);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_MCO);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_MCO);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_MCO);

    /* E.Pataky RS line configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource3, GPIO_AF_MCO);

    /* NOE and NWE configuration */
    /* E.Pataky modified for BLANVIEW - checked all good */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource4, GPIO_AF_MCO);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource5, GPIO_AF_MCO);

    /* NE3 configuration */
    /* E.Pataky modified for BLANVIEW */
    /* E.Pataky NE1 configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_MCO);
}

/**
  * @brief  Initializes the LCD.
  * @param  None
  * @retval None
  */
void STM322xG_LCD_Init(void)
{
    //unsigned int chipid;

    LCD_RST_SEQUENCE;

    /* Configure the LCD Control pins --------------------------------------------*/
    LCD_CtrlLinesConfig();

    /* Configure the FSMC Parallel interface -------------------------------------*/
    LCD_FSMCConfig();

    Delay_ms(50);

    /* E.Pataky modified for BLANVIEW */
    // Check HX8347 chipid
    //chipid = LCD_ReadReg(HX8347_R67H);

    /*if(chipid != HX8347_HIMAXID_CODE)
    {
        printf("Read HX8347 chip ID error, skip initialization.\r\n");
        return ;
    }
    else*/
    {
        // himax HX8347-A01 (Blanview)
        LCD_WriteReg(0x96,0x01);    // RS=0 , TEST 1 setteing, RS=1
        LCD_WriteReg(0x19,0x87);    // OSC control
        Delay_ms(10);
        LCD_WriteReg(0x00,0x0);     //
        LCD_WriteReg(0x26,0x80);    // Display OFF setting
        LCD_WriteReg(0x1B,0x0C);        // GASENB:0:0:PON:DK:XDK:VLCD:STB
        LCD_WriteReg(0x43,0x00);
        LCD_WriteReg(0x20,0x00);    // Power supply setting initializing
        LCD_WriteReg(0x1F, 0x07);
        LCD_WriteReg(0x44, 0x7F);   // VCOM control 2
        LCD_WriteReg(0x45, 0x14);   // VCOM control 3
        LCD_WriteReg(0x1D, 0x05);
        LCD_WriteReg(0x1E, 0x00);
        LCD_WriteReg(0x1C, 0x04);   // Power supply operation start
        LCD_WriteReg(0x1B, 0x14);
        Delay_ms(40);
        LCD_WriteReg(0x43, 0x80);
        LCD_WriteReg(0x42, 0x08);   // Power control   BGP control
        LCD_WriteReg(0x23, 0x95);   // Cycle control
        LCD_WriteReg(0x24, 0x95);
        LCD_WriteReg(0x25, 0xFF);
        LCD_WriteReg(0x21, 0x10);
        LCD_WriteReg(0x2B, 0x00);
        LCD_WriteReg(0x95, 0x01);

        LCD_WriteReg(0x1A, 0x00);   // OSC control
        LCD_WriteReg(0x93, 0x0F);
        LCD_WriteReg(0x70, 0x66);
        LCD_WriteReg(0x18, 0x01);   // Gate scan control: 0:0:0:0:0:0:SCROL:SM
        LCD_WriteReg(0x46, 0x86);   // gamma control
        LCD_WriteReg(0x47, 0x60);

        LCD_WriteReg(0x48, 0x01);
        LCD_WriteReg(0x49, 0x67);
        LCD_WriteReg(0x4A, 0x46);
        LCD_WriteReg(0x4B, 0x13);
        LCD_WriteReg(0x4C, 0x01);
        LCD_WriteReg(0x4D, 0x67);

        LCD_WriteReg(0x4E, 0x00);
        LCD_WriteReg(0x4F, 0x13);
        LCD_WriteReg(0x50, 0x02);
        LCD_WriteReg(0x51, 0x00);
        LCD_WriteReg(0x38, 0x00);   // RGB interface control
        LCD_WriteReg(0x39, 0x00);

        LCD_WriteReg(0x27, 0x02);   // Display control
        LCD_WriteReg(0x28, 0x03);
        LCD_WriteReg(0x29, 0x08);
        LCD_WriteReg(0x2A, 0x08);
        LCD_WriteReg(0x2C, 0x08);
        LCD_WriteReg(0x2D, 0x08);
        LCD_WriteReg(0x35, 0x09);
        LCD_WriteReg(0x36, 0x09);
        LCD_WriteReg(0x91, 0x14);
        LCD_WriteReg(0x37, 0x00);

        LCD_WriteReg(0x01, 0x06);   // DISPLAY MODE, -:-:-:-:IDMON:INVON:NORON:PTLON

        LCD_WriteReg(0x3A, 0xA1);   // Cycle control
        LCD_WriteReg(0x3B, 0xA1);
        LCD_WriteReg(0x3C, 0xA0);
        LCD_WriteReg(0x3D, 0x00);
        LCD_WriteReg(0x3E, 0x2D);

        LCD_WriteReg(0x40, 0x03);
        LCD_WriteReg(0x41, 0xCC);
        LCD_WriteReg(0x0A, 0x00);   //  Partial Area setting
        LCD_WriteReg(0x0B, 0x00);
        LCD_WriteReg(0x0C, 0x01);
        LCD_WriteReg(0x0D, 0x3F);
        LCD_WriteReg(0x0E, 0x00);   // Vertical Scroll setting
        LCD_WriteReg(0x0F, 0x00);
        LCD_WriteReg(0x10, 0x01);
        LCD_WriteReg(0x11, 0x40);
        LCD_WriteReg(0x12, 0x00);
        LCD_WriteReg(0x13, 0x00);

        LCD_WriteReg(0x14, 0x00);
        LCD_WriteReg(0x15, 0x00);


        LCD_WriteReg(0x02, 0x00);   // Column start address setting
        LCD_WriteReg(0x03, 0x00);   // Column start address setting
        LCD_WriteReg(0x04, 0x01);   // Column end address setting
        LCD_WriteReg(0x05, 0x3F);   // Column end address setting
        LCD_WriteReg(0x06, 0x00);   // Row start address setting
        LCD_WriteReg(0x07, 0x00);   // Row start address setting
        LCD_WriteReg(0x08, 0x00);   // Row end address setting
        LCD_WriteReg(0x09, 0xEF);   // Row end address setting

        LCD_WriteReg(0x16, 0xA8);   // RAM access control, 00000000 MY:MX:MV:0:BGR:0:0:0
        LCD_WriteReg(0x72, 0x00);   // Data control

        LCD_WriteReg(0x22, 0x00);   // Data Write Index
        Delay_ms(60);

        LCD_WriteReg(0x94, 0x0A);   // Display on setting
        LCD_WriteReg(0x90, 0x7F);
        LCD_WriteReg(0x26, 0x84);
        Delay_ms(40);
        LCD_WriteReg(0x26, 0xA4);
        LCD_WriteReg(0x26, 0xAC);
        Delay_ms(40);
        LCD_WriteReg(0x26, 0xBC);
        LCD_WriteReg(0x96, 0x00);   // Test 1 setting
        Delay_ms(40);

        LCD_DISPLAY_ON;
    }

    // LCD_SetFont(&LCD_DEFAULT_FONT);
}

/**
  * @brief  Sets the LCD Text and Background colors.
  * @param  _TextColor: specifies the Text Color.
  * @param  _BackColor: specifies the Background Color.
  * @retval None
  */
void LCD_SetColors(__IO uint16_t _TextColor, __IO uint16_t _BackColor)
{
    TextColor = _TextColor;
    BackColor = _BackColor;
}

/**
  * @brief  Gets the LCD Text and Background colors.
  * @param  _TextColor: pointer to the variable that will contain the Text
            Color.
  * @param  _BackColor: pointer to the variable that will contain the Background
            Color.
  * @retval None
  */
void LCD_GetColors(__IO uint16_t *_TextColor, __IO uint16_t *_BackColor)
{
    *_TextColor = TextColor;
    *_BackColor = BackColor;
}

/**
  * @brief  Sets the Text color.
  * @param  Color: specifies the Text color code RGB(5-6-5).
  * @retval None
  */
void LCD_SetTextColor(__IO uint16_t Color)
{
    TextColor = Color;
}


/**
  * @brief  Sets the Background color.
  * @param  Color: specifies the Background color code RGB(5-6-5).
  * @retval None
  */
void LCD_SetBackColor(__IO uint16_t Color)
{
    BackColor = Color;
}

/**
  * @brief  Gets the Text Font.
  * @param  None.
  * @retval the used font.
  */
//sFONT *LCD_GetFont(void)
//{
//  return CurrentChar;
//}

/**
  * @brief  Clears the selected line.
  * @param  Line: the Line to be cleared.
  *   This parameter can be one of the following values:
  *     @arg Linex: where x can be 0..n
  * @retval None
  */
void LCD_ClearLine(uint16_t Line)
{
    uint16_t refcolumn = LCD_MAX_WIDTH - 1;
    /* Send the string character by character on lCD */
    while (((refcolumn + 1)& 0xFFFF) >= CurrentChar->width)
    {
        /* Display one character on LCD */
        //LCD_DisplayChar(Line, refcolumn, ' ');
        /* Decrement the column position by 16 */
        refcolumn -= CurrentChar->width;
    }
}

/**
  * @brief  Clears the hole LCD.
  * @param  Color: the color of the background.
  * @retval None
  */
void LCD_Clear(uint16_t Color) {
    uint32_t index = 0;
    LCD_SetCursor(0x00, 0x00); //0x013F);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    for(index = 0; index < 240*320; index++)
    {
        *LCD_RAM = Color;
    }
}


//------------------------------------------------------------------------------
/// Set cursor of LCD srceen.
/// \param pLcdBase   LCD base address.
/// \param x          X-coordinate of upper-left corner on LCD.
/// \param y          Y-coordinate of upper-left corner on LCD.
//------------------------------------------------------------------------------

void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos) {
    unsigned char x1, x2, y1, y2;
    x1 = Xpos & 0xff;
    x2 = (Xpos & 0xff00) >>8;
    y1 = Ypos & 0xff;
    y2 = (Ypos & 0xff00) >>8;
    LCD_WriteReg(HX8347_R02H, x2); // column high
    LCD_WriteReg(HX8347_R03H, x1); // column low
    LCD_WriteReg(HX8347_R06H, y2); // row high
    LCD_WriteReg(HX8347_R07H, y1); // row low
}


/**
  * @brief  Displays a character from X, Y position.
  * @param  Line: the Line where to display the character shape .
  *   This parameter can be one of the following values:
  *
  * @param  *ptr: pointer to string to display on LCD.
  * @retval None
  */
inline void LCD_DisplayStringLine(uint16_t X, uint16_t Y, char* ptr)
{
    /* Send the string character by character on lCD */
    while ((*ptr != 0))
    {
        while ((*ptr != 0) & (X + LCD_CHAR_SPACE +8) <= LCD_MAX_WIDTH)
        {
            /* Display one character on LCD */
            LCD_DisplayChar(X, Y, *ptr);
            X += CurrentChar->width + LCD_CHAR_SPACE;
            /* Point on the next character */
            ptr++;
        }
        X = 0;
    }
}
/**
  * @brief  Sets a display window
  * @param  Xpos: specifies the X bottom left position.
  * @param  Ypos: specifies the Y bottom left position.
  * @param  Height: display window height.
  * @param  Width: display window width.
  * @retval None
  */
void LCD_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width)
{
    /* Horizontal GRAM Start Address */
    if(Xpos >= Height)
    {
        LCD_WriteReg(LCD_REG_80, (Xpos - Height + 1));
    }
    else
    {
        LCD_WriteReg(LCD_REG_80, 0);
    }
    /* Horizontal GRAM End Address */
    LCD_WriteReg(LCD_REG_81, Xpos);
    /* Vertical GRAM Start Address */
    if(Ypos >= Width)
    {
        LCD_WriteReg(LCD_REG_82, (Ypos - Width + 1));
    }
    else
    {
        LCD_WriteReg(LCD_REG_82, 0);
    }
    /* Vertical GRAM End Address */
    LCD_WriteReg(LCD_REG_83, Ypos);
    LCD_SetCursor(Xpos, Ypos);
}

/**
  * @brief  Disables LCD Window mode.
  * @param  None
  * @retval None
  */
void LCD_WindowModeDisable(void)
{
    LCD_SetDisplayWindow(239, 0x13F, 240, 320);
    LCD_WriteReg(LCD_REG_3, 0x1018);
}

/**
  * @brief  Displays a line.
  * @param Xpos: specifies the X position.
  * @param Ypos: specifies the Y position.
  * @param Length: line length.
  * @param Direction: line direction.
  *   This parameter can be one of the following values: Vertical or Horizontal.
  * @retval None
  */
void LCD_DrawLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction)/*ok*/
{
    uint32_t i = 0;

    //LCD_SetCursor(Xpos, 319 - Ypos);
    Xpos = 320 - Xpos;
    ////Xpos = Xpos + Length;
    //LCD_SetCursor(Xpos, Ypos);

    if(Direction == LCD_DIR_VERTICAL)
        //if(Direction == LCD_DIR_HORIZONTAL)
    {
        LCD_SetCursor(Xpos, Ypos  );
        LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */

        for(i = 0; i < Length; i++)
        {
            LCD_WriteRAM(TextColor);
        }
    }
    else
    {
        LCD_SetCursor(Xpos, Ypos);
        for(i = 0; i < Length; i++)
        {
            LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
            LCD_WriteRAM(TextColor);
            Xpos--;
            //LCD_SetCursor(Xpos, 319 - Ypos);
            LCD_SetCursor(Xpos, Ypos);

        }
    }
}

const tImage* getCharImage(uint16_t i)
{
    return FontSet[i].image;
}

u16 b2_linear(u16 a1, u16 b1, u16 a3, u16 b3, u16 a2) {
    u16 b2=0;
    b2=b1+((b3-b1)*((a2-a1)/(a3-a1)));
    return b2;
}

uint16_t ImplementColor(uint16_t PixelColor) {
    uint16_t redPart;
    uint16_t greenPart;
    uint16_t bluePart;
    //With background color Black
    if(Black==BackColor) {
        //Get each value of Black foreground and White background
        PixelColor=(PixelColor&0x07E0)>>3;
        //Reverse the value to Black background
        //Assembly the value Red Green Blue
        switch(TextColor) {
        case LCD_COLOR_WHITE:
            PixelColor=255-PixelColor;
            PixelColor=ASSEMBLE_RGB(PixelColor, PixelColor, PixelColor);
            break;
        case LCD_COLOR_RED:
            PixelColor=255-PixelColor;
            PixelColor=ASSEMBLE_RGB(PixelColor, 0, 0);
            break;
        case LCD_COLOR_GREEN:
            PixelColor=255-PixelColor;
            PixelColor=ASSEMBLE_RGB(0, PixelColor, 0);
            break;
        case LCD_COLOR_BLUE:
            PixelColor=255-PixelColor;
            PixelColor=ASSEMBLE_RGB(0, 0, PixelColor);
            break;
        case LCD_COLOR_YELLOW:
            PixelColor=255-PixelColor;
            PixelColor=ASSEMBLE_RGB(PixelColor, PixelColor, 0);
            break;
        case LCD_COLOR_GREY:
            PixelColor=(PixelColor&0x07E0)>>3;
            //PixelColor= 270 - PixelColor;
            //  PixelColor=ASSEMBLE_RGB(PixelColor, PixelColor, 0);
            bluePart = redPart = greenPart = (1-(PixelColor/255))*102;
            PixelColor=ASSEMBLE_RGB(redPart, greenPart , bluePart);
            break;
        default:
            break;
        }
    }
    //Whith Red background
    else if(Red==BackColor) {
        //Get each value of Black foreground and White background
        PixelColor=(PixelColor&0x07E0)>>3;
        //Assembly the value Red Green Blue
        switch(TextColor) {
        case LCD_COLOR_WHITE:
            //Reverse the value to Black background
            PixelColor=285-PixelColor;
            PixelColor=ASSEMBLE_RGB(0xFF, PixelColor, PixelColor);
            break;
        case LCD_COLOR_BLACK:
            PixelColor=ASSEMBLE_RGB(PixelColor, 0, 0);
            break;
        default:
            break;
        }
    }
    //With Green background
    else if(LCD_COLOR_GREEN==BackColor) {
        //Get each value of Black foreground and White background
        PixelColor=(PixelColor&0x07E0)>>3;
        //Assembly the value Red Green Blue
        switch(TextColor) {
        case LCD_COLOR_BLACK:
            PixelColor=ASSEMBLE_RGB(0, PixelColor, 0);
            break;
        case LCD_COLOR_WHITE:
            PixelColor=285-PixelColor;
            PixelColor=ASSEMBLE_RGB(PixelColor, 0xFF, PixelColor);
            break;
        default:
            break;
        }
    }
    //Whith Yellow background
    else if(LCD_COLOR_YELLOW==BackColor) {
        switch(TextColor) {
        case LCD_COLOR_BLACK:
            PixelColor= PixelColor & Yellow;
            break;
        default:
            break;
        }
    }
    //Grey background
    else if(Grey==BackColor) {
        switch(TextColor) {
        case Green:
        case Yellow:
        case White:
            //case Blue:
            // get color components of pixelColor
            redPart = (PixelColor >> 11) & 0x001f ;
            greenPart = (PixelColor >> 5) & 0x003f ;
            bluePart = (PixelColor & 0x001f) ;
            redPart = (redPart) * (0x001F - 15) / 0x001F;
            redPart = (0x001F - redPart);
            greenPart = (greenPart) * (0x003F - 27) / 0x003F;
            greenPart = (0x003F - greenPart);
            bluePart = (bluePart) * (0x001F - 15) / 0x001F;
            bluePart = (0x001F - bluePart);
            // now assemble and display
            PixelColor= ((redPart << 11) | (greenPart << 5) |bluePart);
            break;
        case Red:
            PixelColor=(PixelColor&0x07E0)>>3;
            bluePart = greenPart = (102*PixelColor)/255;
            redPart= ~greenPart;
            PixelColor=ASSEMBLE_RGB(redPart, greenPart , bluePart);
            break;
        case Blue:
            PixelColor = (PixelColor&0x07E0)>>3;
            redPart = greenPart = (102*PixelColor)/255;
            bluePart = ~greenPart;
            PixelColor=ASSEMBLE_RGB(redPart, greenPart , bluePart);
            break;
        case Black:    //Perfect
            PixelColor = (PixelColor&0x07E0)>>3;
            bluePart = redPart = greenPart = (102*PixelColor)/255;
            PixelColor=ASSEMBLE_RGB(redPart, greenPart , bluePart);
            break;
        default:
            //return 0x2945;
            break;
        }
    }
    //White background
    else if(White == BackColor) {
        switch(TextColor) {
        case Black:
            return PixelColor;
            break;
        case Blue:
            return (PixelColor|Blue);
            break;
        case Red:
            return (PixelColor|Red);
            break;
        default:
            break;
        }
    }
    //Blue
    else if(Blue==BackColor) {
        switch(TextColor) {
        case White:
            //Get each value of Black foreground and White background
            PixelColor=(PixelColor&0x07E0)>>3;
            //Reverse the value to Black background
            PixelColor = 285-PixelColor;
            PixelColor = ASSEMBLE_RGB(PixelColor, PixelColor, 160 );
            break;
        default:
            break;
        }
    }
    else {
    }
    //Return the Pixel color afer processing
    return PixelColor;
}


/**DucThinh90
  * @brief  Draws a character on LCD.
  * @param  Xpos: the Line where to display the character shape.
  * @param  Ypos: start column address.
  * @param  c: pointer to the character data.
  * @retval None
  */
#ifdef ANTIALIASING
inline void LCD_DrawChar(uint16_t Xpos, uint16_t Ypos, const tImage *_char) {
    uint16_t ScanX = 0;
    uint16_t ScanY = 0;
    int16_t sequence = 0;
    int16_t nonsequence = 0;
    u16 Value = 0;
    u16* DataFontPtr = (u16*) (_char->_data);

    for(ScanY = 0; ScanY < _char->height; ScanY ++) { //Scan the height of character
        for (ScanX = 0 ; ScanX < _char->width; ScanX ++) { //Scan the width of character
            //load new data
            if((sequence == 0) && (nonsequence == 0)) {
                sequence = *(DataFontPtr++);
                if(sequence < 0) {
                    nonsequence = -sequence;
                    sequence = 0;
                }
            }
            if(sequence > 0) {
                Value = *DataFontPtr;
                sequence --;
                if(sequence == 0) {
                    DataFontPtr++;
                }
            }
            if(nonsequence > 0) {
                Value = *(DataFontPtr++);
                nonsequence--;
            }
            if (Value != 0xffff) { //If found the White color--> pass by
                LCD_SetCursor(ScanX + Xpos, ScanY+Ypos);
                LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
                LCD_WriteRAM((Value == 0x0000) ? TextColor : (ImplementColor(Value)));
            }
        }
    }
}
//#endif
//When no antialiasing
#else
void PutPixelColor(int16_t x, int16_t y)
{
    LCD_SetCursor(x, y);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    LCD_WriteRAM(TextColor);//Write the TextColor to the pixel
}
void LCD_DrawChar(uint16_t Xpos, uint16_t Ypos, tImage *_char) {
    u16 value = 0;
    u16 x0, y0;
    u16 counter = 0;
    const u16 *pdata = (const u16 *) _char->_data;
    for (y0 = 0; y0 < _char->height; y0++) {
        for (x0 = 0; x0 < _char->width; x0++) {
            if (counter == 0) {
                value = *pdata++;
                counter = 16;
            }
            counter--;
            if ((value & 0x8000) == 0x8000) {
                PutPixelColor(Xpos + x0, Ypos + y0);
            }
            //else {
            //TextColor = BackColor;
            //PutPixelColor(Xpos + x0, Ypos + y0);
            //}
            value = value << 1;
        }
    }
}
#endif
/**
  * @brief  Displays one character (16dots width, 24dots height).
  * @param  Line: the Line where to display the character shape .
  *   This parameter can be one of the following values:
  *     @arg Linex: where x can be 0..9
  * @param  Column: start column address.
  * @param  Ascii: character ascii code, must be between 0x20 and 0x7E.
  * @retval None
  */

void LCD_DisplayChar(uint16_t Column, uint16_t Line, uint8_t Ascii) {
    Ascii -= 32;
    CurrentChar = (ptImage)((FontSet + Ascii)->image);
    LCD_DrawChar(Column, Line, CurrentChar);
}

//Get the Length of the difined string ducthinh90
void GetTheWordLength(char *_ptrCheck) {
    uint16_t LenOfWord = 0;
    uint16_t i = 0;//The number of arrray or number of word
    uint8_t _ascii;
    /* Send the string character by character on lCD */
    while ((*_ptrCheck != 0)) { //Check characters to the end of string
        _ascii = *_ptrCheck;
        if(_ascii != ' ') {
            _ascii -= 32;// *ptrCheck = ASCII table
            CurrentChar = (ptImage)((FontSet + _ascii)->image);
            /* Get the Length of each words */
            LenOfWord += CurrentChar->width;
        }
        else {
            LenWord[i++] = LenOfWord;
            LenOfWord = 0;//Reset the Length value
        }
        /* Point on the next character */
        _ptrCheck ++;
    }
    LenWord [i] = LenOfWord;//If not found the space that mean the end of the string still put to the last element array
}
inline void LCD_DisplayStringLine_As_Left(uint16_t _X1,uint16_t _X2, uint16_t _Y, char *_ptr) {
    uint16_t check = 0;
    uint16_t Xtemp = _X1;
    uint16_t XRemain = 0;
    GetTheWordLength(_ptr);
    HeightNow = 0;
    /* Send the string character by character on lCD */
    while ((*_ptr != 0) && (_X1 < _X2))   //check all the characters
    {
        while ((*_ptr != 0) && (LenWord [check] < (_X2 - XRemain)) && (_X1 < _X2)) //Check out the enough space
        {
            /* Display one character on LCD */
            LCD_DisplayChar(_X1, _Y, *_ptr);
            _X1 += CurrentChar->width;
            /* Point to the next character */
            _ptr++;
            if (*_ptr == ' ') {
                check ++;                    //Next word array
                XRemain = _X1 + SpaceWidth;  //the sceen too fit when choose X1 only and we must add ahalf space to reserve
            }
        }
        _X1 = Xtemp;                         //return the position to start point setup
        (*_ptr == ' ') ? _ptr++: _ptr;       //pass by the space infront of each line...
        _Y += (CurrentChar->height)*1.7;     //increase the height to next line with addition space
        XRemain = 0;                         //must be reloaded default value before the next loop
    }
    HeightNow =_Y;
}

void CenterPrepare(uint16_t X1_,uint16_t X2_, char *ptr_) {
    uint16_t check  = 0;
    uint8_t _ascii  = 0;
    uint16_t Xtemp  = X1_;
    uint16_t XRemain = 0;
    uint16_t i      = 0;
    uint16_t sub    = X2_-X1_;
    GetTheWordLength(ptr_);
    /* Send the string character by character on lCD */
    while ((*ptr_ != 0) && (X1_ < X2_)) { //check all the characters and quit when X1 > X2 ...it impossible
        while ((*ptr_ != 0) && (LenWord [check] < (X2_ - XRemain)) && (X1_ < X2_)) { //Check out the enough space
            _ascii = *ptr_;
            _ascii -= 32;     // *ptrCheck = ASCII table
            CurrentChar =(ptImage)((FontSet + _ascii)->image);
            X1_ += CurrentChar->width;
            /* Point to the next character */
            ptr_++;
            if (*ptr_ == ' ') {
                check ++;//Next word array
                XRemain = X1_+ SpaceWidth;
            }
        }
        SpaceLeft[i++] = sub -X1_ + Xtemp;
        X1_ = Xtemp;      //return the position to start point setup
        XRemain = 0;      //must be reloaded default value before the next loop
    }
}

inline void LCD_DisplayStringLine_Center(uint16_t X1,uint16_t X2, uint16_t _Y, char *ptr) {
    uint16_t check = 0;
    uint16_t Xtemp = X1;
    uint16_t XRemain = 0;
    uint16_t i= 0;
    HeightNow = 0;
    CenterPrepare(X1, X2, ptr);
    /* Send the string character by character on lCD */
    while ((*ptr != 0) && (X1 < X2)) //check all the characters and quit when X1 > X2 ...it impossible
    {
        while ((*ptr != 0) && (LenWord [check] < (X2 - XRemain)) && (X1 < X2)) //Check out the enough space
        {
            /* Display one character on LCD */
            LCD_DisplayChar((uint16_t)(X1 + (SpaceLeft[i]*0.5)), _Y, *ptr);
            X1 += CurrentChar->width;
            /* Point to the next character */
            ptr++;
            if (*ptr == ' ')
            {
                check ++;//Next word array
                XRemain = X1+ SpaceWidth ;//the sceen too fit when choose X1 only and we must add ahalf space to reserve
            }
        }
        i++;
        X1 = Xtemp ; //return the position to start point setup
        _Y += (CurrentChar->height)*1.3;//increase the height to next line
        XRemain = 0;    //must be reloaded default value before the next loop

    }
    HeightNow = _Y;
}

/*ducthinh90 : get the length of string line*/
uint16_t GetTheLineLength(char*_ptrCheck)
{
    uint16_t LenOfLine = 0;
    uint8_t _ascii;
    while ((*_ptrCheck != 0))//Check characters to the end of string
    {
        _ascii = *_ptrCheck;
        _ascii -= 32;// *ptrCheck = ASCII table
        CurrentChar =(ptImage)((FontSet + _ascii)->image);
        LenOfLine += CurrentChar->width;
        /* Point to the next character */
        _ptrCheck ++;
    }
    return LenOfLine;
}
void LCD_DisplayStringLine_As_Right(uint16_t X, uint16_t _Y, char* _ptr)
{
    signed int X_;
    X_ = X - GetTheLineLength(_ptr);
    if(X_ > 0)
    {
        LCD_DisplayStringLine(X_, _Y, _ptr);
    }
    else
    {
        X_= 0;
    }
}
void LCD_DrawBMP(uint16_t Xpos, uint16_t Ypos, ptImage _char,u8 quarterpart) {
    uint16_t ScanX      = 0;
    uint16_t ScanY      = 0;
    int16_t sequence    = 0;
    int16_t nonsequence = 0;
    u16 Value = 0;
    u16* DataFontPtr = (u16*) (_char->_data);

    for(ScanY = 0; ScanY < _char->height; ScanY ++) { //Scan the height of character
        for (ScanX = 0 ; ScanX < _char->width; ScanX ++) { //Scan the width of character
            switch (quarterpart) {
            case 0:
                LCD_SetCursor(Xpos+ScanX, Ypos+ScanY);//First quater
                break ;
            case 3:
                LCD_SetCursor(Xpos+(_char->height-ScanY), Ypos+ScanX);//Second quarter
                break;
            case 2:
                LCD_SetCursor(Xpos+(_char->width-ScanX), Ypos+(_char->height-ScanY));//Third quarter
                break;
            case 1:
                LCD_SetCursor(Xpos+ScanY ,Ypos+_char->width-ScanX);//Fourth quarter
                break;
            }
            LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
            //load new data
            if((sequence == 0) && (nonsequence == 0)) {
                sequence = *(DataFontPtr++);
                if(sequence < 0) {
                    nonsequence = -sequence;
                    sequence = 0;
                }
            }
            if(sequence > 0) {
                Value = *DataFontPtr;
                sequence --;
                if(sequence == 0) {
                    DataFontPtr++;
                }
            }
            if(nonsequence > 0) {
                Value = *(DataFontPtr++);
                nonsequence--;
            }
            *LCD_RAM = Value;
        }
    }
}




/**
  * @brief  Displays a rectangle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Height: display rectangle height.
  * @param  Width: display rectangle width.
  * @retval None
  */
//@PhuThinh modifed
void LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Height, uint16_t Width)
{
    //Xpos = 320 - Xpos;
    //Ypos = 240 - Ypos;

    // LCD_DrawLine(0, 60, 160, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(Xpos, Ypos, Width, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(Xpos, (Ypos + Height -1), Width, LCD_DIR_HORIZONTAL);

    LCD_DrawLine(Xpos, Ypos, Height-1, LCD_DIR_VERTICAL);
    LCD_DrawLine((Xpos + Width -1 ),Ypos , Height-1, LCD_DIR_VERTICAL);
}

/*

*/
void LCD_FillRect(u16 PosX, u16 PosY,u16 Width, u16 Height, u16 _Color) {//Fill rectangle with height and wide = 320 , X =0
    u16 Row = PosY;
    u16 Colum = PosX;
    for(Row = PosY; Row < Height + PosY  ; Row++) {
        LCD_SetCursor( PosX, Row);
        LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
        for(Colum = PosX; Colum < PosX+Width; Colum++) {
            *LCD_RAM = _Color;
        }
    }
}


/**
  * @brief  Displays a circle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Radius
  * @retval None
  */

//@PhuThinh modifed
void LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
    int  D;/* Decision Variable */
    uint32_t  CurX;/* Current X Value */
    uint32_t  CurY;/* Current Y Value */

    D = 3 - (Radius << 1);
    CurX = 0;
    CurY = Radius;

    while (CurX <= CurY)
    {
        LCD_SetCursor(Xpos + CurX, Ypos + CurY);
        LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
        LCD_WriteRAM(TextColor);
        LCD_SetCursor(Xpos + CurX, Ypos - CurY);
        LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
        LCD_WriteRAM(TextColor);
        LCD_SetCursor(Xpos - CurX, Ypos + CurY);
        LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
        LCD_WriteRAM(TextColor);
        LCD_SetCursor(Xpos - CurX, Ypos - CurY);
        LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
        LCD_WriteRAM(TextColor);
        LCD_SetCursor(Xpos + CurY, Ypos + CurX);
        LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
        LCD_WriteRAM(TextColor);
        LCD_SetCursor(Xpos + CurY, Ypos - CurX);
        LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
        LCD_WriteRAM(TextColor);
        LCD_SetCursor(Xpos - CurY, Ypos + CurX);
        LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
        LCD_WriteRAM(TextColor);
        LCD_SetCursor(Xpos - CurY, Ypos - CurX);
        LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
        LCD_WriteRAM(TextColor);
        if (D < 0)
        {
            D += (CurX << 2) + 6;
        }
        else
        {
            D += ((CurX - CurY) << 2) + 10;
            CurY--;
        }
        CurX++;
    }
}


/**
  * @brief  Displays a full rectangle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Height: rectangle height.
  * @param  Width: rectangle width.
  * @retval None
  */
//@PhuThinh modifed
void LCD_DrawFullRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)/*OK*/
{


    LCD_SetTextColor(TextColor);
    // LCD_DrawRect(Xpos, Ypos, Height, Width );
    // LCD_DrawRect(Xpos, Ypos, Width, Height );


    Width -= 2;
    Height-= 2;
    Xpos++;
    Ypos++;

    LCD_SetTextColor(BackColor);

    while(Height--)
        //while(Width--)

    {
        LCD_DrawLine(Xpos, Ypos++, Width, LCD_DIR_HORIZONTAL);
        //LCD_DrawLine(Xpos, Ypos++, Height, LCD_DIR_HORIZONTAL);

        //Height--;
    }

    LCD_SetTextColor(TextColor);


}


/**
  * @brief  Displays a full circle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Radius
  * @retval None
  */

//@PhuThinh modifed

void LCD_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
    int  D;    /* Decision Variable */
    uint32_t  CurX;/* Current X Value */
    uint32_t  CurY;/* Current Y Value */

    D = 3 - (Radius << 1);

    CurX = Radius;
    CurY = 0;

    LCD_SetTextColor(BackColor);

    while (CurY <= CurX)
    {
        if(CurX > 0)
        {
            LCD_DrawLine(Xpos - CurX, Ypos + CurY, 2*CurX, LCD_DIR_HORIZONTAL);
            LCD_DrawLine(Xpos - CurX, Ypos - CurY, 2*CurX, LCD_DIR_HORIZONTAL);
        }

        if(CurY > 0)
        {
            LCD_DrawLine(Xpos - CurY, Ypos + CurX, 2*CurY, LCD_DIR_HORIZONTAL);
            LCD_DrawLine(Xpos - CurY, Ypos - CurX, 2*CurY, LCD_DIR_HORIZONTAL);
        }
        if (D < 0)
        {
            D += (CurY << 2) + 6;
        }
        else
        {
            D += ((CurY - CurX) << 2) + 10;
            CurX--;
        }
        CurY++;
    }

    LCD_SetTextColor(TextColor);
    LCD_DrawCircle(Xpos, Ypos, Radius);
}

/*
uint16_t abs(uint16_t a, uint16_t b)
{
 if( a>= b)
     return (a-b);
 else
     return (b-a);
}
*/
/**
  * @brief  Displays an uni-line (between two points).
  * @param  x1: specifies the point 1 x position.
  * @param  y1: specifies the point 1 y position.
  * @param  x2: specifies the point 2 x position.
  * @param  y2: specifies the point 2 y position.
  * @retval None
  */
void LCD_DrawUniLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
            yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
            curpixel = 0;


    deltax = (x2 - x1);        /* The difference between the x's */
    deltay = (y2 - y1);        /* The difference between the y's */
    deltax = ABS(deltax);        /* The difference between the x's */
    deltay = ABS(deltay);        /* The difference between the y's */

//deltax = abs(x2,x1);
//deltay = abs(y2,y1);

    x = x1;                                 /* Start x off at the first pixel */
    y = y1;                               /* Start y off at the first pixel */

    if (x2 >= x1)                 /* The x-values are increasing */
    {
        xinc1 = 1;
        xinc2 = 1;
    }
    else                          /* The x-values are decreasing */
    {
        xinc1 = -1;
        xinc2 = -1;
    }

    if (y2 >= y1)                 /* The y-values are increasing */
    {
        yinc1 = 1;
        yinc2 = 1;
    }
    else                          /* The y-values are decreasing */
    {
        yinc1 = -1;
        yinc2 = -1;
    }

    if (deltax >= deltay)         /* There is at least one x-value for every y-value */
    {
        xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
        yinc2 = 0;                  /* Don't change the y for every iteration */
        den = deltax;
        num = deltax / 2;
        numadd = deltay;
        numpixels = deltax;         /* There are more x-values than y-values */
    }
    else                          /* There is at least one y-value for every x-value */
    {
        xinc2 = 0;                  /* Don't change the x for every iteration */
        yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
        den = deltay;
        num = deltay / 2;
        numadd = deltax;
        numpixels = deltay;         /* There are more y-values than x-values */
    }

    for (curpixel = 0; curpixel <= numpixels; curpixel++)
    {
        PutPixel(x, y);             /* Draw the current pixel */
        num += numadd;              /* Increase the numerator by the top of the fraction */
        if (num >= den)             /* Check if numerator >= denominator */
        {
            num -= den;               /* Calculate the new numerator value */
            x += xinc1;               /* Change the x as appropriate */
            y += yinc1;               /* Change the y as appropriate */
        }
        x += xinc2;                 /* Change the x as appropriate */
        y += yinc2;                 /* Change the y as appropriate */
    }
}

/**
  * @brief  Displays an poly-line (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_PolyLine(pPoint Points, uint16_t PointCount)
{
    int16_t X = 0, Y = 0;

    if(PointCount < 2)
    {
        return;
    }

    while(--PointCount)
    {
        X = Points->X;
        Y = Points->Y;
        Points++;
        LCD_DrawUniLine(X, Y, Points->X, Points->Y);
    }
}

/**
  * @brief  Displays an relative poly-line (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @param  Closed: specifies if the draw is closed or not.
  *           1: closed, 0 : not closed.
  * @retval None
  */
void LCD_PolyLineRelativeClosed(pPoint Points, uint16_t PointCount, uint16_t Closed)
{
    int16_t X = 0, Y = 0;
    pPoint First = Points;

    if(PointCount < 2)
    {
        return;
    }
    X = Points->X;
    Y = Points->Y;
    while(--PointCount)
    {
        Points++;
        LCD_DrawUniLine(X, Y, X + Points->X, Y + Points->Y);
        X = X + Points->X;
        Y = Y + Points->Y;
    }
    if(Closed)
    {
        LCD_DrawUniLine(First->X, First->Y, X, Y);
    }
}

/**
  * @brief  Displays a closed poly-line (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_ClosedPolyLine(pPoint Points, uint16_t PointCount)
{
    LCD_PolyLine(Points, PointCount);
    LCD_DrawUniLine(Points->X, Points->Y, (Points+PointCount-1)->X, (Points+PointCount-1)->Y);
}

/**
  * @brief  Displays a relative poly-line (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_PolyLineRelative(pPoint Points, uint16_t PointCount)
{
    LCD_PolyLineRelativeClosed(Points, PointCount, 0);
}

/**
  * @brief  Displays a closed relative poly-line (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_ClosedPolyLineRelative(pPoint Points, uint16_t PointCount)
{
    LCD_PolyLineRelativeClosed(Points, PointCount, 1);
}


/**
  * @brief  Displays a  full poly-line (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_FillPolyLine(pPoint Points, uint16_t PointCount)
{
    /*  public-domain code by Darel Rex Finley, 2007 */
    uint16_t  nodes = 0, nodeX[MAX_POLY_CORNERS], pixelX = 0, pixelY = 0, i = 0,
              j = 0, swap = 0;
    uint16_t  IMAGE_LEFT = 0, IMAGE_RIGHT = 0, IMAGE_TOP = 0, IMAGE_BOTTOM = 0;

    IMAGE_LEFT = IMAGE_RIGHT = Points->X;
    IMAGE_TOP= IMAGE_BOTTOM = Points->Y;

    for(i = 1; i < PointCount; i++)
    {
        pixelX = POLY_X(i);
        if(pixelX < IMAGE_LEFT)
        {
            IMAGE_LEFT = pixelX;
        }
        if(pixelX > IMAGE_RIGHT)
        {
            IMAGE_RIGHT = pixelX;
        }

        pixelY = POLY_Y(i);
        if(pixelY < IMAGE_TOP)
        {
            IMAGE_TOP = pixelY;
        }
        if(pixelY > IMAGE_BOTTOM)
        {
            IMAGE_BOTTOM = pixelY;
        }
    }

    LCD_SetTextColor(BackColor);

    /*  Loop through the rows of the image. */
    for (pixelY = IMAGE_TOP; pixelY < IMAGE_BOTTOM; pixelY++)
    {
        /* Build a list of nodes. */
        nodes = 0;
        j = PointCount-1;

        for (i = 0; i < PointCount; i++)
        {
            if (((POLY_Y(i)<(double) pixelY) && (POLY_Y(j)>=(double) pixelY)) || \
                    ((POLY_Y(j)<(double) pixelY) && (POLY_Y(i)>=(double) pixelY)))
            {
                nodeX[nodes++]=(int) (POLY_X(i)+((pixelY-POLY_Y(i))*(POLY_X(j)-POLY_X(i)))/(POLY_Y(j)-POLY_Y(i)));
            }
            j = i;
        }

        /* Sort the nodes, via a simple "Bubble" sort. */
        i = 0;
        while (i < nodes-1)
        {
            if (nodeX[i]>nodeX[i+1])
            {
                swap = nodeX[i];
                nodeX[i] = nodeX[i+1];
                nodeX[i+1] = swap;
                if(i)
                {
                    i--;
                }
            }
            else
            {
                i++;
            }
        }

        /*  Fill the pixels between node pairs. */
        for (i = 0; i < nodes; i+=2)
        {
            if(nodeX[i] >= IMAGE_RIGHT)
            {
                break;
            }
            if(nodeX[i+1] > IMAGE_LEFT)
            {
                if (nodeX[i] < IMAGE_LEFT)
                {
                    nodeX[i]=IMAGE_LEFT;
                }
                if(nodeX[i+1] > IMAGE_RIGHT)
                {
                    nodeX[i+1] = IMAGE_RIGHT;
                }
                LCD_SetTextColor(BackColor);
                LCD_DrawLine(pixelY, nodeX[i+1], nodeX[i+1] - nodeX[i], LCD_DIR_HORIZONTAL);
                LCD_SetTextColor(TextColor);
                PutPixel(pixelY, nodeX[i+1]);
                PutPixel(pixelY, nodeX[i]);
                /* for (j=nodeX[i]; j<nodeX[i+1]; j++) PutPixel(j,pixelY); */
            }
        }
    }

    /* draw the edges */
    LCD_SetTextColor(TextColor);
}

/**
  * @brief  Prepare to write to the LCD RAM.
  * @param  None
  * @retval None
  */
inline void LCD_WriteRAM_Prepare(void)
{
    *LCD_REG = HX8347_R22H;
}

/**
  * @brief  Writes to the LCD RAM.
  * @param  RGB_Code: the pixel color in RGB mode (5-6-5).
  * @retval None
  */
inline void LCD_WriteRAM(uint16_t RGB_Code)
{
    /* Write 16-bit GRAM Reg */
    *LCD_RAM = RGB_Code;
}

/**
  * E.Pataky, faster with 32bit
  * @brief  Writes to the LCD RAM.
  * @param  RGB_Code: the pixel color in RGB mode (5-6-5).
  * @retval None
  */
inline void LCD_WriteRAM2(uint32_t RGB_Codes)
{
    /* Write 16-bit GRAM Reg */
    *LCD_RAM_LONG = RGB_Codes;
}

/**
  * @brief  Reads the LCD RAM.
  * @param  None
  * @retval LCD RAM Value.
  */
inline uint16_t LCD_ReadRAM(void)
{
    /* Write 16-bit Index (then Read Reg) */
    *LCD_REG = LCD_REG_34; /* Select GRAM Reg */
    /* Read 16-bit Reg */
    return *(LCD_RAM_1);
}

/**
  * @brief  Power on the LCD.
  * @param  None
  * @retval None
  */
void LCD_PowerOn(void)
{
    /* Power On sequence ---------------------------------------------------------*/
    LCD_WriteReg(LCD_REG_16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
    LCD_WriteReg(LCD_REG_17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
    LCD_WriteReg(LCD_REG_18, 0x0000); /* VREG1OUT voltage */
    LCD_WriteReg(LCD_REG_19, 0x0000); /* VDV[4:0] for VCOM amplitude*/
    Delay_ms(200);                 /* Dis-charge capacitor power voltage (200ms) */
    LCD_WriteReg(LCD_REG_16, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
    LCD_WriteReg(LCD_REG_17, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */
    Delay_ms(50);                  /* Delay 50 ms */
    LCD_WriteReg(LCD_REG_18, 0x0139); /* VREG1OUT voltage */
    Delay_ms(50);                  /* Delay 50 ms */
    LCD_WriteReg(LCD_REG_19, 0x1d00); /* VDV[4:0] for VCOM amplitude */
    LCD_WriteReg(LCD_REG_41, 0x0013); /* VCM[4:0] for VCOMH */
    Delay_ms(50);                  /* Delay 50 ms */
    LCD_WriteReg(LCD_REG_7, 0x0173);  /* 262K color and display ON */
}

/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */
void LCD_DisplayOn(void)
{
    // Display ON Setting
    LCD_WriteReg(HX8347_R90H, 0x7F); // SAP=0111 1111
    LCD_WriteReg(HX8347_R26H, 0x04); // GON=0, DTE=0, D=01
    Delay_ms(100);
    LCD_WriteReg(HX8347_R26H, 0x24); // GON=1, DTE=0, D=01
    LCD_WriteReg(HX8347_R26H, 0x2C); // GON=1, DTE=0, D=11
    Delay_ms(100);
    LCD_WriteReg(HX8347_R26H, 0x3C); // GON=1, DTE=1, D=11
}

/**
  * @brief  Configures LCD Control lines (FSMC Pins) in alternate function mode.
  * @param  None
  * @retval None
  */
void LCD_CtrlLinesConfig(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);

    /* SRAM Data lines,  NOE and NWE configuration */

    /* SRAM Data lines configuration */
    /* E.Pataky modified for BLANVIEW - checked all good */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |
                                  GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                  GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);


    /* E.Pataky modified for BLANVIEW - checked all good */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
                                  GPIO_Pin_15;

    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_FSMC);


    /* NOE and NWE configuration */
    /* E.Pataky modified for BLANVIEW - checked all good */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource4, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource5, GPIO_AF_FSMC);

    /* E.Pataky RS line configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource3, GPIO_AF_FSMC);

    /* NE3 configuration */
    /* E.Pataky NE1 configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC);
}

/**
  * @brief  Configures the Parallel interface (FSMC) for LCD(Parallel mode)
  * @param  None
  * @retval None
  */
void LCD_FSMCConfig(void)
{
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  p;

    /* Enable FSMC clock */
    RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);

    /*-- FSMC Configuration ------------------------------------------------------*/
    p.FSMC_AddressSetupTime = 10;
    p.FSMC_AddressHoldTime = 10;
    p.FSMC_DataSetupTime = 9;
    p.FSMC_BusTurnAroundDuration = 0;
    p.FSMC_CLKDivision = 0;
    p.FSMC_DataLatency = 0;
    p.FSMC_AccessMode = FSMC_AccessMode_A;
    /* Color LCD configuration ------------------------------------
       LCD configured as follow:
          - Data/Address MUX = Disable
          - Memory Type = SRAM
          - Data Width = 16bit
          - Write Operation = Enable
          - Extended Mode = Enable
          - Asynchronous Wait = Disable */

    //FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM3;
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    //FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

    /* Enable FSMC NOR/SRAM Bank3 */
    //FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);

}

/**
  * @brief  Displays a pixel.
  * @param  x: pixel x.
  * @param  y: pixel y.
  * @retval None
  */
void PutPixel(int16_t x, int16_t y)
{
    if(x < 0 || x > 320 || y < 0 || y > 240)
    {
        return;
    }
    LCD_DrawLine(x, y, 1, LCD_DIR_HORIZONTAL);
}

#if 0
#ifndef USE_Delay
/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
static void delay(__IO uint32_t nCount)
{
    __IO uint32_t index = 0;
    for(index = (100000 * nCount); index != 0; index--)
    {
    }
}
#endif /* USE_Delay*/
#endif
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
