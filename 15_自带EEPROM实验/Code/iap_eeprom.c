#include "iap_eeprom.h"
#include <reg52.h>
#include <intrins.h>

/**********打开ISP/IAP功能**************/   
void ISP_IAP_Enable(void)
{
    EA = 0;  //关中断  
    ISP_CONTR = ISP_CONTR & 0x18;  
    ISP_CONTR = ISP_CONTR | WaitTime; // 设置等待时间
    ISP_CONTR = ISP_CONTR | 0x80;   //允许ISP/IAP操作
}
 
/**********关闭ISP/IAP功能**************/   
void ISP_IAP_Disable(void)
{
	 ISP_CONTR = ISP_CONTR & 0x7f; //禁止ISP/IAP操作
     ISP_CMD = 0x00;    //去除ISP/IAP命令
	 ISP_TRIG = 0x00;   //防止ISP/IAP命令无触发
	 EA   =   1;        // 开中断 
}
 
/**********触发ISP/IAP**************/  
void ISPTrig(void)
{
	 ISP_TRIG = 0x46;  //先送46h，再送B9h到ISP/IAP触发寄存器，每次都需如此
	 ISP_TRIG = 0xb9;  //送完B9h后，ISP/IAP命令立即被触发启动
	 _nop_();
}
 
/**********字节读**************/
unsigned char byte_read(unsigned int byte_addr)
{
     unsigned char  dat = 0;    //读EEPROM数据缓存
 
	 EA = 0;     //关中断
	 ISP_ADDRH = (unsigned char)(byte_addr >> 8);     //送地址高字节
	 ISP_ADDRL = (unsigned char)(byte_addr & 0x00ff); //送地址低字节
     ISP_IAP_Enable();             //打开ISP/IAP功能
	 ISP_CMD   = ISP_CMD & 0xf8;   //清除ISP_CMD寄存器低3位
	 ISP_CMD   = ISP_CMD | RdCommand; //写入读数据命令 
	 ISPTrig();                //触发ISP/IAP
	 dat = ISP_DATA;           //将ISP_DATA寄存器中的数据保存起来
     ISP_IAP_Disable();        //关闭ISP/IAP功能 
	 EA  = 1;           //使能中断
	 return dat;        //返回读到的数据
}
 
/**********字节写**************/
void byte_write(unsigned int byte_addr,unsigned char Orig_data)
{
	 EA  = 0;  //关中断
	 ISP_ADDRH = (unsigned char)(byte_addr >> 8);       //送地址高字节
	 ISP_ADDRL = (unsigned char)(byte_addr & 0x00ff);   //送地址低字节
	 ISP_IAP_Enable();                   //打开ISP/IAP功能
     ISP_CMD  = ISP_CMD & 0xf8;         //清除ISP_CMD寄存器低3位
	 ISP_CMD  = ISP_CMD | PrgCommand;   //写入写数据命令 
	 ISP_DATA = Orig_data;      //写入数据到ISP_DATA寄存器
	 ISPTrig();                //触发ISP/IAP
	 ISP_IAP_Disable();        //关闭ISP/IAP功能 
	 EA =1;            //使能中断
}
/**********扇区擦除**************/
void SectorErase(unsigned int sector_addr)
{
	 EA = 0;   
	 ISP_ADDRH = (unsigned char)(sector_addr >> 8);        //送擦除地址高字节
	 ISP_ADDRL = (unsigned char)(sector_addr & 0x00ff);    //送擦除地址低字节
	 ISP_IAP_Enable(); 
     ISP_CMD = ISP_CMD & 0xf8;           //清除ISP_CMD寄存器低3位
	 ISP_CMD = ISP_CMD | EraseCommand;   //写入擦除数据命令
	 ISPTrig();       //触发ISP/IAP
	 ISP_IAP_Disable();    //关闭ISP/IAP功能 
 
}