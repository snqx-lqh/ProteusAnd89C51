#ifndef _LCD1602_H
#define _LCD1602_H

#include <reg52.h>

#ifndef u8
#define u8  unsigned char
#endif

#ifndef u16
#define u16 unsigned int
#endif

/**********************************
PIN口定义
**********************************/
#define LCD1602_DATAPINS  P0      //data bus 数据总线
sbit LCD1602_RS = P2^6;
sbit LCD1602_RW = P2^5;
sbit LCD1602_E  = P2^7;	 

/**********************************
函数声明
**********************************/
void Lcd1602_Delay1ms(u16 c);   
void LcdShowStr(u8 x,u8 y,u8 *str);     //显示字符串
void LcdInit();                                                          //1602初始化

#endif

