#ifndef __CONTROL_H
#define __CONTROL_H

#include "sys.h"

#define PI 3.14159265

#define DIFFERENCE 100

extern int Balance_Pwm,Velocity_Pwm,Turn_Pwm;

int balance(float angle,float gyro);
int velocity(int encoder_left,int encoder_right);
void Set_Pwm(int moto1,int moto2);
void Key(void);
void Xianfu_Pwm(void);
void Get_Angle(u8 way);
int myabs(int a);
int EXTI15_10_IRQHandler(void);
#endif
