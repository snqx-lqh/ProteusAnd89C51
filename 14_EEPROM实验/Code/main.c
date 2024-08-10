#include <reg52.h>
#include <intrins.h>
 
#define unchar unsigned char
#define uint unsigned int
	
unchar code dis_table[] = "0123456789";
	
sbit button = P3^2;		//定义按键
sbit lcden = P2^7;		//定义lcd的E端口
sbit lcdrw = P2^5;		//定义lcd的rw端口
sbit lcdrs = P2^6;		//定义lcd的rs端口
sbit SCL = P2^1;			//定义SCL时钟线端口
sbit SDA = P2^0;			//定义SDA数据线端口
 
//IIC延时函数，延时必须精确，否则无法准确传输
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
 
//往LCD1602中写命令
void Write_Com(unchar com)
{
	lcdrs = 0;				//lcdrs为低电平时，选择指令寄存器
	P0 = com;
	DelayMs(5);
	lcden = 1;
	DelayMs(5);
	lcden = 0;
}
 
//往LCD1602中写数据
void Write_data(unchar date)
{
	lcdrs = 1;				//lcdrs为高电平时，选择数据寄存器
	P0 = date;
	DelayMs(5);
	lcden = 1;				//当lcden由高电平变为低电平时，LCD1602开始执行命令
	DelayMs(5);
	lcden = 0;
}
 
//LCD1602的初始化函数
void init()
{
	lcdrw = 0;				//lcdrw高电平时为读操作，低电平时为写操作 
	lcden = 0;
	Write_Com(0x38);
	Write_Com(0x0c);
	Write_Com(0x06);
	Write_Com(0x01);
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
 
//显示数字函数
void display(unchar date)
{
	Write_Com(0x80);
	Write_data(dis_table[date/100]);						//显示百位
	Write_data(dis_table[date%100/10]);					//显示十位
	Write_data(dis_table[date%10]);							//显示个位
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
				Write_add(num,0x00);	//将num写入到0x00地址处
			}
			while(button == 0)
			{
				;
			}
		}
		NUM = Read_add(0x00);			//将0x00处的数据读取出来
		display(NUM);
	}
}