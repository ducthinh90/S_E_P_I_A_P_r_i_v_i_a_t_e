
/****************************************************************/
// Author: PhuThinh
// Date: 2/25/14
// Desc: handle backrounds for lcd
//C:\Users\PhuThinh\AppData\Roaming\Skype\My Skype Received Files
/****************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "alldefs.h"
#include "backgrounds.h"
#include <stdlib.h>
#include<stdio.h>
//#include "text.h"
#include "flashmem.h"
#include "stm32f2xx_rtc.h"
#include "math.h"
#include "stm32f2xx_iwdg.h"
#include <string.h>
#include <stdlib.h>
#include "sysUtils.h"
#include "IconSEPIA.h"
#include "ShapeSEPIA.h"
#define USE_SONAR   1

#ifdef USE_SONAR
#include "sonarCtrl.h"
#include "sonarCmd.h"
extern NAVIGATE_CTRL *pSCB;
extern void getPartnerIDList(void);
extern P_DAT pList[];
#endif
//to do
//thinking how to update selection, text on the right, update at BG or text??
//prepare data as buff, data temp
//seperate display time,date as OCX
// icon file = 75%
extern const uint16_t BMP_AR1[188][20];
extern const uint16_t BMP_TL_1[188][19];
extern const uint16_t BMP_Home_bot[20][320];
extern const uint16_t BMP_back[11][13];
extern const uint16_t BMP_H2_HistoryX15Y90[77][78];
extern const uint16_t BMP_SET_GAS[57][57];
extern const uint16_t BMP_DATE_TIME[57][57];
extern const uint16_t BMP_Alarm[57][57];
extern const uint16_t BMP_SET_TMT[57][60];
extern const uint16_t BMP_Brightness[57][60];
extern const uint16_t BMP_compass[57][60];
extern const uint16_t BMP_Bluetooth[57][60];
extern const uint16_t BMP_Utility[57][60];
extern const uint16_t BMP_NI_O2[57][60];

extern const uint16_t BMP_BMP_H_TOP[21][320];
extern const uint16_t BMP_TL[188][19] ;
extern const uint16_t BMP_AR[186][20];
extern const uint16_t BMP_icons_clock[47][34];

extern const uint16_t BMP_icon_wifi[48][20] ;
extern const uint16_t BMP_icon_gas[49][21];
extern const uint16_t BMP_icon_D25[19][105];
extern const uint16_t BMP_icon_ds[20][28];
extern const uint16_t BMP_icon_TMT[43][23];
extern const uint16_t BMP_H74_icons[162][280] ;
extern const uint16_t BMP_SO13_bot[23][320];
extern const uint16_t BMP_Sepia_TL[188][19];


extern const uint16_t BMP_History[60][60];
extern const uint16_t BMP_History_Sel[60][60];
extern const uint16_t BMP_Navigation[60][60];
extern const uint16_t BMP_Navigation_Sel[60][60];
extern const uint16_t BMP_MyInfo[60][60];
extern const uint16_t BMP_MyInfo_Sel[60][60];

extern const uint16_t BMP_OPMode[60][60];
extern const uint16_t BMP_OPMode_Sel[60][60];

extern const uint16_t BMP_GoDive[60][60] ;
extern const uint16_t BMP_GoDive_Sel[60][60] ;

extern const uint16_t BMP_SepiaInfo[60][60];
extern const uint16_t BMP_SepiaInfo_Sel[60][60];

extern const uint16_t BMP_Setting[60][60];
extern const uint16_t BMP_Setting_Sel[60][60] ;

extern const uint16_t BMP_Log[60][60] ;
extern const uint16_t BMP_Log_Sel[60][60] ;

extern const uint16_t BMP_TMTStatus[60][60];
extern const uint16_t BMP_TMTStatus_Sel[60][60] ;


extern const uint16_t BMP_SetTMT[57][57];
extern const uint16_t BMP_SetTMT_Sel[57][57];


extern const uint16_t BMP_Menu_Top[21][320];

extern const uint16_t BMP_SetID[57][57];
extern const uint16_t BMP_SetID_Sel[57][57] ;

extern const uint16_t BMP_NavMode[57][57] ;
extern const uint16_t BMP_NavMode_Sel[57][57];

extern const uint16_t BMP_Chanel[57][57];
extern const uint16_t BMP_Chanel_Sel[57][57];

extern const uint16_t BMP_Paring[57][57] ;
extern const uint16_t BMP_Paring_Sel[57][57];

extern const uint16_t BMP_SetSMS[57][57];
extern const uint16_t BMP_SetSMS_Sel[57][57] ;

extern const uint16_t BMP_Partner[57][57];
extern const uint16_t BMP_Partner_Sel[57][57] ;

extern const uint16_t BMP_ABParing[62][76];
extern const uint16_t BMP_Select[16][23];
extern const uint16_t BMP_save[13][29];

/*SETTING*/



extern const uint16_t BMP_Sonar_Top[20][320];
extern const uint16_t BMP_Mail[15][19];
extern const uint16_t BMP_up_down[52][27];
extern const uint16_t BMP_Up[18][21];
extern const uint16_t BMP_Down[18][21] ;
extern const uint16_t BMP_ReSync[70][61];
extern const uint16_t BMP_ReSync_Complete[114][109] ;
extern const uint16_t BMP_ReSync_Fail[110][74] ;
extern const uint16_t BMP_NIO2[39][37];
extern const uint16_t BMP_Sonar_circle[182][186];

extern const uint16_t BMP_Mail_Red[17][21];
extern const uint16_t BMP_Mail_SOS[17][21];

extern const tChar myriad_bold_9[];
extern const tChar myriad_bold_10[];
extern const tChar myriad_bold_11[];

extern const tChar myriad_bold_12[];
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
extern const tChar myriad_bold_25[];
extern const tChar myriad_bold_28[];
extern const tChar myriad_bold_30[];
extern const tChar myriad_bold_32[];
extern const tChar myriad_bold_35[];
extern const tChar myriad_bold_40[];
extern const tChar myriad_bold_42[];
extern const tChar myriad_bold_45[];
extern const tChar myriad_bold_50[];
extern const tChar myriad_bold_57[];
extern const tChar myriad_norm_17[];

enum {NORM, GAUGE};
u8 OP_mode = NORM;
u8 set_tmt_flat = 0;//0 = set/on hightlight, 1 = set serial highlight
u16 len =0;
u8 midnight; //0: AM ; 1: PM  '{' : '|'
u8 hh ;
u8 mm ;
u8 _premm;
u8 _prehh;
u8 _premidnight;
u8 hr_buf[3];//Hour buffer
u8 min_buf[3];//Minute buffer
extern volatile u8 screenCod;
volatile u8 PrescreenCod = BLACK;
uint8_t Midday[6] ;
uint8_t TL_buf[3];
uint8_t AR_buf[3];
u8 Bat = 75;
u8 Temp = 65;
volatile u8 screenCodnext = SO8;
//volatile u8 screenCodnext = Hz;

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define IsNormMode                  ((in_buf[5]&0x01) == 0)


#define PI        3.1415926
float Deg = 0;
uint16_t Deg_cp = 0;
uint16_t X_Sum[500], Y_Sum[500];

uint16_t Point_circle = 0;
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u8 previous_sel = Sel_line1 ;
u8 current_sel  = Sel_line1;
u8 current_stop = 0;
u8 precurrent_stop = 0;
uint8_t _preTEMP = 0;


//extern PlanBuffer _PlanBuffer[17];
volatile u8 ST_ready_get_data = 1;


u8 Redbar_flat = sel_col;
u8 main_menu = sel_col;

/*demo data*/
//uint8_t number_test = 0;
//uint16_t deep = 0;
//extern uint16_t pressure;
//uint16_t timeCounter = 0;//update each avery 1/2 sec

extern uint8_t hh ;
extern uint8_t mm ;
uint8_t premm = 0xff;
//uint8_t preSurmm = 0xff;

u8 surf_h = 59;
u8 surf_m = 33;
u8 presurf_m = 0xff;

uint8_t ss= 00;
enum {AM_, PM_};
extern uint8_t midnight;

uint8_t display = 1;
enum {waitdata, gotdata};
uint8_t DataFromTI = waitdata;
enum {FLASH_OFF,FLASH_ON};
u8 Flashing_flat = FLASH_OFF;
u16 PreGTR_Time = 0;
u16 PreGas_Num = 1;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* extern variables ---------------------------------------------------------*/

extern uint8_t FREQUENCY;
extern uint8_t FREQUENCY_NOM;
extern uint8_t FREQUENCY_HIGH;
extern  uint16_t row;
extern   uint16_t col;
extern  uint16_t TextColor  ;
extern  uint16_t  BackColor;
extern volatile u8 PrescreenCod;
extern volatile u8 screenCod;


extern const tChar myriad_bold_15[];
extern const tChar myriad_bold_22[];
//extern const tChar myriad_bold_12[];
//extern const tChar myriad_bold_11[];
//extern const tChar myriad_bold_14[];
//extern const tChar myriad_bold_15[];
//extern const tChar myriad_bold_16[];
//extern const tChar myriad_bold_17[];
//extern const tChar myriad_normal_17[];
//extern const tChar myriad_bold_22[];
extern const tChar myriad_bold_38[];
extern const tChar *FontSet ;

extern uint8_t *sBuf;

const tImage *CurrentChar;


//extern signed int temper;
extern uint8_t pretemper;
//extern uint8_t u8_bat;
//extern float  PO2num;
extern uint8_t TL_per;
extern  uint8_t AR_per;
extern  uint8_t divetime;
extern  uint8_t ATRnum_;
//extern  uint8_t FO2num;
uint8_t PreFO2num = 0xff;
float  PrePO2num= 0xff;
extern uint16_t  FTnum;
extern uint8_t prebat;
uint8_t predivetime = 2;
uint8_t preATRnum_ = 0;
uint8_t preAIRnum_ = 0;
uint8_t preTL_per = 0;
uint8_t preAR_per = 0;
uint16_t  preFTnum = 0;
//u8 PreGas_Num = 1;

extern uint8_t SN1;
extern uint8_t SN2;
extern uint8_t SN3;

extern u8 Reset_buf[5];
extern u8 ReCoHigh ;
extern u8 ReCoLow ;

extern uint8_t  u8_BrightNess ;
extern uint8_t BrightNess_buf[8];
u8 debug_decode = 0;
u8 previousOP = 0x20;


//u8 dateformat = 0;
//u8 timeformat = 0;
//u8 month = 0;
//u8 day = 0;
//u8 year = 0;
//u8 munite = 0;
//u8 hour = 0;
uint8_t Premidnight  = 0;
u8 USB_Precount = 0;
u8 BT_Precount = 0;

extern u8 Month;        //OPCODE = 20H. MENSTAT = 21H, 22H and 23H. Total is 15 bytes
extern u8 Day;
extern u8 Year;
extern u8 rev_1;
extern u8 rev_2;

u8 hrType;
u8 UnitType_;
extern u8 AudAlarm;
uint8_t MD;
extern u8 FO2default;
extern u8 FO2default;  //BIT 4: 0 = 50% default OFF/ 1 = ON

extern uint8_t *TextRight4;
extern uint8_t *TextRight4_0;
extern u8 MD_buf[9];
extern u8 AutoDim ;//AUTO DIM:  BIT 6: 0 =  OFF, 1 = ON


uint8_t time_buf[6];
extern uint8_t deep_buf[6];
extern uint8_t pressure_buf[6];
extern uint8_t SurfTime_buf[6];
extern  uint8_t temper_buf[6];
char battery_buf[6];
extern  uint8_t divetime_buf[6];
extern uint8_t GTRnum_buf[6];
extern uint8_t FO2num_buf[6];
extern uint8_t PO2num_buf[7];
extern uint8_t FTnum_buf[8];
//extern  uint8_t TL_buf[6];


extern u8 maxDivetime_buf[6];
extern u8 aveDivenum_buf[6];
extern u8 maxDepth_buf[6];
extern u8 aveDepth_buf[6];
extern u8 lowestTemp_buf[6];
extern u8 totalDive_buf[6];
extern u8 SampleRate_buf[8];
extern u8 Altitude_buf[5];


extern uint8_t DiveNum_buf[3];//DIVE# = Dive number from 0 to 24 in BINARY.
extern uint8_t EDTnum_buf[6];
extern uint8_t DTRnum_buf[6];
extern uint8_t TLBGnum_buf[6];
extern uint8_t NDCnum_buf[6];
extern uint8_t O2num_buf[6];
extern uint8_t DepNum_buf[8];
extern uint8_t totalDiveTime_buf[6];
extern u8 CountDown_Str[8];
extern uint8_t EDT_TimeBuf[8];

extern uint8_t FLYtime_buf[13];//OPCODE 14H
extern uint8_t DESATtime_buf[13];//OPCODE 14H
extern u8 TurnString[10];
extern u8 EndString[10];


float PremaxDepth = 0;
u16 PreEDT = 0;
u8 PreAltitude = 0;
u8 PreO2SAT;
u16 PreFLYTime = 0;
u16 PreDESATTime;
u8 PreFO2_Num = 0;
float PrePO2_Num =0;


u8 PreRowHighLight=        0;
u8 PreStartPlan = 0;
u8 PreEndPlan = 0;

u8 PreStartLog = 0;
u8 PreEndLog = 0;

u8 PreDSAT_bit = 0;
//float maxDepth =0;
extern u8 FO2_Air_flat ;

u8 PreStartTime_mm = 0;
u8 PreStartTime_hh = 0;

u8 PreDiveTime = 0;

u8 PreMaxDepth= 0;
u8 PreElevation= 0;
u16 PreStartPress= 0;
u16 PreEndPress= 0;
u16 PreaveDepth= 0;
uint8_t _Temper_buf[6];
/**************************************************************************/
// Author: PhuThinh
// Date: 4/1/2014
// Desc: displayBackground
// INPUTs:
//                  * @param  screenCode: BG code
// OUTPUTs:
//                 @retval none
//
/**************************************************************************/
/*
Point X_Ypos[3] = {
                                {120,80},
                                {60,240},
                                {180,240},
                                };

pPoint Points_test = &X_Ypos;
*/

//extern uint16_t page_ch ;

/**************************************************************************/
// Author: PhuThinh
// Date: 2/27/2014
// Desc: Draw a full ellipse.
// INPUTs:
//                  * @param  Xpos: specifies the X position, can be a value from 0 to 240.
//                  * @param  Ypos: specifies the Y position, can be a value from 0 to 320.
//                  * @param  Radius: specifies Radius.
//                  * @param  Radius2: specifies Radius2.
//                  * @param  quadrant: 1,2,3,4.
// OUTPUTs:
//                @retval None
//
/**************************************************************************/

void LCD_DrawEllipse_Part(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, uint16_t Radius2, u8 quadrant)
{
    int x = -Radius, y = 0, err = 2-2*Radius, e2;
    float K = 0, rad1 = 0, rad2 = 0;

    rad1 = Radius;
    rad2 = Radius2;

    if (Radius > Radius2)
    {
        do
        {
            K = (float)(rad1/rad2);


            if(quadrant == 1) {
                LCD_DrawLine((Xpos-x), (Ypos-(uint16_t)(y/K)), (2*(uint16_t)(y/K) + 1)/2, LCD_DIR_VERTICAL);
            }
            else if(quadrant == 2) {
                LCD_DrawLine((Xpos+x), (Ypos-(uint16_t)(y/K)), (2*(uint16_t)(y/K) + 1)/2, LCD_DIR_VERTICAL);
            }
            else if(quadrant == 3) {
                LCD_DrawLine((Xpos+x), (Ypos-(uint16_t)(y/K) +(2*(uint16_t)(y/K) + 1)/2), (2*(uint16_t)(y/K) + 1)/2, LCD_DIR_VERTICAL);
            }
            else if(quadrant == 4) {
                LCD_DrawLine((Xpos-x), (Ypos-(uint16_t)(y/K)+(2*(uint16_t)(y/K) + 1)/2), (2*(uint16_t)(y/K) + 1)/2, LCD_DIR_VERTICAL);

            }
            e2 = err;
            if (e2 <= y)
            {
                err += ++y*2+1;
                if (-x == y && e2 <= x) e2 = 0;
            }
            if (e2 > x) err += ++x*2+1;

        }
        while (x <= 0);
    }
    else
    {
        y = -Radius2;
        x = 0;
        do
        {
            K = (float)(rad2/rad1);
            if(quadrant == 1) {
                LCD_DrawLine((Xpos-(uint16_t)(x/K) +(2*(uint16_t)(x/K) + 1)/2 ), (Ypos+y), (2*(uint16_t)(x/K) + 1)/2, LCD_DIR_HORIZONTAL);

            }
            else if(quadrant == 2) {
                LCD_DrawLine((Xpos-(uint16_t)(x/K)), (Ypos+y), (2*(uint16_t)(x/K) + 1)/2, LCD_DIR_HORIZONTAL);

            }
            else if(quadrant == 3) {
                LCD_DrawLine((Xpos-(uint16_t)(x/K)), (Ypos-y), (2*(uint16_t)(x/K) + 1)/2, LCD_DIR_HORIZONTAL);
            }

            else if(quadrant == 4) {
                LCD_DrawLine((Xpos-(uint16_t)(x/K)+(2*(uint16_t)(x/K) + 1)/2), (Ypos-y), (2*(uint16_t)(x/K) + 1)/2, LCD_DIR_HORIZONTAL);
            }

            e2 = err;
            if (e2 <= x)
            {
                err += ++x*2+1;
                if (-y == x && e2 <= y) e2 = 0;
            }
            if (e2 > y)
                err += ++y*2+1;
        }
        while (y <= 0);
    }

}

void Draw_C1A(void)
{
    //  writeBMP_nTimes((uint16_t const *)&BMP_C1A_main, 320,5,0,0,48);
    // writeBMP_nTimes((uint16_t const *)&BMP_C1A_topX25Y0, 50,190,25,0,1);
    // writeBMP_nTimes((uint16_t const *)&BMP_C1A_left_X0Y42, 237,22,0,42,1);
    //  writeBMP_nTimes((uint16_t const *)&BMP_C1A_right_X218Y42, 237,22,218,42,1);

    //  LCD_SetTextColor(ASSEMBLE_RGB(183,183,183));
    //  LCD_DrawLine(24,108,189,LCD_DIR_HORIZONTAL);
    //  LCD_SetTextColor(ASSEMBLE_RGB(127,127,127));
    //  LCD_DrawLine(24,109,189,LCD_DIR_HORIZONTAL);

    //writeBMP_nTimes((uint16_t const *)&BMP_C_X45Y115, 168,151,45,115,1);
    //  LCD_SetTextColor(Red);
    //  LCD_SetBackColor(Red);

    //lcd320x240_drawcircle(X_CP,Y_CP,R1_CP);
    //lcd320x240_drawcircle(X_CP,Y_CP,R1_CP-1);
    //lcd320x240_drawcircle(X_CP,Y_CP,R1_CP-2);

    /*start test*/
    // LCD_DrawCircle1(X_CP,Y_CP,R1_CP);
    // displayCirlce();

    /*stop test*/



    //LCD_SetTextColor(ASSEMBLE_RGB(100,100,100));
    //LCD_SetBackColor(ASSEMBLE_RGB(100,100,100));


    //DrawFullCircle(X_CP,Y_CP,R1_CP);
    //LCD_SetTextColor(White);
    //LCD_SetBackColor(White);
    //DrawFullCircle(X_CP,Y_CP,R2_CP);

    //LCD_SetTextColor(Red);
    //lcd320x240_drawcircle(X_CP,Y_CP,R3_CP);

    //LCD_DrawCircle1(X_CP,Y_CP,R3_CP);//ok

    //LCD_DrawEllipse_Part(X_CP,Y_CP,R3_CP,R3_CP,1); /*2%*/
    //LCD_DrawEllipse_Part(X_CP,Y_CP,R3_CP,R3_CP,2); /*2%*/
    //LCD_DrawEllipse_Part(X_CP,Y_CP,R3_CP,R3_CP,3); /*2%*/
    //LCD_DrawEllipse_Part(X_CP,Y_CP,R3_CP,R3_CP,4); /*2%*/
    // LCD_DrawEllipse(X_CP,Y_CP,R2_CP,R2_CP);
    // LCD_SetTextColor(White);
    //LCD_SetBackColor(White);

    //LCD_SetTextColor(Black);
    //DrawCompass(10);

    //  result =mux(2,3);
    //result = giai_thua(4);
    //result = sin(3.14159/2);



    //LCD_FillScreen(White);
//         LCD_FillScreen(ASSEMBLE_RGB(0,200,255));

    //  writeIcons_unselect((uint16_t const *)&BMP_navigation, 115,155,20,140);

//    writeBMP_nTimes((uint16_t const *)&BMP_beach320x240, 145,187,0,0,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_beach320x240, 145,187,0,0,1);



//writeBMP_nTimes((uint16_t const *)&BMP_BMP_H_TOP, 21,320,0,0,1);
    //  writeBMP_nTimes((uint16_t const *)&BMP_BMP_H_TOP, 21,320,0,0,1);
    //  writeBMP_nTimes((uint16_t const *)&BMP_Home_bot, 20,320,0,220,1);
    //redrawScreen(0, 21,320, 220,SEPIA_BG);


    //redrawScreen(0, 25,155, 40,SEPIA_GRAY);  /*HOME-color*/
    // writeBMP_nTimes((uint16_t const *)&BMP_back, 11,13,3,27,1);

    // LCD_SetTextColor(0x528A);/*line color*/
    // LCD_DrawLine(0, 43, 320, LCD_DIR_HORIZONTAL);
    //LCD_DrawLine(155, 45, 175, LCD_DIR_VERTICAL);

    // LCD_DrawLine(0, 67 +21*0, 155, LCD_DIR_HORIZONTAL);
    // LCD_DrawLine(0, 67 +21*1, 155, LCD_DIR_HORIZONTAL);
    // LCD_DrawLine(0, 67 +21*2, 155, LCD_DIR_HORIZONTAL);
    // LCD_DrawLine(0, 67 +21*3, 155, LCD_DIR_HORIZONTAL);
    // LCD_DrawLine(0, 67 +21*4, 155, LCD_DIR_HORIZONTAL);
    // LCD_DrawLine(0, 67 +21*5, 155, LCD_DIR_HORIZONTAL);
    // LCD_DrawLine(0, 67 +21*6, 155, LCD_DIR_HORIZONTAL);
    // LCD_DrawLine(0, 67 +21*7, 155, LCD_DIR_HORIZONTAL);
    TextColor = Red;
    BackColor = Red;
    // LCD_DrawLine(20, 60, 160, LCD_DIR_HORIZONTAL);
    //LCD_DrawLine(20, 60, 50, LCD_DIR_VERTICAL);a
    Draw_H5();

    // LCD_DrawFullRect(20, 60, 120, 80);
}

