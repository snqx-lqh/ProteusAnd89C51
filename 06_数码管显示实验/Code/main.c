/**
  ************************************* Copyright ****************************** 
  *
  *                 (C) Copyright 2022, LQH, China, GCU.
  *                                All Rights Reserved
  *                              
  *                                      By LQH
  *                       
  * FileName   : main.c   	
  * Author     : 少年潜行(snqx-lgh)			
  * Date       : 2022-07-03         
  * Description: CSDN主页： https://blog.csdn.net/wan1234512?type=blog
			     Gitee地址：https://gitee.com/snqx-lqh
  ******************************************************************************
  */
#include <reg52.h>
#include "main.h"

#include "seg.h"

#ifndef u8
#define u8  unsigned char
#endif

#ifndef u16
#define u16 unsigned int
#endif

void Timer0_Init(void);
void segBuffChange(void);

void main()
{
	Timer0_Init();
	while(1)
	{

	}
}

/**
  * @name    SegBuffChange
  * @brief   根据显示状态变量，修改现在的显示变量
  * @param   : [输入/出] 
  * @retval  返回值
  */
void SegBuffChange()
{
	segBuff[7] = 1;
	segBuff[6] = 2;
	segBuff[5] = 3;
	segBuff[4] = 4;
	segBuff[3] = 5;
	segBuff[2] = 6;
	segBuff[1] = 7;
	segBuff[0] = 8;
}

//仿真中用5ms，实际用2ms
void Timer0_Init(void)		//5毫秒@11.0592MHz
{
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0x00;				//设置定时初始值
	TH0 = 0xEE;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;
    EA = 1;
}
void Timer0() interrupt 1
{
	TL0 = 0x00;				//设置定时初始值
	TH0 = 0xEE;				//设置定时初始值
	segBuffChange();//显示BUFF改变
	SegShow();//数码管显示
}
