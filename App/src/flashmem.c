/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: handle flash memory
// Timing:  http://prntscr.com/3l9u3w
/****************************************************************/

#include "alldefs.h" // all defines
#include "stm32f2xx_spi.h"
#include "flashmem.h"
#include "stopWatch.h"
#include "gpio.h"


// spi flash memory variables
unsigned long spi_dummy;
uint8_t spi_dat[100];
uint16_t spi_page;
uint8_t spi_byte;
uint16_t spiTimeOutCtr;
uint8_t mfg_id;
uint8_t dev_id1;
uint8_t dev_id2;
uint16_t f_data_w[25];
uint16_t f_data_d[128];
uint16_t f_data_d2[128];
uint16_t f_data_d3[128];
uint16_t f_data_d4[128];
static uint16_t page = 0;//Always smaller than 32.768
static const uint8_t f_chiperase[4] = {0xc7, 0x94, 0x80, 0x9a};
//static const uint8_t f_pagerase[4] = {0x81, 0x00, 0x00, 0x00};
extern const tChar *FontSet;
extern const tChar myriad_bold_45[];
extern const tChar myriad_bold_9[];
extern const tChar myriad_bold_11[];
extern const tChar myriad_bold_12[];
const tImage *CurrentChar;
extern const tImage* getCharImage(uint16_t i);


#if 0
static const uint16_t image_data_0x20_t[42] = {
    0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff
};
#endif

/**
  * @brief  Sends a byte through the SPI interface and return the byte received
  *         from the SPI bus.
  * @param  byte: byte to send.
  * @retval The value of the received byte.
  */
void sFLASH_ErasePage(void)
{

    /*
        spiWait();
        spi_byte = page;
        spi_page = page;
        FLASH_MEM_CS_L;
        sFLASH_SendByte(0x81);
        sFLASH_SendByte(spi_page >> 8);
        sFLASH_SendByte(spi_page);
        sFLASH_SendByte(spi_byte);

        FLASH_MEM_CS_H;


     */
//spiWait();
    Spi_senddata((uint8_t*)f_chiperase, 4);
}

void Spi_senddata(uint8_t * f_data, uint16_t len)
{
    uint16_t i = 0;
    spiWait();
    FLASH_MEM_CS_L;

    for(i=0; i<len; i++)
    {
        sFLASH_SendByte(f_data[i]);
    }
    FLASH_MEM_CS_H;
}
uint8_t sFLASH_SendByte(uint8_t byte)
{
#ifdef BOARD_TYPE_1
    /*!< Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPI1, byte);

    /*!< Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

    /*!< Return the byte read from the SPI bus */
    return SPI_I2S_ReceiveData(SPI1);
#endif
#ifdef BOARD_TYPE_2
    /*!< Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPI2, byte);

    /*!< Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

    /*!< Return the byte read from the SPI bus */
    return SPI_I2S_ReceiveData(SPI2);
#endif
#ifdef BOARD_TYPE_3
    /*!< Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPI1, byte);

    /*!< Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

    /*!< Return the byte read from the SPI bus */
    return SPI_I2S_ReceiveData(SPI1);
#endif

}

/**
  * @brief  Sends a byte through the SPI interface and return the byte received
  *         from the SPI bus.
  * @param  byte: byte to send.
  * @retval The value of the received byte.
  */
