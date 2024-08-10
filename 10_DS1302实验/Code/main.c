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
#include "ds1302.h"

void Timer0Init(void);
void segBuffChange(void);
void ClockChangeFunction(void);

u8 showMode = 0;

sbit KEY0 = P3^0;
sbit KEY1 = P3^1;
sbit KEY2 = P3^2;
sbit KEY3 = P3^3;

u8 isKey0 = 0;
u8 isKey1 = 0;
u8 isKey2 = 0;
u8 isKey3 = 0;

void main()
{
	ds1302init();
	Timer0Init();
	while(1)
	{
		ds1302readtime();
		ClockChangeFunction();
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
	if(showMode == 0)
	{
		segBuff[5] = second%10;
		segBuff[4] = second/10;
		segBuff[3] = minute%10;
		segBuff[2] = minute/10;
		segBuff[1] = hour%10;
		segBuff[0] = hour/10;
	}else if(showMode == 1)
	{
		segBuff[5] = day%10;
		segBuff[4] = day/10;
		segBuff[3] = month%10;
		segBuff[2] = month/10;
		segBuff[1] = year%10;
		segBuff[0] = year/10;
	}
}

/**
  * @name    KeyScan
  * @brief   按键按下时，各个状态值变1
  * @param   mode: 1 连续 0 不连续 
  * @retval  返回值
  */
void KeyScan(u8 mode)
{
    static int keyCount = 0;
    static int keyState = 0;
    if(mode == 1) keyState=0;
    if (keyState == 0 && (KEY0 == 0||KEY1 == 0||KEY2 == 0||KEY3 == 0))
    {
        keyCount++;
        if(keyCount>2)
        {
            keyState = 1;
            keyCount=0;
            if(KEY0 == 0) isKey0 = 1;
            else if(KEY1 == 0) isKey1 = 1;
			else if(KEY2 == 0) isKey2 = 1;
			else if(KEY3 == 0) isKey3 = 1;
        }
    } else if (KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && KEY3 == 1)
    {
        keyState = 0;
    }
}

/**
  * @name    ClockChangeFunction
  * @brief   按键按下后的执行函数
  * @param   : [输入/出] 
  * @retval  返回值
  */
void ClockChangeFunction()
{
	if(isKey0 == 1)
	{
		isKey0 = 0;
		
	}else if(isKey1 == 1)
	{
		isKey1 = 0;
		if(showMode == 0)//切换时间和日期的显示
			showMode = 1;
		else if(showMode == 1)
			showMode = 0;
	}else if(isKey2 == 1)
	{
		isKey2 = 0;
		
	}else if(isKey3 == 1)
	{
		isKey3 = 0;
	}
}

void Timer0Init(void) //5毫秒@11.0592MHz
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
    TL0 = 0x00; //设置定时0初始值
    TH0 = 0xEE; //设置定时0初始值
	KeyScan(0);//按键扫描
	SegBuffChange();//数码管值改变
	SegShow();//数码管显示
}
