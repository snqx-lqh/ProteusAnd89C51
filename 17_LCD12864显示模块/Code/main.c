#include <reg52.h>
#include "LCD12864.h"
#include "fonts.h"

void main()
{
	init_lcd();
	Clr_Scr();
	LCDMcs=0; //左屏开显示
	LCDScs=1;
	hz_LCDDisp16(0,48,Hz_Deng);// Hz_Wo为某个汉字的首地址
    LCDMcs=1; //右屏开显示
	LCDScs=0;
	hz_LCDDisp16(0,0,Bmp_Miao);
	hz_LCDDisp16(0,16,Bmp_bo);
	while(1)
    {
  
	}
}
