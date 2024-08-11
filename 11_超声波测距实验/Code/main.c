#include "reg52.h"

#include "stdio.h"
#include "hc_sr04.h"

#define u8 unsigned char
#define u16 unsigned int
			   
u8 uartBuff[30] = {0};

void UartInit(void)		//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	TL1 = 0xFD;			//���ö�ʱ��ʼֵ
	TH1 = 0xFD;			//���ö�ʱ����ֵ
	ET1 = 0;			//��ֹ��ʱ���ж�
	TR1 = 1;			//��ʱ��1��ʼ��ʱ
	ES = 0;             //�򿪴����ж�
	EA = 1;             //��ȫ���ж�
}

void SendBuffLen(u8 *str,u8 len)
{
	while(len != 0)
	{
		SBUF = *str;
		while(!TI);
		TI = 0;
		str++;
		len --;
	}
}

void delayms(unsigned int ms)
{
	unsigned char i=100,j;
	for(;ms;ms--)
	{
		while(--i)
		{
			j=10;
			while(--j);
		}
	}
}

void main()
{
	float dist_value = 0;
	HCSR04_Init();
	UartInit();
	TimeInit();
	sprintf((char*)uartBuff,"������ʵ��\r\n" );
	SendBuffLen(uartBuff,sizeof(uartBuff));
	while(1)
	{
		StartModule();
		dist_value = DistCount();
		sprintf((char*)uartBuff,"distance:%.2f\r\n",dist_value);
		SendBuffLen(uartBuff,sizeof(uartBuff));
		delayms(80);
	}
}




