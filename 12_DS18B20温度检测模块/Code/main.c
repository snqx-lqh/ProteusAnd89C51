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
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFD;			//设置定时初始值
	TH1 = 0xFD;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
	ES = 1;             //打开串口中断
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