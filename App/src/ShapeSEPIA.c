/******************************************************************************/
//File: ShapeSEPIA.c
//Description:Shape for SEPIA
//Created by:DucThinh
//History: 1/19/2016 Created
//
/*****************************************************************************/

#include "ShapeSEPIA.h"
void DrawShape(ShapeName ShapeName_) {
    switch(ShapeName_) {
    case Shape_TopBar:
        LCD_FillRect(70, 0, 250, 20, LCD_COLOR_WHITE);
        LCD_FillRect(0, 0, 70, 20, 0x07FF);
        break;
    case Shape_BottomBar:
        LCD_FillRect(0, 220, 320, 20, LCD_COLOR_WHITE);
        break;
    }
}