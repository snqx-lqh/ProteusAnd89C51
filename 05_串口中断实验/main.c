#include "reg52.h"

#define u8  unsigned char
#define u16 unsigned int

sbit LED = P2^0;

void UartInit(void)		//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	TL1 = 0xFD;			//���ö�ʱ��ʼֵ
	TH1 = 0xFD;			//���ö�ʱ����ֵ
	ET1 = 0;			//��ֹ��ʱ���ж�
	TR1 = 1;			//��ʱ��1��ʼ��ʱ
	ES = 1;             //�򿪴����ж�
	EA = 1;             //��ȫ���ж�
}

void SendBuffLen(u8 *str,u8 len)
{
	while(len != 0)
	{
		SBUF = *str;
		while(!TI);
		TI = 0;
		str++;
		len --;
	}
}

char str[] = "hello world\r\n";

int main()
{
	UartInit();
	SendBuffLen(str,sizeof(str));
	while(1)
	{
		
	}
}

void UartRoutine(void) interrupt 4
{
	u8 res;	
	if(RI)
	{
		res = SBUF;
		if(res == 0x01)
		{
			LED = 0;
			SendBuffLen("hello world\r\n",sizeof("hello world\r\n"));
		}else
		{
			LED = 1;
			SendBuffLen("�����ַ�����\r\n",sizeof("�����ַ�����\r\n"));
		}
		RI = 0;
	}	
}