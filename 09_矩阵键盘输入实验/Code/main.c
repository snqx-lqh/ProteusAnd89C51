/**
  ************************************* Copyright ****************************** 
  *
  *                 (C) Copyright 2022, LQH, China, GCU.
  *                                All Rights Reserved
  *                              
  *                                      By LQH
  *                       
  * FileName   : main.c   	
  * Author     : ����Ǳ��(snqx-lgh)			
  * Date       : 2023-06-14         
  * Description: CSDN��ҳ�� https://blog.csdn.net/wan1234512?type=blog
			     Gitee��ַ��https://gitee.com/snqx-lqh
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
  * @brief   �������º�Ĺ��ܺ���
  * @param   : [����/��] 
  * @retval  
 **/
void KeyDownFunction()
{
    u8 KeyValueTemp = 0;
    if(KeyState == 1)
    {
        KeyValueTemp = KeyValue;
        if(KeyValue != 0)//ʵ�ֵ��μ�ⰴ��
            KeyValue = 0;
        if(KeyValueTemp == KEY_Open )//ʹ�ܿ������ܺ���
        {
           P2 = 0XAA;
        }else if(KeyValueTemp == KEY_Close)//ʹ�ܹ������ܺ���
        {
           P2 = 0XBB;
        }else if(KeyValueTemp == KEY_Change)//ʹ���޸����빦�ܺ���
        {
           P2 = 0XCC;
        }
      
    }
}

void Timer0Init(void) //5����@11.0592MHz
{
    TMOD = 0x01; //���ö�ʱ��ģʽ
    TL0 = 0x00;  //���ö�ʱ0��ʼֵ
    TH0 = 0xEE;  //���ö�ʱ0��ʼֵ
    TF0 = 0;     //���TF0��־
    TR0 = 1;     //��ʱ��0��ʼ��ʱ
    ET0 = 1;
    EA = 1;
}

void Timer0() interrupt 1
{
    TL0 = 0x00; //���ö�ʱ0��ʼֵ
    TH0 = 0xEE; //���ö�ʱ0��ʼֵ
    KeyScan();

}
