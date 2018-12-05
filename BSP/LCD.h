#ifndef __LCD_H
#define __LCD_H

#include "stm32f7xx_hal.h"
#include "spi.h"




#define LCD_WIDTH 720
#define LCD_HEIGHT 480

//第一层显存首地址,SDRAM的首地址
#define LCD_LAYER1_START_ADDR 0xD0000000
#define LCD_LAYER1_BUFFER_SIZE LCD_WIDTH * LCD_HEIGHT * 2

//第二层显存首地址,SDRAM的首地址
#define LCD_LAYER2_START_ADDR (LCD_LAYER1_START_ADDR + LCD_LAYER1_BUFFER_SIZE)
#define LCD_LAYER2_BUFFER_SIZE LCD_WIDTH*LCD_HEIGHT * 3




void SPI2_Reg_Write(void);
void LCD_Configuration(void);
void SPI_SendData(uint8_t addr,uint8_t dat);
#endif