uint8_t sFLASH_Send2Byte(uint16_t byte)
{
    uint8_t low_byte,high_byte;

    low_byte = byte&0x00ff;
    high_byte = byte>>8;

#ifdef BOARD_TYPE_1
    /*!< Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPI1, high_byte);

    /*!< Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

    /*!< Return the byte read from the SPI bus */
    SPI_I2S_ReceiveData(SPI1);

    /*!< Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPI1, low_byte);

    /*!< Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

    /*!< Return the byte read from the SPI bus */
    return SPI_I2S_ReceiveData(SPI1);
#endif


#ifdef BOARD_TYPE_3
    /*!< Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPI2, high_byte);

    /*!< Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

    /*!< Return the byte read from the SPI bus */
    SPI_I2S_ReceiveData(SPI2);

    /*!< Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPI2, low_byte);

    /*!< Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

    /*!< Return the byte read from the SPI bus */
    return SPI_I2S_ReceiveData(SPI2);
#endif


#ifdef BOARD_TYPE_3
    /*!< Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPI1, high_byte);

    /*!< Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

    /*!< Return the byte read from the SPI bus */
    SPI_I2S_ReceiveData(SPI1);

    /*!< Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPI1, low_byte);

    /*!< Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

    /*!< Return the byte read from the SPI bus */
    return SPI_I2S_ReceiveData(SPI1);
#endif


}
/**
  * @brief  Reads a byte from the SPI Flash.
  * @note   This function must be used only if the Start_Read_Sequence function
  *         has been previously called.
  * @param  None
  * @retval Byte Read from the SPI Flash.
  */
uint8_t sFLASH_ReadByte(void)
{
    return (sFLASH_SendByte(0x00));
}

/**
  * function for reading many bytes at once
  */
void sFLASH_ReadBytes(int numToRead)
{
    int ctr = 0;
    while(ctr < numToRead)
    {
#ifdef BOARD_TYPE_1
        /*!< Loop while DR register in not emplty */
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

        /*!< Send byte through the SPI1 peripheral */
        SPI_I2S_SendData(SPI1, 0x00);

        /*!< Wait to receive a byte */
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

        /*!< Return the byte read from the SPI bus */
        spi_dat[ctr] = SPI_I2S_ReceiveData(SPI1);
#endif
#ifdef BOARD_TYPE_2
        /*!< Loop while DR register in not emplty */
        while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

        /*!< Send byte through the SPI1 peripheral */
        SPI_I2S_SendData(SPI2, 0x00);

        /*!< Wait to receive a byte */
        while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

        /*!< Return the byte read from the SPI bus */
        spi_dat[ctr] = SPI_I2S_ReceiveData(SPI2);
#endif
#ifdef BOARD_TYPE_3
        /*!< Loop while DR register in not emplty */
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

        /*!< Send byte through the SPI1 peripheral */
        SPI_I2S_SendData(SPI1, 0x00);

        /*!< Wait to receive a byte */
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

        /*!< Return the byte read from the SPI bus */
        spi_dat[ctr] = SPI_I2S_ReceiveData(SPI1);
#endif

        ctr += 1;
    }
}


