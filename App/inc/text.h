
#ifndef __TEXT_H
#define __TEXT_H
#define Green_BackGround  ASSEMBLE_RGB(58, 224, 58)
#define Orange_BackGround ASSEMBLE_RGB(209, 100, 27)
#define Black_BackGround ASSEMBLE_RGB(126, 119, 117)
#define Red_BackGround ASSEMBLE_RGB(209, 100, 27)//Not right 
#define Yellow_BackGround ASSEMBLE_RGB(209, 100, 27)//Not right
#define Bold 1
#define Norm 0


typedef struct {
    u8 PDE_String[10];
    u8 NDC_String[10];
} PlanBuffer;

typedef struct {
    u8* Row_String_Left;//Row on the left
    u8 Row_String_Right_0[6];//Row on the right
    u8 Row_String_Right_1[6];//Row on the right
} RowPreview;

#define OpCode                                        in_buf[OPCODE_BYTE]
#define MENSTAT                                        in_buf[MENSTAT_BYTE]
#define MainMode                                in_buf[5]//The format for MAIN MODE = MM for short.

//OPCODE 12H
//PLAN MODE
#define PDEPL(X)                                       (u8)Plan_Data[X][0]//high byte in 
#define PDEPH(X)                                      (u8)Plan_Data[X][1]// low byte
#define PDE(X)                                        (u16)(((PDEPH(X)) * 256 + (PDEPL(X))) >> 4)

#define NDCL(X)                                        (u8)Plan_Data[X][2]
#define NDCH(X)                                        (u8)Plan_Data[X][3]
#define NDC(X)                                        ((u16)(((NDCH(X)) * 256) + (NDCL(X))))
//OPCODE 13H
#define LogHighLight						((u8)(in_buf[6] - 1))
#define StartRecord						((u8)in_buf[7])
#define EndRecord						((u8)(in_buf[9]))
#define TotalRecord						((u8)in_buf[10])
#define CurrentRecord					((u8)in_buf[11])
#define DiveTimeLow_					(u8)Log_Data[CurrentRecord][10]
#define DiveTimeHigh_					(u8)Log_Data[CurrentRecord][11]
#define MaxDepthLogLow					(u8)Log_Data[CurrentRecord][8]
#define MaxDepthLogHigh					(u8)Log_Data[CurrentRecord][9]
#define AltitudeLog						(u8)Log_Data[CurrentRecord][13]
//Bluetooth count down
#define BlueTooth_CountDown                ((u8)(in_buf[5]))        // OPMODE = 0XH.  05H, 06H, 07H, 08H, 09H, 0AH, 0BH, 0CH, 0DH. Total send 0AH = 10 bytes.


//Day Month Year
#define DMY_String                                 ((u8*)(MD) ? ("D.M.Y") : ("M.D.Y"))/* Day Month Year String H9A, H9B
                                                                                                */
#define DM_String                                 ((u8*)(MD) ? ("D.M") : ("M.D"))/* Day Month Year String H8A, H8B
                                                                                                */

//Battery
#define BATT                                         ((u8)(in_buf[12])) /* BATT%: Battery percentage from 0% to 100% in binary.
                                                                                        */
//USRFLG CODE
//5. DSAT or Z+
#define DSAT_bit                                    ((u8)(((in_buf[8]) & BIT_5)>>5))   //USRFLG CODE : BIT 5: 0 = DSAT, 1 = PZ+ Algorithm
#define DSAT_String                                ((u8*)(DSAT_bit) ? "Z+" : "DSAT")
//FO2 50% ON/OFF
//#define FO2default					((u8)( in_buf[8] & BIT_4)) //BIT 4: 0 = 50% default OFF/ 1 = ON
//#define FO2def_String					((u8*)(FO2default == BIT_4) ? "ON" : "OFF")
#define MORFLG							 ((u8) in_buf[9])
#define STDFLG							((u8) in_buf[10])
#define DEEPSTOP_String					((u8*)((MORFLG & BIT_4) == BIT_4) ? "ON" : "OFF")
#define MORFLG_LowNibble				((u8)(MORFLG & 0x0F))
#define MORFLG_HighNibble				((u8)(MORFLG >> 4))
//#define SAFETY_STOP_String				((u8*)(SafetyStopPrepare()))
//#define SAFETY_STOP_String				((u8*)(MORFLG_LowNibble == 0) ? "OFF" :((MORFLG_LowNibble == 1) ? "ON" : "SET"))
#define STDFLG_LowNibble				((u8)(STDFLG & 0x0F))
#define PFSHOT							 ((u8) in_buf[11])

//SET PREVIEW
#define NPRV1							((u8) in_buf[12])
#define NPRV1_bit0						((u8)(NPRV1 & BIT_0) >> 0)
#define NPRV1_bit1						((u8)(NPRV1 & BIT_1) >> 1)
#define NPRV1_bit2						((u8)(NPRV1 & BIT_2) >> 2)
#define NPRV1_bit3						((u8)(NPRV1 & BIT_3) >> 3)
#define NPRV1_bit4						((u8)(NPRV1 & BIT_4) >> 4)
#define NPRV1_bit5						((u8)(NPRV1 & BIT_5) >> 5)
#define NPRV1_bit6						((u8)(NPRV1 & BIT_6) >> 6)
#define NPRV1_bit7						((u8)(NPRV1 & BIT_7) >> 7)

