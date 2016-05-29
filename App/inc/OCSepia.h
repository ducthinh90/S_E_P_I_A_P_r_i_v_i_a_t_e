/******************************************************************************/
//File: OCSepia.h
//Description:Operation code for SEPIA from TI to ST
//Created by:DucThinh
//History: 11/29/2015 Created
//
/*****************************************************************************/
#ifndef _OPCODE_SEPIA_H__
#define _OPCODE_SEPIA_H__

/*OPERATION CODE OF SEPIA*/
typedef enum{
  OC_SleepMode                         = 0x00,
  OC_MyInfoData                        = 0x01,
  OC_PLANData                          = 0x02,
  OC_LOGData                           = 0x03,
  OC_NIO2Data                          = 0x05,
  OC_SAVE                              = 0x06,
  OC_CLEAR                             = 0x07,
  OC_USBWaitForTheConnection           = 0x08,
  OC_USB120SecCountingDown             = 0x0A,
  OC_USBConnectionMade                 = 0x0B,
  OC_USBDataDownloadInProgress         = 0x0C,
  OC_USBDataUploadInProgress           = 0x0D,
  OC_USBUpdatingFirmware               = 0x0F,
  OC_SurfaceMode                       = 0x10,
  OC_ConditionalViolationOnSurface     = 0x11,
  OC_PlanMode                          = 0x12,
  OC_LogMode                           = 0x13,
  OC_SetGasMenu                        = 0x15,
  OC_SetAlarmMenu                      = 0x16,
  OC_SetUtilitiesMenu                  = 0x17,
  OC_SetTMTMenu                        = 0x18,
  OC_GaugeSwitchTMTMenu                = 0x19,
  OC_SonarMenu                         = 0x1A,
  OC_SonarMode                         = 0x1B,
  OC_CompassMode                       = 0x1C,
  OC_NormSwitchGasMenu                 = 0x1D,
  OC_DiveMenu                          = 0x1E,//Norm/Gauge/DS/DECO Dive Menu
  OC_DiveMode                          = 0x1F,
  OC_HomeMenu                          = 0x20,
  OC_HomeSetupMenu                     = 0x21,
  OC_SetDateTimeMenu                   = 0x22,
  OC_NavigationMenu                    = 0x23
 }OCNum;

/*MAIN STATUS OF SEPIA (Buffer 5th)*/
/* HOME MENU STATUS (0x20):
    1.HISTORY
    2.OP MODE
    3.SETTINGS
    4.NAVIGATION
    5.GO DIVE
    6.LOG
    7.MY INFO
    8.SEPIA INFO
    9.TMT STATUS  */
    
typedef enum  {
  HMS_HistorySelect     = 0x10,
  HMS_HistoryEnter,
  HMS_OpModeSelect      = 0x20,
  HMS_OpModeEnter,
  HMS_SettingSelect     = 0x30,
  HMS_SettingEnter,
  HMS_NavigationSelect  = 0x40,
  HMS_NavigationEnter,
  HMS_GoDiveSelect      = 0x50,
  HMS_GoDiveEnter,
  HMS_LogSelect         = 0x60,
  HMS_LogEnter,
  HMS_MyInfoSelect      = 0x70,
  HMS_MyInfoEnter,
  HMS_SepiaInfoSelect   = 0x80,
  HMS_SepiaInfoEnter,
  HMS_TMTStatusSelect   = 0x90,
  HMS_TMTStatusEnter
}Home_Menu_Status;

/*HOME SETTINGS (0x21)
  1.  SET GASES
  2.  SET TMT
  3.  BLUETOOTH
  4.  DATE & TIME
  5.  BRIGHTNESS
  6.  UTILITIES
  7.  ALARMS
  8.  SET COMPASS
  9.  Clear NI-O2   */
typedef enum{
  HSS_SetGasSelect        = 0x10,
  HSS_SetGasEnter,
  HSS_SetTMTSelect        = 0x20,
  HSS_SetTMTEnter,
  HSS_BluetoothSelect     = 0x30, 
  HSS_BluetoothEnter,
  HSS_DateTimeSelect      = 0x40,
  HSS_DateTimeEnter,       
  HSS_BrigthnessSelect    = 0x50,
  HSS_BrightnessEnter,     
  HSS_UtilitiesSelect     = 0x60,
  HSS_UtilitiesEnter,      
  HSS_AlarmSelect         = 0x70,
  HSS_AlarmEnter,          
  HSS_SetCompassSelect    = 0x80,
  HSS_SetComapssEnter,
  HSS_ClearNiO2Select     = 0x90,
 HSS_ClearNiO2Enter
}Home_Setting_Status;
/*
SET DATE TIME (22H)
1. DATE FORMAT
2. TIME FORMAT
3. SET DATE
4. SET TIME
*/
typedef enum{
  SDTS_DateSelect         = 0x10,
  SDTS_DateEnter,
  SDTS_TimeSelect         = 0x20,
  SDTS_TimeEnter,
  SDTS_SetDateSelect      = 0x30,
  SDTS_SetDateEnter,
  SDTS_SetTimeSelect      = 0x40,
  SDTS_SetTimeEnter
 }Set_Date_Time_Status;

