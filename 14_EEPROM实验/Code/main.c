#include <reg52.h>

#include "LCD1602.h"
#include "eeprom.h"
#include "stdio.h"


#define unchar unsigned char
#define uint unsigned int
	
unchar Disp[16]={0};	
sbit button = P3^2;		//定义按键

void main()
{
	unchar num=0,NUM=0;
	static uint count = 0;
	LcdInit();
	IIC_init();
	
	while(1)
	{
		count ++;
		if(count>10)//每循环10次刷新一次
		{
			count = 0;
			sprintf((char*)Disp,"read num:%d",(int)NUM);
			LcdShowStr(0,0,Disp);
		}
		if(button == 0)
		{
			Lcd1602_Delay1ms(10);
			if(button == 0)
			{
				num = Read_add(0x00);
				num ++;
				Write_add(num,0x00);	//将num写入到0x00地址处
			}
			while(button == 0)
			{
				;
			}
		}
		NUM = Read_add(0x00);			//将0x00处的数据读取出来
		
		Lcd1602_Delay1ms(10);
	}
}