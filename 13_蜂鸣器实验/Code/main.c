#include "reg52.h"
#include "intrins.h"

sbit BEEP = P1^5;

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

int main()
{	
	while(1)
	{		
		BEEP = 1;
		Delay500ms();
		BEEP = 0;
		Delay500ms();
	}
}
