#ifndef __LCD_H
#define __LCD_H

#include "stm32f7xx_hal.h"
#include "spi.h"







void SPI2_Reg_Write(void);
void LCD_Configuration(void);
void SPI_SendData(uint8_t addr,uint8_t dat);
#endif