#define Bold_V1_0						((u8)((MENSTAT == 0x01) ? 1 : NPRV1_bit0))
#define Bold_V1_1						((u8)((MENSTAT == 0x02) ? 1 : NPRV1_bit1))
#define Bold_V1_2						((u8)((MENSTAT == 0x03) ? 1 : NPRV1_bit2))
#define Bold_V1_3						((u8)((MENSTAT == 0x04) ? 1 : NPRV1_bit3))
#define Bold_V1_4						((u8)((MENSTAT == 0x05) ? 1 : NPRV1_bit4))
#define Bold_V1_5						((u8)((MENSTAT == 0x06) ? 1 : NPRV1_bit5))
#define Bold_V1_6						((u8)((MENSTAT == 0x07) ? 1 : NPRV1_bit6))
#define Bold_V1_7						((u8)((MENSTAT == 0x08) ? 1 : NPRV1_bit7))
#define Bold_V1_8						((u8)((MENSTAT == 0x09) ? 1 : 0))

#define NPRV2							((u8) in_buf[13])
#define NPRV2_bit0						((u8)(NPRV2 & BIT_0) >> 0)
#define NPRV2_bit1						((u8)(NPRV2 & BIT_1) >> 1)
#define NPRV2_bit2						((u8)(NPRV2 & BIT_2) >> 2)
#define NPRV2_bit3						((u8)(NPRV2 & BIT_3) >> 3)
#define NPRV2_bit4						((u8)(NPRV2 & BIT_4) >> 4)
#define NPRV2_bit5						((u8)(NPRV2 & BIT_5) >> 5)
#define NPRV2_bit6						((u8)(NPRV2 & BIT_6) >> 6)
#define NPRV2_bit7						((u8)(NPRV2 & BIT_7) >> 7)

#define Bold_V2_0						((u8)((MENSTAT == 0x01) ? 1 : NPRV2_bit0))
#define Bold_V2_1						((u8)((MENSTAT == 0x02) ? 1 : NPRV2_bit1))
#define Bold_V2_2						((u8)((MENSTAT == 0x03) ? 1 : NPRV2_bit2))
#define Bold_V2_3						((u8)((MENSTAT == 0x04) ? 1 : NPRV2_bit3))
#define Bold_V2_4						((u8)((MENSTAT == 0x05) ? 1 : NPRV2_bit4))
#define Bold_V2_5						((u8)((MENSTAT == 0x06) ? 1 : NPRV2_bit5))
#define Bold_V2_6						((u8)((MENSTAT == 0x07) ? 1 : NPRV2_bit6))
#define Bold_V2_7						((u8)((MENSTAT == 0x08) ? 1 : NPRV2_bit7))
#define Bold_V2_8						((u8)((MENSTAT == 0x09) ? 1 : 0))

#define RowSelected 						((u16)((NPRV2 * 256) + NPRV1))
//Aud Alarm
//u8 AudAlarm							((u8)( in_buf[8] & BIT_1))   //BIT 1: 0 = Audible Alarm OFF, 1 = ON
#define USRFLG							 ((u8) in_buf[8])
//7. SEA or FRESH
#define WaterType_bit                            ((u8)(USRFLG & BIT_7))   //BIT 7: 0 = SEA, 1 = FRESH water
#define WaterType_String                        ((u8*)(WaterType_bit != BIT_7) ? "SEA" : "FRESH") //BIT 7: 0 = SEA, 1 = FRESH water

//Conservative
#define Coseva_bit                                   ((u8)((USRFLG & BIT_6)>>6))     //USRFLG CODE : BIT 6: 0 = Conservative OFF, 1 = ON  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
#define Coseva_StringOnOff                ((u8*)(Coseva_bit) ? "ON" : "OFF")//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
#define Coseva_StringCF                        ((u8*)(Coseva_bit) ? "CF" : "")//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//History data
#define DegreeConvert(X)                 ((X) - 32)/1.8  //Convert from F to C degree
#define ImperialConvert(X)                 ((UnitType_)? ((X)*0.3048) : (X))//Convert from Imperial to Meter

//Lowest temperatue
#define lowestTemp                                 (u8)in_buf[9]//TEMP = Lowest temperature.

//Total dives
#define TotD2                                          (u8)in_buf[11]// (TotD2 * 256)  + TotD1 = Total dives.
#define TotD1                                          (u8)in_buf[10]// (TotD2 * 256)  + TotD1 = Total dives.
#define totalDive                                         ((u16)(((TotD2) * 256) + (TotD1))) //(TotD2 * 256)  + TotD1 = Total dives.

