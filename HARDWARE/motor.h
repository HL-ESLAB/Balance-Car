#ifndef __MOTOR_H
#define __MOTOR_H

#include "sys.h"
#define PWMA   TIM1->CCR4  
#define AIN2   PBout(15)
#define AIN1   PBout(14)
#define BIN1   PBout(13)
#define BIN2   PBout(12)
#define PWMB   TIM1->CCR1 
void LC_CHG(u16 ChannelPulse);
void RC_CHG(u16 ChannelPulse);
void Motor_Init(void);
void Left_Motor(u8 direction, u16 speed);
void Right_Motor(u8 direction, u16 speed);
#endif