/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: wait for ready
// INPUTs: n/a
// OUTPUTs: return whether loop was killed
// HW DEPEDANCIES: 25MHz xtal on board, ST STM32F207ZG
// SW DEPENDENCIEs: n/a
/****************************************************************/
uint8_t spiWait(void)
{
    spiTimeOutCtr = 0;
    do {
        FLASH_MEM_CS_L;
        //stopwatch_delay(60); // 0.5us @ 120Mhz
        spi_dat[0] = sFLASH_SendByte(0xD7); // read status register
        FLASH_MEM_CS_H;
        spiTimeOutCtr += 1;
    } while(((spi_dat[0] & BIT7) != BIT7) && (spiTimeOutCtr < 5000));

    if(spiTimeOutCtr < 5000)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void spiWait1(void) {
    FLASH_MEM_CS_L;
//stopwatch_delay(60); // 0.5us @ 120Mhz
    while (((sFLASH_SendByte(0xD7)) >> 7) != 0x01) {
    }

    FLASH_MEM_CS_H;
}
/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: setup flash memory
// INPUTs:
// OUTPUTs:
// HW DEPEDANCIES:
/****************************************************************/
void flashMemCfg(void)
{
    SPI_InitTypeDef SPI_InitStruct;
#ifdef BOARD_TYPE_1
    // SPI flash
    /*
      AT45DB641E flash memory
      64Mbit = 8MB
      32768 pages, 256 bytes per page
      page erase (256 bytes), block erase (2kb), sector erase (256 kB), or chip erase (8MB)
      deep power down mode available
      - Verification: http://prntscr.com/3l308c
      PC4 - RESET
      PA4 - CS
      PA5 - SCLK
      PA6 - MISO
      PA7 - MOSI
    */
    setIOasOUTPUT(GPIOC, GPIO_Pin_4);
    GPIO_SetBits(GPIOC, GPIO_Pin_4); // make RESET pin high
    setIOasOUTPUT(GPIOA, GPIO_Pin_4);
    GPIO_SetBits(GPIOA, GPIO_Pin_4); // make SS pin high
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
    setIOasSPI(GPIOA, GPIO_Pin_5);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
    setIOasSPI(GPIOA, GPIO_Pin_6);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
    setIOasSPI(GPIOA, GPIO_Pin_7);
    SPI_I2S_DeInit(SPI1);
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; // 30 mhz
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_Init(SPI1, &SPI_InitStruct);
    SPI_Cmd(SPI1, ENABLE);
#endif
#ifdef BOARD_TYPE_2
    // SPI flash
    /*
      AT45DB641E flash memory
      64Mbit = 8MB
      32768 pages, 256 bytes per page
      page erase (256 bytes), block erase (2kb), sector erase (256 kB), or chip erase (8MB)
      deep power down mode available
      - Verification: http://prntscr.com/3l308c
      PC1 - RESET
      PB9 - CS
      PB10 - SCLK
      PC2 - MISO
      PC3 - MOSI
    */
    setIOasOUTPUT(GPIOC, GPIO_Pin_1);
    GPIO_SetBits(GPIOC, GPIO_Pin_1); // make RESET pin high
    setIOasOUTPUT(GPIOB, GPIO_Pin_9);
    GPIO_SetBits(GPIOB, GPIO_Pin_9); // make SS pin high
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_SPI2);
    setIOasSPI(GPIOB, GPIO_Pin_10);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource2, GPIO_AF_SPI2);
    setIOasSPI(GPIOC, GPIO_Pin_2);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF_SPI2);
    setIOasSPI(GPIOC, GPIO_Pin_3);
    SPI_I2S_DeInit(SPI2);
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; // 30 mhz
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_Init(SPI2, &SPI_InitStruct);
    SPI_Cmd(SPI2, ENABLE);
#endif
#ifdef BOARD_TYPE_3
    // SPI flash
    /*
      AT45DB641E flash memory
      64Mbit = 8MB
      32768 pages, 256 bytes per page
      page erase (256 bytes), block erase (2kb), sector erase (256 kB), or chip erase (8MB)
      deep power down mode available
      - Verification: http://prntscr.com/3l308c
      PC4 - RESET
      PA4 - CS
      PA5 - SCLK
      PA6 - MISO
      PA7 - MOSI
    */
    setIOasOUTPUT(GPIOC, GPIO_Pin_4);
    GPIO_SetBits(GPIOC, GPIO_Pin_4); // make RESET pin high
    setIOasOUTPUT(GPIOA, GPIO_Pin_4);
    GPIO_SetBits(GPIOA, GPIO_Pin_4); // make SS pin high
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
    setIOasSPI(GPIOA, GPIO_Pin_5);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
    setIOasSPI(GPIOA, GPIO_Pin_6);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
    setIOasSPI(GPIOA, GPIO_Pin_7);
    SPI_I2S_DeInit(SPI1);
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; // 30 mhz
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_Init(SPI1, &SPI_InitStruct);
    SPI_Cmd(SPI1, ENABLE);
