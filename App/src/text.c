
/****************************************************************/
// Author: PhuThinh
// Date: 2/25/14
// Desc: handle backrounds for lcd
/****************************************************************/
#ifndef TEST

/* Includes ------------------------------------------------------------------*/
#include "alldefs.h"


//#include "text.h"
//#include <stdlib.h>
//#include<stdio.h>
//#include "backgrounds.h"
//#include "flashmem.h"
//#include "fonts.h"

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t LenWord[100];
uint16_t SpaceLeft[100];
extern uint8_t in_buf[];
extern u8 AlarmCode;
extern const tImage TitleRedBar;
extern const tImage YellowTitleBar;
extern const tImage TitleBarGrey;
extern const tImage Image_Compass_Text_North;
extern const tImage Image_Compass_Text_West;
extern const tImage Image_Compass_Text_South;
extern const tImage Image_Compass_Text_East;
extern const tImage Image_Compass_Text_NorthWest;
extern const tImage Image_Compass_Text_NorthEast;
extern const tImage Image_Compass_Text_SouthWest;
extern const tImage Image_Compass_Text_SouthEast;
char compass_buf[5];
u16 preDISA=0;
u16 preCOUN=0;
u16 preREF=0;
u16 preREV=0;
u16 preRefPointX=0;
u16 preRefPointY=0;
u16 preRevPointX=0;
u16 preRevPointY=0;
extern u8 Log_Data[24][32];
float PO2Value[4];
extern const tImage Arrow_Grey;
extern const tImage Arrow_red;
extern const tImage Arrow_Yellow;
/*Define the data of Text */
char* _MainTitle[11] = {        "NORM",
                                "GAUGE",
                                "DECO",
                                "VIOLATION",
                                "SAFETY STOP",
                                "DEEP STOP",
                                "NORTH",
                                "REFERENCE",
                                "SET HEADING",
                                "SET REVERSE",
                                "REVERSE"
                       } ;

char* _BottomTitle[34] = {        "DO NOT SWITCH TO GAS 3, HIGH PO2",
                                  "PRESS (<) TO RETURN TO DIVE MENU",
                                  "(<) BACK TO MAIN MENU",//"PRESS (<) TO RETURN TO MAIN MENU",
                                  "(<) BACK TO MENU",//"PRESS (<) TO RETURN TO MENU",
                                  "(<) BACK TO SETUP MENU",//"PRESS (<) TO RETURN TO SETUP MENU",
                                  "(>) TO ACCESS - (<) BACK TO HOME MENU",//"PRESS (>) TO ACCESS CALIBRATION",
                                  "(>) TO ACCESS - (<) BACK TO MAIN",//"PRESS (>) TO ACCESS SET ALARMS MENU",
                                  "(>) TO ACCESS - (<) BACK TO MENU",//"PRESS (>) TO ACCESS SET GAS MENU",
                                  "(>) TO ACCESS - (<) BACK TO HOME MENU",//"PRESS (>) TO ACCESS SET MENU",
                                  "(>) TO ACCESS",//"PRESS (>) TO ACCESS SETUP",
                                  "(>) TO SET",//"PRESS (>) TO FLASH OPTION",
                                  "(>) TO SET",//"PRESS (>) TO FLASH VALUE, ALLOW SET",
                                  "(>) TO SET",//"PRESS (>) TO FLASH YEAR, ALLOW SET",
                                  "(>) TO SET",//"PRESS (>) TO FLASH, ALLOW SET",
                                  "(>) TO INITIALIZE",
                                  "(>) TO PREVIEW DEEP STOP",
                                  "PRESS (>) TO SAVE OPTION",
                                  "(>) TO ACCESS",//"PRESS (>) TO SHOW INFO",
                                  "(>) TO VIEW DATA",
                                  "(>) TO VIEW DATA",//"PRESS (>) TO VIEW DEPTHS, TIMES",
                                  "(>) TO VIEW LIST",
                                  "(>) TO VIEW LISTING, DATA",
                                  "(v) TO MENU - (>) TO COMPASS",
                                  "WAIT WHILE PROCESSING",
                                  "WILL REVERT TO MENU",
                                  "USE DIVERLOG APP",
                                  "(<) TO SURF MAIN - (v) TO REF",
                                  "(<) TO SURF MAIN - (v) TO NORTH",
                                  "(<) TO DIVE MAIN - (v) TO REF",
                                  "(<) TO DIVE MAIN - (v) TO NORTH",
                                  "ROTATE - KEEP LEVEL - (>) TO LOCK",
                                  "(<) TO DIVE MAIN - HEADING LOCKED",
                                  "(<) BACK TO SET MENU",
                                  "(>) TO ACCESS MAIN "
                         };
RowPreview _RowPreview[16] =
{   {"GAS 1 FO2, PO2" ,'\0','\0'},
    {"GAS 2 FO2, PO2" ,'\0','\0'},
    {"GAS 3 FO2, PO2" ,'\0','\0'},
    {"GAS 4 FO2, PO2" ,'\0','\0'},
    {"DEPTH AL" , 		'\0','\0'},
    {"EDT AL" , 		'\0','\0'},
    {"TLBG AL" , 		'\0','\0'},
    {"DTR ALARM" , 	'\0','\0'},
    {"TURN PRESS AL" ,	'\0','\0'},
    {"LOW PRESS AL" , 	'\0','\0'},
    {"WATER TYPE" , 	'\0','\0'},
    {"DEEP STOP" , 		'\0','\0'},
    {"SAFETY STOP" ,	'\0','\0'},
    {"ALGORITHM" ,		'\0','\0'},
    {"CONSERVATIVE" ,	'\0','\0'},
    {"SAMPLING RATE" ,	'\0','\0'}
};
RowPreview _RowSetPreview[18] =
{   {"GAS 1 FO2, PO2" ,'\0','\0'},
    {"GAS 2 FO2, PO2" ,'\0','\0'},
    {"GAS 3 FO2, PO2" ,'\0','\0'},
    {"GAS 4 FO2, PO2" ,'\0','\0'},
    {"DEPTH AL" , 		'\0','\0'},
    {"EDT AL" , 		'\0','\0'},
    {"TLBG AL" , 		'\0','\0'},
    {"DTR ALARM" , 	'\0','\0'},
    {"GO TO SCREEN 2" ,  '\0','\0'},
    {"TURN PRESS AL" ,	'\0','\0'},
    {"LOW PRESS AL" , 	'\0','\0'},
    {"WATER TYPE" , 	'\0','\0'},
    {"DEEP STOP" , 		'\0','\0'},
    {"SAFETY STOP" ,	'\0','\0'},
    {"ALGORITHM" ,		'\0','\0'},
    {"CONSERVATIVE" ,	'\0','\0'},
    {"SAMPLING RATE" ,	'\0','\0'},
    {"GO TO SCREEN 1" ,  '\0','\0'}
};

char *LeftText_[10];
char *RightText_[10];
tImage *CurrentChar;
u8 u8_BrightNess;
char Gas_buff[6];

/*update data*/
char time_buf[6];
char hr_buf[3];//Hour buffer
char min_buf[3];//Minute buffer
char deep_buf[6];
char pressure_buf[10];
//uint8_t SurfTime_buf[6];//
char SurfHr_buf[3];
char SurfMin_buf[3];
char _Temper_buf[6];
char battery_buf[6];
char divetime_buf[6];
char TotalAscentTime_buf[6];
char DiveNum_buf[3];//DIVE# = Dive number from 0 to 24 in BINARY.
char GTRnum_buf[6];
char SafetyDepth_buf[6];
char SafetyTimeMin_buf[3];
char SafetyTimeSec_buf[3];
char FO2num_buf[7];
char FO21_buf[7];
char FO22_buf[7];
char FO23_buf[7];
char FO24_buf[7];
char EDTnum_buf[6];
char DTRnum_buf[6];
char TLBGnum_buf[6];
char NDCnum_buf[6];
char PO2num_buf[6];
char O2num_buf[6];
char DepNum_buf[8];
char* DecoDepth_buf = "1";
//u8* SafetyDepth_buf;
char DecoTime_buf[6] ;
char totalDiveTime_buf[6];
char CountDown_Str[8];
char TurnString[10];
char EndString[10];
char EDT_TimeBuf[8];
PlanBuffer _PlanBuffer[17];//17 PLAN is maximum
char FLYtime_buf[13];//OPCODE 14H
char DESATtime_buf[13];//OPCODE 14H
char BrightNess_buf[9];
char Midday[6] ;
char TL_buf[6];
char AR_buf[6];
char RTM_buf[6];
//uint8_t u8_bat;
char divetime;
char ATRnum_;
extern const tImage RectangleAngle;

char *TextRight4;
char *TextRight4_0;
char *TextRight4_1;
char *TextRight4_2;
char *TextRight4_3;
char* SafetyStopDepth_Str;
char* SafetyStopTime_Str;
char *TextLeft3_0;
char *TextLeft3_1;
uint8_t TL_per ;//#define TLBG                                        ((u8)(in_buf[20]))//OPCODE = 10H.
uint8_t AR_per ;//#define ASCBG                                        ((u8)(in_buf[21]))//OPCODE = 10H.
enum {AM_, PM_};
uint8_t midnight; //0: AM ; 1: PM  '{' : '|'
uint8_t hh ;
uint8_t mm ;

/*Decode variables*/
u8 hrType ;     //BIT 0: 0 = 12 hour format, 1 = 24 hour format
u8 AudAlarm;    //BIT 1: 0 = Audible Alarm OFF, 1 = ON
//u8 MD;          //BIT 2: 0 = M.D format, 1 = D.M format
u8 UnitType_;   //BIT 3: 0 = Imperial/F. 1 = Metric/C.
u8 FO2default;  //BIT 4: 0 = 50% default OFF/ 1 = ON
u8 AutoDim; //AUTO DIM:  BIT 6: 0 =  OFF, 1 = ON

//History Data
char maxDivetime_buf[6];
char aveDivenum_buf[6];
char maxDepth_buf[6];
char aveDepth_buf[6]= {0,0,0,0,0,0};
char lowestTemp_buf[6];
char totalDive_buf[4];
char SampleRate_buf[8];
char Altitude_buf[5];
char DeepStop_buf[8];

//Time data
u8 Month;        //OPCODE = 20H. MENSTAT = 21H, 22H and 23H. Total is 15 bytes
u8 Day;
u8 Year;
char MD_buf[9];
char Month_buf[3];
char Day_buf[3];
char Year_buf[3];

//Serial number buffer define
char Serialnum_buf[12];
char BluetoothNum_buf[9];
u8 SN1;
u8 SN2;
u8 SN3;

//Reset code
u8 ReCoHigh ;
u8 ReCoLow ;
char Reset_buf_high[3];
char Reset_buf_low[3];

//Firmware Revision Code
u8 rev_1 ;
u8 rev_2 ;
char FirmRev_buf[10];

//Declination
char DeclineString[6];

//Image put to process circle
static const uint16_t PutImage_data[6] = {
    0x0009,0xffff
};
const tImage PutImage = { PutImage_data, 3, 3};

static const uint16_t ClearImage_data[2] = {
    0x0009,0x0000
};
const tImage ClearImage = { ClearImage_data, 3, 3};

//My information data
u8 MyInDa[10][16]; //MyInData[Row][Bytes number] --> 10 rows and 16 bytes in each row
u8 CC_byte = 0xff;
u8 _preTEMP;
u8 _premm=0;
u8 _prehh=0;
u8 preNPRV1 = 100;//Always innital diffirent from 0
u8 preMSG = 1;
uint8_t _premidnight=0;
u8 _DCMARK_BIT2=0;
u8 _DCMARK_BIT3=0;
extern const tImage TopCompassYellow ;
extern const tImage TopCompassGreen;
extern const uint16_t BMP_S1A_left_X0Y40[245][25];
extern const uint16_t BMP_S1A_right_X240Y40[245][25];
extern const uint16_t BMP_S1A_left_X0Y40[245][25];
extern const uint16_t BMP_S1A_right_X240Y40[245][25];
extern const tImage CompassBase;
extern const uint16_t BMP_Bat_Blue1_X150Y5[22][47];
extern const uint16_t BMP_Bat_Blue2_X150Y20[20][50];
extern const uint16_t BMP_Bat_Blue3_X148Y19[17][47] ;
extern const uint16_t BMP_Bat_Orange_X151Y24[17][47] ;
extern const uint16_t BMP_Bat_Red_X150Y23[18][48];
extern const tImage Image_MainMenu_TopTitle;
extern const tImage Image_HomeMenu_TopTitle;
extern const tImage Image_Battery;
extern uint16_t deep;
extern s8 count ;
extern u8 Fw_version;
extern float PO2_value;
extern char MyInfo_Data[10][16];
extern uint8_t PreFO2num;
extern float PO2num1;
extern float PO2num2;
extern float PO2num3;
extern float PO2num4;
extern u8 _preTLBG;
extern u8 _preBATT;
extern u8 _preASCBG;
extern u8 _preEARMARK;
extern u8 PreElevation;
u8 _preFO2;
float _prePO2;
float _prePO2Current;
u8 _preDVSTAT;
float _preDepth = 0;//D1A
float _preDECODepth = 0;//D1A
u16 _preNDC;
u16 _preRTM;
u8 _preMORFLG;
extern u16 _preEDT;
u8 _preSTDFLG;
extern u8 _preSSTIMEMin;
u8 _preSSTIMESec;
u8 _preGas_Num = 1;
u16 _preTank_Pressure;
u16 _preGTR_Time;
u16 _preSurf_Hour;
u16 _preSurf_Min;
u16 _preDEST;
extern u8 menulist;
extern u8 _preDiveNum;
extern u8 Gas_index;
extern float _preMaxDepth;
extern u8 _preDESD;
extern u16 PreEDT;
extern u8 PreAltitude;
extern u8 PreO2SAT;
extern u16 _preTAT;
extern u16 PreFLYTime;
extern u16 PreDESATTime;
extern float PrePO2_Num;
extern u8 AlarmCode;
extern u8 preAlarmCode;//Previous Alarm Code
extern u8 preMainMode;
extern Point compasspoint[360];
extern Point CirclePoint[360];
extern float PO2Setting1;
extern float PO2Setting2;
extern float PO2Setting3;
extern float PO2Setting4;
/* Private function prototypes -----------------------------------------------*/

/* extern variables ---------------------------------------------------------*/

extern const tChar myriad_bold_9[];
extern const tChar myriad_bold_11[];
extern const tChar myriad_bold_12[];
extern const tChar myriad_bold_14[];
extern const tChar myriad_bold_15[];
extern const tChar myriad_bold_16[];
extern const tChar myriad_bold_17[];
extern const tChar myriad_bold_22[];
extern const tChar myriad_bold_25[];
extern const tChar myriad_bold_30[];
extern const tChar myriad_norm_17[];
extern const tChar myriad_bold_38[];
extern const tChar myriad_bold_42[];
extern const tChar myriad_bold_50[];
extern const tChar myriad_bold_57[];
extern const tChar DinCondense_Bold_56[];
extern const tChar DinCondense_Bold_18[];
extern const tChar DinCondense_Bold_28[];
extern const tChar DinCondense_Bold_57[];
extern const tChar DinCondense_Bold_42[];
extern const tChar DinCondense_Bold_38[];
extern const tChar myriad_bold_19[];
extern unsigned char screenCod;
extern const tImage TopShapeCure;
ptChar FontSet ;
extern Point RefPoint[360];
extern const tImage RefPointImage;
extern const tImage RefPointClearImage;
extern uint8_t *sBuf;
extern uint16_t TextColor ;
extern uint16_t BackColor ;
extern u8 Plan_Data[17][8];
extern u8 Log_Data[24][32];
uint16_t HeightNow = 0;
u8 NPRV1_ = 0;
u16 len =0;


const tImage* getCharImage(uint16_t i)
{
    return FontSet[i].image;
}


void compass_text(u8 MS) {
    char* text;
    u8 _X1 = 20;
    u8 _X2 = 220;
    u16 _Y = 120;
    FontSet = (tChar*)myriad_bold_16;
    LCD_SetColors(White, Black);
    switch (MS) {
    case 0x00:
        LCD_Clear(Black);
        text = "HARDWARE INITIALIZATION";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x01:
        LCD_Clear(Black);
        text = "HARDWARE INITIALIZATION";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x02:
        LCD_Clear(Black);
        text = "LEVEL 180 THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x03:
        LCD_Clear(Black);
        text = "LEVEL 180 THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x04:
        LCD_Clear(Black);
        text = "LEVEL 0 THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x05:
        LCD_Clear(Black);
        text = "LEVEL 0 THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x06:
        LCD_Clear(Black);
        text = "BOTTOM UP THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x07:
        LCD_Clear(Black);
        text = "BOTTOM UP THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x08:
        LCD_Clear(Black);
        text = "TOP UP THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x09:
        LCD_Clear(Black);
        text = "TOP UP THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x0A:
        LCD_Clear(Black);
        text = "RIGHT UP THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x0B:
        LCD_Clear(Black);
        text = "RIGHT UP THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x0C:
        LCD_Clear(Black);
        text = "LEFT UP THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x0D:
        LCD_Clear(Black);
        text = "LEFT UP THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x0E:
        LCD_Clear(Black);
        text = "FACE DOWN THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x0F:
        LCD_Clear(Black);
        text = "FACE DOWN THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x1B:
        LCD_Clear(Black);
        text = "HARDWARE INITIALIZATION FAILED";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;


    /*second part*/
    case 0x13:
        if(screenCod != H12E) {
            screenCod = H12E;
            Draw_H38B();
            Text_H12E();
        }
        // else {
        //while(Round_Compass <= 360 && MENSTAT == 0x13) {
        //Draw_Circle(Round_Compass, &PutImage);
        //}
        //}
        break;

    case 0x14:
        Draw_H38B();
        Text_H12F();
        break;

    case 0x17:
        if(CC_byte!=in_buf[5]) {
            Draw_H38B();
            CC_byte = in_buf[5];
        }
        if(CC_byte == 0x00) {
            Text_H12B();
        }
        else if(CC_byte == 0x01) {
            Text_H12C();
        }
        break;

    case 0x18:
        Draw_H38B();
        Text_H12D();
        break;

    case 0x1A:
        Draw_H38B();
        Text_H12G();
        break;
    }
}

/**
  * @brief  Draws a character on LCD.
  * @param  Xpos: the Line where to display the character shape.
  * @param  Ypos: start column address.
  * @param  c: pointer to the character data.
  * @retval None
  */
/*
inline void LCD_DrawCharBACKUP(uint16_t Xpos, uint16_t Ypos)
{

uint16_t ScanX;
uint16_t ScanY;
uint16_t offset_ch = 0;
uint16_t f_data = 0;
uint16_t numpage = CurrentChar->num;
LCD_SetCursor(Xpos, Ypos);//Set the cursor to the postion
for(ScanY = Ypos; ScanY < (CurrentChar->height + Ypos); ScanY ++)//Scan the height of character
{
   for (ScanX = Xpos; ScanX < (CurrentChar->width + Xpos); ScanX ++)//Scan the width of character
   {
       f_data =  sFLASH_readpixel(numpage, offset_ch);
       if(offset_ch < 127)
       {
           offset_ch ++;
       }
       else
       {
           offset_ch = 0;
           numpage ++;
       }
       LCD_SetCursor(ScanX, ScanY);
       LCD_WriteRAM_Prepare();
       if (f_data != White) { //If found the White color pass by
           LCD_WriteRAM((f_data == Black) ? TextColor : (ImplementColor(f_data)));
       }

   }

}

}
*/
/*----------------------------------------------------------
-Function:Implement Color text
-Date:
-Version:
-Change:
-Author: ducthinh90@hotmail.com
-Description:
-Input:
-Output:
-Return:
------------------------------------------------------------*/
/*
inline uint16_t ImplementColor(uint16_t PixelColor)
{
    uint16_t Color;
    uint16_t redPart;
    uint16_t greenPart;
    uint16_t bluePart;
    uint16_t redPart2;
    uint16_t greenPart2;
    uint16_t bluePart2;

    if(TextColor == Black)
    {
        // get color components of pixelColor
        redPart = (PixelColor >> 11) & 0x001f ;
        greenPart = (PixelColor  >> 5) & 0x003f ;
        bluePart = (PixelColor  & 0x001f) ;

        // convert the percentage of white used to percentage of backgroundColor used
        redPart = (redPart) * (0x001F - 6) / 0x001F;
        redPart = (0x001F - redPart);
        greenPart = (greenPart) * (0x003F - 10) / 0x003F;
        greenPart = (0x003F - greenPart);
        bluePart = (bluePart) * (0x001F - 8) / 0x001F;
        bluePart = (0x001F - bluePart);

        // now assemble and display
        Color= ((redPart << 11) | (greenPart << 5) |bluePart);
        return ~Color;
        // return PixelColor;
    }

    else if (TextColor == White)
    {
        // get color components of pixelColor
        redPart = (PixelColor >> 11) & 0x001f ;
        greenPart = (PixelColor  >> 5) & 0x003f ;
        bluePart = (PixelColor  & 0x001f) ;
        // get color components of backgroundColor
        redPart2 = (BackColor>> 11) & 0x001f ;
        greenPart2 = (BackColor >> 5) & 0x003f ;
        bluePart2 = ((BackColor) & 0x001f) ;

        // convert the percentage of white used to percentage of backgroundColor used
        redPart = (redPart) * (0x001F - redPart2) / 0x001F;
        redPart = (0x001F - redPart);
        greenPart = (greenPart) * (0x003F - greenPart2) / 0x003F;
        greenPart = (0x003F - greenPart);
        bluePart = (bluePart) * (0x001F - bluePart2) / 0x001F;
        bluePart = (0x001F - bluePart);

        // now assemble and display
        Color= ((redPart << 11) | (greenPart << 5) |bluePart);
        return Color;
    }

    else if(TextColor == Red)
    {
        PixelColor = PixelColor | 0xF800;
        return PixelColor;
    }
    else if(Green==TextColor)
    {
        return PixelColor;
    }
    else
    {
        // get color components of pixelColor
        redPart = ((~PixelColor) >> 11) & 0x001f ;
        greenPart = ((~PixelColor)  >> 5) & 0x003f ;
        bluePart = ((~PixelColor)  & 0x001f) ;
        // get color components of backgroundColor
        redPart2 = ((~BackColor)>> 11) & 0x001f ;
        greenPart2 = ((~BackColor) >> 5) & 0x003f ;
        bluePart2 = ((~BackColor) & 0x001f) ;

        // convert the percentage of white used to percentage of backgroundColor used
        redPart = (redPart) * (0x001F - redPart2) / 0x001F;
        redPart = (0x001F - redPart);
        greenPart = (greenPart) * (0x003F - greenPart2) / 0x003F;
        greenPart = (0x003F - greenPart);
        bluePart = (bluePart) * (0x001F - bluePart2) / 0x001F;
        bluePart = (0x001F - bluePart);

        // now assemble and display
        Color= ((redPart << 11) | (greenPart << 5) |bluePart);
        return Color;
    }
}

    */

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
        PixelColor=260-PixelColor;
        //Assembly the value Red Green Blue
        switch(TextColor) {
        case LCD_COLOR_WHITE:
            PixelColor=ASSEMBLE_RGB(PixelColor, PixelColor, PixelColor);
            break;
        case LCD_COLOR_RED:
            PixelColor=ASSEMBLE_RGB(PixelColor, 0, 0);
            break;
        case LCD_COLOR_GREEN:
            PixelColor=ASSEMBLE_RGB(0, PixelColor, 0);
            break;
        case LCD_COLOR_BLUE:
        case 0x07FF:
            PixelColor=ASSEMBLE_RGB(0, 0, PixelColor);
            break;
        case LCD_COLOR_YELLOW:
            PixelColor=ASSEMBLE_RGB(PixelColor, PixelColor, 0);
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
        }
    }
    //Whith Yellow background
    else if(LCD_COLOR_YELLOW==BackColor) {
        //Get each value of Black foreground and White background
        PixelColor=(PixelColor&0x07E0)>>3;
        //Assembly the value Red Green Blue
        switch(TextColor) {
        case LCD_COLOR_BLACK:
            PixelColor=ASSEMBLE_RGB(PixelColor, PixelColor, 0);
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
            //Reverse the value to Black background
            PixelColor=285-PixelColor;
            PixelColor=ASSEMBLE_RGB(PixelColor,120 , 120);
            break;
        case Black:
            return 0x2945;
            break;
        }
    }
    else if(Blue==BackColor) {
        switch(TextColor) {
        case White:
            //Get each value of Black foreground and White background
            PixelColor=(PixelColor&0x07E0)>>3;
            //Reverse the value to Black background
            PixelColor=285-PixelColor;
            PixelColor = ASSEMBLE_RGB(PixelColor, PixelColor, 160 );
            break;
        }
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
        /* Point to next character */
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
char text[22];
void WriteLeftText_AlignRight (void) { //Write text on left with bold text select
    uint8_t i = 0;
    u8 DayNum = 0;
    u8 MonthNum = 0;
    u8 YearNum = 0;
    len = 0;
    for (i = 0; i <= (EndRecord - StartRecord); i++)    {
        MonthNum = Bcd2ToByte(Log_Data[StartRecord+i][1]);
        if(MonthNum < 10) {//Add the 0 character when the value of Month smaller than 2 digits
            text[len++] = '0';
        }
        len += Num2Str((u16) MonthNum, text + len, 5);//Month
        text[len++] = '/';
        DayNum = Bcd2ToByte(Log_Data[StartRecord+i][2]);
        if(DayNum < 10) {
            text[len++] = '0';
        }
        len += Num2Str((u16) DayNum, text + len, 5);//Day
        text[len++] = '/';
        YearNum = Bcd2ToByte(Log_Data[StartRecord+i][3]);
        if(YearNum < 10) {
            text[len++] = '0';
        }
        len += Num2Str((u16) YearNum, text + len, 5);//Year
        text[len++] = ' ';
        text[len++] = ' ';
        text[len++] = ' ';
        text[len++] = ' ';
        text[len++] = '#';
        len += Num2Str((u16) Log_Data[StartRecord+i][0], text + len, 5);//Dive number 1-24
        if(Log_Data[StartRecord+i][0]<10) { //Need space to display correctly
            text[len++] = ' ';
            text[len++] = ' ';
        }
        text[len++] = ' ';
        text[len++] = ' ';
        text[len++] = ' ';
        if(Log_Data[StartRecord+i][16]<10) { //Need space to display correctly
            text[len++] = ' ';
        }
        len += Num2Str((u16) Log_Data[StartRecord+i][16], text + len, 5);//Current dive number
        text[len] = '\0';
        FontSet=(tChar*)myriad_bold_16;
        if (i == LogHighLight) {
            LCD_SetColors(Black, Green);
        }
        else {
            LCD_SetColors(White, Black);
        }
        LCD_DisplayStringLine(3, 109+(i*22), text);
        len = 0;//Reset len
    }
}
void Text_H1A(void) {
    char *text;
    WriteText_Title_1();//Top

    text = "HOME MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "MY INFO";
    LeftText_[1] = "PROPLUS X INFO";
    LeftText_[2] = "SETUP MENU";
    LeftText_[3] = "LOG";
    LeftText_[4] = "HISTORY";
    LeftText_[5] = "NORM MODE";
    LeftText_[6] = "GAUGE MODE";
    WriteLeftText(7,0);//Left
    text = "PERSONAL DATA ENTERED USING DIVERLOG APP";
    WriteText_Right_1(text,Black);//Right
    DisplayBottomTitle(_BottomTitle[17]);//Bottom
}

void Text_H2A(void) {
    char *text;
    PrepareClock(time_buf,1);
    PrepareTemper();
    PrepareBattery();
    PrepareMidday(midnight);
    WriteText_Title_1();//Top
    DisplayMainMenu("HOME MENU", White);//Below
    LeftText_[0] = "MY INFO";
    LeftText_[1] = "PROPLUS X INFO";
    LeftText_[2] = "SETUP MENU";
    LeftText_[3] = "LOG";
    LeftText_[4] = "HISTORY";
    LeftText_[5] = "NORM MODE";
    LeftText_[6] = "GAUGE MODE";
    WriteLeftText(7,1);//Left
    text = "ENTERED ~~~~BY~~~~ FACTORY ~~~OR~~~ UPDATES USING DIVERLOG APP";
    WriteText_Right_1(text,Black);//Right
    DisplayBottomTitle(_BottomTitle[17]);//Bottom
}

void Text_H2B(void) {
    char *text;

    text = "PROPLUS X";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "INFORMATION";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "MY INFO";
    LeftText_[1] = "PROPLUS X INFO";
    LeftText_[2] = "SETUP MENU";
    LeftText_[3] = "LOG";
    LeftText_[4] = "HISTORY";
    LeftText_[5] = "NORM MODE";
    LeftText_[6] = "GAUGE MODE";
    WriteLeftText(7,1);//Left

    ProcessFirmwareRev();
    WriteText_Right_2();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}
void Text_H3A(void) {
    char *text;
    text = "CLEAR";
    WriteText_Title_2(text,1,Black,White);// Top

    FontSet = (ptChar)myriad_bold_22;
    LCD_SetColors(Red, Grey);
    LCD_DisplayStringLine_Center(0,240,38, "ARE YOU SURE [");

    WriteText_Left_2();//Left

    ProcessResetCode();
    WriteText_Right_3();//Right

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE, NEXT";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_H1B(void) {
    char *text;
    text = "PERSONAL";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "INFORMATION";
    DisplayMainMenu(text, White);//Below
    WriteText_Right_0();
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_H4A(void) {
    char *text;
    PrepareClock(time_buf,1);
    PrepareTemper();
    PrepareBattery();
    PrepareMidday(1);
    WriteText_Title_1();                    //Top

    DisplayMainMenu("HOME MENU", White);//Below

    LeftText_[0] = "MY INFO";
    LeftText_[1] = "PROPLUS X INFO";
    LeftText_[2] = "SETUP MENU";
    LeftText_[3] = "LOG";
    LeftText_[4] = "HISTORY";
    LeftText_[5] = "NORM MODE";
    LeftText_[6] = "GAUGE MODE";
    WriteLeftText(7,2);                    //Left

    text ="SELECT TO ACCESS SETTINGS FOR GENERAL FUNCTIONS";
    LCD_DisplayText(145, 240,105, (ptChar)myriad_bold_15, Black, White, AlignCenter, text);

    DisplayBottomTitle(_BottomTitle[9]);//Bottom
}
void Text_H5A(void) { //not yet
    char *text;
    text = "HOME";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SETUP MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "BLUETOOTH";
    LeftText_[2] = "SET DATE, TIME";
    LeftText_[3] = "CAL COMPASS";
    LeftText_[4] = "SET DECLINATION";
    WriteLeftText(5,0);//Left

    ProcessAutoDimBright();
    WriteText_Right_6(BrightNess_buf);

    text = "SELECT TO ~~ADJUST~~ BY % ~~~OR~~~ AUTO DIM";
    WriteText_Right_7(text);
    DisplayBottomTitle(_BottomTitle[11]);//Bottom
}
void Text_H5B(void) {
    char* text;
    text = "ADJUST";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "BRIGHTNESS";
    DisplayMainMenu(text, White);//Below
    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "BLUETOOTH";
    LeftText_[2] = "SET DATE, TIME";
    LeftText_[3] = "CAL COMPASS";
    LeftText_[4] = "SET DECLINATION";
    WriteLeftText(5,0);//Left
    ProcessAutoDimBright();
    WriteText_Right_6(BrightNess_buf);//Right
    TextRight4    = "VALUE";
    TextRight4_0  = "^ - INCREASE";
    TextRight4_1  = "v - DECREASE";
    TextRight4_2  = "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_H6A(void) {
    char* text;
    text = "HOME";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SETUP MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "BLUETOOTH";
    LeftText_[2] = "SET DATE, TIME";
    LeftText_[3] = "CAL COMPASS";
    LeftText_[4] = "SET DECLINATION";
    WriteLeftText(5,1);//Left

    text = "SELECT ~~~TO~~~ ENABLE CONNECTION";
    WriteText_Right_5(text, Black, White);//Right
    DisplayBottomTitle(_BottomTitle[14]);//Bottom
}

void Text_H6B(void) {
    char *text;
    text = "INITIALIZE";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "BLUETOOTH";
    DisplayMainMenu(text, White);//Below
    TextLeft3_0 = "~~PLEASE~~ WAIT...";
    TextLeft3_1 = "~~ABOUT~~ 5 SEC...";
    WriteText_Left_3(106);
    DisplayBottomTitle(_BottomTitle[23]);//Bottom
}
void Text_H6C(void) {
    char* text;
    text = "INITIALIZE";
    WriteText_Title_2(text, 0,Black,White);//Top
    text = "BLUETOOTH";
    DisplayMainMenu(text, White);//Below
    WriteText_Left_11();//Left
    DisplayBottomTitle(_BottomTitle[23]);//Bottom
}
void Text_H6D(void) {
    char* text;
    text = "INITIALIZE";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "BLUETOOTH";
    DisplayMainMenu(text, White);//Below
    TextLeft3_0 = "FAILED";
    TextLeft3_1 = "~~~WAIT~~~ WHILE BLUETOOTH DEACTIVATES";
    WriteText_Left_10(106);//Left
    DisplayBottomTitle(_BottomTitle[24]);//Bottom
}
void Text_H6E(void) {
    char *text;
    text = "CONNECTED";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "BLUETOOTH";
    DisplayMainMenu(text, White);//Below
    TextLeft3_0 = "CONNECTION MADE";
    WriteText_Left_4();//Left
    DisplayBottomTitle(_BottomTitle[25]);//Bottom
}
void Text_H6F(void) {
    char *text;
    text = "CONNECTED";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "BLUETOOTH";
    DisplayMainMenu(text, White);//Below
    TextLeft3_0 = "DATA DOWNLOAD ~~~IN~~~ PROGRESS";
    WriteText_Left_4();//Left
    DisplayBottomTitle(_BottomTitle[23]);//Bottom
}

void Text_H6G(void) {
    char *text;
    text = "CONNECTED";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "BLUETOOTH";
    DisplayMainMenu(text, White);//Below
    TextLeft3_0 = "DATA ~UPLOAD~ ~~~IN~~~ PROGRESS";
    WriteText_Left_4();//Left
    DisplayBottomTitle(_BottomTitle[23]);//Bottom
}

void Text_H6H(void) {
    char *text;
    text = "CONNECTED";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "BLUETOOTH";
    DisplayMainMenu(text, White);//Below
    TextLeft3_0 = "UPDATING PPX FIRMWARE WAIT FOR PC/MAC MESSAGE";
    WriteText_Left_4();//Left
    DisplayBottomTitle(_BottomTitle[23]);//Bottom
}
void Text_H7A(void) {
    char *text;
    text = "HOME";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "SETUP MENU";
    DisplayMainMenu(text, White);//Below
    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "BLUETOOTH";
    LeftText_[2] = "SET DATE, TIME";
    LeftText_[3] = "CAL COMPASS";
    LeftText_[4] = "SET DECLINATION";
    WriteLeftText(5,2);//Left
    text = "SELECT TO ACCESS - ~~~~~~~~~~ SETTINGS APPLY TO ALL MODES";
    WriteText_Right_5(text, Black, White);//Right
    DisplayBottomTitle(_BottomTitle[8]);//Bottom
}
void Text_H8A(void) {
    char *text;
    text = "DATE, TIME";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "SET MENU";
    DisplayMainMenu(text, White);//Below
    LeftText_[0] = "DATE FORMAT";
    LeftText_[1] = "DATE";
    LeftText_[2] = "TIME FORMAT";
    LeftText_[3] = "TIME";
    WriteLeftText(4,0);//Left
    WriteText_Right_6(DM_String);
    text = "SELECT ~~~TO~~~ ACCESS";
    WriteText_Right_7(text);
    DisplayBottomTitle(_BottomTitle[4]);//Bottom
}

void Text_H8B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "DATE FORMAT";
    DisplayMainMenu(text, White);//Below
    LeftText_[0] = "DATE FORMAT";
    LeftText_[1] = "DATE";
    LeftText_[2] = "TIME FORMAT";
    LeftText_[3] = "TIME";
    WriteLeftText(4,0);//Left
    WriteText_Right_6(DM_String);
    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[32]);//Bottom
}

void Text_H9A(void) {
    char *text;
    text = "DATE, TIME";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "SET MENU";
    DisplayMainMenu(text, White);//Below
    LeftText_[0] = "DATE FORMAT";
    LeftText_[1] = "DATE";
    LeftText_[2] = "TIME FORMAT";
    LeftText_[3] = "TIME";
    WriteLeftText(4,1);//Left
    Process_DMY_data_1();
    WriteText_Right_9();
    text = "SELECT ~~~TO~~~ ACCESS";
    WriteText_Right_7(text);
    DisplayBottomTitle(_BottomTitle[12]);//Bottom
}

void Text_H9B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "DATE";
    DisplayMainMenu(text, White);//Below
    LeftText_[0] = "DATE FORMAT";
    LeftText_[1] = "DATE";
    LeftText_[2] = "TIME FORMAT";
    LeftText_[3] = "TIME";
    WriteLeftText(4,1);//Left

    Process_DMY_data_1();
    WriteText_Right_9();

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_H10A(void) {
    char *text;
    text = "DATE, TIME";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "SET MENU";
    DisplayMainMenu(text, White);//Below
    LeftText_[0] = "DATE FORMAT";
    LeftText_[1] = "DATE";
    LeftText_[2] = "TIME FORMAT";
    LeftText_[3] = "TIME";
    WriteLeftText(4,2);//Left
    TextRight4 = hr_type_2(hrType);
    TextRight4_0 = hr_type_1(hrType);
    WriteText_Right_8();
    text = "SELECT ~~~TO~~~ ACCESS";
    WriteText_Right_7(text);
    DisplayBottomTitle(_BottomTitle[11]);//Bottom
}

