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
  * @brief   ������ʾ״̬�������޸����ڵ���ʾ����
  * @param   : [����/��] 
  * @retval  ����ֵ
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

//��������5ms��ʵ����2ms
void Timer0_Init(void)		//5����@11.0592MHz
{
	TMOD |= 0x01;			//���ö�ʱ��ģʽ
	TL0 = 0x00;				//���ö�ʱ��ʼֵ
	TH0 = 0xEE;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	ET0 = 1;
    EA = 1;
}
void Timer0() interrupt 1
{
	TL0 = 0x00;				//���ö�ʱ��ʼֵ
	TH0 = 0xEE;				//���ö�ʱ��ʼֵ
	segBuffChange();//��ʾBUFF�ı�
	SegShow();//�������ʾ
}
