#include "reg52.h"

sbit LED = P2^0;
sbit KEY1 = P3^2;
sbit KEY2 = P3^3;

void Exti0Init()
{
	IT0 = 1;//1:下降沿触发 0:低电平触发
	EX0 = 1;//打开外部中断1
	EA = 1;//打开总中断开关
}

void Exti1Init()
{
	IT1 = 1;//1:下降沿触发 0:低电平触发
	EX1 = 1;//打开外部中断1
	EA = 1;//打开总中断开关
}

void Int0Routine(void) interrupt 0
{
	if(KEY1 == 0)
	{
		LED = !LED;
	}
}

void Int1Routine(void) interrupt 2
{
	if(KEY2 == 0)
	{
		LED = !LED;
	}
}

int main()
{
	Exti0Init();
	Exti1Init();
	while(1)
	{
		
	}
}