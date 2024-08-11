#ifndef _BSP_KEY_H
#define _BSP_KEY_H

#include <reg52.h>

#ifndef u8
#define u8  unsigned char
#endif

#ifndef u16
#define u16 unsigned int
#endif

sbit key1 = P3^0;
sbit key2 = P3^1;
sbit key3 = P3^2;
sbit key4 = P3^3;

void KeyInit(void);
u8 KeyScan(u8 mode);

#endif