//Total dive hours
#define TDT1                                                 (u8)in_buf[12]
#define TDT2                                                 (u8)in_buf[13]
#define totalDiveTime                         ((u16)(((TDT2) * 256) + (TDT1))) //(TDT2 * 256) + TDT1 = Total dive time in hours.
//OPCODE 12H -------------------------------------------------------------------------------------------------
#define RowHighLight                                ((u8)(in_buf[10] -1))//Row 1->9 highlight
#define StartPlan                                        ((u8)in_buf[5])
#define EndPlan                                        ((u8)in_buf[6])

//------------------------------------------------------------------------------------------------------------
//OPCODE = 14H------------------------------------------------------------------------------------------------
//Last Elapse Dive Time
#define EDTL                                                ((u8) (OpCode == NORMMAIN_MENU && MENSTAT == 0x21) ? in_buf[10] : ((OpCode == OC_LogMode) ? DiveTimeLow_ : in_buf[32]))
#define EDTH                                               ((u8) (OpCode == NORMMAIN_MENU && MENSTAT == 0x21) ? in_buf[11] : ((OpCode == OC_LogMode) ? DiveTimeHigh_ : in_buf[33]))
#define EDT   							((u16)((OpCode == NORMMAIN_MENU) &&(MENSTAT == 0x21) || (OpCode == OC_LogMode)) ? ((((EDTH) * 256) + EDTL))  :  in_buf[20])//Last Elapse Dive Time = (EDTH * 256 + EDTL) in minutes.
// (((OpCode == NORMMAIN_MENU) || (OpCode == PLAN_MODE))        ?        (in_buf[12])        :0x00)))
//Temperature
//#define TEMP                                                (u8)(OpCode == LOG) ? (Log_Data[CurrentRecord][17]) : in_buf[9]//page 10 NORM MORE DATA
#define TEMP                                       in_buf[9]

//Maximum depth

#define MXDL                                         ((u8)        ((OpCode == OC_HomeMenu)                ?        (in_buf[16])        :\
                                                                                (((OpCode == NORMMAIN_MENU) || (OpCode == OC_PlanMode))        ?        (in_buf[12]) : MaxDepthLogLow)))

#define MXDH                                         ((u8)        ((OpCode == OC_HomeMenu)                ?        (in_buf[17])        :\
                                                                                (((OpCode == NORMMAIN_MENU) || (OpCode == OC_PlanMode))        ?        (in_buf[13]) : MaxDepthLogHigh)))//0x00 is default 

#define maxDepth                                  ((float)(((MXDH) * 256 + (MXDL)) >> 4))        //(MXD2 * 256) + MXD1 = Maximum depth in binary format 1FF.f in FT.

//Maximum Operation Depth
#define MODL						  ((u8)((OpCode == OC_PlanMode) ? in_buf[12]: in_buf[32]))
#define MODH						 ((u8)((OpCode == OC_PlanMode) ? in_buf[13]: in_buf[33]))
#define MOD							((float)(((MODH) * 256 + (MODL)) >> 4))//MOD = Maximum Operation Depth = 1FF.f in Feet or Metric depends on BIT3 of USRFLG.

//Depth alarm MENSAT = 91H
#define DEPL                                          (u8)in_buf[14]
#define DEPH                                         (u8)in_buf[15]
#define DEPTH                                       ((float)(((DEPH) * 256 + (DEPL)) >> 4))//DEPTH is in 1FF.f format, 0 = OFF, or from 30 FT (1E0h) to 330FT (14A0h), or from 10 M (00a0h) to 100M (0640h).

//O2
#define O2SAT                                         (u8)((OpCode == OC_LogMode) ? Log_Data[CurrentRecord][22]: in_buf[16]) //O2SAT is in binary format, from 00% (00H) to 100% (64H).

//Fly time and DESAT time is in binary minutes, convert them to HH:MM.
#define FLYL                                                (u8)in_buf[10]
#define FLYH                                                (u8)in_buf[11]
#define FLYTime                                        ((u16)(((FLYH) * 256) + (FLYL)))//Fly time and DESAT time is in binary minutes, convert them to HH:MM.
#define FLY_Hr                                        ((u16)(FLYTime / 60))
#define FLY_Min                                        ((u16)(FLYTime % 60))

#define DESATL                                        (u8)in_buf[12]
#define DESATH                                        (u8)in_buf[13]
#define DESATTime                                ((u16)(((DESATH) * 256) + (DESATL)))//Fly time and DESAT time is in binary minutes, convert them to HH:MM.
#define DESAT_Hr                                        ((u16)(DESATTime / 60))
#define DESAT_Min                                ((u16)(DESATTime % 60))

//Maximum dive time in minutes
#define MDT1                                         (u8)in_buf[14]
#define MDT2                                         (u8)in_buf[15]
#define maxDiveTime                             ((u16)(((MDT2) * 256) + (MDT1))) //(MDT2 * 256) + MDT1 = Maximum dive time.

