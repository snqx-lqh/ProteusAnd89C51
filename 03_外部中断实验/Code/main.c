#include "reg52.h"

sbit LED = P2^0;
sbit KEY1 = P3^2;
sbit KEY2 = P3^3;

void Exti0Init()
{
	IT0 = 1;//1:�½��ش��� 0:�͵�ƽ����
	EX0 = 1;//���ⲿ�ж�1
	EA = 1;//�����жϿ���
}

void Exti1Init()
{
	IT1 = 1;//1:�½��ش��� 0:�͵�ƽ����
	EX1 = 1;//���ⲿ�ж�1
	EA = 1;//�����жϿ���
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