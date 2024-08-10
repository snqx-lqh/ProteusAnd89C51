#include <reg52.h>
#include "LCD1602.h"
#include "stdio.h"

u8 Disp[16]={0};

int main()
{
    LcdInit();
    while (1)
    {
        sprintf((char*)Disp,"first display");
        LcdShowStr(0,0,Disp);
        sprintf((char*)Disp,"distance:%2d",(u16)12);
        LcdShowStr(0,1,Disp);
    }  
}

