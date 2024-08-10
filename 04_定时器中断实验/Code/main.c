#include "reg52.h"

sbit LED = P2^0;

void Timer0_Init(void)		//5����@11.0592MHz
{
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TMOD |= 0x01;			//���ö�ʱ��ģʽ
	TL0 = 0x00;				//���ö�ʱ��ʼֵ
	TH0 = 0xEE;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	ET0 = 1;                //�򿪶�ʱ���ж�
	EA = 1;                 //�������ж�
}


void Timer0Routine(void) interrupt 1
{
	static int count = 0;
	TL0 = 0x00;				//���ö�ʱ��ʼֵ
	TH0 = 0xEE;				//���ö�ʱ��ʼֵ
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