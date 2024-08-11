#include <reg52.h>

#include "LCD1602.h"
#include "eeprom.h"
#include "stdio.h"


#define unchar unsigned char
#define uint unsigned int
	
unchar Disp[16]={0};	
sbit button = P3^2;		//���尴��

void main()
{
	unchar num=0,NUM=0;
	static uint count = 0;
	LcdInit();
	IIC_init();
	
	while(1)
	{
		count ++;
		if(count>10)//ÿѭ��10��ˢ��һ��
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
				Write_add(num,0x00);	//��numд�뵽0x00��ַ��
			}
			while(button == 0)
			{
				;
			}
		}
		NUM = Read_add(0x00);			//��0x00�������ݶ�ȡ����
		
		Lcd1602_Delay1ms(10);
	}
}