#endif

    // read mfg id
    spiWait();
    FLASH_MEM_CS_L;
    sFLASH_SendByte(0x9F);
    mfg_id = sFLASH_ReadByte();
    dev_id1 = sFLASH_ReadByte();
    dev_id2 = sFLASH_ReadByte();
    FLASH_MEM_CS_H;

    // configure device for 256 bytes per page
    spiWait();
    FLASH_MEM_CS_L;
    sFLASH_SendByte(0x3d);
    sFLASH_SendByte(0x2A);
    sFLASH_SendByte(0x80);
    sFLASH_SendByte(0xA6);
    FLASH_MEM_CS_H;


    setIOasOUTPUT(GPIOF, GPIO_Pin_14);
    /*
            stopwatch_delay(60000000);
    //sFLASH_ErasePage();
    	spiWait();
       setIOasOUTPUT(GPIOF, GPIO_Pin_14);
    //StoreFont_16Bold();
       stopwatch_delay(60000000);

       sFLASH_ReadData(f_data_d,128,6);

       sFLASH_ReadData(f_data_d2,128,7);
          sFLASH_ReadData(f_data_d3,128,8);

       sFLASH_ReadData(f_data_d4,128,364);
        spiWait();
    GPIO_SetBits(GPIOF, GPIO_Pin_14);
    */
}

void sFLASH_SendData(uint8_t * f_data, uint16_t len, uint16_t page)
{
    uint16_t i , f_byte;
    spiWait();
    f_byte = 0;
    //spi_page = 0x0000;
    FLASH_MEM_CS_L;
    sFLASH_SendByte(0x58);
    sFLASH_SendByte(page >> 8);
    sFLASH_SendByte(page);
    sFLASH_SendByte(spi_byte);
    sFLASH_SendByte(f_byte);

    for(i = 0; i<len; i++)
    {
        sFLASH_SendByte(f_data[i]);
    }
    FLASH_MEM_CS_H;

}
void sFLASH_ReadData(uint16_t * f_data, uint16_t len, uint16_t page)
{
    uint16_t f_dummy;

    int ctr = 0;
    uint16_t low_byte = 0;
    uint16_t high_byte = 0;
    uint16_t _spi_byte=0;
    spiWait();
    f_dummy = 0x00;
    FLASH_MEM_CS_L;
    sFLASH_SendByte(0x0B);
    sFLASH_SendByte(page >> 8);
    sFLASH_SendByte(page);
    sFLASH_SendByte(_spi_byte);
    sFLASH_SendByte(f_dummy);

    //  sFLASH_ReadBytes(len);

    while(ctr < len)
    {
#ifdef BOARD_TYPE_1
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        SPI_I2S_SendData(SPI1, 0x00);
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
        low_byte= SPI_I2S_ReceiveData(SPI1);

        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        SPI_I2S_SendData(SPI1, 0x00);
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
        high_byte= SPI_I2S_ReceiveData(SPI1);

#endif

#ifdef BOARD_TYPE_2
        while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
        SPI_I2S_SendData(SPI2, 0x00);
        while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
        low_byte= SPI_I2S_ReceiveData(SPI2);

        while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
        SPI_I2S_SendData(SPI2, 0x00);
        while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
        high_byte= SPI_I2S_ReceiveData(SPI2);

#endif

#ifdef BOARD_TYPE_3
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        SPI_I2S_SendData(SPI1, 0x00);
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
        low_byte= SPI_I2S_ReceiveData(SPI1);

        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        SPI_I2S_SendData(SPI1, 0x00);
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
        high_byte= SPI_I2S_ReceiveData(SPI1);

#endif

        f_data[ctr] = (low_byte<<8)|high_byte;

        ctr += 1;

    }

    FLASH_MEM_CS_H;

}






void sFLASH_SendData2Byte(uint16_t * f_data, uint16_t len, uint16_t page)
{
    uint16_t i , f_byte;
    spiWait();
    f_byte = 0;
    FLASH_MEM_CS_L;
    sFLASH_SendByte(0x58);
    sFLASH_SendByte(page >> 8);
    sFLASH_SendByte(page);
    sFLASH_SendByte(f_byte);
    for(i = 0; i<len; i++)
    {
        sFLASH_Send2Byte(f_data[i]);
    }
    FLASH_MEM_CS_H;
    spiWait();
}
//Store one character which defined the size and the first element in the array

