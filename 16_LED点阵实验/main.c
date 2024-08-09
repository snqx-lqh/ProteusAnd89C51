#include<reg51.h>
#include<intrins.h>

typedef unsigned char uchar;
typedef unsigned int uint;
void delayms(uint xms);
void hc595(uchar byteData);

sbit SER = P3^4;    //p3.4脚控制串行数据输入
sbit SCK = P3^6;    //串行输入时钟
sbit RCK = P3^5;    //存储寄存器时钟

uchar code table[]=
                                 {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
uchar num=0;
void main()
{
        while(1)
        {
                   for(num=0;num<8;num++)
                {
                        hc595(table[num]);        
                        delayms(500);
                }
        }        //        hc595(0x55);            // Q7~Q0=0101 0101                 }
}



/*功能:发送一个字节的数据给595，再并行输出*/
void hc595(char byteData)
{
    char i=0;   
    for(i=0;i<8;i++)
    {
        SER = byteData>>7;        //送出7位数据
        byteData= byteData<<1;      

        SCK = 0;          //上升沿，让串行输入时钟变为高电平，并延时2个时钟周期
        _nop_();
        _nop_();
        SCK = 1;          //变为低电平，为下次准备
    }  
   
   //位移寄存器数据准备完毕,转移到存储寄存器
   RCK = 0;         //上升沿，让存储寄存器时钟变为高电平，并延时2个时钟周期
   _nop_();
   _nop_();
   RCK = 1;

}


void delayms(uint xms )  //延时xms函数
{
        uint a,b;
        for(a=xms;a>0;a--)
         for(b=110;b>0;b--);
}