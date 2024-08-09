#include "reg52.h"

#define u8  unsigned char
#define u16 unsigned int

sbit LED = P2^0;

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

char str[] = "hello world\r\n";

int main()
{
	UartInit();
	SendBuffLen(str,sizeof(str));
	while(1)
	{
		
	}
}

void UartRoutine(void) interrupt 4
{
	u8 res;	
	if(RI)
	{
		res = SBUF;
		if(res == 0x01)
		{
			LED = 0;
			SendBuffLen("hello world\r\n",sizeof("hello world\r\n"));
		}else
		{
			LED = 1;
			SendBuffLen("中文字符测试\r\n",sizeof("中文字符测试\r\n"));
		}
		RI = 0;
	}	
}