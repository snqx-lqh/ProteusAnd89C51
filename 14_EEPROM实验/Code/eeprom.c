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

//IIC初始化函数
void IIC_init()
{
	SCL = 1;
	Delay();
	SDA = 1;
	Delay();
}
 
//IIC起始信号函数
void IIC_start()
{
	//当SCL信号为高电平期间，SDA出现下降沿时，就是起始信号
	SDA = 1;
	Delay();
	SCL = 1;
	Delay();
	SDA = 0;
	Delay();
}
 
//IIC应答信号函数
void IIC_respons()
{
	//在SCL高电平期间，讲SDA线拉低，产生应答信号，表明数据传输成功
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
 
//定义停止信号函数
void IIC_stop()
{
	//当SCL在高电平时，SDA产生一个上升沿信号为停止信号
	SDA = 0;
	Delay();
	SCL = 1;
	Delay();
	SDA = 1;
	Delay();
}
 
//写一个字节函数
void IIC_writebyte(unchar date)
{
	unchar i,temp;
	temp = date;
	for(i = 0;i < 8;i++)
	{
		temp = temp << 1;	//溢出的一位自动保存到寄存器CY中
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
 
//IIC读一个字节函数
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
 
//往AT24C02的地址中写数据
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
 
//从AT24C02的地址中读数据
unchar Read_add(unchar address)
{
	unchar date;
	IIC_start();
	IIC_writebyte(0xa0);		//AT24C02的地址为0xa0时是写入
	IIC_respons();
	IIC_writebyte(address);
	IIC_respons();
	IIC_start();
	IIC_writebyte(0xa1);		//AT24C02的地址为0xa1时是读
	IIC_respons();
	date = IIC_readbyte();	//将数据读取到date中
	IIC_stop();							//停止信号
	return date;
}