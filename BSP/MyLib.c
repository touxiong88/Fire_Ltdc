#include "MyLib.h"
//POSITION_VAL(0X2000000)-1;
#if STM32F1SYSCLK 
static uint32_t fac_us=72;
#endif
#if STM32F4SYSCLK 
static uint32_t fac_us=180;
#endif
#if STM32F7SYSCLK 
static uint32_t fac_us=216;
#endif
#if STM32H7SYSCLK 
static uint32_t fac_us=400;
#endif

#if STM32F1SYSCLK
/****************************************************************************
* 名    称：delay_us(uint32_t nus)
* 功    能：微秒延时函数
* 入口参数：uint32_t  nus
* 出口参数：无
* 说    明：输入范围(1~1000)ns
* 调用方法：无 
****************************************************************************/ 
void delay_us(uint32_t nus)
{
	 uint32_t temp;
	 SysTick->LOAD = 9*nus;
	 SysTick->VAL=0X00;//清空计数器
	 SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
	 do
	 {
	  temp=SysTick->CTRL;//读取当前倒计数值
	 }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
	 
	 SysTick->CTRL=0x00; //关闭计数器
	 SysTick->VAL =0X00; //清空计数器
}

/****************************************************************************
* 名    称：delay_ms(uint16_t nms)
* 功    能：毫秒延时函数
* 入口参数：uint16_t nms
* 出口参数：无
* 说    明：输入范围(1~1000)ms
* 调用方法：无 
****************************************************************************/ 
void delay_ms(uint16_t nms)
{
	 uint32_t temp;
	 SysTick->LOAD = 9000*nms;
	 SysTick->VAL=0X00;//清空计数器
	 SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
	 do
	 {
	  temp=SysTick->CTRL;//读取当前倒计数值
	 }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
	 SysTick->CTRL=0x00; //关闭计数器
	 SysTick->VAL =0X00; //清空计数器
}
#endif
#if STM32F7SYSCLK 

//延时nus
//nus为要延时的us数.	
//注意:nus的值不要大于1000us
void delay_us(uint32_t nus)
{		
	uint32_t ticks;
	uint32_t told,tnow,tcnt=0;
	uint32_t reload=SysTick->LOAD;				//LOAD的值	    	 
	ticks=nus*fac_us; 						//需要的节拍数 
	told=SysTick->VAL;        				//刚进入时的计数器值
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
		}  
	};
}
//延时nms
//nms:要延时的ms数
void delay_ms(uint16_t nms)
{
	uint32_t i;
	for(i=0;i<nms;i++) delay_us(1000);
}
#endif
#if STM32H7SYSCLK 

//延时nus
//nus为要延时的us数.	
//注意:nus的值不要大于1000us
void delay_us(uint32_t nus)
{		
	uint32_t ticks;
	uint32_t told,tnow,tcnt=0;
	uint32_t reload=SysTick->LOAD;				//LOAD的值	    	 
	ticks=nus*fac_us; 						//需要的节拍数 
	told=SysTick->VAL;        				//刚进入时的计数器值
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
		}  
	};
}
//延时nms
//nms:要延时的ms数
void delay_ms(uint16_t nms)
{
	uint32_t i;
	for(i=0;i<nms;i++) delay_us(1000);
}
#endif
void ConvertFloatTo4ByteCmd(float fValue, uint8_t* inByte)
{
	unsigned char * fMem = (unsigned char *)(&fValue);
	memset(inByte, 0, 4);
	inByte[0] = fMem[0];
	inByte[1] = fMem[1];
	inByte[2] = fMem[2];
	inByte[3] = fMem[3];
}

