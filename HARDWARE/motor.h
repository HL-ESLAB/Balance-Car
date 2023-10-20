#ifndef __MOTOR_H
#define __MOTOR_H

#include "sys.h"
void LC_CHG(u16 ChannelPulse);
void RC_CHG(u16 ChannelPulse);
void Motor_Init(void);
void Left_Motor(u8 direction, u16 speed);
void Right_Motor(u8 direction, u16 speed);
#endif
