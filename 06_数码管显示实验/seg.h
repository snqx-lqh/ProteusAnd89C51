#ifndef _SEG_H
#define _SEG_H

#include <reg52.h>

#ifndef u8
#define u8  unsigned char
#endif

#ifndef u16
#define u16 unsigned int
#endif

extern u8 segBuff[];

void SegShow();

#endif