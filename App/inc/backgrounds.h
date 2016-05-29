
#ifndef __BACKGROUNDS_H
#define __BACKGROUNDS_H



//#define  MAX_BG_DISPLAY              30// 35
//enum{	BLACK,H1A,H1B,H2A,H2B,H7A,H22B,H23A,H38B,H38E,H41B,H42B,H42E,H43B,H44A,H44B,H46A,H47A,
//		S1A,S4B,S5B,S9A,S13B,D1A,D4A,D6C,D7A,D7B,D7C,D8C,D9B,D10A,C1A,
//		A1A,A1B,A5A,A5C,A7A,A8A,A10A,A11A,A12B,A17A,A17B,A19A,A20A,A22A,A24A,A25A

//};
/*
enum{	BLACK,H1A,S1A,D1A,H1B,H2A,H2B,H7A,H22B,H23A,H38B,H38E,H41B,H42B,H42E,H43B,H44A,H44B,H46A,H47A,
		S4B,S5B,S9A,S13B,D4A,D4B,D6C,D7A,D7B,D7C,D9B,D10A,//C1A,
		A1A,A1B,A4A,A5A,A5C,A7A,A8A,A10A,A11A,A12B,A17A,A17B,A19A,A20A,A22A,A24A,A25A

};                                                                                                          yes
*/
enum {	BLACK,H1,H2,H3,H4,H5,H6,H9,H10,H11,H12,H13,H14,H15,H16,H19,H20,H21,H22,H23,H81,H86,H94,H101,S1,D25,D1,D9,D36,D37,D38,H74,H73,H78,H79,H80,SO1,SO7,SO8,SO9,SO10,SO12,SO13,SO13_2,SO16,SO18,Pairing1,Pairing2,Pairing3,Pairing4,
        Hz
     };
#define  MAX_BG_DISPLAY              Hz

typedef enum{
    BGP_TopPart,
    BGP_BottomPart,
    BGP_
}BackGroundPart;

#define DrawPart(name) void Draw_Part(name)
#define White                       LCD_COLOR_WHITE
#define Black                       LCD_COLOR_BLACK
#define Grey                        LCD_COLOR_GREY
#define Blue                       LCD_COLOR_BLUE
#define Blue2                       LCD_COLOR_BLUE2
#define Red                         LCD_COLOR_RED
#define Magenta                     LCD_COLOR_MAGENTA
#define Green                       LCD_COLOR_GREEN
#define Cyan                       LCD_COLOR_CYAN
#define Yellow                     LCD_COLOR_YELLOW
#define Line0                       LCD_LINE_0
#define Line1                              LCD_LINE_1
#define Line2                       LCD_LINE_2
#define Line3                       LCD_LINE_3
#define Line4                       LCD_LINE_4
#define Line5                       LCD_LINE_5
#define Line6                       LCD_LINE_6
#define Line7                       LCD_LINE_7
#define Line8                       LCD_LINE_8
#define Line9                       LCD_LINE_9
#define Horizontal                  LCD_DIR_HORIZONTAL
#define Vertical                    LCD_DIR_VERTICAL


#define MSG							((u8)in_buf[MSG_FLASH])


#define X_CP			121
#define Y_CP			209
#define R1_CP		70
#define R2_CP		50
#define R3_CP		40

//#define X_CT		       160
//#define Y_CT		       120


/*Define to decode data from TI*/

#define OPCODE_BYTE			4
#define MENSTAT_BYTE		6
#define MSG_FLASH			7
#define NPRV1_BYTE			12
#define NPRV2_BYTE			13
#define LOGSTAT				5

#define LCD_ON						0xF0
#define BLACK_SCEEN					0xF1
#define WELCOME						0xF2
#define WAIT_FOR_BEEP				0xF3
#define RESET_ST					0xF4

#define SEND_FW_VER				0xFF
#define ERROR_EEPROM 				0xE0
#define ERROR_CALIBRATION  			0xE1
#define ERROR_CHECKSUM  			0xE2
#define ERROR_ATOD  				0xE3
#define CHANGE_BATTERY  			0xE4
#define ERROR_LAST_DIVE 			0xE5
#define ERROR_ALTITUDE  			0xE6



//#define HOME_MENU					0x20
//#define HOME_SETUP_MENU 			0x21
//#define SET_DATE_TIME 				0x22
//#define NAVIGATION_MENU 			0x23  //new
#define NAV_MODE_MENU 			       0x26  //new
#define SEND_SMS 			              0x29  //new
#define SELECT_PARTNER		              0xab
#define NAV_MODE_SET_MENU 	       0xff  //new - need change
#define PARTNER_MENU		              0x28

//#define SURFACE_MODE				0x10
//#define PLAN_MODE					0x12
//#define LOG 							0x13
#define NORMMAIN_MENU  			0x14
//#define NORM_SET_GAS				0x15
//#define NORM_SET_ALARM				0x16
//#define NORM_SET_UTILITIES 			0x17
#define SET_NORM_PREVIEW1 			0x18
#define SET_NORM_PREVIEW2			0x19
//#define SONAR_MENU                              0x1A
//#define SONAR_MODE                              0x1B
//#define DIVE_MODE					0x1F
//#define DIVE_MENU					0x1E//new


