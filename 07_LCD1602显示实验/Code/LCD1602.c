#include "LCD1602.h"

/**
  * @name    Lcd1602_Delay1ms
  * @brief   延时函数，延时1ms
  * @param   : [输入/出] 
  * @retval  返回值
  */
void Lcd1602_Delay1ms(u16 c)   //误差 0us
{
    u8 a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}
    	
}
/**
  * @name    LcdWriteCom
  * @brief   向LCD写入一个字节的命令
  * @param   com
  * @retval  返回值
  */
void LcdWriteCom(u8 com)	  //写入命令
{
	LCD1602_E = 0;     //使能
	LCD1602_RS = 0;	   //选择发送命令
	LCD1602_RW = 0;	   //选择写入
	
	LCD1602_DATAPINS = com;     //放入命令
	Lcd1602_Delay1ms(1);		//等待数据稳定

	LCD1602_E = 1;	          //写入时序
	Lcd1602_Delay1ms(5);	  //保持时间
	LCD1602_E = 0;
}
/**
  * @name    LcdWriteData
  * @brief   向LCD写入一个字节的数据
  * @param   dat
  * @retval  返回值
  */
void LcdWriteData(u8 dat)			//写入数据
{
	LCD1602_E = 0;	//使能清零
	LCD1602_RS = 1;	//选择输入数据
	LCD1602_RW = 0;	//选择写入

	LCD1602_DATAPINS = dat; //写入数据
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;   //写入时序
	Lcd1602_Delay1ms(5);   //保持时间
	LCD1602_E = 0;
}	
/**
  * @name    LcdInit
  * @brief   初始化LCD屏
  * @param   无
  * @retval  返回值
  */
void LcdInit()						  //LCD初始化子程序
{
 	LcdWriteCom(0x38);  //开显示
	LcdWriteCom(0x0c);  //开显示不显示光标
	LcdWriteCom(0x06);  //写一个指针加1
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x80);  //设置数据指针起点
}	
/**
  * @name    LcdSetCursor
  * @brief   设置显示 RAM 起始地址，亦即光标位置，(x,y)-对应屏幕上的字符坐标
  * @param   x y
  * @retval  返回值
  */
void LcdSetCursor(u8 x, u8 y)
{
	u8 addr;

	if (y == 0) //由输入的屏幕坐标计算显示 RAM 的地址
		addr = 0x00 + x; //第一行字符地址从 0x00 起始
	else
		addr = 0x40 + x; //第二行字符地址从 0x40 起始
	LcdWriteCom(addr | 0x80); //设置 RAM 地址
}
/**
  * @name    LcdShowStr
  * @brief   在液晶上显示字符串，(x,y)-对应屏幕上的起始坐标，str-字符串指针
  * @param   x y str
  * @retval  返回值
  */
void LcdShowStr(u8 x, u8 y, u8 *str)
{
	LcdSetCursor(x, y); //设置起始地址
	while (*str != '\0') //连续写入字符串数据，直到检测到结束符
	{
		LcdWriteData(*str++); //先取 str 指向的数据，然后 str 自加 1
	}
}
