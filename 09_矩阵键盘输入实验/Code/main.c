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
  * Date       : 2023-06-14         
  * Description: CSDN主页： https://blog.csdn.net/wan1234512?type=blog
			     Gitee地址：https://gitee.com/snqx-lqh
  ******************************************************************************
  */
#include <reg52.h>
#include "main.h"
#include <stdio.h>
#include <string.h>

#include "KeyScan.h"

void KeyDownFunction(void);
void Timer0Init(void);

void main()
{
	Timer0Init();
	while(1)
	{
        KeyDownFunction();
	}
}

/**
  * @Name    KeyDownFunction
  * @brief   按键按下后的功能函数
  * @param   : [输入/出] 
  * @retval  
 **/
void KeyDownFunction()
{
    u8 KeyValueTemp = 0;
    if(KeyState == 1)
    {
        KeyValueTemp = KeyValue;
        if(KeyValue != 0)//实现单次检测按键
            KeyValue = 0;
        if(KeyValueTemp == KEY_Open )//使能开锁功能函数
        {
           P2 = 0XAA;
        }else if(KeyValueTemp == KEY_Close)//使能关锁功能函数
        {
           P2 = 0XBB;
        }else if(KeyValueTemp == KEY_Change)//使能修改密码功能函数
        {
           P2 = 0XCC;
        }
      
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
    KeyScan();

}