void StoreCharacterToPage(const uint16_t* dataFont, uint16_t Size)
{
    while((page < MaxNumPage) && (Size != 0))
    {
        if(Size <= 128)
        {
            sFLASH_SendData2Byte((uint16_t*)dataFont, Size, page++);
            spiWait();
            break;
        }
        else
        {
            sFLASH_SendData2Byte((uint16_t*)dataFont, MaxPageSize, page++);
            spiWait();
            Size -=128;
            dataFont +=128;
        }

    }
}
void StoreFont_16Bold(void)
{
    uint16_t i = 0;
    FontSet = myriad_bold_12; //&(myriad_bold_12);
    for(i=0; i < 96; i++)
    {
        CurrentChar = getCharImage(i);
        //StoreCharacterToPage(CurrentChar->_data, CurrentChar->size);
    }
}
//StoreCharacterToPage(CurrentChar->_data, 42);
//i = 5 ;
//CurrentChar = (*(FontSet + i ))->image;
//StoreCharacterToPage(image_data_0x21_t, 511);


//sFLASH_SendData2Byte(image_data_0x20_t, 42, 0);
//sFLASH_SendData2Byte(image_data_0x21_t, 42, 1);


//StoreCharacterToPage(image_data_0x21_t, 42);
//StoreCharacterToPage(image_data_0x20_t, 42);

uint16_t sFLASH_readpixel(uint16_t page, uint16_t offset)
{

    uint16_t low_byte = 0;
    uint16_t high_byte = 0;
    uint16_t data_out = 0;

    FLASH_MEM_CS_L;
    sFLASH_SendByte(0x0B);
    sFLASH_SendByte(page >> 8);
    sFLASH_SendByte(page);
    sFLASH_SendByte(offset*2);
    sFLASH_SendByte(0);


    low_byte = sFLASH_SendByte(0);
//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//SPI_I2S_SendData(SPI1, 0x00);
//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
//low_byte= SPI_I2S_ReceiveData(SPI1);

//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//SPI_I2S_SendData(SPI1, 0x00);
//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
//high_byte= SPI_I2S_ReceiveData(SPI1);
    high_byte = sFLASH_SendByte(0);

    data_out= (low_byte<<8)|high_byte;


    FLASH_MEM_CS_H;
    spiWait();
    return data_out;


}
/*
uint16_t start_page = 0;
void StoreFont_16Bold(void)
{
 uint8_t i = 0;
 FontSet = myriad_bold_12;
 for(i=0;i< 96;i++)
 {
 //i=0;
 CurrentChar = (*(FontSet + i ))->image;
 //writefont2flash(CurrentChar->_data,CurrentChar->size, start_page);

 start_page += writefont2flash(CurrentChar->_data,CurrentChar->size, start_page);
 }
}

uint16_t writefont2flash(uint16_t * f_data,int16_t lengh, uint16_t start_addr)
{

 uint16_t i,f_page= 0;

 f_page = lengh/128;
 (lengh%128 ==0) ? (f_page) : (f_page++) ;

 //page = 600;
 for(i = 0;i<f_page;i++)
 {
  sFLASH_SendData2Byte(f_data+128*i, 128,i+start_addr);
 }

 return f_page;

}
void getlenpages(tChar *Font, uint8_t* size)
{
 uint8_t i = 0;
 uint8_t pagenum = 0;

 for(i = 0; i<96;i++)
 {
  CurrentChar = (*(Font + i ))->image;
  pagenum = CurrentChar->size/128;
  (CurrentChar->size%128 ==0) ? (pagenum) : (pagenum++) ;
  size[i] = pagenum;
 }
}
getlenpages(FontSet, sizepage);
u8 sizepage[100];
*/
