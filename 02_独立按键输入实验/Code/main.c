#include <reg52.h>
#include "bsp_key.h"

#define u8  unsigned char
#define u16 unsigned int
	
static void key_example1(void);
static void key_example2(void);

int main()
{
	KeyInit();
    while (1)
    {
		//key_example1();
		key_example2();
    }
}

static void key_example1(void)
{
	if(key1 == 0)
	{
		P2 = 0XAA;
	}else
	{
		P2 = 0X55;
	}
}

static void key_example2(void)
{
	u8 key_value = 0;
	key_value = KeyScan(0);
	if(key_value==1)
	{
		P2 = 0XAA;
	}
	if(key_value==2)
	{
		P2 = 0X55;
	}
	if(key_value==3)
	{
		P2 = 0X78;
	}
	if(key_value==4)
	{
		P2 = 0X32;
	}
}



