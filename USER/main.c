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
u8 Way_Angle=1;                             //��ȡ�Ƕȵ��㷨��1����Ԫ��  2��������  3�������˲� 
u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu=2; //����ң����صı���
u8 Flag_Stop=1,Flag_Show=0,Flag_Hover=0;    //ֹͣ��־λ�� ��ʾ��־λ Ĭ��ֹͣ ��ʾ��
int Encoder_Left,Encoder_Right;             //���ұ��������������
int Moto1,Moto2;                            //���PWM���� Ӧ��Motor�� ��Moto�¾�	
float Angle_Balance,Gyro_Balance,Gyro_Turn; //ƽ����� ƽ�������� ת��������
float Balance_Kp=300,Balance_Kd=1,Velocity_Kp=80,Velocity_Ki=0.4;//PID����
float Zhongzhi;
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
							//MPU��ʼ��
			
	
	Application_Init();
	 
	vTaskStartScheduler(); 		//�����������
	
	while(1)
	{
		
	}
}



   

