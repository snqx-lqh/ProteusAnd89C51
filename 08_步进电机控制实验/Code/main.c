#include "reg52.h"
#include "step_motor.h"

void Timer0Init(void);
 

int main()
{
    Timer0Init();
    while (1)
    {
    }
}

void Timer0Init(void) //5毫秒@12.000MHz
{
    TMOD = 0x01; //设置定时器模式
    TL0 = 0x00;  //设置定时0初始值
    TH0 = 0xEE;  //设置定时0初始值
    TF0 = 0;     //清除TF0标志
    TR0 = 1;     //定时器0开始计时
    ET0 = 1;
    EA = 1;
}

void Timer0() interrupt 1
{
    static int counts = 0;

    TL0 = 0x00; //设置定时0初始值
    TH0 = 0xEE; //设置定时0初始值
    counts++;
    if (counts > 100)
    {
        MotorTurn(CW);
        counts = 0;
    }
}

