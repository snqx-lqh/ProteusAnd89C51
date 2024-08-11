#ifndef _LCD12864_H
#define _LCD12864_H

#include <reg52.h>

#define LCDLCDDisp_Off   0x3e
#define LCDLCDDisp_On    0x3f
#define Page_Add     0xb8//页地址
#define LCDCol_Add     0x40//列地址
#define Start_Line     0xC0//行地址

/*****液晶显示器的端口定义*****/
#define data_ora P1 /*液晶数据总线*/
sbit LCDMcs=P2^0 ;    /*片选1*/
sbit LCDScs=P2^1 ;    /*片选2*/
sbit RESET=P2^5 ;  /*复位信号*/
sbit LCDDi=P2^2 ;     /*数据/指令 选择*/
sbit LCDRW=P2^3 ;     /*读/写 选择*/
sbit LCDEnable=P2^4 ;     /*读/写 使能*/

void init_lcd(void);
void Clr_Scr(void);
void hz_LCDDisp16(unsigned char page,unsigned char column, unsigned char code *hzk);

#endif
