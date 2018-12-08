#include "LCD.h"

const uint16_t init_dat[68]=
{
0x0003,
//0x0121,
0x0227,
0x032e,//V
0x0463,//H
0x0587,//07,input control
0x0680,// D7 			D6 D5 D4 D3 D2 D1 D0
			 // 4:3/3:2             UD RL  
0x0720,// D7 D6 D5 D4 D3 D2 D1 D0
			 //                      HSYNC
0x081B,
0x0900,// D7 	D6 D5 D4  D3 D2 D1 D0
			 //               16:9
0x0A25,
0x0B20,
0x0C20,
0x0D0D,
0x0E20,
0x0F20,
0x1040,
0x113F,
0x1231,
0x1340,
0x1408,
0x1506,
0x16B4,
0x1700,
0x1888,
0x19FF,
0x1A00,
0x1B80,
0x1C00,
0x1D00,
0x1E00,
0x1F3F,
0x2085,
0x2189,
0x2287,
0x2387,
0x2487,
0x258C,
0x2683,
0x270C,
0x282B,
0x2923,
0x2A28,
0x2B28,
0x2C30,
0x2D3B,
0x2E00,
0x2F08,
0x3000,
0x3100,
0x3200,
0x3300,
0x3400,
0x3500,
0x3600,
0x3700,
0x3800,
0x3900,
0x3A00,
0x3B00,
0x3C00,
0x3D00,
0x3E00,
0x3F00,
0x4000,
0x418E,
0x42A0,
0x4300,
0x4429,
//0x0600,
};

void SPI2_Reg_Write(void)
{
	uint8_t reg;
	uint8_t value;
	
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
	for(uint8_t i=0;i<sizeof(init_dat);i++)
	{
		reg=init_dat[i]>>8;
		value=init_dat[i];
		if(HAL_SPI_Transmit(&hspi2, (uint8_t *)&reg, 1, 1000)!=HAL_OK)
		{
		}
		if(HAL_SPI_Transmit(&hspi2, (uint8_t *)&value, 1, 1000)!=HAL_OK)
		{
		}
	}
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}

void LCD_Reset(void)
{
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(500);
}
void Lcd_Init(void)
{
	LCD_Reset();
	SPI2_Reg_Write();
}


