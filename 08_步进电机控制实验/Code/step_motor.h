#ifndef _STEP_MOTOR_H
#define _STEP_MOTOR_H

#include "reg52.h"

sbit MotorA1 = P1^0;
sbit MotorB1 = P1^1;
sbit MotorC1 = P1^2;
sbit MotorD1 = P1^3;

#define CW 0
#define CCW 1
#define STOP 2

void MotorTurn(unsigned char motorState);

#endif
