#ifndef __MyLib_H
#define __MyLib_H

#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "usart.h"

#define STM32F1SYSCLK 0
#define STM32F4SYSCLK  0
#define STM32F7SYSCLK  1
#define STM32H7SYSCLK  0

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  
typedef const int16_t sc16;  
typedef const int8_t sc8;  

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  
typedef __I int16_t vsc16; 
typedef __I int8_t vsc8;   

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  
typedef const uint16_t uc16;  
typedef const uint8_t uc8; 

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  
typedef __I uint16_t vuc16; 
typedef __I uint8_t vuc8;

typedef struct
{
  uint8_t task1:1;
  uint8_t task2:1;
  uint8_t task3:1;
  uint8_t task4:1;
  uint8_t task5:1;
  uint8_t task6:1;
}Task;
extern Task pTask;

typedef struct
{
  uint8_t Res;
  uint8_t USART1_lenth;
  uint8_t complete:1;
  uint8_t Receive_Data[15];
}nUSART1;
extern nUSART1 USART1_Packet;

typedef struct
{
  uint8_t Res;
  uint8_t USART3_lenth;
  uint8_t complete:1;
  uint8_t Receive_Data[15];
}nUSART3;
extern nUSART3 USART3_Packet;


void ConvertFloatTo4ByteCmd(float fValue, uint8_t* inByte);
void ConvertDoubleTo8ByteCmd(double fValue, uint8_t* inByte);
double Convert8ByteCmdToDouble(uint8_t* inByte);
float Convert4ByteCmdToFloat(uint8_t* inByte);
char *my_itoa(int num, char *str, int radix);
int my_strchr_n(const char *str, int ch);
int my_strchr_nn(const char *str, int ch, int cnt);
uint8_t Check_Sum(uint8_t p[],uint8_t size);
uint8_t Check_Sum16(uint8_t p[],uint8_t size);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);
#if 0
void I2C_WriteOneByte(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t value);
void I2C_Write(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint16_t num);
void I2C_Read(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint16_t num);
#endif


#endif

