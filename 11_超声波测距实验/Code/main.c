#include "reg52.h"

#include "stdio.h"
#include "hc_sr04.h"

#define u8 unsigned char
#define u16 unsigned int
			   
u8 uartBuff[30] = {0};

void UartInit(void)		//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFD;			//设置定时初始值
	TH1 = 0xFD;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
	ES = 0;             //打开串口中断
	EA = 1;             //打开全部中断
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
	sprintf((char*)uartBuff,"超声波实验\r\n" );
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




