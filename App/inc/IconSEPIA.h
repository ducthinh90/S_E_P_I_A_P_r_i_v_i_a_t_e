

#ifndef _ICON_SEPIA_H__
#define _ICON_SEPIA_H__
#include "fonts.h"
#include "stm322xg_eval_lcd.h"
#include "OCSepia.h"
#include "backgrounds.h"
typedef enum{
      Icon_TopBar_Battery,
      Icon_TopBar_Clock,
      Icon_TopBar_DesatTime,
      Icon_TopBar_FlyTime,
      Icon_TopBar_Temper,
      Icon_BottomBar_ArrowLeft,
      Icon_BottomBar_ArrowUp,
      Icon_BottomBar_ArrowDown,
      Icon_BottomBar_Select,
      Icon_HomeMenu_GoDive,
}IconName;

/*Icon status*/
typedef enum{
  UnSelect  = 0,  
  Select    = 1
 }IconStatus;

/*Icon*/
typedef struct{
  IconName    _IconName;
  IconStatus  _IconStatus;
}IconSepiaTypedef;

/*Icon prototype*/
/*Draw icon for SEPIA*/
void DrawIcon(IconName, IconStatus);
#endif