//Total depth
#define TDHH                                          (u8)in_buf[21]
#define TDHL                                          (u8)in_buf[20]
#define TDLH                                          (u8)in_buf[19]
#define TDLL                                          (u8)in_buf[18]
#define totalDepth                                 ((u16)(((((TDHH) * 256 + (TDHL)) * 65536) + (((TDLH) * 256) + (TDLL)))>>4))

//Average Depth
#define aveDepth                                  ((u16)(OpCode = OC_LogMode) ? ((Log_Data[CurrentRecord][27]* 256 + Log_Data[CurrentRecord][26]) / 16): ((totalDepth)/(totalDive)))

//Average dive times
#define aveDiveTime                                 ((u16)(((totalDiveTime) * 60)/(totalDive)))

//Maximum altitude
#define Altitude                                        ((u8)((OpCode == OC_LogMode) ? AltitudeLog : in_buf[17]))

//Decline
//#define EASWES                                 ((signed char)(in_buf[10]))//OPCODE = 21H.  MENSTAT = X0H. Total is 7 bytes.
#define EASWES                                         ((u8)in_buf[10])//OPCODE = 21H.  MENSTAT = X0H. Total is 7 bytes.
#define DeclineBit                                 ((u8)(EASWES>>7))//BIT7: 0 = EAST  / 1 = WEST
#define EASWES_String                          ((u8*) ((DeclineBit) ? ("WEST") : ("EAST")))//BIT7: 0 = EAST  / 1 = WEST
#define DeclineProcess                         (((u8)(EASWES & 0x7F) == 0x00) ? ProcessDecline_1() : ProcessDecline_2())//EASWES = 0 -> "OFF"

//SURFACE - 1 (S1A, S1B)----------------------------------------------------------------------------------
#define SI_Low                                        ((u8)(in_buf[14]))//OPCODE = 10H. 
#define SI_High                                        ((u8)(in_buf[15]))//OPCODE = 10H. 
#define SurfTime                                          ((u16)((SI_High<<8) + (u16)SI_Low))        /* Add SI_High and SI_Low to get SurfTime total
                                                                                                                                */
#define Surf_Hour                                ((u16)(SurfTime / 60))                                        /* Surface time / 60 mins --> Surf Hour
                                                                                                                                */
#define Surf_Min                                        ((u16)(SurfTime % 60))                                        /* Surface time % 60 mins --> Surf Minutes
                                                                                                                                */
//1. GTRL (LSB) and GTRH (MSB) = Gas Time Remaining in binary minutes.  When FFFF, display - - PSI or BAR. No GTR if Gas# = Gas2, 3, or 4.
#define GTR_Low                                        ((u8)(in_buf[18]))//OPCODE = 10H. 
#define GTR_High                                        ((u8)(in_buf[19]))//OPCODE = 10H. 
#define GTR_Time                                        ((u16)((GTR_High<<8) + (u16)GTR_Low))        /* Add GTR_High and GTR_Low to get Gas Time Remaining in binary minutes
                                                                                                                                Gas time remain
                                                                                                                                */
//2. Gas# (1/2/3/4...)
#define Gas_Num                                        ((u8)((OpCode == OC_SetGasMenu) ? ((u8)(MENSTAT >> 4)) : ((OpCode == 0x18) ? (MENSTAT & 0x0F) : in_buf[22])))

#define PSI_2_BAR(X)                                ((u16)( (X) /14.50377438972831))/* PSI to BAR unit (input PSI and return BAR number)
                                                                                                                                */
#define FO2FLG                                          ((u8)        ((OpCode == OC_SurfaceMode)                ?        (in_buf[25])        :\
                                                                                (((OpCode == OC_SetGasMenu) || (OpCode == NORMMAIN_MENU))        ?        (in_buf[23])        :(in_buf[9]))))
#define FO2Bit_1                                        ((u8)(FO2FLG & BIT_1))
#define FO2Bit_2                                        ((u8)(FO2FLG & BIT_2))
#define FO2Bit_3                                        ((u8)(FO2FLG & BIT_3))
#define FO2Bit_4                                        ((u8)(FO2FLG & BIT_4))
#define FO2Bit_5                                        ((u8)(FO2FLG & BIT_5))


//3. Tank pressure (PSI or BAR) S1A/S1B
#define Tank_Low                                        ((u8)(in_buf[16]))//OPCODE = 10H. 
#define Tank_High                                ((u8)(in_buf[17]))//OPCODE = 10H. 
#define Tank_Pressure                        ((u16)((Tank_High<<8) + (u16)Tank_Low))/*TANK PRESSURE (PSI or BAR depends on BIT 3 of USRFLG). 
                                                                                                                                Display SPG when Gas# = Gas 2, 3, or 4.                                                                                                                                */
//Tank define for LOG MODE 0x13
#define Start_PressLow					((u8)Log_Data[CurrentRecord][18])
#define Start_PressHigh					((u8)Log_Data[CurrentRecord][19])
#define Start_Pressure					((u16)(((Start_PressHigh) * 256) + (Start_PressLow)))