void Headings_text(void)
{

    char time_buf1[6];
    char time_buf2[6];
    char time_buf3[6];


    FontSet = myriad_bold_16;
    LCD_SetTextColor(Black);
    LCD_SetBackColor(White);

    pre_battery();
    //pre_temper(temper_buf,69);
    pre_time(time_buf1,0,23,35);
    pre_time(time_buf2,0,18,25);
    pre_time(time_buf3,0,23,20);

    LCD_SetBackColor(SEPIA_SELECT);
    //LCD_DisplayStringLine(18,20, time_buf1);

    LCD_SetBackColor(White);
    LCD_DisplayStringLine(88,20, time_buf2);

    LCD_DisplayStringLine(157,20, time_buf3);

    //LCD_DisplayStringLine(218,20, temper_buf);

    LCD_DisplayStringLine(258,20, battery_buf);

}
void Draw_H1(void) {
    LCD_Clear(SEPIA_BG);
    DrawShape(Shape_TopBar);
    DrawIcon(Icon_TopBar_Clock,UnSelect);
    DrawIcon(Icon_TopBar_Battery,UnSelect);
    DrawIcon(Icon_TopBar_FlyTime,UnSelect);
    DrawIcon(Icon_TopBar_Temper,UnSelect);
    DrawIcon(Icon_TopBar_DesatTime,UnSelect);
    DrawShape(Shape_BottomBar);
    DrawIcon(Icon_BottomBar_ArrowDown,UnSelect);
    DrawIcon(Icon_BottomBar_ArrowLeft,UnSelect);
    DrawIcon(Icon_BottomBar_ArrowUp,UnSelect);
    DrawIcon(Icon_BottomBar_Select,UnSelect);
    DrawIcon(Icon_HomeMenu_GoDive,UnSelect);
    //writeBMP_nTimes((uint16_t const *)&BMP_Menu_Top, 21,320,0,20,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_Home_bot, 20,320,0,220,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_History, 60,60,15,30,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_Navigation, 60,60,15,90,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_MyInfo, 60,60,15,150,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_OPMode, 60,60,130,30,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_GoDive, 60,60,128,90,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_SepiaInfo, 60,60,130,150,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_Setting, 60,60,245,30,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_Log, 60,60,245,90,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_TMTStatus, 60,60,245,150,1);
    //Headings_text();
    //SEPIA.DrawIcon(Icon_BottomBar_ArrowUp);
}
void Draw_H2(void) {
    redrawScreen(0, 25,320, 220,SEPIA_BG);/*redraw full main*/
    redrawScreen(0, 25,160, 40,0x8410);  /*HOME-color*/
    writeBMP_nTimes((uint16_t const *)&BMP_back, 11,13,3,27,1);
    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(0, 45, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(112, 45, 175, LCD_DIR_VERTICAL);
    LCD_DrawLine(112, 67 +21*0, 208, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(112, 67 +21*1, 208, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(112, 67 +21*2, 208, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(112, 67 +21*3, 208, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(112, 67 +21*4, 208, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(112, 67 +21*5, 208, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(112, 67 +21*6, 208, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(112, 67 +21*7, 208, LCD_DIR_HORIZONTAL);
    writeBMP_nTimes((uint16_t const *)&BMP_H2_HistoryX15Y90, 77,78,15,90,1);
    Text_H2();
}

void Draw_H3(void)
{

    redrawScreen(0, 25,320, 220,SEPIA_BG);/*redraw full main*/
    //redrawScreen(0, 70,320, 133,SEPIA_SELECT);

    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(0, 43, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 196, 320, LCD_DIR_HORIZONTAL);

    redrawScreen(0, 25,160, 40,0x8410);  /*HOME-color*/
    writeBMP_nTimes((uint16_t const *)&BMP_back, 11,13,3,27,1);
}
void Draw_H4(void) {
    redrawScreen(0, 25,320, 220,SEPIA_BG);/*redraw full main*/
    redrawScreen(0, 25,160, 40,0x8410);  /*HOME-color*/
    writeBMP_nTimes((uint16_t const *)&BMP_back, 11,13,3,27,1);
}



void Draw_H74(void)
{

    redrawScreen(0, 22,320, 220,SEPIA_BG);
    redrawScreen(0, 25,160, 40,SEPIA_GRAY);  /*HOME-color*/
    writeBMP_nTimes((uint16_t const *)&BMP_back, 11,13,3,27,1);

    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(0, 43, 320, LCD_DIR_HORIZONTAL);

    FontSet = myriad_bold_14;
    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_GRAY);
    LCD_DisplayStringLine_As_Left(20,160,40, "HOME");
    FontSet = myriad_bold_17;
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_As_Left(180,320,43, "NAVIGATION");
    writeBMP_nTimes((uint16_t const *)&BMP_SetID, 57,57,15,45,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_SetID_Sel, 57,57,15,45,1);

    writeBMP_nTimes((uint16_t const *)&BMP_NavMode, 57,57,15,103,1);
    // writeBMP_nTimes((uint16_t const *)&BMP_NavMode_Sel, 57,57,15,103,1);


    writeBMP_nTimes((uint16_t const *)&BMP_Chanel, 57,57,130,45,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_Chanel_Sel, 57,57,130,45,1);

    writeBMP_nTimes((uint16_t const *)&BMP_Paring, 57,57,130,103,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_Paring_Sel, 57,57,130,103,1);

    writeBMP_nTimes((uint16_t const *)&BMP_SetSMS, 57,57,245,45,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_SetSMS_Sel, 57,57,245,45,1);

    writeBMP_nTimes((uint16_t const *)&BMP_Partner, 57,57,245,103,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_Partner_Sel, 57,57,245,103,1);


    /*
        FontSet = myriad_bold_9;
        LCD_SetTextColor(White);

        LCD_DisplayStringLine_Center(15,75,146, "DATE&TIME");
        LCD_DisplayStringLine_Center(15,75,204, "ALARMS");
        LCD_DisplayStringLine_Center(130,190,88, "SET TMT");
        LCD_DisplayStringLine_Center(130,190,146, "BRIGHTNESS");
        LCD_DisplayStringLine_Center(125,195,204, "SET COMPASS");
        LCD_DisplayStringLine_Center(245,305,88, "BLUETOOTH");
        LCD_DisplayStringLine_Center(245,305,146, "UTILITIES");
        LCD_DisplayStringLine_Center(245,307,204, "CLEAR Ni-O2");
        LCD_SetTextColor(Black);

        LCD_DisplayStringLine_Center(15,75,88, "SET GASES");
    */

}
void Draw_H5(void)
{

    writeBMP_nTimes((uint16_t const *)&BMP_BMP_H_TOP, 21,320,0,0,1);
    writeBMP_nTimes((uint16_t const *)&BMP_Home_bot, 20,320,0,220,1);
    redrawScreen(0, 21,320, 220,SEPIA_BG);


    redrawScreen(0, 25,155, 40,SEPIA_GRAY);  /*HOME-color*/
    writeBMP_nTimes((uint16_t const *)&BMP_back, 11,13,3,27,1);

    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(0, 43, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(155, 45, 175, LCD_DIR_VERTICAL);

    LCD_DrawLine(0, 67 +21*0, 155, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*1, 155, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*2, 155, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*3, 155, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*4, 155, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*5, 155, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*6, 155, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*7, 155, LCD_DIR_HORIZONTAL);




}

void Draw_H6(void) {
    //Draw_H5();
    redrawScreen(156, 45,320 , 200 ,SEPIA_BG);        /*redraw right side for set GAS*/

    redrawScreen(164, 56,256 , 77 ,SEPIA_GRAY);
    redrawScreen(258, 56,315 , 77 ,SEPIA_GRAY);

    redrawScreen(164, 80,256 , 101 ,SEPIA_SELECT);
    redrawScreen(258, 80,315 , 101 ,SEPIA_SELECT);
    redrawScreen(164, 104,256 , 125 ,SEPIA_GRAY);
    redrawScreen(258, 104,315 , 125 ,SEPIA_GRAY);
    Text_H6();
}

void Draw_H94(void)
{
    //LCD_FillScreen(SEPIA_BG);
    redrawScreen(0, 21,320, 220,SEPIA_BG);
    redrawScreen(0, 21,141, 47,SEPIA_SELECT);
    redrawScreen(142, 21,320, 47,SEPIA_GRAY);

    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(180, 47, 173, LCD_DIR_VERTICAL);

    LCD_DrawLine(0, 91, 180, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 136, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 179, 180, LCD_DIR_HORIZONTAL);
}



void Draw_H9(void)
{
    //Draw_H5();
    //Select_unselect_Left(4,1);
    DisplayText_Left(line4, line1, GAS);


    redrawScreen(156, 45,320 , 200 ,SEPIA_BG);        /*redraw right side for set GAS*/

    redrawScreen(164, 56,315 , 77 ,SEPIA_GRAY);
    redrawScreen(164, 80,315 , 101 ,SEPIA_SELECT);

    DisplayText_Right_GAS(FO2_50,1);


}


void Draw_H10(void)
{
    redrawScreen(156, 45,320 , 200 ,SEPIA_BG);        /*redraw right side for set GAS*/
    Text_H10();

}

void Draw_H11(void)
{
    //Draw_H5();
    //Select_unselect_Left(line1,line5);
    redrawScreen(156, 45,320 , 200 ,SEPIA_BG);        /*redraw right side for set GAS*/
    redrawScreen(164, 56,256 , 77 ,SEPIA_SELECT);
    redrawScreen(258, 56,315 , 77 ,SEPIA_SELECT);
    redrawScreen(164, 80,315 , 101 ,SEPIA_GRAY);

    Text_H11();
}

void Draw_H12(void)
{

    redrawScreen(156, 45,320 , 100 ,SEPIA_BG);        /*redraw right side for set Serial*/
    redrawScreen(164, 56,256 , 77 ,SEPIA_GRAY);
    redrawScreen(258, 56,315 , 77 ,SEPIA_GRAY);
    redrawScreen(164, 80,315 , 101 ,SEPIA_SELECT);

    Text_H12();
}


void Draw_H13(void)
{
    redrawScreen(0, 25,320, 220,SEPIA_BG);/*redraw full main*/
    //redrawScreen(0, 70,320, 133,SEPIA_SELECT);
    //redrawScreen(0, 133,320, 196,SEPIA_SELECT);


    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(0, 43, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 196, 320, LCD_DIR_HORIZONTAL);

    redrawScreen(0, 25,160, 40,0x8410);  /*HOME-color*/
    writeBMP_nTimes((uint16_t const *)&BMP_back, 11,13,3,27,1);
}
void Draw_H14(void)
{
    Draw_H5();
}

void Draw_H15(void)
{
    //Draw_H5();
    redrawScreen(156, 45,320 , 200 ,SEPIA_BG);        /*redraw right side for set GAS*/

    redrawScreen(164, 56,315 , 77 ,SEPIA_GRAY);
    redrawScreen(164, 80,315 , 101 ,SEPIA_SELECT);
}

void Draw_H19(void)
{

    redrawScreen(156, 45,320 , 200 ,SEPIA_BG);        /*redraw right side for set GAS*/

    redrawScreen(164, 56,256 , 77 ,SEPIA_SELECT);
    redrawScreen(258, 56,315 , 77 ,SEPIA_SELECT);

    redrawScreen(164, 80,256 , 101 ,SEPIA_GRAY);
    redrawScreen(258, 80,315 , 101 ,SEPIA_GRAY);

    redrawScreen(164, 104,256 , 125 ,SEPIA_GRAY);
    redrawScreen(258, 104,315 , 125 ,SEPIA_GRAY);

}
void Draw_H20(void)
{
    redrawScreen(156, 45,320 , 200 ,SEPIA_BG);        /*redraw right side for set GAS*/
    redrawScreen(164, 56,256 , 77 ,SEPIA_SELECT);
    redrawScreen(258, 56,315 , 77 ,SEPIA_SELECT);

    redrawScreen(164, 80,256 , 101 ,SEPIA_GRAY);
    redrawScreen(258, 80,315 , 101 ,SEPIA_GRAY);

#ifdef _12h
    redrawScreen(164, 104,256 , 125 ,SEPIA_GRAY);
    redrawScreen(258, 104,315 , 125 ,SEPIA_GRAY);
#endif

    // #ifdef _24h
    LCD_SetTextColor(0x528A);
    LCD_DrawRect(164, 104, 125-104,  256-164 );
    LCD_DrawRect(258, 104, 125-104,  315-258 );


    // #endif
}

void Draw_H78(void) {
    redrawScreen(0, 22,320, 220,SEPIA_BG);
    redrawScreen(0, 25,152, 40,SEPIA_GRAY);  /*HOME-color*/
    writeBMP_nTimes((uint16_t const *)&BMP_back, 11,13,3,27,1);
    writeBMP_nTimes((uint16_t const *)&BMP_ABParing, 62,76,36,90,1);
    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(0, 43, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(152, 43, 176, LCD_DIR_VERTICAL);
    FontSet = myriad_bold_14;
    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_GRAY);
    //LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_As_Left(20,160,40, "NAVIGATION");
    FontSet = myriad_bold_17;
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_Center(150,320,43, "PAIRING");
    FontSet = myriad_bold_30;
    LCD_DisplayStringLine_Center(150, 320, 140, "PAIRING");
}

void Draw_H80(void) {
    redrawScreen(0, 22,320, 220,SEPIA_BG);
    redrawScreen(0, 25,152, 40,SEPIA_GRAY);  /*HOME-color*/
    writeBMP_nTimes((uint16_t const *)&BMP_back, 11,13,3,27,1);
    writeBMP_nTimes((uint16_t const *)&BMP_ABParing, 62,76,36,90,1);



    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(0, 43, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(152, 43, 176, LCD_DIR_VERTICAL);


    FontSet = myriad_bold_14;
    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_GRAY);
    LCD_DisplayStringLine_As_Left(20,160,40, "NAVIGATION");
    FontSet = myriad_bold_17;
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_Center(150,320,43, "PAIRING");
    FontSet = myriad_bold_30;
    LCD_SetTextColor(Red) ;
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_Center(150, 320, 120, "PAIRING FAILED");

}

char ID_Sornar[5]="\0";
char Chanel_Buf[2];
char CN_num = 0;
u8 Total_list = 0;

void Draw_H79(void) {
    u8 i = 0;

    redrawScreen(0, 44,320, 220,SEPIA_BG);

    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(0, 43, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(152, 43, 176, LCD_DIR_VERTICAL);
    LCD_DrawLine(76, 43, 175, LCD_DIR_VERTICAL);

    LCD_DrawLine(0, 67 +21*0, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*1, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*2, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*3, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*4, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*5, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*6, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*7, 152, LCD_DIR_HORIZONTAL);
    FontSet = myriad_bold_15;
    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_Center(150,320,80, "PAIRING COMPLETE");


    LCD_DisplayStringLine_As_Left(197,320,156, "ID:");
    LCD_DisplayStringLine_As_Left(191,320,190, "Channel:");
    //memcpy(ID_Sornar, &pSCB->ownID, 3);
    //memcpy(ID_Sornar, pSCB->operID, 3);
    ///memcpy(ID_Sornar, GET_OP_ID(), 3);
    //memcpy(Chanel_Buf, &pSCB->operID, 1);
    //CN_num = pSCB->ownChannelNum;
    //Num2Str(pSCB->ownChannelNum, Chanel_Buf, 1);
    ///Num2Str(GET_OP_CHANNEL()+1, Chanel_Buf, 1);
    // memcpy(ID_Sornar, GET_OP_ID(), 3);
    //Num2Str(GET_OP_CHANNEL()+1, Chanel_Buf, 1);

#ifdef USE_SONAR
    getPartnerIDList();
    Num2Str(GET_OP_CHANNEL()+1, Chanel_Buf, 1);
    memcpy(ID_Sornar, GET_OP_ID(), 3);
#endif

    FontSet = myriad_bold_17;
    //LCD_DisplayStringLine_As_Left(224,320,156, "THINH");
    //LCD_DisplayStringLine_As_Left(263,320,190, "2");
    LCD_DisplayStringLine_As_Left(224,320,156, ID_Sornar);
    LCD_DisplayStringLine_As_Left(263,320,190, Chanel_Buf);


    FontSet = myriad_bold_17;
    LCD_SetTextColor(SEPIA_GREEN) ;
    LCD_DisplayStringLine_Center(150,320,114, "READY TO DIVE");


    FontSet = myriad_bold_15;

    /*
        LCD_SetTextColor(SEPIA_SELECT) ;
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_Center(0,76,65+21*0, "MIC");
        LCD_DisplayStringLine_Center(0,76,65+21*1, "EVA");
        LCD_DisplayStringLine_Center(0,76,65+21*2, "EGI");

        LCD_SetTextColor(White) ;

        LCD_DisplayStringLine_Center(0,76,65+21*3, "SU1");
        LCD_DisplayStringLine_Center(0,76,65+21*4, "SU2");
        LCD_DisplayStringLine_Center(0,76,65+21*5, "JIM");
        LCD_DisplayStringLine_Center(0,76,65+21*6, "VAL");
        LCD_DisplayStringLine_Center(0,76,65+21*7, "TIM");


        LCD_DisplayStringLine_Center(76,155,65+21*0, "TAM");
        LCD_DisplayStringLine_Center(76,155,65+21*1, "NIC");
        LCD_DisplayStringLine_Center(76,155,65+21*2, "ALI");
        LCD_DisplayStringLine_Center(76,155,65+21*3, "FRE");
        LCD_DisplayStringLine_Center(76,155,65+21*4, "SAM");
        LCD_DisplayStringLine_Center(76,155,65+21*5, "BOA");
    */

#ifdef USE_SONAR


    LCD_SetTextColor(SEPIA_SELECT) ;
    LCD_SetBackColor(SEPIA_BG);
    Total_list = TOTAL_PARTNERS();
    if(Total_list<=8) {
        for(i = 0; i<Total_list; i++) {
            LCD_DisplayStringLine_Center(0,76,65+21*i, pList[i].pID);
        }
    }
    else {
        for(i = 0; i<8; i++) {
            LCD_DisplayStringLine_Center(0,76,65+21*i, pList[i].pID);
        }
        for(i = 8; i<Total_list; i++) {
            LCD_DisplayStringLine_Center(76,155,65+21*i, pList[i].pID);
        }

    }

#endif

}


void Draw_H75(void) {

    redrawScreen(0, 22,320, 220,SEPIA_BG);
    redrawScreen(0, 25,152, 40,SEPIA_GRAY);  /*HOME-color*/
    writeBMP_nTimes((uint16_t const *)&BMP_back, 11,13,3,27,1);
    writeBMP_nTimes((uint16_t const *)&BMP_ABParing, 62,76,36,90,1);



    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(0, 43, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(152, 43, 176, LCD_DIR_VERTICAL);


    FontSet = myriad_bold_14;
    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_GRAY);
    LCD_DisplayStringLine_As_Left(20,160,40, "NAVIGATION");
    FontSet = myriad_bold_17;
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_Center(150,320,43, "PAIRING");

    FontSet = myriad_bold_15;
    LCD_DisplayStringLine_Center(160,310,100, "You have to set your ID for pairing.  ");

    writeBMP_nTimes((uint16_t const *)&BMP_Select, 16,23,185,150,1);
    writeBMP_nTimes((uint16_t const *)&BMP_save, 13,29,158,180,1);
    LCD_DisplayStringLine_Center(170,320,165, "to set ID");
    LCD_DisplayStringLine_Center(175,320,195, "to back to Menu");



}


void Draw_H81(void) { //H86,H89

    //redrawScreen(0, 44,320, 220,SEPIA_BG);
    LCD_SetTextColor(0x528A);
    LCD_DrawLine(0, 43, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(152, 43, 176, LCD_DIR_VERTICAL);
    LCD_DrawLine(76, 43, 175, LCD_DIR_VERTICAL);

    LCD_DrawLine(0, 67 +21*0, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*1, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*2, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*3, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*4, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*5, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*6, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*7, 152, LCD_DIR_HORIZONTAL);

    redrawScreen(0, 25,152, 40,SEPIA_GRAY);  /*HOME-color*/
    writeBMP_nTimes((uint16_t const *)&BMP_back, 11,13,3,27,1);
    FontSet = myriad_bold_14;
    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_GRAY);
    LCD_DisplayStringLine_As_Left(20,160,40, "NAVIGATION");
}
void Draw_H86(void) {

    redrawScreen(0, 44,320, 220,SEPIA_BG);
    LCD_SetTextColor(0x528A);
    LCD_DrawLine(0, 43, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(152, 43, 176, LCD_DIR_VERTICAL);
    // LCD_DrawLine(76, 43, 175, LCD_DIR_VERTICAL);

    LCD_DrawLine(0, 67 +21*0, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*1, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*2, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*3, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*4, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*5, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*6, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*7, 152, LCD_DIR_HORIZONTAL);

    redrawScreen(0, 25,152, 40,SEPIA_GRAY);  /*HOME-color*/
    writeBMP_nTimes((uint16_t const *)&BMP_back, 11,13,3,27,1);

}

void Draw_H23(void)
{
    Draw_H5();

    Select_unselect_Left(0,8);
    //Select_unselect_Left(1,8);
    DisplayText_Left(line4, line1, BRIGHTNESS);
}

void Draw_S1(void)
{

    //writeBMP_nTimes((uint16_t const *)&BMP_BMP_H_TOP, 21,320,0,0,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_Home_bot, 20,320,0,220,1);


    redrawScreen(0, 21,320, 220,SEPIA_BG);

    //writeBMP_nTimes((uint16_t const *)&BMP_TL, 188,19,0,27,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_AR, 186,20,300,28,1);
    writeBMP_nTimes((uint16_t const *)&BMP_icons_clock, 47,34,50,37,1);
    writeBMP_nTimes((uint16_t const *)&BMP_icon_wifi, 48,20,255,35,1);
    writeBMP_nTimes((uint16_t const *)&BMP_icon_gas, 49,21,33,163,1);


    //redrawScreen(20, 95,157, 158,SEPIA_GRAY);
    //redrawScreen(158, 95,300, 158,SEPIA_SELECT);


    LCD_SetTextColor(0x528A);/*line color*/
    //LCD_DrawLine(73, 21, 73, LCD_DIR_VERTICAL);
    LCD_DrawLine(237, 21, 70, LCD_DIR_VERTICAL);

    LCD_DrawLine(159, 87, 70, LCD_DIR_VERTICAL);

    LCD_DrawLine(100, 159, 58, LCD_DIR_VERTICAL);
    LCD_DrawLine(210, 159, 58, LCD_DIR_VERTICAL);


    LCD_DrawLine(0, 87, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 158, 320, LCD_DIR_HORIZONTAL);

    DisplayPercentTLBG(Green,52);
    DisplayPercentARBG(Green,0);


    //redrawScreen(20, 34,72, 55,SEPIA_GRAY);
    //redrawScreen(20, 61,72, 82,SEPIA_GRAY);


}


void Draw_D25(void)
{
    /*
        redrawScreen(0, 21,320, 220,SEPIA_BG);
        redrawScreen(65, 0,200, 20,SEPIA_TOP);

        writeBMP_nTimes((uint16_t const *)&BMP_icon_D25, 19,105,82,2,1);
        //writeBMP_nTimes((uint16_t const *)&BMP_AR, 186,20,300,28,1);
        writeBMP_nTimes((uint16_t const *)&BMP_icon_ds, 20,28,260,52,1);
        writeBMP_nTimes((uint16_t const *)&BMP_icon_TMT, 43,23,15,168,1);

        redrawScreen(0, 95,157, 114,SEPIA_Cyan);
        redrawScreen(0, 114,157, 158,SEPIA_SELECT);


        redrawScreen(158, 95,300, 114,SEPIA_GRAY2);
        redrawScreen(158, 114,300, 158,SEPIA_GRAY);


        LCD_SetTextColor(0x528A);
        //LCD_DrawLine(73, 21, 73, LCD_DIR_VERTICAL);
        // LCD_DrawLine(260, 21, 73, LCD_DIR_VERTICAL);

        LCD_DrawLine(100, 159, 55, LCD_DIR_VERTICAL);
        LCD_DrawLine(210, 159, 55, LCD_DIR_VERTICAL);


        LCD_DrawLine(0, 215, 320, LCD_DIR_HORIZONTAL);
        LCD_DrawLine(0, 216, 320, LCD_DIR_HORIZONTAL);

        DisplayPercentARBG(Green,65);
    */

    redrawScreen(0, 21,320, 240,SEPIA_BG);

    writeBMP_nTimes((uint16_t const *)&BMP_icon_gas, 49,21,33,163,1);
    writeBMP_nTimes((uint16_t const *)&BMP_icon_ds, 20,28,260,52,1);

    writeBMP_nTimes((uint16_t const *)&BMP_Mail_Red, 17,21,95,1,1);

    LCD_SetTextColor(0x528A);/*line color*/

    LCD_DrawLine(159, 87, 70, LCD_DIR_VERTICAL);

    LCD_DrawLine(100, 159, 58, LCD_DIR_VERTICAL);
    LCD_DrawLine(210, 159, 58, LCD_DIR_VERTICAL);


    LCD_DrawLine(0, 87, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 158, 320, LCD_DIR_HORIZONTAL);

    DisplayPercentTLBG(Green,52);
    DisplayPercentARBG(Green,0);
    writeBMP_nTimes((uint16_t const *)&BMP_Home_bot, 20,320,0,220,1);
}
void Draw_D9(void)
{
    redrawScreen(0, 21,320, 220,SEPIA_BG);
    redrawScreen(200, 0,320, 20,SEPIA_TOP);

    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(0, 30, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*1, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*2, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*3, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*4, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*5, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*6, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*7, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*8, 320, LCD_DIR_HORIZONTAL);

    LCD_DrawLine(152, 30, 190, LCD_DIR_VERTICAL);

    writeBMP_nTimes((uint16_t const *)&BMP_TL, 188,19,0,27,1);
    writeBMP_nTimes((uint16_t const *)&BMP_AR, 186,20,300,28,1);
    redrawScreen(21, 30+22*1,151, 30+22*2,SEPIA_SELECT);

    DisplayPercentTLBG(Green,52);
    DisplayPercentARBG(Green,65);

}

void Draw_H73(void)
{
    writeBMP_nTimes((uint16_t const *)&BMP_Menu_Top, 21,320,0,0,1);
    writeBMP_nTimes((uint16_t const *)&BMP_Home_bot, 20,320,0,220,1);
    redrawScreen(0, 21,320, 220,SEPIA_BG);
    writeBMP_nTimes((uint16_t const *)&BMP_NIO2, 39,37,140,25,1);

    FontSet = myriad_bold_19;
    LCD_SetTextColor(White);
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_Center(0,320,180, "CALIBRATE COMPASS");
    //FontSet = myriad_bold_15;
    //LCD_DisplayStringLine_Center(0,320,120, "DATA SAVED");


}
void Draw_H741(void)
{

    writeBMP_nTimes((uint16_t const *)&BMP_BMP_H_TOP, 21,320,0,0,1);
    writeBMP_nTimes((uint16_t const *)&BMP_Home_bot, 20,320,0,220,1);
    redrawScreen(0, 21,320, 220,SEPIA_BG);
    writeBMP_nTimes((uint16_t const *)&BMP_H74_icons, 162,280,21,54,1);

    redrawScreen(0, 25,155, 40,SEPIA_GRAY);  /*HOME-color*/
    writeBMP_nTimes((uint16_t const *)&BMP_back, 11,13,3,27,1);

    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(0, 42, 320, LCD_DIR_HORIZONTAL);
}

void Draw_SO8(void)
{
    redrawScreen(0, 0,320, 240,SEPIA_BG);
    writeBMP_nTimes((uint16_t const *)&BMP_Menu_Top, 21,320,0,0,1);
    writeBMP_nTimes((uint16_t const *)&BMP_Home_bot, 20,320,0,220,1);

    redrawScreen(0, 21,320, 220,SEPIA_BG);
    redrawScreen(0, 217,320, 240,SEPIA_TOP);

    //writeBMP_nTimes((uint16_t const *)&BMP_Sonar_Top, 20,320,0,0,1);
    writeBMP_nTimes((uint16_t const *)&BMP_Mail, 15,19,10,221,1);

    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(0, 30, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*1, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*2, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*3, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*4, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*5, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*6, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*7, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*8, 320, LCD_DIR_HORIZONTAL);

    LCD_DrawLine(152, 30, 190, LCD_DIR_VERTICAL);

    //   writeBMP_nTimes((uint16_t const *)&BMP_TL, 188,19,0,27,1);
    //  writeBMP_nTimes((uint16_t const *)&BMP_AR, 186,20,300,28,1);
    DisplayPercentTLBG(Green,52);
    DisplayPercentARBG(Green,65);

    // redrawScreen(21, 30+22*1,151, 30+22*2,SEPIA_SELECT);
    //redrawScreen(21, 30+22*2,151, 30+22*3,SEPIA_SELECT);


}
void Draw_SO18(void)
{
    redrawScreen(0, 21,320, 220,SEPIA_BG);

    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(0, 30, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*1, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*2, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*3, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*4, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*5, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*6, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*7, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*8, 152, LCD_DIR_HORIZONTAL);

    LCD_DrawLine(152, 30, 190, LCD_DIR_VERTICAL);

    DisplayPercentTLBG(Green,52);
    DisplayPercentARBG(Green,65);

}

void Draw_SO7(void)
{
    redrawScreen(0, 21,320, 220,SEPIA_BG);
    // redrawScreen(70, 0,320, 20,SEPIA_TOP);
    //redrawScreen(0, 217,320, 240,SEPIA_TOP);
    // writeBMP_nTimes((uint16_t const *)&BMP_icon_D25, 19,105,82,2,1);
    //  redrawScreen(70, 0,114, 20,SEPIA_TOP);
//   writeBMP_nTimes((uint16_t const *)&BMP_SO13_bot, 23,320,0,217,1);
    // writeBMP_nTimes((uint16_t const *)&BMP_Sonar_Top, 20,320,0,0,1);
    //writeBMP_nTimes((uint16_t const *)&BMP_Mail, 15,19,10,221,1);



    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(0, 30, 320, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*1, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*2, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*3, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*4, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*5, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*6, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*7, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 30+22*8, 152, LCD_DIR_HORIZONTAL);

    LCD_DrawLine(152, 30, 190, LCD_DIR_VERTICAL);

    //   writeBMP_nTimes((uint16_t const *)&BMP_TL, 188,19,0,27,1);
    //  writeBMP_nTimes((uint16_t const *)&BMP_AR, 186,20,300,28,1);
    DisplayPercentTLBG(Green,52);
    DisplayPercentARBG(Green,65);

}

void Draw_SO10(void)
{
    redrawScreen(0, 21,320, 220,SEPIA_BG);
    //redrawScreen(70, 0,320, 20,SEPIA_TOP);
    //writeBMP_nTimes((uint16_t const *)&BMP_icon_D25, 19,105,82,2,1);
    //redrawScreen(70, 0,114, 20,SEPIA_TOP);
    //writeBMP_nTimes((uint16_t const *)&BMP_SO13_bot, 23,320,0,217,1);

    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(0, 24, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 36, 150, LCD_DIR_HORIZONTAL);
    redrawScreen(0, 24,150, 36,SEPIA_GRAY);


    LCD_DrawLine(0, 36+20*1, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 36+20*2, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 36+20*3, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 36+20*4, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 36+20*5, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 36+20*6, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 36+20*7, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 36+20*8, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 36+20*9, 150, LCD_DIR_HORIZONTAL);

    LCD_DrawLine(62, 24, 194, LCD_DIR_VERTICAL);
    LCD_DrawLine(106, 24, 194, LCD_DIR_VERTICAL);
    LCD_DrawLine(150, 24, 194, LCD_DIR_VERTICAL);

    LCD_DrawLine(170, 24, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(170, 36, 150, LCD_DIR_HORIZONTAL);
    redrawScreen(170, 24,320, 36,SEPIA_GRAY);

    LCD_DrawLine(170, 36+20*1, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(170, 36+20*2, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(170, 36+20*3, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(170, 36+20*4, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(170, 36+20*5, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(170, 36+20*6, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(170, 36+20*7, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(170, 36+20*8, 150, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(170, 36+20*9, 150, LCD_DIR_HORIZONTAL);

    LCD_DrawLine(170, 24, 194, LCD_DIR_VERTICAL);
    LCD_DrawLine(170+62, 24, 194, LCD_DIR_VERTICAL);
    LCD_DrawLine(170+106, 24, 194, LCD_DIR_VERTICAL);


    //redrawScreen(0, 36+20*1,62, 36+20*2,SEPIA_SELECT);
    //redrawScreen(0, 36+20*4,62, 36+20*5,White);
    //redrawScreen(0, 36+20*7,62, 36+20*8,White);

    //redrawScreen(170, 37+20*0,170+62, 36+20*1,White);
}

void Draw_SO16(void)
{
    redrawScreen(0, 21,320, 220,SEPIA_BG);
    writeBMP_nTimes((uint16_t const *)&BMP_Up, 18,21,150,41,1);
    writeBMP_nTimes((uint16_t const *)&BMP_Down, 18,21,150,190,1);


    DisplayPercentTLBG(Green,52);
    DisplayPercentARBG(Green,65);

}


//void writeBMP_nTimes(uint16_t const *bmpPtr,int16_t height,  int16_t width, uint16_t X_offset, uint16_t Y_offset, int16_t nTimes )/*OK*/
void redrawScreenSection(uint16_t Xpos1, uint16_t Ypos1,uint16_t Xpos2, uint16_t Ypos2, uint16_t const *bmpPtr,int16_t height,  int16_t width,int16_t X_offset, uint16_t Y_offset)

{
    //int8_t i = 0;
    //uint32_t tmpCtr1;
    int16_t i = 0;
    uint32_t tmpCtr1 = 0;
    //uint32_t tmpword;
    int16_t hight_sect, nTimes  = 0;

    //145,187  height = 320
    hight_sect = Ypos2 - Ypos1;
    //width_sect = Xpos2 - Xpos1;

    nTimes = 1;
    for(i = 0; i<nTimes; i++)
    {
        *LCD_REG = HX8347_R06H;
        *LCD_RAM =0;
        // for(col = 240; col > 240 - height; col --)
        for(col = 0; col < hight_sect; col ++) {
            tmpCtr1 =(u32)(col)*(width);

            // for(row = 0; row < width; row ++)
            for(row = 320; row > 320 - width; row --) {
                if(nTimes <=1 &&row >(320-Xpos2 -X_offset)&& row<(320-Xpos1-X_offset)) {
                    *LCD_REG = HX8347_R03H;
                    *LCD_RAM = (col + Y_offset) & 0xff;
                    *LCD_REG = HX8347_R02H;
                    *LCD_RAM = ((col + Y_offset) & 0xff00)>>8;

                    *LCD_REG = HX8347_R06H;
                    *LCD_RAM = ((row+ i*width - X_offset) & 0xff00) >>8;

                    *LCD_REG = HX8347_R07H;
                    *LCD_RAM = (row + i*width -X_offset) & 0xff;

                    *LCD_REG = HX8347_R22H;
                    *LCD_RAM = *(bmpPtr + tmpCtr1 + 320-row);
                }
            }
        }
    }
}


void redrawScreen(uint16_t Xpos1, uint16_t Ypos1,uint16_t Xpos2, uint16_t Ypos2,uint16_t Color)
{
    uint16_t Width,  Height;
    uint16_t Xpos,  Ypos;
    Xpos =         Xpos1;
    Ypos =         Ypos1;
    Width =         Xpos2 - Xpos1+1;
    Height =         Ypos2 - Ypos1;

    LCD_SetBackColor(Color);
    LCD_SetTextColor(Color);
    LCD_DrawFullRect(Xpos, Ypos, Width, Height);
}


/**************************************************************************/
// Author: PhuThinh
// Date: 4/1/2014
// Desc: convert a uint8_t number to string
// INPUTs:
//                  * @param  num: value which want convert
//                  * @param  str: buffer to store string
//                  * @maxlen  : max length of string.
// OUTPUTs:
//                @retval lengh of string
//
/**************************************************************************/

uint8_t Num2Str(uint16_t num, char * str, uint8_t maxlen)
{
    uint8_t len =0;
    uint8_t len_temp = 0;
    uint8_t string[10];
    int i =0;
    for ( i = 0; i< maxlen; i++) {
        string[i]  = (uint16_t)(num %10) + 0x30 ;
        num = (uint16_t)(num /10);
    }

    for( i =maxlen -1; i > 0; i--) {
        if(string[i] =='0')
            continue;
        else
            break;
    }

    len = i + 1;

    for(len_temp = len ; len_temp > 0 ; len_temp--)
    {
        *str = string[len_temp-1];
        str ++;
    }

    return len;

}

uint8_t Hex2Str(uint16_t num, uint8_t * str, uint8_t maxlen)
{
    uint8_t len =0;
    uint8_t len_temp = 0;
    uint8_t string[10];
    u8 char_tmp = 0;
    int i =0;
    for ( i = 0; i< maxlen; i++) {
        char_tmp = (uint16_t)(num %16);
        if(char_tmp ==10) {
            string[i] ='A';
        }
        else if(char_tmp ==11) {
            string[i] ='B';
        }
        else if(char_tmp ==12) {
            string[i] ='C';
        }
        else if(char_tmp ==13) {
            string[i] ='D';
        }
        else if(char_tmp ==14) {
            string[i] ='E';
        }
        else if(char_tmp ==15) {
            string[i] ='F';
        }

        else {
            string[i]  = (uint16_t)(num %16) + 0x30 ;
        }
        num = (uint16_t)(num /16);
    }

    for( i =maxlen -1; i > 0; i--) {
        if(string[i] =='0')
            continue;
        else
            break;
    }

    len = i + 1;

    for(len_temp = len ; len_temp > 0 ; len_temp--)
    {
        *str = string[len_temp-1];
        str ++;
    }

    return len;

}

//*****************************************************************************
// void Ascii_Float2Str(u8 *str, u16 *len, float fvalue, u16 precision)
// Parameter:
//
// Note:         Copy float to string
// By:                Nguyen Phu Thinh , 02/07/2010
//*****************************************************************************
void Ascii_Float2Str(char *str, u16 *len, float fvalue, u16 precision)
{
    u32 tmp, i, count = 0, n;
    u8 buffer[15], *p = buffer;
    tmp = 10;
    (*len) =0;
    for(i = 0; i < precision; i++)
        tmp *=  10;

    /* negative value */
    if(fvalue  < 0 ) {
        *str = '-';
        str ++;
        (*len) ++;
        fvalue = -fvalue;
    }
    else
    {
        //*str = '+';
        //str ++;
        //(*len) ++;
    }
    fvalue += 5.0f / tmp;
    tmp = (u32)fvalue;
    do
    {
        *p++ = tmp % 10 + '0';
        count++;
        tmp /= 10;
    }
    while(tmp);

    p--;
    for(i = 0; i < count; i++)
    {
        *str++ = *p--;
    }
    n = count;
    if(precision)
    {
        *str++ = '.';
        n++;

        tmp = (u32)fvalue;
        for(i = 0; i < precision; i++)
        {
            fvalue -= tmp;
            fvalue *= 10;
            tmp = (u32)fvalue;
            *str++ = tmp + '0';
            n++;
        }
    }
    (*len)  += n;

}

u8 decode_step = 0xff;
u8 OP_current = 0xAA;
u8 Fw_version = 0x01;
u8 Plan_Data[17][8];
u8 Log_Data[24][32];

u8 Plan_data_flat = 0;
u8 icons_index_sel = 0;
u8 icons_index_unsel = 0;

u8 pre_icon = 0x10;

#if 1
void decode(void)
{
    switch(in_buf[OPCODE_BYTE])
    {

    case WAIT_FOR_BEEP:
        LCD_Clear(White);
        BackColor = White;
        FontSet = myriad_bold_22;
        LCD_SetTextColor(Black);
        LCD_DisplayStringLine_Center(100, 220, 80, "WAIT FOR BEEP, THEN ACTIVATE");
        break;

    case BLACK_SCEEN:
        LCD_Clear(Black);
        break;


    case OC_SAVE:
    case OC_CLEAR:
        if(screenCod !=H73) {
            screenCod =H73;
            Draw_H73();
            if(in_buf[OPCODE_BYTE] ==OC_SAVE) {
                FontSet = myriad_bold_15;
                LCD_DisplayStringLine_Center(0,320,120, "DATA SAVED");
            }
            else {
                FontSet = myriad_bold_15;
                LCD_DisplayStringLine_Center(0,320,120, "DATA CLEARED");
            }
        }

        break;

    case SEND_FW_VER:
        /*fw version here*/
        //out_buf[0] = 0x5A;
        //out_buf[1] = Fw_version;
        //out_buf[2] = 0x5B;    //need calculate again if change fw
        //out_buf[3] = 0x00;

        sendACK_Data(&Fw_version, 1);
        break;

    case WELCOME:
        LCD_Clear(White);
        FontSet = myriad_bold_22;
        LCD_SetTextColor(Black);
        LCD_DisplayStringLine_Center(90, 230, 107, "WELCOME SEPIA");
        screenCod = Hz;
        break;


    case COMPASS_CALIB:
        //screenCod = H12B;
        screenCod = Hz;
        if((decode_step!=in_buf[MENSTAT_BYTE])||decode_step == 0x17) {
            decode_step =in_buf[MENSTAT_BYTE];
            compass_text(in_buf[MENSTAT_BYTE]);
        }
        break;

    case OC_HomeSetupMenu:
        if(screenCod !=H4) {
            screenCod =H4;
            Draw_H4();
        }

        break;


    case OC_HomeMenu:
        switch(in_buf[MENSTAT_BYTE]) {
        case HMS_HistorySelect:

        case 0x20:
        case 0x30:
        case 0x40:
        case 0x50:
        case 0x60:
        case 0x70:
        case 0x80:
        case 0x90:
            //UpdateHeader();
            if(screenCod !=H1) {
                screenCod = H1;
                Draw_H1();
                _prehh = 0xff;
                _preTEMP = 0;
                previous_sel = in_buf[MENSTAT_BYTE];
                current_sel = in_buf[MENSTAT_BYTE];
                DrawIcon(Icon_HomeMenu_GoDive, Select);
                //Select_HomeMenu(current_sel);
            }
            else if(current_sel!=in_buf[MENSTAT_BYTE]) { /*update icons*/
                previous_sel = current_sel;
                current_sel = in_buf[MENSTAT_BYTE];
                //UnSelect_HomeMenu(previous_sel);
                //Select_HomeMenu(current_sel);
                //DrawIcon(Icon_HomeMenu_GoDive, Select);
                //DrawIcon(previous_sel, HMS_GoDiveSelect);
            }
            break;

        case 0x81:
            if( screenCod != H101) {
                screenCod = H101;
                redrawScreen(0, 21,320, 220,SEPIA_BG);
                Text_H101();
            }
            break;
        case HMS_HistoryEnter:
            //LCD_DrawBMP(0, 0, (ptImage)&HistoryIconLarge, 0);
            break;
        }

        break;


    case OC_NavigationMenu://H74
        switch(in_buf[MENSTAT_BYTE]) {
        case 0x10:
        case 0x20:
        case 0x30:
        case 0x40:
        case 0x50:
        case 0x60:
            if(screenCod !=H74) {
                screenCod = H74;
                Draw_H74();
                previous_sel = in_buf[MENSTAT_BYTE];
                current_sel = in_buf[MENSTAT_BYTE];
                Select_NavMenu(current_sel);
            }
            else if(current_sel!=in_buf[MENSTAT_BYTE]) { /*update icons*/
                previous_sel = current_sel;
                current_sel = in_buf[MENSTAT_BYTE];

                UnSelect_NavMenu(previous_sel);
                Select_NavMenu(current_sel);

            }
            break;

        case 0x51:
            if(screenCod !=H78) {
                screenCod =H78;
                Draw_H78();
            }

            break;

        case 0x52:
            if(screenCod !=H79) {
                screenCod =H79;
                Draw_H79();
            }
            break;

        case 0x53:
            if(screenCod !=H80) {
                screenCod =H80;
                Draw_H80();
            }
            break;
        }
        break;

    case OC_SurfaceMode:
        UpdateHeader();
        if(screenCod !=S1) {
            screenCod =S1;
            Draw_S1();
            Text_S1();
        }
        break;


    case OC_DiveMode:
        UpdateHeader();
        if(screenCod !=D1) {
            screenCod =D1;
            Draw_D25();
            Text_D25();
        }
        break;

    case OC_DiveMenu:
        UpdateHeader();
        switch(in_buf[MENSTAT_BYTE]) {
        case 0x10:
        case 0x20:
        case 0x30:
        case 0x40:
        case 0x50:
        case 0x60:
            if(screenCod !=SO7) {
                screenCod =SO7;
                Draw_SO7();
                Text_DiveMenu();
                previous_sel = in_buf[MENSTAT_BYTE];
                current_sel = in_buf[MENSTAT_BYTE];
                Select_DiveMenu(current_sel);
            }
            else if(current_sel!=in_buf[MENSTAT_BYTE]) {
                previous_sel = current_sel;
                current_sel = in_buf[MENSTAT_BYTE];
                UnSelect_DiveMenu(previous_sel);
                Select_DiveMenu(current_sel);
            }
            break;

        case 0x61:
            if(screenCod !=D36) {
                screenCod =D36;
                //Draw_SO7();
                //Text_DiveMenu();
                Re_Sync(0);
            }
            break;

        case 0x62:
            if(screenCod != D37) { // David Le fixed it.
                screenCod = D37;
                Re_Sync(1);
            }
            break;

        case 0x63:
            if(screenCod != D38) { // David Le fixed it.
                screenCod = D38;
                Re_Sync(2);
            }
            break;

        }
        break;

    case OC_SonarMode:
        UpdateHeader();
        if(screenCod !=SO1) {
            screenCod =SO1;
            Draw_SonarMain();
        }
        break;

    case OC_SonarMenu:
        UpdateHeader();
        switch(in_buf[MENSTAT_BYTE]) {
        case 0x10:
        case 0x20:
        case 0x30:
        case 0x40:
        case 0x50:

            if(screenCod !=SO7) {
                screenCod =SO7;
                Draw_SO7();
                Text_SO7();
                previous_sel = in_buf[MENSTAT_BYTE];
                current_sel = in_buf[MENSTAT_BYTE];
                Select_SonarMenu(current_sel);
            }
            else if(current_sel!=in_buf[MENSTAT_BYTE]) {
                previous_sel = current_sel;
                current_sel = in_buf[MENSTAT_BYTE];
                UnSelect_SonarMenu(previous_sel);
                Select_SonarMenu(current_sel);
            }
            break;

        case 0x41:

            if(screenCod !=SO16) {
                screenCod =SO16;
                Draw_SO16();
                Text_SO16();
            }
            break;
        }
        break;


    case NAV_MODE_MENU: //here SO18,19,20,21
        UpdateHeader();
        if(screenCod !=SO18) {
            screenCod =SO18;
            Draw_SO18();
            Text_SO18();
            previous_sel = in_buf[MENSTAT_BYTE];
            current_sel = in_buf[MENSTAT_BYTE];
            Select_SonarNavMode(current_sel);
        }
        else if(current_sel!=in_buf[MENSTAT_BYTE]) {
            previous_sel = current_sel;
            current_sel = in_buf[MENSTAT_BYTE];
            UnSelect_SonarNavMode(previous_sel);
            Select_SonarNavMode(current_sel);
        }

        break;

#if 0 // Notes: This is duplicated with the case above. PThinh or DThinh, please fix this error.
    case NAV_MODE_SET_MENU: //here H86,H87,H88,H89
        UpdateHeader();
        if(screenCod !=H86) {
            screenCod =H86;
            Draw_H86();
            Text_H86();
            previous_sel = in_buf[MENSTAT_BYTE];
            current_sel = in_buf[MENSTAT_BYTE];
            Select_SetNavMode(current_sel);
        }
        else if(current_sel!=in_buf[MENSTAT_BYTE]) {
            previous_sel = current_sel;
            current_sel = in_buf[MENSTAT_BYTE];
            UnSelect_SetNavMode(previous_sel);
            Select_SetNavMode(current_sel);
        }

        break;
#endif


    case SEND_SMS:
        UpdateHeader();
        if(screenCod !=SO8) {
            screenCod =SO8;
            Draw_SO8();
            Text_SO8();
            previous_sel = in_buf[MENSTAT_BYTE];
            current_sel = in_buf[MENSTAT_BYTE];
            Select_SMS(current_sel);

        }
        else if(current_sel!=in_buf[MENSTAT_BYTE]) {
            previous_sel = current_sel;
            current_sel = in_buf[MENSTAT_BYTE];
            UnSelect_SMS(previous_sel);
            Select_SMS(current_sel);
        }

        break;

    case PARTNER_MENU:
        if(screenCod !=SO10) {
            screenCod =SO10;
            Draw_SO10();
            Text_SO10();
        }
        break;


    case SELECT_PARTNER:
        if(screenCod !=H81) {
            screenCod =H81;
            Draw_H81();
            Text_H81();
        }
        break;



    default:
        //LCD_FillScreen(White);
        //FontSet = myriad_bold_22;
        //LCD_SetTextColor(BLACK);
        //LCD_DisplayStringLine_Center(88, 200, 107, "NOT YET DECODE");

        //screenCod = Hz;

        break;



    }

}
#else

void decode(void)
{
    switch(screenCod)
    {
    case SO8:
        if(screenCod != PrescreenCod) {
            screenCodnext = SO9;
            PrescreenCod = screenCod;
            //Draw_H1();
            //icons_index_sel = 1;
            Draw_SO8();
            Text_SO8();
            UpdateHeader();
            //Headings_text();
        }
        break;

    case SO9:
        if(screenCod != PrescreenCod) {
            screenCodnext = SO13;
            PrescreenCod = screenCod;
            //Draw_H74();
            Draw_SO7();
            Text_SO7();
        }
        break;

    case SO13:
        if(screenCod != PrescreenCod) {
            screenCodnext = Hz;
            PrescreenCod = screenCod;
            //Draw_H78();
            Draw_D25();
            Text_D25();
        }
        break;
    case Pairing2:
        if(screenCod != PrescreenCod) {
            screenCodnext = Pairing3;
            PrescreenCod = screenCod;
            Draw_H79();
        }
        break;

    case Pairing3:
        if(screenCod != PrescreenCod) {
            screenCodnext = D9;
            PrescreenCod = screenCod;
            Draw_H75();
        }
        break;

    case D9:
        Draw_D9();
        Text_D9();
        screenCodnext = H5;
        break;


    case H5:
        if(screenCod != PrescreenCod) {
            screenCodnext = H94;
            PrescreenCod = screenCod;
            Draw_H5();
            Text_H5();
            icons_index_sel = 0;
            icons_index_unsel = 0;

        }
        else {
            icons_index_unsel = icons_index_sel;
            icons_index_sel++;
            DisplayText_Left(icons_index_sel, icons_index_unsel, GAS);

            if(icons_index_sel >=4) {
                screenCodnext = H6;
            }
        }
        break;


    case H94:

        Draw_H94();
        Text_H94();
        screenCodnext = S1;
        break;

    case S1:

        Draw_S1();
        Text_S1();
        screenCodnext = D25;
        break;

    case D25:

        Draw_D25();
        Text_D25();
        screenCodnext = H74;
        break;


    case H74:
        Draw_H74();
        Text_H74();
        screenCodnext = SO13;
        break;

    case SO13:
        Draw_SO7();
        Text_SO7();
        screenCodnext = SO12;
        break;

    case SO12:
        Draw_SO8();
        Text_SO8();
        screenCodnext = SO13_2;
        break;

    case SO13_2:
        Draw_SO13_2();
        Text_SO13_2();
        screenCodnext = Hz;
        break;

    }

}


#endif
uint8_t Bcd2ToByte(uint8_t Value)
{
    uint8_t tmp = 0;
    tmp = ((uint8_t)(Value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
    return (tmp + (Value & (uint8_t)0x0F));
}

uint8_t ByteToBcd2(uint8_t Value)
{
    uint8_t bcdhigh = 0;

    while (Value >= 10)
    {
        bcdhigh++;
        Value -= 10;
    }

    return  ((uint8_t)(bcdhigh << 4) | Value);
}


void lcd320x240_drawcircle(uint16_t Xpos, uint16_t Ypos,uint16_t d)  /*OK*/
{
    int u8d;
    int s16tswitch=0, y=0, x=0;

    u8d = Ypos - Xpos;
    y = d;
    s16tswitch = 3 - 2 * d;
    while (x <= y)
    {
        PutPixel(Xpos + x, Ypos + y);
        PutPixel(Xpos + x, Ypos - y);

        PutPixel(Xpos - x, Ypos + y);
        PutPixel(Xpos - x, Ypos - y);

        PutPixel(Ypos + y - u8d, Ypos + x);
        PutPixel(Ypos + y - u8d, Ypos - x);
        PutPixel(Ypos - y - u8d, Ypos + x);
        PutPixel(Ypos - y - u8d, Ypos - x);

        if (s16tswitch < 0)
            s16tswitch += (4 * x + 6);
        else
        {
            s16tswitch += (4 * (x - y) + 10);
            y--;
        }

        x++;
    }
}


float X_max, X_min, Y_max, Y_min;

float result = 0;
float X_t;
float Y_t;
void lcd320x240_drawcircle1(uint16_t Xpos, uint16_t Ypos,uint16_t d)  // Draw a circle center column1 and rowA diametre d
{
    int u8d;
    int s16tswitch=0, y=0, x=0;
    float  Rad =0;
    u8 flat1, flat2, flat3, flat4, flat5, flat6, flat7, flat8;



    Rad = Deg*PI/180;
    Y_t = d*cos(Rad);
    X_t = d*sin(Rad);
    //Y_t = d*cos(Rad);
    //X_t = d*sin(Rad);
    if(X_t <0)
        X_t = X_t*(-1);
    if(Y_t <0)
        Y_t = Y_t*(-1);

    // result = sin(degree);
    if(Deg<=90) {
        X_max = Xpos+X_t;
        X_min = Xpos ;
        Y_max = Ypos+Y_t;
        Y_min = Ypos -d;

        flat1 = 0;/*ok*/
        flat2 = 1;/*ok*/
        flat3 = 0;
        flat4 = 0;
        flat5 = 0;
        flat6 = 1;
        flat7 = 1;
        flat8 = 1;
    }
    else if(Deg<=180&& Deg >90) {
        X_max = Xpos+d;
        X_min = Xpos ;
        Y_max = Ypos+Y_t;
        Y_min = Ypos -d;
        flat1 = 1;
        flat2 = 1;
        flat3 = 1;
        flat4 = 1;
        flat5 = 1;
        flat6 = 1;
        flat7 = 1;
        flat8 = 1;
    }
    else if(Deg<=270&& Deg >180) {
        X_max = Xpos+d;
        X_min = Xpos -X_t;
        Y_max = Ypos+d;
        Y_min = Ypos -d;

        flat1 = 1;
        flat2 = 1;
        flat3 = 1;
        flat4 = 0;
        flat5 = 1;
        flat6 = 1;
        flat7 = 1;
        flat8 = 0;
    }
    else if(Deg<=315&& Deg >270) {
        X_max = Xpos+d;
        X_min = Xpos -d;
        Y_max = Ypos+d;
        Y_min = Ypos -d;

        flat1 = 0;
        flat2 = 0;
        flat3 = 0;
        flat4 = 0;/*315 to 360*/
        flat5 = 0;
        flat6 = 0;
        flat7 = 0;
        flat8 = 1;/*270 to 315*/
    }





    u8d = Ypos - Xpos;
    y = d;
    s16tswitch = 3 - 2 * d;
    while (x <= y)
    {
        if((Xpos + x <=X_max)&&(Xpos + x>= X_min)&&(Ypos + y<= Y_max)&&(Ypos + y>= Y_min)&&flat1) {

            PutPixel(Xpos + x, Ypos + y);
        }
        if((Xpos + x <=X_max)&&(Xpos + x>= X_min)&&(Ypos - y<= Y_max)&&(Ypos - y>= Y_min)&&flat2) {
            PutPixel(Xpos + x, Ypos - y);
        }

        if((Xpos - x <=X_max)&&(Xpos - x>= X_min)&&(Ypos + y<= Y_max)&&(Ypos + y>= Y_min)&&flat3) {
            PutPixel(Xpos - x, Ypos + y);
        }

        if((Xpos - x <=X_max)&&(Xpos - x>= X_min)&&(Ypos - y<= Y_max)&&(Ypos - y>= Y_min)&&flat4) {
            PutPixel(Xpos - x, Ypos - y);
        }

        if((Ypos + y - u8d <=X_max)&&(Ypos + y - u8d>= X_min)&&(Ypos + x<= Y_max)&&(Ypos + x>= Y_min)&&flat5) {

            PutPixel(Ypos + y - u8d, Ypos + x);
        }

        if((Ypos + y - u8d <=X_max)&&(Ypos + y - u8d>= X_min)&&(Ypos - x<= Y_max)&&(Ypos - x>= Y_min)&&flat6) {
            PutPixel(Ypos + y - u8d, Ypos - x);
        }

        if((Ypos - y - u8d <=X_max)&&(Ypos - y - u8d>= X_min)&&(Ypos + x<= Y_max)&&(Ypos + x>= Y_min)&&flat7) {
            PutPixel(Ypos - y - u8d, Ypos + x);
        }

        if((Ypos - y - u8d <=X_max)&&(Ypos - y - u8d>= X_min)&&(Ypos - x<= Y_max)&&(Ypos - x>= Y_min)&&flat8) {
            PutPixel(Ypos - y - u8d, Ypos - x);
        }


        if (s16tswitch < 0)
            s16tswitch += (4 * x + 6);
        else
        {
            s16tswitch += (4 * (x - y) + 10);
            y--;
        }

        x++;
    }
}
#if 0
#define SIZE                70
uint16_t X1[SIZE], Y1[SIZE];
uint16_t X2[SIZE], Y2[SIZE];
uint16_t X3[SIZE], Y3[SIZE];
uint16_t X4[SIZE], Y4[SIZE];
uint16_t X5[SIZE], Y5[SIZE];
uint16_t X6[SIZE], Y6[SIZE];
uint16_t X7[SIZE], Y7[SIZE];
uint16_t X8[SIZE], Y8[SIZE];





void LCD_DrawCircle1(uint16_t  x0,uint16_t  y0,uint16_t  radius)
{
    int  f = 1 - radius;
    int  ddF_x = 0;
    int  ddF_y = -2 * radius;
    int  x = 0;
    int  y = radius;
    Point_circle = 0;

    PutPixel(x0, y0 + radius);
    PutPixel(x0, y0 - radius);
    PutPixel(x0 + radius, y0);
    PutPixel(x0 - radius, y0);
    while(x < y)
    {
        if(f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x + 1;

        //PutPixel(x0 + x, y0 + y);
        //PutPixel(x0 - x, y0 + y);
        //PutPixel(x0 + x, y0 - y);
        //PutPixel(x0 - x, y0 - y);
        //PutPixel(x0 + y, y0 + x);
        //PutPixel(x0 - y, y0 + x);
        //PutPixel(x0 + y, y0 - x);
        //PutPixel(x0 - y, y0 - x);
        X1[Point_circle] = x0 + x;
        Y1[Point_circle] =  y0 + y;

        X2[Point_circle] = x0 - x;
        Y2[Point_circle] =  y0 + y;

        X3[Point_circle] = x0 + x;
        Y3[Point_circle] =  y0 - y;

        X4[Point_circle] = x0 - x;
        Y4[Point_circle] =  y0 - y;

        X5[Point_circle] = x0 + y;
        Y5[Point_circle] =  y0 + x;

        X6[Point_circle] = x0 - y;
        Y6[Point_circle] =  y0 + x;

        X7[Point_circle] = x0 + y;
        Y7[Point_circle] =  y0 - x;

        X8[Point_circle] = x0 - y;
        Y8[Point_circle] =  y0 - x;
        Point_circle++;
    }
}

void displayCirlce(void)
{
    uint16_t i = 0;
    for(i =0; i<Point_circle; i++) {
        //PutPixel(X1[i],Y1[i]);                 /*part4, swap*/
        //PutPixel(X2[i],Y2[i]);                /*part5, ok*/
        //PutPixel(X3[i],Y3[i]);                /*part1, ok*/
        //PutPixel(X4[i],Y4[i]);                /*part8, swap*/
        //PutPixel(X5[i],Y5[i]);                /*part3, ok*/
        //PutPixel(X6[i],Y6[i]);                /*part6, swap*/
        //PutPixel(X7[i],Y7[i]);                /*part2, swap*/
        //PutPixel(X8[i],Y8[i]);                /*part7, ok*/


        X_Sum[i] = X3[i];
        Y_Sum[i] = Y3[i];
    }
    for(i =0 ; i<Point_circle; i++) {
        X_Sum[Point_circle+i] = X7[Point_circle -i];                // 2
        Y_Sum[Point_circle+i] = Y7[Point_circle -i];
    }

    for(i =0 ; i<Point_circle; i++) {
        X_Sum[Point_circle*2+i] = X5[i];                                        // 3
        Y_Sum[Point_circle*2+i] = Y5[i];
    }

    for(i =0 ; i<Point_circle; i++) {
        X_Sum[Point_circle*3+i] = X1[Point_circle -i];                // 4
        Y_Sum[Point_circle*3+i] = Y1[Point_circle -i];
    }

    for(i =0 ; i<Point_circle; i++) {
        X_Sum[Point_circle*4+i] = X2[i];                                        // 5
        Y_Sum[Point_circle*4+i] = Y2[i];
    }

    for(i =0 ; i<Point_circle; i++) {
        X_Sum[Point_circle*5+i] = X6[Point_circle -i];                // 6
        Y_Sum[Point_circle*5+i] = Y6[Point_circle -i];
    }

    for(i =0 ; i<Point_circle; i++) {
        X_Sum[Point_circle*6+i] = X8[i];                                        // 7
        Y_Sum[Point_circle*6+i] = Y8[i];
    }

    for(i =0 ; i<Point_circle; i++) {
        X_Sum[Point_circle*7+i] = X4[Point_circle -i];                // 8
        Y_Sum[Point_circle*7+i] = Y4[Point_circle -i];
    }


    //for( i =0; i<Point_circle*8; i++){
    //        PutPixel(X_Sum[i],Y_Sum[i]);
    //}

}
#endif
/**************************************************************************/
// Author: PhuThinh
// Date: 2/27/2014
// Desc: Draw ellipse
// INPUTs:
//                  * @param  Xpos: specifies the X position, can be a value from 0 to 240.
//                  * @param  Ypos: specifies the Y position, can be a value from 0 to 320.
//                  * @param  Radius: specifies Radius.
//                  * @param  Radius2: specifies Radius2.
// OUTPUTs:
//                @retval None
//
/**************************************************************************/



void LCD_DrawEllipse(uint16_t  Xpos, uint16_t Ypos, uint16_t Radius1, uint16_t Radius2)
{
    int dx = 0, dy = Radius2; /* im I. Quadranten von links oben nach rechts unten */
    long a2 = Radius1*Radius1, b2 = Radius2*Radius2;
    long err = b2-(2*Radius2-1)*a2, e2; /* Fehler im 1. Schritt */

    do
    {
        PutPixel(Xpos+dx, Ypos+dy); /* I. Quadrant */
        PutPixel(Xpos-dx, Ypos+dy); /* II. Quadrant */
        PutPixel(Xpos-dx, Ypos-dy); /* III. Quadrant */
        PutPixel(Xpos+dx, Ypos-dy); /* IV. Quadrant */

        e2 = 2*err;
        if (e2 < (2*dx+1)*b2) {
            dx++;
            err += (2*dx+1)*b2;
        }
        if (e2 > -(2*dy-1)*a2) {
            dy--;
            err -= (2*dy-1)*a2;
        }
    }
    while (dy >= 0);

    while (dx++ < Radius1)
    {   /* fehlerhafter Abbruch bei flachen Ellipsen (b=1) */
        PutPixel(Xpos+dx, Ypos); /* -> Spitze der Ellipse vollenden */
        PutPixel(Xpos-dx, Ypos);
    }

}

/**************************************************************************/
// Author: PhuThinh
// Date: 2/27/2014
// Desc: Draw a full ellipse.
// INPUTs:
//                  * @param  Xpos: specifies the X position, can be a value from 0 to 240.
//                  * @param  Ypos: specifies the Y position, can be a value from 0 to 320.
//                  * @param  Radius: specifies Radius.
//                  * @param  Radius2: specifies Radius2.
// OUTPUTs:
//                @retval None
//
/**************************************************************************/
void LCD_DrawFullEllipse(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, uint16_t Radius2)
{
    int x = -Radius, y = 0, err = 2-2*Radius, e2;
    float K = 0, rad1 = 0, rad2 = 0;

    rad1 = Radius;
    rad2 = Radius2;

    if (Radius > Radius2)
    {
        do
        {
            K = (float)(rad1/rad2);
            LCD_DrawLine((Xpos+x), (Ypos-(uint16_t)(y/K)), (2*(uint16_t)(y/K) + 1), LCD_DIR_VERTICAL);
            LCD_DrawLine((Xpos-x), (Ypos-(uint16_t)(y/K)), (2*(uint16_t)(y/K) + 1), LCD_DIR_VERTICAL);

            e2 = err;
            if (e2 <= y)
            {
                err += ++y*2+1;
                if (-x == y && e2 <= x) e2 = 0;
            }
            if (e2 > x) err += ++x*2+1;

        }
        while (x <= 0);
    }
    else
    {
        y = -Radius2;
        x = 0;
        do
        {
            K = (float)(rad2/rad1);
            LCD_DrawLine((Xpos-(uint16_t)(x/K)), (Ypos+y), (2*(uint16_t)(x/K) + 1), LCD_DIR_HORIZONTAL);
            LCD_DrawLine((Xpos-(uint16_t)(x/K)), (Ypos-y), (2*(uint16_t)(x/K) + 1), LCD_DIR_HORIZONTAL);

            e2 = err;
            if (e2 <= x)
            {
                err += ++x*2+1;
                if (-y == x && e2 <= y) e2 = 0;
            }
            if (e2 > y)
                err += ++y*2+1;
        }
        while (y <= 0);
    }

}




void DrawCompass(u16 percent)
{
    /*1 line = 5 degree*/
    /*divide compass into 3 part(cirlce), c3 is draw 1 time.   c1,c2 need that 360/5 = 72  X,Y - depend degree we will draw line depend on c1,c2*/
    /*step1: take 72  X1/Y1 , X2/Y2 - draw at 0 degree*/
    /*step2: draw 0 to 360 - and need redraw too*/

}


void DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
    /*
        int x = -Radius, y = 0, err = 2-2*Radius, e2;
        float K = 0, rad1 = 0, rad2 = 0;

        rad1 = Radius;
        rad2 = Radius;

        y = -Radius;
        x = 0;
        do
        {
            K = (float)(rad2/rad1);
            LCD_DrawLine((Xpos-(uint16_t)(x/K)), (Ypos+y), (2*(uint16_t)(x/K) + 1), LCD_DIR_HORIZONTAL);
            LCD_DrawLine((Xpos-(uint16_t)(x/K)), (Ypos-y), (2*(uint16_t)(x/K) + 1), LCD_DIR_HORIZONTAL);

            e2 = err;
            if (e2 <= x)
            {
                err += ++x*2+1;
                if (-y == x && e2 <= y) e2 = 0;
            }
            if (e2 > y)
                err += ++y*2+1;
        }
        while (y <= 0);

    */
}


void pre_battery(void)
{
    u8 len  = 0;
    len = Num2Str((u16) Bat, battery_buf, 5);
    battery_buf[len++] ='%';
    battery_buf[len] ='\0';
}

void pre_percent(uint8_t * buf,uint8_t percent)
{
    u16 len  = 0;
    //len = Num2Str((u16) percent, TL_buf, 5);
    Ascii_Float2Str(buf, &len, percent, 0);


    //TL_buf[len++] ='%';
    buf[len] ='\0';
}




void pre_temper(char* buf, u8 value)
{
    u16 len  = 0;
    float temp = value;
    UnitType_ = 0;

    if(UnitType_)
    {
        temp = DegreeConvert(temp);
        Ascii_Float2Str(buf, &len, temp,0);
    }
    else
    {
        len += Num2Str((u16)temp, buf + len, 5);
    }
    //temper_buf[len++] ='*';//
    // temper_buf[len++] = (!UnitType_) ? '$' : 0x7d ;//==1 ->C degree uint |==0 ->F degree unit
    buf[len]='\0';
}



void pre_time(char *Clock, uint8_t flat,u8 hour, u8 munite)
{
    u8 len  = 0;
    u8 _hh = hour;
    u8 _mm = munite;
    hrType = 1;

    if(flat)
    {
        if((midnight == 1) && (hrType == 1)) {
            _hh = _hh + 12;
            if(_hh == 24) {
                _hh = 12;
            }
        }
        if((midnight == 0)&&(_hh == 12)&& (hrType == 1)) {
            _hh = 0;
        }

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
void pre_TotalDive(uint8_t *buf, uint8_t value)
{
    u8 len  = 0;
    len = Num2Str(value, buf, 5);
    buf[len] ='\0';
}
void pre_TotalDivetime(uint8_t *buf, uint8_t value)
{
    u8 len  = 0;
    len = Num2Str(value, buf, 5);
    buf[len++] ='H';
    buf[len++] ='R';
    buf[len] ='\0';
}
void pre_Divetime(uint8_t *buf, uint8_t value)
{
    u8 len  = 0;
    len = Num2Str(value, buf, 5);
    buf[len++] ='M';
    buf[len++] ='I';
    buf[len++] ='N';
    buf[len] ='\0';
}
void pre_Depth(uint8_t *buf, uint8_t value)
{
    u8 len  = 0;
    len = Num2Str(value, buf, 5);
    buf[len++] ='F';
    buf[len++] ='T';
    buf[len] ='\0';
}


u16 fonts_test = 0x0000;
u8 Fonts_buf[8] = "123456";
void Test_Fonts(void)
{
    // LCD_FillScreen(White);
    //LCD_SetTextColor(Black);
    LCD_Clear(SEPIA_BG);
    //redrawScreen(0, 0,320, 150,fonts_test++);
    // LCD_SetTextColor(White);

    //FontSet = &(fonts_9);
    //LCD_DisplayStringLine(20,50, "fonts demo, smallest size --  FONT DEMO");

    // FontSet = &(fonts_12);
    //LCD_DisplayStringLine(20,100, "PELAGIC - SEPIA");

    //FontSet = &(fonts_40);m
    //FontSet = &(fonts_35);
    //FontSet = myriad_bold_30;
    //Fonts_buf[0] = '0';
    //Fonts_buf[1]  ='x';
    //Fonts_buf[2]  =' ';
    //Fonts_buf[3] = ' ';
    //Fonts_buf[4] = ' ';
    //Fonts_buf[5] = ' ';
    //Fonts_buf[6] = ' ';
    //Fonts_buf[7] = ' ';


    //LCD_DisplayStringLine(50,100, "Nguyen Phu Thinh");
    //fonts_test = 0xffff;
    //Hex2Str(fonts_test, Fonts_buf+2, 6);
    //LCD_DisplayStringLine(20,200, Fonts_buf);


    /*
        redrawScreen(0, 0,80, 60,ASSEMBLE_RGB(0,0,0)); //Black
        redrawScreen(80, 0,160, 60,ASSEMBLE_RGB(128,128,128));//gray
        redrawScreen(160, 0,240, 60,ASSEMBLE_RGB(192,192,192));//silver
        redrawScreen(240, 0,320, 60,ASSEMBLE_RGB(255,255,255));//white

        redrawScreen(0, 60,80, 120,ASSEMBLE_RGB(128,0,0)); //maroon
        redrawScreen(80, 60,160, 120,ASSEMBLE_RGB(255,0,0));//red
        redrawScreen(160, 60,240, 120,ASSEMBLE_RGB(128,128,0));//olive
        redrawScreen(240, 60,320, 120,ASSEMBLE_RGB(255,255,0));//yellow

        redrawScreen(0, 120,80, 180,ASSEMBLE_RGB(0,128,0)); //green
        redrawScreen(80, 120,160, 180,ASSEMBLE_RGB(0,255,0));//lime
        redrawScreen(160, 120,240, 180,ASSEMBLE_RGB(0,128,128));//teal
        redrawScreen(240, 120,320, 180,ASSEMBLE_RGB(0,255,255));//aqua

        redrawScreen(0, 180,80, 240,ASSEMBLE_RGB(0,0,128)); //navy
        redrawScreen(80, 180,160, 240,ASSEMBLE_RGB(0,0,255));//blue
        redrawScreen(160, 180,240, 240,ASSEMBLE_RGB(128,0,128));//purple
        redrawScreen(240, 180,320, 240,ASSEMBLE_RGB(255,0,255));//fuchsia
    */

    //LCD_SetTextColor(Red);
    //LCD_SetBackColor(Green);
//LCD_DrawFullRect(50,50,50,50);
    //LCD_DrawRect(50,50,50,50);

    Draw_S1();
}

/**ducthinh90
  * @brief  Displays a pixel with defined color
  * @param  x: pixel x.s
  * @param  y: pixel y.
  * @retval None
  */


uint8_t TotalDives = 123;
uint8_t TotalDives_buf[10] ="162";
uint8_t TotalDivesTime = 234;
uint8_t TotalDivesTime_buf[10]="128 HR";
uint8_t MaxDivesTime =75;
uint8_t MaxDivesTime_buf[10]="72 MIN";
uint8_t AvgDivesTime = 48;
uint8_t AvgDivesTime_buf[10]="39 MIN";
uint8_t MaxDepth = 135;
uint8_t MaxDepth_buf[10]="136 FT";
uint8_t AvgDepth = 98;
uint8_t AvgDepth_buf[10]="43 FT";
uint8_t LowTemp = 50;
uint8_t LowTemp_buf[10]="39 F";
uint8_t MaxAtitude_buf[10]="EL2";




void Text_H2(void)
{
    FontSet = myriad_bold_12;
    LCD_SetTextColor(White);
    LCD_DisplayStringLine_As_Left(20,160,26, "HOME");
    FontSet = myriad_bold_14;
    LCD_DisplayStringLine_As_Left(205,320,25, "HISTORY");

    LCD_DisplayStringLine_As_Left(120,320,49+21*0, "TOTAL DIVES");
    LCD_DisplayStringLine_As_Left(120,320,49+21*1, "TOTAL DIVE TIME");
    LCD_DisplayStringLine_As_Left(120,320,49+21*2, "MAX DIVE TIME");
    LCD_DisplayStringLine_As_Left(120,320,49+21*3, "AVERAGE DIVE TIME");
    LCD_DisplayStringLine_As_Left(120,320,49+21*4, "MAX DEPTH");
    LCD_DisplayStringLine_As_Left(120,320,49+21*5, "AVERAGE DEPTH");
    LCD_DisplayStringLine_As_Left(120,320,49+21*6, "LOWEST TEMP");
    LCD_DisplayStringLine_As_Left(120,320,49+21*7, "MAX ALTITUDE");

    pre_TotalDive(TotalDives_buf,TotalDives);
    pre_TotalDivetime(TotalDivesTime_buf,TotalDivesTime);
    pre_Divetime(MaxDivesTime_buf,MaxDivesTime);
    pre_Divetime(AvgDivesTime_buf,AvgDivesTime);
    pre_Depth(MaxDepth_buf,MaxDepth);
    pre_Depth(AvgDepth_buf,AvgDepth);
    pre_temper(LowTemp_buf,LowTemp);
    LowTemp_buf[2] ='F';
    LowTemp_buf[3] ='\0';

    LCD_DisplayStringLine_As_Right(310,49+21*0, TotalDives_buf);
    LCD_DisplayStringLine_As_Right(310,49+21*1, TotalDivesTime_buf);
    LCD_DisplayStringLine_As_Right(310,49+21*2, MaxDivesTime_buf);
    LCD_DisplayStringLine_As_Right(310,49+21*3, AvgDivesTime_buf);
    LCD_DisplayStringLine_As_Right(310,49+21*4, MaxDepth_buf);
    LCD_DisplayStringLine_As_Right(310,49+21*5, AvgDepth_buf);
    LCD_DisplayStringLine_As_Right(310,49+21*6, LowTemp_buf);
    LCD_DisplayStringLine_As_Right(310,49+21*7, MaxAtitude_buf);
}



void Text_H3(void)
{

    FontSet = myriad_bold_12;
    LCD_SetTextColor(White);
    LCD_DisplayStringLine_As_Left(20,160,26, "HOME");
    FontSet = myriad_bold_14;
    LCD_DisplayStringLine_As_Left(205,320,25, "OP MODE");

    FontSet = myriad_bold_38;
    if(OP_mode == NORM) {
        redrawScreen(0, 70,320, 133,SEPIA_SELECT);
        redrawScreen(0, 133,320, 196,SEPIA_BG);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(SEPIA_SELECT);


        LCD_DisplayStringLine_Center(0,320,80, "NORM MODE");
        LCD_SetTextColor(White);
        LCD_SetBackColor(Black);

        LCD_DisplayStringLine_Center(0,320,142, "GAUGE MODE");
    }
    else {
        redrawScreen(0, 70,320, 133,SEPIA_BG);
        redrawScreen(0, 133,320, 196,SEPIA_SELECT);
        LCD_SetTextColor(White);
        LCD_SetBackColor(Black);

        LCD_DisplayStringLine_Center(0,320,80, "NORM MODE");
        LCD_SetTextColor(Black);
        LCD_SetBackColor(SEPIA_SELECT);
        LCD_DisplayStringLine_Center(0,320,142, "GAUGE MODE");
    }
}

void Text_H5(void)
{

    Headings_text();

    FontSet = myriad_bold_14;
    //LCD_SetTextColor(White);
    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_GRAY);
    //LCD_DisplayStringLine_As_Left(20,160,26, "SETTINGS");
    LCD_DisplayStringLine_As_Left(20,160,40, "SETTINGS");

    FontSet = myriad_bold_17;
    LCD_SetBackColor(SEPIA_BG);
    //LCD_DisplayStringLine_As_Left(205,320,23, "SET GASES");
    LCD_DisplayStringLine_As_Left(205,320,43, "SET GASES");



    DisplayText_Left(line_none, line_all, GAS);
    DisplayText_Left(1, line_none, GAS);
    DisplayText_Right_GAS(GAS2,0);
}

void Text_H6(void)
{
    //FontSet = myriad_bold_12;
    //LCD_SetTextColor(White);
    // LCD_DisplayStringLine_As_Left(20,160,26, "SETTINGS");
    // FontSet = myriad_bold_14;
    //LCD_DisplayStringLine_As_Left(205,320,25, "SET GASES");

    // FontSet = myriad_bold_14;
    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_GRAY);
    LCD_DisplayStringLine_As_Left(170,256,60+23*0, "SET");
    LCD_DisplayStringLine_As_Right(310,60+23*0, "ON");

    LCD_DisplayStringLine_As_Left(170,256,60+23*2, "PO2 ALARM");
    LCD_DisplayStringLine_As_Right(310,60+23*2, "1.40");


    LCD_SetTextColor(Black) ;
    LCD_SetBackColor(SEPIA_SELECT);

    LCD_DisplayStringLine_As_Left(170,256,60+23*1, "FO2");
    LCD_DisplayStringLine_As_Right(310,60+23*1, "32%");

}

void Text_H10(void)
{

    redrawScreen(180, 25,280 , 40 ,SEPIA_BG);        /*redraw top -right side for setting*/
    FontSet = myriad_bold_14;
    LCD_SetTextColor(White) ;
    LCD_SetBackColor(Black);
    LCD_DisplayStringLine_Center(180,300,27, "SET TMT");



    DisplayText_Left(line_none, line_all, TMT);
    DisplayText_Left(line1, line_none, TMT);
    DisplayText_Right_TMT( TMT2, 0);
}
void Text_H11(void)
{
    set_tmt_flat = 0;
    DisplayText_Right_TMT( TMT2, 1);
    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_Center(170,320,60+23*3, "SERIAL");

    Select_unselect_TMTnum(7, 7);
}

void Text_H12(void)
{
    set_tmt_flat = 1;
    DisplayText_Right_TMT( TMT2, 1);
    Select_unselect_TMTnum(1, 8);
}

void Text_H13(void)
{

    FontSet = myriad_bold_12;
    LCD_SetTextColor(White);
    LCD_DisplayStringLine_As_Left(20,160,26, "SETTINGS");
    FontSet = myriad_bold_14;
    LCD_DisplayStringLine_As_Left(205,320,25, "BLUETOOTH");

    FontSet = myriad_bold_38;
    if(OP_mode == NORM) {
        redrawScreen(0, 70,320, 133,SEPIA_SELECT);
        redrawScreen(0, 133,320, 196,SEPIA_BG);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(SEPIA_SELECT);
        LCD_DisplayStringLine_Center(0,320,80, "BT ON");
        LCD_SetTextColor(White);
        LCD_SetBackColor(Black);
        LCD_DisplayStringLine_Center(0,320,142, "BT OFF");
    }
    else {
        redrawScreen(0, 70,320, 133,SEPIA_BG);
        redrawScreen(0, 133,320, 196,SEPIA_SELECT);
        LCD_SetTextColor(White);
        LCD_SetBackColor(Black);
        LCD_DisplayStringLine_Center(0,320,80, "BT ON");
        LCD_SetTextColor(Black);
        LCD_SetBackColor(SEPIA_SELECT);
        LCD_DisplayStringLine_Center(0,320,142, "BT OFF");
    }
}

void Text_H14(void)
{
    FontSet = myriad_bold_12;
    LCD_SetTextColor(White);
    LCD_DisplayStringLine_As_Left(20,160,26, "SETTINGS");
    FontSet = myriad_bold_14;
    LCD_DisplayStringLine_As_Left(205,320,25, "DATE & TIME");


    DisplayText_Left(line_none, line_all, DATE);
    DisplayText_Left(0, line_none, GAS);
    //DisplayText_Right_GAS(GAS2,0);
    DisplayText_Right_Date(Date_format,0);
}
void Text_H15(void)
{
    DisplayText_Right_Date(Time_format,1);

}
void Text_H19(void)
{
    DisplayText_Right_Date(Set_Date,1);

}
void Text_H20(void)
{
    DisplayText_Right_Date(Set_time,1);

}

void Text_H23(void)
{
    FontSet = myriad_bold_12;

    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_GRAY);
    LCD_DisplayStringLine_As_Left(20,160,26, "SETTINGS");
    LCD_SetBackColor(SEPIA_BG);
    FontSet = myriad_bold_14;
    LCD_DisplayStringLine_As_Left(205,320,25, "BRIGHNESS");


    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_BG);
    //LCD_DisplayStringLine_Center(190,290,90, "To adjust the % of full allumination.");


    DisplayText_Left(line_none, line_all, BRIGHTNESS);
    DisplayText_Left(0, line_none, BRIGHTNESS);


    dispay_brightness(100);
}

void Text_H81(void)
{

    FontSet = myriad_bold_15;
    LCD_SetTextColor(SEPIA_SELECT) ;
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_Center(0,76,65+21*0, "MIC");
    LCD_DisplayStringLine_Center(0,76,65+21*1, "EVA");
    LCD_DisplayStringLine_Center(0,76,65+21*2, "EGI");

    LCD_SetTextColor(White) ;

    LCD_DisplayStringLine_Center(0,76,65+21*3, "SU1");
    LCD_DisplayStringLine_Center(0,76,65+21*4, "SU2");
    LCD_DisplayStringLine_Center(0,76,65+21*5, "JIM");
    LCD_DisplayStringLine_Center(0,76,65+21*6, "VAL");
    LCD_DisplayStringLine_Center(0,76,65+21*7, "TIM");


    LCD_DisplayStringLine_Center(76,155,65+21*0, "TAM");
    LCD_DisplayStringLine_Center(76,155,65+21*1, "NIC");
    LCD_DisplayStringLine_Center(76,155,65+21*2, "ALI");
    LCD_DisplayStringLine_Center(76,155,65+21*3, "FRE");
    LCD_DisplayStringLine_Center(76,155,65+21*4, "SAM");
    LCD_DisplayStringLine_Center(76,155,65+21*5, "BOA");



    redrawScreen(155, 22,320, 44,SEPIA_BG);
    redrawScreen(155, 46,320, 220,SEPIA_BG); /*the right side*/


    FontSet = myriad_bold_17;
    LCD_SetBackColor(SEPIA_BG);
    LCD_SetTextColor(White) ;
    LCD_DisplayStringLine_Center(150,320,43, "PARTNERS");

    FontSet = myriad_bold_15;


    LCD_DisplayStringLine_Center(160,310,70, "Select max 3 partners to be displayed on  Sonar Map  ");

    writeBMP_nTimes((uint16_t const *)&BMP_Select, 16,23,155,150,1);
    writeBMP_nTimes((uint16_t const *)&BMP_save, 13,29,158,180,1);

    LCD_DisplayStringLine_Center(170,320,165, "to select/deselect");
    LCD_DisplayStringLine_Center(175,320,195, "to save and exit");


    //redrawScreen(0, 46+21*0,75, 46+21*1,SEPIA_SELECT);
    //FontSet = myriad_bold_15;
    //LCD_SetTextColor(Black) ;
    //LCD_SetBackColor(SEPIA_SELECT);
    //LCD_DisplayStringLine_Center(0,76,65+21*0, "MIC");

}

void Text_H86(void)
{

    FontSet = myriad_bold_14;
    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_As_Left(10,155,65+21*0, "FULL");
    LCD_DisplayStringLine_As_Left(10,155,65+21*1, "RX ON, TX STAND BY");
    LCD_DisplayStringLine_As_Left(10,155,65+21*2, "RX TX STAND BY");
    LCD_DisplayStringLine_As_Left(10,155,65+21*3, "OFF");



    redrawScreen(155, 22,320, 44,SEPIA_BG);
    redrawScreen(155, 46,320, 220,SEPIA_BG); /*the right side*/

    //FontSet = myriad_bold_14;
    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_GRAY);
    LCD_DisplayStringLine_As_Left(20,160,40, "NAVIGATION");

    FontSet = myriad_bold_17;
    LCD_SetBackColor(SEPIA_BG);
    LCD_SetTextColor(White) ;
    LCD_DisplayStringLine_Center(150,320,43, "NAV MODE");

    FontSet = myriad_bold_15;
//LCD_DisplayStringLine_Center(158,315,65, "RX and TX ON. SMS and locator features will be available during dive. You can switch to other nav modes when desired ");
    //LCD_DisplayStringLine_Center(159,316,65, "RX and TX ON. SMS and locator features will be available during dive.You can switch to other nav modes when desired");


    //LCD_DisplayStringLine_Center(162,290,65, "RX and TX ON. SMS and locator features will be available during dive. You can switch to other nav modes when desired ");

    writeBMP_nTimes((uint16_t const *)&BMP_Select, 16,23,180,191,1);
    LCD_DisplayStringLine_Center(175,320,205, "to confirm");


}


void Text_H89(void)
{

    FontSet = myriad_bold_14;
    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_As_Left(10,155,65+21*0, "FULL");
    LCD_DisplayStringLine_As_Left(10,155,65+21*1, "RX ON, TX STAND BY");
    LCD_DisplayStringLine_As_Left(10,155,65+21*2, "RX TX STAND BY");
    LCD_DisplayStringLine_As_Left(10,155,65+21*3, "OFF");



    redrawScreen(155, 22,320, 44,SEPIA_BG);
    redrawScreen(155, 46,320, 220,SEPIA_BG); /*the right side*/

    FontSet = myriad_bold_17;
    LCD_SetBackColor(SEPIA_BG);
    LCD_SetTextColor(White) ;
    LCD_DisplayStringLine_Center(150,320,43, "NAV MODE");

    FontSet = myriad_bold_15;
    //LCD_DisplayStringLine_Center(162,320,65, "List the partners and partner groups with their depths and tank pressures. Select partners to be displayed on Sonar Map.");//SO13
    //LCD_DisplayStringLine_Center(162,320,65, "RX and TX ON.SMS and locator features their depths and tank pressures. Select partners to be displayed on Sonar Map.");//SO13
    LCD_DisplayStringLine_Center(158,315,65, "RX and TX ON SMS and locator features will be available during dive You can switch to other nav modes when desired ");


    //LCD_DisplayStringLine_Center(162,290,65, "RX and TX ON. SMS and locator features will be available during dive. You can switch to other nav modes when desired ");

    writeBMP_nTimes((uint16_t const *)&BMP_Select, 16,23,180,191,1);
    LCD_DisplayStringLine_Center(175,320,205, "to confirm");


    //redrawScreen(0, 46+21*0,75, 46+21*1,SEPIA_SELECT);
    //FontSet = myriad_bold_15;
    //LCD_SetTextColor(Black) ;
    //LCD_SetBackColor(SEPIA_SELECT);
    //LCD_DisplayStringLine_Center(0,76,65+21*0, "MIC");

}
void Text_H94(void)
{
    FontSet = myriad_bold_19;
    LCD_SetTextColor(Black);
    LCD_SetBackColor(SEPIA_SELECT);
    LCD_DisplayStringLine_Center(0,141,22, "DATA 2");

    FontSet = myriad_bold_16;
    LCD_SetTextColor(White);
    LCD_SetBackColor(SEPIA_GRAY);
    //LCD_DisplayStringLine_Center(141,320,22, "52  11/13/14  #2 02:05P");
    LCD_DisplayStringLine_As_Left(141,320,22, "  52  11/13/14");
    LCD_DisplayStringLine_As_Left(243,320,22, "#2 02:05P");

    FontSet = myriad_bold_16;
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_Center(0,179,53, "Gas 1: AIR");
    FontSet = myriad_bold_14;
    LCD_DisplayStringLine_Center(0,180,70, "Start:2897 - End:1089 PSI");

    FontSet = myriad_bold_16;
    LCD_DisplayStringLine_As_Left(50,180,106, "Gas 2: ");
    //LCD_DisplayStringLine_As_Left(95,180,106, "NX 32");


    LCD_DisplayStringLine_Center(0,179,150, "Gas 3: OFF");
    LCD_DisplayStringLine_Center(0,179,194, "Gas 4: OFF");

    LCD_SetTextColor(SEPIA_GREEN);
    LCD_DisplayStringLine_As_Left(95,180,106, " NX 32");

    FontSet = myriad_bold_19;
    LCD_SetTextColor(SEPIA_GRAY);
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_Center(180,320,65, "MAX PO2");
    LCD_SetTextColor(White);
    LCD_DisplayStringLine_As_Left(216,320,95, "0.89");

    FontSet = myriad_bold_15;
    LCD_DisplayStringLine_As_Left(261,320,100, "ATA");
    LCD_SetTextColor(SEPIA_GRAY);
    FontSet = myriad_bold_19;
    LCD_DisplayStringLine_Center(180,320,150, "O2 SAT");
    LCD_SetTextColor(White);
    LCD_DisplayStringLine_Center(180,320,180, "49%");

}

void Text_S1(void)
{
    FontSet = myriad_bold_57;
    LCD_SetTextColor(SEPIA_Cyan);
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_As_Left(90,320,85, "0:34");
    LCD_SetTextColor(White);

    FontSet = myriad_bold_38;

    LCD_SetTextColor(SEPIA_GREEN);
    LCD_DisplayStringLine_Center(22,155,145, "NORM");


    LCD_SetTextColor(SEPIA_Cyan);
    LCD_DisplayStringLine_As_Left(115,320,200, "2789");

    LCD_SetTextColor(White);

    FontSet = myriad_bold_22;
    LCD_DisplayStringLine_As_Left(60,320,200, "AIR");
    LCD_DisplayStringLine_As_Left(236,320,215, "ATR");
    LCD_DisplayStringLine_As_Left(236,320,179, "_ _");
    LCD_SetTextColor(SEPIA_Cyan);
    LCD_DisplayStringLine_As_Left(136,320,215, "PSI");
    LCD_SetTextColor(White);


    FontSet = myriad_bold_17;
    LCD_SetTextColor(White);
    LCD_DisplayStringLine_Center(155,300,116, "LAST DIVE #4");
    FontSet = myriad_bold_15;
    LCD_DisplayStringLine_As_Left(166,320,135, "05/19/14");
    LCD_DisplayStringLine_As_Left(250,320,135, "22:43");
    LCD_DisplayStringLine_As_Left(178,320,157, "83 FT  -");
    LCD_DisplayStringLine_As_Left(236,320,157, "48 MIN");

}


void Text_D25(void)
{
    FontSet = myriad_bold_57;
    LCD_SetTextColor(White);
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_As_Left(115,320,80, "76");
    FontSet = myriad_bold_38;
    LCD_DisplayStringLine_As_Left(220,320,200, "23");

    LCD_SetTextColor(Green);
    LCD_DisplayStringLine_As_Left(115,320,200, "2789");
    LCD_SetTextColor(White);

    FontSet = myriad_bold_22;
    //LCD_DisplayStringLine_As_Left(39,320,170, "TMT");
    //LCD_DisplayStringLine_As_Left(52,320,190, "1");
    //LCD_DisplayStringLine_As_Left(138,320,190, "PSI");
    //LCD_DisplayStringLine_As_Left(234,320,190, "ATR");

    FontSet = myriad_bold_19;
    //LCD_SetTextColor(Black);
    // LCD_SetBackColor(White);
    //LCD_DisplayStringLine_As_Left(71,320,0, "1");

    FontSet = myriad_bold_38;
    LCD_DisplayStringLine_As_Left(202,320,155, "39");
    LCD_SetTextColor(Green);
    LCD_DisplayStringLine_As_Left(54,320,155, "23");
    LCD_SetTextColor(White);

    FontSet = myriad_bold_22;
    LCD_DisplayStringLine_As_Left(250,320,150, "MIN");
    LCD_SetTextColor(Green);
    LCD_DisplayStringLine_As_Left(103,320,150, "MIN");
    LCD_SetTextColor(White);

    LCD_DisplayStringLine_As_Left(182,320,70, "FT");




    // LCD_SetBackColor(SEPIA_GRAY);
    FontSet = myriad_bold_17;
    LCD_DisplayStringLine_As_Left(190,320,115, "DIVE TIME");
    FontSet = myriad_bold_16;
    LCD_DisplayStringLine_As_Left(265,320,190, "MIN");


    LCD_SetTextColor(Green);
    LCD_DisplayStringLine_As_Left(54,320,115, "NO DECO");

    FontSet = myriad_bold_17;
    LCD_SetTextColor(Red);
    //LCD_DisplayStringLine_As_Left(25,320,50, "MIC");
    //LCD_DisplayStringLine_As_Left(25,320,70, "SOS");



    LCD_SetTextColor(White);
    FontSet = myriad_bold_22;
    LCD_DisplayStringLine_As_Left(60,320,200, "AIR");
    LCD_DisplayStringLine_As_Left(236,320,219, "GTR");
    LCD_SetTextColor(Green);
    LCD_DisplayStringLine_As_Left(136,320,219, "PSI");

    LCD_SetTextColor(Red);
    LCD_SetBackColor(SEPIA_TOP);
    FontSet = myriad_bold_16;
    LCD_DisplayStringLine_As_Left(85,320,18, "2");

}

void Text_D9(void)
{
    FontSet = myriad_bold_14;
    LCD_SetTextColor(White);
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_As_Left(25,320,35, "BRIGTHNESS");
    LCD_DisplayStringLine_As_Left(25,320,35+22*2, "PROFILE_TISSUE");
    LCD_DisplayStringLine_As_Left(25,320,35+22*3, "DS PREVIEW");
    LCD_DisplayStringLine_As_Left(25,320,35+22*4, "GAS SWITCH");
    LCD_SetTextColor(Black);
    LCD_SetBackColor(SEPIA_SELECT);
    LCD_DisplayStringLine_As_Left(25,320,35+22*1, "MORE DATA");


    FontSet = myriad_bold_12;
    LCD_SetTextColor(White);
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_As_Left(158,320,35, "NO DECO");
    LCD_DisplayStringLine_As_Left(158,320,35+22*1, "DIVE TIME");
    LCD_DisplayStringLine_As_Left(158,320,35+22*2, "MAX DEPTH");
    LCD_DisplayStringLine_As_Left(158,320,35+22*3, "ELEVATION");
    LCD_DisplayStringLine_As_Left(158,320,35+22*4, "GAS 1");
    LCD_DisplayStringLine_As_Left(158,320,35+22*5, "PO2 AL");
    LCD_DisplayStringLine_As_Left(158,320,35+22*6, "O2 SAT");
    LCD_DisplayStringLine_As_Left(158,320,35+22*7, "CURRENT PO2");

    LCD_SetTextColor(SEPIA_GREEN);
    LCD_DisplayStringLine_As_Left(243,320,35, "23 MIN");
    LCD_SetTextColor(White);
    LCD_DisplayStringLine_As_Left(243,320,35+22*1, "39 MIN");
    LCD_DisplayStringLine_As_Left(243,320,35+22*2, "123 FT");
    LCD_DisplayStringLine_As_Left(243,320,35+22*3, "SEA");
    LCD_DisplayStringLine_As_Left(243,320,35+22*4, "NX 32");
    LCD_DisplayStringLine_As_Left(243,320,35+22*5, "1.40");

    LCD_SetTextColor(SEPIA_GREEN);
    LCD_DisplayStringLine_As_Left(243,320,35+22*6, "32%");
    LCD_DisplayStringLine_As_Left(243,320,35+22*7, "0.89");


    FontSet = myriad_bold_19;
    LCD_SetTextColor(Black);
    LCD_SetBackColor(SEPIA_TOP);
    LCD_DisplayStringLine_As_Left(229,320,0, "56");
    FontSet = myriad_bold_14;
    LCD_DisplayStringLine_As_Left(254,320,6, "FT");

}
void Text_H74(void)
{

    Headings_text();

    FontSet = myriad_bold_14;
    //LCD_SetTextColor(White);
    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_GRAY);
    LCD_DisplayStringLine_As_Left(20,160,26, "HOME");
    FontSet = myriad_bold_14;
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_As_Left(200,320,25, "NAVIGATION");


    FontSet = myriad_bold_9;
    //LCD_SetTextColor(WHITE_ICON);
    LCD_SetTextColor(White);
    LCD_DisplayStringLine_As_Left(30,320,92, "SET ID");
    LCD_DisplayStringLine_As_Left(27,320,150, "SET SMS");
    LCD_DisplayStringLine_As_Left(24,320,204, "PARTNERS");

    LCD_DisplayStringLine_As_Left(142,320,92, "PAIRING");
    LCD_DisplayStringLine_As_Left(247,320,92, "NAV MODE");
    LCD_DisplayStringLine_As_Left(249,320,150, "RE-SYNC");

    LCD_SetTextColor(Black) ;
    LCD_SetBackColor(SEPIA_SELECT);
    LCD_DisplayStringLine_As_Left(138,320,150, "CHANNEL");

}

void Text_DiveMenu(void)
{

    //uint8_t time_buf1[6];


    LCD_SetTextColor(Black);
    LCD_SetBackColor(White);

    FontSet = myriad_bold_14;

    LCD_SetTextColor(White);
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_As_Left(25,320,50, "BRIGTHNESS");
    LCD_DisplayStringLine_As_Left(25,320,50+22*1, "MORE DATA");
    LCD_DisplayStringLine_As_Left(25,320,50+22*2, "PROFILE-TISSUE");
    LCD_DisplayStringLine_As_Left(25,320,50+22*3, "DS PREVIEW");
    LCD_DisplayStringLine_As_Left(25,320,50+22*4, "GAS SWITCH");
    LCD_DisplayStringLine_As_Left(25,320,50+22*5, "RE-SYNC");



    //LCD_SetTextColor(Black);
    // LCD_SetBackColor(SEPIA_SELECT);

    //LCD_DisplayStringLine_As_Left(37,320,239, "EVA :");


    LCD_SetTextColor(White);
    LCD_SetBackColor(SEPIA_BG);
    FontSet = myriad_bold_15;
    //LCD_DisplayStringLine_Center(162,290,55, "List the partners and partner groups with their depths and tank pressures. Select partners to be displayed on Sonar Map.");//SO13
    // LCD_DisplayStringLine_Center(172,280,85, "Select an SMS and send to partners  ");//SO11


    // FontSet = myriad_bold_15;
    //LCD_SetTextColor(Black);
    //LCD_SetBackColor(SEPIA_TOP);
    // LCD_DisplayStringLine_As_Left(81,220,238, "I am surfacing");
    //  LCD_DisplayStringLine_As_Left(263,320,238, "12:45 P");

    Select_DiveMenu(0x10);

}



void Select_unselect_Left(u8 index_sel, u8 index_unsel)
{

    switch(index_unsel)
    {
    case 0:
        redrawScreen(0, 46 +21*0, 155, 66 +21*0 ,SEPIA_BG);
        break;

    case 1:
        redrawScreen(0, 46 +21*1, 155, 66 +21*1 ,SEPIA_BG);
        break;

    case 2:
        redrawScreen(0, 46 +21*2, 155, 66 +21*2 ,SEPIA_BG);
        break;

    case 3:
        redrawScreen(0, 46 +21*3, 155, 66 +21*3 ,SEPIA_BG);
        break;

    case 4:
        redrawScreen(0, 46 +21*4, 155, 66 +21*4 ,SEPIA_BG);
        break;

    case 5:
        redrawScreen(0, 46 +21*5, 155, 66 +21*5 ,SEPIA_BG);
        break;

    case 6:
        redrawScreen(0, 46 +21*6, 155, 66 +21*6 ,SEPIA_BG);
        break;

    case 7:
        redrawScreen(0, 46 +21*7, 155, 66 +21*7 ,SEPIA_BG);
        break;

    case 8:
        redrawScreen(0, 46 +21*0, 155, 66 +21*0 ,SEPIA_BG);
        redrawScreen(0, 46 +21*1, 155, 66 +21*1 ,SEPIA_BG);
        redrawScreen(0, 46 +21*2, 155, 66 +21*2 ,SEPIA_BG);
        redrawScreen(0, 46 +21*3, 155, 66 +21*3 ,SEPIA_BG);
        redrawScreen(0, 46 +21*4, 155, 66 +21*4 ,SEPIA_BG);
        redrawScreen(0, 46 +21*5, 155, 66 +21*5 ,SEPIA_BG);
        redrawScreen(0, 46 +21*6, 155, 66 +21*6 ,SEPIA_BG);
        redrawScreen(0, 46 +21*7, 155, 66 +21*7 ,SEPIA_BG);
        break;

    default:
        break;

    }
    switch(index_sel)
    {
    case 0:
        redrawScreen(0, 46 +21*0, 155, 66 +21*0 ,SEPIA_SELECT);
        break;

    case 1:
        redrawScreen(0, 46 +21*1, 155, 66 +21*1 ,SEPIA_SELECT);
        break;

    case 2:
        redrawScreen(0, 46 +21*2, 155, 66 +21*2 ,SEPIA_SELECT);
        break;

    case 3:
        redrawScreen(0, 46 +21*3, 155, 66 +21*3 ,SEPIA_SELECT);
        break;

    case 4:
        redrawScreen(0, 46 +21*4, 155, 66 +21*4 ,SEPIA_SELECT);
        break;

    case 5:
        redrawScreen(0, 46 +21*5, 155, 66 +21*5 ,SEPIA_SELECT);
        break;

    case 6:
        redrawScreen(0, 46 +21*6, 155, 66 +21*6 ,SEPIA_SELECT);
        break;

    case 7:
        redrawScreen(0, 46 +21*7, 155, 66 +21*7 ,SEPIA_SELECT);
        break;



    default:
        break;

    }
    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(0, 67 +21*0, 155, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*1, 155, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*2, 155, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*3, 155, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*4, 155, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*5, 155, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*6, 155, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*7, 155, LCD_DIR_HORIZONTAL);
}

void Text_SO8(void)
{

    //uint8_t time_buf1[6];

    LCD_SetTextColor(Black);
    LCD_SetBackColor(White);

    FontSet = myriad_bold_14;
    // FontSet = myriad_bold_13;

    LCD_SetTextColor(Red);
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_As_Left(25,320,50, "1:SOS");
    LCD_SetTextColor(White);
    LCD_DisplayStringLine_As_Left(25,320,50+22*1, "2:OK");
    LCD_DisplayStringLine_As_Left(25,320,50+22*2, "3:ARE YOU OK");
    LCD_DisplayStringLine_As_Left(25,320,50+22*3, "4:YES");
    LCD_DisplayStringLine_As_Left(25,320,50+22*4, "5:NO");
    LCD_DisplayStringLine_As_Left(25,320,50+22*5, "6:LOW BATTERY");
    LCD_DisplayStringLine_As_Left(25,320,50+22*6, "7:FINISH THE DIVE");
    LCD_DisplayStringLine_As_Left(25,320,50+22*7, "8:COME HERE");

    LCD_DisplayStringLine_As_Left(158,320,50+22*0, "9:STAY THERE");
    LCD_DisplayStringLine_As_Left(158,320,50+22*1, "10:ALL COME HERE");
    LCD_DisplayStringLine_As_Left(158,320,50+22*2, "11:IM SURFACING");
    LCD_DisplayStringLine_As_Left(158,320,50+22*3, "12:GO TO SURFACE");
    LCD_DisplayStringLine_As_Left(158,320,50+22*4, "13:GO TO BOAT");
    LCD_DisplayStringLine_As_Left(158,320,50+22*5, "14:ASCEND");

    //Select_SMS(3);
    //LCD_SetTextColor(Black);
    //LCD_SetBackColor(SEPIA_SELECT);

    //LCD_DisplayStringLine_As_Left(37,320,239, "EVA :");


    LCD_SetTextColor(White);
    LCD_SetBackColor(SEPIA_BG);
    FontSet = myriad_bold_15;
    //LCD_DisplayStringLine_Center(162,290,55, "List the partners and partner groups with their depths and tank pressures. Select partners to be displayed on Sonar Map.");//SO13
    //LCD_DisplayStringLine_Center(172,280,85, "Select from the 15 preset SMS to send to partners  ");//SO11


    FontSet = myriad_bold_16;

    LCD_SetTextColor(Black);
    LCD_SetBackColor(SEPIA_TOP);
    LCD_DisplayStringLine_As_Left(37,320,239, "EVA :");
    LCD_DisplayStringLine_As_Left(81,220,238, "I am surfacing");
    LCD_DisplayStringLine_As_Left(263,320,238, "12:45");
    LCD_DisplayStringLine_As_Left(300,320,238, "A");

}
void Text_SO7(void)
{

    //uint8_t time_buf1[6];


    //LCD_SetTextColor(Black);
    //LCD_SetBackColor(White);

    FontSet = myriad_bold_14;

    LCD_SetTextColor(White);
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_As_Left(25,320,50, "BRIGTHNESS");
    LCD_DisplayStringLine_As_Left(25,320,50+22*1, "SEND SMS");
    LCD_DisplayStringLine_As_Left(25,320,50+22*2, "PARTNERS");

    LCD_DisplayStringLine_As_Left(25,320,50+22*3, "SMS LIST");
    LCD_DisplayStringLine_As_Left(25,320,50+22*4, "NAV MODE");



    //LCD_SetTextColor(Black);
    // LCD_SetBackColor(SEPIA_SELECT);

    //LCD_DisplayStringLine_As_Left(37,320,239, "EVA :");


    LCD_SetTextColor(White);
    LCD_SetBackColor(SEPIA_BG);
    FontSet = myriad_bold_15;
    //LCD_DisplayStringLine_Center(162,290,55, "List the partners and partner groups with their depths and tank pressures. Select partners to be displayed on Sonar Map.");//SO13
    LCD_DisplayStringLine_Center(172,280,85, "Select an SMS and send to partners  ");//SO11


    // FontSet = myriad_bold_15;
    //LCD_SetTextColor(Black);
    //LCD_SetBackColor(SEPIA_TOP);
    // LCD_DisplayStringLine_As_Left(81,220,238, "I am surfacing");
    //  LCD_DisplayStringLine_As_Left(263,320,238, "12:45 P");

//Select_SonarMenu(0x30);
}

void Text_SO10(void)
{

    /*Left side, row 1*/
    FontSet = myriad_bold_11;
    LCD_SetTextColor(White);
    LCD_SetBackColor(SEPIA_GRAY);
    LCD_DisplayStringLine_Center(0,62,36, "I D");
    LCD_DisplayStringLine_Center(62,106,36, "FT");
    LCD_DisplayStringLine_Center(106,150,36, "PSI");

    LCD_DisplayStringLine_Center(170+0,170+62,36, "I D");
    LCD_DisplayStringLine_Center(170+62,170+106,36, "FT");
    LCD_DisplayStringLine_Center(170+106,170+150,36, "PSI");

    FontSet = myriad_bold_15;
    //LCD_SetTextColor(White);
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_As_Left(10,150,55+20*0, "MIC");
    LCD_DisplayStringLine_As_Left(10,150,55+20*2, "EGI");
    LCD_DisplayStringLine_As_Left(10,150,55+20*3, "SU1");
    LCD_DisplayStringLine_As_Left(10,150,55+20*5, "JIM");
    LCD_DisplayStringLine_As_Left(10,150,55+20*6, "VAL");
    LCD_DisplayStringLine_As_Left(10,150,55+20*8, "CHR");

    //LCD_SetTextColor(Black);
    //LCD_SetBackColor(SEPIA_SELECT);
    LCD_DisplayStringLine_As_Left(10,150,55+20*1, "EVA");

    //LCD_SetTextColor(Black);
    //LCD_SetBackColor(White);
    LCD_DisplayStringLine_As_Left(10,150,55+20*4, "SU2");
    LCD_DisplayStringLine_As_Left(10,150,55+20*7, "TIM");

    /*Left side, row 2*/

    LCD_SetTextColor(White);
    LCD_SetBackColor((SEPIA_BG));
    LCD_DisplayStringLine_As_Right(99,55+20*0, "65");
    LCD_DisplayStringLine_As_Right(99,55+20*1, "78");
    LCD_DisplayStringLine_As_Right(99,55+20*2, "138");
    LCD_DisplayStringLine_As_Right(99,55+20*3, "132");
    LCD_DisplayStringLine_As_Right(99,55+20*4, "209");
    LCD_DisplayStringLine_As_Right(99,55+20*5, "89");
    LCD_DisplayStringLine_As_Right(99,55+20*6, "97");
    LCD_DisplayStringLine_As_Right(99,55+20*7, "56");
    LCD_DisplayStringLine_As_Right(99,55+20*8, "99");

    /*Left side, row 3*/
    //LCD_SetTextColor(Red);
    // LCD_SetBackColor((SEPIA_BG));

    LCD_SetTextColor(SEPIA_GREEN);
    LCD_SetBackColor((SEPIA_BG));
    LCD_DisplayStringLine_As_Right(148,55+20*0, "354");
    LCD_DisplayStringLine_As_Right(148,55+20*1, "456");

    //LCD_SetTextColor(Yellow);
    LCD_DisplayStringLine_As_Right(148,55+20*2, "895");
    //LCD_SetTextColor(SEPIA_GREEN);
    //LCD_SetBackColor((SEPIA_BG));

    LCD_DisplayStringLine_As_Right(148,55+20*3, "1398");
    LCD_DisplayStringLine_As_Right(148,55+20*4, "2890");
    LCD_DisplayStringLine_As_Right(148,55+20*5, "2645");
    LCD_DisplayStringLine_As_Right(148,55+20*6, "1765");
    LCD_DisplayStringLine_As_Right(148,55+20*7, "2011");
    LCD_DisplayStringLine_As_Right(148,55+20*8, "1879");

    /*Right side, row 1*/

    //LCD_SetTextColor(Black);
    //LCD_SetBackColor(White);
    LCD_SetTextColor(White);
    LCD_SetBackColor((SEPIA_BG));
    LCD_DisplayStringLine_As_Left(170+10,170+150,55+20*0, "TAM");
    //LCD_SetTextColor(White);
    //LCD_SetBackColor((SEPIA_BG));
    LCD_DisplayStringLine_As_Left(170+10,170+150,55+20*1, "BOA");

    /*Right side, row 2*/

    LCD_SetTextColor(White);
    LCD_SetBackColor((SEPIA_BG));
    LCD_DisplayStringLine_As_Right(170+99,55+20*0, "78");
    LCD_DisplayStringLine_As_Right(170+99,55+20*1, "10");

    /*Right side, row 3*/

    LCD_SetTextColor(SEPIA_GREEN);
    LCD_SetBackColor((SEPIA_BG));
    LCD_DisplayStringLine_As_Right(170+148,55+20*0, "1048");

}
void Text_SO16(void)
{

    //uint8_t time_buf1[6];
    uint8_t Y_off = 77;

    FontSet = myriad_bold_14;

    LCD_SetTextColor(White);
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_As_Left(25,320,Y_off, "JIM: Go to surface");
    LCD_DisplayStringLine_As_Left(25,320,Y_off+18*1, "EVA: Low battery");
    LCD_DisplayStringLine_As_Left(25,320,Y_off+18*2, "SU: OK");
    LCD_DisplayStringLine_As_Left(25,320,Y_off+18*3, "SAM: Stay there");
    LCD_DisplayStringLine_As_Left(25,320,Y_off+18*4, "SAM: All divers");
    LCD_DisplayStringLine_As_Left(25,320,Y_off+18*5, "EGI: Yes");
    LCD_DisplayStringLine_As_Left(25,320,Y_off+18*6, "JIM: Are you OK");

    LCD_DisplayStringLine_As_Left(235,320,Y_off, "11:44 A");
    LCD_DisplayStringLine_As_Left(235,320,Y_off+18*1, "11:43 A");
    LCD_DisplayStringLine_As_Left(235,320,Y_off+18*2, "11:42 A");
    LCD_DisplayStringLine_As_Left(235,320,Y_off+18*3, "11:41 A");
    LCD_DisplayStringLine_As_Left(235,320,Y_off+18*4, "11:40 A");
    LCD_DisplayStringLine_As_Left(235,320,Y_off+18*5, "11:39 A");
    LCD_DisplayStringLine_As_Left(235,320,Y_off+18*6, "11:38 A");


}


void Text_SO18(void)
{

    //uint8_t time_buf1[6];

    FontSet = myriad_bold_13;

    LCD_SetTextColor(White);
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_As_Left(22,320,52, "FULL");
    LCD_DisplayStringLine_As_Left(22,320,52+22*1, "RX ON,TX STAND BY");
    LCD_DisplayStringLine_As_Left(22,320,52+22*2, "RX TX STAND BY");
    LCD_DisplayStringLine_As_Left(22,320,52+22*3, "OFF");
}


void Text_H101(void)
{
    redrawScreen(0, 25,160, 40,SEPIA_GRAY);  /*HOME-color*/
    writeBMP_nTimes((uint16_t const *)&BMP_back, 11,13,3,27,1);
    LCD_SetTextColor(0x528A);/*line color*/
    LCD_DrawLine(0, 43, 320, LCD_DIR_HORIZONTAL);
    FontSet = myriad_bold_14;
    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_GRAY);
    LCD_DisplayStringLine_As_Left(20,160,40, "HOME");
    FontSet = myriad_bold_17;
    LCD_SetBackColor(SEPIA_BG);
    LCD_DisplayStringLine_As_Left(180,320,43, "SEPIA INFO");

    redrawScreen(0, 48,320, 70,SEPIA_SELECT);
    LCD_SetTextColor(Black) ;
    LCD_SetBackColor(SEPIA_SELECT);

    LCD_DisplayStringLine_As_Left(10,320,68, "James Smith");
    FontSet = myriad_bold_15;
    LCD_DisplayStringLine_As_Left(150,320,68, "DAN MEMBER 230049");


    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_BG);

    FontSet = myriad_bold_15;
    LCD_DisplayStringLine_As_Left(100,320,100, "MODEL:");
    LCD_DisplayStringLine_As_Left(100,320,120, "SN:");
    LCD_DisplayStringLine_As_Left(100,320,140, "FIRMWARE:");
    LCD_DisplayStringLine_As_Left(100,320,160, "LASTCAL:");
    LCD_DisplayStringLine_As_Left(100,320,180, "BT DEVICE NAME:");


    LCD_DisplayStringLine_As_Left(235,320,100, "SEPIA");
    LCD_DisplayStringLine_As_Left(235,320,120, "1234567");
    LCD_DisplayStringLine_As_Left(235,320,140, "1A");
    LCD_DisplayStringLine_As_Left(235,320,160, "11-07-2015");
    LCD_DisplayStringLine_As_Left(235,320,180, "AB233445");




}


u8  buf0[20], buf1[20], buf2[20], buf3[20], buf4[20], buf5[20], buf6[20], buf7[20];
void DisplayText_Left(u8 index_sel, u8 index_unsel, u8 whatdisplay)
{
//prepare data here, input num: gas, time,date....
//after that prepare  8 buff data for 8 line
// base on select, unselect to draw fonts, BG
    //u8 * buf0, buf1, buf2, buf3, buf4, buf5, buf6, buf7;


    switch(whatdisplay)
    {
    case GAS:
        stringcopy(buf0,  "GAS1 AIR", 15);
        stringcopy(buf1,  "GAS2 32%      1.40", 20);
        stringcopy(buf2, "GAS3 OFF", 15);
        stringcopy(buf3, "GAS4 OFF", 15);
        stringcopy(buf4, "FO2 50% DEFAULT", 15);
        break;

    case TMT:

        stringcopy(buf0,  "TMT 1", 15);
        stringcopy(buf1,  "TMT 2", 15);
        stringcopy(buf2, "TMT 3", 15);
        stringcopy(buf3, "TMT 4", 15);
        stringcopy(buf4, "\0", 15);

        break;

    case DATE:

        stringcopy(buf0,  "DATE FORMAT", 15);
        stringcopy(buf1,  "TIME FORMAT", 15);
        stringcopy(buf2, "SET DATE", 15);
        stringcopy(buf3, "SET TIME", 15);
        stringcopy(buf4, "\0", 15);
        break;

    case BRIGHTNESS:

        stringcopy(buf0,  "ADJUST BRIGHTNESS", 20);
        stringcopy(buf1,  "AUTO DIM", 15);
        stringcopy(buf2, "\0", 15);
        stringcopy(buf3, "\0", 15);
        stringcopy(buf4, "\0", 15);

        break;


    }



    Select_unselect_Left(index_sel, index_unsel);
    //need write text like that



    FontSet = myriad_bold_15;
    LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_BG);

    switch(index_unsel)
    {
    case 0:
        LCD_DisplayStringLine_As_Left(5,155,65+21*0, buf0);
        break;

    case 1:
        LCD_DisplayStringLine_As_Left(5,155,65+21*1, buf1);
        break;

    case 2:
        LCD_DisplayStringLine_As_Left(5,155,65+21*2, buf2);
        break;

    case 3:
        LCD_DisplayStringLine_As_Left(5,155,65+21*3, buf3);
        break;

    case 4:
        LCD_DisplayStringLine_As_Left(5,155,65+21*4, buf4);
        break;

    case 5:

        break;

    case 6:

        break;

    case 7:

        break;

    case 8: //all
        LCD_DisplayStringLine_As_Left(5,155,65+21*0, buf0);
        LCD_DisplayStringLine_As_Left(5,155,65+21*1, buf1);
        LCD_DisplayStringLine_As_Left(5,155,65+21*2, buf2);
        LCD_DisplayStringLine_As_Left(5,155,65+21*3, buf3);
        LCD_DisplayStringLine_As_Left(5,155,65+21*4, buf4);

        break;

    default:
        break;

    }


    LCD_SetTextColor(Black) ;
    LCD_SetBackColor(White);

    switch(index_sel)
    {
    case 0:
        LCD_DisplayStringLine_As_Left(5,155,65+21*0, buf0);
        break;

    case 1:
        LCD_DisplayStringLine_As_Left(5,155,65+21*1, buf1);
        break;

    case 2:
        LCD_DisplayStringLine_As_Left(5,155,65+21*2, buf2);
        break;

    case 3:
        LCD_DisplayStringLine_As_Left(5,155,65+21*3, buf3);
        break;

    case 4:
        LCD_DisplayStringLine_As_Left(5,155,65+21*4, buf4);
        break;

    case 5:

        break;

    case 6:

        break;

    case 7:

        break;

    default:
        break;

    }


}

void DisplayText_Right_GAS(u8 Gas_index, u8 flat)
{
    FontSet = myriad_bold_17;

    if(flat ==0)//selsect on left
    {

        switch(Gas_index)
        {
        case GAS1:

            break;

        case GAS2:
            LCD_SetTextColor(White) ;
            LCD_SetBackColor(SEPIA_BG);
            LCD_DisplayStringLine_Center(170,315,100, "  To set OFF,   or set FO2 for AIR or Nitrox then PO2 Alarm.");
            break;

        case GAS3:
            LCD_SetTextColor(Red) ;
            LCD_SetBackColor(SEPIA_BG);
            LCD_DisplayStringLine_Center(190,290,110, "You cannot set GAS 3 when GAS 2 is set OFF");
            break;


        case FO2_50:
            LCD_SetTextColor(White) ;
            LCD_SetBackColor(SEPIA_BG);
            LCD_DisplayStringLine_Center(170,300,140, "ON will auto set FO2 to 50% after dives, which requires FO2 to be set for a new dive");

            FontSet = myriad_bold_38;
            LCD_DisplayStringLine_Center(170,300,80, "OFF");

            break;

        }
    }
    else////selsect on right
    {
        switch(Gas_index)
        {
        case GAS1:

            break;

        case GAS2:

            break;

        case GAS3:

            break;


        case FO2_50:
            LCD_SetTextColor(White) ;
            LCD_SetBackColor(SEPIA_GRAY);
            LCD_DisplayStringLine_As_Left(225,256,60+23*0, "ON");

            LCD_SetTextColor(Black) ;
            LCD_SetBackColor(SEPIA_SELECT);
            LCD_DisplayStringLine_As_Left(225,256,60+23*1, "OFF");

            break;

        }


    }

}



void DisplayText_Right_TMT(u8 TMT_index, u8 flat)
{
    FontSet = myriad_bold_14;

    if(flat ==0)//selsect on left
    {

        switch(TMT_index)
        {
        case TMT1:

            break;

        case TMT2:
            LCD_SetTextColor(White) ;
            LCD_SetBackColor(SEPIA_BG);
            LCD_DisplayStringLine_Center(192,290,90, "To set the TMT ON or OFF, set serial codes for connection.");
            break;

        case TMT3:

            break;

        case TMT4:

            break;

        }
    }


    else////selsect on right
    {
        switch(TMT_index)
        {
        case TMT1:

            break;

        case TMT2:
            if(set_tmt_flat == 0) {
                LCD_SetTextColor(Black) ;
                LCD_SetBackColor(SEPIA_SELECT);
                LCD_DisplayStringLine_As_Left(170,256,60+23*0, "SET");
                LCD_DisplayStringLine_As_Right(310,60+23*0, "ON");

                LCD_SetTextColor(White) ;
                LCD_SetBackColor(SEPIA_GRAY);
                LCD_DisplayStringLine_Center(170,320,60+23*1, "SET SERIAL");
            }
            else if(set_tmt_flat ==1) {
                LCD_SetTextColor(White) ;
                LCD_SetBackColor(SEPIA_GRAY);
                LCD_DisplayStringLine_As_Left(170,256,60+23*0, "SET");
                LCD_DisplayStringLine_As_Right(310,60+23*0, "ON");
                LCD_SetTextColor(Black) ;
                LCD_SetBackColor(SEPIA_SELECT);
                LCD_DisplayStringLine_Center(170,320,60+23*1, "SET SERIAL");
            }

            break;

        case TMT3:

            break;


        case TMT4:
            //LCD_SetTextColor(White) ;
            // LCD_SetBackColor(SEPIA_GRAY);
            // LCD_DisplayStringLine_As_Left(225,256,60+23*0, "ON");

            //LCD_SetTextColor(Black) ;
            // LCD_SetBackColor(SEPIA_SELECT);
            // LCD_DisplayStringLine_As_Left(225,256,60+23*1, "OFF");

            break;

        }
    }

}


void DisplayText_Right_Date(u8 index, u8 flat)
{
    FontSet = myriad_bold_38;

    if(flat ==0)//selsect on left
    {
        LCD_SetTextColor(White) ;
        LCD_SetBackColor(SEPIA_BG);
        switch(index)
        {
        case Date_format:
            LCD_DisplayStringLine_Center(170,320,90, "M/D/Y");
            break;

        case Time_format:
            LCD_DisplayStringLine_Center(170,320,90, "12h");
            break;

        case Set_Date:
            FontSet = myriad_bold_30;
            LCD_DisplayStringLine_Center(155,320,100, "10/31/2014");
            break;

        case Set_time:
            ///FontSet = myriad_bold_30;
            LCD_DisplayStringLine_Center(155,320,90, "10:45");
            break;
        }
    }
    else////selsect on right
    {
        switch(index)
        {


        case Date_format:
            FontSet = myriad_bold_14;
            LCD_SetTextColor(White) ;
            LCD_SetBackColor(SEPIA_GRAY);
            LCD_DisplayStringLine_Center(155,320,60+23*0, "M/D/Y");

            LCD_SetTextColor(Black) ;
            LCD_SetBackColor(SEPIA_SELECT);
            LCD_DisplayStringLine_Center(155,320,60+23*1, "D/M/Y");
            break;

        case Time_format:
            FontSet = myriad_bold_14;
            LCD_SetTextColor(White) ;
            LCD_SetBackColor(SEPIA_GRAY);
            LCD_DisplayStringLine_Center(155,320,60+23*0, "12h");

            LCD_SetTextColor(Black) ;
            LCD_SetBackColor(SEPIA_SELECT);
            LCD_DisplayStringLine_Center(155,320,60+23*1, "24h");
            break;

        case Set_Date:
            FontSet = myriad_bold_14;

            LCD_SetTextColor(Black) ;
            LCD_SetBackColor(SEPIA_SELECT);
            LCD_DisplayStringLine_As_Left(170,256,60+23*0, "YEAR");
            LCD_DisplayStringLine_As_Right(310,60+23*0, "2014");

            LCD_SetTextColor(White) ;
            LCD_SetBackColor(SEPIA_GRAY);
            LCD_DisplayStringLine_As_Left(170,256,60+23*1, "MONTH");
            LCD_DisplayStringLine_As_Right(310,60+23*1, "10");

            LCD_DisplayStringLine_As_Left(170,256,60+23*2, "DAY");
            LCD_DisplayStringLine_As_Right(310,60+23*2, "31");

            break;

        case Set_time:
            FontSet = myriad_bold_14;

            LCD_SetTextColor(Black) ;
            LCD_SetBackColor(SEPIA_SELECT);
            LCD_DisplayStringLine_As_Left(170,256,60+23*0, "HOUR");
            LCD_DisplayStringLine_As_Right(310,60+23*0, "22");

            LCD_SetTextColor(White) ;
            LCD_SetBackColor(SEPIA_GRAY);
            LCD_DisplayStringLine_As_Left(170,256,60+23*1, "MUNITE");
            LCD_DisplayStringLine_As_Right(310,60+23*1, "45");

            //#ifdef _24h
            //LCD_SetTextColor(0x528A);
            //LCD_SetBackColor(Black);
            // #endif
            LCD_SetTextColor(0x528A) ;
            // LCD_SetBackColor(SEPIA_SELECT);
            LCD_DisplayStringLine_As_Left(170,256,60+23*2, "AM/PM");
            LCD_DisplayStringLine_As_Right(310,60+23*2, "PM");

            break;



        }


    }

}


void Select_unselect_TMTnum(u8 index_sel, u8 index_unsel)
{

    //redrawScreen(170, 153,191 , 173 ,SEPIA_SELECT);
    //redrawScreen(192, 153,213 , 173 ,SEPIA_SELECT);
    //redrawScreen(214, 153,235 , 173 ,SEPIA_SELECT);
    //redrawScreen(236, 153,256 , 173 ,SEPIA_SELECT);
    //redrawScreen(257, 153,278 , 173 ,SEPIA_SELECT);
    //redrawScreen(279, 153,300 , 173 ,SEPIA_SELECT);


    FontSet = myriad_bold_19;

    //LCD_SetTextColor(White) ;
    LCD_SetBackColor(SEPIA_BG);
    switch(index_unsel)
    {
    case 1:
        redrawScreen(170, 153,191 , 173 ,SEPIA_BG);
        LCD_SetTextColor(White) ;
        LCD_DisplayStringLine(175,60+23*4, "1");
        break;

    case 2:
        redrawScreen(192, 153,213 , 173 ,SEPIA_BG);
        LCD_SetTextColor(White) ;
        LCD_DisplayStringLine(175+22*1,60+23*4, "2");
        break;

    case 3:
        redrawScreen(214, 153,235 , 173 ,SEPIA_BG);
        LCD_SetTextColor(White) ;
        LCD_DisplayStringLine(175+22*2,60+23*4, "3");
        break;

    case 4:
        redrawScreen(236, 153,256 , 173 ,SEPIA_BG);
        LCD_SetTextColor(White) ;
        LCD_DisplayStringLine(175+22*3,60+23*4, "4");
        break;

    case 5:
        redrawScreen(257, 153,278 , 173 ,SEPIA_BG);
        LCD_SetTextColor(White) ;
        LCD_DisplayStringLine(175+22*4,60+23*4, "5");
        break;

    case 6:
        redrawScreen(279, 153,300 , 173 ,SEPIA_BG);
        LCD_SetTextColor(White) ;
        LCD_DisplayStringLine(175+22*5,60+23*4, "6");
        break;

    case 7: //all
        LCD_SetTextColor(White) ;
        LCD_DisplayStringLine(175,60+23*4, "1");
        LCD_DisplayStringLine(175+22*1,60+23*4, "2");
        LCD_DisplayStringLine(175+22*2,60+23*4, "3");
        LCD_DisplayStringLine(175+22*3,60+23*4, "4");
        LCD_DisplayStringLine(175+22*4,60+23*4, "5");
        LCD_DisplayStringLine(175+22*5,60+23*4, "6");
        break;


    default:
        break;
    }



    LCD_SetBackColor(SEPIA_SELECT);
    switch(index_sel)
    {
    case 1:
        redrawScreen(170, 153,191 , 173 ,SEPIA_SELECT);
        LCD_SetTextColor(Black) ;
        LCD_DisplayStringLine(175,60+23*4, "1");
        break;

    case 2:
        redrawScreen(192, 153,213 , 173 ,SEPIA_SELECT);
        LCD_SetTextColor(Black) ;
        LCD_DisplayStringLine(175+22*1,60+23*4, "2");
        break;

    case 3:
        redrawScreen(214, 153,235 , 173 ,SEPIA_SELECT);
        LCD_SetTextColor(Black) ;
        LCD_DisplayStringLine(175+22*2,60+23*4, "3");
        break;

    case 4:
        redrawScreen(236, 153,256 , 173 ,SEPIA_SELECT);
        LCD_SetTextColor(Black) ;
        LCD_DisplayStringLine(175+22*3,60+23*4, "4");
        break;

    case 5:
        redrawScreen(257, 153,278 , 173 ,SEPIA_SELECT);
        LCD_SetTextColor(Black) ;
        LCD_DisplayStringLine(175+22*4,60+23*4, "5");
        break;

    case 6:
        redrawScreen(279, 153,300 , 173 ,SEPIA_SELECT);
        LCD_SetTextColor(Black) ;
        LCD_DisplayStringLine(175+22*5,60+23*4, "6");
        break;

    default:
        break;
    }

}


void dispay_brightness(u8 percent)
{

    redrawScreen(170, 135,300 , 210 ,SEPIA_SELECT);

}







u8 stringcopy(u8 *dest, u8 * src, u16 lengh)
{
    u8 i = 0;
    for(i =0; i < lengh; i++) {
        if(dest && src) {
            *dest = *src;
            dest ++;
            src ++;

        } else
            goto exit;
    }
exit:

    return i;
}



void Delay(__IO uint32_t num)
{
    __IO uint32_t index = 0;

    /* default system clock is 24MHz */
    for(index = (24000 * num); index != 0; index--)
    {
    }
}


void DisplayPercentTLBG(uint16_t Color, uint8_t percent)
{
    uint16_t pixel = 0;
    //uint8_t per_buf[3];

    //writeBMP_nTimes((uint16_t const *)&BMP_Sepia_TL, 188,19,0,27,1);
    writeBMP_nTimes((uint16_t const *)&BMP_TL_1, 188,19,0,27,1);

    pixel = percent*1.27;
    /*100% =130  pixels, x% = x*1.3 pixel */
    LCD_SetBackColor(Color);
    LCD_SetTextColor(Color);

    redrawScreen(5, 74,14, 201,SEPIA_BG);

    if(percent>=2)/*display at least 2 %*/
    {
        redrawScreen(5, 200 - pixel  ,14, 201,Green);  /*HOME-color*/
    }


    LCD_SetTextColor(White);

    LCD_DrawLine(6,106,8,LCD_DIR_HORIZONTAL);

    LCD_DrawLine(6,137,8,LCD_DIR_HORIZONTAL);
    LCD_DrawLine(6,138,8,LCD_DIR_HORIZONTAL);

    LCD_DrawLine(6,168,8,LCD_DIR_HORIZONTAL);

    LCD_DrawLine(6,199,8,LCD_DIR_HORIZONTAL);
    LCD_DrawLine(6,200,8,LCD_DIR_HORIZONTAL);


    if(percent<100) {
        FontSet = myriad_bold_12;
    }
    else {
        FontSet = myriad_bold_9;
    }
    LCD_SetTextColor(Black) ;
    LCD_SetBackColor(SEPIA_TOP);

    pre_percent(TL_buf, percent);
    LCD_DisplayStringLine_Center(0,18,70, TL_buf);

    FontSet = myriad_bold_12;
    //LCD_DisplayStringLine_Center(0,20,55, "%");


}


void DisplayPercentARBG(uint16_t Color, uint8_t percent)
{
    uint16_t pixel = 0;

    //writeBMP_nTimes((uint16_t const *)&BMP_AR, 186,20,300,28,1);
    writeBMP_nTimes((uint16_t const *)&BMP_AR1, 188,20,300,28,1);
    pixel = percent*1.27;
    /*100% =130  pixels, x% = x*1.3 pixel */
    LCD_SetBackColor(Color);
    LCD_SetTextColor(Color);

    redrawScreen(306, 74,314, 201,SEPIA_BG); //SEPIA_BG

    if(percent>=2)/*display at least 2 %*/
    {
        redrawScreen(306, 200 - pixel  ,314, 201,Green);
    }


    LCD_SetTextColor(White);

    LCD_DrawLine(306,106,8,LCD_DIR_HORIZONTAL);

    LCD_DrawLine(306,137,8,LCD_DIR_HORIZONTAL);
    LCD_DrawLine(306,138,8,LCD_DIR_HORIZONTAL);

    LCD_DrawLine(306,168,8,LCD_DIR_HORIZONTAL);

    LCD_DrawLine(306,199,8,LCD_DIR_HORIZONTAL);
    LCD_DrawLine(306,200,8,LCD_DIR_HORIZONTAL);



    if(percent<100) {
        FontSet = myriad_bold_12;
    }
    else {
        FontSet = myriad_bold_9;
    }
    LCD_SetTextColor(Black) ;
    LCD_SetBackColor(White);

    pre_percent(AR_buf,percent);
    LCD_DisplayStringLine_Center(300,320,70, AR_buf);

    FontSet = myriad_bold_12;
    //LCD_DisplayStringLine_Center(300,320,55, "%");

}

void Select_NavMenu(u8 icon)
{
    switch(icon) {
    case 0x10:
        writeBMP_nTimes((uint16_t const *)&BMP_SetID_Sel, 57,57,15,45,1);
        break;

    case 0x20:
        writeBMP_nTimes((uint16_t const *)&BMP_Chanel_Sel, 57,57,130,45,1);
        break;

    case 0x30:
        writeBMP_nTimes((uint16_t const *)&BMP_SetSMS_Sel, 57,57,245,45,1);
        break;

    case 0x40:
        writeBMP_nTimes((uint16_t const *)&BMP_NavMode_Sel, 57,57,15,103,1);
        break;

    case 0x50:
        writeBMP_nTimes((uint16_t const *)&BMP_Paring_Sel, 57,57,130,103,1);
        break;

    case 0x60:
        writeBMP_nTimes((uint16_t const *)&BMP_Partner_Sel, 57,57,245,103,1);
        break;
    }
}

void UnSelect_NavMenu(u8 icon)
{
    switch(icon) {
    case 0x10:
        writeBMP_nTimes((uint16_t const *)&BMP_SetID, 57,57,15,45,1);
        break;

    case 0x20:
        writeBMP_nTimes((uint16_t const *)&BMP_Chanel, 57,57,130,45,1);
        break;

    case 0x30:
        writeBMP_nTimes((uint16_t const *)&BMP_SetSMS, 57,57,245,45,1);
        break;

    case 0x40:
        writeBMP_nTimes((uint16_t const *)&BMP_NavMode, 57,57,15,103,1);
        break;

    case 0x50:
        writeBMP_nTimes((uint16_t const *)&BMP_Paring, 57,57,130,103,1);
        break;

    case 0x60:
        writeBMP_nTimes((uint16_t const *)&BMP_Partner, 57,57,245,103,1);
        break;
    }
}

void Select_HomeMenu(u8 icon)
{
    switch(icon) {
    case HMS_HistorySelect:
        writeBMP_nTimes((uint16_t const *)&BMP_History_Sel, 60,60,15,30,1);
        break;

    case HMS_OpModeSelect:
        writeBMP_nTimes((uint16_t const *)&BMP_OPMode_Sel, 60,60,130,30,1);
        break;

    case HMS_SettingSelect:
        writeBMP_nTimes((uint16_t const *)&BMP_Setting_Sel, 60,60,245,30,1);
        break;

    case HMS_NavigationSelect:
        writeBMP_nTimes((uint16_t const *)&BMP_Navigation_Sel, 60,60,15,90,1);
        break;

    case HMS_GoDiveSelect:
        writeBMP_nTimes((uint16_t const *)&BMP_GoDive_Sel, 60,60,128,90,1);
        break;

    case HMS_LogSelect:
        writeBMP_nTimes((uint16_t const *)&BMP_Log_Sel, 60,60,245,90,1);
        break;
    case HMS_MyInfoSelect:
        writeBMP_nTimes((uint16_t const *)&BMP_MyInfo_Sel, 60,60,15,150,1);
        break;
    case HMS_SepiaInfoSelect:
        writeBMP_nTimes((uint16_t const *)&BMP_SepiaInfo_Sel, 60,60,130,150,1);
        break;
    case HMS_TMTStatusSelect:
        writeBMP_nTimes((uint16_t const *)&BMP_TMTStatus_Sel, 60,60,245,150,1);
        break;

    }
}


void UnSelect_HomeMenu(u8 icon) {
    switch(icon) {
    case HMS_HistorySelect:
        writeBMP_nTimes((uint16_t const *)&BMP_History, 60,60,15,30,1);
        break;

    case HMS_OpModeSelect:
        writeBMP_nTimes((uint16_t const *)&BMP_OPMode, 60,60,130,30,1);
        break;

    case HMS_SettingSelect:
        writeBMP_nTimes((uint16_t const *)&BMP_Setting, 60,60,245,30,1);
        break;

    case HMS_NavigationSelect:
        writeBMP_nTimes((uint16_t const *)&BMP_Navigation, 60,60,15,90,1);
        break;

    case HMS_GoDiveSelect:
        writeBMP_nTimes((uint16_t const *)&BMP_GoDive, 60,60,128,90,1);
        break;

    case HMS_LogSelect:
        writeBMP_nTimes((uint16_t const *)&BMP_Log, 60,60,245,90,1);
        break;
    case HMS_MyInfoSelect:
        writeBMP_nTimes((uint16_t const *)&BMP_MyInfo, 60,60,15,150,1);
        break;
    case HMS_SepiaInfoSelect:
        writeBMP_nTimes((uint16_t const *)&BMP_SepiaInfo, 60,60,130,150,1);
        break;
    case HMS_TMTStatusSelect:
        writeBMP_nTimes((uint16_t const *)&BMP_TMTStatus, 60,60,245,150,1);
        break;
    }
}


void Select_SonarMenu(u8 Sel_line)
{

    FontSet = myriad_bold_14;
    redrawScreen(155, 45,297, 210,SEPIA_BG);

    switch(Sel_line) {
    case 0x10:
        redrawScreen(21, 30+22*0,151, 30+22*1,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50, "BRIGTHNESS");

        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        FontSet = myriad_bold_38;
        LCD_DisplayStringLine_Center(155,300,100, "60 %");

        FontSet = myriad_bold_14;
        LCD_DisplayStringLine_Center(155,300,130, "To adjust the % of full illumination.  ");//SO11
        break;

    case 0x20:
        redrawScreen(18, 30+22*1,151, 30+22*2,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*1, "SEND SMS");

        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        //LCD_DisplayStringLine_Center(175,290,130, "Select an SMS and send to partners.  ");
        FontSet = myriad_bold_15;
        LCD_DisplayStringLine_Center(172,280,85, "Select an SMS and send to partners  ");
        break;

    case 0x30:
        redrawScreen(18, 30+22*2,151, 30+22*3,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*2, "PARTNERS");

        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_Center(175,290,70, "Display depths and tank presures of selected partners. Select/deselect partners.  ");
        break;

    case 0x40:
        redrawScreen(21, 30+22*3,151, 30+22*4,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*3, "SMS LIST");


        writeBMP_nTimes((uint16_t const *)&BMP_up_down, 52,27,165,120,1);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_Center(155,300,80, "Review the SMS list. ");

        LCD_DisplayStringLine_As_Left(193,320,138, "to scroll down");
        LCD_DisplayStringLine_As_Left(193,320,172, "to scroll up");



        break;

    case 0x50:
        redrawScreen(21, 30+22*4,151, 30+22*5,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*4, "NAV MODE");

        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_Center(175,270,90, "Set the RX and TX ON, STAND BY or OFF. ");

        break;

    case Sel_line6:
        redrawScreen(21, 30+22*5,151, 30+22*6,LCD_COLOR_GREEN);
        break;

    case Sel_line7:
        redrawScreen(21, 30+22*6,151, 30+22*7,LCD_COLOR_GREEN);
        break;

    case Sel_line8:
        redrawScreen(21, 30+22*7,151, 30+22*8,LCD_COLOR_GREEN);
        break;

    }

}


void UnSelect_SonarMenu(u8 Sel_line)
{

    FontSet = myriad_bold_14;

    switch(Sel_line) {
    case 0x10:
        redrawScreen(21, 30+22*0,151, 30+22*1,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(25,320,50, "BRIGTHNESS");

        break;

    case 0x20:
        redrawScreen(21, 30+22*1,151, 30+22*2,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(25,320,50+22*1, "SEND SMS");

        break;

    case 0x30:
        redrawScreen(21, 30+22*2,151, 30+22*3,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(25,320,50+22*2, "PARTNERS");
        break;

    case 0x40:
        redrawScreen(21, 30+22*3,151, 30+22*4,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(25,320,50+22*3, "SMS LIST");
        break;

    case 0x50:
        redrawScreen(21, 30+22*4,151, 30+22*5,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(25,320,50+22*4, "NAV MODE");
        break;

    case 0x60:
        redrawScreen(21, 30+22*5,151, 30+22*6,SEPIA_BG);
        break;

    case 0x70:
        redrawScreen(21, 30+22*6,151, 30+22*7,SEPIA_BG);
        break;

    case 0x80:
        redrawScreen(21, 30+22*7,151, 30+22*8,SEPIA_BG);
        break;

    }

}



void Select_DiveMainMenu(u8 Sel_line)
{

    FontSet = myriad_bold_14;
    redrawScreen(155, 45,297, 210,SEPIA_BG);

    switch(Sel_line) {
    case Sel_line1:
        redrawScreen(21, 30+22*0,151, 30+22*1,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50, "BRIGTHNESS");

        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        FontSet = myriad_bold_38;
        LCD_DisplayStringLine_Center(155,300,100, "60 %");

        FontSet = myriad_bold_14;
        LCD_DisplayStringLine_Center(155,300,130, "To adjust the % of full illumination.  ");
        break;

    case Sel_line2:
        redrawScreen(21, 30+22*1,151, 30+22*2,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*1, "MORE DATA");
        break;

    case Sel_line3:
        redrawScreen(21, 30+22*2,151, 30+22*3,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*2, "PROFILE-TISSUE");

        //LCD_SetTextColor(White);
        //LCD_SetBackColor(SEPIA_BG);
        // LCD_DisplayStringLine_Center(175,290,70, "Display depths and tank presures of selected partners. Select/deselect partners.  ");
        break;

    case Sel_line4:
        redrawScreen(21, 30+22*3,151, 30+22*4,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*3, "DS PREVIEW");
        break;

    case Sel_line5:
        redrawScreen(21, 30+22*4,151, 30+22*5,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*4, "GAS SWITCH");
        break;

    case Sel_line6:
        redrawScreen(21, 30+22*5,151, 30+22*6,LCD_COLOR_GREEN);

        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*5, "RE-SYNC");

        //writeBMP_nTimes((uint16_t const *)&BMP_ReSync, 70,61,200,41,1);

        writeBMP_nTimes((uint16_t const *)&BMP_ReSync_Complete, 114,109,180,41,1);
        //  writeBMP_nTimes((uint16_t const *)&BMP_ReSync_Fail, 110,74,185,41,1);

        LCD_SetTextColor(White) ;
        LCD_SetBackColor(SEPIA_BG);
        FontSet = myriad_bold_15;
        LCD_DisplayStringLine_As_Left(197,320,185, "ID:");
        LCD_DisplayStringLine_As_Left(191,320,205, "Channel:");

        FontSet = myriad_bold_17;
        stringcopy(buf0,  "THINH", 5);
        //LCD_DisplayStringLine_As_Left(224,320,185, "THINH");
        LCD_DisplayStringLine_As_Left(224,320,185, buf0);
        //LCD_DisplayStringLine_As_Left(263,320,205, "2");
        stringcopy(buf1,  "3", 1);
        LCD_DisplayStringLine_As_Left(263,320,205, buf1);

        break;

    case Sel_line7:
        redrawScreen(21, 30+22*6,151, 30+22*7,LCD_COLOR_GREEN);
        break;

    case Sel_line8:
        redrawScreen(21, 30+22*7,151, 30+22*8,LCD_COLOR_GREEN);
        break;

    }

}
void Select_SonarNavMode(u8 Sel_line)
{
    u16 line = 0;
    FontSet = myriad_bold_13;
    redrawScreen(155, 35,297, 210,SEPIA_BG);

    switch(Sel_line) {
    case 0x00:
        redrawScreen(19, 30+22*0,151, 30+22*1,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(22,320,50, "FULL");

        FontSet = myriad_bold_14;
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        //LCD_DisplayStringLine_Center(159,300,65, "RX and TX ON. SMS and locator features will be available during dive.You can switch to other nav modes when desired.   ");

        line = 55;
        LCD_DisplayStringLine_Center(159,300,line, "RX and TX ON.");
        line += 20;
        LCD_DisplayStringLine_Center(159,300,line, "SMS and locator");
        line += 20;
        LCD_DisplayStringLine_Center(159,300,line, "features will be");
        line += 20;
        LCD_DisplayStringLine_Center(159,300,line, "available.");
        line += 20;
        LCD_DisplayStringLine_Center(159,300,line, "You can switch to");
        line += 20;
        LCD_DisplayStringLine_Center(159,300,line, "other nav modes");
        line += 20;
        LCD_DisplayStringLine_Center(159,300,line, "when desired.");


        writeBMP_nTimes((uint16_t const *)&BMP_Select, 16,23,180,191,1);
        LCD_DisplayStringLine_Center(175,320,205, "to confirm");

        break;

    case 0x01:
        redrawScreen(21, 30+22*1,151, 30+22*2,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(22,320,50+22*1, "RX ON,TX STAND BY");

        FontSet = myriad_bold_14;
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        //LCD_DisplayStringLine_Center(159,300,35, "You can locate other partners and recieve SMS. Other partners cannot locate you and you cannot send SMS. You can switch to other nac modes when desired.");
        line = 50;
        LCD_DisplayStringLine_Center(155,300,line, "You can locate other");
        line += 17;
        LCD_DisplayStringLine_Center(155,300,line, "partners and recieve");
        line += 17;
        LCD_DisplayStringLine_Center(159,300,line, "SMS. Other partners");
        line += 17;
        LCD_DisplayStringLine_Center(159,300,line, "cannot locate you");
        line += 17;
        LCD_DisplayStringLine_Center(159,300,line, "and you cannot");
        line += 17;
        LCD_DisplayStringLine_Center(159,300,line, "send SMS.");
        line += 17;
        LCD_DisplayStringLine_Center(159,300,line, "You can switch to");
        line += 17;
        LCD_DisplayStringLine_Center(159,300,line, "other nav modes");
        line += 17;
        LCD_DisplayStringLine_Center(159,300,line, "when desired.");

        writeBMP_nTimes((uint16_t const *)&BMP_Select, 16,23,180,191,1);
        LCD_DisplayStringLine_Center(175,320,205, "to confirm");


        break;

    case 0x02:
        redrawScreen(21, 30+22*2,151, 30+22*3,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(22,320,50+22*2, "RX TX STAND BY");
        FontSet = myriad_bold_14;
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        //LCD_DisplayStringLine_Center(159,300,60, "SMS and locator features will be available. You can switch to other nac modes when desired.");
        line = 75;
        LCD_DisplayStringLine_Center(159,300,line, "SMS and locator");
        line += 20;
        LCD_DisplayStringLine_Center(159,300,line, "features will be");
        line += 20;
        LCD_DisplayStringLine_Center(159,300,line, "available.");
        line += 20;
        LCD_DisplayStringLine_Center(159,300,line, "You can switch to");
        line += 20;
        LCD_DisplayStringLine_Center(159,300,line, "other nav modes");
        line += 20;
        LCD_DisplayStringLine_Center(159,300,line, "when desired.");

        writeBMP_nTimes((uint16_t const *)&BMP_Select, 16,23,180,191,1);
        LCD_DisplayStringLine_Center(175,320,205, "to confirm");

        break;

    case 0x03:
        redrawScreen(21, 30+22*3,151, 30+22*4,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(22,320,50+22*3, "OFF");
        FontSet = myriad_bold_14;
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        //LCD_DisplayStringLine_Center(159,300,35, "SMS and locator features will be unavailable. You can use the compass.");
        line = 50;
        LCD_DisplayStringLine_Center(159,300,line, "SMS and locator");
        line += 17;
        LCD_DisplayStringLine_Center(159,300,line, "features will be");
        line += 17;
        LCD_DisplayStringLine_Center(159,300,line, "unavailable.");
        line += 17;
        LCD_DisplayStringLine_Center(159,300,line, "You can use the");
        line += 17;
        LCD_DisplayStringLine_Center(159,300,line, "compass.");
        line += 17;
        LCD_SetTextColor(Red);
        LCD_DisplayStringLine_Center(159,300,line, "Attention!");
        line += 17;
        LCD_DisplayStringLine_Center(159,300,line, "Paring will be");
        line += 17;
        LCD_DisplayStringLine_Center(159,300,line, "cancelled.You have");
        line += 17;
        LCD_DisplayStringLine_Center(159,300,line, " to perform re-sync.");
        writeBMP_nTimes((uint16_t const *)&BMP_Select, 16,23,180,191,1);
        LCD_SetTextColor(White);
        LCD_DisplayStringLine_Center(175,320,205, "to confirm");

        break;
    }

}

void UnSelect_SonarNavMode(u8 Sel_line)
{

    FontSet = myriad_bold_13;
    switch(Sel_line) {
    case 0x00:
        redrawScreen(21, 30+22*0,151, 30+22*1,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(22,320,50, "FULL");
        break;

    case 0x01:
        redrawScreen(21, 30+22*1,151, 30+22*2,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(22,320,50+22*1, "RX ON,TX STAND BY");
        break;

    case 0x02:
        redrawScreen(21, 30+22*2,151, 30+22*3,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(22,320,50+22*2, "RX TX STAND BY");

        break;

    case 0x03:
        redrawScreen(21, 30+22*3,151, 30+22*4,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(22,320,50+22*3, "OFF");

        break;
    }

}
void Select_SetNavMode(u8 Sel_line)
{
    u16 line = 0;
    FontSet = myriad_bold_13;
    redrawScreen(155, 45,297, 210,SEPIA_BG);

    switch(Sel_line) {
    case 0x00:
        redrawScreen(0, 44+22*0,151, 44+22*1,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);

        LCD_DisplayStringLine_As_Left(10,155,65+21*0, "FULL");

        FontSet = myriad_bold_14;
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        // LCD_DisplayStringLine_Center(159,320,70, "RX and TX ON. SMS and locator features will be available during dive.You can switch to other nav modes when desired.   ");

        line = 70;
        LCD_DisplayStringLine_Center(159,320,line, "RX and TX ON.");
        line += 17;
        LCD_DisplayStringLine_Center(159,320,line, "SMS and locator");
        line += 17;
        LCD_DisplayStringLine_Center(150,320,line, "features will be available");
        line += 17;
        LCD_DisplayStringLine_Center(159,320,line, "during dive.");
        line += 17;
        LCD_DisplayStringLine_Center(159,320,line, "You can switch to");
        line += 17;
        LCD_DisplayStringLine_Center(159,320,line, "other nav modes");
        line += 17;
        LCD_DisplayStringLine_Center(159,320,line, "when desired.");


        writeBMP_nTimes((uint16_t const *)&BMP_Select, 16,23,180,191,1);
        LCD_DisplayStringLine_Center(175,320,205, "to confirm");

        break;

    case 0x01:
        redrawScreen(0, 44+22*1,151, 44+22*2,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(10,155,65+22*1, "RX ON,TX STAND BY");

        FontSet = myriad_bold_13;
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        //LCD_DisplayStringLine_Center(159,300,35, "You can locate other partners and recieve SMS. Other partners cannot locate you and you cannot send SMS. You can switch to other nac modes when desired.");
        line = 70;
        LCD_DisplayStringLine_Center(150,320,line, "You can locate other");
        line += 17;
        LCD_DisplayStringLine_Center(150,320,line, "partners and recieve SMS");
        line += 17;
        LCD_DisplayStringLine_Center(150,320,line, "during dive.");
        line += 17;
        LCD_DisplayStringLine_Center(150,320,line, "Other partners cannot");
        line += 17;
        LCD_DisplayStringLine_Center(150,320,line, " locate you and you");
        line += 17;
        LCD_DisplayStringLine_Center(150,320,line, " cannot send SMS.");
        line += 17;
        LCD_DisplayStringLine_Center(150,320,line, "You can switch to other");
        line += 17;
        LCD_DisplayStringLine_Center(150,320,line, " nav modes when desired.");

        writeBMP_nTimes((uint16_t const *)&BMP_Select, 16,23,180,191,1);
        LCD_DisplayStringLine_Center(175,320,205, "to confirm");


        break;

    case 0x02:
        redrawScreen(0, 44+22*2,151, 44+22*3,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(10,155,65+22*2, "RX TX STAND BY");
        FontSet = myriad_bold_13;
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        //LCD_DisplayStringLine_Center(159,300,60, "SMS and locator features will be available. You can switch to other nac modes when desired.");
        line = 75;
        LCD_DisplayStringLine_Center(159,320,line, "SMS and locator");
        line += 20;
        LCD_DisplayStringLine_Center(159,320,line, "features will be");
        line += 20;
        LCD_DisplayStringLine_Center(159,320,line, "available.");
        line += 20;
        LCD_DisplayStringLine_Center(159,320,line, "You can switch to");
        line += 20;
        LCD_DisplayStringLine_Center(159,320,line, "other nav modes");
        line += 20;
        LCD_DisplayStringLine_Center(159,320,line, "when desired.");

        writeBMP_nTimes((uint16_t const *)&BMP_Select, 16,23,180,191,1);
        LCD_DisplayStringLine_Center(175,320,205, "to confirm");

        break;

    case 0x03:
        redrawScreen(0, 44+22*3,151, 44+22*4,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(10,155,65+22*3, "OFF");
        FontSet = myriad_bold_13;
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        //LCD_DisplayStringLine_Center(159,300,35, "SMS and locator features will be unavailable. You can use the compass.");
        line = 70;
        LCD_DisplayStringLine_Center(150,320,line, "SMS and locator features");
        line += 17;
        LCD_DisplayStringLine_Center(150,320,line, "will unavailable");
        line += 17;
        LCD_DisplayStringLine_Center(150,320,line, "You can use the compass");
        line += 17;
        LCD_SetTextColor(Red);
        LCD_DisplayStringLine_Center(150,320,line, "Attention!");
        line += 17;
        LCD_DisplayStringLine_Center(150,320,line, "Paring will be cancelled.");
        line += 17;
        LCD_DisplayStringLine_Center(150,320,line, "You have to perform");
        line += 17;
        LCD_DisplayStringLine_Center(150,320,line, "re-sync or paring again.");
        writeBMP_nTimes((uint16_t const *)&BMP_Select, 16,23,180,191,1);
        LCD_SetTextColor(White);
        LCD_DisplayStringLine_Center(175,320,205, "to confirm");

        break;
    }

    LCD_SetTextColor(0x528A);
    LCD_DrawLine(0, 67 +21*0, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*1, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*2, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*3, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*4, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*5, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*6, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*7, 152, LCD_DIR_HORIZONTAL);

}

void UnSelect_SetNavMode(u8 Sel_line)
{

    FontSet = myriad_bold_13;
    switch(Sel_line) {
    case 0x00:
        redrawScreen(0, 44+22*0,151, 44+22*1,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(10,155,65+21*0, "FULL");
        break;

    case 0x01:
        redrawScreen(0, 44+22*1,151, 44+22*2,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(10,155,65+21*1, "RX ON, TX STAND BY");
        break;

    case 0x02:
        redrawScreen(0, 44+22*2,151, 44+22*3,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(10,155,65+21*2, "RX TX STAND BY");

        break;

    case 0x03:
        redrawScreen(0, 44+22*3,151, 44+22*4,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(10,155,65+21*3, "OFF");

        break;
    }
    LCD_SetTextColor(0x528A);
    LCD_DrawLine(0, 67 +21*0, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*1, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*2, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*3, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*4, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*5, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*6, 152, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(0, 67 +21*7, 152, LCD_DIR_HORIZONTAL);
}

void Select_SMS(u8 Sel_line)
{

    FontSet = myriad_bold_14;
    switch(Sel_line) {
    case 0x01:
        redrawScreen(19, 30+22*0,151, 30+22*1,LCD_COLOR_GREEN);
        LCD_SetTextColor(Red);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50, "1:SOS");
        break;

    case 0x02:
        redrawScreen(19, 30+22*1,151, 30+22*2,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*1, "2:OK");
        break;

    case 0x03:
        redrawScreen(19, 30+22*2,151, 30+22*3,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*2, "3:ARE YOU OK");
        break;

    case 0x04:
        redrawScreen(19, 30+22*3,151, 30+22*4,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*3, "4:YES");
        break;

    case 0x05:
        redrawScreen(19, 30+22*4,151, 30+22*5,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*4, "5:NO");
        break;

    case 0x06:
        redrawScreen(19, 30+22*5,151, 30+22*6,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,52+22*5, "6:LOW BATTERY");
        break;

    case 0x07:
        redrawScreen(19, 30+22*6,151, 30+22*7,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*6, "7:FINISH THE DIVE");
        break;

    case 0x08:
        redrawScreen(19, 30+22*7,151, 30+22*8,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*7, "8:COME HERE");
        break;

    case 0x09:
        redrawScreen(152, 30+22*0,298, 30+22*1,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(165,320,50+22*0, "9:STAY THERE");
        break;
    case 0x0a:
        redrawScreen(152, 30+22*1,298, 30+22*2,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(165,320,50+22*1, "10:ALL COME HERE");
        break;
    case 0x0b:
        redrawScreen(152, 30+22*2,298, 30+22*3,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(165,320,50+22*2, "11:I'M SURFACING");
        break;

    case 0x0c:
        redrawScreen(152, 30+22*3,298, 30+22*4,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(165,320,50+22*3, "12:GO TO SURFACE");
        break;
    case 0x0d:
        redrawScreen(152, 30+22*4,298, 30+22*5,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(165,320,52+22*4, "13:GO TO BOAT");
        break;
    case 0x0e:
        redrawScreen(152, 30+22*5,298, 30+22*6,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(165,320,50+22*5, "14:ASCEND");
        break;


    }

}

void UnSelect_SMS(u8 Sel_line)
{

    FontSet = myriad_bold_13;
    switch(Sel_line) {
    case 0x01:
        redrawScreen(19, 30+22*0,151, 30+22*1,Black);
        LCD_SetTextColor(Red);
        LCD_SetBackColor(Black);
        LCD_DisplayStringLine_As_Left(25,320,50, "1:SOS");
        break;

    case 0x02:
        redrawScreen(19, 30+22*1,151, 30+22*2,Black);
        LCD_SetTextColor(White);
        LCD_SetBackColor(Black);
        LCD_DisplayStringLine_As_Left(25,320,50+22*1, "2:OK");
        break;

    case 0x03:
        redrawScreen(19, 30+22*2,151, 30+22*3,Black);
        LCD_SetTextColor(White);
        LCD_SetBackColor(Black);
        LCD_DisplayStringLine_As_Left(25,320,50+22*2, "3:ARE YOU OK?");
        break;

    case 0x04:
        redrawScreen(19, 30+22*3,151, 30+22*4,Black);
        LCD_SetTextColor(White);
        LCD_SetBackColor(Black);
        LCD_DisplayStringLine_As_Left(25,320,50+22*3, "4:YES");
        break;

    case 0x05:
        redrawScreen(19, 30+22*4,151, 30+22*5,Black);
        LCD_SetTextColor(White);
        LCD_SetBackColor(Black);
        LCD_DisplayStringLine_As_Left(25,320,50+22*4, "5:NO");
        break;

    case 0x06:
        redrawScreen(19, 30+22*5,151, 30+22*6,Black);
        LCD_SetTextColor(White);
        LCD_SetBackColor(Black);
        LCD_DisplayStringLine_As_Left(25,320,52+22*5, "6:LOW BATTERY");
        break;

    case 0x07:
        redrawScreen(19, 30+22*6,151, 30+22*7,Black);
        LCD_SetTextColor(White);
        LCD_SetBackColor(Black);
        LCD_DisplayStringLine_As_Left(25,320,50+22*6, "7:FINISH THE DIVE");
        break;

    case 0x08:
        redrawScreen(19, 30+22*7,151, 30+22*8,Black);
        LCD_SetTextColor(White);
        LCD_SetBackColor(Black);
        LCD_DisplayStringLine_As_Left(25,320,50+22*7, "8:COME HERE");
        break;

    case 0x09:
        redrawScreen(152, 30+22*0,298, 30+22*1,Black);
        LCD_SetTextColor(White);
        LCD_SetBackColor(Black);
        LCD_DisplayStringLine_As_Left(165,320,50+22*0, "9:STAY THERE");
        break;
    case 0x0a:
        redrawScreen(152, 30+22*1,298, 30+22*2,Black);
        LCD_SetTextColor(White);
        LCD_SetBackColor(Black);
        LCD_DisplayStringLine_As_Left(165,320,50+22*1, "10:ALL COME HERE");
        break;
    case 0x0b:
        redrawScreen(152, 30+22*2,298, 30+22*3,Black);
        LCD_SetTextColor(White);
        LCD_SetBackColor(Black);
        LCD_DisplayStringLine_As_Left(165,320,50+22*2, "11:I'M SURFACING");
        break;

    case 0x0c:
        redrawScreen(152, 30+22*3,298, 30+22*4,Black);
        LCD_SetTextColor(White);
        LCD_SetBackColor(Black);
        LCD_DisplayStringLine_As_Left(165,320,50+22*3, "12:GO TO SURFACE");
        break;
    case 0x0d:
        redrawScreen(152, 30+22*4,298, 30+22*5,Black);
        LCD_SetTextColor(White);
        LCD_SetBackColor(Black);
        LCD_DisplayStringLine_As_Left(165,320,52+22*4, "13:GO TO BOAT");
        break;
    case 0x0e:
        redrawScreen(152, 30+22*5,298, 30+22*6,Black);
        LCD_SetTextColor(White);
        LCD_SetBackColor(Black);
        LCD_DisplayStringLine_As_Left(165,320,50+22*5, "14:ASCEND");
        break;


    }

}


void Draw_SonarMain(void)
{
    //LCD_FillScreen(SEPIA_BG);
    redrawScreen(0, 21,320, 220,SEPIA_BG);
    redrawScreen(0, 217,320, 240,SEPIA_TOP);

#if 0 //SMS SOS
    redrawScreen(0, 217,320, 240,Red);
    LCD_SetTextColor(White);
    LCD_SetBackColor(Red);
    LCD_DisplayStringLine_As_Left(81,220,238, "I am surfacing");
    LCD_DisplayStringLine_As_Left(263,320,238, "12:45 P");
    writeBMP_nTimes((uint16_t const *)&BMP_Mail_SOS, 17,21,10,221,1);
#endif

    //writeBMP_nTimes((uint16_t const *)&BMP_Sonar_Top, 20,320,0,0,1);
    writeBMP_nTimes((uint16_t const *)&BMP_Mail, 15,19,10,221,1);
    writeBMP_nTimes((uint16_t const *)&BMP_Sonar_circle, 182,186,65,30,1);

    FontSet = myriad_bold_15;
    LCD_SetTextColor(Black);
    LCD_SetBackColor(SEPIA_TOP);
    LCD_DisplayStringLine_As_Left(81,220,238, "I am surfacing");
    LCD_DisplayStringLine_As_Left(263,320,238, "12:45 P");

    LCD_SetTextColor(SEPIA_GREEN);
    LCD_SetBackColor(Black);
    FontSet = myriad_bold_19;
    LCD_DisplayStringLine_As_Left(5,150,45, "BOA");
    FontSet = myriad_bold_15;
    LCD_DisplayStringLine_As_Left(5,150,60, "DISTANCE");
    FontSet = myriad_bold_19;
    LCD_DisplayStringLine_As_Left(5,150,80, "245 FT");

    FontSet = myriad_bold_19;
    LCD_DisplayStringLine_As_Left(5,150,175, "BOA");
    FontSet = myriad_bold_15;
    LCD_DisplayStringLine_As_Left(5,150,190, "DEPTH");
    FontSet = myriad_bold_19;
    LCD_DisplayStringLine_As_Left(5,150,210, "9 FT");

    FontSet = myriad_bold_30;

    LCD_DisplayStringLine_As_Left(251,320,60, "298");
    FontSet = myriad_bold_19;
    LCD_DisplayStringLine_As_Right(300,80, "FT");

}


void PrepareClock(uint8_t *Clock, uint8_t flat)//will fix the function to get 1 function with no if..else
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
    if(flat)
    {
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

void PrepareMidday(uint8_t midnight_flat)
{
    if(midnight_flat== AM_)
    {
        Midday[0] = 'A';
        //Midday[1] = 'M';
    }
    else
    {
        Midday[0] = 'P';
        //Midday[1] = 'M';
    }
}
void PrepareTemper(void)
{
    float temp = in_buf[9];
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
#if 1
void UpdateHeader(void)
{
    mm = in_buf[10];
    mm = Bcd2ToByte(mm);
    hh = in_buf[11]&0x7F;
    hh = Bcd2ToByte(hh);


    //USRFLG CODE
    hrType = in_buf[8]&0x01;                                //12 or 24
    //AudAlarm= in_buf[8]&0x02;                        //alarm on/off
    MD= in_buf[8]&0x04;                                        //M.D or D.M
    UnitType_= (in_buf[8]&0x08)>>3;                        //Unit
    if((in_buf[11]&0x80) ==0x00) {
        midnight = AM_;
    }
    else {
        midnight = PM_;
    }

    if(_preTEMP !=in_buf[9]) {//TEMP
        _preTEMP=in_buf[9];
        redrawScreenSection(218, 0,250, 20, (uint16_t const *)&BMP_Menu_Top, 21,320,0,0);
        PrepareTemper();
        FontSet = myriad_bold_15;
        LCD_SetTextColor(Black);
        LCD_SetBackColor(White);
        LCD_DisplayStringLine(218,20, _Temper_buf);
    }
    if(_premm != mm ||_prehh != hh ||_premidnight != midnight) {
        redrawScreenSection(0, 0,70, 20, (uint16_t const *)&BMP_Menu_Top, 21,320,0,0);
        /*start time*/
        _premm = mm;
        _prehh = hh;
        _premidnight = midnight;
        DisplayMainClock();
    }

    if((MSG&BIT_7) == BIT_7) {
        redrawScreenSection(32, 0,36, 20, (uint16_t const *)&BMP_Menu_Top, 21,320,0,0);
    }
    else {
        DisplayMainClock();
    }
}

#endif
void UpdateHeader1(void)
{
    mm = 48;
    //mm = Bcd2ToByte(mm);
    //hh = in_buf[11]&0x7F;
    hh = 11;


    //USRFLG CODE
    hrType = 0;                                //12 or 24
    //AudAlarm= in_buf[8]&0x02;                        //alarm on/off
    MD= in_buf[8]&0x04;                                        //M.D or D.M
    UnitType_= 0;                        //Unit

    midnight = AM_;


    in_buf[9] = 68;
    PrepareTemper();
    FontSet = myriad_bold_15;

    LCD_SetTextColor(Black);
    LCD_SetBackColor(White);
    //pre_temper(temper_buf,69);
    LCD_DisplayStringLine(216,18, _Temper_buf);

    LCD_DisplayStringLine(256,19, "72");

    DisplayMainClock();
}

void DisplayMainClock(void) {
    FontSet = myriad_bold_16;
    LCD_SetTextColor(Black);
    LCD_SetBackColor(SEPIA_SELECT);
    PrepareClock(time_buf,1);
    PrepareMidday(midnight);
    //LCD_DisplayStringLine(18,20, time_buf);

    if(!hrType) {
        LCD_DisplayStringLine(32,18, ":");
        LCD_DisplayStringLine_As_Right(31,18,hr_buf);
        LCD_DisplayStringLine_As_Left(37,60,18,min_buf);
        LCD_DisplayStringLine(55,18, Midday);
    }
    else {
        LCD_DisplayStringLine(32,18, ":");
        LCD_DisplayStringLine_As_Right(31,18,hr_buf);
        LCD_DisplayStringLine_As_Left(37,60,18,min_buf);
    }
}


void Select_DiveMenu(u8 Sel_line)
{

    FontSet = myriad_bold_14;
    redrawScreen(155, 45,297, 210,SEPIA_BG);

    switch(Sel_line) {
    case 0x10:
        redrawScreen(21, 30+22*0,151, 30+22*1,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50, "BRIGTHNESS");

        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        FontSet = myriad_bold_38;
        LCD_DisplayStringLine_Center(155,300,100, "60 %");

        FontSet = myriad_bold_14;
        LCD_DisplayStringLine_Center(155,300,130, "To adjust the % of full illumination.  ");//SO11
        break;

    case 0x20:
        redrawScreen(18, 30+22*1,151, 30+22*2,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*1, "MORE DATA");

        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        //LCD_DisplayStringLine_Center(175,290,130, "Select an SMS and send to partners.  ");
        FontSet = myriad_bold_15;
        //LCD_DisplayStringLine_Center(172,280,85, "Select an SMS and send to partners  ");
        break;

    case 0x30:
        redrawScreen(18, 30+22*2,151, 30+22*3,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*2, "PROFILE-TISSUE");

        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        // LCD_DisplayStringLine_Center(175,290,70, "Display depths and tank presures of selected partners. Select/deselect partners.  ");
        break;

    case 0x40:
        redrawScreen(21, 30+22*3,151, 30+22*4,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*3, "DS PREVIEW");

        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        //LCD_DisplayStringLine_Center(175,290,70, "Displays a profile for the dive in progress.  ");

        break;

    case 0x50:
        redrawScreen(21, 30+22*4,151, 30+22*5,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*4, "GAS SWITCH");

        break;

    case 0x60:
        redrawScreen(21, 30+22*5,151, 30+22*6,LCD_COLOR_GREEN);
        LCD_SetTextColor(Black);
        LCD_SetBackColor(LCD_COLOR_GREEN);
        LCD_DisplayStringLine_As_Left(25,320,50+22*5, "RE-SYNC");
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_Center(175,290,80, "Perform re-sync to be able to use Sonar and SMS features.  ");
        break;

    }

}

void UnSelect_DiveMenu(u8 Sel_line)
{

    FontSet = myriad_bold_14;

    switch(Sel_line) {
    case 0x10:
        redrawScreen(21, 30+22*0,151, 30+22*1,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(25,320,50, "BRIGTHNESS");

        break;

    case 0x20:
        redrawScreen(21, 30+22*1,151, 30+22*2,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(25,320,50+22*1, "MORE DATA");

        break;

    case 0x30:
        redrawScreen(21, 30+22*2,151, 30+22*3,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(25,320,50+22*2, "PROFILE-TISSUE");
        break;

    case 0x40:
        redrawScreen(21, 30+22*3,151, 30+22*4,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(25,320,50+22*3, "DS PREVIEW");
        break;

    case 0x50:
        redrawScreen(21, 30+22*4,151, 30+22*5,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(25,320,50+22*4, "GAS SWITCH");
        break;

    case 0x60:
        redrawScreen(21, 30+22*5,151, 30+22*6,SEPIA_BG);
        LCD_SetTextColor(White);
        LCD_SetBackColor(SEPIA_BG);
        LCD_DisplayStringLine_As_Left(25,320,50+22*5, "RE-SYNC");
        break;
    }

}


void Re_Sync(u8 status) {
    redrawScreen(155, 45,297, 210,SEPIA_BG);



    if(status == 0) { //re-syncronising
        writeBMP_nTimes((uint16_t const *)&BMP_ReSync, 70,61,200,41,1);
        LCD_SetTextColor(White) ;
        LCD_SetBackColor(SEPIA_BG);
        FontSet = myriad_bold_15;
        LCD_DisplayStringLine_As_Left(197,320,185, "ID:");
        LCD_DisplayStringLine_As_Left(191,320,205, "Channel:");
        //FontSet = myriad_bold_17;
        //stringcopy(buf0,  "ADE", 3);
        //LCD_DisplayStringLine_As_Left(224,320,185, buf0);
        //stringcopy(buf1,  "3", 1);
        //LCD_DisplayStringLine_As_Left(263,320,205, buf1);


#ifdef USE_SONAR
        Num2Str(GET_OP_CHANNEL()+1, Chanel_Buf, 1);
        memcpy(ID_Sornar, GET_OP_ID(), 3);
        FontSet = myriad_bold_17;
        LCD_DisplayStringLine_As_Left(224,320,185, ID_Sornar);
        LCD_DisplayStringLine_As_Left(263,320,205, Chanel_Buf);
#endif



    }
    else if(status == 1) { //re-syncronising complete
        writeBMP_nTimes((uint16_t const *)&BMP_ReSync_Complete, 114,109,180,41,1);
        LCD_SetTextColor(White) ;
        LCD_SetBackColor(SEPIA_BG);
        FontSet = myriad_bold_15;
        LCD_DisplayStringLine_As_Left(197,320,185, "ID:");
        LCD_DisplayStringLine_As_Left(191,320,205, "Channel:");
        //FontSet = myriad_bold_17;
        //stringcopy(buf0,  "ABC", 3);
        //LCD_DisplayStringLine_As_Left(224,320,185, buf0);
        //stringcopy(buf1,  "3", 1);
        //LCD_DisplayStringLine_As_Left(263,320,205, buf1);
#ifdef USE_SONAR
        Num2Str(GET_OP_CHANNEL()+1, Chanel_Buf, 1);
        memcpy(ID_Sornar, GET_OP_ID(), 3);
        FontSet = myriad_bold_17;
        LCD_DisplayStringLine_As_Left(224,320,185, ID_Sornar);
        LCD_DisplayStringLine_As_Left(263,320,205, Chanel_Buf);
#endif

    }
    else if(status == 2) { //re-syncronising failed
        writeBMP_nTimes((uint16_t const *)&BMP_ReSync_Fail, 110,74,185,41,1);
    }

}
void compass_text(u8 MS)
{
    u8* text;
    u8 _X1 = 50;
    u8 _X2 = 250;
    u16 _Y = 120;
    //LCD_Clear(White);
    FontSet = myriad_bold_16;
    TextColor = Black;
    switch (MS)
    {
    case 0x00:
        //LCD_Clear(White);
        LCD_Clear(White);
        TextColor = Black;
        text = "HARDWARE INITIALIZATION";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x01:
        //LCD_Clear(White);
        LCD_Clear(White);
        TextColor = Black;
        text = "HARDWARE INITIALIZATION";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x02:
        LCD_Clear(White);
        TextColor = Black;
        text = "LEVEL 180 THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x03:
        LCD_Clear(White);
        TextColor = Black;
        text = "LEVEL 180 THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x04:
        LCD_Clear(White);
        TextColor = Black;
        text = "LEVEL 0 THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x05:
        LCD_Clear(White);
        text = "LEVEL 0 THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x06:
        LCD_Clear(White);
        TextColor = Black;
        text = "BOTTOM UP THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x07:
        LCD_Clear(White);
        TextColor = Black;
        text = "BOTTOM UP THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x08:
        LCD_Clear(White);
        TextColor = Black;
        text = "TOP UP THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x09:
        LCD_Clear(White);
        TextColor = Black;
        text = "TOP UP THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x0A:
        LCD_Clear(White);
        TextColor = Black;
        text = "RIGHT UP THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x0B:
        LCD_Clear(White);
        TextColor = Black;
        text = "RIGHT UP THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x0C:
        LCD_Clear(White);
        TextColor = Black;
        text = "LEFT UP THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x0D:
        LCD_Clear(White);
        TextColor = Black;
        text = "LEFT UP THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x0E:
        LCD_Clear(White);
        TextColor = Black;
        text = "FACE DOWN THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x0F:
        LCD_Clear(White);
        TextColor = Black;
        text = "FACE DOWN THEN PRESS THE ^ BUTTON";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    case 0x1B:
        //LCD_Clear(White);
        LCD_Clear(White);
        TextColor = Black;
        text = "HARDWARE INITIALIZATION FAILED";
        LCD_DisplayStringLine_Center(_X1, _X2, _Y, text);
        break;
    }


}

/*MENU*/
void HistoryMenu(void) {
}
void OpmodeMenu(void) {
}
void SettingMenu(void) {
}
//void NavigationMenu(void){
// }
void GoDiveMenu(void) {
}
void LogMenu(void) {
}
void MyInfoMenu(void) {
}
void SepiaInfoMenu(void) {
}
void TMTStatusMenu(void) {
}
/*End MENU*/



