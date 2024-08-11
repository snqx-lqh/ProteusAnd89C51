#include "reg52.h"
#include "DS18B20.h"
#include "intrins.h"
#include "stdio.h"

#ifndef u8
#define u8  unsigned char
#endif

#ifndef u16
#define u16 unsigned int
#endif

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
	ES = 1;             //�򿪴����ж�
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

void Delay1000ms()		//@11.0592MHz
{
	unsigned char data i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


u8 uartBuff[30] = {0};

int main()
{
	int temp = 0;
	UartInit();
	while(1)
	{
		temp = Ds18b20ReadTemp();
		sprintf((char*)uartBuff,"TEMP:%d\r\n",temp);
		SendBuffLen(uartBuff,sizeof(uartBuff));
		sprintf((char*)uartBuff,"TEMPf:%.2f\r\n",temp*0.0625);
		SendBuffLen(uartBuff,sizeof(uartBuff));
		Delay1000ms();
	}
}