#define COMPASS_CALIB		0x40

#define MY_INFO_DATA 			0x01
#define PLAN_DATA 				0x02
#define LOG_DATA 					0x03
#define NI_O2_DATA 				0x05
//#define SAVE							0x06
//#define CLEAR 						0x07
#define USB_WAIT					0x08
#define USB_120						0x09
#define USB_CONNECT			0x0A
#define USB_DOWN					0x0B
#define USB_DATA_UP				0x0C
#define USB_UPDATING			0x0D

#define DRAW_CIRLCE					0xAA


//#define 	SEPIA_BG					0x3186
#define 	SEPIA_BG					BLACK

#define 	SEPIA_SELECT				0x63F
#define 	WHITE_ICON					0xad95

#define 	SEPIA_GRAY 				0x8410
#define 	SEPIA_GRAY2 				0x94B2

#define 	SEPIA_GREEN				0x07E7

#define 	SEPIA_TOP                             0xEF5D//  0xF79E

#define  SEPIA_Cyan                             0x069F


/*
#define  H2A_SCEEN_CODE                        		0x01
#define  H38B_SCEEN_CODE                        		0x02
#define  H42E_SCEEN_CODE                        		0x03
#define  S1A_SCEEN_CODE                       		0x04
#define  D4A_SCEEN_CODE                        		0x05
#define  D7A_SCEEN_CODE                        		0x06
#define  D7B_SCEEN_CODE                        		0x07
#define  D7C_SCEEN_CODE                        		0x08
#define  C1A_SCEEN_CODE                        		0x09
#define  A10A_SCEEN_CODE                        		0x0A
#define  A11A_SCEEN_CODE                        		0x0B
*/
/*
typedef enum
{
    MyInfo 		= 	0x00,
    OCXInfo 	= 		0x01,
    SetupMenu 	= 	0x02,
    Log 			= 	0x03,
    History 		= 	0x04,
    Norm_mode 	= 	0x05,
    Gaug_mode 	= 	0x06


} Selection;
*/
/*
typedef enum
{
    Brightness 		= 	0x00,
    Bluetooth 			= 	0x01,
    Date_Time 		= 	0x02,
    Calibrate 			= 	0x03,
    Declination 		= 	0x04

} Selection_setup;
*/
/*
typedef enum
{
    Date_format 		= 	0x00,
    Date 				= 	0x01,
    Time_format 		= 	0x02,
    Time 				= 	0x03,
} date_setup;
*/
/*
enum
{
	Brightness  		= 	0x00,
	Last_Dive_Data 	= 	0x01,
	More_Data 		= 	0x02,
	PLAN			= 	0x03,
	Set_GAS			= 	0x04,
	Set_Alarm		= 	0x05,
	Set_Utilities		= 	0x06,
	Set_Preview		= 	0x07,
	View_Preview	= 	0x08
} ;
*/
enum
{
    Sel_line1  = 0x00,
    Sel_line2  = 0x01,
    Sel_line3  = 0x02,
    Sel_line4  = 0x03,
    Sel_line5  = 0x04,
    Sel_line6  = 0x05,
    Sel_line7  = 0x06,
    Sel_line8  = 0x07,
    Sel_line9 = 0x08
};
enum {GAS, TMT, DATE, BRIGHTNESS};
enum {GAS1, GAS2, GAS3,GAS4,FO2_50};
enum {TMT1, TMT2, TMT3,TMT4};
enum {Date_format, Time_format, Set_Date,Set_time};


enum {line0,line1, line2,line3, line4, line5, line6, line7, line_all, line_none};
enum {icon1,icon2, icon3,icon4, icon5, icon6,icon7, icon8, icon9};

//History data
#define DegreeConvert(X)                 ((X) - 32)/1.8  //Convert from F to C degree
#define ImperialConvert(X)                 ((UnitType_)? ((X)*0.3048) : (X))//Convert from Imperial to Meter

void Draw_C1A(void);


void Delay(__IO uint32_t num);

void data_update(void);
void redrawScreenSection(uint16_t Xpos1, uint16_t Ypos1,uint16_t Xpos2, uint16_t Ypos2, uint16_t const *bmpPtr,int16_t height,  int16_t width,int16_t X_offset, uint16_t Y_offset);
void writeBMP_nTimes(uint16_t const *bmpPtr,int16_t height,  int16_t width, uint16_t X_offset, uint16_t Y_offset, int16_t nTimes );
void Percent_bar_left(uint16_t Color, uint8_t percent);
void Percent_bar_right(uint16_t Color, uint8_t percent);
void redraw_selection(u8 sel);
void Ascii_Float2Str(char *str, u16 *len, float fvalue, u16 precision);
uint8_t Num2Str(uint16_t num, char *str, uint8_t maxlen);
void Draw_Redbar(u8 position);
//void LCD_DisplayStringLine_As_Left(uint16_t X, uint16_t Y, uint8_t *ptr);

