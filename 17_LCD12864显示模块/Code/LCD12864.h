#ifndef _LCD12864_H
#define _LCD12864_H

#include <reg52.h>

#define LCDLCDDisp_Off   0x3e
#define LCDLCDDisp_On    0x3f
#define Page_Add     0xb8//ҳ��ַ
#define LCDCol_Add     0x40//�е�ַ
#define Start_Line     0xC0//�е�ַ

/*****Һ����ʾ���Ķ˿ڶ���*****/
#define data_ora P1 /*Һ����������*/
sbit LCDMcs=P2^0 ;    /*Ƭѡ1*/
sbit LCDScs=P2^1 ;    /*Ƭѡ2*/
sbit RESET=P2^5 ;  /*��λ�ź�*/
sbit LCDDi=P2^2 ;     /*����/ָ�� ѡ��*/
sbit LCDRW=P2^3 ;     /*��/д ѡ��*/
sbit LCDEnable=P2^4 ;     /*��/д ʹ��*/

void init_lcd(void);
void Clr_Scr(void);
void hz_LCDDisp16(unsigned char page,unsigned char column, unsigned char code *hzk);

#endif