void Text_H10B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "TIME FORMAT";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "DATE FORMAT";
    LeftText_[1] = "DATE";
    LeftText_[2] = "TIME FORMAT";
    LeftText_[3] = "TIME";
    WriteLeftText(4,2);//Left

    TextRight4 = hr_type_2(hrType);
    TextRight4_0 = hr_type_1(hrType);
    WriteText_Right_8();

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}
void Text_H11A(void) {
    char *text;
    text = "DATE, TIME";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "DATE FORMAT";
    LeftText_[1] = "DATE";
    LeftText_[2] = "TIME FORMAT";
    LeftText_[3] = "TIME";
    WriteLeftText(4,3);//Left
    text = "SELECT ~~~TO~~~ ACCESS";
    WriteText_Right_7(text);//Right
    PrepareClock(time_buf,1);//xxx
    WriteText_Right_18();//Right below
    DisplayBottomTitle(_BottomTitle[11]);//Bottom
}

void Text_H11B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "TIME OF DAY";
    DisplayMainMenu(text, White);//Below
    LeftText_[0] = "DATE FORMAT";
    LeftText_[1] = "DATE";
    LeftText_[2] = "TIME FORMAT";
    LeftText_[3] = "TIME";
    WriteLeftText(4,3);//Left
    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    TextRight4_2 = "hr:min";
    WriteText_Right_10();//Right
    PrepareClock(time_buf,1);//xxx
    WriteText_Right_18();//Right below
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}
void Text_H12A(void) {
    char *text;
    text = "HOME";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SETUP MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "BLUETOOTH";
    LeftText_[2] = "SET DATE, TIME";
    LeftText_[3] = "CAL COMPASS";
    LeftText_[4] = "SET DECLINATION";

    WriteLeftText(5,3);//Left

    text = "CALIBRATE PRIOR TO FIRST USE AND AFTER BATTERY CHANGE.";
    WriteText_Right_5(text, Black, White);//Right
    DisplayBottomTitle(_BottomTitle[5]);//Bottom
}
void Text_H12B(void) {
    char *text;
    text = "CALIBRATE";
    WriteText_Title_2(text,1,Black,White);//Tops
    text = "COMPASS";
    DisplayMainMenu(text, White);//Below
    FontSet = (ptChar)myriad_bold_22;
    LCD_SetColors(White, Black);
    LCD_DisplayStringLine_Center(58, 190, 107, "~~~TURN~~~ FACE DOWN UNTIL BEEP, THEN TURN FACE UP");
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}
void Text_H12C(void) {
    char *text;
    text = "CALIBRATE";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "COMPASS";
    DisplayMainMenu(text, White);//Below
    FontSet = (ptChar)myriad_bold_22;
    LCD_SetColors(White, Black);
    LCD_DisplayStringLine_Center(45, 195, 112, "~~~TURN~~~ FACE UP UNTIL BEEP, THEN ROTATE");
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_H12D(void) {
    char *text;
    text = "CALIBRATE";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "COMPASS";
    DisplayMainMenu(text, White);//Below

    FontSet = (ptChar)myriad_bold_22;
    LCD_SetColors(White, Black);
    LCD_DisplayStringLine_Center(58, 190, 123, "ROTATE ~~360*~~ KEEP LEVEL");
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}
void Text_H12E(void) {
    char *text;
    text = "CALIBRATE";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "COMPASS";
    DisplayMainMenu(text, White);//Below
    FontSet = (ptChar)myriad_bold_22;
    LCD_SetColors(White, Black);
    LCD_DisplayStringLine_Center(0, 240, 160, "PROGRESS");
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}
void Text_H12F(void) {
    char *text;
    text = "CALIBRATE";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "COMPASS";
    DisplayMainMenu(text, White);//Below

    FontSet = (ptChar)myriad_bold_22;
    LCD_SetColors(Green, Black);
    LCD_DisplayStringLine_Center(58, 190, 125, "READY PASSED CALIBRATION");
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}
void Text_H12G(void) {
    char *text;
    text = "CALIBRATE";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "COMPASS";
    DisplayMainMenu(text, White);//Below
    FontSet = (ptChar)myriad_bold_22;
    LCD_SetColors(Red, Black);
    LCD_DisplayStringLine_Center(58, 190, 125, "FAILED CALIBRATE AGAIN");
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}
void Text_H12H(void) {
    char *text;
    text = "RESIDUAL";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "NI - O2 DATA";
    DisplayMainMenu(text, White);//Below
    text = "DATA SAVED";
    WriteText_Right_6(text);
    TextLeft3_0 ="AFTER THE BATTERY IS CHANGED, NI - O2 DATA WILL BE~ SAVED AND~ OPERATION WILL MOVE TO THE COMPASS CAL~~ FACE DOWN SCREEN.";
    WriteText_Left_5();
    DisplayBottomTitle(_BottomTitle[10]);//Bottom
}

void Text_H13A(void) {
    char *text;
    text = "HOME";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "SETUP MENU";
    DisplayMainMenu(text, White);//Below
    DeclineProcess;
    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "BLUETOOTH";
    LeftText_[2] = "SET DATE, TIME";
    LeftText_[3] = "CAL COMPASS";
    LeftText_[4] = "SET DECLINATION";
    WriteLeftText(5,4);//Left
    text = "SELECT TO ACCESS - ~~~~~~~~  IN A NEW GLOBAL REGION";
    WriteText_Right_7(text);//Right
    DisplayBottomTitle(_BottomTitle[13]);//Bottom
}
void Text_H13B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "DECLINATION";
    DisplayMainMenu(text, White);//Below

    DeclineProcess;

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "BLUETOOTH";
    LeftText_[2] = "SET DATE, TIME";
    LeftText_[3] = "CAL COMPASS";
    LeftText_[4] = "SET DECLINATION";
    WriteLeftText(5,4);//Left

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}
void Text_H14A(void) {
    char* text;
    PrepareClock(time_buf,1);
    PrepareTemper();
    PrepareBattery();
    PrepareMidday(1);
    WriteText_Title_1();                    //Top

    DisplayMainMenu("HOME MENU", White);//Below

    LeftText_[0] = "MY INFO";
    LeftText_[1] = "PROPLUS X INFO";
    LeftText_[2] = "SETUP MENU";
    LeftText_[3] = "LOG";
    LeftText_[4] = "HISTORY";
    LeftText_[5] = "NORM MODE";
    LeftText_[6] = "GAUGE MODE";
    WriteLeftText(7,3);                    //Left

    if((MSG&0x0F) == 0) {
        text = "~~NO~~ ~~DIVES~~ RECORDED YET.";
        WriteText_Right_5(text, Black, White);//Right
    }
    else {
        text = "~~MOST~~ ~~RECENT~~ DIVE TO OLDEST RECORDED.";
        WriteText_Right_1(text, Black);//Right
        DisplayBottomTitle(_BottomTitle[21]);//Bottom
    }
}

void Text_S1A(void) {
    WriteText_Middle_0();//Middle
    DisplayPSIvsGTR();
    DisplayTextMiddle_2(GAS_Str());//Middle
    DisplayBottomTitle(_BottomTitle[22]);//Bottom
}

inline u8 ListReturn(void) { //NormAndGaugeMainMenu_ListNumReturn
    if((in_buf[5] & BIT_5) == BIT_5) {
        return 3;//Just display 3 first items in list BRIGHTNESS + LAST DIVE DATA + MORE DATA
    }
    else {
        //if(IsNormMode==0) {
        if((in_buf[5]&BIT_0)!=BIT_0) {
            return 9;//Full list display
        }
        else {
            return 6;
        }
    }
}
void Text_S2A(void) {
    char *text;
    WriteText_Title_2(_MainTitle[0],1,Black,White);//Top

    text = "MAIN MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "LAST DIVE DATA";
    LeftText_[2] = "MORE DATA";
    LeftText_[3] = "PLAN";
    LeftText_[4] = "SET GAS";
    LeftText_[5] = "SET ALARMS";
    LeftText_[6] = "SET UTILITIES";
    LeftText_[7] = "SET PREVIEW";
    LeftText_[8] = "VIEW PREVIEW";
    WriteLeftText(ListReturn(),0); //Left

    ProcessAutoDimBright();
    WriteText_Right_6(BrightNess_buf);//Right

    text = "SELECT TO ~~ADJUST~~ BY % ~~~OR~~~ AUTO DIM";
    WriteText_Right_7(text);//Right
    DisplayBottomTitle(_BottomTitle[11]);//Bottom
}

void Text_S2B(void) {
    char *text;
    text = "ADJUST";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "BRIGHTNESS";
    DisplayMainMenu(text, White);//Below
    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "LAST DIVE DATA";
    LeftText_[2] = "MORE DATA";
    LeftText_[3] = "PLAN";
    LeftText_[4] = "SET GAS";
    LeftText_[5] = "SET ALARMS";
    LeftText_[6] = "SET UTILITIES";
    LeftText_[7] = "SET PREVIEW";
    LeftText_[8] = "VIEW PREVIEW";
    WriteLeftText(ListReturn(),0); //Left
    ProcessAutoDimBright();
    WriteText_Right_6(BrightNess_buf);//Right
    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}
void Text_S3A(void) {
    char* text;
    WriteText_Title_2(_MainTitle[0],1,Black,White);//Top

    text = "MAIN MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "LAST DIVE DATA";
    LeftText_[2] = "MORE DATA";
    LeftText_[3] = "PLAN";
    LeftText_[4] = "SET GAS";
    LeftText_[5] = "SET ALARMS";
    LeftText_[6] = "SET UTILITIES";
    LeftText_[7] = "SET PREVIEW";
    LeftText_[8] = "VIEW PREVIEW";
    WriteLeftText(ListReturn(),1); //Left
    text = "ACCESS ~~~FOR~~~ ~~LATEST~~ DIVE DATA";
    WriteText_Right_1(text, Black);//Right
    DisplayBottomTitle(_BottomTitle[18]);//Bottom
}