void ConvertDoubleTo8ByteCmd(double fValue, uint8_t* inByte)
{
	unsigned char * fMem = (unsigned char *)(&fValue);
	memset(inByte, 0, 8);
	inByte[0] = fMem[0];
	inByte[1] = fMem[1];
	inByte[2] = fMem[2];
	inByte[3] = fMem[3];

	inByte[4] = fMem[4];
	inByte[5] = fMem[5];
	inByte[6] = fMem[6];
	inByte[7] = fMem[7];
}
double Convert8ByteCmdToDouble(uint8_t* inByte)
{
	double fOut=0.0;
	
	unsigned char fMem[8]={0};
	double *p = (double*)fMem;
	
	fMem[0] = inByte[0];
	fMem[1] = inByte[1];
	fMem[2] = inByte[2];
	fMem[3] = inByte[3];
	
	fMem[4] = inByte[4];
	fMem[5] = inByte[5];
	fMem[6] = inByte[6];
	fMem[7] = inByte[7];
	
	fOut = *p;
	return fOut;
}
float Convert4ByteCmdToFloat(uint8_t* inByte)
{
	float fOut=0.0;
	
	unsigned char fMem[4]={0};
	float *p = (float*)fMem;
	
	fMem[0] = inByte[0];
	fMem[1] = inByte[1];
	fMem[2] = inByte[2];
	fMem[3] = inByte[3];
	
	fOut = *p;
	return fOut;
}

/*******************************
函数名：my_itoa
功能：将整形转换字符数组
参数：
	num：		整形值
	*str:		字符数组地址
	*radix:	进制
返回值：字符数组的指针
*********************************/


char *my_itoa(int num, char *str, int radix)
{
	/*索引表*/
	char index[] = "0123456789ABCDEF";
	char temp = 0;
	unsigned int unum;
	int i = 0, j, k;
	
	if(radix == 10 && 0 > num)
	{
		unum = (unsigned int)-num;
		str[i++] = '-';
	}
	else
		unum = (unsigned int) num;
	
	/*转换*/
	do
	{
		str[i++] = index[unum % (unsigned int)radix];
		unum/=radix;
	}while(unum);
	str[i] = '\0';
	if(str[0] == '-')
		k = 1;
	else
		k = 0;
	
	for(j = k; j <= (i - 1) / 2; j++)
	{
		temp = str[j];
		str[j] = str[i-1 + k - j];
		str[i-1 + k - j] = temp;
	}
	return str;
}

/*******************************
函数名：my_strchr_n
功能：查找字符串str里面ch所在位置
参数：
	*str:		字符数组地址
		ch:		查找的字符
返回值：字符数组的指针
*********************************/

int my_strchr_n(const char *str, int ch)
{
	unsigned int cnt = 0;
	while(*str != '\0')
	{
		if(*str == ch)
			return cnt;
		cnt++;
		str++;
	}
	
	return -1;
}

/*******************************
函数名：my_strchr_nn
功能：查找字符串str里面ch所在位置
参数：
	*str:		字符数组地址
		ch:		查找的字符
		cnt:	查找个数
返回值：字符数组的指针
*********************************/

int my_strchr_nn(const char *str, int ch, int cnt)
{
	unsigned int i = 0;

	for(i = 0; i < cnt; i++)
	{
		if(*str == ch)
			return i;
		str++;
	}
	
	return -1;
}
int fputc(int ch,FILE *f)
{
	HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,0x1000);
	return ch;
}
uint8_t Check_Sum(uint8_t p[],uint8_t size)
{
   uint8_t i=0;
   uint16_t sum=0;
   for(i=0;i<size;i++)
   {
      sum+=p[i];
   }
   return (uint8_t)sum&0xff;
}

uint8_t Check_Sum16(uint8_t p[],uint8_t size)
{
   uint8_t i=0;
   uint16_t sum=0;
   for(i=0;i<size;i++)
   {
      sum+=p[i];
   }
   return sum;
}
#if 0
void I2C_WriteOneByte(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t value)
{
	while( HAL_I2C_Mem_Write(I2Cx, I2C_Addr, addr, I2C_MEMADD_SIZE_8BIT, &value, 0x01, 1000) != HAL_OK )
	{};
}

void I2C_Write(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint16_t num)
{
	while(num--)
	{
		 I2C_WriteOneByte(I2Cx, I2C_Addr,addr++,*buf++); 
	}
}
void I2C_Read(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint16_t num)
{
	while(HAL_I2C_Mem_Read (I2Cx ,I2C_Addr,addr,I2C_MEMADD_SIZE_8BIT,buf,num,1000) != HAL_OK )
	{};
}
#endif




