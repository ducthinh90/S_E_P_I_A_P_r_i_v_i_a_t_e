/******************************************************************************/
//File: IconSEPIA.c
//Description:Icon for SEPIA
//Created by:DucThinh
//History: 1/29/2016 Created
//
/*****************************************************************************/
#include "IconSEPIA.h"
#include "Image_TopBar_Clock.c"
#include "Image_TopBar_Batterry.c"
#include "Image_TopBar_FlyTime.c"
#include "Image_TopBar_Temper.c"
#include "Image_TopBar_DesatTime.c"
#include "Image_BottomBar_ArrowUp.c"
#include "Image_BottomBar_ArrowLeft.c"
#include "Image_BottomBar_Select.c"
#include "Image_HomeMenu_GoDive.c"
/*External variables*/

/*------------------------------------------------------------------------------------*/
void DrawIcon(IconName _IconName, IconStatus _Status) {
    LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_WHITE);
    switch (_IconName) {
    case Icon_TopBar_Clock:
        LCD_DrawChar(3, (20-Image_TopBar_Clock.height)/2, (ptImage)&Image_TopBar_Clock);
        break;
    case Icon_TopBar_Battery:
        LCD_DrawBMP(297, (20-Image_TopBar_Battery.height)/2, (ptImage)&Image_TopBar_Battery, 0);
        break;
    case Icon_TopBar_FlyTime:
        LCD_DrawBMP(142, (20-Image_TopBar_FlyTime.height)/2, (ptImage)&Image_TopBar_FlyTime, 0);
        break;
    case Icon_TopBar_Temper:
        LCD_DrawBMP(214, (20-Image_TopBar_Temper.height)/2, (ptImage)&Image_TopBar_Temper, 0);
        break;
    case Icon_TopBar_DesatTime:
        LCD_DrawBMP(74, (20-Image_TopBar_DesatTime.height)/2, (ptImage)&Image_TopBar_DesatTime, 0);
        break;
    case Icon_BottomBar_ArrowUp:
        LCD_DrawBMP(112, ((20-Image_BottomBar_ArrowUp.height)/2)+220, (ptImage)&Image_BottomBar_ArrowUp, 0);
        break;
    case Icon_BottomBar_ArrowDown:
        LCD_DrawBMP(185, ((20-Image_BottomBar_ArrowUp.height)/2)+220, (ptImage)&Image_BottomBar_ArrowUp, 2);
        break;
    case Icon_BottomBar_ArrowLeft:
        LCD_DrawBMP(40, ((20- Image_BottomBar_ArrowLeft.height)/2)+220, (ptImage)&Image_BottomBar_ArrowLeft, 0);
        break;
    case Icon_BottomBar_Select:
        LCD_DrawBMP(258, ((20-Image_BottomBar_Select.height)/2)+220, (ptImage)&Image_BottomBar_Select, 0);
        break;
    case Icon_HomeMenu_GoDive:
        switch(_Status) {
        case Select:
            LCD_SetColors(Black, White);
            LCD_FillRect(26, 30, 57, 57, Blue);
            break;
        default:
            LCD_SetColors(White, Black);
            LCD_FillRect(26, 30, 57, 57, Black);
            break;
        }
        LCD_DrawChar((26+((57-Image_HomeMenu_GoDive.width)/2)), 34,(ptImage)&Image_HomeMenu_GoDive);
        break;
    default:
        LCD_FillRect(0, 120, 120, 3, LCD_COLOR_RED);//Error notification
        break;
    }
}
