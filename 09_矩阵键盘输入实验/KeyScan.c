#include "KeyScan.h"

u8 KeyValue = 0;
u8 KeyState = 0; //1 为按下 0 为抬起

/**
  * @name    KeyScan
  * @brief   按键检测函数
  * @param   : [输入/出] 
  * @retval  返回值
  */
void KeyScan(void)
{
    static u8 count = 0;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f && KeyState == 0)
	{
        count ++;
		if(GPIO_KEY!=0x0f && count > 2 && KeyState == 0)
		{
            count = 0;
			KeyState = 1;
			//列
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=1;break;
				case(0X0b):	KeyValue=2;break;
				case(0X0d): KeyValue=3;break;
				case(0X0e):	KeyValue=4;break;
			}
			//行
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
			}
		}
	}else if(GPIO_KEY==0x0F && KeyState == 1)
    {
        KeyState = 0;
        KeyValue = 0;
    }
}
