#include<reg51.h>
#include<intrins.h>

typedef unsigned char uchar;
typedef unsigned int uint;
void delayms(uint xms);
void hc595(uchar byteData);

sbit SER = P3^4;    //p3.4�ſ��ƴ�����������
sbit SCK = P3^6;    //��������ʱ��
sbit RCK = P3^5;    //�洢�Ĵ���ʱ��

uchar code table[]=
                                 {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
uchar num=0;
void main()
{
        while(1)
        {
                   for(num=0;num<8;num++)
                {
                        hc595(table[num]);        
                        delayms(500);
                }
        }        //        hc595(0x55);            // Q7~Q0=0101 0101                 }
}



/*����:����һ���ֽڵ����ݸ�595���ٲ������*/
void hc595(char byteData)
{
    char i=0;   
    for(i=0;i<8;i++)
    {
        SER = byteData>>7;        //�ͳ�7λ����
        byteData= byteData<<1;      

        SCK = 0;          //�����أ��ô�������ʱ�ӱ�Ϊ�ߵ�ƽ������ʱ2��ʱ������
        _nop_();
        _nop_();
        SCK = 1;          //��Ϊ�͵�ƽ��Ϊ�´�׼��
    }  
   
   //λ�ƼĴ�������׼�����,ת�Ƶ��洢�Ĵ���
   RCK = 0;         //�����أ��ô洢�Ĵ���ʱ�ӱ�Ϊ�ߵ�ƽ������ʱ2��ʱ������
   _nop_();
   _nop_();
   RCK = 1;

}


void delayms(uint xms )  //��ʱxms����
{
        uint a,b;
        for(a=xms;a>0;a--)
         for(b=110;b>0;b--);
}