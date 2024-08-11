#include "ADC0832.h"
#include <reg52.h>
#include <intrins.h>

sbit Clk  = P2^0;
sbit CS   = P2^1;
sbit DATI = P2^2;
sbit DATO = P2^3;

/****************************************************************************
��������:ADת���ӳ���
��ڲ���:CH
���ڲ���:dat
****************************************************************************/
unsigned char adc0832(unsigned char CH)
{
    unsigned char i,test,adval,dat;
    adval = 0x00;
    test = 0x00;
    Clk = 0;       //��ʼ��
    DATI = 1;
    _nop_();
    CS = 0;
    _nop_();
    Clk = 1;
    _nop_();


    if ( CH == 0x00 )      //ͨ��ѡ��
    {
        Clk = 0;
        DATI = 1;      //ͨ��0�ĵ�һλ
        _nop_();
        Clk = 1;
        _nop_();
        Clk = 0;
        DATI = 0;      //ͨ��0�ĵڶ�λ
        _nop_();
        Clk = 1;
        _nop_();
    }
    else
    {
        Clk = 0;
        DATI = 1;      //ͨ��1�ĵ�һλ
        _nop_();
        Clk = 1;
        _nop_();
        Clk = 0;
        DATI = 1;      //ͨ��1�ĵڶ�λ
        _nop_();
        Clk = 1;
        _nop_();
    }

    Clk = 0;
    DATI = 1;
    for( i = 0; i < 8; i++ )    //��ȡǰ8λ��ֵ
    {
        _nop_();
        adval <<= 1;
        Clk = 1;
        _nop_();
        Clk = 0;
        if (DATO)
            adval |= 0x01;
        else
            adval |= 0x00;
    }
    for (i = 0; i < 8; i++)      //��ȡ��8λ��ֵ
    {
        test >>= 1;
        if (DATO)
            test |= 0x80;
        else
            test |= 0x00;
        _nop_();
        Clk = 1;
        _nop_();
        Clk = 0;
    }
    if (adval == test)      //�Ƚ�ǰ8λ���8λ��ֵ���������ͬ��ȥ����һֱ������ʾΪ�㣬�뽫����ȥ��
        dat = test;
    nop_();
    CS = 1;        //�ͷ�ADC0832
    DATO = 1;
    Clk = 1;
    return dat;
}

