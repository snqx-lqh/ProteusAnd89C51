#include <reg52.h>
#include <intrins.h>
#include "LCD1602.h"
#include "iap_eeprom.h"
#include "stdio.h"

#define uchar unsigned char   
#define uint unsigned int

sbit K1   = P3^2;                           //按钮1
sbit K2   = P3^3;                           //按钮2
 
void IntConfiguration();

uchar ON_Hour=7;                                                                 
uchar Warning_TempH=32;                                                                             
uchar Disp[16]={0};

void main(void)
{
    LcdInit();
    IntConfiguration();

    SectorErase(0x2000);                  
    byte_write(0x2001,ON_Hour);          
    byte_write(0x2002,Warning_TempH); 
	byte_write(0x2007,14);	

	while(1)
	{
		ON_Hour = byte_read(0x2001);
		Warning_TempH = byte_read(0x2003);
		sprintf((char*)Disp,"ON_Hour:%2d",(u16)ON_Hour);
		LcdShowStr(0,0,Disp);
		sprintf((char*)Disp,"TempH:  %2d",(u16)Warning_TempH);
		LcdShowStr(0,1,Disp);
	}
}


void IntConfiguration()
{
	//设置INT0
	IT0=1;//跳变沿出发方式（下降沿）
	EX0=1;//打开INT0的中断允许。
 
	IT1=1;//跳变沿出发方式（下降沿）
	EX1=1;//打开INT0的中断允许。
	EA=1;//打开总中断      
}
void Int0() interrupt 1                 
{
   SectorErase(0x2000);                  // 擦除第1个扇区（2000h~21FFh）
   byte_write(0x2001,0x07);          
   byte_write(0x2002,32);
}
void Int1() interrupt 2                 
{
   SectorErase(0x2000);                  // 擦除第1个扇区（2000h~21FFh）
   byte_write(0x2001,0x08);          
   byte_write(0x2002,33);
}