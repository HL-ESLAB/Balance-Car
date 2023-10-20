#include "motor.h"

void Motor_Init(void)
{
	//��ʼ�����Ƶ��ת���4��GPIO 	(GPIOB_Pin_15 GPIOB_Pin_14 GPIOB_Pin_13 GPIOB_Pin_12)
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_13|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}

//��ת:IN1 1 IN2 0
//��ת:IN1 0 IN2 1
//ֹͣ:IN1 0 IN2 0
void Left_Motor(u8 direction, u16 speed)//0ֹͣ 1ǰ�� 2���� 
{
	//direction = 1;
	if(direction == 0)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	}
	else if(direction == 1)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	}
	else if(direction == 2)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
		GPIO_SetBits(GPIOB, GPIO_Pin_14);
	}
	else
	{
	
	}
	
	speed = 500;
	LC_CHG(speed);   //FΪ��Ƶ�� CΪռ�ձ� ��F=2000��Cȡֵ0-1000	
}	

void Right_Motor(u8 direction, u16 speed)		//0 ֹͣ 1ǰ�� 2����    speedȡֵ0-1000
{
	if(direction == 0)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	}
	else if(direction == 1)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	}
	else if(direction == 2)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
	}
	else
	{
		
	}
	
	speed = 500;
	RC_CHG(speed);
}

//**********************************************************************************************
//							ռ�ձȵ���
//**********************************************************************************************

/*����������ռ�ձȵ�������������TIM3��*/
void LC_CHG(u16 ChannelPulse)   //FΪ��Ƶ�� CΪռ�ձ� ��F=2000��Cȡֵ0-1000
{
	TIM_SetCompare3(TIM3,ChannelPulse);     
}
void RC_CHG(u16 ChannelPulse)   //FΪ��Ƶ�� CΪռ�ձ� ��F=2000��C=0.5
{
	TIM_SetCompare4(TIM3,ChannelPulse);     
}

