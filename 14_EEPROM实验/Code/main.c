#include <reg52.h>
#include <intrins.h>
 
#define unchar unsigned char
#define uint unsigned int
	
unchar code dis_table[] = "0123456789";
	
sbit button = P3^2;		//���尴��
sbit lcden = P2^7;		//����lcd��E�˿�
sbit lcdrw = P2^5;		//����lcd��rw�˿�
sbit lcdrs = P2^6;		//����lcd��rs�˿�
sbit SCL = P2^1;			//����SCLʱ���߶˿�
sbit SDA = P2^0;			//����SDA�����߶˿�
 
//IIC��ʱ��������ʱ���뾫ȷ�������޷�׼ȷ����
void Delay()
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}
 
void DelayMs(uint ms)
{
	uint i;
	while(ms--)
	{
		for(i = 110;i > 0;i--)
		{
			;
		}
	}
}
 
//��LCD1602��д����
void Write_Com(unchar com)
{
	lcdrs = 0;				//lcdrsΪ�͵�ƽʱ��ѡ��ָ��Ĵ���
	P0 = com;
	DelayMs(5);
	lcden = 1;
	DelayMs(5);
	lcden = 0;
}
 
//��LCD1602��д����
void Write_data(unchar date)
{
	lcdrs = 1;				//lcdrsΪ�ߵ�ƽʱ��ѡ�����ݼĴ���
	P0 = date;
	DelayMs(5);
	lcden = 1;				//��lcden�ɸߵ�ƽ��Ϊ�͵�ƽʱ��LCD1602��ʼִ������
	DelayMs(5);
	lcden = 0;
}
 
//LCD1602�ĳ�ʼ������
void init()
{
	lcdrw = 0;				//lcdrw�ߵ�ƽʱΪ���������͵�ƽʱΪд���� 
	lcden = 0;
	Write_Com(0x38);
	Write_Com(0x0c);
	Write_Com(0x06);
	Write_Com(0x01);
}
 
//IIC��ʼ������
void IIC_init()
{
	SCL = 1;
	Delay();
	SDA = 1;
	Delay();
}
 
//IIC��ʼ�źź���
void IIC_start()
{
	//��SCL�ź�Ϊ�ߵ�ƽ�ڼ䣬SDA�����½���ʱ��������ʼ�ź�
	SDA = 1;
	Delay();
	SCL = 1;
	Delay();
	SDA = 0;
	Delay();
}
 
//IICӦ���źź���
void IIC_respons()
{
	//��SCL�ߵ�ƽ�ڼ䣬��SDA�����ͣ�����Ӧ���źţ��������ݴ���ɹ�
	unchar i = 0;
	SCL = 1;
	Delay();
	while(SDA == 1 && (i < 255))
	{
		i ++;
	}
	SCL = 0;
	Delay();
}
 
//����ֹͣ�źź���
void IIC_stop()
{
	//��SCL�ڸߵ�ƽʱ��SDA����һ���������ź�Ϊֹͣ�ź�
	SDA = 0;
	Delay();
	SCL = 1;
	Delay();
	SDA = 1;
	Delay();
}
 
//дһ���ֽں���
void IIC_writebyte(unchar date)
{
	unchar i,temp;
	temp = date;
	for(i = 0;i < 8;i++)
	{
		temp = temp << 1;	//�����һλ�Զ����浽�Ĵ���CY��
		SCL = 0;
		Delay();
		SDA = CY;
		Delay();
		SCL = 1;
		Delay();
	}
	SCL = 0;
	Delay();
	SCL = 1;
	Delay();
}
 
//IIC��һ���ֽں���
unchar IIC_readbyte()
{
	unchar i,Data;
	SCL = 0;
	Delay();
	SDA = 1;
	for(i = 0;i < 8;i++)
	{
		SCL = 1;
		Delay();
		SDA = 1;
		Data = (Data << 1) | SDA;
		SCL = 0;
		Delay();
	}
	Delay();
	return Data;
}
 
//��AT24C02�ĵ�ַ��д����
void Write_add(unchar date,unchar address)
{
	IIC_start();
	IIC_writebyte(0xa0);
	IIC_respons();
	IIC_writebyte(address);
	IIC_respons();
	IIC_writebyte(date);
	IIC_respons();
	IIC_stop();
}
 
//��AT24C02�ĵ�ַ�ж�����
unchar Read_add(unchar address)
{
	unchar date;
	IIC_start();
	IIC_writebyte(0xa0);		//AT24C02�ĵ�ַΪ0xa0ʱ��д��
	IIC_respons();
	IIC_writebyte(address);
	IIC_respons();
	IIC_start();
	IIC_writebyte(0xa1);		//AT24C02�ĵ�ַΪ0xa1ʱ�Ƕ�
	IIC_respons();
	date = IIC_readbyte();	//�����ݶ�ȡ��date��
	IIC_stop();							//ֹͣ�ź�
	return date;
}
 
//��ʾ���ֺ���
void display(unchar date)
{
	Write_Com(0x80);
	Write_data(dis_table[date/100]);						//��ʾ��λ
	Write_data(dis_table[date%100/10]);					//��ʾʮλ
	Write_data(dis_table[date%10]);							//��ʾ��λ
}
 
void main()
{
	unchar num,NUM;
	init();
	IIC_init();
	
	while(1)
	{
		if(button == 0)
		{
			DelayMs(10);
			if(button == 0)
			{
				num = Read_add(0x00);
				num ++;
				Write_add(num,0x00);	//��numд�뵽0x00��ַ��
			}
			while(button == 0)
			{
				;
			}
		}
		NUM = Read_add(0x00);			//��0x00�������ݶ�ȡ����
		display(NUM);
	}
}