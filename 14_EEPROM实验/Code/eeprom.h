#ifndef _EEPROM_H
#define _EEPROM_H

#include <reg52.h>

#define unchar unsigned char
#define uint unsigned int

sbit SCL = P2^1;			//����SCLʱ���߶˿�
sbit SDA = P2^0;			//����SDA�����߶˿�

void IIC_init(void);
void Write_add(unchar date,unchar address);
unchar Read_add(unchar address);

#endif
