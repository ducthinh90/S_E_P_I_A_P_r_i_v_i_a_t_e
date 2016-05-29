


#include "alldefs.h" // all defines


// ------------------------------------------------------------------------
// flash spi
// ------------------------------------------------------------------------
void flashMemCfg(void);
uint8_t sFLASH_SendByte(uint8_t);
uint8_t sFLASH_ReadByte(void);
uint8_t spiWait(void);

#ifdef BOARD_TYPE_1
#define FLASH_MEM_CS_L GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define FLASH_MEM_CS_H GPIO_SetBits(GPIOA, GPIO_Pin_4)
#endif
#ifdef BOARD_TYPE_2
#define FLASH_MEM_CS_L GPIO_ResetBits(GPIOB, GPIO_Pin_9)
#define FLASH_MEM_CS_H GPIO_SetBits(GPIOB, GPIO_Pin_9)
#endif
#ifdef BOARD_TYPE_3
#define FLASH_MEM_CS_L GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define FLASH_MEM_CS_H GPIO_SetBits(GPIOA, GPIO_Pin_4)
#endif



#define MaxNumPage 32768
#define MaxPageSize 128//128 of 2bytes
#define START_PAGE_BOLD22  35
uint8_t sFLASH_SendByte(uint8_t byte);

uint8_t sFLASH_ReadByte(void);

void sFLASH_ReadBytes(int numToRead);

void sFLASH_SendData(uint8_t * f_data, uint16_t len, uint16_t page);
void sFLASH_ReadData(uint16_t * f_data, uint16_t len, uint16_t page);
void sFLASH_ErasePage(void);
uint8_t sFLASH_Send2Byte(uint16_t byte);
void sFLASH_SendData2Byte(uint16_t * f_data, uint16_t len, uint16_t page);

void StoreFont_16Bold(void);
void Spi_senddata(uint8_t * f_data, uint16_t len);
void spiWait1(void) ;
uint16_t sFLASH_readpixel(uint16_t page, uint16_t offset);