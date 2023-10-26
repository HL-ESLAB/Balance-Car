#include "delay.h"
#include "sys.h"
#include "led.h"
#include "App.h"
#include "mpu6500.h"
#include "usart.h"


#include "FreeRTOS.h"
#include "task.h"


/*********************************************************
功能：任务创建管理
**********************************************************/

/***全局变量***/
//MPU6500_STRUCT  *pSensor;


//任务函数
void start_task(void *pvParameters);

//任务句柄
TaskHandle_t LED_Task_Handler;
TaskHandle_t IMU_Task_Handler;


void Application_Init(void)
{
		//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )256,        						//任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )2,       							//任务优先级
                (TaskHandle_t*  )NULL);   							//任务句柄              
             										
}

//LED0任务函数 
void Led_Task(void *pvParameters)
{
	TickType_t	PreviousWakeTime = xTaskGetTickCount(); 
	while(1)
	{
		PreviousWakeTime = xTaskGetTickCount();
		LED0=~LED0;
		vTaskDelayUntil(&PreviousWakeTime, configTICK_RATE_HZ/10);
	}
}

void IMU_Task(void *pvParameters)
{
	TickType_t	PreviousWakeTime = xTaskGetTickCount();
	while(1)
	{
		PreviousWakeTime = xTaskGetTickCount();
		

		delay_ms(10);
		
		vTaskDelayUntil(&PreviousWakeTime, configTICK_RATE_HZ/10);
	}	
}


//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
    //创建LED0任务
    xTaskCreate(Led_Task, "Led_Task", 256, NULL, 3, &LED_Task_Handler);
		xTaskCreate(IMU_Task, "IMU_Task", 256, NULL, 3, &IMU_Task_Handler);
    vTaskDelete(NULL);              //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}