#define End_PressLow					((u8)Log_Data[CurrentRecord][20])
#define End_PressHigh					((u8)Log_Data[CurrentRecord][21])
#define End_Pressure						((u16)(((End_PressHigh) * 256) + (End_PressLow)))

//4. Others
#define TLBG                                                ((u8)((OpCode == OC_SetAlarmMenu||OpCode == NORMMAIN_MENU) ? in_buf[21]: in_buf[20]))//OPCODE = 10H. TLBG = from 0% to 100% in binary
#define ASCBG                                        ((u8)(in_buf[21]))//OPCODE = 10H. ASCBG = from 0% to 100% in binary.
#define FO2_Num                                        ((u8)(in_buf[FO2_ReturnNum()]))//OPCODE = 10H. FO2 = 0 = Air, or from 21% to 100% in binary.
#define DTR								((u8) in_buf[22])
#define TURNL							((u8) in_buf[16])
#define TURNH							((u8) in_buf[17])
#define TURN								 ((u16)((TURNH<<8) + (u16)TURNL))
#define ENDL								((u8) in_buf[18])
#define ENDH								((u8) in_buf[19])
#define END								 ((u16)((ENDH<<8) + (u16)ENDL))

//FO2 and PO2 Value
#define FO2								((u8)((OpCode == OC_SurfaceMode || OpCode == OC_DiveMode) ? in_buf[23]: in_buf[14]))
#define FO21								((u8)((OpCode == 0x1D) ? in_buf[10]: ((OpCode == OC_LogMode) ? Log_Data[CurrentRecord][23]: in_buf[24])))
#define FO22 							((u8)((OpCode == 0x1D) ? in_buf[14]: in_buf[26]))
#define FO23 							((u8)((OpCode == 0x1D) ? in_buf[18]: in_buf[28]))
#define FO24 							((u8)((OpCode == 0x1D) ? in_buf[22]: in_buf[30]))

#define PO2								((float)((OpCode == OC_SurfaceMode || OpCode == OC_DiveMode) ? in_buf[24]: in_buf[15]))
#define PO21								((float)((OpCode == 0x1D) ? (in_buf[11]):((OpCode == OC_LogMode) ? Log_Data[CurrentRecord][24]: in_buf[25])))
#define PO22 							((float)((OpCode == 0x1D) ? (in_buf[15]): (in_buf[27])))
#define PO23 							((float)((OpCode == 0x1D) ? (in_buf[19]): (in_buf[29])))
#define PO24 							((float)((OpCode == 0x1D) ? (in_buf[21]): (in_buf[31])))

#define PO2_Num                                        (((float)in_buf[PO2_ReturnNum()]/(float)100))//OPCODE = 10H. PO2 is in binary, divided by 100 to get the real value
//#define PO2_Num                                        ((float)   (((OpCode == NORM_SET_GAS) && ((MENSTAT == 0x10) ||(MENSTAT == 0x12))) ? ((float)in_buf[25]/(float)100):\
//   (((OpCode == NORM_SET_GAS) && ((MENSTAT == 0x20) ||(MENSTAT == 0x22))) ? ((float)in_buf[27]/(float)100):\
//   (((OpCode == NORM_SET_GAS) && ((MENSTAT == 0x30) ||(MENSTAT == 0x32))) ? ((float)in_buf[29]/(float)100):\
//  (((OpCode == NORM_SET_GAS) && ((MENSTAT == 0x40) ||(MENSTAT == 0x42))) ? ((float)in_buf[31]/(float)100):\
//  ((((OpCode == NORMMAIN_MENU) && (MENSTAT ==  0x31))|| (OpCode == PLAN_MODE)||((OpCode == NORM_SET_GAS) && (MENSTAT ==  0x91))) ? ((float)in_buf[15]/(float)100):\
//  ((((OpCode == SURFACE_MODE)||(OpCode == 0x1E)||(OpCode == 0x1F)) ? ((float)in_buf[24]/(float)100):\
// ((((OpCode == 0x1D)) ? ((float)in_buf[11]/(float)100):\
// 0x00))))))))))
#define DiveNum                                        ((u8)(in_buf[13]))//OPCODE = 10H. DIVE# = Dive number from 0 to 24 in BINARY.
#define PressureStr                                ((u8*)((!UnitType_) ? "PSI" : "BAR"))

//-----------------------------------------------------------------------------------------------------------

