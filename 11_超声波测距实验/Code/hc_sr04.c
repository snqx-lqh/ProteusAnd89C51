#include "hc_sr04.h"
#include "intrins.h"

float dist;
unsigned long time;
u16 tt,flag=0;

void HCSR04_Init()
{
	Trig = 0;
	Echo = 1;
}

void  StartModule() 		         //����ģ��
{
	Trig=1;			                     //����һ��ģ��
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	Trig=0;
}

//��ʱ��0��ʼ��   
void TimeInit()
{
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TMOD |= 0x01;			//���ö�ʱ��ģʽ
	TL0 = 0x00;				//���ö�ʱ��ʼֵ
	TH0 = 0x00;				//���ö�ʱ��ʼֵ
	TF0 = 1;				//���TF0��־
	TR0 = 0;				 
	ET0 = 1;                //�򿪶�ʱ���ж�
	EA = 1;                 //�������ж�
}

void Time0() interrupt 1
{
	flag++;
}

//���㺯��
float DistCount()
{
	while(!Echo);
	TR0=1;
	while(Echo);
	TR0=0;
	time=flag*65535+TH0*256+TL0;	
	TH0=0;
	TL0=0;
	flag = 0;
	dist=(float)(time*0.017);

	return dist;
}
