#include <reg52.h>
#include "LCD12864.h"
#include "fonts.h"

void main()
{
	init_lcd();
	Clr_Scr();
	LCDMcs=0; //��������ʾ
	LCDScs=1;
	hz_LCDDisp16(0,48,Hz_Deng);// Hz_WoΪĳ�����ֵ��׵�ַ
    LCDMcs=1; //��������ʾ
	LCDScs=0;
	hz_LCDDisp16(0,0,Bmp_Miao);
	hz_LCDDisp16(0,16,Bmp_bo);
	while(1)
    {
  
	}
}
