#include "LCD12864.h"

/****************************************************************************
函数功能:LCD延时程序
入口参数:t
出口参数:
****************************************************************************/
void LCDdelay(unsigned int t)
{
	unsigned int i,j;
	for(i=0;i<t;i++);
	for(j=0;j<10;j++);
}
/****************************************************************************
状态检查，LCD是否忙
*****************************************************************************/
void CheckState()		
{
   unsigned char dat,DATA;//状态信息（判断是否忙）
   LCDDi=0; // 数据\指令选择，D/I（RS）="L" ，表示 DB7∽DB0 为显示指令数据 
   LCDRW=1; //R/W="H" ，E="H"数据被读到DB7∽DB0 
   do
   {
      DATA=0x00;
      LCDEnable=1;	//EN下降源
	  LCDdelay(2);//延时
	  dat=DATA;
      LCDEnable=0;
      dat=0x80 & dat; //仅当第7位为0时才可操作(判别busy信号)
    }
    while(!(dat==0x00));
}
/*****************************************************************************
函数功能:写命令到LCD程序，RS(DI)=L,RW=L,EN=H，即来一个脉冲写一次
入口参数:cmdcode
出口参数:
*****************************************************************************/
void write_com(unsigned char cmdcode)
{
    CheckState();//检测LCD是否忙
	LCDDi=0;
	LCDRW=0;
	P1=cmdcode;		
	LCDdelay(2);
	LCDEnable=1;
	LCDdelay(2);
	LCDEnable=0;
}
/*****************************************************************************
函数功能:LCD初始化程序
入口参数:
出口参数:
*****************************************************************************/
void init_lcd()
{
	LCDdelay(100);	
	LCDMcs=1;//刚开始关闭两屏
	LCDScs=1;
	LCDdelay(100);
	write_com(LCDLCDDisp_Off);	 //写初始化命令
	write_com(Page_Add+0);
	write_com(Start_Line+0);
	write_com(LCDCol_Add+0);
	write_com(LCDLCDDisp_On);
}
/*****************************************************************************
函数功能:写数据到LCD程序，RS(DI)=H,RW=L,EN=H，即来一个脉冲写一次
入口参数:LCDDispdata
出口参数:
*****************************************************************************/
void write_data(unsigned char LCDDispdata)
{
    CheckState();//检测LCD是否忙
	LCDDi=1;
	LCDRW=0;
	P1=LCDDispdata;
	LCDdelay(2);
	LCDEnable=1;
	LCDdelay(2);
	LCDEnable=0;
}
/*****************************************************************************
函数功能:清除LCD内存程序
入口参数:pag,col,hzk
出口参数:
*****************************************************************************/
void Clr_Scr()
{
	unsigned char j,k;
	LCDMcs=0; //左、右屏均开显示
	LCDScs=0;
 	write_com(Page_Add+0);
 	write_com(LCDCol_Add+0);
 	for(k=0;k<8;k++)//控制页数0-7，共8页
 	{
		write_com(Page_Add+k); //每页每页进行写
  		for(j=0;j<64;j++)  //每页最多可写32个中文文字或64个ASCII字符
		{
      		write_com(LCDCol_Add+j);
			write_data(0x00);//控制列数0-63，共64列，写点内容，列地址自动加1
		}
	}
}
/*****************************************************************************
函数功能:指定位置显示汉字16*16程序
入口参数:page,column,hzk
出口参数:
*****************************************************************************/
void hz_LCDDisp16(unsigned char page,unsigned char column, unsigned char code *hzk)
{
	unsigned char j=0,i=0;
	for(j=0;j<2;j++)
	{
		write_com(Page_Add+page+j);
		write_com(LCDCol_Add+column);
		for(i=0;i<16;i++) 
			write_data(hzk[16*j+i]);
	}
}


