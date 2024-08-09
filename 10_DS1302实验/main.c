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
  * Date       : 2022-07-03         
  * Description: CSDN��ҳ�� https://blog.csdn.net/wan1234512?type=blog
			     Gitee��ַ��https://gitee.com/snqx-lqh
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
  * @brief   ������ʾ״̬�������޸����ڵ���ʾ����
  * @param   : [����/��] 
  * @retval  ����ֵ
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
  * @brief   ��������ʱ������״ֵ̬��1
  * @param   mode: 1 ���� 0 ������ 
  * @retval  ����ֵ
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
  * @brief   �������º��ִ�к���
  * @param   : [����/��] 
  * @retval  ����ֵ
  */
void ClockChangeFunction()
{
	if(isKey0 == 1)
	{
		isKey0 = 0;
		
	}else if(isKey1 == 1)
	{
		isKey1 = 0;
		if(showMode == 0)//�л�ʱ������ڵ���ʾ
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
	KeyScan(0);//����ɨ��
	SegBuffChange();//�����ֵ�ı�
	SegShow();//�������ʾ
}
