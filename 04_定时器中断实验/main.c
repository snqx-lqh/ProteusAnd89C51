#include "reg52.h"

sbit LED = P2^0;

void Timer0_Init(void)		//5毫秒@11.0592MHz
{
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0x00;				//设置定时初始值
	TH0 = 0xEE;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;                //打开定时器中断
	EA = 1;                 //打开所有中断
}


void Timer0Routine(void) interrupt 1
{
	static int count = 0;
	TL0 = 0x00;				//设置定时初始值
	TH0 = 0xEE;				//设置定时初始值
	count++;
	if(count>100)
	{
		LED = !LED;
		count = 0;
	}
}

int main()
{
	Timer0_Init();
	while(1)
	{
		
	}
}