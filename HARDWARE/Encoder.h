#ifndef __ENCODER_H
#define __ENCODER_H

#include "sys.h"

void Encoder_Init(void);
void Encoder_Init_TIM2(void);
int Read_Encoder(u8 TIMX);
void TIM4_IRQHandler(void);
void TIM2_IRQHandler(void);
#endif
