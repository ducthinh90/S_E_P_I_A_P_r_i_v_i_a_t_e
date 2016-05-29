#ifndef HANDLE_BUTTONS_H
#define HANDLE_BUTTONS_H

void initButtons(GPIO_InitTypeDef *GPIO_InitStructure, EXTI_InitTypeDef *EXTI_InitStructure, NVIC_InitTypeDef *NVIC_InitStructure);
void Timer2_Init(void);
void Timer2_Start(void);
void Timer2_Stop(void);


#endif