void Text_S3B(void) {
    char *text;
    WriteText_Title_2(_MainTitle[0],1,Black,White);//Top

    text = "LAST DIVE DATA";
    DisplayMainMenu(text, White);//Below

    WriteText_Left_0(0, "MAX DEPTH");
    WriteText_Left_0(2, "DIVE TIME");

    PrepareMaxDepth(maxDepth_buf,0);
    WriteText_Right_17(0, maxDepth_buf,Black, White);

    prepare_LastElapseDiveTime();
    WriteText_Right_17(2, EDT_TimeBuf,Black,White);
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S4B(void) {
    char *text;
    WriteText_Title_2(_MainTitle[0],1,Black,White);//Top

    text = "MORE DATA";
    DisplayMainMenu(text, White);//Below

    WriteText_Left_0(0, "TEMPERATURE");
    WriteText_Left_0(1, "ALTITUDE");
    WriteText_Left_0(2, "GAS 1 FO2");
    WriteText_Left_0(3, "GAS 1 PO2 AL");
    WriteText_Left_0(4, "O2 SAT");
    WriteText_Left_0(5, "TIME TO FLY");
    WriteText_Left_0(6, "DESAT TIME");

    PrepareTemper();
    WriteText_Right_17(0, _Temper_buf,Black, White);

    PrepareAltitude();
    WriteText_Right_17(1, Altitude_buf, Black, White);

    WriteText_Right_17(2, FO2_String(FO2), Black, White);

    WriteText_Right_17(3, PO2_String(FO2, PO2), Black, White);

    PrepareO2();
    WriteText_Right_17(4, O2num_buf, Black, White);

    prepare_FLYtime(FLYtime_buf);
    WriteText_Right_17(5, FLYtime_buf,Black,White);

    prepare_DESATTime();
    WriteText_Right_17(6, DESATtime_buf, Black, White);

    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}
void Text_S4A(void) {
    char* text;
    WriteText_Title_2(_MainTitle[0],1,Black,White);//Top

    text = "MAIN MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "LAST DIVE DATA";
    LeftText_[2] = "MORE DATA";
    LeftText_[3] = "PLAN";
    LeftText_[4] = "SET GAS";
    LeftText_[5] = "SET ALARMS";
    LeftText_[6] = "SET UTILITIES";
    LeftText_[7] = "SET PREVIEW";
    LeftText_[8] = "VIEW PREVIEW";
    WriteLeftText(ListReturn(),2); //Left

    text = "CURRENT STATUS";
    WriteText_Right_1(text, Black);//Right

    DisplayBottomTitle(_BottomTitle[18]);//Bottom
}
void Text_S5A(void) {
    char*text;
    WriteText_Title_2(_MainTitle[0],1,Black,White);//Top

    text = "MAIN MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "LAST DIVE DATA";
    LeftText_[2] = "MORE DATA";
    LeftText_[3] = "PLAN";
    LeftText_[4] = "SET GAS";
    LeftText_[5] = "SET ALARMS";
    LeftText_[6] = "SET UTILITIES";
    LeftText_[7] = "SET PREVIEW";
    LeftText_[8] = "VIEW PREVIEW";
    WriteLeftText(9,3); //Left

    text = "NO DECO ~~DIVE~~ ~~TIMES~~ ALLOWED";
    WriteText_Right_1(text, Black);//Right

    DisplayBottomTitle(_BottomTitle[19]);//Bottom
}

void Text_S5B(void) {
    char *text;
    text = "PLAN";
    Update_Plan_Data();//Just need update once when need change
    WriteText_Title_2(text,1,Black,White);//Top

    text = "DEPTHS,LIMITS";
    DisplayMainMenu(text, White);//Below
    LCD_SetColors(White, Black);
    FontSet=(tChar*)myriad_bold_16;
    LCD_DisplayStringLine(5, 74, "DEPTH        LIMIT");
    WriteLeftText_1();

    WriteText_Left_6(DSAT_String, White);//Left top text

    TextRight4 = "FO2 SET";
    WriteText_Right_13(85,FO2_String(FO2));//Write text to pos Y

    TextRight4 = "PO2 SET";
    WriteText_Right_13(145, PO2_String(FO2, PO2));

    TextRight4 = "MAX";
    PrepareMaxDepth(maxDepth_buf, 0);
    WriteText_Right_13(195,maxDepth_buf);

    TextRight4_0 = "^ - UP LIST";
    TextRight4_1 = "v - DOWN LIST";
    TextRight4_2 = "\0";
    TextRight4_3 = "\0";
    WriteText_Right_14(155,256);

    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S6A(void) {
    char *text;
    WriteText_Title_2(_MainTitle[0],1,Black,White);//Top

    text = "MAIN MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "LAST DIVE DATA";
    LeftText_[2] = "MORE DATA";
    LeftText_[3] = "PLAN";
    LeftText_[4] = "SET GAS";
    LeftText_[5] = "SET ALARMS";
    LeftText_[6] = "SET UTILITIES";
    LeftText_[7] = "SET PREVIEW";
    LeftText_[8] = "VIEW PREVIEW";
    WriteLeftText(9,4); //Left

    text =  "~~ACCESS~~ TO SET ~~EACH~~ ~~~GAS~~~ TO BE ~~USED~~";
    WriteText_Right_5(text, Black, White); //Right

    DisplayBottomTitle(_BottomTitle[7]);//Bottom
}

void Text_S6B(void) {
    char *text;
    text = "GAS";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "GAS 1";
    LeftText_[1] = "GAS 2";
    LeftText_[2] = "GAS 3";
    LeftText_[3] = "GAS 4";
    //LeftText_[4] = "FO2 50% DEFAULT";
    WriteLeftText(4,0); //Left

    TextRight4 = "FO2";
    WriteText_Right_13(85, FO2_String(FO21));
    if(FO21 != 0) {
        TextRight4 = "PO2 ALARM";
        WriteText_Right_13(135,PO2_String(FO21, PO21));
    }
    text = "~~ACCESS~~ TO SET ~FO2&~ ~~~PO2~~~ ALARM";
    WriteText_Right_7(text);//Right

    DisplayBottomTitle(_BottomTitle[11]);//Bottom
}

void Text_S6C(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "GAS 1";
    DisplayMainMenu(text, White);//Below

    TextRight4 = "FO2";
    WriteText_Right_13(85, FO2_String(FO21));

    if(FO21 != 0) {
        TextRight4 = "PO2 ALARM";
        WriteText_Right_13(135,PO2_String(FO21, PO21));
    }

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S7A(void) {
    char *text;
    text = "GAS";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "GAS 1";
    LeftText_[1] = "GAS 2";
    LeftText_[2] = "GAS 3";
    LeftText_[3] = "GAS 4";
    WriteLeftText(4,1); //Left

    TextRight4 = "FO2";
    WriteText_Right_13(85, FO2_String(FO22));

    if(FO22 != 0) {
        TextRight4 = "PO2 ALARM";
        WriteText_Right_13(135,PO2_String(FO22, PO22));
    }

    text = "~~ACCESS~~ TO SET ~FO2&~ ~~~PO2~~~ ALARM";
    WriteText_Right_7(text);//Right

    DisplayBottomTitle(_BottomTitle[11]);//Bottom
}

void Text_S7B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "GAS 1";
    LeftText_[1] = "GAS 2";
    LeftText_[2] = "GAS 3";
    LeftText_[3] = "GAS 4";
    //LeftText_[4] = "FO2 50% DEFAULT";
    WriteLeftText(4,1); //Left

    text = LeftText_[1] ;
    DisplayMainMenu(text, White);//Below

    TextRight4 = "FO2";
    WriteText_Right_13(85, FO2_String(FO22));

    if(FO22 != 0) {
        TextRight4 = "PO2 ALARM";
        WriteText_Right_13(135,PO2_String(FO22, PO22));
    }

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S8A(void) {
    char *text;
    text = "GAS";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "GAS 1";
    LeftText_[1] = "GAS 2";
    LeftText_[2] = "GAS 3";
    LeftText_[3] = "GAS 4";
    WriteLeftText(4,2); //Left

    TextRight4 = "FO2";
    WriteText_Right_13(85, FO2_String(FO23));

    if(FO23 != 0) {
        TextRight4 = "PO2 ALARM";
        WriteText_Right_13(135,PO2_String(FO23, PO23));
    }
    text = "~~ACCESS~~ TO SET ~FO2&~ ~~~PO2~~~ ALARM";
    WriteText_Right_7(text);//Right

    DisplayBottomTitle(_BottomTitle[11]);//Bottom
}

void Text_S8B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "GAS 1";
    LeftText_[1] = "GAS 2";
    LeftText_[2] = "GAS 3";
    LeftText_[3] = "GAS 4";
    //LeftText_[4] = "FO2 50% DEFAULT";
    WriteLeftText(4,2); //Left

    text = LeftText_[2] ;
    DisplayMainMenu(text, White);//Below

    TextRight4 = "FO2";
    WriteText_Right_13(85, FO2_String(FO23));

    if(FO23 != 0) {
        TextRight4 = "PO2 ALARM";
        WriteText_Right_13(135,PO2_String(FO23, PO23));
    }

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}


void Text_S9A(void) {
    char *text;
    text = "GAS";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "GAS 1";
    LeftText_[1] = "GAS 2";
    LeftText_[2] = "GAS 3";
    LeftText_[3] = "GAS 4";
    //LeftText_[4] = "FO2 50% DEFAULT";
    WriteLeftText(4,3); //Left

    TextRight4 = "FO2";
    WriteText_Right_13(85, FO2_String(FO24));

    if(FO24 != 0) {
        TextRight4 = "PO2 ALARM";
        WriteText_Right_13(135,PO2_String(FO24, PO24));
    }
    text = "~~ACCESS~~ TO SET ~FO2&~ ~~~PO2~~~ ALARM";
    WriteText_Right_7(text);//Right

    DisplayBottomTitle(_BottomTitle[11]);//Bottom
}

void Text_S9B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "GAS 1";
    LeftText_[1] = "GAS 2";
    LeftText_[2] = "GAS 3";
    LeftText_[3] = "GAS 4";
    //LeftText_[4] = "FO2 50% DEFAULT";
    WriteLeftText(4,3); //Left

    text = LeftText_[3];
    DisplayMainMenu(text, White);//Below

    TextRight4 = "FO2";
    WriteText_Right_13(85, FO2_String(FO24));

    if(FO24 != 0) {
        TextRight4 = "PO2 ALARM";
        WriteText_Right_13(135,PO2_String(FO24, PO24));
    }
    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right

    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S11A(void) {
    char *text;
    WriteText_Title_2(_MainTitle[0],1,Black,White);//Top

    text = "MAIN MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "LAST DIVE DATA";
    LeftText_[2] = "MORE DATA";
    LeftText_[3] = "PLAN";
    LeftText_[4] = "SET GAS";
    LeftText_[5] = "SET ALARMS";
    LeftText_[6] = "SET UTILITIES";
    LeftText_[7] = "SET PREVIEW";
    LeftText_[8] = "VIEW PREVIEW";
    WriteLeftText(9,5); //Left

    text = "~~ACCESS~~ TO SET ~~ALARMS~~ TO BE ~~~USED~~~";
    WriteText_Right_5(text, Black, White);//Right
    DisplayBottomTitle(_BottomTitle[6]);//Bottom
}


void Text_S12A(void) {
    char *text;
    text = "ALARMS";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TLBG";
    LeftText_[4] = "DTR";
    LeftText_[5] = "TURN PRESS";
    LeftText_[6] = "LOW PRESS";
    WriteLeftText(7,0); //Left

    text = OnOffStr(AudAlarm);
    WriteText_Right_6(text);

    text = "OFF WILL DISABLE BEEPS EXCEPT A VIOLATION";
    WriteText_Right_7(text);//Right
    DisplayBottomTitle(_BottomTitle[13]);//Bottom
}


void Text_S12B(void) {
    char *text;
    text = "ALARMS";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TLBG";
    LeftText_[4] = "DTR";
    LeftText_[5] = "TURN PRESS";
    LeftText_[6] = "LOW PRESS";
    WriteLeftText(7,0); //Left

    text = LeftText_[0];
    DisplayMainMenu(text, White);//Below

    text = OnOffStr(AudAlarm);
    WriteText_Right_6(text);

    TextRight4 = "SETTING";
    TextRight4_0= "^ - TOGGLE";
    TextRight4_1= "v - TOGGLE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}


void Text_S13A(void) {
    char *text;
    text = "ALARMS";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TLBG";
    LeftText_[4] = "DTR";
    LeftText_[5] = "TURN PRESS";
    LeftText_[6] = "LOW PRESS";
    WriteLeftText(7,1); //Left

    PrepareDepth(DepNum_buf,1);
    WriteText_Right_6(DepNum_buf);

    text = "~~ALERT~~ ~~AT~~ ~~DEPTH~~ ~SET~";
    WriteText_Right_7(text);//Right

    DisplayBottomTitle(_BottomTitle[13]);//Bottom
}


void Text_S13B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TLBG";
    LeftText_[4] = "DTR";
    LeftText_[5] = "TURN PRESS";
    LeftText_[6] = "LOW PRESS";
    WriteLeftText(7,1); //Left

    text = LeftText_[1];
    DisplayMainMenu(text, White);//Below

    PrepareDepth(DepNum_buf,1);
    WriteText_Right_6(DepNum_buf);

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right

    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}


void Text_S14A(void) {
    char *text;
    text = "ALARMS";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TLBG";
    LeftText_[4] = "DTR";
    LeftText_[5] = "TURN PRESS";
    LeftText_[6] = "LOW PRESS";
    WriteLeftText(7,2); //Left

    PrepareEDT(EDTnum_buf,0);
    WriteText_Right_6(EDTnum_buf);

    text = "~ALERT~ ~~~AT~~~ ~ELAPSED~ ~~TIME~~ SET";
    WriteText_Right_7(text);//Right

    DisplayBottomTitle(_BottomTitle[13]);//Bottom
}


void Text_S14B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TLBG";
    LeftText_[4] = "DTR";
    LeftText_[5] = "TURN PRESS";
    LeftText_[6] = "LOW PRESS";

    WriteLeftText(7,2); //Left

    text = "ELAPSED TIME ALARM";
    DisplayMainMenu(text, White);//Below

    PrepareEDT(EDTnum_buf,0);
    WriteText_Right_6(EDTnum_buf);

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right

    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S15A(void) {
    char *text;
    text = "ALARMS";
    WriteText_Title_2(text,1,Black,White);//Top
    text ="SET MENU";
    DisplayMainMenu(text, White);//Below
    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TLBG";
    LeftText_[4] = "DTR";
    LeftText_[5] = "TURN PRESS";
    LeftText_[6] = "LOW PRESS";

    WriteLeftText(7,3); //Left
    PrepareAlarmTLBG(TLBGnum_buf, 2);
    WriteText_Right_6(TLBGnum_buf);
    text = "ALERT ~~~AT~~~ %OF ~NITROGEN~ ~~SET~~";
    WriteText_Right_7(text);//Right
    DisplayBottomTitle(_BottomTitle[11]);//Bottom
}

void Text_S15B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TLBG";
    LeftText_[4] = "DTR";
    LeftText_[5] = "TURN PRESS";
    LeftText_[6] = "LOW PRESS";

    WriteLeftText(7,3); //Left

    text =   LeftText_[3];
    DisplayMainMenu(text, White);//Below

    PrepareAlarmTLBG(TLBGnum_buf, 2);
    WriteText_Right_6(TLBGnum_buf);//Right

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S16A(void) {
    char *text;
    text = "ALARMS";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TLBG";
    LeftText_[4] = "DTR";
    LeftText_[5] = "TURN PRESS";
    LeftText_[6] = "LOW PRESS";
    WriteLeftText(7,4); //Left

    prepare_DTRNum(DTRnum_buf,0);
    WriteText_Right_6(DTRnum_buf);

    text = "ALERT ~~~AT~~~ ~~DIVE~~ TIME REMAINING SET";
    WriteText_Right_7(text);//Right

    DisplayBottomTitle(_BottomTitle[11]);//Bottom
}


void Text_S16B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TLBG";
    LeftText_[4] = "DTR";
    LeftText_[5] = "TURN PRESS";
    LeftText_[6] = "LOW PRESS";
    WriteLeftText(7,4); //Left

    text = LeftText_[4];
    DisplayMainMenu(text, White);//Below

    prepare_DTRNum(DTRnum_buf,0);
    WriteText_Right_6(DTRnum_buf);

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right

    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S17A(void) {
    char *text;
    text = "ALARMS";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TLBG";
    LeftText_[4] = "DTR";
    LeftText_[5] = "TURN PRESS";
    LeftText_[6] = "LOW PRESS";

    WriteLeftText(7,5); //Left

    prepare_TurnEndAlarm(TurnString, TURN);
    WriteText_Right_6(TurnString);

    text = "ALERT ~~~AT~~~ TANK PRESSURE SET";
    WriteText_Right_7(text);//Right

    DisplayBottomTitle(_BottomTitle[13]);//Bottom
}

void Text_S17B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top
    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TLBG";
    LeftText_[4] = "DTR";
    LeftText_[5] = "TURN PRESS";
    LeftText_[6] = "LOW PRESS";

    WriteLeftText(7,5); //Left
    text =   "TURN PRESS ALARM";
    DisplayMainMenu(text, White);//Below
    prepare_TurnEndAlarm(TurnString, TURN);
    WriteText_Right_6(TurnString);
    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S18A(void) {
    char *text;
    text = "ALARMS";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TLBG";
    LeftText_[4] = "DTR";
    LeftText_[5] = "TURN PRESS";
    LeftText_[6] = "LOW PRESS";

    WriteLeftText(7,6); //Left

    prepare_TurnEndAlarm(EndString, END);
    WriteText_Right_6(EndString);

    text = "ALERT ~~~AT~~~ TANK PRESSURE SET";
    WriteText_Right_7(text);//Right

    DisplayBottomTitle(_BottomTitle[13]);//Bottom
}

void Text_S18B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TLBG";
    LeftText_[4] = "DTR";
    LeftText_[5] = "TURN PRESS";
    LeftText_[6] = "LOW PRESS";

    WriteLeftText(7,6); //Left

    text =   "LOW PRESS ALARM";
    DisplayMainMenu(text, White);//Below

    prepare_TurnEndAlarm(EndString, END);
    WriteText_Right_6(EndString);

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S19A(void) {
    char *text;
    text =_MainTitle[0];
    WriteText_Title_2(text,1,Black,White);//Top

    text = "MAIN MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "LAST DIVE DATA";
    LeftText_[2] = "MORE DATA";
    LeftText_[3] = "PLAN";
    LeftText_[4] = "SET GAS";
    LeftText_[5] = "SET ALARMS";
    LeftText_[6] = "SET UTILITIES";
    LeftText_[7] = "SET PREVIEW";
    LeftText_[8] = "VIEW PREVIEW";
    WriteLeftText(9,6); //Left

    text =  "~~ACCESS~~ TO SET ~UTILITIES~ TO BE ~~~USED~~~";
    WriteText_Right_5(text, Black, White); //Right

    DisplayBottomTitle(_BottomTitle[6]);//Bottom
}

void Text_S20A(void) {
    char *text;
    text = "UTILITIES";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "DEEP STOP";
    LeftText_[3] = "SAFETY STOP";
    LeftText_[4] = "ALGORITHM";
    LeftText_[5] = "CONSERVATIVE";
    LeftText_[6] = "SAMPLE RATE";
    WriteLeftText(7,0);//Left

    text = WaterType_String;
    WriteText_Right_6(text);
    text = "BASIS ~~~FOR~~~ DEPTH VALUES";
    WriteText_Right_7(text);
    DisplayBottomTitle(_BottomTitle[13]);//Bottom
}

void Text_S20B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "DEEP STOP";
    LeftText_[3] = "SAFETY STOP";
    LeftText_[4] = "ALGORITHM";
    LeftText_[5] = "CONSERVATIVE";
    LeftText_[6] = "SAMPLE RATE";
    WriteLeftText(7,0);//Left

    text = LeftText_[0];
    DisplayMainMenu(text, White);//Below

    text = WaterType_String;
    WriteText_Right_6(text);

    TextRight4 = "SETTING";
    TextRight4_0= "^ - TOGGLE";
    TextRight4_1= "v - TOGGLE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S21A(void) {
    char *text;
    text = "UTILITIES";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "DEEP STOP";
    LeftText_[3] = "SAFETY STOP";
    LeftText_[4] = "ALGORITHM";
    LeftText_[5] = "CONSERVATIVE";
    LeftText_[6] = "SAMPLE RATE";
    WriteLeftText(7,1);//Left

    TextRight4 = UnitType_2(UnitType_);
    TextRight4_0 = UnitType_1(UnitType_);
    WriteText_Right_8();

    text = "~~~FOR~~~ DEPTH, PRESSURE, TEMP";
    WriteText_Right_7(text);
    DisplayBottomTitle(_BottomTitle[13]);//Bottom
}

void Text_S21B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "UNITS OF MEASURE";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "DEEP STOP";
    LeftText_[3] = "SAFETY STOP";
    LeftText_[4] = "ALGORITHM";
    LeftText_[5] = "CONSERVATIVE";
    LeftText_[6] = "SAMPLE RATE";
    WriteLeftText(7,1);//Left

    TextRight4 = UnitType_2(UnitType_);
    TextRight4_0 = UnitType_1(UnitType_);
    WriteText_Right_8();

    TextRight4 = "SETTING";
    TextRight4_0= "^ - TOGGLE";
    TextRight4_1= "v - TOGGLE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right

    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S22A(void) {
    char *text;
    text = "UTILITIES";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "DEEP STOP";
    LeftText_[3] = "SAFETY STOP";
    LeftText_[4] = "ALGORITHM";
    LeftText_[5] = "CONSERVATIVE";
    LeftText_[6] = "SAMPLE RATE";
    WriteLeftText(7,2);//Left

    WriteText_Right_6(DEEPSTOP_String);

    text = "NO DECO STOP AT ~1/2 MAX~ DEPTH";
    WriteText_Right_7(text);

    DisplayBottomTitle(_BottomTitle[11]);//Bottom
}

void Text_S22B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "DEEP STOP";
    LeftText_[3] = "SAFETY STOP";
    LeftText_[4] = "ALGORITHM";
    LeftText_[5] = "CONSERVATIVE";
    LeftText_[6] = "SAMPLE RATE";
    WriteLeftText(7,2);//Left

    text = LeftText_[2];
    DisplayMainMenu(text, White);//Below

    WriteText_Right_6(DEEPSTOP_String);

    TextRight4 = "SETTING";
    TextRight4_0= "^ - TOGGLE";
    TextRight4_1= "v - TOGGLE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right

    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S23A(void) {
    char *text;
    text = "UTILITIES";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "DEEP STOP";
    LeftText_[3] = "SAFETY STOP";
    LeftText_[4] = "ALGORITHM";
    LeftText_[5] = "CONSERVATIVE";
    LeftText_[6] = "SAMPLE RATE";
    WriteLeftText(7,3);//Left
    WriteText_Right_6(SafetyStopPrepare());

    text = "NO DECO STOP AT DEPTH & TIME SET";
    WriteText_Right_7(text);

    DisplayBottomTitle(_BottomTitle[11]);//Bottom
}

void Text_S23B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "DEEP STOP";
    LeftText_[3] = "SAFETY STOP";
    LeftText_[4] = "ALGORITHM";
    LeftText_[5] = "CONSERVATIVE";
    LeftText_[6] = "SAMPLE RATE";
    WriteLeftText(7,3);//Left

    text = LeftText_[3];
    DisplayMainMenu(text, White);//Below
    WriteText_Right_6(SafetyStopPrepare());

    TextRight4 = "SELECTION";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right

    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S23C(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "DEEP STOP";
    LeftText_[3] = "SAFETY STOP";
    LeftText_[4] = "ALGORITHM";
    LeftText_[5] = "CONSERVATIVE";
    LeftText_[6] = "SAMPLE RATE";
    WriteLeftText(7,3);//Left
    text = LeftText_[3];
    DisplayMainMenu(text, White);//Below
    WriteText_Right_22();
    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_21();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S24A(void) {
    char *text;
    text = "UTILITIES";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "DEEP STOP";
    LeftText_[3] = "SAFETY STOP";
    LeftText_[4] = "ALGORITHM";
    LeftText_[5] = "CONSERVATIVE";
    LeftText_[6] = "SAMPLE RATE";
    WriteLeftText(7,4);//Left

    text = DSAT_String;
    WriteText_Right_6(text);

    text = "DSAT IS MORE LIBERAL ~FOR~ GENERAL DIVING";
    WriteText_Right_7(text);

    DisplayBottomTitle(_BottomTitle[11]);//Bottom
}

void Text_S24B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "DEEP STOP";
    LeftText_[3] = "SAFETY STOP";
    LeftText_[4] = "ALGORITHM";
    LeftText_[5] = "CONSERVATIVE";
    LeftText_[6] = "SAMPLE RATE";
    WriteLeftText(7,4);//Left

    text = LeftText_[4];
    DisplayMainMenu(text, White);//Below

    text = DSAT_String;
    WriteText_Right_6(text);

    TextRight4 = "SETTING";
    TextRight4_0= "^ - TOGGLE";
    TextRight4_1= "v - TOGGLE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right

    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S25A(void) {
    char *text;
    text = "UTILITIES";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "DEEP STOP";
    LeftText_[3] = "SAFETY STOP";
    LeftText_[4] = "ALGORITHM";
    LeftText_[5] = "CONSERVATIVE";
    LeftText_[6] = "SAMPLE RATE";
    WriteLeftText(7,5);//Left

    text =OnOffStr(Coseva_bit);
    WriteText_Right_6(text);

    text = "ON DECREASES DIVE TIMES BY 1 ALTITUDE LEVEL";
    WriteText_Right_7(text);

    DisplayBottomTitle(_BottomTitle[11]);//Bottom
}

void Text_S25B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "DEEP STOP";
    LeftText_[3] = "SAFETY STOP";
    LeftText_[4] = "ALGORITHM";
    LeftText_[5] = "CONSERVATIVE";
    LeftText_[6] = "SAMPLE RATE";
    WriteLeftText(7,5);//Left

    text = "CONSERV FACTOR";
    DisplayMainMenu(text, White);//Below

    text =OnOffStr(Coseva_bit);
    WriteText_Right_6(text);

    TextRight4 = "SETTING";
    TextRight4_0= "^ - TOGGLE";
    TextRight4_1= "v - TOGGLE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right

    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S26A(void) {
    char *text;
    text = "UTILITIES";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "DEEP STOP";
    LeftText_[3] = "SAFETY STOP";
    LeftText_[4] = "ALGORITHM";
    LeftText_[5] = "CONSERVATIVE";
    LeftText_[6] = "SAMPLE RATE";
    WriteLeftText(7,6);//Left

    prepare_SampleRate(SampleRate_buf);
    WriteText_Right_6(SampleRate_buf);

    text = "INTERVAL DATA IS SAMPLED FOR DIVERLOG";
    WriteText_Right_7(text);

    DisplayBottomTitle(_BottomTitle[13]);//Bottom
}

void Text_S26B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "PC SAMPLING RATE";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "DEEP STOP";
    LeftText_[3] = "SAFETY STOP";
    LeftText_[4] = "ALGORITHM";
    LeftText_[5] = "CONSERVATIVE";
    LeftText_[6] = "SAMPLE RATE";
    WriteLeftText(7,6);//Left

    prepare_SampleRate(SampleRate_buf);
    WriteText_Right_6(SampleRate_buf);

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right

    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S27A(void) {
    char *text;
    WriteText_Title_2(_MainTitle[0],1,Black,White);//Top

    text = "MAIN MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "LAST DIVE DATA";
    LeftText_[2] = "MORE DATA";
    LeftText_[3] = "PLAN";
    LeftText_[4] = "SET GAS";
    LeftText_[5] = "SET ALARMS";
    LeftText_[6] = "SET UTILITIES";
    LeftText_[7] = "SET PREVIEW";
    LeftText_[8] = "VIEW PREVIEW";
    WriteLeftText(9,7); //Left

    text =  "ACCESS TO ~~SELECT~~ ~~UP TO~~ ~9 ITEMS~ ~~FOR~~ VIEWING";
    WriteText_Right_5(text, Black, White); //Right

    DisplayBottomTitle(_BottomTitle[8]);//Bottom
}

void Text_S27B(void) {
    char *text;
    text = "PREVIEW";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    //LeftText_[8] = (u8 *)Malloc(30);
    LeftText_[8]="GO TO SCREEN 2";
    WriteText_Left_8(Sel_line1,Bold_V1_0 ,_RowPreview[0].Row_String_Left);
    WriteText_Left_8(Sel_line2,Bold_V1_1, _RowPreview[1].Row_String_Left);
    WriteText_Left_8(Sel_line3,Bold_V1_2, _RowPreview[2].Row_String_Left);
    WriteText_Left_8(Sel_line4,Bold_V1_3, _RowPreview[3].Row_String_Left);
    WriteText_Left_8(Sel_line5,Bold_V1_4, _RowPreview[4].Row_String_Left);
    WriteText_Left_8(Sel_line6,Bold_V1_5, _RowPreview[5].Row_String_Left);
    WriteText_Left_8(Sel_line7,Bold_V1_6, _RowPreview[6].Row_String_Left);
    WriteText_Left_8(Sel_line8,Bold_V1_7, _RowPreview[7].Row_String_Left);
    WriteText_Left_8(Sel_line9,Bold_V1_8, LeftText_[8]);
    //Free(LeftText_[8],sizeof(LeftText_[8]));

    TextRight4_0 = "^ - UP LIST";
    TextRight4_1 = "v - DOWN LIST";
    TextRight4_2 = "> - SAVE";
    TextRight4_3 = "(FLASH/SOLID)";
    WriteText_Right_14(150,210);

    text =  "~FLASH~ ~~UP TO~~ ~9 PICKS,~ THEN ~~SAVE~~";
    WriteText_Right_5(text, Black, White); //Right

    DisplayBottomTitle(_BottomTitle[2]);//Bottom
}

void Text_S27C(void) {
    // LeftText_[8] = (u8 *)Malloc(30);
    LeftText_[8]="GO TO SCREEN 1";
    WriteText_Left_8(Sel_line1,Bold_V2_0, _RowPreview[8].Row_String_Left);
    WriteText_Left_8(Sel_line2,Bold_V2_1, _RowPreview[9].Row_String_Left);
    WriteText_Left_8(Sel_line3,Bold_V2_2, _RowPreview[10].Row_String_Left);
    WriteText_Left_8(Sel_line4,Bold_V2_3, _RowPreview[11].Row_String_Left);
    WriteText_Left_8(Sel_line5,Bold_V2_4, _RowPreview[12].Row_String_Left);
    WriteText_Left_8(Sel_line6,Bold_V2_5, _RowPreview[13].Row_String_Left);
    WriteText_Left_8(Sel_line7,Bold_V2_6, _RowPreview[14].Row_String_Left);
    WriteText_Left_8(Sel_line8,Bold_V2_7, _RowPreview[15].Row_String_Left);
    WriteText_Left_8(Sel_line9,Bold_V2_8, LeftText_[8]);
    // Free(LeftText_[8],sizeof(LeftText_[8]));
}

void Text_S28A(void) {
    char *text;
    WriteText_Title_2(_MainTitle[0],1,Black,White);//Top

    text = "MAIN MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "LAST DIVE DATA";
    LeftText_[2] = "MORE DATA";
    LeftText_[3] = "PLAN";
    LeftText_[4] = "SET GAS";
    LeftText_[5] = "SET ALARMS";
    LeftText_[6] = "SET UTILITIES";
    LeftText_[7] = "SET PREVIEW";
    LeftText_[8] = "VIEW PREVIEW";
    WriteLeftText(9,8); //Left

    text = "~~ACCESS~~ TO VIEW ~~ITEMS~~ SELECTED";
    WriteText_Right_1(text, Black);//Right

    DisplayBottomTitle(_BottomTitle[20]);//Bottom
}

void RowPreviewProcess(void) {
    PrepareDepth(DepNum_buf, 1);//4//
    PrepareEDT(EDTnum_buf,0);//4
    PrepareAlarmTLBG(TLBGnum_buf, 2);
    prepare_DTRNum(DTRnum_buf,0);
    prepare_TurnEndAlarm(TurnString, TURN);
    prepare_TurnEndAlarm(EndString, END);
    CheckStopDepth();//SAFETY STOP
    CheckStopTime();//SAFETY STOP
    prepare_SampleRate(SampleRate_buf);
    FO2PreviewProcess();
    //NPRV1_ = NPRV1;//Load the value to check the GAS 1 or 2, 3, 4

//FO21 & PO21
    _RowPreview[0].Row_String_Right_0[0]= FO21_buf[0];
    _RowPreview[0].Row_String_Right_0[1]= FO21_buf[1];
    _RowPreview[0].Row_String_Right_0[2]= FO21_buf[2];
    _RowPreview[0].Row_String_Right_0[3]= FO21_buf[3];
    _RowPreview[0].Row_String_Right_0[4]= FO21_buf[4];

    _RowPreview[0].Row_String_Right_1[0]= *(PO2_String(FO21,PO21) + 0);
    _RowPreview[0].Row_String_Right_1[1]= *(PO2_String(FO21,PO21) + 1);
    _RowPreview[0].Row_String_Right_1[2]= *(PO2_String(FO21,PO21) + 2);
    _RowPreview[0].Row_String_Right_1[3]= *(PO2_String(FO21,PO21) + 3);
    _RowPreview[0].Row_String_Right_1[4]= *(PO2_String(FO21,PO21) + 4);

//FO22 & PO22
    _RowPreview[1].Row_String_Right_0[0]= FO22_buf[0];
    _RowPreview[1].Row_String_Right_0[1]= FO22_buf[1];
    _RowPreview[1].Row_String_Right_0[2]= FO22_buf[2];
    _RowPreview[1].Row_String_Right_0[3]= FO22_buf[3];
    _RowPreview[1].Row_String_Right_0[4]= FO22_buf[4];

    _RowPreview[1].Row_String_Right_1[0]= *(PO2_String(FO22,PO22) + 0);
    _RowPreview[1].Row_String_Right_1[1]= *(PO2_String(FO22,PO22) + 1);
    _RowPreview[1].Row_String_Right_1[2]= *(PO2_String(FO22,PO22) + 2);
    _RowPreview[1].Row_String_Right_1[3]= *(PO2_String(FO22,PO22) + 3);
    _RowPreview[1].Row_String_Right_1[4]= *(PO2_String(FO22,PO22) + 4);

//FO23 & PO23
    _RowPreview[2].Row_String_Right_0[0]= FO23_buf[0];
    _RowPreview[2].Row_String_Right_0[1]= FO23_buf[1];
    _RowPreview[2].Row_String_Right_0[2]= FO23_buf[2];
    _RowPreview[2].Row_String_Right_0[3]= FO23_buf[3];
    _RowPreview[2].Row_String_Right_0[4]= FO23_buf[4];

    _RowPreview[2].Row_String_Right_1[0]= *(PO2_String(FO23,PO23) + 0);
    _RowPreview[2].Row_String_Right_1[1]= *(PO2_String(FO23,PO23) + 1);
    _RowPreview[2].Row_String_Right_1[2]= *(PO2_String(FO23,PO23) + 2);
    _RowPreview[2].Row_String_Right_1[3]= *(PO2_String(FO23,PO23) + 3);
    _RowPreview[2].Row_String_Right_1[4]= *(PO2_String(FO23,PO23) + 4);

//FO24 & PO24
    _RowPreview[3].Row_String_Right_0[0]= FO24_buf[0];
    _RowPreview[3].Row_String_Right_0[1]= FO24_buf[1];
    _RowPreview[3].Row_String_Right_0[2]= FO24_buf[2];
    _RowPreview[3].Row_String_Right_0[3]= FO24_buf[3];
    _RowPreview[3].Row_String_Right_0[4]= FO24_buf[4];

    _RowPreview[3].Row_String_Right_1[0]= *(PO2_String(FO24,PO24) + 0);
    _RowPreview[3].Row_String_Right_1[1]= *(PO2_String(FO24,PO24) + 1);
    _RowPreview[3].Row_String_Right_1[2]= *(PO2_String(FO24,PO24) + 2);
    _RowPreview[3].Row_String_Right_1[3]= *(PO2_String(FO24,PO24) + 3);
    _RowPreview[3].Row_String_Right_1[4]= *(PO2_String(FO24,PO24) + 4);

//Others data
    _RowPreview[4].Row_String_Right_0[0]= DepNum_buf[0];
    _RowPreview[4].Row_String_Right_0[1]= DepNum_buf[1];
    _RowPreview[4].Row_String_Right_0[2]= DepNum_buf[2];
    _RowPreview[4].Row_String_Right_0[3]= DepNum_buf[3];
    _RowPreview[4].Row_String_Right_0[4]= DepNum_buf[4];

    _RowPreview[5].Row_String_Right_0[0] = EDTnum_buf[0];
    _RowPreview[5].Row_String_Right_0[1] = EDTnum_buf[1];
    _RowPreview[5].Row_String_Right_0[2] = EDTnum_buf[2];
    _RowPreview[5].Row_String_Right_0[3] = EDTnum_buf[3];
    _RowPreview[5].Row_String_Right_0[4] = EDTnum_buf[4];

    _RowPreview[6].Row_String_Right_0[0] = TLBGnum_buf[0];
    _RowPreview[6].Row_String_Right_0[1] = TLBGnum_buf[1];
    _RowPreview[6].Row_String_Right_0[2] = TLBGnum_buf[2];
    _RowPreview[6].Row_String_Right_0[3] = TLBGnum_buf[3];
    _RowPreview[6].Row_String_Right_0[4] = TLBGnum_buf[4];

    _RowPreview[7].Row_String_Right_0[0] = DTRnum_buf[0];
    _RowPreview[7].Row_String_Right_0[1] = DTRnum_buf[1];
    _RowPreview[7].Row_String_Right_0[2] = DTRnum_buf[2];
    _RowPreview[7].Row_String_Right_0[3] = DTRnum_buf[3];
    _RowPreview[7].Row_String_Right_0[4] = DTRnum_buf[4];

    _RowPreview[8].Row_String_Right_0[0] = TurnString[0];
    _RowPreview[8].Row_String_Right_0[1] = TurnString[1];
    _RowPreview[8].Row_String_Right_0[2] = TurnString[2];
    _RowPreview[8].Row_String_Right_0[3] = TurnString[3];
    _RowPreview[8].Row_String_Right_0[4] = TurnString[4];

    _RowPreview[9].Row_String_Right_0[0] = EndString[0] ;
    _RowPreview[9].Row_String_Right_0[1] = EndString[1] ;
    _RowPreview[9].Row_String_Right_0[2] = EndString[2] ;
    _RowPreview[9].Row_String_Right_0[3] = EndString[3] ;
    _RowPreview[9].Row_String_Right_0[4] = EndString[4] ;

    _RowPreview[10].Row_String_Right_0[0] = *(WaterType_String + 0);
    _RowPreview[10].Row_String_Right_0[1] = *(WaterType_String + 1);
    _RowPreview[10].Row_String_Right_0[2] = *(WaterType_String + 2);
    _RowPreview[10].Row_String_Right_0[3] = *(WaterType_String + 3);
    _RowPreview[10].Row_String_Right_0[4] = *(WaterType_String + 4);

    _RowPreview[11].Row_String_Right_0[0]= *(DEEPSTOP_String + 0);
    _RowPreview[11].Row_String_Right_0[1]= *(DEEPSTOP_String + 1);
    _RowPreview[11].Row_String_Right_0[2]= *(DEEPSTOP_String + 2);
    _RowPreview[11].Row_String_Right_0[3]= *(DEEPSTOP_String + 3);
    _RowPreview[11].Row_String_Right_0[4]= *(DEEPSTOP_String + 4);

    _RowPreview[13].Row_String_Right_0[0] = *(DSAT_String + 0);
    _RowPreview[13].Row_String_Right_0[1] = *(DSAT_String + 1);
    _RowPreview[13].Row_String_Right_0[2] = *(DSAT_String + 2);
    _RowPreview[13].Row_String_Right_0[3] = *(DSAT_String + 3);
    _RowPreview[13].Row_String_Right_0[4] = *(DSAT_String + 4);

    _RowPreview[14].Row_String_Right_0[0] = *(Coseva_StringOnOff + 0);
    _RowPreview[14].Row_String_Right_0[1] = *(Coseva_StringOnOff + 1);
    _RowPreview[14].Row_String_Right_0[2] = *(Coseva_StringOnOff + 2);
    _RowPreview[14].Row_String_Right_0[3] = *(Coseva_StringOnOff + 3);
    _RowPreview[14].Row_String_Right_0[4] = *(Coseva_StringOnOff + 4);

    _RowPreview[15].Row_String_Right_0[0] = SampleRate_buf[0];
    _RowPreview[15].Row_String_Right_0[1] = SampleRate_buf[1];
    _RowPreview[15].Row_String_Right_0[2] = SampleRate_buf[2];
    _RowPreview[15].Row_String_Right_0[3] = SampleRate_buf[3];
    _RowPreview[15].Row_String_Right_0[4] = SampleRate_buf[4];

    if(MORFLG_LowNibble == 1) {//When SAFETY STOP ON-- >
        _RowPreview[12].Row_String_Right_0[0]= *(SafetyStopDepth_Str + 0);
        _RowPreview[12].Row_String_Right_0[1]= *(SafetyStopDepth_Str + 1);
        _RowPreview[12].Row_String_Right_0[2]= *(SafetyStopDepth_Str + 2);
        _RowPreview[12].Row_String_Right_0[3]= *(SafetyStopDepth_Str + 3);
        _RowPreview[12].Row_String_Right_0[4]= *(SafetyStopDepth_Str + 4);
        _RowPreview[12].Row_String_Right_0[5]= *(SafetyStopDepth_Str + 5);

        _RowPreview[12].Row_String_Right_1[0]= *(SafetyStopTime_Str + 0);
        _RowPreview[12].Row_String_Right_1[1]= *(SafetyStopTime_Str + 1);
        _RowPreview[12].Row_String_Right_1[2]= *(SafetyStopTime_Str + 2);
        _RowPreview[12].Row_String_Right_1[3]= *(SafetyStopTime_Str + 3);
        _RowPreview[12].Row_String_Right_1[4]= *(SafetyStopTime_Str + 4);
        _RowPreview[12].Row_String_Right_1[5]= *(SafetyStopTime_Str + 5);
    }
    else {
        _RowPreview[12].Row_String_Right_0[0]= *(SafetyStopPrepare() + 0);
        _RowPreview[12].Row_String_Right_0[1]= *(SafetyStopPrepare() + 1);
        _RowPreview[12].Row_String_Right_0[2]= *(SafetyStopPrepare() + 2);
        _RowPreview[12].Row_String_Right_0[3]= *(SafetyStopPrepare() + 3);
        _RowPreview[12].Row_String_Right_0[4]= *(SafetyStopPrepare() + 4);
    }

}

void Text_S28B(void) {
    char *text;
    u8 i  = 0;
    u16 _RowSelected = 0;
    u8 _Row = 0;
    WriteText_Title_2(_MainTitle[0],1,Black,White);//Top

    text = "DIVE PREVIEW";
    DisplayMainMenu(text, White);//Below

    DisplayBottomTitle(_BottomTitle[2]);//Bottom

    RowPreviewProcess();

    for(i = 0; i < 16; i++) {
        _RowSelected = (RowSelected >> i) & 0x0001;
        if(_RowSelected > 0) {
            WriteText_Left_0(_Row, _RowPreview[i].Row_String_Left);
            WriteText_Right_17(_Row, _RowPreview[i].Row_String_Right_0,Black, White);//Write only 1 parameter
            if(((RowSelected & BIT0) == BIT0 && i == 0 && FO21 != 0)||
                    ((RowSelected & BIT1) == BIT1 && i == 1 && FO22 != 0)||
                    ((RowSelected & BIT2) == BIT2 && i == 2 && FO23 != 0)||
                    ((RowSelected & BIT3) == BIT3 && i == 3 && FO24 != 0)||
                    ((RowSelected & BIT12) == BIT12 && i == 12 && MORFLG_LowNibble == 1 )) { //When ON will display 2 parametters and other will be OFF no comma
                LCD_DisplayStringLine(195,84+(_Row*24), ",");
                LCD_DisplayStringLine(199,84+(_Row*24), _RowPreview[i].Row_String_Right_1);
            }
            _Row ++;
        }
    }

}

void Text_S29A(void) {
    WriteText_Middle_0();//Middle
    DisplayPSIvsGTR();
    DisplayBottomTitle(_BottomTitle[22]);//Bottom
}

void Text_S30A(void) {
    char *text;
    text = "GAUGE";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "MAIN MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "LAST DIVE DATA";
    LeftText_[2] = "MORE DATA";
    LeftText_[3] = "SET ALARMS";
    LeftText_[4] = "SET UTILITIES";
    LeftText_[5] = "VIEW PREVIEW";
    WriteLeftText(ListReturn(),0); //Left

    ProcessAutoDimBright();
    WriteText_Right_6(BrightNess_buf);//Right


    text = "SELECT TO ~~ADJUST~~ BY % ~~~OR~~~ AUTO DIM";
    WriteText_Right_7(text);//Right

    DisplayBottomTitle(_BottomTitle[11]);//Bottom
}


void Text_S30B(void) {
    char *text;
    text = "ADJUST";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "LAST DIVE DATA";
    LeftText_[2] = "MORE DATA";
    LeftText_[3] = "SET ALARMS";
    LeftText_[4] = "SET UTILITIES";
    LeftText_[5] = "VIEW PREVIEW";
    WriteLeftText(ListReturn(),0); //Left

    text = LeftText_[0];
    DisplayMainMenu(text, White);//Below

    ProcessAutoDimBright();
    WriteText_Right_6(BrightNess_buf);//Right

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right

    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S31A(void) {
    char *text;
    text = "GAUGE";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "MAIN MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "LAST DIVE DATA";
    LeftText_[2] = "MORE DATA";
    LeftText_[3] = "SET ALARMS";
    LeftText_[4] = "SET UTILITIES";
    LeftText_[5] = "VIEW PREVIEW";
    WriteLeftText(ListReturn(),1); //Left

    text = "ACCESS ~~~FOR~~~ ~~LATEST~~ DIVE DATA";
    WriteText_Right_1(text, Black);//Right

    DisplayBottomTitle(_BottomTitle[18]);//Bottom
}
void Text_S31B(void) {
    char *text;
    text = "GAUGE";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "LAST DIVE DATA";
    DisplayMainMenu(text, White);//Below

    WriteText_Left_0(0, "MAX DEPTH");
    WriteText_Left_0(2, "DIVE TIME");
    PrepareMaxDepth(maxDepth_buf,0);
    WriteText_Right_17(0, maxDepth_buf,Black, White);

    prepare_LastElapseDiveTime();
    WriteText_Right_17(2, EDT_TimeBuf,Black, White);
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S32A(void) {
    char *text;
    text = "GAUGE";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "MAIN MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "LAST DIVE DATA";
    LeftText_[2] = "MORE DATA";
    LeftText_[3] = "SET ALARMS";
    LeftText_[4] = "SET UTILITIES";
    LeftText_[5] = "VIEW PREVIEW";
    WriteLeftText(ListReturn(),2); //Left

    text = "CURRENT STATUS";
    WriteText_Right_1(text, Black);//Right
    DisplayBottomTitle(_BottomTitle[18]);//Bottom
}

void Text_S32B(void) {
    char *text;
    text = "GAUGE";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "MORE DATA";
    DisplayMainMenu(text, White);//Below

    WriteText_Left_0(0, "TEMPERATURE");
    WriteText_Left_0(1, "ALTITUDE");
    WriteText_Left_0(2, "TIME TO FLY");

    PrepareTemper();
    WriteText_Right_17(0, _Temper_buf,Black, White);

    PrepareAltitude();
    WriteText_Right_17(1, Altitude_buf,Black, White);

    prepare_FLYtime(FLYtime_buf);
    WriteText_Right_17(2, FLYtime_buf,Black, White);

    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S33A(void) {
    char *text;
    text = "GAUGE";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "MAIN MENU";
    DisplayMainMenu(text, White);//Below
    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "LAST DIVE DATA";
    LeftText_[2] = "MORE DATA";
    LeftText_[3] = "SET ALARMS";
    LeftText_[4] = "SET UTILITIES";
    LeftText_[5] = "VIEW PREVIEW";
    WriteLeftText(6,3); //Left
    text =  "~ACCESS~ ~TO SET~ ~ALARMS~ TO BE ~USED~";
    WriteText_Right_5(text, Black, White); //Right
    DisplayBottomTitle(_BottomTitle[6]);//Bottom
}

void Text_S34A(void) {
    char *text;
    text = "ALARMS";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "SET MENU";
    DisplayMainMenu(text, White);//Below
    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TURN PRESS";
    LeftText_[4] = "LOW PRESS";
    WriteLeftText(5,0); //Left
    text = OnOffStr(AudAlarm);
    WriteText_Right_6(text);
    text = "OFF WILL DISABLE BEEPS EXCEPT A VIOLATION";
    WriteText_Right_7(text);//Right
    DisplayBottomTitle(_BottomTitle[13]);//Bottom
}

void Text_S34B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top
    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TURN PRESS";
    LeftText_[4] = "LOW PRESS";
    WriteLeftText(5,0); //Left
    text = LeftText_[0];
    DisplayMainMenu(text, White);//Below
    text = OnOffStr(AudAlarm);
    WriteText_Right_6(text);
    TextRight4 = "SETTING";
    TextRight4_0= "^ - TOGGLE";
    TextRight4_1= "v - TOGGLE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S35A(void) {
    char *text;
    text = "ALARMS";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TURN PRESS";
    LeftText_[4] = "LOW PRESS";
    WriteLeftText(5,1); //Left

    PrepareDepth(DepNum_buf,1);
    WriteText_Right_6(DepNum_buf);

    text = "~~ALERT~~ ~~AT~~ ~~DEPTH~~ ~SET~";
    WriteText_Right_7(text);//Right

    DisplayBottomTitle(_BottomTitle[13]);//Bottom
}


void Text_S35B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TURN PRESS";
    LeftText_[4] = "LOW PRESS";
    WriteLeftText(5,1); //Left

    text = LeftText_[1];
    DisplayMainMenu(text, White);//Below

    PrepareDepth(DepNum_buf,1);
    WriteText_Right_6(DepNum_buf);

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right

    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S36A(void) {
    char *text;
    text = "ALARMS";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TURN PRESS";
    LeftText_[4] = "LOW PRESS";

    WriteLeftText(5,2); //Left

    PrepareEDT(EDTnum_buf,0);
    WriteText_Right_6(EDTnum_buf);

    text = "~ALERT~ ~~AT~~ ELAPSED TIME ~~SET~~";
    WriteText_Right_7(text);//Right

    DisplayBottomTitle(_BottomTitle[13]);//Bottom
}


void Text_S36B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TURN PRESS";
    LeftText_[4] = "LOW PRESS";

    WriteLeftText(5,2); //Left

    text ="ELAPSED TIME ALARM";
    DisplayMainMenu(text, White);//Below

    PrepareEDT(EDTnum_buf,0);
    WriteText_Right_6(EDTnum_buf);

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right

    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S37A(void) {
    char *text;
    text = "ALARMS";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TURN PRESS";
    LeftText_[4] = "LOW PRESS";

    WriteLeftText(5,3); //Left

    prepare_TurnEndAlarm(TurnString, TURN);
    WriteText_Right_6(TurnString);

    text = "ALERT ~~~AT~~~ TANK PRESSURE SET";
    WriteText_Right_7(text);//Right
    DisplayBottomTitle(_BottomTitle[13]);//Bottom
}


void Text_S37B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,0,Black,White);//Top

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TURN PRESS";
    LeftText_[4] = "LOW PRESS";

    WriteLeftText(5,3); //Left

    text = "TURN PRESS ALARM";
    DisplayMainMenu(text, White);//Below

    prepare_TurnEndAlarm(TurnString, TURN);
    WriteText_Right_6(TurnString);

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S38A(void) {
    char *text;
    text = "ALARMS";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TURN PRESS";
    LeftText_[4] = "LOW PRESS";
    WriteLeftText(5,4); //Left

    prepare_TurnEndAlarm(EndString, END);
    WriteText_Right_6(EndString);

    text = "ALERT ~~~AT~~~ TANK PRESSURE SET";
    WriteText_Right_7(text);//Right
    DisplayBottomTitle(_BottomTitle[13]);//Bottom
}

void Text_S38B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "AUDIBLE";
    LeftText_[1] = "DEPTH";
    LeftText_[2] = "EDT";
    LeftText_[3] = "TURN PRESS";
    LeftText_[4] = "LOW PRESS";
    WriteLeftText(5,4); //Left

    text =   "LOW PRESS ALARM";
    DisplayMainMenu(text, White);//Below

    prepare_TurnEndAlarm(EndString, END);
    WriteText_Right_6(EndString);

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S39A(void) {
    char *text;
    text = "GAUGE";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "MAIN MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "LAST DIVE DATA";
    LeftText_[2] = "MORE DATA";
    LeftText_[3] = "SET ALARMS";
    LeftText_[4] = "SET UTILITIES";
    LeftText_[5] = "VIEW PREVIEW";
    WriteLeftText(6,4); //Left

    text = "~~ACCESS~~ TO SET ~UTILITIES~ TO BE ~~~USED~~~";
    WriteText_Right_5(text, Black, White); //Right
    DisplayBottomTitle(_BottomTitle[6]);//Bottom
}

void Text_S40A(void) {
    char *text;
    text = "UTILITIES";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "SAMPLE RATE";
    WriteLeftText(3,0);//Left

    text = WaterType_String;
    WriteText_Right_6(text);

    text = "BASIS ~~FOR~~ DEPTH VALUES";
    WriteText_Right_7(text);
    DisplayBottomTitle(_BottomTitle[13]);//Bottom
}

void Text_S40B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "SAMPLE RATE";
    WriteLeftText(3,0);//Left

    text = LeftText_[0];
    DisplayMainMenu(text, White);//Below

    text = WaterType_String;

    WriteText_Right_6(text);

    TextRight4 = "SETTING";
    TextRight4_0= "^ - TOGGLE";
    TextRight4_1= "v - TOGGLE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S41A(void) {
    char *text;
    text = "UTILITIES";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "SAMPLE RATE";
    WriteLeftText(3,1);//Left

    TextRight4 = UnitType_2(UnitType_);
    TextRight4_0 = UnitType_1(UnitType_);
    WriteText_Right_8();

    text = "~FOR~ DEPTH, PRESSURE, TEMP";
    WriteText_Right_7(text);
    DisplayBottomTitle(_BottomTitle[13]);//Bottom
}

void Text_S41B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "UNITS OF MEASURE";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "SAMPLE RATE";
    WriteLeftText(3,1);//Left

    TextRight4 = UnitType_2(UnitType_);
    TextRight4_0 = UnitType_1(UnitType_);
    WriteText_Right_8();

    TextRight4 = "SETTING";
    TextRight4_0= "^ - TOGGLE";
    TextRight4_1= "v - TOGGLE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S42A(void) {
    char *text;
    text = "UTILITIES";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "SET MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "SAMPLE RATE";
    WriteLeftText(3,2);//Left

    prepare_SampleRate(SampleRate_buf);
    WriteText_Right_6(SampleRate_buf);

    text = "INTERVAL DATA IS SAMPLED FOR PC/MAC";
    WriteText_Right_7(text);
    DisplayBottomTitle(_BottomTitle[11]);//Bottom
}

void Text_S42B(void) {
    char *text;
    text = "SET";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "PC SAMPLING RATE";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "WATER TYPE";
    LeftText_[1] = "UNITS";
    LeftText_[2] = "SAMPLE RATE";
    WriteLeftText(3,2);//Left

    prepare_SampleRate(SampleRate_buf);
    WriteText_Right_6(SampleRate_buf);

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_S43A(void) {
    char *text;
    text = "GAUGE";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "MAIN MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "LAST DIVE DATA";
    LeftText_[2] = "MORE DATA";
    LeftText_[3] = "SET ALARMS";
    LeftText_[4] = "SET UTILITIES";
    LeftText_[5] = "VIEW PREVIEW";
    WriteLeftText(6,5); //Left

    text = "~ACCESS~ ~TO VIEW~ ~ITEMS~";
    WriteText_Right_1(text, Black);//Right
    DisplayBottomTitle(_BottomTitle[20]);//Bottom
}

void Text_S43B(void) {
    char *text;
    text = "GAUGE";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "DIVE PREVIEW";
    DisplayMainMenu(text, White);//Below

    WriteText_Left_0(0, "DEPTH AL");
    WriteText_Left_0(1, "EDT AL");
    WriteText_Left_0(2, "TURN AL");
    WriteText_Left_0(3, "END AL");
    WriteText_Left_0(4, "WATER TYPE");
    WriteText_Left_0(5, "SAMPLING RATE");

    PrepareDepth(DepNum_buf,1);
    WriteText_Right_17(0, DepNum_buf,Black,White);//00

    PrepareEDT(EDTnum_buf, 0);
    WriteText_Right_17(1, EDTnum_buf,Black,White);//01

    prepare_TurnEndAlarm(TurnString, TURN);
    WriteText_Right_17(2, TurnString,Black, White);//02

    prepare_TurnEndAlarm(EndString, END);
    WriteText_Right_17(3, EndString,Black,White);//03

    WriteText_Right_17(4, WaterType_String ,Black,White);//04
    prepare_SampleRate(SampleRate_buf);//
    WriteText_Right_17(5,SampleRate_buf,Black, White);//05

    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_D1A(void) {
    DisplayBottomTitle(_BottomTitle[22]);//Bottom
    DisplayDepth();
    DisplayNDC();
    DisplayEDT();
    DisplayTLBG();
    DisplayASCBG();
    DisplayGAS();
    DisplayFO2();
    DisplayPO2Current();
    if(Gas_Num == 1) {
        DisplayPressure();
        DisplayGTR();
    }
    else {
        DisplaySPG();
    }
}

void Text_D2A(void) {
    char *text;
    switch (MainMode) {
    case 0x90:
        text=_MainTitle[1];
        LCD_SetColors(Black, White);
        break;
    case 0x60:
        text=_MainTitle[2];
        LCD_SetColors(Black, White);
        break;
    case 0x80:
        text=_MainTitle[3];
        LCD_SetColors(Red, White);
        break;
    case 0x30:
        if((DSSTAT&BIT_7)==BIT_7) {
            text=_MainTitle[5];
        }
        else {
            text=_MainTitle[4];
        }
        LCD_SetColors(Black, White);
        break;
    default:
        text=_MainTitle[0];
        LCD_SetColors(Black, White);
        break;
    }
    WriteText_Title_2(text,1,TextColor,BackColor);//Top

    text = "DIVE MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "MORE DATA";
    LeftText_[2] = ((MainMode== 0x90)||(MainMode== 0x80)) ? "" : "GAS SWITCH";
    LeftText_[3] = ((MainMode== 0x90)||
                    (MainMode== 0x30)||
                    (((SUSTAT&BIT_5)== BIT_5)&&(MainMode!= 0x90))||
                    (MainMode== 0x40)||
                    (MainMode== 0x50)||
                    (MainMode== 0x60)||
                    (MainMode== 0x70)||
                    (MainMode== 0x80)) ? "" : "DS PREVIEW";
    WriteLeftText(4,0); //Left

    ProcessAutoDimBright();
    WriteText_Right_6(BrightNess_buf);//Right

    text = "SELECT TO ~~ADJUST~~ BY % ~~~OR~~~ AUTO DIM";
    WriteText_Right_7(text);//Right
    DisplayBottomTitle(_BottomTitle[11]);//Bottom
}

void Text_D2B(void) {
    char *text;
    text = "ADJUST";
    WriteText_Title_2(text,1,Black,White);//Top

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "MORE DATA";
    LeftText_[2] = ((MainMode== 0x90)||(MainMode== 0x80)) ? "" : "GAS SWITCH";
    LeftText_[3] = ((MainMode== 0x90)||
                    (MainMode== 0x30)||
                    (((SUSTAT&BIT_5)== BIT_5)&&(MainMode!= 0x90))||
                    (MainMode== 0x40)||
                    (MainMode== 0x50)||
                    (MainMode== 0x60)||
                    (MainMode== 0x70)||
                    (MainMode== 0x80)) ? "" : "DS PREVIEW";

    WriteLeftText(4,0); //Left
    DisplayMainMenu(LeftText_[0], White);//Below
    ProcessAutoDimBright();
    WriteText_Right_6(BrightNess_buf);//Right

    TextRight4 = "VALUE";
    TextRight4_0= "^ - INCREASE";
    TextRight4_1= "v - DECREASE";
    TextRight4_2= "> - SAVE";
    WriteText_Right_4();//Right
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}
void Text_D3A(void) {
    char *text;
    switch (MainMode) {
    case 0x90:
        text=_MainTitle[1];
        LCD_SetColors(Black, White);
        break;
    case 0x60:
        text=_MainTitle[2];
        LCD_SetColors(Black, White);
        break;
    case 0x80:
        text=_MainTitle[3];
        LCD_SetColors(Red, White);
        break;
    case 0x30:
        if((DSSTAT&BIT_7)==BIT_7) {
            text=_MainTitle[5];
        }
        else {
            text=_MainTitle[4];
        }
        LCD_SetColors(Black, White);
        break;
    default:
        text=_MainTitle[0];
        LCD_SetColors(Black, White);
        break;
    }
    WriteText_Title_2(text,1,TextColor,BackColor);//Top

    text = "DIVE MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "MORE DATA";
    LeftText_[2] = ((MainMode== 0x90)||
                    (MainMode== 0x80)) ? "" : "GAS SWITCH";
    LeftText_[3] = ((MainMode== 0x90)||
                    (MainMode== 0x30)||
                    (((SUSTAT&BIT_5)== BIT_5)&&(MainMode!= 0x90))||
                    (MainMode== 0x40)||
                    (MainMode== 0x50)||
                    (MainMode== 0x60)||
                    (MainMode== 0x70)||
                    (MainMode== 0x80)) ? "" : "DS PREVIEW";

    WriteLeftText(4,1); //Left

    text = "CURRENT STATUS";
    WriteText_Right_1(text, Black);//Right

    DisplayBottomTitle(_BottomTitle[18]);//Bottom
}
void Text_D4A(void) {
    char *text;
    //text = ((MainMode == 0x90)) ? _MainTitle[1]:((MainMode == 0x60) ? _MainTitle[2] : ((MainMode == 0x80) ? _MainTitle[3] : _MainTitle[0])) ;
    switch (MainMode) {
    case 0x90:
        text=_MainTitle[1];
        break;
    case 0x60:
        text=_MainTitle[2];
        break;
    case 0x80:
        text=_MainTitle[3];
        break;
    case 0x30:
        if((DSSTAT&BIT_7)==BIT_7) {
            text=_MainTitle[5];
        }
        else {
            text=_MainTitle[4];
        }
        break;
    default:
        text=_MainTitle[0];
        break;
    }
    WriteText_Title_2(text,1,Black,White);//Top

    text = "DIVE MENU";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "MORE DATA";
    LeftText_[2] = ((MainMode== 0x90)||(MainMode== 0x80)) ? "" : "GAS SWITCH";
    LeftText_[3] = ((MainMode== 0x90)||
                    (MainMode== 0x30)||
                    (((SUSTAT&BIT_5)== BIT_5)&&(MainMode!= 0x90))||
                    (MainMode== 0x40)||
                    (MainMode== 0x50)||
                    (MainMode== 0x60)||
                    (MainMode== 0x70)||
                    (MainMode== 0x80)) ? "" : "DS PREVIEW";
    WriteLeftText(4,2); //Left
    text =  "~ACCESS~ ~TO VIEW~ ~~GAS~~ OPTIONS ~~SET~~";
    WriteText_Right_5(text, Black, White); //RightText_

    DisplayBottomTitle(_BottomTitle[15]);//Bottom
}

void Text_D3B(void) {
    char *text;
    len= 0;
    switch (MainMode) {
    case 0x90:
        text=_MainTitle[1];
        LCD_SetColors(Black, White);
        break;
    case 0x60:
        text=_MainTitle[2];
        LCD_SetColors(Black, White);
        break;
    case 0x80:
        text=_MainTitle[3];
        LCD_SetColors(Red, White);
        break;
    case 0x30:
        if((DSSTAT&BIT_7)==BIT_7) {
            text=_MainTitle[5];
        }
        else {
            text=_MainTitle[4];
        }
        LCD_SetColors(Black, White);
        break;
    default:
        text=_MainTitle[0];
        LCD_SetColors(Black, White);
        break;
    }
    WriteText_Title_2(text,1,TextColor,BackColor);//Top

    DisplayMainMenu("MORE DIVE DATA", White);//Below
    if(MainMode == 0x90) {
        WriteText_Left_0(0, "DIVE TIME");
        WriteText_Left_0(1, "MAX DEPTH");
        WriteText_Left_0(2, "TIME OF DAY");
        WriteText_Left_0(3, "TEMPERATURE");

        PrepareEDT(EDTnum_buf, 0);
        WriteText_Right_17(0, EDTnum_buf,Black, White);//01

        PrepareMaxDepth(maxDepth_buf, 0);
        WriteText_Right_17(1, maxDepth_buf, Black, White);//02

        PrepareClock(time_buf, 0);
        WriteText_Right_17(2, time_buf, Black, White);//03

        PrepareTemper();
        WriteText_Right_17(3, _Temper_buf, Black, White);//04
    }
    else {
        WriteText_Left_0(0, (((MainMode==0x60)||(MainMode==0x70)) ? "TOTAL ASCENT" : "NDC"));
        WriteText_Left_0(1, "DIVE TIME");
        WriteText_Left_0(2, "MAX DEPTH");
        WriteText_Left_0(3, "TIME OF DAY");
        WriteText_Left_0(4, "TEMPERATURE");
        WriteText_Left_0(5, StrFO2MoreDiveData());
        WriteText_Left_0(6, StrPO2MoreDiveData());
        WriteText_Left_0(7, "O2 SAT");
        WriteText_Left_0(8, "CURRENT PO2");
        if((MainMode==0x60)||(MainMode==0x70)) { //DECO MORE DATA
            len += Num2Str(TAT,TotalAscentTime_buf , 2);
            TotalAscentTime_buf[len++]=']';
            TotalAscentTime_buf[len]='\0';
            WriteText_Right_17(0, TotalAscentTime_buf,Black, White );//01
        }
        else {
            PrepareNDC(NDCnum_buf,0);
            WriteText_Right_17(0, NDCnum_buf, ((MainMode==0x80) ? Red : Black), White);//00
        }
        PrepareEDT(divetime_buf, 0);
        WriteText_Right_17(1, divetime_buf,Black, White );//01
        PrepareMaxDepth(maxDepth_buf, 0);
        //WriteText_Right_17(2, maxDepth_buf, ((MainMode==0x80) ? Red : Black), White);//02
        WriteText_Right_17(2, maxDepth_buf, Black, White);//02
        PrepareClock(time_buf, 0);
        WriteText_Right_17(3, time_buf, Black, White);//03
        PrepareTemper();
        WriteText_Right_17(4, _Temper_buf,Black, White);//04
        WriteText_Right_17(5, FO2_String(FO2), Black, White);//05
        WriteText_Right_17(6, PO2_String(FO2, in_buf[24]), ((MainMode==0x80) ? Red : Black), White);//06
        PrepareO2();
        WriteText_Right_17(7, O2num_buf, ((MainMode==0x80) ? Red : Black), White);//07
        WriteText_Right_17(8, PO2CurrentString(),((MainMode==0x80) ? Red : Black), White);//08
    }
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

//Display D3B
char StrFO2[10];
char* StrFO2MoreDiveData(void) {
    StrFO2[0] = 'G';
    StrFO2[1] = 'A';
    StrFO2[2] = 'S';
    StrFO2[3] = ' ';
    Num2Str((u16)Gas_Num, StrFO2 + 4, 2);
    StrFO2[5] = ' ';
    StrFO2[6] = 'F';
    StrFO2[7] = 'O';
    StrFO2[8] = '2';
    StrFO2[9] = '\0';
    return StrFO2;
}
//Display D3B
char StrPO2[14];
char* StrPO2MoreDiveData(void) {
    if((MainMode==0x60)||(MainMode==0x70)) { //DECO MORE DATA
        StrPO2[0]   = 'D';
        StrPO2[1]   = 'E';
        StrPO2[2]   = 'C';
        StrPO2[3]   = 'O';
        StrPO2[4]   = ' ';
        StrPO2[5]   = 'P';
        StrPO2[6]   = 'O';
        StrPO2[7]   = '2';
        StrPO2[8]   = ' ';
        StrPO2[9]   = 'A';
        StrPO2[10]  = 'L';
        StrPO2[11]  = '\0';
    }
    else {
        StrPO2[0] = 'G';
        StrPO2[1] = 'A';
        StrPO2[2] = 'S';
        StrPO2[3] = ' ';
        Num2Str((u16)Gas_Num, StrPO2 + 4, 1);
        StrPO2[5] = ' ';
        StrPO2[6] = 'P';
        StrPO2[7] = 'O';
        StrPO2[8] = '2';
        StrPO2[9] = ' ';
        StrPO2[10] = 'A';
        StrPO2[11] = 'L';
        StrPO2[12] = '\0';
    }
    return StrPO2;
}

void Text_D5C(void) {
    char *text;
    text = "DEEP STOP";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "PREVIEW";
    DisplayMainMenu(text, White);//Below

    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "MORE DATA";
    LeftText_[2] = "GAS SWITCH";
    LeftText_[3] = "DS PREVIEW";
    WriteLeftText(4,3); //Left

    PrepareMaxDepth(DepNum_buf, 0);//°                                                                                                                                                                                                                                                                                                        //missing update data here
    WriteText_Right_15();

    WriteText_Right_16();
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_D5A(void) {
    char *text;
    WriteText_Title_2(_MainTitle[0],1,Black,White);//Top
    text = "DIVE MENU";
    DisplayMainMenu(text, White);//Below
    LeftText_[0] = "BRIGHTNESS";
    LeftText_[1] = "MORE DATA";
    LeftText_[2] = "GAS SWITCH";
    LeftText_[3] = "DS PREVIEW";
    WriteLeftText(4,3); //Left
    //Check the Bit 4 of MORFLG to show on the right
    if((MORFLG & BIT_4) == BIT_4) {
        if(UnitType_) {
            text = "~TRIGGERS~ AT 24 M, STOP IS AT 1/2 MAX ~DEPTH~";
        }
        else {
            text = "~TRIGGERS~ AT 80 FT, STOP IS AT 1/2 MAX ~DEPTH~";
        }
        WriteText_Right_1(text, Black);//Right
    }
    else {
        text = "DEEP STOP ~IS SET~ ~OFF~";
        WriteText_Right_5(text, Black, White); //Right
    }
    DisplayBottomTitle(_BottomTitle[15]);//Bottom
}

void Text_D4B(void) {
    char *text;
    text = "NORM";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "DIVE MENU";
    DisplayMainMenu(text, White);//Below
    TextRight4_0 = "^ - UP LIST";
    TextRight4_1 = "v - DOWN LIST";
    TextRight4_2 = "> - TO SWITCH";
    TextRight4_3 = "\0";
    WriteText_Right_14(150,200);
    WriteText_Left_9();
}

void Text_D6A(void) {
    DisplayDepth();
    DisplayTLBG();//TL number
    DisplayASCBG();//AR number
    if(Gas_Num == 1) {
        DisplayPressure();
        DisplayGTR();
    }
    else {
        DisplaySPG();
    }
    LeftText_[9] = "DEEP" ;
    WriteText_Middle_7B();//Middle
    DisplayTextMiddle_2(GAS_Str());//Middle
    DisplayBottomTitle(_BottomTitle[22]);//Bottom
}

void Text_D7A(void) {
    DisplayDepth();
    DisplayTLBG();//TL number
    DisplayASCBG();//AR number
    if(Gas_Num == 1) {
        DisplayPressure();
        DisplayGTR();
    }
    else {
        DisplaySPG();
    }
    LeftText_[9] = "SAFETY" ;
    WriteText_Middle_7();//Middle
    DisplayTextMiddle_2(GAS_Str());//Middle
    DisplayBottomTitle(_BottomTitle[22]);//Bottom
}

void Text_D9A(void) {
    DisplayMainTitle(_MainTitle[1]);
    DisplayTemper_Pos1();
    DisplayBattery_Pos1();
    DisplayClock_Pos1();
    DisplayDepth();
    DisplayEDT();
    DisplayRunStatus();
    DisplayRunTime();
    DisplayASCBG();//AR number
    if(Gas_Num == 1) {
        DisplayPressure();
        DisplayGTR();
    }
    else {
        DisplaySPG();
    }
    DisplayBottomTitle(_BottomTitle[22]);//Bottom
}
void LogStartTime_String(void) {
    hh = Bcd2ToByte(Log_Data[CurrentRecord][5] & 0x7F);
    mm = Bcd2ToByte(Log_Data[CurrentRecord][4]);
    PrepareClock(time_buf, 0);
}

void Text_H14B(void) {
    char *text;
    text = "LOG";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "DATA 1";
    DisplayMainMenu(text, White);//Below
    TextColor=White;
    FontSet=(tChar*)myriad_bold_16;
    LCD_DisplayStringLine_As_Right(140, 74, "DATE          #    LOG");
    WriteLeftText_AlignRight(); //Left
    //http://prntscr.com/632t99
    if(((Log_Data[CurrentRecord][12]&0x81)==0)) { //BIT 7 and BIT 0 must be 0
        WriteText_Left_6(DSAT_String, White);//Left top text
    }
    WriteText_Right_19(84, "START TIME");
    LogStartTime_String();//Update background.c in here
    WriteText_Right_23(99, time_buf);//Update background.c in here

    WriteText_Right_19(124, "DIVE TIME");
    PrepareEDT(divetime_buf, 0);//Update background.c in here
    WriteText_Right_23(139, divetime_buf);//Update background.c in here

    WriteText_Right_19(170, "MAX DEPTH");
    PrepareMaxDepth(maxDepth_buf, 0);
    WriteText_Right_23(185, maxDepth_buf);//Update background.c in here

    WriteText_Right_19(209, "ELEVATION");
    PrepareAltitude();
    WriteText_Right_23(224,Altitude_buf);//Update background.c in here

    TextRight4_0 = "^ - UP LIST";
    TextRight4_1 = "v - DOWN LIST";
    TextRight4_2 = "> - TO DATA 2";
    TextRight4_3 = "\0";
    WriteText_Right_14(150,244);
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_H14C(void) {
    char *text;
    text = "DATA 2";
    DisplayMainMenu(text, White);//Below
    TextColor=White;
    FontSet=(tChar*)myriad_bold_16;
//http://prntscr.com/632t99
// if(((Log_Data[CurrentRecord][12]&0x81)==0)) { //BIT 7 and BIT 0 must be 0

    WriteText_Right_19(84, "START PRESS");
    Prepare_PressNum(pressure_buf,Start_Pressure,0);//Update background.c in here
    WriteText_Right_23(99,pressure_buf);//Update background.c in here

    WriteText_Right_19(124, "END PRESS");
    Prepare_PressNum(pressure_buf,End_Pressure,0);//Update background.c in here
    WriteText_Right_23(139,pressure_buf);//Update background.c in here

    WriteText_Right_19(170, "AVE DEPTH");
    prepare_aveDepthnum(aveDepth_buf,0);
    WriteText_Right_23(185, aveDepth_buf);//Update background.c in here

    WriteText_Right_19(209, "LOW TEMP");
    PrepareTemper();
    WriteText_Right_23(224, _Temper_buf);//Update background.c in here

    TextRight4_0 = "^ - UP LIST";
    TextRight4_1 = "v - DOWN LIST";
    TextRight4_2 = "> - TO DATA 3";
    TextRight4_3 = "\0";
    WriteText_Right_14(150,244);
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_H14D(void) {
    char *text;
    text = "DATA 3";
    DisplayMainMenu(text, White);//Below
    TextColor=White;
    FontSet=(tChar*)myriad_bold_16;
    //http://prntscr.com/632t99
    //if(((Log_Data[CurrentRecord][12]&0x81)==0)) { //BIT 7 and BIT 0 must be 0
    if((Log_Data[CurrentRecord][12] & BIT_0) != BIT_0) {
        //Redraw the line
        LCD_SetTextColor(0x0000);
        LCD_DrawLine(145,120,95,LCD_DIR_HORIZONTAL);
        LCD_DrawLine(145,164,95,LCD_DIR_HORIZONTAL);
        LCD_DrawLine(145,206,95,LCD_DIR_HORIZONTAL);
        //Draw the text
        WriteText_Right_19(84, "FO2 SET");
        WriteText_Right_23(99,FO2_String(FO21));//Update background.c in here
        WriteText_Right_19(124, "MAX PO2");
        WriteText_Right_23(139,PO2_String(FO21,(((uint16_t)Log_Data[CurrentRecord][29] * 256) + Log_Data[CurrentRecord][28])));//Update background.c in here   //@npthinh
        WriteText_Right_19(170, "O2 SAT(END)");
        PrepareO2();
        WriteText_Right_23(185, O2num_buf);
        LCD_FillRect(145, 243, 95, 1, Black);
    }
    else {
        DrawPart(WhiteRect_RightMenu);
        //Write text
        LCD_FillRect(145, 230, 95, 1, Black);
        text = "~GAUGE~ ~~DIVE~~ ~NO~ ~DATA.~";
        LCD_DisplayText(145, 240, 100, (ptChar)myriad_bold_14, Black, White, AlignCenter, text);
    }
    TextRight4_0 = "^ - UP LIST";
    TextRight4_1 = "v - DOWN LIST";
    TextRight4_2 = "> - TO DATA 1";
    TextRight4_3 = "\0";
    WriteText_Right_14(150,244);
}

void Text_H15A(void) {
    char *text;
    PrepareClock(time_buf,1);
    PrepareTemper();
    PrepareBattery();
    PrepareMidday(midnight);
    WriteText_Title_1();                    //Top

    DisplayMainMenu("HOME MENU", White);//Below

    LeftText_[0] = "MY INFO";
    LeftText_[1] = "PROPLUS X INFO";
    LeftText_[2] = "SETUP MENU";
    LeftText_[3] = "LOG";
    LeftText_[4] = "HISTORY";
    LeftText_[5] = "NORM MODE";
    LeftText_[6] = "GAUGE MODE";
    WriteLeftText(7,4);                    //Left
    if((MSG&0x0F) == 0) {
        text = "~~NO~~ ~~DIVES~~ RECORDED YET.";
        WriteText_Right_5(text, Black, White);//Right
    }
    else {
        text = "DIVE DATA";
        WriteText_Right_1(text, Black);//Right
        DisplayBottomTitle(_BottomTitle[18]);//Bottom
    }
}

void Text_H15B(void) {
    char *text;
    text = "HISTORY";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "DATA";
    DisplayMainMenu(text, White);//Below

    WriteText_Left_0(0, "TOTAL DIVES");
    WriteText_Left_0(1, "TOTAL DIVE TIME");
    WriteText_Left_0(2, "MAX DIVE TIME");
    WriteText_Left_0(3, "AVE DIVE TIME");
    WriteText_Left_0(4, "MAX DEPTH");
    WriteText_Left_0(5, "AVE DEPTH");
    WriteText_Left_0(6, "LOWEST TEMP");
    WriteText_Left_0(7, "MAX ALTITUDE");

    prepare_totalDives();
    WriteText_Right_17(0, totalDive_buf,Black, White);

    prepare_totalDiveTimeNum();
    WriteText_Right_17(1, totalDiveTime_buf,Black,White);

    PrepareMaxDiveTime();
    WriteText_Right_17(2, maxDivetime_buf,Black,White);

    prepare_aveDiveNum(aveDivenum_buf,0);
    WriteText_Right_17(3, aveDivenum_buf,Black,White);

    PrepareMaxDepth(maxDepth_buf,0);
    WriteText_Right_17(4, maxDepth_buf,Black,White);

    prepare_aveDepthnum(aveDepth_buf, 0);
    WriteText_Right_17(5, aveDepth_buf,Black,White);

    prepare_lowestTempNum();
    WriteText_Right_17(6, lowestTemp_buf,Black,White);

    PrepareAltitude();
    WriteText_Right_17(7, Altitude_buf, Black,White);
    DisplayBottomTitle(_BottomTitle[3]);//Bottom
}

void Text_H18A(void) {
    char *text;
    text = "CONNECT";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "USB";
    DisplayMainMenu(text, White);//Below

    TextLeft3_0 = "WAIT FOR ~~THE~~ CONNECTION TO BE ACCEPTED";
    TextLeft3_1 = "~~ABOUT~~ 5 SEC...";
    WriteText_Left_3(100);
    DisplayBottomTitle(_BottomTitle[23]);//Bottom
}
void Text_H18B(void) {
    char *text;
    text = "CONNECT";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "USB";
    DisplayMainMenu(text, White);//Below
    TextLeft3_0 = "BATTERY CHARGING";
    TextLeft3_1 = " ";
    WriteText_Left_3(105);
    DisplayBottomTitle(_BottomTitle[23]);//Bottom
}
void Text_H18C(void) {
    char *text;
    text = "CONNECT";
    WriteText_Title_2(text,1,Black,White);//Top
    text = "USB";
    DisplayMainMenu(text, White);//Below
    TextLeft3_0 = "CONNECTION MADE";
    WriteText_Left_4();//Left
    DisplayBottomTitle(_BottomTitle[23]);//Bottom
}
void Text_H18D(void) {
    char *text;
    text = "CONNECTED";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "USB";
    DisplayMainMenu(text, White);//Below

    TextLeft3_0 = "DATA DOWNLOAD ~~IN~~ PROGRESS";
    WriteText_Left_4();//Left
    DisplayBottomTitle(_BottomTitle[23]);//Bottom
}
void Text_H18E(void) {
    char *text;
    text = "CONNECTED";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "USB";
    DisplayMainMenu(text, White);//Below

    TextLeft3_0 = "DATA ~~UPLOAD~~ ~~IN~~ PROGRESS";
    WriteText_Left_4();//Left
    DisplayBottomTitle(_BottomTitle[23]);//Bottom
}
void Text_H18F(void) {
    char *text;
    text = "CONNECTED";
    WriteText_Title_2(text,1,Black,White);//Top

    text = "USB";
    DisplayMainMenu(text, White);//Below

    TextLeft3_0 = "UPDATING ~~~PPX~~~ FIRMWARE WAIT FOR PC/MAC MESSAGE";
    WriteText_Left_4();//Left
    DisplayBottomTitle(_BottomTitle[23]);//Bottom
}
void Text_H17A(char* Hmenu) {
    char *text;
    PrepareClock(time_buf,1);
    PrepareTemper();
    PrepareBattery();
    PrepareMidday(midnight);
    WriteText_Title_1();//Top
    //text = "HOME MENU";
    DisplayMainMenu(Hmenu, White);//Below
    LeftText_[0] = "MY INFO";
    LeftText_[1] = "PROPLUS X INFO";
    LeftText_[2] = "SETUP MENU";
    LeftText_[3] = "LOG";
    LeftText_[4] = "HISTORY";
    LeftText_[5] = "NORM MODE";
    LeftText_[6] = "GAUGE MODE";
    WriteLeftText(7,5);//Left
    text =  "~SELECT~ ~TO~ ACCESS ~NORM~ SURFACE ~MAIN~";
    WriteText_Right_5(text, Black, White);//Right
    DisplayBottomTitle(_BottomTitle[33]);//Bottom
}

void Text_H18AOld(void) {
    char *text;
    PrepareClock(time_buf,1);
    PrepareTemper();
    PrepareBattery();
    PrepareMidday(midnight);
    WriteText_Title_1();//Top
    DisplayMainMenu("HOME MENU", White);//Below
    LeftText_[0] = "MY INFO";
    LeftText_[1] = "PROPLUS X INFO";
    LeftText_[2] = "SETUP MENU";
    LeftText_[3] = "LOG";
    LeftText_[4] = "HISTORY";
    LeftText_[5] = "NORM MODE";
    LeftText_[6] = "GAUGE MODE";
    WriteLeftText(7,6);//Left
    text =  "~SELECT~ ~TO~ ACCESS ~GAUGE~ SURFACE ~MAIN~";
    WriteText_Right_5(text, Black, White);//Right
}

void DisplayDepth(void) { //http://prntscr.com/5c2vfd
    PrepareDepth(DepNum_buf,0);
    //When MSG == 0x02 or 0x82 0x04 0x84 white text and red background, others white back ground and black text.
    DisplayTextMiddle_3((((MSG==0x04)||
                          (MSG==0x84))? Red : White));//Middle
}
void DisplayDepthCompass(void) { //http://prntscr.com/5c2vfd
    PrepareDepth(DepNum_buf,0);
    //When MSG == 0x02 or 0x82 0x04 0x84 white text and red background, others white back ground and black text.
    DisplayTextMiddle_4((((MSG==0x04)||
                          (MSG==0x84))? Red : White));//Middle
}

void Text_A1B(void) {
    DrawPart(TitleBar_Deco);
    DisplayDepth();
    DisplayTLBG();//TL number
    DisplayASCBG();//AR number
    if(Gas_Num == 1) {
        DisplayPressure();
        DisplayGTR();
    }
    else {
        DisplaySPG();
    }
    LeftText_[9] = "DECO" ;
    WriteText_Middle_8();//Middle
    DisplayTextMiddle_2(GAS_Str());//Middle
    DisplayBottomTitle(_BottomTitle[22]);//Bottom
}

void Text_A4A(void) {
    DisplayDepth();
    DisplayTLBG();//TL number
    DisplayASCBG();//AR number
    if(Gas_Num == 1) {
        DisplayPressure();
        DisplayGTR();
    }
    else {
        DisplaySPG();
    }
    LeftText_[9] = "DECO" ;
    WriteText_Middle_8();//Middle
    DisplayTextMiddle_2(GAS_Str());//Middle
    DisplayBottomTitle(_BottomTitle[22]);//Bottom
}
void Text_A5B(void) {
    WriteText_Title_4("DOWN TO STOP", 0);//Top
    PrepareSurfTime();
    WriteText_Middle_9();//Middle
    // PrepareTLBG();
    DisplayTLBG();//TL number
    Prepare_GTRnum(GTRnum_buf);
    if(Gas_Num == 1) {
        DisplayPressure();
        DisplayGTR();
    }
    else {
        DisplaySPG();
    }

    LeftText_[9] = "DECO" ;
    WriteText_Middle_8();//Middle
    DisplayTextMiddle_2(GAS_Str());//Middle
    DisplayBottomTitle(_BottomTitle[22]);//Bottom
}

void Text_A16A(void) {
    DisplayDepth();
    DisplayTLBG();//TL number
    DisplayASCBG();//AR number
    Prepare_GTRnum(GTRnum_buf);
    if(Gas_Num == 1) {
        DisplayPressure();
        DisplayGTR();
    }
    else {
        DisplaySPG();
    }

    DisplayTextMiddle_2(GAS_Str());//Middle
    DisplayBottomTitle(_BottomTitle[22]);//Bottom
}
void Text_A10A(void) {
    char *text;
    text = "VIOLATION";
    WriteText_Title_2(text,5,White,Red);//Top
    DisplayDepth();
    DisplayTLBG();//TL number
    DisplayASCBG();//AR number
    WriteText_Middle_5(136, "^~~GO UP~~^",Red, Black);
    if(Gas_Num == 1) {
        DisplayPressure();
        DisplayGTR();
    }
    else {
        DisplaySPG();
    }
    DisplayTextMiddle_2(GAS_Str());//Middle
    DisplayBottomTitle(_BottomTitle[22]);//Bottom
}

void Text_A12A(void) {
    char *text;
    text = "VIOLATION";
    WriteText_Title_2(text,5,White,Red);//Top
    WriteText_Middle_0();//Middle
    if(Gas_Num == 1) {
        DisplayPressure();
        DisplayGTR();
    }
    else {
        DisplaySPG();
    }
    DisplayTextMiddle_2(GAS_Str());//Middle
    DisplayTLBG();//TL number
    DisplayBottomTitle(_BottomTitle[22]);//Bottom
}
//NORM VIOLATION
void Text_A12A_1(void) {
    DisplayMainTitle(_MainTitle[0]);
    WriteText_Middle_0();//Middle
    if(Gas_Num == 1) {
        DisplayPressure();
        DisplayGTR();
    }
    else {
        DisplaySPG();
    }
    DisplayTextMiddle_2(GAS_Str());//Middle
    DisplayTLBG();//TL number
    DisplayBottomTitle(_BottomTitle[22]);//Bottom
}

void Text_A28A(void) {
    WriteText_Middle_14("~ERROR~ EEPROM");
}

void Text_A28B(void) {
    WriteText_Middle_14("ERROR CALIBRATION");
}

void Text_A28C(void) {
    WriteText_Middle_14("ERROR CHECKSUM");
}

void Text_A28D(void) {
    WriteText_Middle_14("~~ERROR~~ ~~~A TO D~~~");
}

void Text_A28E(void) {
    WriteText_Middle_14("CHANGE BATTERRY");
}

void Text_A28F(void) {
    WriteText_Middle_14("~~ERROR~~ LAST DIVE");
}

void Text_A28G(void) {
    WriteText_Middle_14("~~ERROR~~ ALTITUDE");
}

//Write left text
void WriteLeftText (uint8_t numLine, uint8_t FlagChoose) { //Write text on left with bold text select
    uint8_t i;
    for (i = 0; i < numLine; i++)
    {
        if (i == FlagChoose)
        {
            FontSet = (tChar*)myriad_bold_16;
            LCD_SetColors(Black, Green);
        }
        else
        {
            FontSet = (tChar*)myriad_bold_16;
            LCD_SetColors(White, Black);
        }
        LCD_DisplayStringLine(5,85+(i*23), LeftText_[i]);
    }
}

void Set_Text_Bold(void) {
    FontSet = (tChar*)myriad_bold_16;
    TextColor = LCD_COLOR_BLACK;
}

void Process_PDE_String(u8 Row_) {
    len = 0;
    len = Num2Str(PDE(Row_), _PlanBuffer[Row_].PDE_String, 5);
    _PlanBuffer[Row_].PDE_String[len++] = (UnitType_ > 0 ) ? 0x3f : 0x60 ;//==1 -> M uint |==0 -> FT unit
    _PlanBuffer[Row_].PDE_String[len] = '\0';
}

void Process_NDC_String(u8 Row_) {
    len = 0;
    len += Num2Str(NDC(Row_), _PlanBuffer[Row_].NDC_String, 5);
    _PlanBuffer[Row_].NDC_String[len++] =' ';
    _PlanBuffer[Row_].NDC_String[len++] ='m';
    _PlanBuffer[Row_].NDC_String[len++] ='i';
    _PlanBuffer[Row_].NDC_String[len++] ='n';
    _PlanBuffer[Row_].NDC_String[len]         ='\0';

}
//Update all data in buffer to string
void Update_Plan_Data(void) {
    u8 i = 0;
    for (i = 0; i < 17; i++) {
        Process_PDE_String(i);
        Process_NDC_String(i);
    }
}
void DisplayMainTitle(char* MainTitle) {
    LCD_SetColors(White, Grey);
    FontSet = (ptChar)myriad_bold_17;
    LCD_DisplayStringLine_Center(0,240,0, MainTitle);
}

void WriteLeftText_1(void) {
    u8 i = 0;
    //Update_Plan_Data();
    //Just need update once when need change
    //http://prntscr.com/60q5mv
    if((0==EndPlan)||(0xFF==StartPlan)) {//http://prntscr.com/60q5mv
        Set_Text_Bold();
        LCD_DisplayStringLine(14,109, (!UnitType_) ? "30 FT__0 min" : "9 M__0 min" );
    }
    else {
        for (i = 0; i <= (EndPlan - StartPlan); i++) {
            FontSet=(tChar*)myriad_bold_16;
            if(i == RowHighLight) {
                LCD_SetColors(Black, Green);
            }
            else {
                LCD_SetColors(White, Black);
            }
            //LCD_DisplayStringLine(58,109+(i*22), "__");//Display __ in the middle
            LCD_DisplayStringLine_As_Right(55 , 109+(i*22),_PlanBuffer[i + StartPlan].PDE_String);//
            LCD_DisplayStringLine_As_Right(140, 109+(i*22),_PlanBuffer[i + StartPlan].NDC_String);
        }
    }
}

/*Write Text: Main Title=======================================================================================================*/

void WriteText_Title_1(void) {
    DisplayTemper_Pos3();
    DisplayClock_Pos3();
    DisplayBattery_Pos2();
}
void WriteText_Title_2(char *content,uint16_t _Y, uint16_t textcolor_, u16 backcolor_) {
    LCD_SetColors(textcolor_, backcolor_);
    FontSet = (ptChar)myriad_bold_22;
    LCD_DisplayStringLine_Center(5, 235, _Y, content);
}
//Sub program to display temper location 1: http://prntscr.com/50g3l6
void DisplayTemper_Pos1(void) {
    PrepareTemper();
    LCD_SetColors(White, Grey);
    FontSet = (ptChar)myriad_bold_14;
    LCD_DisplayStringLine_As_Right(73,20, _Temper_buf);//TEMPRATURE
}
void DisplayTemper_Pos2(void) {
    PrepareTemper();
    LCD_SetColors(White,Red);
    FontSet = (ptChar)myriad_bold_14;
    LCD_DisplayStringLine_As_Right(73,20, _Temper_buf);//TEMPRATURE
}
void DisplayTemper_Pos3(void) {
    PrepareTemper();
    LCD_SetColors(Black, White);
    FontSet = (ptChar)myriad_bold_14;
    LCD_DisplayStringLine_Center(36, 77, 7, _Temper_buf);
}

//http://prntscr.com/50l500
void DisplayClock_Pos1(void) {
    PrepareClock(time_buf,1);
    PrepareMidday(midnight);
    LCD_SetColors(White, Grey);
    FontSet = (ptChar)myriad_bold_14;
    if(!hrType) {
        LCD_DisplayChar(101, 20, ':');//Redraw (101,20) to (105,37)
        LCD_DisplayStringLine(106,20,min_buf);
        LCD_DisplayStringLine_As_Right(101,20,hr_buf);
        FontSet = (ptChar)myriad_bold_9;//Can be delete when change the font
        LCD_DisplayStringLine(125,19, Midday);
    }
    else {
        LCD_DisplayStringLine(113,20,min_buf);
        LCD_DisplayStringLine_As_Right(108,20,hr_buf);
        LCD_DisplayChar(108, 20, ':');//Redraw (108,20) to (112,37)
    }
}
void DisplayClock_Pos2(void) {
    PrepareClock(time_buf,1);
    PrepareMidday(midnight);
    LCD_SetColors(White,Red);
    FontSet = (ptChar)myriad_bold_14;
    if(!hrType) {
        LCD_DisplayChar(101, 20, ':');//Redraw (101,20) to (105,37)
        LCD_DisplayStringLine(106,20,min_buf);
        LCD_DisplayStringLine_As_Right(101,20,hr_buf);
        FontSet = (ptChar)myriad_bold_9;//Can be delete when change the font
        LCD_DisplayStringLine(125,19, Midday);
    }
    else {
        LCD_DisplayStringLine(113,20,min_buf);
        LCD_DisplayStringLine_As_Right(108,20,hr_buf);
        LCD_DisplayChar(108, 20, ':');//Redraw (108,20) to (112,37)
    }
}
void DisplayClock_Pos3(void) {
    PrepareClock(time_buf,1);
    PrepareMidday(midnight);
    LCD_SetColors(Black, White);
    FontSet = (ptChar)myriad_bold_14;
    if(!hrType)    {
        LCD_DisplayChar(101, 7, ':');//Redraw (101,7) to (105,24)
        LCD_DisplayStringLine(106,7,min_buf);
        LCD_DisplayStringLine_As_Right(101,7,hr_buf);
        FontSet = (ptChar)myriad_bold_9;
        LCD_DisplayStringLine(125,6, Midday);
    }
    else {
        LCD_DisplayStringLine(113,7,min_buf);
        LCD_DisplayStringLine_As_Right(108,7,hr_buf);
        LCD_DisplayChar(108, 7, ':');//Redraw (108,7) to (112,24)
    }
}


void DisplayBattery_Pos1(void) {
    //Display battery as the level
    if(BATT > 27) {
        battery1(Green);
    }
    else if(BATT < 10) {
        battery1(Red);
    }
    else {
        battery1(Yellow);
    }
    PrepareBattery();
    TextColor = Black;
    FontSet = (ptChar)myriad_bold_12;
    BackColor = (BATT > 27) ? Green: (BATT < 10 ? Red : Yellow);
    LCD_DisplayStringLine_Center(153,191,22,battery_buf);
}

void DisplayBattery_Pos2(void) {
    //Display battery as the level
    if(BATT > 27) {
        battery(Green);
    }
    else if(BATT < 10) {
        battery(Red);
    }
    else {
        battery(Yellow);
    }
    PrepareBattery();
    TextColor = Black;
    FontSet = (ptChar)myriad_bold_12;
    BackColor = (BATT > 27) ? Green: (BATT < 10 ? Red : Yellow);
    LCD_DisplayStringLine_Center(153,191,7, battery_buf);
}

void DisplayBattery_Pos3(void) {
    //Display battery as the level
    if(BATT > 27) {
        battery_red(Green);
    }
    else if(BATT < 10) {
        battery_red(Red);
    }
    else {
        battery_red(Yellow);
    }
    PrepareBattery();
    TextColor = Black;
    FontSet = (ptChar)myriad_bold_11;
    BackColor = (BATT > 27) ? Green: (BATT < 10 ? Red : Yellow);
    LCD_DisplayStringLine_Center(153,195,24,battery_buf);
}
void WriteText_Title_4(char* content, uint8_t Up)
{
    LCD_SetColors(White,Red);
    FontSet = (ptChar)myriad_bold_19;                                                                                        //font 20 is better
    LCD_DisplayStringLine_Center(0, 240, 5, content);
    if(Up) {
        LCD_DisplayStringLine(41,17, "^");
        LCD_DisplayStringLine(185,17, "^");
    }
    else {
        LCD_DisplayStringLine(41,17, "v");
        LCD_DisplayStringLine(185,17, "v");
    }
}
void WriteText_Title_6(uint16_t color_)
{
    TextColor = LCD_COLOR_WHITE;
    BackColor = color_;//Remember implement color
    FontSet = (ptChar)myriad_bold_14;
    LCD_DisplayStringLine(42,20, _Temper_buf);//TEMPRATURE
    if(!hrType)
    {
        LCD_DisplayStringLine(101, 20, ":");//Redraw (101,20) to (105,37)
        LCD_DisplayStringLine(106,20,min_buf);
        LCD_DisplayStringLine_As_Right(101,20,hr_buf);
        FontSet = (ptChar)myriad_bold_9;
        LCD_DisplayStringLine(125,21, Midday);
    }
    else
    {
        LCD_DisplayStringLine(113,20,min_buf);
        LCD_DisplayStringLine_As_Right(108,20,hr_buf);
        LCD_DisplayStringLine(108, 20, ":");//Redraw (108,20) to (112,37)
    }

    FontSet = (ptChar)myriad_bold_11;
    BackColor = Orange_BackGround;
    LCD_DisplayStringLine_Center(153,195,23,battery_buf);

}

/*Write Text: Left Text============================
Always reload the data LeftText_[] arrays and FlagChoose
uint8_t Position : Position from 0..1..2..3..4..5...
uint8_t _Bold    : The text will be bold or normal type
uint8_t content : the data of text will be display
*/

void WriteText_Left_0 (uint8_t Position, char*content) {
    FontSet = (ptChar)myriad_bold_14;
    LCD_SetColors(White, Black);
    LCD_DisplayStringLine_As_Right(125,85+(Position*24), content);
}

void WriteText_Left_2(void) {
    FontSet = (ptChar)myriad_bold_17;
    LCD_SetColors(Red, Black);
    LCD_DisplayStringLine_Center(0, 145, 85, "WARNING");
    FontSet = (ptChar)myriad_bold_14;
    LCD_DisplayStringLine_Center(0, 145, FontHeight*0+110, "THIS FEATURE DELETES ALL DATA FOR CALCULATING REPETITIVE DIVES.");
    LCD_DisplayStringLine_Center(0, 145, FontHeight*6+110, "IT IS INTENDED FOR REUSE OF THE PROPLUS-X BY ANOTHER DIVER");
    LCD_DisplayStringLine_Center(0, 145, FontHeight*12+110, "PRESS (>) TO START.");
}
void WriteText_Left_3( uint16_t _Y) {
    FontSet = (ptChar)myriad_bold_19;                                                                                                                                                                                                                                                                                                                        //font 20 is better
    TextColor = White;
    BackColor = Black;
    LCD_DisplayStringLine_Center(0, 145, _Y, TextLeft3_0);
    FontSet = (ptChar)myriad_bold_17;
    LCD_DisplayStringLine_Center(10,135 ,HeightNow + 5, TextLeft3_1);
}
void WriteText_Left_4(void) {
    TextColor = Green;
    BackColor= Black;
    FontSet = (ptChar)myriad_bold_19;
    LCD_DisplayStringLine_Center(0, 145, 100, TextLeft3_0);
}
void WriteText_Left_5(void) {
    LCD_SetColors(White, Black);
    FontSet = (ptChar)myriad_bold_14;
    LCD_DisplayStringLine_As_Left(0, 145, 95, TextLeft3_0);
}

void WriteText_Left_6(char* text, uint16_t _color) {
    TextColor = _color;
    //BackColor = (OpCode==LOG)? Grey : Black;//Remember implement color
    BackColor = Grey;
    FontSet = (ptChar)myriad_bold_11;
    LCD_DisplayStringLine_Center(0,35,8, text);
}
void UpdateDSATorZplus(void) {
    WriteText_Left_6(DSAT_String, White);//Left top text
}
void DisplayTLBG(void) { //Write TL number
    PrepareTLBG();
    LCD_SetColors(White, Grey);
    FontSet = (ptChar)myriad_bold_11;
    LCD_DisplayStringLine_Center(0,24,80, TL_buf);
    if(TLBG == 100) {
        DisplayPercentLeft(Red,TLBG);
    }
    else if(TLBG<=70) {
        DisplayPercentLeft(Green,TLBG);
    }
    else {
        DisplayPercentLeft(Yellow,TLBG);
    }
}
u8 PreBold[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
u8 Process_Diffirent_Preview(u8 pos, u8 bold) {
    if(PreBold[(pos>>4)-1] == bold) {
        return 0;
    }
    else {
        return 1;
    }
}
void WriteText_Left_8 (uint8_t Position, uint8_t _Bold, char *content) {
    u8 flag = Process_Diffirent_Preview(Position , _Bold) ;
    if(1 == flag) {
        UnSelect_HomeMenu(Position);
        PreBold[(Position>>4)-1] = _Bold;
    }
    FontSet = (tChar*)myriad_bold_16;
    if (1 == _Bold) {
        Select_HomeMenu(Position);
        LCD_SetColors(Black, Green);
    }
    else {
        LCD_SetColors(White, Black);
    }
    LCD_DisplayStringLine(7,85+(((Position>>4)-1)*23), content);//Sel 0x10 >> 4 = 1
}

void WriteText_Left_9 (void) {
    u8 position=0;
    char gasnum[6];
    gasnum[0]='G';
    gasnum[1]='A';
    gasnum[2]='S';
    gasnum[3]=' ';
    gasnum[4]= 0;
    gasnum[5]= 0;
    PO2Value[0]=PO21;
    PO2Value[1]=PO22;
    PO2Value[2]=PO23;
    PO2Value[3]=PO24;
    for(position=0; position<4; position++) {
        if((MENSTAT - 1) == position) {
            if(PO2Value[position]>=160) { //Change the text to red
                ClearPart(BottomTitle_Red);
                DisplayBottomTitle_1((char*)_BottomTitle[0]);//D4C
                LCD_SetColors(Red, White);
            }
            else {
                ClearPart(BottomTitle);
                DisplayBottomTitle(_BottomTitle[1]);
                LCD_SetColors(Black, White);
            }
            FontSet = (ptChar)myriad_bold_22;
            LCD_DisplayStringLine(173, 84,"PO2");
            FontSet = (ptChar)myriad_bold_30;
            LCD_DisplayStringLine_Center(146,240, 113, StrPO2SwitchText(position));
            LCD_SetColors(Black, Green);//Color selected text on the left
        }
        else {
            LCD_SetColors(White, Black);
        }
        Num2Str((u16)(position+1), gasnum+4, 2);
        FontSet = (ptChar)myriad_bold_22;
        LCD_DisplayStringLine(5,84+(position*32), gasnum);
        LCD_DisplayStringLine(90, 84+(position * 32 ), StrFO2SwitchText(position));
        gasnum[5]=0;//remove the last character
    }
}
void WriteText_Left_10( uint16_t _Y) {
    FontSet = (ptChar)myriad_bold_22;                                                                                                                                                                                                                                                                                                                        //font 20 is better
    LCD_SetColors(White,Black);
    LCD_DisplayStringLine_Center(0, 145, _Y, TextLeft3_0);
    FontSet = (ptChar)myriad_bold_17;
    LCD_DisplayStringLine_Center(10,135 ,HeightNow + 15, TextLeft3_1);
}
void WriteText_Left_11(void) {
    FontSet = (ptChar)myriad_bold_22;                                                                                                                                                                                                                                                                                                                        //font 20 is better
    LCD_SetColors(White, Black);
    ProcessCountDown();
    LCD_DisplayStringLine_Center(0, 145, 106, CountDown_Str);//Redraw  (34,106) and (112,132)
    FontSet = (ptChar)myriad_bold_17;
    LCD_DisplayStringLine_Center(10,135 ,152, "COUNTING DOWN");
}
void ProcessCountDown(void) { //process count down bluetooth
    len = 0;
    len += Num2Str((u16)BlueTooth_CountDown, CountDown_Str, 3);
    CountDown_Str[len++] = ' ';
    CountDown_Str[len++] = 's';
    CountDown_Str[len++] = 'e';
    CountDown_Str[len++] = 'c';
    CountDown_Str[len] = '\0';
}
//WriteText Middle====================================================================
void WriteText_Middle_0(void) {
    DrawPart(SurfaceTime);
    FontSet = (ptChar)myriad_bold_19;
    TextColor=White;
    LCD_DisplayStringLine(36,135, "DIVE");//
    DisplayDiveNum();
}
void DisplayDiveNum(void) {
    len=0;
    LCD_SetColors(White, Black);
    FontSet = (ptChar)myriad_bold_38;
    len+=Num2Str(DiveNum, DiveNum_buf,3);
    DiveNum_buf[len] = '\0';
    LCD_DisplayStringLine(115,138, DiveNum_buf);//
}

//FO2 is in binary, if it equals 0 check BITX in FO2FLG, if BITX = 0 then FO2X = OFF, BITX = 1 then FO2 = then Air.
//Otherwise, it will be from 21% (15h) to 100% (64h).

char* FO2_String(u8 FO2Value) {
    len = 0;
    if(FO2Value == 0) {                //FO2 string will be "AIR" with GAS1 only display AIR
        if         ((Gas_Num == 1) ||                                        //With GAS1 always AIR
                    ((Gas_Num == 2)  && (FO2Bit_2 == BIT_2))||
                    ((Gas_Num == 3)  && (FO2Bit_3 == BIT_3))||
                    ((Gas_Num == 4)  && (FO2Bit_4 == BIT_4))||
                    (OpCode == PLAN_MODE)||
                    (OpCode == LOG)) {
            return "AIR";
        }
        else {                                                                //FO2 will be "OFF"
            return "OFF";
        }
    }
    //That mean the FO2 value != 0 always display the value
    else {
        len += Num2Str((u16)FO2Value, FO2num_buf, 5);
        FO2num_buf[len++] ='%';
        FO2num_buf[len] ='\0';
        return FO2num_buf;
    }
}

void FO2PreviewProcess(void) {
    u8 len1 = 0;
    u8 len2 = 0;
    u8 len3 = 0;
    u8 len4 = 0;
    if(FO21 == 0) {
        FO21_buf[0] = 'A';
        FO21_buf[1] = 'I';
        FO21_buf[2] = 'R';
        FO21_buf[3] = '\0';
    }
    if(FO21 != 0) {
        len1 = Num2Str((u16)FO21, FO21_buf, 5);
        FO21_buf[len1++] ='%';
        FO21_buf[len1] ='\0';
    }

    if((FO22 == 0) && (FO2Bit_2 == BIT_2)) {
        FO22_buf[0] = 'A';
        FO22_buf[1] = 'I';
        FO22_buf[2] = 'R';
        FO22_buf[3] = '\0';
    }
    if((FO22 == 0) && (FO2Bit_2 != BIT_2)) {
        FO22_buf[0] = 'O';
        FO22_buf[1] = 'F';
        FO22_buf[2] = 'F';
        FO22_buf[3] = '\0';
    }
    if(FO22 != 0) {
        len2 = Num2Str((u16)FO22, FO22_buf, 5);
        FO22_buf[len2++] ='%';
        FO22_buf[len2] ='\0';
    }

    if((FO23 == 0) && (FO2Bit_3 == BIT_3)) {
        FO23_buf[0] = 'A';
        FO23_buf[1] = 'I';
        FO23_buf[2] = 'R';
        FO23_buf[3] = '\0';
    }
    if((FO23 == 0) && (FO2Bit_3 != BIT_3)) {
        FO23_buf[0] = 'O';
        FO23_buf[1] = 'F';
        FO23_buf[2] = 'F';
        FO23_buf[3] = '\0';
    }
    if(FO23 != 0) {
        len3 = Num2Str((u16)FO23, FO23_buf, 5);
        FO23_buf[len3++] ='%';
        FO23_buf[len3] ='\0';
    }

    if((FO24 == 0) && (FO2Bit_4 == BIT_4)) {
        FO24_buf[0] = 'A';
        FO24_buf[1] = 'I';
        FO24_buf[2] = 'R';
        FO24_buf[3] = '\0';
    }
    if((FO24 == 0) && (FO2Bit_4 != BIT_4)) {
        FO24_buf[0] = 'O';
        FO24_buf[1] = 'F';
        FO24_buf[2] = 'F';
        FO24_buf[3] = '\0';
    }
    if(FO24 != 0) {
        len4 = Num2Str((u16)FO24, FO24_buf, 5);
        FO24_buf[len4++] ='%';
        FO24_buf[len4] ='\0';
    }

}

//When the value of FO2 == 0 --> AIR or OFF --> Display PO2 string -- or blank --> else --> Convert to string number of PO2
char* PO2_String(u8 FO2Value, float PO2Value) {
    len=0;
    //When the SURFACE_MODE or in_buff[5] == 80h/90h http://prntscr.com/5hz179
    //06 Jan 2015 http://prntscr.com/5ouo68
    //22 Jan 2015 http://prntscr.com/5ve34s http://prntscr.com/5ve8gg
    //28 Jan 2015 http://prntscr.com/5xwihc
    if((OpCode == SURFACE_MODE)||(MainMode==0x80)||(MainMode==0x90)||(MainMode==0x10)) {
        return "--";
    }
    else if((MainMode==0x70)&&(NORM_SW_GAS!=OpCode)) {
        return "1.60";
    }
    else if(((MainMode==0x20)||(MainMode==0x40)||(MainMode==0x50))&&(NORM_SW_GAS!=OpCode)) {
        PO2Value = PO2Value/(float)100;
        Ascii_Float2Str(PO2num_buf, &len, PO2Value, 2);
        PO2num_buf[len++] ='\0';
        return PO2num_buf;
    }
    else {
        if(FO2Value == 0) {
            return "- -";//Display nothing
        }
        else {
            PO2Value = PO2Value/(float)100;
            Ascii_Float2Str(PO2num_buf, &len, PO2Value, 2);//Why we can not use the private variables
            if(LOG==OpCode) {
                PO2num_buf[len++] ='!';//ATA prufix
            }
            else {
                len++;
            }
            PO2num_buf[len] ='\0';
            return PO2num_buf;
        }
    }
}

//http://prntscr.com/7w3xlc
char* PO2CurrentString(void) {
    float temp=0;
    if((MainMode==0x80)||(OpCode == SURFACE_MODE)) {
        return "--";
    }
    else {
        if((FO2==0)) {
            return "--";//Display nothing
        }
        else {
            temp = PO2Current/(float)100;
            sprintf(PO2num_buf, "%.2f", temp);
            return PO2num_buf;
        }
    }
}

/*@brief Add thi sub program to draw this just once display
 http://prntscr.com/510pu6
@brief http://prntscr.com/510qr1*/
void DisplayGAS(void) {
    LCD_SetBackColor(Grey);
    FontSet = (ptChar)myriad_bold_12;
    LCD_SetTextColor(White);
    if(FO2>20) {
        LCD_SetTextColor(Green);
    }
    LCD_DisplayStringLine(95,283, "FO2");
    FontSet = (ptChar)myriad_bold_17;
    LCD_DisplayStringLine(94,258, GAS_Str());
}
/*@brief http://prntscr.com/510rv7*/
void DisplayFO2(void) {
    BackColor=Grey;
    TextColor= ((FO2>20) ? Green : White);
    FontSet = (ptChar)myriad_bold_17;
    LCD_DisplayStringLine_Center(34,97,278, FO2_String(FO2));
}
/*@brief http://prntscr.com/510sfb
08/25: add the color warning BUG 93 (81/82 in spec)
PO2 color instruction: http://prntscr.com/89lgux
*/
/*void prepare_FO2num(u8* buf) {
    len;
    if(        ((Gas_Num== 2) && (FO2Bit_2) &&(!FO2_Num))
               ||((Gas_Num==3) && (FO2Bit_3)&&(!FO2_Num))
               ||((Gas_Num==4) && (FO2Bit_4)&&(!FO2_Num))) {
        buf[0] = 'A';
        buf[1] = 'I';
        buf[2] = 'R';
        buf[3] ='\0';
        _FO2check = 1;
    }
    else if( ((Gas_Num==2) && (!FO2Bit_2)&&(!FO2_Num))
             ||((Gas_Num==3) && (!FO2Bit_3)&&(!FO2_Num))
             ||((Gas_Num==4) && (!FO2Bit_4)&&(!FO2_Num))) {
        // LCD_DisplayStringLine_Center(34,97,278, "OFF");
        buf[0] = 'O';
        buf[1] = 'F';
        buf[2] = 'F';
        buf[3] ='\0';
        _FO2check = 2;
    }
    else {
        //prepare_FO2num(FO2num_buf);
        //LCD_DisplayStringLine_Center(34,97,278, FO2num_buf);
        if(FO2_Num == 0)
        {
            buf[0] = 'A';
            buf[1] = 'I';
            buf[2] = 'R';
            buf[3] ='\0';
            _FO2check = 3;
        }
        else
        {
            len = Num2Str(FO2_Num, buf, 5);
            buf[len++] ='%';
            buf[len] ='\0';
            _FO2check = 4;
        }
    }
}
*/

/*
void prepare_PO2num(u8* buf) {
    len = 0;
    if((!FO2_Num) && (Gas_Num > 0)) { //if FO2 == 0
                    buf[0] = '-';
            buf[1] = ' ';
            buf[2] = '-';
            buf[3] ='\0';
    }
    else {
        if(FO2_Num > 0 || Gas_Num > 0) {//<-> FO2num != 0
            Ascii_Float2Str(buf, &len, PO2_Num, 2);//
            buf[len++] ='\0';
        }
        else if((FO2_Num == 0) && (OpCode == 0x12)) {//When the GASX is AIR or OFF, PO2 displays as - -.
            buf[len++] = '-';
            buf[len++] = '-';
            buf[len] = '\0';
        }
                //else if(Gas_Num())
        else {
            buf[len] = '\0';
        }
    }
}
*/
/*@brief Add thi sub program to draw this just once display
* http://prntscr.com/510pu6
*/
void Sub_Middle_1(void) {
    LCD_SetColors(White, Grey);
    FontSet = (ptChar)myriad_bold_12;
    LCD_DisplayStringLine(95,283, "FO2");
    LCD_DisplayStringLine(132,283, "PO2");
}

/*@brief http://prntscr.com/510sfb
void DisplayPO2(void) {
    LCD_SetColors(White, Grey);
    BackColor = 0x8410;
    FontSet = (ptChar)myriad_bold_17;
    LCD_DisplayStringLine_Center(158,209, 278, PO2_String(FO2, PO2));
}*/

/*@brief
Write to internal flash the value of PO2 setting with defined pages
ducthinh90 11/06/2015

void Write_PO2SetVal(void){
FLASH_Unlock();
// Clear pending flags (if any)
FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
//Clear sector 11 for ready writing to flash
FLASH_EraseSector(FLASH_Sector_11, VoltageRange_3);
//Write value to define pages
FLASH_ProgramWord((__IO uint32_t)PO2Add1, (u32)PO2Setting1);
FLASH_ProgramWord((__IO uint32_t)PO2Add2, (u32)PO2Setting2);
FLASH_ProgramWord((__IO uint32_t)PO2Add3, (u32)PO2Setting3);
FLASH_ProgramWord((__IO uint32_t)PO2Add4, (u32)PO2Setting4);
FLASH_Lock();
}
*/

/*@brief http://prntscr.com/510sfb
08/25: add the color warning BUG 93 (81/82 in spec)
PO2 color instruction:
http://prntscr.com/89lgux
*/
void SetPO2Color(void) {
    BackColor = Grey;
    if((OpCode == SURFACE_MODE)||(FO2==0)) {//In AIR or SURFACE display white
        TextColor = White;
    }
    else {
        if(PO2Current >= (PO2SEL)) {
            TextColor = Red;
        }
        else if(PO2Current < (PO2SEL - 20)) {
            TextColor = White;
        }
        else {
            TextColor = Yellow;
        }
    }
}

void DisplayPO2Current(void) {
    SetPO2Color();
    FontSet = (ptChar)myriad_bold_12;
    LCD_DisplayStringLine(132,283, "PO2");
    FontSet = (ptChar)myriad_bold_17;
    LCD_DisplayStringLine_Center(158,209, 278, PO2CurrentString());
}
void DisplayPO2Warning(void) {
    FontSet = (ptChar)myriad_bold_25;
    LCD_SetColors(Yellow, Black);
    LCD_DisplayStringLine(53,135, "PO2 =");
    LCD_DisplayStringLine(135, 135, PO2CurrentString());//PO2_String(FO2, PO2)
}
void DisplayO2Warning(void) {
    LCD_SetColors(Yellow, Black);
    FontSet = (ptChar)myriad_bold_25;
    //LCD_DisplayStringLine(35,135, "O2SAT =");
    //PrepareO2(O2num_buf, 1);
    //LCD_DisplayStringLine(152, 135, O2num_buf);
    sprintf(O2num_buf, "O2 SAT=%d%%", O2SAT);
    LCD_DisplayStringLine_Center(0, LCD_PIXEL_WIDTH, 135, O2num_buf);
}
void DisplayO2Alarm(void) {
    LCD_SetColors(Red, Black);
    FontSet = (ptChar)myriad_bold_25;
    LCD_DisplayStringLine(44, 120, "^  GO UP  ^");
    LCD_DisplayStringLine(55,155, "O2 =");
    PrepareO2();
    LCD_DisplayStringLine(130, 155, O2num_buf);
}
void DisplayO2AlarmSurface(void) {
    LCD_SetColors(Red, Black);
    FontSet = (ptChar)myriad_bold_25;
    LCD_DisplayStringLine(60,135, "O2 = 100%");
}
void DisplayPO2Alarm(void) {
    LCD_SetColors(Red, Black);
    FontSet = (ptChar)myriad_bold_25;
    if(TLBG<100) {
        LCD_DisplayStringLine(44, 120, "^  GO UP  ^");
        LCD_DisplayStringLine(53,155, "PO2 =");
        LCD_DisplayStringLine(135, 155, PO2CurrentString());
    }
    else {
        LCD_DisplayStringLine(53,135, "PO2 =");
        LCD_DisplayStringLine(135, 135, PO2CurrentString());//PO2_String(FO2, PO2)
    }
}
void DisplayTextMiddle_2(char *text) {
    DisplayGAS();
    DisplayFO2();
    DisplayPO2Current();
}
void DisplayTextMiddle_3(uint16_t tcolor) {
    LCD_SetColors(tcolor, Grey);
    FontSet = (ptChar)myriad_bold_57;
    LCD_DisplayStringLine_As_Right(150,63,DepNum_buf);
    LCD_DisplayStringLine(160, 63, ((UnitType_ > 0 ) ? "?" : "`"));
}
void DisplayTextMiddle_4(uint16_t tcolor) {
    TextColor = tcolor;
    BackColor = Black;
    FontSet = (ptChar)myriad_bold_57;
    LCD_DisplayStringLine_As_Right(150,57,DepNum_buf);
    LCD_DisplayStringLine(160, 57, ((UnitType_ > 0 ) ? "?" : "`"));
}

void DisplayEDT(void) {
    PrepareEDT(EDTnum_buf, 1);
    BackColor=Black;
    TextColor= (((MSG==0x05)||(MSG==0x85)) ? Red : White);
    FontSet = (ptChar)myriad_bold_42;
    LCD_DisplayStringLine_As_Right(202,130, EDTnum_buf);
    FontSet = (ptChar)myriad_bold_17;
    LCD_DisplayStringLine(135,170, "EDT");
    FontSet = (ptChar)myriad_bold_12;
    LCD_DisplayStringLine(183,170, "min");
    LCD_FillRect(173, 174, 1, 14, TextColor);
}
void DisplayNDC(void) {
    PrepareNDC(NDCnum_buf, 1);
    BackColor=Black;
    TextColor=((MSG==0x08||MSG==0x88) ? Red : Green);//When enter A23A DECO DIVE TIME change color
    FontSet = (ptChar)myriad_bold_42;
    LCD_DisplayStringLine_As_Right(105, 130, NDCnum_buf);
    FontSet = (ptChar)myriad_bold_12;
    LCD_DisplayStringLine(85,170, "min");
    FontSet = (ptChar)myriad_bold_17;
    LCD_DisplayStringLine(31,170,"NDC");
    LCD_FillRect(75, 174, 1, 14, TextColor);//Line
}
void WriteText_Middle_4(void) {
    DisplayNDC();
    DisplayEDT();
}
void WriteText_Middle_5(uint16_t _Y, char *text, u16 _Textcolor, u16 _backcolor) {
    LCD_SetColors(_Textcolor, _backcolor);
    FontSet = (ptChar)myriad_bold_25;
    LCD_DisplayStringLine_Center(0,240,_Y, text);//y=125
}
void WriteText_Middle_6(char *text) {
    LCD_SetColors(Blue, Black);
    FontSet = (ptChar)myriad_bold_38;
    LCD_DisplayStringLine_Center(40,200,210, text);
}
void DisplayStopMin(void) {
    LCD_SetColors(White, Black);
    FontSet = (ptChar)myriad_bold_42;
    PrepareSafetyTimeMin();
    LCD_DisplayStringLine_As_Right(153, 145, SafetyTimeMin_buf);
    FontSet = (ptChar)myriad_bold_15;
    LCD_DisplayStringLine(123,122,"STOP");
    FontSet = (ptChar)myriad_bold_12;
    LCD_DisplayStringLine(135,177,"min:sec");
    //Display colon once
    FontSet = (ptChar)myriad_bold_42;
    LCD_DisplayStringLine(153, 145, ":");
}
void DisplayStopSec(void) {
    LCD_SetColors(White, Black);
    FontSet = (ptChar)myriad_bold_42;
    PrepareSafetyTimeSec();
    LCD_DisplayStringLine(164, 145, SafetyTimeSec_buf);
}
void WriteText_Middle_7(void) {
    DisplaySafetyStop();
    DisplayStopMin();
    DisplayStopSec();
}

void DisplayDeepStop(void) {
    PrepareMaxDepth(maxDepth_buf, 0);
    LCD_SetColors(Green, Black);
    FontSet = (ptChar)myriad_bold_42;
    LCD_DisplayStringLine_As_Right(115, 145,maxDepth_buf);
    LCD_SetColors(White, Black);
    FontSet = (tChar*)myriad_bold_16;
    LCD_DisplayStringLine_As_Right(118,122,"DEEP");
}

void DisplaySafetyStop(void) {
    LCD_SetColors(Green, Black);
    FontSet = (ptChar)myriad_bold_42;
    LCD_DisplayStringLine_As_Right(113, 145,StrSafetyDepth());
    LCD_SetColors(White, Black);
    FontSet = (tChar*)myriad_bold_16;
    LCD_DisplayStringLine_As_Right(118,122,"SAFETY");
}
void WriteText_Middle_7B(void) {
    DisplayDeepStop();
    DisplayStopMin();
    DisplayStopSec();
}

void WriteText_Middle_7C(void) {
    DisplaySafetyStop();
    DisplayStopMin();
    DisplayStopSec();
}

DoubleString DecoString[6]= {
    {"10`","3?"},
    {"20`","6?"},
    {"30`","9?"},
    {"40`","12?"},
    {"50`","15?"},
    {"60`","18?"}
}   ;
void PrepareDecoDepth(void) {
    u8 i = 0;
    for(i=1; i<7; i++) {
        if(DESD == i) {
            DecoDepth_buf = (!UnitType_) ? DecoString[i-1].String_1: DecoString[i-1].String_2;
        }
    }
}
s16 testvar = 0;
u16 DECOColor(void) {
    testvar=((s16)DEPTH-(s16)((DESD*10)));
    if(10<((s16)DEPTH-(s16)((DESD*10)))) {
        LCD_SetTextColor(Yellow);
    }
    else if(0<((s16)DEPTH-(s16)((DESD*10)))) {
        LCD_SetTextColor(Green);
    }
    else {
        LCD_SetTextColor(Red);
    }
    return TextColor;
}
//http://prntscr.com/80c6h6
void DisplayDECODepth(void) {
    PrepareDecoDepth();
    LCD_SetColors(DECOColor(), Black);
    FontSet = (ptChar)myriad_bold_42;
    LCD_DisplayStringLine_Center(24,123,145,DecoDepth_buf);
    FontSet = (ptChar)myriad_bold_15;
    LCD_DisplayStringLine_As_Right(115,122,"DECO");
    //Clear area
    DrawPart(LineVertical_2);
}

void DisplayDECOTime(void) {
    len =0;
    len += Num2Str(DEST, DecoTime_buf, 2);
    DecoTime_buf[len] = '\0';
    LCD_SetColors(DECOColor(), Black);
    FontSet = (ptChar)myriad_bold_15;
    LCD_DisplayStringLine(123,122,"STOP");
    //always white
    LCD_SetColors(White, Black);
    FontSet = (ptChar)myriad_bold_42;
    LCD_DisplayStringLine_As_Right(185, 145,DecoTime_buf);
    FontSet = (ptChar)myriad_bold_12;
    LCD_DisplayStringLine(190,143,"min");
    //Clear area
    DrawPart(LineVertical_2);
}
void WriteText_Middle_8(void) {
    DisplayDECODepth();
    DisplayDECOTime();
}

void WriteText_Middle_9(void) {
    LCD_SetColors(Blue, Black);
    FontSet = (ptChar)myriad_bold_12;
    LCD_DisplayStringLine(157,97, "hr:min");//
    FontSet = (ptChar)myriad_bold_38;
    LCD_DisplayStringLine(141,62, ":");//Redraw (148,53) and (158,99)
    FontSet = (ptChar)myriad_bold_19;
    LCD_DisplayStringLine(36,61, "SURF");//
    DisplaySurfHr();
    DisplaySurfMin();
}
void DisplaySurfHr(void) {
    LCD_SetColors(Blue, Black);
    FontSet = (ptChar)myriad_bold_38;
    LCD_DisplayStringLine_As_Right(141,62, SurfHr_buf);//
}
void DisplaySurfHrCompass(void) {
    LCD_SetColors(Blue, Black);
    FontSet = (ptChar)myriad_bold_38;
    LCD_DisplayStringLine_As_Right(141,52, SurfHr_buf);//
}

void DisplaySurfMin(void) {
    LCD_SetColors(Blue, Black);
    FontSet = (ptChar)myriad_bold_38;
    LCD_DisplayStringLine(151,62,SurfMin_buf);//
}
void DisplaySurfMinCompass(void) {
    LCD_SetColors(Blue, Black);
    FontSet = (ptChar)myriad_bold_38;
    LCD_DisplayStringLine(151,52,SurfMin_buf);//
}

void WriteText_Middle_10(uint16_t tcolor) { //PSI num
    LCD_SetColors(Blue, Black);
    FontSet = (ptChar)myriad_bold_38;
    LCD_DisplayStringLine_Center(25,134, 190, pressure_buf);
    FontSet = (ptChar)myriad_bold_15;
    if(UnitType_) {
        LCD_DisplayStringLine(98,229, "BAR");
    }
    else {
        LCD_DisplayStringLine(98,229, "PSI");
    }
}

void WriteText_Middle_11(uint16_t tcolor) { //GTR num
    TextColor = tcolor;
    BackColor = Orange_BackGround;
    FontSet = (ptChar)myriad_bold_38;
    LCD_DisplayStringLine_Center(134,213,190, GTRnum_buf);
    FontSet = (ptChar)myriad_bold_15;
    LCD_DisplayStringLine(140,229, "GTR");
    FontSet = (ptChar)myriad_bold_12;
    LCD_DisplayStringLine(183,229, "min");
}
void WriteText_Middle_12(uint16_t bcolor) { //NDC number
    TextColor = LCD_COLOR_WHITE;
    BackColor = bcolor;
    FontSet = (ptChar)myriad_bold_12;
    LCD_DisplayStringLine(85,170, "min");
    FontSet = (ptChar)myriad_bold_17;
    LCD_DisplayStringLine(31,170,"NDC");
    FontSet = (ptChar)myriad_bold_42;
    LCD_DisplayStringLine_Center(21,123, 117, NDCnum_buf);
}
void WriteText_Middle_13(uint16_t bcolor) { //EDT num
    TextColor = LCD_COLOR_WHITE;
    BackColor = bcolor;
    FontSet = (ptChar)myriad_bold_42;
    LCD_DisplayStringLine_Center(124,217,117, EDTnum_buf);
    FontSet = (ptChar)myriad_bold_17;
    LCD_DisplayStringLine(135,170, "EDT");
    FontSet = (ptChar)myriad_bold_12;
    LCD_DisplayStringLine(183,170, "min");
}
void WriteText_Middle_14(char* text) {
    FontSet = (ptChar)myriad_bold_30;
    LCD_SetColors(White, Red);
    LCD_DisplayStringLine_Center(0, 240, 100, text);
}
void DisplayTextMiddle15(void) {
    FontSet = (ptChar)myriad_bold_22;
    LCD_SetTextColor(White);
    BackColor = Orange_BackGround;
    LCD_DisplayStringLine(9, 80, "GAS");
    LCD_DisplayStringLine(85, 80, "FO2");
    LCD_DisplayStringLine(175,80, "PO2");
}
char* StrFO2SWGAS1(void) {
    if(FO21 == 0) {
        return "AIR";
    }
    else {
        return FO2_String(FO21);
    }
}
char* StrFO2SWGAS2(void) {
    if((FO22 == 0) && ((FO2FLG & BIT_2) == BIT_2)) {
        return "AIR";
    }
    else if((FO22 == 0) && ((FO2FLG & BIT_2) != BIT_2)) {
        return "OFF";
    }
    else {
        return FO2_String(FO22);
    }
}

char* StrFO2SWGAS3(void) {
    if((FO23 == 0) && ((FO2FLG & BIT_3) == BIT_3)) {
        return "AIR";
    }
    else if((FO23 == 0) && ((FO2FLG & BIT_3) != BIT_3)) {
        return "OFF";
    }
    else {
        return FO2_String(FO23);
    }
}
char* StrFO2SWGAS4(void) {
    if((FO24 == 0) && ((FO2FLG & BIT_4) == BIT_4)) {
        return "AIR";
    }
    else if((FO24 == 0) && ((FO2FLG & BIT_4) != BIT_4)) {
        return "OFF";
    }
    else {
        return FO2_String(FO24);
    }
}
//SWITCH MENU D4B
char* StrFO2SwitchText(u8 Position) {
    switch (Position) {
    //Case GAS1
    case 0:
        return StrFO2SWGAS1();
        break;
    //Case GAS2
    case 1:
        return StrFO2SWGAS2();
        break;
    //Case GAS3
    case 2:
        return StrFO2SWGAS3();
        break;
    //Case GAS4
    case 3:
        return StrFO2SWGAS4();
        break;
    //Defalult
    default:
        return 0;
        break;
    }
}
char* StrPO2SwitchText(u8 Position) {
    switch (Position) {
    //Case GAS1
    case 0:
        return PO2_String(FO21, PO21);
        break;
    //Case GAS2
    case 1:
        return PO2_String(FO22, PO22);
        break;
    //Case GAS3
    case 2:
        return PO2_String(FO23, PO23);
        break;
    //Case GAS4
    case 3:
        return PO2_String(FO24, PO24);
        break;
    //Defalut
    default:
        return 0;
        break;
    }
}

void DisplayRunTime(void) {
    LCD_SetColors(Green, Black);
    FontSet = (ptChar)myriad_bold_42;
    Num2Str(RTM, RTM_buf, 3);
    LCD_DisplayStringLine_As_Right(110,130,RTM_buf);
    FontSet = (ptChar)myriad_bold_12;
    LCD_DisplayStringLine(75,170, "min");
}
//Display Run or Stop text
void DisplayRunStatus(void) {
    LCD_SetColors(Green, Black);
    FontSet = (ptChar)myriad_bold_17;
    LCD_DisplayStringLine_As_Right(54,170,(((MORFLG & BIT_7) == BIT_7)) ? "RUN":"STOP");
    LCD_FillRect(60, 174, 1, 14, TextColor);
}


/*Write Text: Right Text============================*/
void WriteText_Right_0(void) { //Personal information
    LCD_SetColors(Black, White);
    FontSet = (ptChar)myriad_bold_19;
    LCD_DisplayStringLine_Center(0,240,72, &MyInfo_Data[0][0]);//Name
    FontSet = (ptChar)myriad_bold_15;
    LCD_DisplayStringLine(5,105, &MyInfo_Data[0][0]+17);//Address
    LCD_DisplayStringLine(5,122, &MyInfo_Data[0][0]+17*2);
    LCD_DisplayStringLine(5,145, &MyInfo_Data[0][0]+17*3);
    LCD_DisplayStringLine(5,162, &MyInfo_Data[0][0]+17*4);
    LCD_DisplayStringLine(5,190, &MyInfo_Data[0][0]+17*5);
    LCD_DisplayStringLine(5,207, &MyInfo_Data[0][0]+17*6);
    LCD_DisplayStringLine(5,222, &MyInfo_Data[0][0]+17*7);
    LCD_DisplayStringLine(5,260, &MyInfo_Data[0][0]+17*8);
    LCD_DisplayStringLine(5,277, &MyInfo_Data[0][0]+17*9);
}

void WriteText_Right_1(char* content, uint16_t _TextColor) {
    TextColor = _TextColor;
    //FontSet = (ptChar)myriad_bold_15;
    BackColor = White;
    //LCD_DisplayStringLine_Center(145,240,87, "VIEW ONLY");
    FontSet = (ptChar)myriad_bold_14;
    LCD_DisplayStringLine_Center(145,240,117,content);
}
void ProcessSerialNum(void) {
    Serialnum_buf[0] = 'S';
    Serialnum_buf[1] = 'N';
    Serialnum_buf[2] = ' ';
    Serialnum_buf[3] = '-';
    Serialnum_buf[4] = ' ';
    Num2Str(SN1>>4, Serialnum_buf+5, 1);
    Num2Str((SN1&0x0F), Serialnum_buf+6, 1);
    Num2Str(SN2>>4, Serialnum_buf+7, 1);
    Num2Str((SN2&0x0F), Serialnum_buf+8, 1);
    Num2Str(SN3>>4, Serialnum_buf+9, 1);
    Num2Str((SN3&0x0F), Serialnum_buf+10, 1);
    Serialnum_buf[11]='\0';
}
void ProcessBluetoothNum(void) {
    BluetoothNum_buf[0] = 'E';
    BluetoothNum_buf[1] = 'R';
    Num2Str(SN1>>4, BluetoothNum_buf+2, 1);
    Num2Str((SN1&0x0F), BluetoothNum_buf+3, 1);
    Num2Str(SN2>>4, BluetoothNum_buf+4, 1);
    Num2Str((SN2&0x0F), BluetoothNum_buf+5, 1);
    Num2Str(SN3>>4, BluetoothNum_buf+6, 1);
    Num2Str((SN3&0x0F), BluetoothNum_buf+7, 1);
    BluetoothNum_buf[8]='\0';
}

void ProcessResetCode(void) {
    if(ReCoHigh < 10) {
        Reset_buf_high[0] = '0';
        Num2Str(ReCoHigh,Reset_buf_high + 1,2);
        Reset_buf_high[2] = '\0';
    }
    else {
        Num2Str(ReCoHigh,Reset_buf_high,2);
        Reset_buf_high[2] = '\0';
    }
    if(ReCoLow < 10) {
        Reset_buf_low[0] = '0';
        Num2Str(ReCoLow,Reset_buf_low + 1,2);
        Reset_buf_low[2] = '\0';
    }
    else {
        Num2Str(ReCoLow,Reset_buf_low,2);
        Reset_buf_low[2] = '\0';
    }
}

void ProcessFirmwareRev(void) { //Process Firmware Revision
    FirmRev_buf[0] = 'R';
    FirmRev_buf[1] = 'E';
    FirmRev_buf[2] = 'V';
    FirmRev_buf[3] = ' ';
    FirmRev_buf[4] = '-';
    Num2Str((u16)rev_1, FirmRev_buf+5, 2);
    FirmRev_buf[6]= rev_2;
    Num2Str((u16)(Fw_version>>4), FirmRev_buf+7, 2);
    Num2Str((u16)(Fw_version & 0x0F), FirmRev_buf+8, 2);
    FirmRev_buf[9]= '\0';
}

void WriteText_Right_2(void) {
    ProcessSerialNum();
    ProcessBluetoothNum();
    Process_DMY_data(MD);
    LCD_SetColors(Black, White);
    FontSet = (ptChar)myriad_bold_12;
    LCD_DisplayStringLine_Center(146,240,90, "PROPLUS-X");
    LCD_DisplayStringLine_Center(146,240,132, Serialnum_buf);
    LCD_DisplayStringLine_Center(156,230,170, "FIRMWARE");
    LCD_DisplayStringLine_Center(156,230,184, FirmRev_buf);
    LCD_DisplayStringLine_Center(146,240,210, "LAST CAL - ");
    LCD_DisplayStringLine_Center(146,240,224, MD_buf);
    LCD_DisplayStringLine_Center(146,240,249, "BLUETOOTH DEVICE NAME");
    LCD_DisplayStringLine_Center(146,240,277, BluetoothNum_buf);
}

void WriteText_Right_3(void) {
    LCD_SetColors(Black, White);
    FontSet = (ptChar)myriad_bold_15;
    LCD_DisplayStringLine_Center(146, 240, 90, "RESET CODE");
    FontSet = (ptChar)myriad_bold_22;
    LCD_DisplayStringLine_As_Right(193, 127, Reset_buf_high);
    LCD_DisplayStringLine(193, 127, Reset_buf_low);
}
void WriteText_Right_4(void) {
    FontSet = (tChar*)myriad_bold_16;
    TextColor = Black;
    BackColor = ASSEMBLE_RGB(56, 56, 56);
    LCD_DisplayStringLine_Center(145, 240, 189, TextRight4);
    FontSet = (ptChar)myriad_bold_12;
    LCD_DisplayStringLine_As_Left(150, LCD_PIXEL_WIDTH, 195 + 1*22, TextRight4_0);
    LCD_DisplayStringLine_As_Left(150, LCD_PIXEL_WIDTH, 195 + 2*22, TextRight4_1);
    LCD_DisplayStringLine_As_Left(150, LCD_PIXEL_WIDTH, 195 + 3*22, TextRight4_2);
}

void WriteText_Right_5(char*content, uint16_t TextColor_, uint16_t BackColor_) {
    TextColor = TextColor_;
    FontSet = (ptChar)myriad_bold_14;
    BackColor = BackColor_;
    LCD_DisplayStringLine_Center(145,240,90,content);
}

void WriteText_Right_6(char* content) {
    LCD_SetColors(Black, White);
    FontSet = (ptChar)myriad_bold_22;
    LCD_DisplayStringLine_Center(145,240,103, content);
}

void WriteText_Right_7(char* content) {
    LCD_SetColors(Black, White);
    FontSet = (ptChar)myriad_bold_14;
    LCD_DisplayStringLine_Center(150,240,190,content);
}
void WriteText_Right_8(void)
{
    LCD_SetColors(Black, White);
    FontSet = (ptChar)myriad_bold_22;
    LCD_DisplayStringLine_Center(146,238,103, TextRight4);
    FontSet = (tChar*)myriad_bold_16;
    LCD_DisplayStringLine_Center(146,238,130, TextRight4_0);
}
void WriteText_Right_9(void) { //H9A, H9B Month/Day/Year type
    LCD_SetColors(Black, White);
    FontSet = (ptChar)myriad_bold_22;
    LCD_DisplayStringLine(174, 103, ".");//'.'
    LCD_DisplayStringLine(206, 103, ".");//'.'
    if(MD) {
        LCD_DisplayStringLine_As_Right(174, 103, Day_buf);//Redraw (148,103) and (174,129)
        LCD_DisplayStringLine_Center(180, 206, 103, Month_buf);//Redraw (180,103) and (206,129)
    }
    else {
        LCD_DisplayStringLine_As_Right(174, 103, Month_buf);
        LCD_DisplayStringLine_Center(180, 206, 103, Day_buf);
    }
    LCD_DisplayStringLine(212, 103,Year_buf);//Redraw (212,103) and (238,129)

    FontSet = (tChar*)myriad_bold_16;
    LCD_DisplayStringLine_Center(146,238,130, DMY_String);
}

void WriteText_Right_10(void) {
    TextColor = LCD_COLOR_BLACK;
    FontSet = (ptChar)myriad_bold_14;
    LCD_DisplayStringLine_Center(146,238,130, TextRight4_2);
}
void WriteText_Right_11(char *text)
{
    LCD_SetColors(White,Black);
    FontSet = (ptChar)myriad_bold_11;
    LCD_DisplayStringLine(217,9, text);
}
void UpdateCFicon(void) {
    WriteText_Right_11(Coseva_StringCF);//Right top text
}
void DisplayASCBG(void) { //Display the right value AR
    PrepareASCBG();
    LCD_SetColors(White, Grey);
    FontSet = (ptChar)myriad_bold_11;
    LCD_DisplayStringLine_Center(218,240,80, AR_buf);
    if(ASCBG == 100) {
        DisplayPercentRight(Red,ASCBG);
    }
    else if(ASCBG<=70) {
        DisplayPercentRight(Green,ASCBG);
    }
    else {
        DisplayPercentRight(Yellow,ASCBG);
    }
}
void WriteText_Right_13(uint16_t _Y, char* buffer) {
    LCD_SetColors(Black, White);
    FontSet = (ptChar)myriad_bold_14;
    LCD_DisplayStringLine_Center(146,238,_Y, TextRight4);
    FontSet = (ptChar)myriad_bold_22;
    LCD_DisplayStringLine_Center(146,238,HeightNow, buffer);
}
void WriteText_Right_14(uint16_t X, uint16_t Y) {
    LCD_SetColors(Black, White);
    FontSet = (ptChar)myriad_bold_12;
    LCD_DisplayStringLine_As_Left(X, LCD_PIXEL_WIDTH, Y, TextRight4_0);
    LCD_DisplayStringLine_As_Left(X, LCD_PIXEL_WIDTH, Y + 17, TextRight4_1);
    LCD_DisplayStringLine_As_Left(X, LCD_PIXEL_WIDTH, Y + 34, TextRight4_2);
    LCD_DisplayStringLine_As_Left(X, LCD_PIXEL_WIDTH, Y + 51, TextRight4_3);

}
void WriteText_Right_15(void) {
    LCD_SetColors(Black, White);
    FontSet = (ptChar)myriad_bold_38;
    LCD_DisplayStringLine_Center(146,240,100, DepNum_buf);//Warning
    //FontSet = &((ptChar)myriad_bold_22);
    //if(UnitType_) {
    //    LCD_DisplayStringLine_Center(152,234,140,"M");
    // }
    //else {
    //    LCD_DisplayStringLine_Center(152,234,140,"FT");
    //}
}
void WriteText_Right_16(void) {
    LCD_SetColors(Black, White);
    FontSet = (ptChar)myriad_bold_38;
    LCD_DisplayStringLine_Center(146,240,215, "2:00");
    FontSet = (tChar*)myriad_bold_16;
    LCD_DisplayStringLine_Center(146,240,260,"min:sec");
}

void WriteText_Right_17 (u16 Position, char*content, uint16_t _textcolor, uint16_t _backcolor) {
    TextColor = _textcolor;
    BackColor= _backcolor;
    FontSet = (ptChar)myriad_bold_14;
    LCD_DisplayStringLine(154,85+(Position*24), content);
    LCD_SetColors(Black, White);
    LCD_DisplayStringLine(142,85+(Position*24), "=");
}

void WriteText_Right_18(void) {                //HH, MM H11A, H11B
    TextColor = LCD_COLOR_BLACK;
    FontSet = (ptChar)myriad_bold_22;
    if(!hrType) { //if hrType == 0
        LCD_DisplayStringLine(207, 103, (!midnight) ? "{" :"|");// Redraw AM or PM (207,103) and (236,129)
        LCD_DisplayStringLine(173, 103, ":");//Width = 6 , Height = 26
        LCD_DisplayStringLine_As_Right(173, 103, hr_buf);//Redraw (147,103)  and (173,129)
        LCD_DisplayStringLine(179, 103, min_buf);//Redraw (179,103) and (205,129)
    }
    else {
        LCD_DisplayStringLine(189, 103, ":");//Width = 6 , Height = 26
        LCD_DisplayStringLine_As_Right(189, 103, hr_buf);//Redraw (163,103) and (189,129)
        LCD_DisplayStringLine(195, 103, min_buf);//Redraw (195,103) and (221,129)
    }
}

void WriteText_Right_19(uint16_t _Y, char*content1) {
    LCD_SetColors(Black, White);
    FontSet = (ptChar)myriad_bold_12;
    LCD_DisplayStringLine_Center(145,240,_Y, content1);
}

void WriteText_Right_23(uint16_t _Y, char* content1) {
    TextColor = LCD_COLOR_BLACK;
    FontSet = (ptChar)myriad_bold_14;
    LCD_DisplayStringLine_Center(145,240,_Y, content1);
}

void WriteText_Right_20(uint16_t X, uint16_t Y, char* text) {
    TextColor = White;
    BackColor = Orange_BackGround;
    FontSet = (ptChar)myriad_bold_12;
    LCD_DisplayStringLine(X, Y, text);
}
void WriteText_Right_21(void) {
    FontSet = (tChar*)myriad_bold_16;
    TextColor = Black;
    BackColor = ASSEMBLE_RGB(56, 56, 56);
    LCD_DisplayStringLine_Center(145, 240, 186, TextRight4);
    FontSet = (ptChar)myriad_bold_12;
    LCD_DisplayStringLine_Center(145, 240, 202, "(TIME, DEPTH)");
    LCD_DisplayStringLine_As_Left(150, LCD_PIXEL_WIDTH, 200 + 1*22, TextRight4_0);
    LCD_DisplayStringLine_As_Left(150, LCD_PIXEL_WIDTH, 200 + 2*22, TextRight4_1);
    LCD_DisplayStringLine_As_Left(150, LCD_PIXEL_WIDTH, 200 + 3*22, TextRight4_2);
}

void WriteText_Right_22(void) {
    LCD_SetColors(Black, White);
    FontSet = (ptChar)myriad_bold_22;
    CheckStopTime();
    CheckStopDepth();
    LCD_DisplayStringLine_Center(145,240,90, SafetyStopTime_Str);
    LCD_DisplayStringLine_Center(145,240,140, SafetyStopDepth_Str);
}

/*Write Text: Bottom*/
void DisplayBottomTitle(char* content) {
    LCD_SetColors(White, Grey);
    FontSet = (ptChar)myriad_bold_11;
    LCD_DisplayStringLine_Center(0, 240, 305, content);
}

void DisplayBottomTitle_1(char* content) {
    LCD_SetColors(White, Red);
    FontSet = (ptChar)myriad_bold_11;
    LCD_DisplayStringLine_Center(0, 238, 303, content);
}

/*Write Text: Main Menu*/

void DisplayMainMenu(char* content, uint16_t colour) {
    LCD_SetColors(colour, Grey);
    FontSet = (ptChar)myriad_bold_22;
    //BackColor = ASSEMBLE_RGB(126, 119, 117);
    LCD_DisplayStringLine_Center(0,240,38, content);
}
/**/
void PrepareO2(void) {                                                                                                                                                                                                           //Ducthinh90 fixed
    // len = 0;
    // if(flat)
    // {
    //Case DIVE MENU VIOLATION
    //Jan06 2015 http://prntscr.com/5ouo68
    if(((OpCode==DIVE_MENU)&&(MainMode==0x80))||(FO2==0)) {
        //buf[len++] ='-';
        //buf[len++] ='-';
        //buf[len] ='\0';
        sprintf(O2num_buf,"--");
    }
    else {
        //len += Num2Str(O2SAT, buf, 5);
        //buf[len++] ='%';
        //buf[len] ='\0';
        sprintf(O2num_buf,"%d%%", O2SAT);
    }
    // }
    //else {
    //buf[0] = 'O';
    //uf[1] = 'F';
    //buf[2] = 'F';
    //buf[3] ='\0';
    //  sprintf(O2num_buf,"OFF");
    // }
}
/*
@brief Prepare NDC number string to display
* u8 *buf = NDCnum_buf
* flag == 1: no include unit letter
* flag == 0: include unit after value
*/
void PrepareNDC(char* buf, uint8_t flag)                                                                                                                                                                                                                                                                       //Ducthinh90 fixed
{
    len = 0;
    if(flag)
    {
        len += Num2Str(NDC_, buf, 5);
        buf[len] ='\0';
    }
    else {
        //When VIOLATION OC = DIVE MODE and buff[5] == 0x80 A11B
        if((OpCode == DIVE_MENU)&&(MainMode==0x80)) {
            buf[len++] ='-';
            buf[len++] ='-';
            buf[len++] =']';
            buf[len] ='\0';
        }
        else {
            len += Num2Str(NDC_, buf, 5);
            buf[len++] =']';
            buf[len] ='\0';
        }
    }
}
//Buffer in EDTnum_buf
//flag = 0 : include "min" after the string
//flag =1 : display the value of EDT only
//Nov.14.2015 http://prntscr.com/92d4rd
void PrepareEDT(char *buf, uint8_t flag) { //DiveTime number                                                                                                                                                                                                                                                               //Ducthinh90 fixed
    u16 EDTTemp = EDT;
    len = 0;
    if(EDTTemp == 0) { //if 0 display OFF
        if((OpCode == DIVE_MODE )||(OpCode == DIVE_MENU)||(LOG== OpCode)) { //incase this http://prntscr.com/512m1t
            buf[0] = '0';
            buf[1] = ']';
            buf[2] = '\0';
        }
        else {
            buf[0] = 'O';
            buf[1] = 'F';
            buf[2] = 'F';
            buf[3] ='\0';
        }
    }
    //When EDT != 0
    else {
        if(flag) {
            len += Num2Str(EDTTemp, buf, 5);
            buf[len] ='\0';
        }
        //Include the "min" after
        else {
            len += Num2Str(EDTTemp, buf, 5);
            buf[len++] =']';
            buf[len] ='\0';
        }
    }
}
void prepare_DTRNum(char*buf, uint8_t flag)                                                                                                                                                                                                                                                                         //Ducthinh90 fixed
{
    u8 DTRTemp = DTR;
    len = 0;
    if(DTRTemp == 0) { //if 0 display OFF
        buf[0] = 'O';
        buf[1] = 'F';
        buf[2] = 'F';
        buf[3] ='\0';
    }
    else {
        if(flag) {
            len += Num2Str(DTRTemp, buf, 5);
            buf[len] ='\0';
        }
        else {
            len += Num2Str(DTRTemp, buf, 5);
            buf[len++] =']';
            buf[len] ='\0';
        }
    }
}
void PrepareAlarmTLBG(char*buf, uint8_t flat) {                                                                                                                                                                                                                                                                        //Ducthinh90 fixed
    u8 TLBGTemp = TLBG;
    len = 0;
    if(TLBGTemp == 0) { //if 0 display OFF
        buf[0] = 'O';
        buf[1] = 'F';
        buf[2] = 'F';
        buf[3] ='\0';
    }
    else {//TLBG != 0
        if(flat == 1) {
            len += Num2Str(TLBGTemp, buf, 5);
            buf[len] ='\0';
        }
        else {
            len += Num2Str(TLBGTemp, buf, 5);
            buf[len++] ='%';
            buf[len] ='\0';
        }
    }
}
/*flat: include the unit after or not*/
void PrepareDepth(char* buf, uint8_t flat) {
    float DepNum = DEPTH;
    len = 0;
    if(DepNum == 0) { //if 0 display OFF
        buf[0] = 'O';
        buf[1] = 'F';
        buf[2] = 'F';
        buf[3] ='\0';
    }
    else {
        if(flat) {
            if(!ALARM_SET_Flag()) {
                DepNum = ImperialConvert(DepNum);
            }
            if((UnitType_ > 0) && (DepNum < 100)) { //Metric and value smaller than 3 digits
                Ascii_Float2Str(buf, &len , (float) DepNum, 1);
            }
            else {
                Ascii_Float2Str(buf, &len , (float) DepNum, 0);
            }
            buf[len++] = (UnitType_ > 0 ) ? 0x3f : 0x60 ;//==1 -> M uint |==0 -> FT unit
            buf[len] ='\0';
        }
        else {
            if(!ALARM_SET_Flag()) {
                DepNum = ImperialConvert(DepNum);
            }
            if((UnitType_ > 0) && (DepNum < 100)) { //Metric and value smaller than 3 digits
                Ascii_Float2Str(buf, &len , (float) DepNum, 1);
            }
            else {
                Ascii_Float2Str(buf, &len , (float) DepNum, 0);
            }
        }
        buf[len] ='\0';
    }
}

void PrepareMaxDepth(char* buf, uint8_t flat) {
    float temp = maxDepth;
    len = 0;
    //When enter the DIVE MENU / DS PREVIEW down it a half
    //if(OpCode == DIVE_MENU && MENSTAT == 0x41) {//http://prntscr.com/58qkyt
    if ((((OpCode == DIVE_MENU) && (MENSTAT == 0x41)) ||
            ((OpCode == DIVE_MODE) && (MainMode== 0x30) && ((DSSTAT & BIT7) == BIT7))) ||
            (((OpCode == DIVE_MODE) && (MENSTAT == 0x41)) ||
             ((OpCode == DIVE_MODE) && (MainMode== 0x30)&&((DSSTAT & BIT7) == BIT7)))) {
        temp = temp/2;
    }
    if(flat > 0) { //if flat == 1
        temp = (float)ImperialConvert(temp);
        if((UnitType_ > 0) && (temp < 100)) { //Metric and value smaller than 3 digits
            Ascii_Float2Str(buf, &len , temp, 1);
            buf[len] ='\0';
        }
        else {
            len += Num2Str((u16)temp, buf, 2);
            buf[len] ='\0';
        }
    }
    else {
        temp = ImperialConvert(temp);
        if((UnitType_ > 0) && (temp < 100)) { //Metric and value smaller than 3 digits
            Ascii_Float2Str(buf, &len , temp, 1);
            buf[len++] = (UnitType_) ? 0x3f : 0x60 ;//==1 -> M uint |==0 -> FT unit
            buf[len] ='\0';
        }
        else if(((FO2_Num < 1) && (OpCode == 0x12))||(0x80==MainMode)) {//BUG91
            buf[len++]='-';
            buf[len++]='-';
            buf[len++]='-';
            buf[len++] = (UnitType_) ? 0x3f : 0x60 ;//==1 -> M uint |==0 -> FT unit
            buf[len]='\0';
        }
        else {
            len += Num2Str((uint16_t)temp, buf, 5);
            buf[len] ='\0';
            buf[len++] = (UnitType_) ? 0x3f : 0x60 ;//==1 -> M uint |==0 -> FT unit
            buf[len] ='\0';
        }
    }
}
//
DoubleString SafetyDepthString[4]= {
    {"10`","3?"},
    {"15`","4?"},
    {"20`","5?"},
    {"","6?"}
}   ;
char* StrSafetyDepth(void) {
    //SafetyDepth_buf;
    char* string;
    u8 SafetyDepth = (STDFLG & 0x0F);
    u8 i = 0;
    for(i=0; i<4; i++) {
        if(SafetyDepth == i) {
            if(!UnitType_) {

                //return SafetyDepthString[i].String_1;
                string = SafetyDepthString[i].String_1;
                goto exit;
            }
            else {
                //return SafetyDepthString[i].String_2;
                string = SafetyDepthString[i].String_2;
                goto exit;
            }
        }
    }
exit:
    return string;
}


void PrepareSafetyTimeMin(void) {
    sprintf(SafetyTimeMin_buf, "%d", (SSTIME/60));
}
void PrepareSafetyTimeSec(void) {
    //SafetyTimeSec_buf
    len = 0;
    if((SSTIME%60)<10) {
        SafetyTimeSec_buf[len] = '0';
        len++;
    }
    len += Num2Str((SSTIME%60), SafetyTimeSec_buf + len, 2);
    SafetyTimeSec_buf[len] = '\0';
}
void prepare_aveDepthnum(char* buf, uint8_t flat) {
    u32 temp = aveDepth;
    len = 0;
    if(flat) {
        temp = (u32)ImperialConvert(temp);
        len += Num2Str((u16)temp, buf, 5);
        buf[len] ='\0';
    }
    else {
        if(UnitType_ > 0) { //Metric and value smaller than 3 digits
            Ascii_Float2Str(buf, &len , (float)ImperialConvert(temp), 1);
        }
        else {
            len += NumDouble2Str(temp, buf, 6);
            buf[len] ='\0';
        }
        buf[len++] = (!UnitType_) ? 0x60 : 0x3f ;//==1 -> M uint |==0 -> FT unit
        buf[len] ='\0';
    }
}

//???
void prepare_totalDives(void) {
    totalDive_buf[0]=0;
    totalDive_buf[1]=0;
    totalDive_buf[2]=0;
    totalDive_buf[3]=0;
    Num2Str(totalDive, totalDive_buf, 4);
}
void prepare_totalDiveTimeNum(void) {
    len = 0;
    len += Num2Str(DiveTimeHours, totalDiveTime_buf,5);
    totalDiveTime_buf[len++] ='\\';
    totalDiveTime_buf[len] ='\0';
}
void prepare_LastElapseDiveTime(void) { //EDT = Last Elapse Dive Time = (EDTH * 256 + EDTL) in minutes.
    len = 0;
    len += Num2Str(EDT, EDT_TimeBuf, 5);
    EDT_TimeBuf[len++] = 0x5d;
    EDT_TimeBuf[len] ='\0';
}

void prepare_aveDiveNum(char *buf, uint8_t flat) {
    len = 0;
    if(flat) {
        len += Num2Str((u16)aveDiveTime, buf, 6);
        buf[len] ='\0';
    }
    else {
        len += Num2Str((u16)aveDiveTime, buf, 6);
        buf[len++] =']';
        buf[len] ='\0';
    }
}

void PrepareMaxDiveTime(void) {
    sprintf(maxDivetime_buf, "%d]", maxDiveTime);
}

/*@author DucThinh90
* @brief Put the Temperature value to buffer to display with algorythm convert
* Call this function above the temper display
*/
void PrepareTemper(void) {
    float temp = TEMP;
    len = 0;
    if(UnitType_) {
        temp = DegreeConvert(temp);
        Ascii_Float2Str(_Temper_buf, &len, temp,0);
    }
    else {
        len += Num2Str((u16)temp, _Temper_buf + len, 5);
    }
    _Temper_buf[len++] ='*';//
    _Temper_buf[len++] = (!UnitType_) ? '$' : 0x7d ;//==1 ->C degree uint |==0 ->F degree unit
    _Temper_buf[len]='\0';
}

void prepare_lowestTempNum(void) {
    float temp = lowestTemp;
    len = 0;
    if(UnitType_) {
        temp = DegreeConvert(temp);
        Ascii_Float2Str(lowestTemp_buf, &len, temp,0);
    }
    else {
        len += Num2Str((u16)lowestTemp, lowestTemp_buf + len, 5);
    }
    lowestTemp_buf[len++] ='*';//
    lowestTemp_buf[len++] = (!UnitType_) ? '$' : 0x7d ;//==1 ->C degree uint |==0 ->F degree unit
    lowestTemp_buf[len]='\0';
}
u8 AltitudeProcess(u8 X) {
    X++;
    X = X >> 1;
    if((X == 0) || (X== 1)) {
        X = 0;
    }
    return X;
}

void PrepareAltitude(void) {
    u8 temp;
    temp = AltitudeProcess(Altitude);
    if(!temp) {
        sprintf(Altitude_buf, "%s", "SEA");
    }
    else {
        sprintf(Altitude_buf,"EL-%d",temp);
    }
}

//http://prntscr.com/7v6qeh
void prepare_FLYtime(char* Clock) {
    len = 0;
    if(((in_buf[5])&BIT5)==BIT_5) {//During 10 mins after dive
        Clock[len++]='-';
        Clock[len++]='-';
        Clock[len++]=':';
        Clock[len++]='-';
        Clock[len++]='-';
    }
    else {                    //After 10mins dive
        len += Num2Str(FLY_Hr, Clock, 5);
        Clock[len++] =':';
        if(FLY_Min<10) {
            Clock[len++] ='0';
        }
        len += Num2Str(FLY_Min, Clock+len, 5);
    }
    Clock[len++] =';';
    Clock[len] ='\0';
}

//http://prntscr.com/7v6qeh
void prepare_DESATTime(void) {
    len = 0;
    if((in_buf[5]&BIT_5) == BIT_5) {//During 10mins after dive
        DESATtime_buf[len++]='-';
        DESATtime_buf[len++]='-';
        DESATtime_buf[len++]=':';
        DESATtime_buf[len++]='-';
        DESATtime_buf[len++]='-';
    }
    else {                      //After 10mins dive
        len += Num2Str(DESAT_Hr, DESATtime_buf, 5);
        DESATtime_buf[len++] =':';
        if(DESAT_Min<10) {
            DESATtime_buf[len++] ='0';
        }
        len += Num2Str(DESAT_Min, DESATtime_buf+len, 5);
    }
    DESATtime_buf[len++] =';';
    DESATtime_buf[len] ='\0';
}

void prepare_SampleRate(char* buf) {                                                                                                                                                                                                                                                                       //Ducthinh90 fixed
    uint16_t SampleRateNum;
    len = 0;
    if(PFSHOT == 0) {
        SampleRateNum = 2;
    }
    else if(PFSHOT == 1) {
        SampleRateNum = 15;
    }
    else if(PFSHOT == 2) {
        SampleRateNum = 30;
    }
    else {
        SampleRateNum = 60;
    }
    len = Num2Str(SampleRateNum, buf, 5);
    buf[len++] ='@';
    buf[len] ='\0';
}
/*
u8 *buf : insert buffer which use to display
u16 pressure: data of Tank
u8 flat: include the unit string inside or not
*/
void Prepare_PressNum(char* buf, u16 Pressure, u8 flag) {
    len = 0;
    if(flag) {
        if(!UnitType_) {
            len += Num2Str(Pressure, buf, 4);
            buf[len] ='\0';
        }
        else {
            //Ascii_Float2Str(buf, &len, PSI_2_BAR(Tank_Pressure), 1);//after ',' will accurate 1 digit
            len += Num2Str(PSI_2_BAR(Pressure), buf, 3);
            buf[len] ='\0';
        }
    }
    else {
        len += Num2Str((!UnitType_) ? Pressure : PSI_2_BAR(Pressure) , buf, 4);
        buf[len++] = (!UnitType_) ? 0x22 : 0x27 ;//==1 -> M uint |==0 ->FT unit
        buf[len] ='\0';
    }
}

void prepare_TurnEndAlarm(char*buf, u16  TurnEndAlarm) {
    len = 0;
    if(TurnEndAlarm == 0) { //if 0 display OFF
        buf[0] = 'O';
        buf[1] = 'F';
        buf[2] = 'F';
        buf[3] ='\0';
    }
    else {
        if(UnitType_ > 0) { //When NORM MODE or GAUGE MODE SET ALARMS do not convert
            if(!ALARM_SET_Flag()) {
                TurnEndAlarm = PSI_2_BAR(TurnEndAlarm);
            }
        }
        len += Num2Str(TurnEndAlarm, buf, 4);
        // len += Num2Str((!UnitType_) ? TurnEndAlarm : PSI_2_BAR(TurnEndAlarm) , buf, 4);
        buf[len++] = (!UnitType_) ? 0x22 : 0x27 ;//==1 -> M uint |==0 ->FT unit
        buf[len] ='\0';
    }
}

void PrepareClock(char* Clock, uint8_t flat)//will fix the function to get 1 function with no if..else
{
    u8 _hh = hh;
    u8 _mm = mm;
    len = 0;
    if((midnight == 1) && (hrType == 1)) {
        _hh = _hh + 12;
        if(_hh == 24) {
            _hh = 12;
        }
    }
    if((midnight == 0)&&(_hh == 12)&& (hrType == 1)) {
        _hh = 0;
    }
    if(flat) {
        len += Num2Str(_hh, hr_buf, 3);
        hr_buf[len] = '\0';
        if(_mm<10) {
            min_buf[0] ='0';
            Num2Str(_mm, min_buf + 1, 3);
        }
        else {
            Num2Str(_mm, min_buf, 3);
        }
        min_buf[2] = '\0';
    }
    else {
        len += Num2Str(_hh, Clock, 5);
        Clock[len++] =':';
        if(_mm<10) {
            Clock[len++] ='0';
        }
        len += Num2Str(_mm, Clock+len, 5);
        if(!hrType) {
            Clock[len++] = ((!midnight) ? '{' : '|');//AM or PM
        }
        Clock[len] ='\0';
    }
}

void PrepareSurfTime(void) {
    sprintf(SurfHr_buf,"%d", Surf_Hour);
    if(Surf_Min < 10) {
        sprintf(SurfMin_buf,"0%d", Surf_Min);
    }
    else {
        sprintf(SurfMin_buf,"%d", Surf_Min);
    }
}
void PrepareMidday(uint8_t midnight_flat) {
    if(midnight_flat== AM_) {
        sprintf(Midday,"%s", "AM");
    }
    else {
        sprintf(Midday,"%s", "PM");
    }
}
void PrepareBattery(void) { //Prepare battery data
    sprintf(battery_buf, "%d%%", BATT);
}
void PrepareTLBG(void) {
    sprintf(TL_buf, "%d", TLBG);
}
void PrepareASCBG(void) {
    sprintf(AR_buf, "%d", ASCBG);
}

void Prepare_GTRnum(char* buf) {
    len = 0;
    //When enter the SURFACE_MODE
    if((OpCode == SURFACE_MODE)||(OpCode == CONDITIONAL)) {
        buf[0] = '-';
        buf[1] = ' ';
        buf[2] = '-';
        buf[3] = '\0';
    }
    //With others MODE
    else {
        if(Gas_Num == 1) {
            /*GTRL (LSB) and GTRH (MSB) = Gas Time Remaining in binary minutes.
                                                                                            When FFFF, display - - PSI or BAR.
                                                                                            No GTR if Gas# = Gas2, 3, or 4
                                                                                            */
            if((GTR_Time == 0) && (OpCode != DIVE_MODE)) {//http://prntscr.com/58of9s
                buf[0] = '-';
                buf[1] = ' ';
                buf[2] = '-';
                buf[3] = '\0';
            }
            else {
                len += Num2Str(GTR_Time, buf, 5);
                buf[len] ='\0';
            }
        }
        else {
            buf[0] = '\0';
        }
    }
}


void Process_DMY_data(uint8_t flag) { //Process Day/Month/Year screen H2B
    if(flag) {
        sprintf(MD_buf,"%d.%d.%d",Day, Month, Year);
    }
    else {
        sprintf(MD_buf,"%d.%d.%d",Month, Day, Year);
    }
}

void Process_DMY_data_1(void) { //Process Day/Month/Year screen H9A, H9B
    sprintf(Day_buf,"%d",Day);
    sprintf(Month_buf,"%d",Month);
    sprintf(Year_buf,"%d",Year);
}

char* hr_type_1(uint8_t flag) { //"(AM,PM)" or "(military)" type
    char *text;
    if(!flag) {
        text = "(AM, PM)";
    }
    else {
        text = "(military)";
    }
    return text;
}
char* hr_type_2(uint8_t flag) { //12hr or 24hr type
    char *text;
    if(!flag) {
        text = "12\\";
    }
    else {
        text = "24\\";
    }
    return text;
}

//=================================================================
//@DucThinh90@hotmail.com
//This function return "ON" or "OFF" string depend on the flag variable 1:ON and 0:OFF
//
//==========================(08/20/2014)=============================
char* OnOffStr(uint8_t flag) {
    char *text;
    if(flag)    {
        text = "ON";
    }
    else {
        text = "OFF";
    }
    return text;
}

//=================================================================
//@DucThinh90@hotmail.com
//This function return "IMPERIAL" or "METRIC" string depend on the flag variable -> 1:METRIC and 0:IMPERIAL
//"FT,PSI" or "M, BAR" string depend on the flag variable -> 1:METRIC / 0:FT,PSI
//==========================(08/20/2014)=============================
char* UnitType_1(uint8_t flag) {
    char *text;
    if(flag) {
        text = "(METRIC)";
    }
    else {
        text = "(IMPERIAL)";
    }
    return text;
}
char* UnitType_2(uint8_t flag) {
    char *text;
    if(flag) {
        text = "M, BAR";
    }
    else {
        text = "FT, PSI";
    }
    return text;
}


//=================================================================
//@DucThinh90@hotmail.com
//This function return "SEA" or "FRESH" string depend on the flag variable 1:FRESH and 0:SEA
//
//==========================(08/20/2014)=============================
/*uint8_t* WaterTypeStr(uint8_t flag)
{
    uint8_t *text;
    if(flag)
    {
        text = "FRESH";
    }
    else
    {
        text = "SEA";
    }
    return text;
}
*/
//=================================================================
//@DucThinh90@hotmail.com
//This function return "WEST" or "EAST" string depend on the flag variable 1:WEST and 0:EAST
//
//==========================(08/25/2014)=============================
/*uint8_t* DeclineString(uint8_t flag)
{
    uint8_t *text;
    if(flag)
    {
        text = "WEST";
    }
    else
    {
        text = "EAST";
    }
    return text;
}
*/
//=================================================================
//@DucThinh90@hotmail.com
//This function return "AUTODIM" or display brightness percent string depend on the flag variable 1: ON, 0: OFF
//
//==========================(08/29/2014)=============================
void ProcessAutoDimBright(void) {
    if(AutoDim || (!u8_BrightNess)) { //When the value of LCDLVL = 0%, should display AUTO DIM.
        sprintf(BrightNess_buf, "%s", "AUTO DIM");
    }
    else {
        sprintf(BrightNess_buf,"%d%%",u8_BrightNess);
        Backlight_CTRL(u8_BrightNess);
    }
}
//Decline process H13A an H13B
void ProcessDecline_1(void) { //When
    WriteText_Right_6("OFF");
}
void ProcessDecline_2(void) {
    u8 temp = EASWES;
    len = 0;
    //signed char temp = EASWES;
    if(DeclineBit) { //Check BIT7 if = 1 then INVERSE the number then ADD 1 to get the positive number
        temp = 0x100 - temp;
        DeclineString[len++] = '-';
    }
    else {
        DeclineString[len++] = '+';
    }
    len += Num2Str((uint16_t) temp , DeclineString + len, 3);
    DeclineString[len++] = '*';
    DeclineString[len] = '\0';
    TextRight4 = DeclineString;                                                                                                                                                                                                                                                                                                                        //°                                                                                                                                                                                                                                                                                                                //missing update data here
    TextRight4_0 = EASWES_String;                                                                                                                                                                                                                                                                                                                //missing update data here
    WriteText_Right_8();
}


//Save data from TI to My Info Data
//void StoreMyInfoData(void) {
//  u8 Row;//10 Rows
//  u8 Byte;//16 Bytes
//Store Row_0
//MyInDa[][] = ;
//}
//Opcode 10H GAS#
char* GAS_Str(void) {
    sprintf(Gas_buff, "GAS %d",Gas_Num);
    return Gas_buff;
}
/*@brief http://prntscr.com/511bur*/
void DisplaySPG(void) {
    WriteText_Middle_6("SPG");
}
/*@brief http://prntscr.com/511cff*/
void DisplayPressure(void) {
    if(1==Gas_Num) {
        //Round to 5 the tank pressure http://prntscr.com/ab8knp
        u16 TankPressure = Tank_Pressure;
        TankPressure = Tank_Pressure - (Tank_Pressure%5);
        Prepare_PressNum(pressure_buf, TankPressure, 1);
        TextColor = ((Tank_Pressure > 1000) ? Blue : ((Tank_Pressure > 500) ? Yellow: Red));
        LCD_SetColors(TextColor, Black);
        FontSet = (ptChar)myriad_bold_38;
        LCD_DisplayStringLine_Center(25,133, 199, pressure_buf);
        FontSet = (tChar*)myriad_bold_16;
        LCD_DisplayStringLine(98,229, PressureStr);
        DrawPart(LineVertical_3);//Always draw line
    }
}
void DisplayGTR(void) {
    if(1==Gas_Num) {
        Prepare_GTRnum(GTRnum_buf);
        if((GTR_Time==0)&&(SURFACE_MODE!=in_buf[OPCODE_BYTE])) {
            TextColor=Red;
        }
        else if((GTR_Time>0)&&(GTR_Time<6)) {
            TextColor=Yellow;
        }
        else {
            TextColor=Green;
        }
        BackColor=Black;
        FontSet = (ptChar)myriad_bold_38;
        LCD_DisplayStringLine_Center(132,218,199, GTRnum_buf);
        FontSet = (tChar*)myriad_bold_16;
        LCD_DisplayStringLine(140,229, "GTR");
        FontSet = (ptChar)myriad_bold_12;
        LCD_DisplayStringLine(183,229, "min");
        LCD_FillRect(177, 234, 1, 12, TextColor);//Line
    }
}

void DisplayPSIvsGTR(void) {
    if(Gas_Num == 1) {
        Prepare_PressNum(pressure_buf, Tank_Pressure, 1);
        Prepare_GTRnum(GTRnum_buf);
        DisplayGTR();
        DisplayPressure();
    }
    else {
        WriteText_Middle_6("SPG");
    }
}

u8 FO2_ReturnNum(void) {
    if((OpCode == NORMMAIN_MENU) ||(OpCode == PLAN_MODE)) {
        if(OpCode == NORMMAIN_MENU && MENSTAT == 0x91) {
            if((NPRV1_ & BIT_0) == BIT_0) { //NORM VIEW PRIVIEW
                return 24;
            }
            else if((NPRV1_ & BIT_1) == BIT_1) {
                // NPRV1_ = NPRV1_ & 0xFD;//Reset value of bit 1
                return 26;
            }
            else if((NPRV1_ & BIT_2) == BIT_2) {
                // NPRV1_ = NPRV1_ & 0xFB;//Reset value of bit 2
                return 28;
            }
            else if((NPRV1_ & BIT_3) == BIT_3) {
                //NPRV1_ = NPRV1_ & 0xF7;//Reset value of bit 3
                return 30;
            }
            else {
                return 0;
            }
        }

        else {
            return 14;
        }
    }
    else if((OpCode == SURFACE_MODE)) {
        return 23;
        // break;
    }
    else if(OpCode == NORM_SET_GAS) {
        if((MENSTAT == 0x10) ||(MENSTAT == 0x11)||(MENSTAT == 0x12)) {
            return 24;
            //break;
        }
        else if((MENSTAT == 0x20) ||(MENSTAT == 0x21)||(MENSTAT == 0x22)) {
            return 26;
            //break;
        }
        else if((MENSTAT == 0x30) ||(MENSTAT == 0x31)||(MENSTAT == 0x32)) {
            return 28;
            //break;
        }
        else if((MENSTAT == 0x40) ||(MENSTAT == 0x41)||(MENSTAT == 0x42)) {
            return 30;
            //break;
        }
        else {
            return 0;
            //break;
        }
    }

    else {
        return 0;
        // break;
    }
}

void CheckStopDepth(void) {
    if(STDFLG_LowNibble == 0) {
        SafetyStopDepth_Str = (UnitType_ > 0) ? "3M" : "10 FT";
    }
    else if(STDFLG_LowNibble == 1) {
        SafetyStopDepth_Str = (UnitType_ > 0) ? "4M" : "15 FT";
    }
    else if(STDFLG_LowNibble == 2) {
        SafetyStopDepth_Str = (UnitType_ > 0) ? "5M" : "20 FT";
    }
    else {
        SafetyStopDepth_Str = (UnitType_ > 0) ? "6M" : "20 FT";//May be fix the character FT
    }
}
void CheckStopTime(void) {
    if((STDFLG & BIT_4) == BIT_4) {
        SafetyStopTime_Str = "5 min";
    }
    else {
        SafetyStopTime_Str = "3 min";
    }
}
char* SafetyStopPrepare(void) {
    if(MORFLG_LowNibble == 0) {
        return "OFF";
    }
    else if (MORFLG_LowNibble == 1) {
        return  "ON";
    }
    else {
        return "SET";
    }
}

u8 ALARM_SET_Flag(void) {
    if((OpCode == NORM_SET_ALARM) ||
            (OpCode == NORMMAIN_MENU && (MENSTAT == 0x61 || MENSTAT == 0x91))) {
        return 1;
    }
    else {
        return 0;
    }
}

void Draw_Circle(u16 DotNum, tImage* _dotImage) {
    u16 i = 0;
    while(DotNum != 0) {
        LCD_DrawBMP(CirclePoint[i].X,CirclePoint[i].Y, (ptImage)&PutImage,0);
        i++;
        DotNum --;
    }
    while(i<361) {
        LCD_DrawBMP(CirclePoint[i].X,CirclePoint[i].Y, (ptImage)&ClearImage,0);
        i++;
    }
}
void DisplayCompass(u16 Degree) {
//Degree = 180;
    FontSet=(ptChar)myriad_bold_12;
    LCD_SetColors(Red, Black);
    //#testing
    //LCD_FillRect(120, 203, 1,1,White) ;
    //for(u16 i=0;i<360;i+=1){
    //LCD_DisplayStringLine(compasspoint[i].X, compasspoint[i].Y, "SW");
    // LCD_FillRect(compasspoint[i].X, compasspoint[i].Y, 1,1,White);
    //LCD_DisplayStringLine(compasspoint[i].X, compasspoint[i].Y, "NW");
    //LCD_DrawChar(compasspoint[i].X-(Image_Compass_Text_North.width/2), compasspoint[i].Y, (ptImage)&Image_Compass_Text_North);
    //LCD_DisplayStringLine(compasspoint[i+90].X, (compasspoint[i+90].Y - ((myriad_bold_15[0].image->height)/2)), "N");
    //LCD_DisplayStringLine_Center(compasspoint[i].X-10, compasspoint[i].X+10, compasspoint[i].Y, "SW");
    //LCD_DisplayStringLine_As_Right(compasspoint[i+270].X, compasspoint[i+270].Y - ((myriad_bold_15[0].image->height)/2), "N");
    //}
    LCD_DrawChar(compasspoint[Degree].X-((Image_Compass_Text_North.width)/2), compasspoint[Degree].Y, (ptImage)&Image_Compass_Text_North);
    TextColor=White;
    FontSet=(ptChar)myriad_bold_12;
    LCD_DrawChar(compasspoint[(Degree+45)%360].X-((Image_Compass_Text_NorthWest.width)/2), compasspoint[(Degree+45)%360].Y, (ptImage)&Image_Compass_Text_NorthWest);
    FontSet=(ptChar)myriad_bold_15;
    LCD_DrawChar(compasspoint[(Degree+90)%360].X-((Image_Compass_Text_West.width)/2), compasspoint[(Degree+90)%360].Y, (ptImage)&Image_Compass_Text_West);
    FontSet=(ptChar)myriad_bold_12;
    LCD_DrawChar(compasspoint[(Degree+135)%360].X-((Image_Compass_Text_SouthWest.width)/2), compasspoint[(Degree+135)%360].Y, (ptImage)&Image_Compass_Text_SouthWest);
    FontSet=(ptChar)myriad_bold_15;
    LCD_DrawChar(compasspoint[((Degree+180)%360)].X-((Image_Compass_Text_South.width)/2), compasspoint[((Degree+180)%360)].Y, (ptImage)&Image_Compass_Text_South);//
    FontSet=(ptChar)myriad_bold_12;
    LCD_DrawChar(compasspoint[(Degree+225)%360].X-((Image_Compass_Text_SouthEast.width)/2), compasspoint[(Degree+225)%360].Y, (ptImage)&Image_Compass_Text_SouthEast);
    FontSet=(ptChar)myriad_bold_15;
    LCD_DrawChar(compasspoint[(Degree+270)%360].X-((Image_Compass_Text_East.width)/2), compasspoint[(Degree+270)%360].Y, (ptImage)&Image_Compass_Text_East);
    FontSet=(ptChar)myriad_bold_12;
    LCD_DrawChar(compasspoint[(Degree+315)%360].X-((Image_Compass_Text_NorthEast.width)/2), compasspoint[(Degree+315)%360].Y, (ptImage)&Image_Compass_Text_NorthEast);
    //Compass number
    len=Num2Str(Degree, compass_buf, 3);
    compass_buf[len++]='*';
    compass_buf[len]=0;
    FontSet=(ptChar)myriad_bold_30;
    LCD_FillRect(88, 188, 64, 30, Black);
    LCD_SetColors(Green, Black);
    LCD_DisplayStringLine_Center(0,240,192,compass_buf);
    //Remove all buffer
    compass_buf[0]=0;
    compass_buf[1]=0;
    compass_buf[2]=0;
    compass_buf[3]=0;
    compass_buf[4]=0;
}
void UpdateCompass(void) {
    if(preDISA!=DISA) {
        //Clear previous position
        LCD_FillRect(compasspoint[preDISA].X-9, compasspoint[preDISA].Y, 18,10,Black);
        LCD_FillRect(compasspoint[(preDISA+45)%360].X-9, compasspoint[(preDISA+45)%360].Y, 18,10,Black);
        LCD_FillRect(compasspoint[(preDISA+90)%360].X-9, compasspoint[(preDISA+90)%360].Y, 18,10,Black);
        LCD_FillRect(compasspoint[(preDISA+135)%360].X-9, compasspoint[(preDISA+135)%360].Y, 18,10,Black);
        LCD_FillRect(compasspoint[((preDISA+180)%360)].X-9, compasspoint[((preDISA+180)%360)].Y, 18,10,Black);
        LCD_FillRect(compasspoint[(preDISA+225)%360].X-9, compasspoint[(preDISA+225)%360].Y, 18,10,Black);
        LCD_FillRect(compasspoint[(preDISA+270)%360].X-9, compasspoint[(preDISA+270)%360].Y, 18,10,Black);
        LCD_FillRect(compasspoint[(preDISA+315)%360].X-9, compasspoint[(preDISA+315)%360].Y, 18,10,Black);
        //Display compass
        DisplayCompass(DISA);
        preDISA=DISA;
    }
//#testing
    /*for(u16 i = 0;i<360;i++) {
            //Clear previous position
            LCD_FillRect(compasspoint[preDISA].X-9, compasspoint[preDISA].Y, 18,10,Black);
            LCD_FillRect(compasspoint[(preDISA+45)%360].X-9, compasspoint[(preDISA+45)%360].Y, 18,10,Black);
            LCD_FillRect(compasspoint[(preDISA+90)%360].X-9, compasspoint[(preDISA+90)%360].Y, 18,10,Black);
            LCD_FillRect(compasspoint[(preDISA+135)%360].X-9, compasspoint[(preDISA+135)%360].Y, 18,10,Black);
            LCD_FillRect(compasspoint[((preDISA+180)%360)].X-9, compasspoint[((preDISA+180)%360)].Y, 18,10,Black);
            LCD_FillRect(compasspoint[(preDISA+225)%360].X-9, compasspoint[(preDISA+225)%360].Y, 18,10,Black);
            LCD_FillRect(compasspoint[(preDISA+270)%360].X-9, compasspoint[(preDISA+270)%360].Y, 18,10,Black);
            LCD_FillRect(compasspoint[(preDISA+315)%360].X-9, compasspoint[(preDISA+315)%360].Y, 18,10,Black);
            //Display compass
            DisplayCompass(i);
            Delay_ms(2000);
            preDISA=i;
    }*/
}
void DisplayCompassCounter(void) {
    if(COUNL<61) {//http://prntscr.com/7cpyyx
        len=Num2Str(COUN, compass_buf, 3);
        compass_buf[len++]='@';
        compass_buf[len]=0;
        FontSet=(ptChar)myriad_bold_14;
        LCD_SetColors(White, Black);
        LCD_DisplayStringLine_Center(188,240,282,compass_buf);
        //Remove all buffer
        compass_buf[0]=0;
        compass_buf[1]=0;
        compass_buf[2]=0;
        compass_buf[3]=0;
        compass_buf[4]=0;
    }
}
void UpdateCompassCounter(void) {
    if(preCOUN!=COUN) {
        LCD_FillRect(188, 282, 53, 14, Black);
        DisplayCompassCounter();
        preCOUN=COUN;
    }
}
void DisplayCompassReference(void) {
    FontSet=(ptChar)myriad_bold_11;
    LCD_SetColors(White, Black);
    LCD_DisplayStringLine(3, 284, "REF");
    len=Num2Str(REF, compass_buf, 3);
    compass_buf[len++] = '*';
    compass_buf[len]=0;
    FontSet=(ptChar)myriad_bold_14;
    LCD_DisplayStringLine(30, 283, compass_buf);
    //Remove all buffer
    compass_buf[0]=0;
    compass_buf[1]=0;
    compass_buf[2]=0;
    compass_buf[3]=0;
    compass_buf[4]=0;
}
//http://prntscr.com/81lmiu
void UpdateCompRefDot(void) {
    if(!DCMARK_BIT2) {
        ClearPart(ReferenceDot);
        DrawPart(ReferenceDot);
    }
}
void UpdateCompRevDot(void) {
    if(!DCMARK_BIT3) {
        ClearPart(ReverseDot);
        DrawPart(ReverseDot);
    }
}
void DisplayCompassReverse(void) {
    FontSet=(ptChar)myriad_bold_11;
    LCD_SetColors(White, Black);
    LCD_DisplayStringLine(3, 284, "REV");
    len=Num2Str(REV, compass_buf, 3);
    compass_buf[len++] = '*';
    compass_buf[len]=0;
    FontSet=(ptChar)myriad_bold_14;
    LCD_DisplayStringLine(30, 283, compass_buf);
    //Remove all buffer
    compass_buf[0]=0;
    compass_buf[1]=0;
    compass_buf[2]=0;
    compass_buf[3]=0;
    compass_buf[4]=0;
}
void UpdateCompRefNum(void) {
    if((preREF!=REF)||(DCMARK_BIT2!=_DCMARK_BIT2)  ) {
        if(DCMARK_BIT2) {
            if((MSG&BIT_7)==BIT_7) {
                ClearPart(ReferenceAngle);
            }
            else {
                DisplayCompassReference();
            }
            _DCMARK_BIT2=DCMARK_BIT2;
        }
        else {
            ClearPart(ReferenceAngle);
            DisplayCompassReference();
            preREF=REF;
        }

    }
}
void UpdateCompassReverse(void) {
    if((preREV!=REV)||(DCMARK_BIT3!=_DCMARK_BIT3)  ) {
        if(DCMARK_BIT3) {
            if((MSG&BIT_7)==BIT_7) {
                ClearPart(ReferenceAngle);
            }
            else {
                DisplayCompassReverse();
            }
            _DCMARK_BIT3=DCMARK_BIT3;
        }
        else {
            ClearPart(ReferenceAngle);
            DisplayCompassReverse();
            preREV=REV;
        }
    }
}

//Compass Arrow direction
void UpdateCompassArrow(void) {
    /*    if(ABS(REF-DISA)<=5) {
            ClearPart(CompassArrrow);
        }
        else {
            if(((DISA>REF)&&(((DISA-REF)/180)==1))||
                    ((DISA<REF)&&(((REF-DISA)/180)==0))) {
                DrawPart(CompassArrrow_Right);
            }
            else {
                DrawPart(CompassArrrow_Left);
            }
        }
    */
    if(!DCMARK_BIT2) { //http://prntscr.com/7fufrk
        switch(LORR) {
        case 0:
            ClearPart(CompassArrrow);
            DrawPart(TopCompass_Green);
            break;
        case 1:
            DrawPart(CompassArrrow_Left_Yellow);
            DrawPart(TopCompass_Yellow);
            break;
        case 2:
            DrawPart(CompassArrrow_Right_Yellow);
            DrawPart(TopCompass_Yellow);
            break;
        }
    }
}
void UpdateCompassArrowReverse(void) {
    if(!DCMARK_BIT3) { //http://prntscr.com/7fufrk
        switch(LORR) {
        case 0:
            ClearPart(CompassArrrow);
            DrawPart(TopCompass_Green);
            break;
        case 1:
            DrawPart(CompassArrrow_Left_Yellow);
            DrawPart(TopCompass_Yellow);
            break;
        case 2:
            DrawPart(CompassArrrow_Right_Yellow);
            DrawPart(TopCompass_Yellow);
            break;
        }
    }
}
//Update data
void UpdateTemper_Pos1(void) {
    if(TEMP != _preTEMP) {
        _preTEMP = TEMP;
        ClearPart(Temperature_Style_1);
        DisplayTemper_Pos1();
    }
}
void UpdateTemper_Pos2(void) {
    if(TEMP != _preTEMP) {
        _preTEMP = TEMP;
        ClearPart(Temperature_Style_2);
        DisplayTemper_Pos2();
    }
}
void UpdateClock_Pos1(void) {
    if(hh != _prehh || mm != _premm || midnight != _premidnight) {
        _prehh = hh;
        _premm = mm;
        _premidnight = midnight;
        LCD_FillRect(83, 20, 52, 14, Grey);
        DisplayClock_Pos1();
    }
    UpdateColonClock(Grey);
}
void UpdateClock_Pos2(void) {
    if(hh != _prehh || mm != _premm || midnight != _premidnight) {
        _prehh = hh;
        _premm = mm;
        _premidnight = midnight;
        LCD_FillRect(83, 20, 58, 14, Red);
        DisplayClock_Pos2();
    }
    UpdateColonClock(Red);
}

void UpdateBattery_Pos1(void) {
    if(BATT != _preBATT) {
        _preBATT = BATT;
        DisplayBattery_Pos1();
    }
}

void UpdateBattery_Pos2(void) {
    if(BATT != _preBATT) {
        _preBATT = BATT;
        DisplayBattery_Pos3();
    }
}
/*
Number from 0, 1, ..9 : position of rows.
Item Status: Flashing, Select or both of them.
*/
void ProcessItem(u8 Number, Status ItemStatus,char* Content ) {
    FontSet = (tChar*)myriad_bold_16;
    //Item flashing
    if(ItemStatus.Flashing) {
        if((MSG&BIT_7)==BIT_7) {
            LCD_SetColors((ItemStatus.HighLight == 1) ? Black : White, (ItemStatus.HighLight == 1) ? Green : Black);
            LCD_FillRect(0, 84+(23*Number), 146, 22, BackColor);
        }
        else {
            LCD_DisplayStringLine(7,85+((Number)*23), Content);
        }
    }
    //No flashing
    else {
        LCD_SetColors((ItemStatus.HighLight == 1) ? Black : White, (ItemStatus.HighLight == 1) ? Green : Black);
        LCD_FillRect(0, 84+(23*Number), 146, 22, BackColor);
        LCD_DisplayStringLine(7,85+((Number)*23), Content);
    }
}
void UpdatePreviewPage_1(void) {
    //Update present item
    //if((MENSTAT)!= preMSG) { //MENSTAT = 01/02/03..09.
    //  ClearPart(ItemPreviewUnSelect);
    //   DrawPart(ItemPreviewSelected);
    //
    for(u8 i=0; i<9; i++) {
        Status _Status;
        _Status.Flashing = (NPRV1>>i)&BIT_0;
        _Status.HighLight = (MENSTAT == (i+1)) ? 1 : 0;
        ProcessItem(i, _Status ,_RowSetPreview[i].Row_String_Left);
    }
    //preMSG = MENSTAT;
    //}
    //Update selected items and flashing
    //if(NPRV1!=preNPRV1) {

    //}
}

void UpdateTLBG(void) {
    if(TLBG != _preTLBG) {
        if(TLBG < _preTLBG) {
            redrawScreenSection(0, 40,22, 285, (uint16_t const *)&BMP_S1A_left_X0Y40, 245,25,0,40);
        }
        _preTLBG = TLBG ;
        redrawScreenSection(0,40, 22, 51, (uint16_t const *)&BMP_S1A_left_X0Y40, 245,25,0,40);
        DisplayTLBG();
    }
}
void FlashingSurficon(void) {
    if((MSG&BIT_7) == BIT_7) {
        LCD_FillRect(30, 55, 60, 30, Black);
    }
    else {
        LCD_SetColors(Blue, Black);
        FontSet = (ptChar)myriad_bold_19;
        LCD_DisplayStringLine(36,61, "SURF");//
    }
}
//http://prntscr.com/5ezo6k Update blinking or not
void UpdateSURFicon(void) {
    if((MainMode&BIT_5) != BIT_5) {
        LCD_SetColors(Blue, Black);
        FontSet = (ptChar)myriad_bold_19;
        LCD_DisplayStringLine(36,61, "SURF");//
    }
    else {
        FlashingSurficon();
    }
}

void UpdateSurfColonicon(void) {
    if((MSG&BIT_7)==BIT_7) {
        redrawScreen(141, 62, 141+10, 62+37,Black);
    }
    else {
        LCD_SetColors(Blue, Black);
        FontSet = (ptChar)myriad_bold_38;
        LCD_DisplayStringLine(141,62, ":");//Redraw (148,53) and (158,99)
    }
}
void UpdateSurfColoniconCompass(void) {
    if((MSG&BIT_7)==BIT_7) {
        redrawScreen(141, 52, 141+10, 52+37,Black);
    }
    else {
        LCD_SetColors(Blue, Black);
        FontSet = (ptChar)myriad_bold_38;
        LCD_DisplayChar(141,52, ':');//Redraw (148,53) and (158,99)
    }
}

void UpdateASCBG(void) {
    if(ASCBG!= _preASCBG) {
        if(ASCBG < _preASCBG) { //if value == 0 clear the bar screen
            redrawScreenSection(217, 40,240, 285, (uint16_t const *)&BMP_S1A_right_X240Y40, 245,25,215,40);
        }
        _preASCBG = ASCBG;
        redrawScreenSection(220, 40,240, 51, (uint16_t const *)&BMP_S1A_right_X240Y40, 245,25,215,40);
        DisplayASCBG();
    }
}
void UpdateDeepStop(void) {
    if((maxDepth!= _preMaxDepth)&& ((MSG&BIT_7)!=0x03)) {
        _preMaxDepth = maxDepth;
        LCD_FillRect(24, 130, 90, 30, Black);
        DisplayDeepStop();
    }
}
void UpdateStopTime(void) {
    //STOP time mins
    if(((SSTIME/60)!= _preSSTIMEMin)&&((MSG & 0x7F) != 0x03)) {
        _preSSTIMEMin = (SSTIME/60);
        LCD_FillRect(126, 145, 27, 37, Black);
        DisplayStopMin();
    }
    //STOP time secs
    if(((SSTIME%60)!= _preSSTIMESec)&&((MSG & 0x7F) != 0x03)) {
        _preSSTIMESec = (SSTIME%60);
        LCD_FillRect(165, 145, 50, 37, Black);
        DisplayStopSec();
    }
}

void UpdateEARMARKAPPLIED(void) {
    if((MSG&0x7F)==0x03) {
        if(EARMARK!=AlarmCode) {
            if(0x90==MainMode) {
                LCD_FillRect(0, 118, 218, 74, Black);
            }
            else {
                DrawPart(BlackRectMiddle);
            }
            LCD_DisplayText(0, 240, 125, (ptChar)myriad_bold_25, Green, Black, AlignCenter, "EARMARK");
            LCD_DisplayText(0, 240, 150, (ptChar)myriad_bold_25, Green, Black, AlignCenter, "APPLIED");
            preAlarmCode=AlarmCode;
            AlarmCode=EARMARK;
        }
    }
}
void UpdateEARMARKAPPLIED_Compass(void) {
    if((MSG&0x7F)==0x03) {
        if(EARMARK!=AlarmCode) {
            ClearPart(Current_Depth);
            LCD_DisplayText(0, 240, 53, (ptChar)myriad_bold_25, Green, Black, AlignCenter, "EARMARK");
            LCD_DisplayText(0, 240, 78, (ptChar)myriad_bold_25, Green, Black, AlignCenter, "APPLIED");
            preAlarmCode=AlarmCode;
            AlarmCode=EARMARK;
        }
    }
    else {
        preAlarmCode=AlarmCode;
        AlarmCode=NOMESSAGE;
    }
}
void UpdateSetHeadingCompass(void) {
    if((DCMARK_BIT2)!=_DCMARK_BIT2) {
        LCD_SetColors(White, Black);
        ClearPart(BottomTitle);
        ClearPart(ReferenceDot);
        _DCMARK_BIT2=DCMARK_BIT2;
        if(_DCMARK_BIT2) {
            DrawPart(TopCompass_Green);
            LCD_DrawChar(115,107, (ptImage)&RefPointImage);//Top compass
            DrawPart(TitleBar_SetHeading);
            DisplayBottomTitle(_BottomTitle[30]);//Bottom
            ClearPart(CompassArrrow);
        }
        else {
            LCD_DrawBMP(115,107, (ptImage)&RefPointClearImage,0);//Top compass
            DrawPart(TitleBar_Reference);
            DisplayBottomTitle(_BottomTitle[27]);
        }
    }
}
void UpdateSetReverseCompass(void) {
    if(DCMARK_BIT3!=_DCMARK_BIT3) {
        //ClearPart(BottomTitle);
        _DCMARK_BIT3=DCMARK_BIT3;
        if(DCMARK_BIT3) {
            DrawPart(TitleBar_SetReverse);
            //DisplayBottomTitle((char*)_BottomTitle[31]);//Bottom
            ClearPart(CompassArrrow);
        }
        else {
            DrawPart(TitleBar_Reverse);
            //DisplayBottomTitle((char*)_BottomTitle[27]);
        }
    }
}
void UpdateRunTimer(void) {
    if((RTM!= _preRTM)&&((MSG & 0x7F) != 0x03)) {
        _preRTM = RTM;
        LCD_FillRect(8, 130, 110, 30, Black);
        DisplayRunTime();
    }
}
void FlashingRUNstatus(void) {
    if(MORFLG != _preMORFLG) {
        _preMORFLG = MORFLG;
        LCD_FillRect(5, 170, 54, 20, Black);
        DisplayRunStatus();
    }
}
void UpdateDECODepth(void) {
    if(((DESD!= _preDESD)||(DEPTH!= _preDECODepth))&& ((MSG & 0x7F) != 0x03)) {
        _preDESD = DESD;
        //_preDECODepth = DEPTH;
        LCD_FillRect(24, 145, 90, 30, Black);
        DisplayDECODepth();
    }
}

void UpdateDECOTime(void) {
    if(((DEST != _preDEST)||(_preDECODepth!=DEPTH))&&((MSG & 0x7F)!=0x03)) {
        _preDEST = DEST;
        _preDECODepth = DEPTH;
        DrawPart(BlackRect_Right);
        DisplayDECOTime();
    }
}
//http://prntscr.com/5vdwh5
void FlashingDelayViolation(void) {
    if(((MSG&0x7F)==0x1A)) {
        LCD_FillRect(24, 145, 90, 30, Black);
        LCD_FillRect(123, 145, 63, 30, Black);//http://prntscr.com/85p9kn
        redrawScreenSection(0, 40,22, 285, (uint16_t const *)&BMP_S1A_left_X0Y40, 245,25,0,40);
        if((MSG)== 0x1A) {
            DisplayTLBG();
            DisplayDECODepth();
            DisplayDECOTime();
        }
        preAlarmCode=AlarmCode;
        AlarmCode=DELAYVIOLATION;
    }
}

void UpdateSafetyDepth(void) {
    if((STDFLG != _preSTDFLG)&&((MSG & 0x7F) != 0x03)) {
        _preSTDFLG = STDFLG;
        DrawPart(BlackRect_Left);
        DisplaySafetyStop();
    }
}
/*
http://prntscr.com/808jt3
- Compare FO2
*/
void UpdateGASnum(void) {
    if((Gas_Num != _preGas_Num)||(FO2!=_preFO2)) {
        _preGas_Num   = Gas_Num;
        _preFO2       = FO2;
        LCD_FillRect(94, 258, 52, (myriad_bold_17[0].image->height), Grey);//rgb 102 102 102
        LCD_FillRect(95, 283, 23, (myriad_bold_12[0].image->height), Grey);
        DisplayGAS();
        LCD_FillRect(34, 278, 55, 20, Grey);//102 102 102
        DisplayFO2();//Need to update to make the text the same color with GAS as spec
    }
}
void UpdateSPG(void) {
    if((Gas_Num != _preGas_Num)&&(1!=Gas_Num)) {
        _preGas_Num = Gas_Num;
        LCD_FillRect(23, 194, 192, 60, Black);
        DisplaySPG();
        _preGTR_Time      = 67;//dumm data to make sure that after SPG will display GTR and Pressure.
        _preTank_Pressure = 238;
    }
}
//When GAS 1
void UpdateTankPressure(void) {
    //Pressure and GTR GAS 1 (GAS 2, 3, 4 display SPG)
    if(((ABS(Tank_Pressure - _preTank_Pressure))>5)&&(1==Gas_Num)) {
        _preTank_Pressure  = Tank_Pressure;
        ClearPart(Pressure);
        DisplayPressure();
    }
}
//
void UpdateGTR(void) {
    if((GTR_Time!=_preGTR_Time)&&(1==Gas_Num)) {
        _preGTR_Time = GTR_Time;
        ClearPart(GasTimeRemain);
        DisplayGTR();
    }
}
void UpdateSurfTime(void) {
    PrepareSurfTime();
    if(Surf_Hour != _preSurf_Hour) {
        _preSurf_Hour = Surf_Hour;
        redrawScreen(78, 62, 153, 99,Black);
        DisplaySurfHr();
    }
    if(Surf_Min !=_preSurf_Min) {
        _preSurf_Min = Surf_Min;
        redrawScreen(151, 62, 226, 99, Black);
        DisplaySurfMin();
    }
}
void UpdateSurfTimeCompass(void) {
    PrepareSurfTime();
    if(Surf_Hour != _preSurf_Hour) {
        _preSurf_Hour = Surf_Hour;
        redrawScreen(78, 52, 153, 89,Black);
        DisplaySurfHrCompass();
    }
    if(Surf_Min !=_preSurf_Min) {
        _preSurf_Min = Surf_Min;
        redrawScreen(151, 52, 226, 89, Black);
        DisplaySurfMinCompass();
    }
}

void UpdateDiveNum(void) {
    if(DiveNum != _preDiveNum) {
        LCD_FillRect(115, 138, 50, 28, Black);
        DisplayDiveNum();
        _preDiveNum = DiveNum;
    }
}
void UpdateFO2(void) {
    if((FO2 != _preFO2)) {
        _preFO2 = FO2;
        LCD_FillRect(34, 278, 55, 20, Grey);//102 102 102
        DisplayFO2();
    }
}
void UpdatePO2(void) {
    if(PO2 != _prePO2) {
        _prePO2 = PO2;
        LCD_FillRect(160, 278, 48, 20, Grey);//102 102 102
        DisplayPO2Current();
    }
}
void UpdatePO2Current(void) {
    if(PO2Current != _prePO2Current||
            (MainMode != _preDVSTAT)) {//May be need add the condition with buff7 changing
        _prePO2Current  = PO2Current;
        _preDVSTAT      = MainMode;
        LCD_FillRect(131, 278, 77, 20, Grey);//102 102 102
        DisplayPO2Current();
    }
}
//    LCD_DisplayStringLine(155,84+(Position*24), content);
void UpdatePO2CurrentMoreData(void) {
    if(PO2Current != _prePO2Current) {
        _prePO2Current = PO2Current;
        LCD_FillRect(153, 276, 50, 14, BG_RIGHT);
        LCD_SetColors(Black, White);
        FontSet = (ptChar)myriad_bold_14;
        LCD_DisplayStringLine(155,276, PO2CurrentString());
    }
}
void UpdateEDTMoreData(u8 pos) {
    if(EDT!=_preEDT) {
        _preEDT=EDT;
        PrepareEDT(EDTnum_buf, 0);
        LCD_FillRect(153, 84+(pos*24), 50, 14, BG_RIGHT);//green
        WriteText_Right_17(pos, EDTnum_buf,Black, White );//01
    }
}
void UpdateNDCMoreData(void) { //0
    if(NDC_!=_preNDC) {
        _preNDC=NDC_;
        PrepareNDC(NDCnum_buf,0);
        LCD_FillRect(153, 84, 50, 14, BG_RIGHT);
        LCD_SetColors(Black, White);
        FontSet = (ptChar)myriad_bold_14;
        LCD_DisplayStringLine(154,84, NDCnum_buf);
    }
}
void UpdateDiveTimeMoreData(void) {
    if(EDT!= _preEDT) {
        _preEDT    = EDT;
        TextColor  = White;
        BackColor  = Green;
        PrepareEDT(divetime_buf, 1);
        LCD_FillRect(153, 84, 50, 14, 0x0660);
        FontSet = (ptChar)myriad_bold_14;
        LCD_DisplayStringLine(155,84, divetime_buf);
    }
}
void UpdateMaxDepthMoreData(u8 pos) {
    if(maxDepth!=_preMaxDepth) {
        _preMaxDepth = maxDepth;
        PrepareMaxDepth(maxDepth_buf, 0);
        LCD_FillRect(153, 84+(pos*24), 50, 14, BG_RIGHT);
        WriteText_Right_17(pos, maxDepth_buf, Black, White);//02/03
    }
}
void UpdateTimeMoreData(u8 pos) {
    if(hh != _prehh || mm != _premm || midnight != _premidnight) {
        _prehh       = hh;
        _premm       = mm;
        _premidnight = midnight;
        PrepareClock(time_buf, 0);
        LCD_FillRect(153,84+(pos*24), 50,14,BG_RIGHT);
        WriteText_Right_17(pos, time_buf, Black, White);//03/02
    }
}
void UpdateTemperMoreData(u8 pos) {
    if(TEMP!=_preTEMP) {
        _preTEMP = TEMP;
        PrepareTemper();
        LCD_FillRect(153,84+(pos*24), 50,14,BG_RIGHT);
        WriteText_Right_17(pos, _Temper_buf, Black, White);//04
    }
}
void UpdateO2MoreData(void) {
    if(O2SAT!=PreO2SAT) {
        PreO2SAT = O2SAT;
        PrepareO2();
        LCD_FillRect(153,84+(7*24), 50,14,BG_RIGHT);
        WriteText_Right_17(7, O2num_buf, Black, White);//07
    }
}
void UpdateTotalAscentTimeMoreData(void) {
    u8 len=0;
    if(TAT!=_preTAT) {
        _preTAT = TAT;
        len += Num2Str(TAT,TotalAscentTime_buf , 2);
        LCD_FillRect(153,84, 50,14,BG_RIGHT);
        TotalAscentTime_buf[len]=']';
        WriteText_Right_17(0, TotalAscentTime_buf,Black, White);
    }
}

//A4A
void FlashingDOWNTOSTOP(void) {
    if(((MSG&0x7F)==0x00)||        //NOMESSAGE
            ((MSG&0x7F)==0x1A)||   //DELAYVIOLATION
            ((MSG&0x7F)==0x12)||   //DOWNTOSTOP
            ((MSG&0x7F)==0x15)||   //LOWBATTWARNING
            ((MSG&0x7F)==0x16)||   //LOWBATTSHUTDOWN
            ((MSG&0x7F)==0x17)||   //LOWBATTSHUTDOWNUPARROW
            ((MSG&0x7F)==0x0B)||   //PO2WARNING
            ((MSG&0x7F)==0x0E)||   //O2WARNING
            ((MSG&0x7F)==0x0C)||   //PO2ALARMGOUP
            ((MSG&0x7F)==0x03)||   //EARMARK
            ((0x70==DVSTAT)&&(OpCode==0x11))) {
        if((MSG&BIT_7)!=BIT_7) {
            LCD_DisplayText(75, 240, 0, (ptChar)myriad_bold_19, White, Red, AlignLeft, "DOWN TO");
            LCD_DisplayText(97, 240, 23, (ptChar)myriad_bold_19, White, Red, AlignLeft, "STOP");
            LCD_DisplayStringLine(45,0, "v");
            LCD_DisplayStringLine(185,0, "v");
        }
        else {
            DrawPart(RedTilte);
        }
        //http://prntscr.com/609jkz
        if((MSG&0x7F)==0x12) {
            if(MSG==0x12) {
                DisplayDECODepth();
            }
        }
    }
}
//Current depth in Imperal/Metric : http://prntscr.com/50btai
void UpdateDepth(void) {
    if(DEPTH != _preDepth) {
        _preDepth = DEPTH;
        ClearPart(Current_Depth);
        DisplayDepth();
    }
}
void UpdateDepthCompass(void) {
    if(DEPTH != _preDepth) {
        _preDepth = DEPTH;
        ClearPart(Current_Depth_Compass);
        DisplayDepthCompass();
    }
}

//http://prntscr.com/5fbk26
void FlashingDEPTH(void) {
//Once display changing area
    if((MSG&0x7F)==0x04) {
        if(DEPTHALARM!=AlarmCode) {
            preAlarmCode=AlarmCode;
            AlarmCode=DEPTHALARM;
        }
        if(MSG==0x04) {
            DisplayDepth();
            WriteText_Title_2("DEPTH",5,White,Red);//Top
        }
        else {
            DrawPart(RedTilte);
            ClearPart(BlackRectDepth);
        }
    }
}
//http://prntscr.com/5fbk26
//A7B
void FlashingTOODEEP(void) {
    if((MSG&0x7F)==0x02) {
        // Once draw the specify needed area
        if(AlarmCode!=TOODEEP) {
            preAlarmCode=AlarmCode;
            AlarmCode=TOODEEP;
        }
        if(MSG==0x02) {
            WriteText_Title_4("TOO DEEP", 1);//Top
            LCD_SetColors(Red,Black);
            FontSet = (ptChar)myriad_bold_57;
            LCD_DisplayStringLine_Center(0,240,63,(UnitType_) ? "  ---  ?" :"  ---  `" );
        }
        else {
            DrawPart(RedTilte);
            ClearPart(BlackRectDepth);
        }
    }
}

//A18B //delayUntilMS(speed);
void FlashingTOOFAST(void) {
    if((MSG&0x7F)==0x01) {//MSG 01h/81h
        if(TOOFAST!=AlarmCode) {
            //writeBMP_nTimes((uint16_t const *)&BMP_A10A_top_X25Y0, 50,190,25,0,1);
            preAlarmCode=AlarmCode;
            AlarmCode=TOOFAST;
        }
        if(MSG==0x01) {
            DisplayASCBG();
            WriteText_Title_2("TOO FAST",5,White,Red);//Top
        }
        else {
            DrawPart(RedTilte);
            redrawScreenSection(217, 40,240, 285, (uint16_t const *)&BMP_S1A_right_X240Y40, 245,25,215,40);//ASCBG bar
        }
    }
}
//A21A
void FlashingDIVETIME(void) {
    if((MSG&0x7F)==0x05) {
        if(DIVETIME!=AlarmCode) {
            DrawPart(RedTilte);
            DrawPart(BlackRect_Right);
            DisplayEDT();
            preAlarmCode=AlarmCode;
            AlarmCode=DIVETIME;
        }
        if(MSG==0x05) {
            WriteText_Title_2("DIVE TIME",5,White,Red);//Top
            DisplayEDT();
        }
        else {
            LCD_FillRect(121, 118, 90, 45, Black);//redraw red rectangle
            DrawPart(RedTilte);
        }
    }
}
//A22A
void FlashingNITROGEN(void) {
    if((MSG&0x7F)==0x07) {
        if(NITROGEN!=AlarmCode) {
            preAlarmCode=AlarmCode;
            AlarmCode=NITROGEN;
        }
        if(MSG==0x07) {
            WriteText_Title_2("NITROGEN",5,Black,Yellow);//Top
            DisplayTLBG();
        }
        else {
            DrawPart(YellowTitle);
            redrawScreenSection(0, 40,22, 285, (uint16_t const *)&BMP_S1A_left_X0Y40, 245,25,0,40);
        }
    }
}
//A23A
void FlashingNODECOTIME(void) {
    if((MSG&0x7F)==0x08) {
        //Draw once
        if(NODECOTIME!=AlarmCode) {
            DisplayNDC();
            DrawPart(BlackRect_Left);
            preAlarmCode=AlarmCode;
            AlarmCode=NODECOTIME;
        }
        if(MSG==0x08) {
            DisplayNDC();
            WriteText_Title_2("NO DECO TIME",5,White,Red);//Top
        }
        else {
            LCD_FillRect(24, 130, 90, 30, Black);//Redraw the NDC number
            DrawPart(RedTilte);
        }
    }
}
//A24A
void FlashingTURNPSI(void) {
    if((MSG&0x7F)==0x09) { //MSG 09h/89h
        if(TURNPSI!=AlarmCode) {
            LCD_FillRect(22, 194, 110, 58, Black);//Draw full red rect
            DisplayPressure();
            preAlarmCode=AlarmCode;
            AlarmCode=TURNPSI;
        }
        if(MSG==0x09) {
            if(UnitType_) {
                WriteText_Title_2("TURN BAR",5,Black,Yellow);//Top
            }
            else {
                WriteText_Title_2("TURN PSI",5,Black,Yellow);//Top
            }
            DisplayPressure();
        }
        else {
            DrawPart(YellowTitle);
            LCD_FillRect(25, 199, 107, 34, Black);//Redraw red rect
        }
    }
}
//A25A
void FlashingENDPSI(void) {
    if((MSG&0x7F)==0x0A) { //MSG 0Ah/8Ah
        if(ENDPSI!=AlarmCode) {
            LCD_FillRect(22, 194, 110, 58, Black);//Draw full red rect
            DisplayPressure();
            preAlarmCode=AlarmCode;
            AlarmCode=ENDPSI;
        }
        if(MSG==0x0A) {
            if(UnitType_) {
                WriteText_Title_2("LOW BAR",5,White,Red);//Top
            }
            else {
                WriteText_Title_2("LOW PSI",5,White,Red);//Top
            }
            DisplayPressure();
        }
        else {
            DrawPart(RedTilte);
            LCD_FillRect(25, 199, 107, 34, Black);//Redraw red rect
        }
    }
}
void FlashingGASTIME(void) {
    if((MSG&0x7F)==0x06) { //MSG 06h/86h
        if(GASTIME!=AlarmCode) {
            preAlarmCode=AlarmCode;
            AlarmCode=GASTIME;
        }
        if(MSG==0x06) {
            if(0==GTR_Time) {
                WriteText_Title_2("GAS TIME",5,White,Red);//Top
            }
            if((GTR_Time>0)&&(GTR_Time<6)) {
                WriteText_Title_2("GAS TIME",5,Black,Yellow);//Top
            }
            DisplayGTR();
        }
        else {
            if(0==GTR_Time) {
                DrawPart(RedTilte);
            }
            if((GTR_Time>0)&&(GTR_Time<6)) {
                DrawPart(YellowTitle);
            }
            LCD_FillRect(136, 199, 81, 30, Black);//Draw full red rect
        }
    }
}
void FlashingWARNING_LowBattery(void) {
    if((MSG&0x7F)==0x15) { //MSG 15h/95h
        if(LOWBATTWARNING!=AlarmCode) {
            preAlarmCode=AlarmCode;
            AlarmCode=LOWBATTWARNING;
        }
        if(MSG==0x15) {
            LCD_FillRect(22, 118, 193, 75, Black);
            LCD_SetColors(Yellow, Black);
            FontSet = (ptChar)myriad_bold_25;
            LCD_DisplayStringLine_Center(0,240,125, "~~WARNING~~ LOW BATT");//y=125
        }
        else {
            if(0x90==MainMode) {
                LCD_FillRect(0, 118, 218, 76, Black);
            }
            else {
                DrawPart(BlackRectMiddle);
            }
        }
    }
}
void FlashingALARM_LowBatteryShutDown(void) {
    if((MSG&0x7F)==0x16) { //MSG 16h/96h
        if(LOWBATTSHUTDOWN!=AlarmCode) {
            preAlarmCode=AlarmCode;
            AlarmCode=LOWBATTSHUTDOWN;
        }
        if(MSG==0x16) {
            LCD_SetColors(Red,Black);
            FontSet = (ptChar)myriad_bold_25;
            LCD_FillRect(22, 118, 193, 75, Black);
            if(MainMode!=0x90) {
                LCD_DisplayStringLine(53, 125, "LOW BATT");
                LCD_DisplayStringLine(37, 155, "SHUT DOWN");
            }
            else {
                LCD_DisplayStringLine_Center(0,217,125, "~LOW BATT~ ~SHUT DOWN~~");//GAUGE MODE
            }
        }
        else {
            if(MainMode!=0x90) {
                DrawPart(BlackRectMiddle);
            }
            else {
                LCD_FillRect(0, 118, 217, 76, Black);
            }
        }
    }
}
// 2015/01/27 http://prntscr.com/5xlkjm
void FlashingALARM_LowBatteryShutDownArrow(void) {
    if((MSG&0x7F)==0x17) { //MSG 17h/97h
        if(LOWBATTSHUTDOWNUPARROW!=AlarmCode) {
            preAlarmCode=AlarmCode;
            AlarmCode=LOWBATTSHUTDOWNUPARROW;
        }
        if(MSG==0x17) {
            LCD_SetColors(Red,Black);
            FontSet = (ptChar)myriad_bold_25;
            LCD_FillRect(22, 118, 193, 75, Black);
            if(MainMode!=0x90) {
                LCD_DisplayStringLine(35, 125, "^LOW BATT^");
                LCD_DisplayStringLine(43, 155, "SHUT DOWN");
            }
            else {
                LCD_DisplayStringLine_Center(0,217,125, "^LOW BATT^ ~SHUT DOWN~~");//Middle with text
            }
        }
        else {
            if(MainMode!=0x90) {
                DrawPart(BlackRectMiddle);
            }
            else {
                LCD_FillRect(0, 118, 217, 76, Black);
            }
        }
    }
}
void FlashingASCBG(void) {
    if((ASCBG>70)&&(ASCBG<100)) {
        if((MSG&0x80)!=0x00) {
            redrawScreenSection(217, 40,240, 285, (uint16_t const *)&BMP_S1A_right_X240Y40, 245,25,215,40);//ASCBG bar
        }
        else {
            DisplayASCBG();
        }
    }
}
//A13A
void FlashingWARNING_PO2(void) {
    if((MSG&0x7F)==0x0B) { //MSG 0Bh/8Bh
        if(PO2WARNING!=AlarmCode) {
            preAlarmCode=AlarmCode;
            AlarmCode=PO2WARNING;
        }
        if(MSG==0x0B) {
            WriteText_Title_2("WARNING",5,Black,Yellow);//Top
            DisplayPO2Warning();
        }
        else {
            if(0x90==MainMode) {
                LCD_FillRect(0, 118, 218, 76, Black);
            }
            else {
                DrawPart(BlackRectMiddle);
            }
            DrawPart(YellowTitle);
        }
    }
}
void FlashingALARM_PO2(void) {
    if(MainMode==0x50) {
        if((MSG==0x80)||                //NORM
                (MSG==0x83)||                //EARMARK
                (MSG==0x95)||                //LOWBATTWARNING
                (MSG==0x96)||                //LOWBATTSHUTDOWN
                (MSG==0x97)) {         //LOWBATTSHUTDOWNUPARROW
            DrawPart(RedTilte);
        }
        if((MSG==0x00)||                //NORM
                (MSG==0x03)||                //EARMARK
                (MSG==0x15)||                //LOWBATTWARNING
                (MSG==0x16)||                //LOWBATTSHUTDOWN
                (MSG==0x17)) {                //LOWBATTSHUTDOWNUPARROW
            WriteText_Title_2("ALARM",5,White,Red);//Top
        }
        if((MSG==0x80)||//NORMAL
                (MSG==0x82)||//TOODEEP
                (MSG==0x81)||//TOOFAST
                (MSG==0x86)||//GASTIME
                (MSG==0x89)|| //TURNPSI
                (MSG==0x8A)|| //ENDPSI
                (MSG==0x87)|| //NITROGEN
                (MSG==0x84)//DEPTH
          ) {
            DrawPart(BlackRectMiddle);
        }
        if((MSG==0x00)                //NORMAL
                ||(MSG==0x02)        //TOODEEP
                ||(MSG==0x01)        //TOOFAST
                ||(MSG==0x06)        //GASTIME
                ||(MSG==0x09)         //TURNPSI
                ||(MSG==0x0A)         //ENDPSI
                ||(MSG==0x07)         //NITROGEN
                ||(MSG==0x04)        //DEPTH
          ) {
            DisplayPO2Alarm();
        }
    }
}
void DisplayAlternateDECOorNODECO(void) {
    if((MSG&0x7F)==0x0C) { //MSG == 0C/8Ch
        if((PO2ALARMGOUP!=AlarmCode)&&(PO2ALARM160!=AlarmCode)) {
            DrawPart(RedTilte);
            WriteText_Title_2("ALARM",5,White,Red);//Top
            if(TLBG<100) {
                if(PO2ALARMGOUP!=AlarmCode) {
                    preAlarmCode=AlarmCode;
                    AlarmCode=PO2ALARMGOUP;
                }
                //Draw NDC
                DrawPart(BlackRect_Left);
                DisplayNDC();
                //Draw EDT
                DrawPart(BlackRect_Right);
                DisplayEDT();
                DrawPart(LineVertical_1);
            }
            else {
                if(PO2ALARM160!=AlarmCode) {
                    preAlarmCode=AlarmCode;
                    AlarmCode=PO2ALARM160;
                }
                //Draw DECO
                DrawPart(BlackRect_Left);
                DisplayDECODepth();
                //Draw STOP
                DrawPart(BlackRect_Right);
                DisplayDECOTime();
            }
            DrawPart(LineHorizontal_1);
            DrawPart(LineHorizontal_2);
        }
    }
}

//A16A, A17A
void FlashingWARNING_O2SAT(void) {
    if((MSG&0x7F)==0x0E) { //MSG 0Eh/8Eh
        if(O2WARNING!=AlarmCode) {
            preAlarmCode=AlarmCode;
            AlarmCode=O2WARNING;
        }
        if(MSG==0x0E) {
            WriteText_Title_2("WARNING",5,Black,Yellow);//Top
            DisplayO2Warning();
        }
        else {
            if(0x90==MainMode) {
                LCD_FillRect(0, 118, 218, 76, Black);
            }
            else {
                DrawPart(BlackRectMiddle);
            }
            DrawPart(YellowTitle);
        }
    }
}
//A16B, A17B
void FlashingALARM_O2_GoUp(void) {
    if(MainMode==0x40) {
        if((MSG==0x80)||               //NORM
                (MSG==0x83)||          //EARMARK
                (MSG==0x95)||          //LOWBATTWARNING
                (MSG==0x96)||          //LOWBATTSHUTDOWN
                (MSG==0x97)) {         //LOWBATTSHUTDOWNUPARROW
            DrawPart(RedTilte);
        }
        if((MSG==0x00)||                //NORM
                (MSG==0x03)||           //EARMARK
                (MSG==0x15)||           //LOWBATTWARNING
                (MSG==0x16)||           //LOWBATTSHUTDOWN
                (MSG==0x17)) {          //LOWBATTSHUTDOWNUPARROW
            WriteText_Title_2("ALARM",5,White,Red);//Top
        }
        if((MSG==0x80)||//NORMAL
                (MSG==0x82)||//TOODEEP
                (MSG==0x81)||//TOOFAST
                (MSG==0x86)||//GASTIME
                (MSG==0x89)|| //TURNPSI
                (MSG==0x8A)|| //ENDPSI
                (MSG==0x87)|| //NITROGEN
                (MSG==0x84)//DEPTH
          ) {
            DrawPart(BlackRectMiddle);
        }
        if((MSG==0x00)||//NORMAL
                (MSG==0x02)||//TOODEEP
                (MSG==0x01)||//TOOFAST
                (MSG==0x06)||//GASTIME
                (MSG==0x09)|| //TURNPSI
                (MSG==0x0A)|| //ENDPSI
                (MSG==0x07)|| //NITROGEN
                (MSG==0x04)//DEPTH
          ) {
            DisplayO2Alarm();
        }
    }
}
void FlashingALARM_O2_SURFACE(void) {//ONLY DVSTAT 40h
    if((0x40==DVSTAT)&&((MainMode&BIT_5)==BIT_5)) { //MSG 10h/90h
        if((MSG&BIT_7)!=BIT_7) {
            DrawPart(RedTilte);
            WriteText_Title_2("ALARM",5,White,Red);//Top
            if(((MSG&0x7F)!=0x15)&&
                    ((MSG&0x7F)!=0x16)) {
                DrawPart(BlackRectMiddle);
                DisplayO2AlarmSurface();
                preAlarmCode=AlarmCode;
                AlarmCode=O2AlarmSurface;
            }
        }
        else {
            DrawPart(RedTilte);
            if(((MSG&0x7F)!=0x15)&&
                    ((MSG&0x7F)!=0x16)) {
                DrawPart(BlackRectMiddle);
                preAlarmCode=AlarmCode;
                AlarmCode=O2AlarmSurface;
            }
        }
    }
}

void FlashingVIOLATION(void) {
    if((MainMode&BIT_5) == BIT_5) {
        if((DVSTAT)==0x80) {//DVSTAT ==80h
            DrawPart(RedTilte);
            if((MSG&BIT_7)!=BIT_7) {
                WriteText_Title_2("VIOLATION",5,White,Red);//Top
            }
            preAlarmCode  = AlarmCode;
            AlarmCode     = VIOLATIONOnly;
        }
    }
}

//DS on the top right screen display
//http://prntscr.com/699r9m
void UpdateDS(void) {
    if((in_buf[34]&BIT_0)==BIT_0) {
        WriteText_Right_11("DS");//Right top text
    }
    else {
        LCD_FillRect(217, 9, 20, 13, Black);//Clear DS text 243 244 244
    }
}
//Blinking colon timming
void UpdateColonClock(u16 Color) {
    if((MSG&BIT_7)!=BIT_7) {
        LCD_SetColors(White, Color);
        FontSet = (ptChar)myriad_bold_14;
        if(!hrType) {
            LCD_DisplayChar(101, 20, ':');//Redraw (101,20) to (105,37)
        }
        else {
            LCD_DisplayChar(108, 20, ':');//Redraw (108,20) to (112,37)
        }
    }
    else {
        if((!hrType)&&(Color==Red)) {
            LCD_FillRect(101, 20, 4, 14, Red);
        }
        else if((hrType)&&(Color==Red)) {
            LCD_FillRect(108, 20, 4, 14, Red);
        }
        else if((!hrType)&&(Color==Grey)) {
            LCD_FillRect(101, 20, 4, 14, Grey);//Clear colon
        }
        else {
            LCD_FillRect(108, 20, 4, 14, Grey);//Clear colon
        }
    }
}

void UpdateNDC(void) {
    if((NDC_ != _preNDC) &&
            ((MSG& 0x7F) != 0x03)) {
        _preNDC = NDC_;
        DrawPart(BlackRect_Left);
        DisplayNDC();
    }
}
void UpdateEDT(void) {
    if((EDT != _preEDT) && ((MSG & 0x7F) != 0x03)) {
        _preEDT = EDT;
        DrawPart(BlackRect_Right);
        DisplayEDT();
    }
}
void FlashingTLBG(void) {
    if(TLBG>99) {
        if((MSG&BIT_7)!=BIT_7) {
            DisplayTLBG();
        }
        else {
            redrawScreenSection(0, 40,22, 285, (uint16_t const *)&BMP_S1A_left_X0Y40, 245,25,0,40);
        }
    }
}
void FlashingVIOLATIONGoUp(void) {
    //Flashing tittle
    if((MSG==0x80)||//NORM
            (MSG==0x83)||//EARMARK
            (MSG==0x95)||//LOWBATTWARNING
            (MSG==0x96)||//LOWBATTSHUTDOWN
            (MSG==0x97)//LOWBATTSHUTDOWNUPARROW
      ) {
        LCD_FillRect(38, 10, 165, 28, Red);
    }
    if((MSG==0x00)||//NORM
            (MSG==0x03)||//EARMARK
            (MSG==0x15)||//LOWBATTWARNING
            (MSG==0x16)||//LOWBATTSHUTDOWN
            (MSG==0x17)//LOWBATTSHUTDOWNUPARROW
      ) {
        WriteText_Title_2("VIOLATION",5,White,Red);//Top
    }
    //Flashing middle
    if((MSG==0x80)||//NORMAL
            (MSG==0x82)||//TOODEEP
            (MSG==0x81)||//TOOFAST
            (MSG==0x86)||//GASTIME
            (MSG==0x89)|| //TURNPSI
            (MSG==0x8A)|| //ENDPSI
            (MSG==0x87)|| //NITROGEN
            (MSG==0x84)//DEPTH
      ) {
        DrawPart(BlackRectMiddle);
    }
    if((MSG==0x00)||//NORMAL
            (MSG==0x02)||//TOODEEP
            (MSG==0x01)||//TOOFAST
            (MSG==0x06)||//GASTIME
            (MSG==0x09)|| //TURNPSI
            (MSG==0x0A)|| //ENDPSI
            (MSG==0x07)|| //NITROGEN
            (MSG==0x04)//DEPTH
      ) {
        WriteText_Middle_5(136, "^~GO UP~^",Red, Black);
    }
}

void FlashingDECOENTRY(void) {
    if((MSG&0x7F)==0x11) {
        DrawPart(RedTilte);
        redrawScreenSection(0, 40,22, 285, (uint16_t const *)&BMP_S1A_left_X0Y40, 245,25,0,40);
        if((MSG)== 0x11) {
            DisplayTLBG();
            DisplayDECODepth();
            DisplayDECOTime();
            WriteText_Title_4("DECO ENTRY", 1);//Top
        }
        preAlarmCode=AlarmCode;
        AlarmCode=DECOENTRY;
    }
}
void UpdateAlarmDiveMode(void) {
    FlashingTOOFAST();
    FlashingTOODEEP();
    FlashingDEPTH();
    FlashingNITROGEN();
    FlashingDIVETIME();//EDT
    FlashingNODECOTIME();//NDC
    UpdateEARMARKAPPLIED();
    FlashingTURNPSI();
    FlashingENDPSI();
    FlashingGASTIME();
    FlashingWARNING_LowBattery();
    FlashingALARM_LowBatteryShutDown();
    FlashingALARM_LowBatteryShutDownArrow();
    FlashingASCBG();
    FlashingWARNING_PO2();//
    FlashingWARNING_O2SAT();
    FlashingALARM_O2_GoUp();//DVSTAT 40h only
    FlashingALARM_PO2();//DVSTAT 50h only
}
////http://prntscr.com/5ymzz2


void redrawScreen(uint16_t Xpos1, uint16_t Ypos1,uint16_t Xpos2, uint16_t Ypos2,uint16_t Color) {
    uint16_t Width,  Height;
    uint16_t Xpos,  Ypos;
    Xpos   =  Xpos1;
    Ypos   =  Ypos1;
    Width  =  Xpos2 - Xpos1+1;
    Height  = Ypos2 - Ypos1;

    LCD_SetBackColor(Color);
    LCD_SetTextColor(Color);
    LCD_DrawFullRect(Xpos, Ypos, Width, Height);
}
void ClearPart(u8 Screen) {
    switch(Screen) {
    case LineVertical_1:
        LCD_FillRect(120, 118, 1, 76, Black);//http://prntscr.com/7234bq
        break;
    case BlackRectDepth:
        LCD_FillRect(25, 63, 180, 40, Black);
        break;
    case ASCBG_Bar:
        redrawScreen(215, 24, 240, 280, Black);
        break;
    case TLBG_Bar:
        LCD_FillRect(0, 42, 23, 250, Black);
        break;
    case Temperature_Style_1:
        LCD_FillRect(36, 20, 36, 14, Grey);
        break;
    case Temperature_Style_2:
        LCD_FillRect(36, 20, 36, 14, Red);
        break;
    case Current_Depth:
        //redrawScreen(23, 63,215, 103, Black);//114
        redrawScreen(23, 47,215, 116, Black);
        break;
    case Current_Depth_Compass:
        redrawScreen(23, 54,215, 103, Black);
        break;
    case SurfaceTime://Clear all the area display include SURF text
        redrawScreen(25, 55,215, 114, Black);
        break;
    case GasTimeRemain:
        LCD_FillRect(135, 194, 82, 56, Black);
        //LCD_FillRect(177, 234, 1, 12, 0x8C71);//The Vertical line
        break;
    case Pressure:
        redrawScreen(22, 194,133, 251, Black);
        break;
    case DsatZpuls:
        switch(in_buf[OPCODE_BYTE]) {
        //case DIVE_MODE:
        case LOG:
        case HOME_MENU:
            redrawScreen(0, 8 ,31, 21, BG_BOT);/*top left DSAT/Z+*/
            break;
        default:
            redrawScreen(0, 8 ,31, 21, Black);
            break;
        }
        break;
    case DS:
        LCD_FillRect(217, 9, 20, 13, Black);//Clear DS text 243 244 244
        break;
    case BottomTitle:
        LCD_FillRect(0, 300, 240, 20, BG_BOT);
        break;
    case BottomTitle_Red:
        LCD_FillRect(0, 300, 240, 20, Red);
        break;
    case TopTitle:
        LCD_FillRect(0, 38, 240, 26, BG_BOT);
        break;
    case CompassArrrow_Left_Yellow:
        LCD_FillRect(30, 118, Arrow_Yellow.width+1, Arrow_Yellow.height+1, Black);
        break;
    case CompassArrrow_Right_Yellow:
        LCD_FillRect(196, 118, Arrow_Yellow.width+1,Arrow_Yellow.height+1, Black);
        break;
    case ReferenceDot:
        LCD_DrawBMP(preRefPointX,preRefPointY, (ptImage)&RefPointClearImage, 0);
        break;
    case ReverseDot:
        LCD_DrawBMP(preRevPointX,preRevPointY, (ptImage)&RefPointClearImage, 0);
        break;
    case CompassArrrow:
        LCD_FillRect(30, 118, Arrow_Yellow.width+1, Arrow_Yellow.height+1, Black);
        LCD_FillRect(196, 118, Arrow_Yellow.width+1,Arrow_Yellow.height+1, Black);
        break;
    case ReferenceAngle:
        LCD_FillRect(0, 282, 65 , 14, Black);
        break;
    case LogData_Update:
        LCD_FillRect(0, 38, 240, 26, BG_BOT);
        redrawScreen(146, 70, 240, 300, BG_RIGHT);//RIGHT
        LCD_SetTextColor(Black);
        LCD_DrawLine(145,120,95,LCD_DIR_HORIZONTAL);
        LCD_DrawLine(145,164,95,LCD_DIR_HORIZONTAL);
        LCD_DrawLine(145,206,95,LCD_DIR_HORIZONTAL);
        LCD_DrawLine(145,243,95,LCD_DIR_HORIZONTAL);
        break;
    case BlackRectLogData:
        redrawScreen(0, 108,144, 290, Black);
        break;
    case ItemPreviewUnSelect:
        LCD_FillRect(0, 84+(23*(preMSG-1)), 146, 23,Black);
        LCD_FillRect(0, 83+(23*preMSG), 146, 1, White);
        LCD_SetColors(White, Black);
        FontSet = (tChar*)myriad_bold_16;
        LCD_DisplayStringLine(7,85+((preMSG-1)*23), _RowSetPreview[preMSG-1].Row_String_Left);//Sel 0x10 >> 4 = 1
        break;
    default:
        break;
    }
}
void DrawPart(u8 Part) {
    switch(Part) {
    case LineVertical_1:
        LCD_FillRect(120, 117, 1, 76, White);
        break;
    case LineVertical_2:
        LCD_FillRect(120, 118, 1, 76, Black);;//Clear the previous vertical line first BUG 68
        LCD_FillRect(120, 140, 1, 53, White);
        break;
    case LineVertical_3:
        LCD_FillRect(134, 200, 1, 50, White);
        break;
    case LineHorizontal_1:
        LCD_FillRect(23, 117, 195, 1, White);
        break;
    case LineHorizontal_2:
        LCD_FillRect(23, 193, 190, 1, White);
        break;
    case LineHorizontal_3:
        LCD_FillRect(0, 117, 213, 1, White);
        break;
    case LineHorizontal_4:
        LCD_FillRect(0, 193, 213, 1, White);
        break;
    case LineHorizontal_5:
        LCD_FillRect(145, 170, 95, 1, Black);
        break;
    case LineHorizontal_6:
        LCD_FillRect(145, 185, 95, 1, Black);
        break;
    case LineHorizontal_7:
        LCD_FillRect(30, 103, 190, 1, White);
        break;
    case LineHorizontal_8:
        LCD_FillRect(23, 112, 195, 1, White);
        break;
    case LineHorizontal_9:
        LCD_FillRect(145, 130, 95, 1, Black);
        break;
    case HomeMenu_Battery:
        LCD_SetColors(Black, White);
        LCD_DrawChar(150, 5, (ptImage)&Image_Battery);
        break;
    case Surface_Battery:
        LCD_SetColors(Black, Grey);
        LCD_DrawChar(150, 20, (ptImage)&Image_Battery);
        break;
    case ASCBG_Bar:
        writeBMP_nTimes((uint16_t*)BMP_S1A_right_X240Y40, 245,25,215,40,1);
        break;
    case TLBG_Bar:
        writeBMP_nTimes((uint16_t*)BMP_S1A_left_X0Y40, 245,25,0,40,1);//TLBG bar
        break;
    case BlackRectMiddle:
        LCD_FillRect(23, 118, 193, 75, Black);
        break;
    case BlackRect_Right:
        LCD_FillRect(121, 118, 95, 75, Black);//Draw black rectangle
        break;
    case BlackRect_Left:
        LCD_FillRect(22, 118, 98, 75, Black);
        break;
    case SurfaceTime:
        LCD_SetColors(Blue, Black);
        FontSet = (ptChar)myriad_bold_12;
        LCD_DisplayStringLine(150,97, "hr:min");//
        FontSet = (ptChar)myriad_bold_38;
        LCD_DisplayStringLine(141,62, ":");
        PrepareSurfTime();
        DisplaySurfHr();
        DisplaySurfMin();
        FontSet = (ptChar)myriad_bold_19;
        LCD_DisplayStringLine(36,61, "SURF");//
        break;
    case SurfaceTimeforCompass:
        LCD_SetColors(Blue, Black);
        FontSet = (ptChar)myriad_bold_12;
        LCD_DisplayStringLine(150,87, "hr:min");//
        FontSet = (ptChar)myriad_bold_38;
        LCD_DisplayStringLine(141,52, ":");
        PrepareSurfTime();
        DisplaySurfHrCompass();
        DisplaySurfMinCompass();
        FontSet = (ptChar)myriad_bold_19;
        LCD_DisplayStringLine(36,51, "SURF");//
        break;
    case TitleBar_Norm://http://prntscr.com/5zynvx
        LCD_DrawBMP(33, 0, (ptImage)&TitleBarGrey, 0);
        DisplayMainTitle(_MainTitle[0]);
        DisplayTemper_Pos1();
        DisplayBattery_Pos1();
        DisplayClock_Pos1();
        LCD_FillRect(78, 20, 1, 20, TextColor);
        LCD_FillRect(144, 20, 1, 20, TextColor);
        break;
    case TitleBar_NORTH:
        LCD_DrawBMP(33, 0, (ptImage)&TitleBarGrey, 0);
        DisplayMainTitle(_MainTitle[6]);
        DisplayTemper_Pos1();
        DisplayBattery_Pos1();
        DisplayClock_Pos1();
        LCD_FillRect(78, 20, 1, 20, TextColor);
        LCD_FillRect(144, 20, 1, 20, TextColor);
        break;
    case TitleBar_Reference:
        LCD_DrawBMP(33, 0, (ptImage)&TitleBarGrey, 0);
        DisplayMainTitle(_MainTitle[7]);
        DisplayTemper_Pos1();
        DisplayBattery_Pos1();
        DisplayClock_Pos1();
        LCD_FillRect(78, 20, 1, 20, TextColor);
        LCD_FillRect(144, 20, 1, 20, TextColor);
        break;
    case TitleBar_SetReverse:
        LCD_DrawBMP(33, 0, (ptImage)&TitleBarGrey, 0);
        DisplayMainTitle(_MainTitle[9]);
        DisplayTemper_Pos1();
        DisplayBattery_Pos1();
        DisplayClock_Pos1();
        LCD_FillRect(78, 20, 1, 20, TextColor);
        LCD_FillRect(144, 20, 1, 20, TextColor);
        break;
    case TitleBar_Reverse:
        LCD_DrawBMP(33, 0, (ptImage)&TitleBarGrey, 0);
        DisplayMainTitle(_MainTitle[10]);
        DisplayTemper_Pos1();
        DisplayBattery_Pos1();
        DisplayClock_Pos1();
        LCD_FillRect(78, 20, 1, 20, TextColor);
        LCD_FillRect(144, 20, 1, 20, TextColor);
        break;
    case TitleBar_Deco:
        LCD_DrawBMP(33, 0, (ptImage)&TitleRedBar, 0);
        LCD_DisplayText(0, 240, 0, (ptChar)myriad_bold_17, White, Red, AlignCenter, _MainTitle[2]);
        DisplayTemper_Pos2();
        DisplayBattery_Pos3();
        DisplayClock_Pos2();
        LCD_FillRect(78, 20, 1, 20, TextColor);
        LCD_FillRect(144, 20, 1, 20, TextColor);
        break;
    case TitleBar_GAUG:
        LCD_DrawBMP(33, 0, (ptImage)&TitleBarGrey, 0);
        DisplayMainTitle(_MainTitle[1]);
        DisplayTemper_Pos1();
        DisplayBattery_Pos1();
        DisplayClock_Pos1();
        LCD_FillRect(78, 20, 1, 20, TextColor);
        LCD_FillRect(144, 20, 1, 20, TextColor);
        break;
    case TitleBar_NormViolation:
        LCD_DrawBMP(33, 0, (ptImage)&TitleRedBar, 0);
        LCD_DisplayText(95, 240, 0, (ptChar)myriad_bold_17, White, Red, AlignLeft, _MainTitle[0]);
        DisplayBattery_Pos3();
        DisplayTemper_Pos2();
        DisplayClock_Pos2();
        LCD_FillRect(78, 20, 1, 20, TextColor);
        LCD_FillRect(144, 20, 1, 20, TextColor);
        break;
    case TitleBar_Violation:
        LCD_DrawBMP(33, 0, (ptImage)&TitleRedBar, 0);
        WriteText_Title_2("VIOLATION",5,White,Red);//Top
        break;
    case TitleBar_SetHeading:
        LCD_DrawBMP(33, 0, (ptImage)&TitleBarGrey, 0);
        DisplayMainTitle(_MainTitle[8]);
        DisplayTemper_Pos1();
        DisplayBattery_Pos1();
        DisplayClock_Pos1();
        LCD_FillRect(78, 20, 1, 20, TextColor);
        LCD_FillRect(144, 20, 1, 20, TextColor);
        break;
    case O2_100Solid:
        LCD_DrawBMP(33, 0, (ptImage)&TitleRedBar, 0);
        WriteText_Title_2("ALARM",5,White,Red);//Top
        //LCD_FillRect(22, 115, 197, 76, Black);
        DrawPart(BlackRectMiddle);
        DrawPart(LineHorizontal_1);
        DisplayO2AlarmSurface();
        break;
    case RedTilte:
        LCD_DrawBMP(33, 0, (ptImage)&TitleRedBar, 0);
        break;
    case YellowTitle:
        LCD_DrawBMP(33, 0, (ptImage)&YellowTitleBar, 0);
        break;
    case GreyTitle:
        LCD_DrawBMP(33, 0, (ptImage)&TitleBarGrey, 0);
        break;
    case BlackRect_LeftMenu:
        redrawScreen(0, 70, 145, 300, Black);//LEFT
        break;
    case WhiteRect_RightMenu:
        redrawScreen(146, 70, 240, 300, BG_RIGHT);//RIGHT
        break;
    case WhiteHalfRect_RightMenu:
        redrawScreen(146, 70, 240, 184, BG_RIGHT);//RIGHT
        break;
    case PO2_DiveMenu:
        redrawScreen(146, 70, 240, 169, BG_RIGHT);//RIGHT
        break;
    case MainMenu_TopTitle:
        //writeBMP_nTimes((uint16_t *)BMP_H1B_Top, 31,178,31,0,1);
        LCD_DrawBMP((240-Image_MainMenu_TopTitle.width)/2, 0,(ptImage)&Image_MainMenu_TopTitle,0);
        break;
    case HomeMenu_TopTitle:
        LCD_DrawBMP((240-Image_HomeMenu_TopTitle.width)/2, 0,(ptImage)&Image_HomeMenu_TopTitle,0);
        break;
    case TopTitle:
        LCD_FillRect(0, 0, 240, 70, BG_BOT);
        break;
    case Compass_Base:
        LCD_DrawBMP((240-CompassBase.width)/2, 120,(ptImage)&CompassBase,0);
        LCD_FillRect(118, 153, 4, 35, White);// 2 lines
        LCD_FillRect(118, 217, 4, 35, White);// 2 lines
        break;
    case ReferenceDot:
        switch(LORR) {
        case 0:
            LCD_SetColors(White, Black);
            break;
        default:
            LCD_SetColors(Yellow, Black);
            break;
        }
        if(DISA>REF) {
            LCD_DrawChar(RefPoint[(DISA-REF)%360].X,RefPoint[(DISA-REF)%360].Y, (ptImage)&RefPointImage);
            preRefPointX=RefPoint[(DISA-REF)%360].X;
            preRefPointY=RefPoint[(DISA-REF)%360].Y;
        }
        else {
            LCD_DrawChar(RefPoint[(360-REF + DISA)%360].X,RefPoint[(360-REF + DISA)%360].Y, (ptImage)&RefPointImage);
            preRefPointX=RefPoint[(360-REF + DISA)%360].X;
            preRefPointY=RefPoint[(360-REF + DISA)%360].Y;
        }
        break;
    case ReverseDot:
        switch(LORR) {
        case 0:
            LCD_SetColors(White, Black);
            break;
        default:
            LCD_SetColors(Yellow, Black);
            break;
        }
        if(DISA>REV) {
            LCD_DrawChar(RefPoint[(DISA-REV)%360].X,RefPoint[(DISA-REV)%360].Y, (ptImage)&RefPointImage);
            preRevPointX=RefPoint[(DISA-REV)%360].X;
            preRevPointY=RefPoint[(DISA-REV)%360].Y;
        }
        else {
            LCD_DrawChar(RefPoint[(360-REV + DISA)%360].X,RefPoint[(360-REV + DISA)%360].Y, (ptImage)&RefPointImage);
            preRevPointX=RefPoint[(360-REV + DISA)%360].X;
            preRevPointY=RefPoint[(360-REV + DISA)%360].Y;
        }
        break;
    case CompassArrrow_Left_Yellow:
        //flashing compass arrow
        if((MSG&BIT_7)!=BIT_7) {
            LCD_DrawBMP(30, 118,(ptImage)&Arrow_Yellow,0);
        }
        else {
            ClearPart(CompassArrrow_Left_Yellow);
        }
        ClearPart(CompassArrrow_Right_Yellow);
        break;
    case CompassArrrow_Right_Yellow:
        //flashing compass arrow
        if((MSG&BIT_7)!=BIT_7) {
            LCD_DrawBMP(196, 118,(ptImage)&Arrow_Yellow,2);
        }
        else {
            ClearPart(CompassArrrow_Right_Yellow);
        }
        ClearPart(CompassArrrow_Left_Yellow);
        break;
    case TopCompass_Yellow:
        LCD_DrawBMP(((240-TopCompassYellow.width)/2), 113, (ptImage)&TopCompassYellow, 0);
        break;
    case TopCompass_Green:
        LCD_DrawBMP(((240-TopCompassGreen.width)/2), 113, (ptImage)&TopCompassGreen, 0);
        break;
    case ItemPreviewSelected:
        //Menstat 00/01/02..08
        LCD_FillRect(0, 84+23*(MENSTAT-1), 146, 23, Green);
        LCD_SetColors(Black, Green);
        FontSet = (tChar*)myriad_bold_16;
        LCD_DisplayStringLine(7,85+((MENSTAT-1)*23), _RowSetPreview[MENSTAT-1].Row_String_Left);//Sel 0x10 >> 4 = 1
        break;
    default:
        break;
    }
}
void LCD_DisplayText(u16 posX1,u16 posX2, u16 posY, ptChar fontsize, u16 colortext, u16 colorbackground, Align _AlignType, char*content) {
    LCD_SetColors(colortext, colorbackground);
    FontSet=fontsize;
    switch(_AlignType) {
    case AlignCenter:
        LCD_DisplayStringLine_Center(posX1, posX2, posY, content);
        break;
    case AlignRight:
        LCD_DisplayStringLine(posX1, posY, content);
        break;
    case AlignLeft:
        LCD_DisplayStringLine(posX1, posY,content);
        break;
    }
}
#endif
