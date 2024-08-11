#include "LCD12864.h"

/****************************************************************************
��������:LCD��ʱ����
��ڲ���:t
���ڲ���:
****************************************************************************/
void LCDdelay(unsigned int t)
{
	unsigned int i,j;
	for(i=0;i<t;i++);
	for(j=0;j<10;j++);
}
/****************************************************************************
״̬��飬LCD�Ƿ�æ
*****************************************************************************/
void CheckState()		
{
   unsigned char dat,DATA;//״̬��Ϣ���ж��Ƿ�æ��
   LCDDi=0; // ����\ָ��ѡ��D/I��RS��="L" ����ʾ DB7��DB0 Ϊ��ʾָ������ 
   LCDRW=1; //R/W="H" ��E="H"���ݱ�����DB7��DB0 
   do
   {
      DATA=0x00;
      LCDEnable=1;	//EN�½�Դ
	  LCDdelay(2);//��ʱ
	  dat=DATA;
      LCDEnable=0;
      dat=0x80 & dat; //������7λΪ0ʱ�ſɲ���(�б�busy�ź�)
    }
    while(!(dat==0x00));
}
/*****************************************************************************
��������:д���LCD����RS(DI)=L,RW=L,EN=H������һ������дһ��
��ڲ���:cmdcode
���ڲ���:
*****************************************************************************/
void write_com(unsigned char cmdcode)
{
    CheckState();//���LCD�Ƿ�æ
	LCDDi=0;
	LCDRW=0;
	P1=cmdcode;		
	LCDdelay(2);
	LCDEnable=1;
	LCDdelay(2);
	LCDEnable=0;
}
/*****************************************************************************
��������:LCD��ʼ������
��ڲ���:
���ڲ���:
*****************************************************************************/
void init_lcd()
{
	LCDdelay(100);	
	LCDMcs=1;//�տ�ʼ�ر�����
	LCDScs=1;
	LCDdelay(100);
	write_com(LCDLCDDisp_Off);	 //д��ʼ������
	write_com(Page_Add+0);
	write_com(Start_Line+0);
	write_com(LCDCol_Add+0);
	write_com(LCDLCDDisp_On);
}
/*****************************************************************************
��������:д���ݵ�LCD����RS(DI)=H,RW=L,EN=H������һ������дһ��
��ڲ���:LCDDispdata
���ڲ���:
*****************************************************************************/
void write_data(unsigned char LCDDispdata)
{
    CheckState();//���LCD�Ƿ�æ
	LCDDi=1;
	LCDRW=0;
	P1=LCDDispdata;
	LCDdelay(2);
	LCDEnable=1;
	LCDdelay(2);
	LCDEnable=0;
}
/*****************************************************************************
��������:���LCD�ڴ����
��ڲ���:pag,col,hzk
���ڲ���:
*****************************************************************************/
void Clr_Scr()
{
	unsigned char j,k;
	LCDMcs=0; //������������ʾ
	LCDScs=0;
 	write_com(Page_Add+0);
 	write_com(LCDCol_Add+0);
 	for(k=0;k<8;k++)//����ҳ��0-7����8ҳ
 	{
		write_com(Page_Add+k); //ÿҳÿҳ����д
  		for(j=0;j<64;j++)  //ÿҳ����д32���������ֻ�64��ASCII�ַ�
		{
      		write_com(LCDCol_Add+j);
			write_data(0x00);//��������0-63����64�У�д�����ݣ��е�ַ�Զ���1
		}
	}
}
/*****************************************************************************
��������:ָ��λ����ʾ����16*16����
��ڲ���:page,column,hzk
���ڲ���:
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


