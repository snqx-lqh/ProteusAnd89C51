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

//计算函数
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
//定时器0初始化   
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

void  StartModule() 		         //启动模块
{
	Trig=1;			                     //启动一次模块
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
	sprintf((char*)uartBuff,"超声波实验\r\n",dist);
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




