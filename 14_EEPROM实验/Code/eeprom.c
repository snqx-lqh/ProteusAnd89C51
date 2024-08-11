#include "eeprom.h"
#include <intrins.h>

void Delay()
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
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