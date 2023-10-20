#include "led.h"
#include "delay.h"
#include "sys.h"
#include "App.h"
#include "Encoder.h"
#include "motor.h"
#include "timer.h"
#include "mpu6500.h"

#include "FreeRTOS.h"
#include "task.h"
/************************************************
��Ŀ���ƣ�ƽ�⳵
��Ŀ���ߣ�hl
20231017
��ֲ����������룬���Ե����IMU����
����ֲ�����������˳��ڴ�Ĵ��󣬽����ڴ������ڴ�����ֲ��ʱ��һ���ǵ��޸�
����궨��
#define configTOTAL_HEAP_SIZE								((size_t)(10*1024))     //ϵͳ�����ܵĶѴ�С
************************************************/

RCC_ClocksTypeDef RCC_CLK;/*  ʱ�ӽṹ�嶨��  */
int main(void)
{
	/* Infinite loop */
	/*Total RO  Size ����ʾ����ռ�õ�Flash�ռ��С*/
	/*Total RW  Size ����ʾ��������ʱռ�õ�RAM�ռ��С*/
	/*Total ROM Size ����ʾ�������ص�Flashռ�ÿռ��С*/
	RCC_GetClocksFreq(&RCC_CLK);                    /*��ȡϵͳʱ��*/
	if(RCC_CLK.SYSCLK_Frequency != 72000000)
	{
		while(1);/*���ϵͳʱ�Ӳ���ȷ�������к���ĳ���*/
	}
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4	 	 
	delay_init();	    				//��ʱ������ʼ��	  
	uart_init(115200);				//��ʼ������
	LED_Init();		  					//��ʼ��LED
	TIM2_Init();							//��ʱ����ʼ��
	Encoder_Init();						//��������ʼ��
	Motor_Init();							//������Ƴ�ʼ��
	PWM_Init();								//PWM�����ʼ��
	Init_MPU9250();						//MPU��ʼ��
			
	
	Application_Init();
	 
	vTaskStartScheduler(); 		//�����������
	
	while(1)
	{
		
	}
}



   

