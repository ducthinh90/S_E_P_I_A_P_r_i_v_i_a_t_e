/**
  ******************************************************************************
  * @file    fonts.h
  * @author  MCD Application Team
  * @version V5.0.2
  * @date    05-March-2012
  * @brief   Header for fonts.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FONTS_H
#define __FONTS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup STM32_EVAL
  * @{
  */

/** @addtogroup Common
  * @{
  */

/** @addtogroup FONTS
  * @{
  */

/** @defgroup FONTS_Exported_Types
  * @{
  */

typedef struct
{
    const uint16_t *_data;
    uint16_t width;
    uint16_t height;
} tImage, *ptImage;

typedef struct
{
    uint16_t _code;
    const tImage *image;
} tChar, *ptChar;

//typedef struct
//{
//   int length;
//  const tChar *chars;
//} tFont;






/**
  * @}
  */

/** @defgroup FONTS_Exported_Constants
  * @{
  */
//#define LINE(x) ((x) * (((tImage* )LCD_GetFont())->Height))

/**
  * @}
  */

/** @defgroup FONTS_Exported_Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup FONTS_Exported_Functions
  * @{
  */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __FONTS_H */

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/