u16 ImplementColor(uint16_t PixelColor);
void LCD_DisplayChar(uint16_t Line, uint16_t Column, uint8_t Ascii);
void Text_H1A(void);//Done
void Text_H2A(void);//OK
void Text_H1B(void);//OK
void Text_H2B(void);//OK
void Text_H3A(void);//OK
void Text_H4A(void);//OK
void Text_H5A(void);//OK
void Text_H5B(void);//OK
void Text_H6A(void);//OK
void Text_H6B(void);//OK
void Text_H6C(void);//OK
void Text_H6D(void);//OK
void Text_H6E(void);//OK
void Text_H6F(void);//OK
void Text_H6G(void);//OK
void Text_H6H(void);//OK
void Text_H7A(void);//OK
void Text_H8A(void);//OK
void Text_H8B(void);//OK
void Text_H9A(void);//OK
void Text_H9B(void);//OK
void Text_H10A(void);//OK
void Text_H10B(void);//OK
void Text_H11A(void);//OK
void Text_H11B(void);//OK
void Text_H12A(void);//OK
void Text_H12B(void);//OK
void Text_H12C(void);//OK
void Text_H12D(void);//OK
void Text_H12E(void);//OK
void Text_H12F(void);//OK
void Text_H12G(void);//OK
void Text_H12H(void);//OK
void Text_H12J(void);//OK
void Text_H13A(void);//OK
void Text_H13B(void);//Pending with ° character
void Text_H14A(void);//OK
void Text_H14B(void);//OK
void Text_H14C(void);//OK
void Text_H14D(void);//OK
void Text_H15A(void);//OK
void Text_H15B(void);//OK
void Text_H16A(void);//OK
void Text_H16B(void);//OK
void Text_H16C(void);//OK
void Text_H16D(void);//OK
void Text_H16E(void);//OK
void Text_H16F(void);//OK
void Text_H17A(void);//OK
void Text_H18A(void);//OK
void Text_S1A(void);//OK
void Text_S1B(void);//OK
void Text_S2A(void);//OK
void Text_S2B(void);//OK
void Text_S3A(void);//OK
void Text_S3B(void);//OK
void Text_S4A(void);//OK
void Text_S4B(void);//OK review timebuff DESAT TIME
void Text_S5A(void);//OK
void Text_S5B(void);//OK
void Text_S6A(void);//OK
void Text_S6B(void);//OK
void Text_S6C(void);//OK
void Text_S7A(void);//OK
void Text_S7B(void);//OK
void Text_S8A(void);//OK
void Text_S8B(void);//OK
void Text_S9A(void);//OK
void Text_S9B(void);//OK
void Text_S10A(void);//OK
void Text_S10B(void);//OK
void Text_S11A(void);//OK
void Text_S12A(void);//OK
void Text_S12B(void);//OK
void Text_S13A(void);//OK
void Text_S13B(void);//OK
void Text_S14A(void);//OK
void Text_S14B(void);//OK
void Text_S15A(void);//OK
void Text_S15B(void);//OK
void Text_S16A(void);//OK
void Text_S16B(void);//OK 5min will be better if find the align better solution or add '0' before smaller 10 value
void Text_S17A(void);//OK
void Text_S17B(void);//OK
void Text_S18A(void);//OK
void Text_S18B(void);//OK
void Text_S19A(void);//OK
void Text_S20A(void);//OK
void Text_S20B(void);//OK
void Text_S21A(void);//OK
void Text_S21B(void);//OK
void Text_S22A(void);//OK
void Text_S22B(void);//OK
void Text_S23A(void);//OK
void Text_S23B(void);//OK
void Text_S23C(void);//
void Text_S24A(void);//OK
void Text_S24B(void);//OK
void Text_S25A(void);//OK
void Text_S25B(void);//OK
void Text_S26A(void);//Ok
void Text_S26B(void);//OK
void Text_S27A(void);//OK
void Text_S27B(void);//OK
void Text_S27C(void);//OK
void Text_S28A(void);//OK
void Text_S28B(void);//OK
void RowPreviewProcess(void) ;
void CheckStopDepth(void);//SAFETY STOP
void CheckStopTime(void);//SAFETY STOP
void Text_S29A(void);//OK
void Text_S29B(void);//OK
void Text_S30A(void);//OK
void Text_S30B(void);//OK
void Text_S31A(void);//OK
void Text_S31B(void);//OK
void Text_S32A(void);//OK
void Text_S32B(void);//OK
void Text_S33A(void);//OK
void Text_S34A(void);//OK
void Text_S34B(void);//OK
void Text_S35A(void);//OK
void Text_S35B(void);//OK
void Text_S36A(void);//OK
void Text_S36B(void);//OK
void Text_S37A(void);//OK
void Text_S37B(void);//OK
void Text_S38A(void);//OK
void Text_S38B(void);//OK
void Text_S39A(void);//OK
void Text_S40A(void);//OK
void Text_S40B(void);//OK
void Text_S41A(void);//OK
void Text_S41B(void);//OK
void Text_S42A(void);//OK
void Text_S42B(void);//OK
void Text_S43A(void);//OK
void Text_S43B(void);//OK
void Text_D1A(void);//Ok
void Text_D1B(void);//Ok
void Text_D1C(void);//OK
void Text_D2A(void);//OK
void Text_D2B(void);//OK
void Text_D3A(void);//OK
void Text_D3B(void);//OK
void Text_D4A(void);//OK
void Text_D4B(void);//OK
void Text_D4C(void);//OK but review the buffer min:sec
void Text_D5A(void);//OK
void Text_D5B(void);//OK
void Text_D5C(void);//OK
void Text_D6A(void);//OK but review the buffer min:sec
void Text_D6B(void);//OK
void Text_D6C(void);//OK
void Text_D7A(void);//OK
void Text_D7B(void);//OK
void Text_D8A(void);//OK
void Text_D8B(void);//OK
void Text_D9A(void);//Nearly OK
void Text_D9B(void);//OK
void Text_D10A(void);//OK
void Text_D10B(void);//OK
void Text_D11A(void);//OK
void Text_D11B(void);//OK
void Text_A1A(void);//OK
void Text_A1B(void);//OK
void Text_A1C(void);//OK
void Text_A2A(void);//OK
void Text_A2B(void);//OK
void Text_A3A(void);//OK
void Text_A3B(void);//OK
void Text_A4A(void);//OK
void Text_A5A(void);//OK
void Text_A5B(void);//OK
void Text_A6A(void);//OK
void Text_A7A(void);//OK
void Text_A7B(void);//OK
void Text_A7C(void);//OK
void Text_A8A(void);//OK
void Text_A8B(void);//OK
void Text_A8C(void);//OK
void Text_A9A(void);//Nearly OK review RUN
void Text_A10A(void);//OK
void Text_A11A(void);//OK
void Text_A11B(void);//OK
void Text_A12A(void);//OK
void Text_A13A(void);//OK
void Text_A14A(void);//OK
void Text_A14B(void);//OK
void Text_A15A(void);//OK
void Text_A15B(void);//Ok
void Text_A16A(void);//Ok
void Text_A16B(void);//OK
void Text_A16C(void);//OK
void Text_A17A(void);//OK
void Text_A17B(void);//OK
void Text_A17C(void);//OK
void Text_A18A(void);//OK
void Text_A18B(void);//OK
void Text_A19A(void);//OK
void Text_A19B(void);//OK
void Text_A20A(void);//OK
void Text_A21A(void);//OK
void Text_A22A(void);//OK
void Text_A23A(void);//OK
void Text_A24A(void);//OK
void Text_A25A(void);//OK
void Text_A26A(void);//OK
void Text_A26B(void);//OK
void Text_A27A(void);//OK
void Text_A27B(void);//OK
void Text_A28A(void);//OK
void Text_A28B(void);//OK
void Text_A28C(void);//OK
void Text_A28D(void);//OK
void Text_A28E(void);//OK
void Text_A28F(void);//OK
void Text_A28G(void);//OK
void WriteLeftText (uint8_t numLine, uint8_t FlagChoose);//Write text on left with bold text select
inline void Set_Text_Bold(void) ;
inline void Set_Text_Normal(void);
inline void Process_PDE_String(u8 );
inline void Process_NDC_String(u8 );
inline void Process_NDC_String(u8 );
void Update_Plan_Data(void);
void WriteLeftText_1 (void);//Write text on left with bold text select
void Text_BaseSurface_2();
void BaseSurface_2();

