#include <reg52.h>
#include "LCD1602.h"
#include "stdio.h"
#include "ADC0832.h"

#define u8  unsigned char
#define u16 unsigned int

uchar Disp[2][16]={0};

u8 adcGet0 = 0;
u8 adcGet1 = 0;

int main()
{
    LcdInit();
    while (1)
    {
		adcGet0 = adc0832(0);
		adcGet1 = adc0832(1);
        sprintf((char*)Disp[0],"adcGet0 = %.2fV",adcGet0/255.0f*5);
        LcdShowStr(0,0,Disp[0]);
        sprintf((char*)Disp[1],"adcGet1 = %3d",(u16)adcGet1);
        LcdShowStr(0,1,Disp[1]);
    }  
}

