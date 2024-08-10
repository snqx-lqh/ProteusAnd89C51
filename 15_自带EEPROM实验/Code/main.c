/***************************************************************
    作品：EEPROM实验，开机还原关电前LED的亮灭状况
  单片机：STC89C52RC
    晶振：12M
编译环境：Keil uVision4 V9.00
***************************************************************/     
//#include <STC89C52RC.H>
#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char   
#define uint unsigned int
/****************特殊功能寄存器声明****************/
sfr ISP_DATA = 0xe2;   
sfr ISP_ADDRH = 0xe3;     
sfr ISP_ADDRL = 0xe4;   
sfr ISP_CMD = 0xe5;   
sfr ISP_TRIG = 0xe6;      
sfr ISP_CONTR = 0xe7;
sbit LED1 = P2^0;
sbit LED2 = P2^1;
sbit K1   = P3^2;                           //按钮1
sbit K2   = P3^3;                           //按钮2
void  cc(uint addr);
void  xcx(uint addr,uchar dat);
uchar dcx(uint addr);
void  Q0();
#ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint unsigned int
#endif
/**********************************
PIN口定义
**********************************/
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;
/**********************************
函数声明
**********************************/
/*在51单片机12MHZ时钟下的延时函数*/
void Lcd1602_Delay1ms(uint c);   //误差 0us
/*LCD1602写入8位命令子函数*/
void LcdWriteCom(uchar com);
/*LCD1602写入8位数据子函数*/      
void LcdWriteData(uchar dat)        ;
/*LCD1602初始化子程序*/               
void LcdInit();      
/*LCD1602写入字符串*/
void LCDWrite_String(uchar x, uchar y,uchar z, uchar *s);
/*设置LCD1602写入字符串的位置*/
void LCD_set_xy(uchar x, uchar y, uchar z);               
void IntConfiguration();
/*
uchar ON_Hour=0x07;          //初始开灯时间  07：00                                                                   1
uchar Warning_TempH=32;         //高温报警温度                                                                                   5
*/
uchar ON_Hour;          //初始开灯时间  07：00                                                                   1
uchar Warning_TempH;         //高温报警温度      
/*┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈
函数：主程序
┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈*/
void main(void)
{
   LcdInit();
   IntConfiguration();
//
/*
   cc(0x2000);                  // 擦除第1个扇区（2000h~21FFh）
   xcx(0x2000,ON_Hour);          // 对EEPROM区2002h写入2
   xcx(0x2001,Warning_TempH);          // 对EEPROM区2002h写入2
*/
//   
   while(1)
   {
   ON_Hour = dcx(0x2000);
   Warning_TempH = dcx(0x2001);
   if((ON_Hour==0x07)||(Warning_TempH==32))
   {
           LcdWriteCom(0x80);
          LCDWrite_String(0, 1, 7, "SUCCESS");
   }
   else
   LcdWriteCom(0x80);
   LCDWrite_String(0, 1, 5, "ERROR");
   }
   /*
   uchar V;
   V = dcx(0x2002);                          // 开机读取EEPROM区2002h数据,还原关电前LED的亮灭状况
   if(V == 2)          {LED1=0;LED2=1;}
   else if(V == 6){LED1=0;LED2=0;}
   while(1)
     {
      if(!K1)
            {
              while(!K1);
              LED1=0;LED2=1;
              cc(0x2000);                  // 擦除第1个扇区（2000h~21FFh）
              xcx(0x2002,2);          // 对EEPROM区2002h写入2
            }
          if(!K2)
            {
              while(!K2);
              LED1=0;LED2=0;
              cc(0x2000);                  // 擦除第1个扇区（2000h~21FFh）
              xcx(0x2002,6);                          // 对EEPROM区2002h写入6
            }
     }
         */
}
/*┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈
函数：擦除某一扇区（每个扇区512字节）
入口：addr = 某一扇区首地址                          
┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈*/
void cc(uint addr)
{      
// 打开 IAP 功能(ISP_CONTR.7)=1:允许编程改变Flash, 设置Flash操作等待时间
// 0x83(晶振<5M)   0x82(晶振<10M)   0x81(晶振<20M)   0x80(晶振<40M)
    ISP_CONTR = 0x81;  
    ISP_CMD   = 0x03;                  // 用户可以对"Data Flash/EEPROM区"进行扇区擦除
    ISP_ADDRL = addr;         // ISP/IAP操作时的地址寄存器低八位，
    ISP_ADDRH = addr>>8;      // ISP/IAP操作时的地址寄存器高八位。
        EA =0;   
    ISP_TRIG = 0x46;          // 在ISPEN(ISP_CONTR.7)=1时,对ISP_TRIG先写入46h，
    ISP_TRIG = 0xB9;          // 再写入B9h,ISP/IAP命令才会生效。
    _nop_();
    Q0();                                          // 关闭ISP/IAP
}
/*┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈
函数：写一字节
入口：addr = 扇区单元地址 , dat = 待写入数据
┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈*/
void xcx(uint addr,uchar dat)
{
    ISP_CONTR = 0x81;                  
    ISP_CMD   = 0x02;              // 用户可以对"Data Flash/EEPROM区"进行字节编程
    ISP_ADDRL = addr;        
    ISP_ADDRH = addr>>8;      
    ISP_DATA  = dat;          // 数据进ISP_DATA
    EA = 0;
    ISP_TRIG = 0x46;         
    ISP_TRIG = 0xB9;         
    _nop_();
    Q0();                                          // 关闭ISP/IAP
}
/*┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈
函数：读一字节
入口：addr = 扇区单元地址
出口：dat  = 读出的数据
┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈*/
uchar dcx(uint addr)
{   
    uchar dat;
      
        ISP_CONTR = 0x81;                  
    ISP_CMD   = 0x01;         // 用户可以对"Data Flash/EEPROM区"进行字节读
    ISP_ADDRL = addr;         
    ISP_ADDRH = addr>>8;      
    EA = 0;
    ISP_TRIG = 0x46;         
    ISP_TRIG = 0xB9;         
    _nop_();
    dat = ISP_DATA;                          // 取出数据
        Q0();                                          // 关闭ISP/IAP                  
        return dat;
}
/*┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈
函数：关闭ISP/IAP操作
┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈*/
void Q0()
{
    ISP_CONTR = 0;            // 关闭IAP功能
    ISP_CMD   = 0;            // 待机模式，无ISP操作
    ISP_TRIG  = 0;            // 关闭IAP功能, 清与ISP有关的特殊功能寄存器
        EA=1;
}
/*
STC89C52RC内部EEPROM详细地址表：
第一扇区                   第二扇区                    第三扇区                    第四扇区
起始地址  结束地址   起始地址   结束地址   起始地址   结束地址   起始地址    结束地址
2000h      21FFh       2200h       23FFh      2400h       25FFh       2600h        27FFH
第五扇区                    第六扇区                     第七扇区                    第八扇区
起始地址   结束地址   起始地址   结束地址    起始地址   结束地址   起始地址    结束地址
2800h       29FFh       2A00h      2BFFh        2C00h      2DFFh      2E00h        2FFFh
*/
/*******************************************************************************
* 函 数 名         : Lcd1602_Delay1ms
* 函数功能                   : 延时函数，延时1ms
* 输    入         : c
* 输    出         : 无
* 说    名         : 该函数是在12MHZ晶振下，12分频单片机的延时。
*******************************************************************************/
void Lcd1602_Delay1ms(uint c)   //误差 0us
{
    uchar a,b;
        for (; c>0; c--)
        {
                 for (b=199;b>0;b--)
                 {
                          for(a=1;a>0;a--);
                 }      
        }         
}
/*******************************************************************************
* 函 数 名         : void LCDWrite_String(uchar x, uchar y, uchar *s)
* 函数功能                   : 向LCD写入一个字符串
* 输    入         : x,y,*s
* 输    出         : 无
*******************************************************************************/
void LCDWrite_String(uchar x, uchar y, uchar z, uchar *s)        //x 0~15 , y 0,1,2,3
{
        LCD_set_xy(x,y,z);
        while(*s)
        {
                LcdWriteData(*s);
                s++;
        }
}
/*******************************************************************************
* 函 数 名         : void LCD_set_xy(uchar x, uchar y,uchar z)
* 函数功能                   : 指定向LCD写入字符串的位置
* 输    入         : x,y,z                 //x:横坐标 y:纵坐标 z:字符串长度
* 输    出         : 无
*******************************************************************************/
void LCD_set_xy(uchar x,uchar y,uchar z)
{
        uchar i;
        if(y==0)
        {
                LcdWriteCom(0x80+x);
                for(i=0;i<z;i++)
                {
                        LcdWriteData(' ');
                }
                LcdWriteCom(0x80+x);
        }
        if(y==1)
        {
                LcdWriteCom(0xc0+x);
                for(i=0;i<z;i++)
                {
                        LcdWriteData(' ');
                }
                LcdWriteCom(0xc0+x);
        }
        if(y==2)
        {
                LcdWriteCom(0x94+x);
                for(i=0;i<z;i++)
                {
                        LcdWriteData(' ');
                }
                LcdWriteCom(0x94+x);
        }
        if(y==3)
        {
                LcdWriteCom(0xd4+x);
                for(i=0;i<z;i++)
                {
                        LcdWriteData(' ');
                }
                LcdWriteCom(0xd4+x);
        }
}
/*******************************************************************************
* 函 数 名         : LcdWriteCom
* 函数功能                   : 向LCD写入一个字节的命令
* 输    入         : com
* 输    出         : 无
*******************************************************************************/
#ifndef         LCD1602_4PINS         //当没有定义这个LCD1602_4PINS时
void LcdWriteCom(uchar com)          //写入命令
{
        LCD1602_E = 0;     //使能
        LCD1602_RS = 0;           //选择发送命令
        LCD1602_RW = 0;           //选择写入
      
        LCD1602_DATAPINS = com;     //放入命令
        Lcd1602_Delay1ms(1);                //等待数据稳定
        LCD1602_E = 1;                  //写入时序
        Lcd1602_Delay1ms(5);          //保持时间
        LCD1602_E = 0;
}
#else
void LcdWriteCom(uchar com)          //写入命令
{
        LCD1602_E = 0;         //使能清零
        LCD1602_RS = 0;         //选择写入命令
        LCD1602_RW = 0;         //选择写入
        LCD1602_DATAPINS = com;        //由于4位的接线是接到P0口的高四位，所以传送高四位不用改
        Lcd1602_Delay1ms(1);
        LCD1602_E = 1;         //写入时序
        Lcd1602_Delay1ms(5);
        LCD1602_E = 0;
//        Lcd1602_Delay1ms(1);
        LCD1602_DATAPINS = com << 4; //发送低四位
        Lcd1602_Delay1ms(1);
        LCD1602_E = 1;         //写入时序
        Lcd1602_Delay1ms(5);
        LCD1602_E = 0;
}
#endif
/*******************************************************************************
* 函 数 名         : LcdWriteData
* 函数功能                   : 向LCD写入一个字节的数据
* 输    入         : dat
* 输    出         : 无
*******************************************************************************/                  
#ifndef         LCD1602_4PINS                  
void LcdWriteData(uchar dat)                        //写入数据
{
        LCD1602_E = 0;        //使能清零
        LCD1602_RS = 1;        //选择输入数据
        LCD1602_RW = 0;        //选择写入
        LCD1602_DATAPINS = dat; //写入数据
        Lcd1602_Delay1ms(1);
        LCD1602_E = 1;   //写入时序
        Lcd1602_Delay1ms(5);   //保持时间
        LCD1602_E = 0;
}
#else
void LcdWriteData(uchar dat)                        //写入数据
{
        LCD1602_E = 0;          //使能清零
        LCD1602_RS = 1;          //选择写入数据
        LCD1602_RW = 0;          //选择写入
        LCD1602_DATAPINS = dat;        //由于4位的接线是接到P0口的高四位，所以传送高四位不用改
        Lcd1602_Delay1ms(1);
        LCD1602_E = 1;          //写入时序
        Lcd1602_Delay1ms(5);
        LCD1602_E = 0;
        LCD1602_DATAPINS = dat << 4; //写入低四位
        Lcd1602_Delay1ms(1);
        LCD1602_E = 1;          //写入时序
        Lcd1602_Delay1ms(5);
        LCD1602_E = 0;
}
#endif
/*******************************************************************************
* 函 数 名       : LcdInit()
* 函数功能                 : 初始化LCD屏
* 输    入       : 无
* 输    出       : 无
*******************************************************************************/                  
#ifndef                LCD1602_4PINS
void LcdInit()                                                  //LCD初始化子程序
{
        LcdWriteCom(0x38);  //开显示
        LcdWriteCom(0x0c);  //开显示不显示光标
        LcdWriteCom(0x06);  //写一个指针加1
        LcdWriteCom(0x01);  //清屏
        LcdWriteCom(0x80);  //设置数据指针起点
}
#else
void LcdInit()                                                  //LCD初始化子程序
{
        LcdWriteCom(0x32);         //将8位总线转为4位总线
        LcdWriteCom(0x28);         //在四位线下的初始化
        LcdWriteCom(0x0c);  //开显示不显示光标
        LcdWriteCom(0x06);  //写一个指针加1
        LcdWriteCom(0x01);  //清屏
        LcdWriteCom(0x80);  //设置数据指针起点
}
#endif
void IntConfiguration()
{
        //设置INT0
        IT0=1;//跳变沿出发方式（下降沿）
        EX0=1;//打开INT0的中断允许。
        //设置INT1
        IT1=1;//跳变沿出发方式（下降沿）
        EX1=1;//打开INT0的中断允许。
        EA=1;//打开总中断      
}
void Int0() interrupt 1                 
{
   cc(0x2000);                  // 擦除第1个扇区（2000h~21FFh）
   xcx(0x2000,0x07);          // 对EEPROM区2002h写入2
   xcx(0x2001,32);
   LcdInit();
}
void Int1() interrupt 2                 
{
   cc(0x2000);                  // 擦除第1个扇区（2000h~21FFh）
   xcx(0x2000,0x08);          // 对EEPROM区2002h写入2
   xcx(0x2001,33);
   LcdInit();
}