void WriteLeftText_AlignRight (void);

/*Basic text to write screen Ducthinh90 */
void WriteText_Title_1(void);
void WriteText_Bottom (uint8_t* );//xxx The same with the bottom 1 but color background diffirent will fix after
void WriteText_Bottom_1(uint8_t* );
void WriteText_MainMenu (uint8_t * , uint16_t );
void WriteText_Title_2 (uint8_t*, uint16_t, uint16_t);
void WriteText_Title_3(uint16_t);
void WriteText_Title_4(uint8_t *, uint8_t );
void WriteText_Title_5(void);
void WriteText_Title_6(uint16_t );//Nearly the same with Title_3
void WriteText_Left_0 (uint8_t , uint8_t , uint8_t *);
void WriteText_Left_1 (uint8_t , uint8_t , uint8_t *);
void WriteText_Left_2(uint8_t * );
void WriteText_Left_3(uint16_t );
void WriteText_Left_4(void);
void WriteText_Left_5(void);
void WriteText_Left_6(uint8_t*, uint16_t);
void WriteText_Left_7(void);
void WriteText_Left_8 (uint8_t , uint8_t , uint8_t*);
//void WriteText_Left_8_SubRedraw (uint8_t Position, uint8_t _Bold, uint8_t *content) ;
void WriteText_Left_9 (uint8_t, uint16_t, uint8_t*);
void WriteText_Left_10( uint16_t );
void WriteText_Left_11(void);
void WriteText_Middle_0(void);
void WriteText_Middle_1(void);//divide to middle 10 and 11
void WriteText_Middle_2(uint8_t*);//Middle
void WriteText_Middle_3(uint16_t);
void WriteText_Middle_4(void);//divide to middle 12 and 13
void WriteText_Middle_5(uint16_t, uint8_t *);
void WriteText_Middle_6(uint8_t *);
void WriteText_Middle_7(void);
void WriteText_Middle_8(void);
void WriteText_Middle_9(void);
void WriteText_Middle_10(uint16_t);
void WriteText_Middle_11(uint16_t);
void WriteText_Middle_12(uint16_t);
void WriteText_Middle_13(uint16_t);
void WriteText_Middle_14(uint8_t*);
void WriteText_Middle_15(void);
void WriteText_Middle_16(uint8_t , uint16_t );
void WriteText_Middle_17(void);
void WriteText_Right_0(void);
void WriteText_Right_1(uint8_t*, uint16_t );
void WriteText_Right_2(void);
void WriteText_Right_3(void);
void WriteText_Right_4(void);
void WriteText_Right_5(uint8_t *, uint16_t, uint16_t);
void WriteText_Right_6(uint8_t *);
void WriteText_Right_7(uint8_t *);
void WriteText_Right_8(void);
void WriteText_Right_9(void);
void WriteText_Right_10(void);
void WriteText_Right_11(uint8_t * );
void WriteText_Right_12(void);
void WriteText_Right_13(uint16_t , uint8_t*);
void WriteText_Right_14(uint16_t, uint16_t);
void WriteText_Right_15(void);
void WriteText_Right_16(void);//Remember fix buffer extracly xxx
void WriteText_Right_17 (uint8_t , uint8_t *,uint16_t, uint16_t);//
void WriteText_Right_18(void);//H11A, H11B
void WriteText_Right_19(uint16_t , uint8_t *  );
void WriteText_Right_20(uint16_t , uint16_t , uint8_t *);
void WriteText_Right_21(void);
void WriteText_Right_22(void);
void WriteText_Right_23(uint16_t , uint8_t *  );

