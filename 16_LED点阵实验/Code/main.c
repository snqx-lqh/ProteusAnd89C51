#include<reg51.h>
#include<intrins.h>

typedef unsigned char uchar;
typedef unsigned int uint;
void delayms(uint xms);
void LedMatrixShow(uchar *showBuff);
//74HC138的ABC引脚
sbit HCA = P2^2;
sbit HCB = P2^3;
sbit HCC = P2^4;

#define SEG P1

uchar code table[]={0x01,0x55,0xAA,0x02,0x03,0x44,0x55,0xAA};
uchar num=0;
void main()
{
        while(1)
        {
			LedMatrixShow(table);
			delayms(2);
        }        
}

void LedMatrixShow(uchar *showBuff)
{
	static uchar segSelectCount = 0;//位选变量
	
	segSelectCount ++;
	if(segSelectCount > 7)
		segSelectCount = 0;

	SEG = 0x00;//消隐
	switch (segSelectCount)
	{
		case 0: HCC = 0;HCB = 0;HCA = 0;SEG = showBuff[0];break;
		case 1: HCC = 0;HCB = 0;HCA = 1;SEG = showBuff[1];break;
		case 2: HCC = 0;HCB = 1;HCA = 0;SEG = showBuff[2];break;
		case 3: HCC = 0;HCB = 1;HCA = 1;SEG = showBuff[3];break;
		case 4: HCC = 1;HCB = 0;HCA = 0;SEG = showBuff[4];break;
		case 5: HCC = 1;HCB = 0;HCA = 1;SEG = showBuff[5];break;
		case 6: HCC = 1;HCB = 1;HCA = 0;SEG = showBuff[6];break;
		case 7: HCC = 1;HCB = 1;HCA = 1;SEG = showBuff[7];break;
		default:HCC = 0;HCB = 0;HCA = 0;SEG = showBuff[0];break;
	}
}

void delayms(uint xms )  //延时xms函数
{
        uint a,b;
        for(a=xms;a>0;a--)
         for(b=110;b>0;b--);
}