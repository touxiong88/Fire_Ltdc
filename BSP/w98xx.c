#include "w98xx.h"

//����SDRAM��ʼ������
void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram)
{
  u32 temp=0;

    //SDRAM��������ʼ������Ժ���Ҫ��������˳���ʼ��SDRAM
  SDRAM_Send_Cmd(1,FMC_SDRAM_CMD_CLK_ENABLE,1,0); //ʱ������ʹ��
  delay_us(500);                                  //������ʱ200us
  SDRAM_Send_Cmd(1,FMC_SDRAM_CMD_PALL,1,0);       //�����д洢��Ԥ���
  SDRAM_Send_Cmd(1,FMC_SDRAM_CMD_AUTOREFRESH_MODE,8,0);//������ˢ�´��� 
    //����ģʽ�Ĵ���,SDRAM��bit0~bit2Ϊָ��ͻ�����ʵĳ��ȣ�
	//bit3Ϊָ��ͻ�����ʵ����ͣ�bit4~bit6ΪCASֵ��bit7��bit8Ϊ����ģʽ
	//bit9Ϊָ����дͻ��ģʽ��bit10��bit11λ����λ
  temp=(u32)SDRAM_MODEREG_BURST_LENGTH_2          |	//����ͻ������:1(������1/2/4/8)
              SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |	//����ͻ������:����(����������/����)
              SDRAM_MODEREG_CAS_LATENCY_3           |	//����CASֵ:3(������2/3)
              SDRAM_MODEREG_OPERATING_MODE_STANDARD |   //���ò���ģʽ:0,��׼ģʽ
              SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;     //����ͻ��дģʽ:1,�������
  SDRAM_Send_Cmd(1,FMC_SDRAM_CMD_LOAD_MODE,1,temp);   //����SDRAM��ģʽ�Ĵ���
    
    //ˢ��Ƶ�ʼ�����(��SDCLKƵ�ʼ���),���㷽��:
	//COUNT=SDRAMˢ������/����-20=SDRAMˢ������(us)*SDCLKƵ��(Mhz)/����
    //����ʹ�õ�SDRAMˢ������Ϊ64ms,SDCLK=240/2=120Mhz,����Ϊ8192(2^13).
	//����,COUNT=64*1000*120/8192-20=780
  HAL_SDRAM_ProgramRefreshRate(&hsdram1,1386);	
}

u8 SDRAM_Send_Cmd(u8 bankx,u8 cmd,u8 refresh,u16 regval)
{
    u32 target_bank=0;
    FMC_SDRAM_CommandTypeDef Command;
    
    if(bankx==0) target_bank=FMC_SDRAM_CMD_TARGET_BANK1;       
    else if(bankx==1) target_bank=FMC_SDRAM_CMD_TARGET_BANK2;   
    Command.CommandMode=cmd;                //����
    Command.CommandTarget=target_bank;      //Ŀ��SDRAM�洢����
    Command.AutoRefreshNumber=refresh;      //��ˢ�´���
    Command.ModeRegisterDefinition=regval;  //Ҫд��ģʽ�Ĵ�����ֵ
    if(HAL_SDRAM_SendCommand(&hsdram1,&Command,0XFFFF)==HAL_OK) //��SDRAM��������
    {
       return 0;  
    }
    else return 1;    
}

//��ָ����ַ(WriteAddr+Bank5_SDRAM_ADDR)��ʼ,����д��n���ֽ�.
//pBuffer:�ֽ�ָ��
//WriteAddr:Ҫд��ĵ�ַ
//n:Ҫд����ֽ���
void FMC_SDRAM_WriteBuffer(u8 *pBuffer,u32 WriteAddr,u32 n)
{
  for(;n!=0;n--)
  {
    *(vu8*)(Bank5_SDRAM_ADDR+WriteAddr)=*pBuffer;
    WriteAddr++;
    pBuffer++;
  }
}

//��ָ����ַ((WriteAddr+Bank5_SDRAM_ADDR))��ʼ,��������n���ֽ�.
//pBuffer:�ֽ�ָ��
//ReadAddr:Ҫ��������ʼ��ַ
//n:Ҫд����ֽ���
void FMC_SDRAM_ReadBuffer(u8 *pBuffer,u32 ReadAddr,u32 n)
{
  for(;n!=0;n--)
  {
    *pBuffer++=*(vu8*)(Bank5_SDRAM_ADDR+ReadAddr);
    ReadAddr++;
  }
}
