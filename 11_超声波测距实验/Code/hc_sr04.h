#ifndef _HC_SR04_H
#define _HC_SR04_H

#include "reg52.h"

#define u8 unsigned char
#define u16 unsigned int

sbit Trig=P2^1;
sbit Echo=P2^0;

void HCSR04_Init(void);
void TimeInit(void);
void  StartModule(void);
float DistCount(void);

#endif
