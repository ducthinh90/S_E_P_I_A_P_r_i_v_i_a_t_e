/******************************************************************************/
//File: ShapeSEPIA.h
//Description:Prototype and macro shape for SEPIA
//Created by:DucThinh
//History: 1/19/2016 Created
/*****************************************************************************/
#ifndef _SHAPE_SEPIA_H
#define _SHAPE_SEPIA_H
#include "stm322xg_eval_lcd.h"

typedef enum{
  Shape_TopBar,
  Shape_BottomBar,    
}ShapeName;
/*Prototype*/
void DrawShape(ShapeName);
#endif