//Protoype use to background
void prepare_PO2num(uint8_t*);
void prepare_BrightNessNum(uint8_t*);
void prepare_FO2num(uint8_t *);
//void prepare_FO2num(void);
u8* FO2_String(u8 FO2Value) ;
void FO2PreviewProcess(void);
u8* PO2_String(u8 FO2Value, float) ;
void prepare_O2num(uint8_t *, uint8_t )         ;
void prepare_NDCNum(uint8_t *, uint8_t);
void prepare_EDTNum(uint8_t *, uint8_t);
void prepare_DTRNum(uint8_t *, uint8_t) ;
void prepare_TLBGnum(uint8_t *, uint8_t ) ;
void prepare_DepthNum(uint8_t *, uint8_t );
void prepare_totalDiveTimeNum(void);
void prepare_LastElapseDiveTime(void);
void Prepare_MaxDiveTime(void);
void prepare_aveDiveNum(uint8_t*, uint8_t);
void prepare_maxDepth(uint8_t*, uint8_t);
void prepare_aveDepthnum(uint8_t*, uint8_t );
void prepare_lowestTempNum(void);
u8 AltitudeProcess(u8);
void Prepare_Altitude(void);
void prepare_temper();
void prepare_FLYtime(uint8_t*);
void prepare_DESATTime(uint8_t*);
void prepare_SampleRate(uint8_t*);
void prepare_PressNum(uint8_t*, u16, u8);
void prepare_TurnEndAlarm(uint8_t *buf, u16  TURNAlarm);
void ProcessSerialNum(void);
void ProcessBluetoothNum(void);
void ProcessResetCode(void);
void ProcessFirmwareRev(void);//Process Firmware Revision
void prepare_time(uint8_t*, uint8_t);
void prepare_Midnight(uint8_t);
void prepare_TL(void);
void prepare_AR(void);
void prepare_divetime(uint8_t*, uint8_t);
void prepare_GTRnum(uint8_t*);
void prepare_AIRnum(uint8_t*, uint8_t);
void prepare_battery(void);
void prepare_surtime(void);
//uint8_t* MD_type(uint8_t);
//uint8_t* MD_type_1(uint8_t flag);
void Process_DMY_data(uint8_t flag);
void Process_DMY_data_1(void);
uint8_t* hr_type_1(uint8_t flag);//AM,PM or military type
uint8_t* hr_type_2(uint8_t flag);//12hr or 24hr type
uint8_t* OnOffStr(uint8_t flag);
uint8_t* UnitType_1(uint8_t flag);
uint8_t* UnitType_2(uint8_t flag);
//uint8_t* DsatStr(uint8_t flag);
//uint8_t* WaterTypeStr(uint8_t flag);
//uint8_t* DeclineString(uint8_t flag);
void ProcessAutoDimBright(void);
void ProcessDecline_2(void);
void ProcessDecline_1(void);
u16 LenString(tChar*, u8*);
u8* GAS_Str(void);
//void Display_FO2Num(void);
//void Display_PO2Num(void);
void PSIvsGTR_Display(void);
void ProcessCountDown(void);//Countdown bluetooth number
u8 FO2_ReturnNum(void);
u8 PO2_ReturnNum(void);
u8* SafetyStopPrepare(void);
u8 ALARM_SET_Flag(void);
void LogStartTime_String(void);
void LogDiveTime_String(void);
void LCD_DisplayChar(uint16_t Column, uint16_t Line, uint8_t Ascii);
#endif
