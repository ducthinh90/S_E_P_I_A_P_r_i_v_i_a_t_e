#ifndef GPIO_H
#define GPIO_H




void initGPIO(GPIO_InitTypeDef *GPIO_InitStructure);
void setIOasOUTPUT(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void setIOasSPI(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
#endif



