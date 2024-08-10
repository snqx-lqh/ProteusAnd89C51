#include "reg52.h"
#include "intrins.h"
#include "stdio.h"

#define u8 unsigned char
#define u16 unsigned int
	
unsigned long dist;
u16 time;
u16 tt,flag;
				   
sbit Trig=P2^1;
sbit Echo=P2^0;

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

//���㺯��
void count()
{
	time=TH0*256+TL0;	
	TH0=0;
	TL0=0;
	dist=(long)(time*0.17);
	if((dist>=4000) || (flag==1)){
		flag=0;
	}
	else{
		sprintf((char*)uartBuff,"distance:%d\r\n",dist);
		SendBuffLen(uartBuff,sizeof(uartBuff));
	}
}
//��ʱ��0��ʼ��   
void TimeInit()
{
	TMOD |= 0x01;
	TH0   = 0;
	TL0   = 0;
	EA    = 1;
	ET0   = 1;
	TR0   = 0;
}
void Time0() interrupt 1
{
	flag=1;
}

void  StartModule() 		         //����ģ��
{
	Trig=1;			                     //����һ��ģ��
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_();
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_();
	Trig=0;
}

void main()
{
	UartInit();
	TimeInit();
	
	Trig=0;
	sprintf((char*)uartBuff,"������ʵ��\r\n",dist);
	SendBuffLen(uartBuff,sizeof(uartBuff));
	while(1)
	{
		StartModule();
		while(!Echo);
		TR0=1;
		while(Echo);
		TR0=0;
		count();
		delayms(80);
	}
}




