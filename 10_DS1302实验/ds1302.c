#include "DS1302.h"

//为1时写入初始设置的time[]变量中的时间，要是为0则初始不写入
#define FIRST_WRITE 1

u8 code readaddre[7]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};
u8 code writeaddre[7]={0x80,0x82,0x84,0x86,0x88,0x8a,0x8c};
u8 time[7]={0x55,0X59,0x22,0x09,0x07,0x06,0x20};//秒，分，时，日，月，周，年
u8 second,minute,hour,day,month,week,year;//存储实际的时间日期
u8 secondTemp,minuteTemp,hourTemp,dayTemp,monthTemp,weekTemp,yearTemp;//存储修改时的时间日期

void ds1302write(u8 addre,u8 dat)
{
	u8 i;
	RST=0;
	_nop_();
	SCK=0;
	_nop_();
	RST=1;
	_nop_();
	for (i=0;i<8;i++)
	{
		IO=addre&0x01;
		addre>>=1;
		SCK=1;
		_nop_();
		SCK=0;
		_nop_();
	}
	for (i=0;i<8;i++)
	{
		IO=dat&0x01;
		dat>>=1;
		SCK=1;
		_nop_();
		SCK=0;
		_nop_();
	}
	RST=0;
}
u8 ds1302read(u8 addre)
{
	u8 i,dat1,dat;
	RST=0;
	_nop_();
	SCK=0;
	_nop_();
	RST=1;
	_nop_();
	for (i=0;i<8;i++)
	{
		IO=addre&0x01;
		addre>>=1;
		SCK=1;
		_nop_();
		SCK=0;
		_nop_();
	}
	_nop_();
	for (i=0;i<8;i++)
	{
		dat1=IO;
		dat=(dat>>1)|(dat1<<7);
		SCK=1;
		_nop_();
		SCK=0;
		_nop_();
	}
	RST=0;
	_nop_();
	SCK=1;
	_nop_();
	IO=1;
	_nop_();
	IO=0;
	_nop_();
	return dat;
}

void ds1302init()
{
#if FIRST_WRITE == 1
	u8 i;
	ds1302write(0x8e,0x00);
	for (i=0;i<7;i++)
	{
		ds1302write(writeaddre[i],time[i]);
	}
	ds1302write(0x8e,0x80);
#endif
}

void ds1302readtime()
{
	u8 i;
	for (i=0;i<7;i++)
	{
		time[i]=ds1302read(readaddre[i]);
	}
	second = (time[0]/16)*10+(time[0]&0x0f);
	minute = (time[1]/16)*10+(time[1]&0x0f);
	hour   = (time[2]/16)*10+(time[2]&0x0f);
	day    = (time[3]/16)*10+(time[3]&0x0f);
	month  = (time[4]/16)*10+(time[4]&0x0f);
	week   = (time[5]/16)*10+(time[5]&0x0f);
	year   = (time[6]/16)*10+(time[6]&0x0f);
}

void ds1302writetime()
{
	u8 i;
	ds1302write(0x8e,0x00);
	time[0] = (((secondTemp/10)<<4) + (secondTemp%10));
	time[1] = (((minuteTemp/10)<<4) + (minuteTemp%10));
	time[2] = (((hourTemp/10)<<4)   + (hourTemp%10));
	time[3] = (((dayTemp/10)<<4)    + (dayTemp%10));
	time[4] = (((monthTemp/10)<<4)  + (monthTemp%10));
	time[5] = (((weekTemp/10)<<4)   + (weekTemp%10));
	time[6] = (((yearTemp/10)<<4)   + (yearTemp%10));
	
	for (i=0;i<7;i++)
	{
		ds1302write(writeaddre[i],time[i]);
	}
	ds1302write(0x8e,0x80);
}