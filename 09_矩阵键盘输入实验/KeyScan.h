#ifndef _KEY_SCAN_H
#define _KEY_SCAN_H

#include "main.h"
#include <reg52.h>

#define GPIO_KEY P1

#define KEY_0       14
#define KEY_1       1
#define KEY_2       2
#define KEY_3       3
#define KEY_4       5
#define KEY_5       6
#define KEY_6       7
#define KEY_7       9
#define KEY_8       10
#define KEY_9       11
#define KEY_Back    15
#define KEY_Open    4
#define KEY_Close   8
#define KEY_Change  12
#define KEY_Confirm 16

extern u8 KeyValue;
extern u8 KeyState;

void KeyScan(void);

#endif
