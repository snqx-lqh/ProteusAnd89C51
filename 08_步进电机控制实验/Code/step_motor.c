#include "step_motor.h"

/**
  * @Name    setMotorLevel
  * @brief   ULN2003组成的控制电路控制函数
  * @param   各个引脚的电平
  * @retval  返回值
  */
void setMotorLevel(unsigned char MotorA,unsigned char MotorB,unsigned char MotorC,unsigned char MotorD)
{
	MotorA1 = MotorA;
	MotorB1 = MotorB;
	MotorC1 = MotorC;
	MotorD1 = MotorD;
}

/**
  * @Name    MotorTurn
  * @brief   ULN2003组成的控制电路控制函数
  * @param   motorState: CW CCW STOP
  * @retval  返回值
  */
void MotorTurn(unsigned char motorState)
{
    static int motor1Step = 0;
    motor1Step++;
    if (motor1Step > 7)
    {
        motor1Step = 0;
    }
    if (motorState == CW)
    {
		switch (motor1Step)
		{
			case 0:setMotorLevel(0,0,0,1);break;
			case 1:setMotorLevel(0,0,1,1);break;
			case 2:setMotorLevel(0,0,1,0);break;
			case 3:setMotorLevel(0,1,1,0);break;
			case 4:setMotorLevel(0,1,0,0);break;
			case 5:setMotorLevel(1,1,0,0);break;
			case 6:setMotorLevel(1,0,0,0);break;
			case 7:setMotorLevel(1,0,0,1);break;
			default:setMotorLevel(0,0,0,1);break;
		}
    }else if (motorState == CCW)
    {
		switch (motor1Step)
		{
			case 0:setMotorLevel(0,0,0,1);break;
			case 1:setMotorLevel(1,0,0,1);break;
			case 2:setMotorLevel(1,0,0,0);break;
			case 3:setMotorLevel(1,1,0,0);break;
			case 4:setMotorLevel(1,0,0,0);break;
			case 5:setMotorLevel(0,1,1,0);break;
			case 6:setMotorLevel(0,0,1,0);break;
			case 7:setMotorLevel(0,0,1,1);break;
			default:setMotorLevel(0,0,0,1);break;
		}
	}
}
