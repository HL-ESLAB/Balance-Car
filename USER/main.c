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
项目名称：平衡车
项目作者：hl
20231017
移植相关驱动代码，调试电机和IMU代码
在移植过程中遇到了超内存的错误，将高内存往低内存中移植的时候，一定记得修改
此项宏定义
#define configTOTAL_HEAP_SIZE								((size_t)(10*1024))     //系统所有总的堆大小
************************************************/

RCC_ClocksTypeDef RCC_CLK;/*  时钟结构体定义  */
int main(void)
{
	/* Infinite loop */
	/*Total RO  Size ：表示程序占用的Flash空间大小*/
	/*Total RW  Size ：表示程序运行时占用的RAM空间大小*/
	/*Total ROM Size ：表示程序下载到Flash占用空间大小*/
	RCC_GetClocksFreq(&RCC_CLK);                    /*获取系统时钟*/
	if(RCC_CLK.SYSCLK_Frequency != 72000000)
	{
		while(1);/*如果系统时钟不正确，则不运行后面的程序*/
	}
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4	 	 
	delay_init();	    				//延时函数初始化	  
	uart_init(115200);				//初始化串口
	LED_Init();		  					//初始化LED
	TIM2_Init();							//定时器初始化
	Encoder_Init();						//编码器初始化
	Motor_Init();							//电机控制初始化
	PWM_Init();								//PWM输出初始化
	Init_MPU9250();						//MPU初始化
			
	
	Application_Init();
	 
	vTaskStartScheduler(); 		//开启任务调度
	
	while(1)
	{
		
	}
}



   

