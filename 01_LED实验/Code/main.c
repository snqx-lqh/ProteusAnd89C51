#include "reg52.h"
#include "intrins.h"

sbit LED = P2^0;

void Delay500ms()		//@11.0592MHz
{
	unsigned char data i, j, k;

	_nop_();
	i = 4;
	j = 129;
	k = 119;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


static void led_example1(void);
static void led_example2(void);

int main()
{	
	while(1)
	{		
		//led_example1();
		led_example2();
	}
}

static void led_example1(void)
{
	LED = 1;
	Delay500ms();
	LED = 0;
	Delay500ms();
}

static void led_example2(void)
{
	P2 = 0X55;
	Delay500ms();
	P2 = 0XAA;
	Delay500ms();
}