/*
SET GASES MENU
1. GAS 1
2. GAS 2
3. GAS 3
4. GAS 4
5. 50% default
*/
typedef enum{
  SGMS_Gas1Select       = 0x10,
  SGMS_Gas1Enter,
  SGMS_Gas2Select       = 0x20,
  SGMS_Gas2Enter,
  SGMS_Gas3Select       = 0x30,
  SGMS_Gas3Enter,
  SGMS_Gas4Select       = 0x40,
  SGMS_Gas4Enter,
  SGMS_50DefaultSlect   = 0x50,
  SGMS_50DefaultEnter
}Set_Gases_Menu_Status;
/*
SET TMT MENU
1. TMT 1
2. TMT 2
3. TMT 3
4. TMT 4
*/
typedef enum{
    STMTS_TMT1Select   = 0x10,
    STMTS_TMT1Enter,
    STMTS_TMT2Select   = 0x20,
    STMTS_TMT2Enter,
    STMTS_TMT3Select   = 0x30,
    STMTS_TMT3Enter,
    STMTS_TMT4Select   = 0x40,
    STMTS_TMT4Enter,
}Set_TMT_Menu_Status;
/*
SET ALARMS MENU (16H)
1. Audible Alarm
2. Depth Alarm
3. EDT Alarm
4. DTR Alarm
5. TLBG Alarm
6. Turn Alarm
7. End Alarm
*/
typedef enum{
  SAMS_AudibleAlarmSelect   = 0x10,
  SAMS_AudibleAlarmEnter,
  SAMS_DepthAlarmSelect     = 0x20,
  SAMS_DepthAlarmEnter,
  SAMS_EDTAlarmSelect       = 0x30,
  SAMS_EDTAlarmEnter,
  SAMS_DTRAlarmSelect       = 0x40,
  SAMS_DTRAlarmEnter,
  SAMS_TLBGAlarmSelect      = 0x50,
  SAMS_TLBGAlarmEnter,
  SAMS_TurnAlarmSelect      = 0x60,
  SAMS_TurnAlarmEnter,
  SAMS_EndAlarmSelect       = 0x70,
  SAMS_EndAlarmEnter
} Set_Alarm_Menu_Status;
/*
NORM SET UTILITIES MENU 17H
  1. Units
  2. Water type
  3. Deep Stop
  4. Safety Stop
  5. Algorithm
  6. Conservative
  7. Sample rate
*/
typedef enum{
    NSUMS_UnitsSelect           = 0x10,
    NSUMS_UnitsEnter,
    NSUMS_WaterTypeSelect       = 0x20,
    NSUMS_WaterTypeEnter,
    NSUMS_DeepStopSelect        = 0x30,
    NSUMS_DeepStopEnter,
    NSUMS_SafetyStopSelect      = 0x40,
    NSUMS_SafetyStopEnter,  
    NSUMS_AlgorithmSelect       = 0x50,
    NSUMS_AlgorithmEnter,
    NSUMS_ConservativeSelect    = 0x60,
    NSUMS_ConservativeEnter,
    NSUMS_SampleRateSelect      = 0x70,
    NSUMS_SampleRateEnter
}Norm_Set_Utilities_Menu_Status;
/*
NAVIGATION MENU 23H
1. Set ID
2. Channel
3. Set SMS
4. NAV Mode
5. PAIRING
6. Partners
*/
typedef enum{
    NMS_SetIDSelect     = 0x10,
    NMS_SetIDEnter,
    NMS_ChannelSelect   = 0x20,
    NMS_ChannelEnter,
    NMS_SetSMSSelect    = 0x30,
    NMS_SetSMSEnter,
    NMS_NAVModeSelect = 0x40,
    NMS_NAVModeEnter,
    NMS_PAIRINGSelect   = 0x50,
    NMS_PAIRINGEnter,
    NMS_PartnersSelect  = 0x60,
    NMS_PartnersEnter,
}Navigation_Menu_Status;

#endif