void battery(uint16_t Color);
void battery1(uint16_t Color);
void battery_red(uint16_t Color);
void H41A_bar(uint16_t Color);
void Draw_H1(void);
void Draw_H2(void);
void Draw_H3(void);
void Draw_H74(void);
void Draw_H4(void);
void Draw_H5(void);
void Draw_H6(void);
void Draw_H9(void);
void Draw_H10(void);
void Draw_H11(void);
void Draw_H12(void);
void Draw_H13(void);
void Draw_H14(void);
void Draw_H15(void);
void Draw_H19(void);
void Draw_H20(void);
void Draw_H23(void);
void Draw_H94(void);
void Draw_SO7(void);
void Draw_SO10(void);
void Draw_SO16(void);
void Draw_SO18(void);
void Draw_SO8(void);
void Draw_H73(void);
void Draw_S1(void);
void Draw_D25(void);
void Draw_D9(void);
void Draw_H74(void);
void Draw_H78(void);
void Draw_H80(void);
void Draw_H81(void);
void Draw_H79(void);
void Draw_H75(void);
void Draw_H86(void);


void Text_H2(void);
void Text_H3(void);
void Text_H5(void);
void Text_H6(void);
void Text_H10(void);
void Text_H11(void);
void Text_H12(void);
void Text_H13(void);
void Text_H14(void);
void Text_H15(void);
void Text_H19(void);
void Text_H20(void);
void Text_H23(void);
void Text_H81(void);
void Text_H86(void);
void Text_H89(void);


void Text_H94(void);
void Text_S1(void);
void Text_D25(void);

void Text_D9(void);
void Text_H74(void);
void Text_SO7(void);
void Text_SO10(void);
void Text_SO8(void);
void Text_SO16(void);
void Text_H101(void);
void Text_DiveMenu(void);
void compass_text(u8 MS);

void decode(void);
uint8_t Bcd2ToByte(uint8_t Value);
uint8_t ByteToBcd2(uint8_t Value);


void lcd320x240_drawcircle(uint16_t Xpos, uint16_t Ypos,uint16_t d);
void LCD_DrawCircle1(uint16_t  x0,uint16_t  y0,uint16_t  radius);
void LCD_DrawEllipse(uint16_t  Xpos, uint16_t Ypos, uint16_t Radius1, uint16_t Radius2);
void LCD_DrawFullEllipse(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, uint16_t Radius2);
void DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);

void DrawCompass(u16 percent);
//float mux(float x,int n);
//int giai_thua(int n);
//float SIN(float x,int n);
//float sin_x (float x );
void displayCirlce(void);
void redrawScreen(uint16_t Xpos1, uint16_t Ypos1,uint16_t Xpos2, uint16_t Ypos2,uint16_t Color);

void pre_battery(void);
void pre_temper(char* buf, u8 value);
void pre_time(char *Clock, uint8_t flat,u8 hour, u8 munite);
void pre_TotadDive(uint8_t *buf, uint8_t value);
void pre_TotalDivetime(uint8_t *buf, uint8_t value);
void pre_Divetime(uint8_t *buf, uint8_t value);
void pre_Depth(uint8_t *buf, uint8_t value);
void Select_unselect_TMTnum(u8 index_sel, u8 index_unsel);
void Test_Fonts(void);
static void PutPixelColor(int16_t x, int16_t y);
uint8_t Hex2Str(uint16_t num, uint8_t * str, uint8_t maxlen);
void Select_unselect_Left(u8 index_sel, u8 index_unsel);
void DisplayText_Left(u8 index_sel, u8 index_unsel, u8 whatdisplay);
void DisplayText_Right_GAS(u8 Gas_index, u8 flat);
u8 stringcopy(u8 *dest, u8 * src, u16 lengh);
void DisplayText_Right_TMT(u8 TMT_index, u8 flat);
void DisplayText_Right_Date(u8 index, u8 flat);
void dispay_brightness(u8 percent);

void DisplayPercentTLBG(uint16_t Color, uint8_t percent);
void DisplayPercentARBG(uint16_t Color, uint8_t percent);
void pre_percent(uint8_t * buf,uint8_t percent);
void Select_NavMenu(u8 icon);
void UnSelect_NavMenu(u8 icon);
void Select_HomeMenu(u8 icon);
void UnSelect_HomeMenu(u8 icon);
void Select_SonarMenu(u8 Sel_line);
void UnSelect_SonarMenu(u8 Sel_line);
void Select_DiveMainMenu(u8 Sel_line);
void Select_SonarNavMode(u8 Sel_line);
void UnSelect_SonarNavMode(u8 Sel_line);
void Select_SMS(u8 Sel_line);
void UnSelect_SMS(u8 Sel_line);
void Draw_SonarMain(void);
void UpdateHeader(void);
void DisplayMainClock(void);
void Text_SO18(void);
void PrepareTemper(void);
void Select_DiveMenu(u8 Sel_line);
void UnSelect_DiveMenu(u8 Sel_line);
void UnSelect_SetNavMode(u8 Sel_line);
void Select_SetNavMode(u8 Sel_line);
void Re_Sync(u8 status);
#endif
