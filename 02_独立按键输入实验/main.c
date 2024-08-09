#include <reg52.h>

#define u8  unsigned char
#define u16 unsigned int
	
sbit key1 = P3^0;
sbit key2 = P3^1;
sbit key3 = P3^2;
sbit key4 = P3^3;

u8 isKey1 = 0;
u8 isKey2 = 0;
u8 isKey3 = 0;
u8 isKey4 = 0;

void KeyScan(u8 mode);
void Delay10ms();		//@11.0592MHz
static void key_example1(void);
static void key_example2(void);

int main()
{
    while (1)
    {
		//key_example1();
		key_example2();
    }
}

static void key_example1(void)
{
	key1 = 1;
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
	KeyScan(0);
	if(isKey1==1)
	{
		P2 = 0XAA;
		isKey1=0;
	}
	if(isKey2==1)
	{
		P2 = 0X55;
		isKey2=0;
	}
	if(isKey3==1)
	{
		P2 = 0X78;
		isKey3=0;
	}
	if(isKey4==1)
	{
		P2 = 0X32;
		isKey4=0;
	}
}

void Delay10ms()		//@11.0592MHz
{
	unsigned char data i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j);
	} while (--i);
}

/**
 * @brief 按键扫描函数
 * 
 * @param mode 模式为1就是连续扫描，为0就是单次
 */
void KeyScan(u8 mode)
{
    static int    keyState = 0;
    if(mode == 1) keyState=0;
    if (keyState == 0 && (key1 == 0||key2 == 0||key3 == 0||key4 == 0))
    {    
		Delay10ms();
		keyState = 1;
		if      (key1 == 0) isKey1=1;
		else if (key2 == 0) isKey2=1;
		else if (key3 == 0) isKey3=1;
		else if (key4 == 0) isKey4=1;
    }else if (key1 == 1 && key2 == 1 && key3 == 1 && key4 == 1)
    {
        keyState = 0;
    }
}

