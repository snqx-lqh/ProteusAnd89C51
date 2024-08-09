/***************************************************************
    ��Ʒ��EEPROMʵ�飬������ԭ�ص�ǰLED������״��
  ��Ƭ����STC89C52RC
    ����12M
���뻷����Keil uVision4 V9.00
***************************************************************/     
//#include <STC89C52RC.H>
#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char   
#define uint unsigned int
/****************���⹦�ܼĴ�������****************/
sfr ISP_DATA = 0xe2;   
sfr ISP_ADDRH = 0xe3;     
sfr ISP_ADDRL = 0xe4;   
sfr ISP_CMD = 0xe5;   
sfr ISP_TRIG = 0xe6;      
sfr ISP_CONTR = 0xe7;
sbit LED1 = P2^0;
sbit LED2 = P2^1;
sbit K1   = P3^2;                           //��ť1
sbit K2   = P3^3;                           //��ť2
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
PIN�ڶ���
**********************************/
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;
/**********************************
��������
**********************************/
/*��51��Ƭ��12MHZʱ���µ���ʱ����*/
void Lcd1602_Delay1ms(uint c);   //��� 0us
/*LCD1602д��8λ�����Ӻ���*/
void LcdWriteCom(uchar com);
/*LCD1602д��8λ�����Ӻ���*/      
void LcdWriteData(uchar dat)        ;
/*LCD1602��ʼ���ӳ���*/               
void LcdInit();      
/*LCD1602д���ַ���*/
void LCDWrite_String(uchar x, uchar y,uchar z, uchar *s);
/*����LCD1602д���ַ�����λ��*/
void LCD_set_xy(uchar x, uchar y, uchar z);               
void IntConfiguration();
/*
uchar ON_Hour=0x07;          //��ʼ����ʱ��  07��00                                                                   1
uchar Warning_TempH=32;         //���±����¶�                                                                                   5
*/
uchar ON_Hour;          //��ʼ����ʱ��  07��00                                                                   1
uchar Warning_TempH;         //���±����¶�      
/*������������������������������������������������������������
������������
������������������������������������������������������������*/
void main(void)
{
   LcdInit();
   IntConfiguration();
//
/*
   cc(0x2000);                  // ������1��������2000h~21FFh��
   xcx(0x2000,ON_Hour);          // ��EEPROM��2002hд��2
   xcx(0x2001,Warning_TempH);          // ��EEPROM��2002hд��2
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
   V = dcx(0x2002);                          // ������ȡEEPROM��2002h����,��ԭ�ص�ǰLED������״��
   if(V == 2)          {LED1=0;LED2=1;}
   else if(V == 6){LED1=0;LED2=0;}
   while(1)
     {
      if(!K1)
            {
              while(!K1);
              LED1=0;LED2=1;
              cc(0x2000);                  // ������1��������2000h~21FFh��
              xcx(0x2002,2);          // ��EEPROM��2002hд��2
            }
          if(!K2)
            {
              while(!K2);
              LED1=0;LED2=0;
              cc(0x2000);                  // ������1��������2000h~21FFh��
              xcx(0x2002,6);                          // ��EEPROM��2002hд��6
            }
     }
         */
}
/*������������������������������������������������������������
����������ĳһ������ÿ������512�ֽڣ�
��ڣ�addr = ĳһ�����׵�ַ                          
������������������������������������������������������������*/
void cc(uint addr)
{      
// �� IAP ����(ISP_CONTR.7)=1:�����̸ı�Flash, ����Flash�����ȴ�ʱ��
// 0x83(����<5M)   0x82(����<10M)   0x81(����<20M)   0x80(����<40M)
    ISP_CONTR = 0x81;  
    ISP_CMD   = 0x03;                  // �û����Զ�"Data Flash/EEPROM��"������������
    ISP_ADDRL = addr;         // ISP/IAP����ʱ�ĵ�ַ�Ĵ����Ͱ�λ��
    ISP_ADDRH = addr>>8;      // ISP/IAP����ʱ�ĵ�ַ�Ĵ����߰�λ��
        EA =0;   
    ISP_TRIG = 0x46;          // ��ISPEN(ISP_CONTR.7)=1ʱ,��ISP_TRIG��д��46h��
    ISP_TRIG = 0xB9;          // ��д��B9h,ISP/IAP����Ż���Ч��
    _nop_();
    Q0();                                          // �ر�ISP/IAP
}
/*������������������������������������������������������������
������дһ�ֽ�
��ڣ�addr = ������Ԫ��ַ , dat = ��д������
������������������������������������������������������������*/
void xcx(uint addr,uchar dat)
{
    ISP_CONTR = 0x81;                  
    ISP_CMD   = 0x02;              // �û����Զ�"Data Flash/EEPROM��"�����ֽڱ��
    ISP_ADDRL = addr;        
    ISP_ADDRH = addr>>8;      
    ISP_DATA  = dat;          // ���ݽ�ISP_DATA
    EA = 0;
    ISP_TRIG = 0x46;         
    ISP_TRIG = 0xB9;         
    _nop_();
    Q0();                                          // �ر�ISP/IAP
}
/*������������������������������������������������������������
��������һ�ֽ�
��ڣ�addr = ������Ԫ��ַ
���ڣ�dat  = ����������
������������������������������������������������������������*/
uchar dcx(uint addr)
{   
    uchar dat;
      
        ISP_CONTR = 0x81;                  
    ISP_CMD   = 0x01;         // �û����Զ�"Data Flash/EEPROM��"�����ֽڶ�
    ISP_ADDRL = addr;         
    ISP_ADDRH = addr>>8;      
    EA = 0;
    ISP_TRIG = 0x46;         
    ISP_TRIG = 0xB9;         
    _nop_();
    dat = ISP_DATA;                          // ȡ������
        Q0();                                          // �ر�ISP/IAP                  
        return dat;
}
/*������������������������������������������������������������
�������ر�ISP/IAP����
������������������������������������������������������������*/
void Q0()
{
    ISP_CONTR = 0;            // �ر�IAP����
    ISP_CMD   = 0;            // ����ģʽ����ISP����
    ISP_TRIG  = 0;            // �ر�IAP����, ����ISP�йص����⹦�ܼĴ���
        EA=1;
}
/*
STC89C52RC�ڲ�EEPROM��ϸ��ַ��
��һ����                   �ڶ�����                    ��������                    ��������
��ʼ��ַ  ������ַ   ��ʼ��ַ   ������ַ   ��ʼ��ַ   ������ַ   ��ʼ��ַ    ������ַ
2000h      21FFh       2200h       23FFh      2400h       25FFh       2600h        27FFH
��������                    ��������                     ��������                    �ڰ�����
��ʼ��ַ   ������ַ   ��ʼ��ַ   ������ַ    ��ʼ��ַ   ������ַ   ��ʼ��ַ    ������ַ
2800h       29FFh       2A00h      2BFFh        2C00h      2DFFh      2E00h        2FFFh
*/
/*******************************************************************************
* �� �� ��         : Lcd1602_Delay1ms
* ��������                   : ��ʱ��������ʱ1ms
* ��    ��         : c
* ��    ��         : ��
* ˵    ��         : �ú�������12MHZ�����£�12��Ƶ��Ƭ������ʱ��
*******************************************************************************/
void Lcd1602_Delay1ms(uint c)   //��� 0us
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
* �� �� ��         : void LCDWrite_String(uchar x, uchar y, uchar *s)
* ��������                   : ��LCDд��һ���ַ���
* ��    ��         : x,y,*s
* ��    ��         : ��
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
* �� �� ��         : void LCD_set_xy(uchar x, uchar y,uchar z)
* ��������                   : ָ����LCDд���ַ�����λ��
* ��    ��         : x,y,z                 //x:������ y:������ z:�ַ�������
* ��    ��         : ��
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
* �� �� ��         : LcdWriteCom
* ��������                   : ��LCDд��һ���ֽڵ�����
* ��    ��         : com
* ��    ��         : ��
*******************************************************************************/
#ifndef         LCD1602_4PINS         //��û�ж������LCD1602_4PINSʱ
void LcdWriteCom(uchar com)          //д������
{
        LCD1602_E = 0;     //ʹ��
        LCD1602_RS = 0;           //ѡ��������
        LCD1602_RW = 0;           //ѡ��д��
      
        LCD1602_DATAPINS = com;     //��������
        Lcd1602_Delay1ms(1);                //�ȴ������ȶ�
        LCD1602_E = 1;                  //д��ʱ��
        Lcd1602_Delay1ms(5);          //����ʱ��
        LCD1602_E = 0;
}
#else
void LcdWriteCom(uchar com)          //д������
{
        LCD1602_E = 0;         //ʹ������
        LCD1602_RS = 0;         //ѡ��д������
        LCD1602_RW = 0;         //ѡ��д��
        LCD1602_DATAPINS = com;        //����4λ�Ľ����ǽӵ�P0�ڵĸ���λ�����Դ��͸���λ���ø�
        Lcd1602_Delay1ms(1);
        LCD1602_E = 1;         //д��ʱ��
        Lcd1602_Delay1ms(5);
        LCD1602_E = 0;
//        Lcd1602_Delay1ms(1);
        LCD1602_DATAPINS = com << 4; //���͵���λ
        Lcd1602_Delay1ms(1);
        LCD1602_E = 1;         //д��ʱ��
        Lcd1602_Delay1ms(5);
        LCD1602_E = 0;
}
#endif
/*******************************************************************************
* �� �� ��         : LcdWriteData
* ��������                   : ��LCDд��һ���ֽڵ�����
* ��    ��         : dat
* ��    ��         : ��
*******************************************************************************/                  
#ifndef         LCD1602_4PINS                  
void LcdWriteData(uchar dat)                        //д������
{
        LCD1602_E = 0;        //ʹ������
        LCD1602_RS = 1;        //ѡ����������
        LCD1602_RW = 0;        //ѡ��д��
        LCD1602_DATAPINS = dat; //д������
        Lcd1602_Delay1ms(1);
        LCD1602_E = 1;   //д��ʱ��
        Lcd1602_Delay1ms(5);   //����ʱ��
        LCD1602_E = 0;
}
#else
void LcdWriteData(uchar dat)                        //д������
{
        LCD1602_E = 0;          //ʹ������
        LCD1602_RS = 1;          //ѡ��д������
        LCD1602_RW = 0;          //ѡ��д��
        LCD1602_DATAPINS = dat;        //����4λ�Ľ����ǽӵ�P0�ڵĸ���λ�����Դ��͸���λ���ø�
        Lcd1602_Delay1ms(1);
        LCD1602_E = 1;          //д��ʱ��
        Lcd1602_Delay1ms(5);
        LCD1602_E = 0;
        LCD1602_DATAPINS = dat << 4; //д�����λ
        Lcd1602_Delay1ms(1);
        LCD1602_E = 1;          //д��ʱ��
        Lcd1602_Delay1ms(5);
        LCD1602_E = 0;
}
#endif
/*******************************************************************************
* �� �� ��       : LcdInit()
* ��������                 : ��ʼ��LCD��
* ��    ��       : ��
* ��    ��       : ��
*******************************************************************************/                  
#ifndef                LCD1602_4PINS
void LcdInit()                                                  //LCD��ʼ���ӳ���
{
        LcdWriteCom(0x38);  //����ʾ
        LcdWriteCom(0x0c);  //����ʾ����ʾ���
        LcdWriteCom(0x06);  //дһ��ָ���1
        LcdWriteCom(0x01);  //����
        LcdWriteCom(0x80);  //��������ָ�����
}
#else
void LcdInit()                                                  //LCD��ʼ���ӳ���
{
        LcdWriteCom(0x32);         //��8λ����תΪ4λ����
        LcdWriteCom(0x28);         //����λ���µĳ�ʼ��
        LcdWriteCom(0x0c);  //����ʾ����ʾ���
        LcdWriteCom(0x06);  //дһ��ָ���1
        LcdWriteCom(0x01);  //����
        LcdWriteCom(0x80);  //��������ָ�����
}
#endif
void IntConfiguration()
{
        //����INT0
        IT0=1;//�����س�����ʽ���½��أ�
        EX0=1;//��INT0���ж�����
        //����INT1
        IT1=1;//�����س�����ʽ���½��أ�
        EX1=1;//��INT0���ж�����
        EA=1;//�����ж�      
}
void Int0() interrupt 1                 
{
   cc(0x2000);                  // ������1��������2000h~21FFh��
   xcx(0x2000,0x07);          // ��EEPROM��2002hд��2
   xcx(0x2001,32);
   LcdInit();
}
void Int1() interrupt 2                 
{
   cc(0x2000);                  // ������1��������2000h~21FFh��
   xcx(0x2000,0x08);          // ��EEPROM��2002hд��2
   xcx(0x2001,33);
   LcdInit();
}