#include "delay.h"
#include "sys.h"
#include "led.h"
#include "App.h"
#include "mpu6500.h"
#include "usart.h"


#include "FreeRTOS.h"
#include "task.h"


/*********************************************************
���ܣ����񴴽�����
**********************************************************/

/***ȫ�ֱ���***/
//MPU6500_STRUCT  *pSensor;


//������
void start_task(void *pvParameters);

//������
TaskHandle_t LED_Task_Handler;
TaskHandle_t IMU_Task_Handler;


void Application_Init(void)
{
		//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )256,        						//�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )2,       							//�������ȼ�
                (TaskHandle_t*  )NULL);   							//������              
             										
}

//LED0������ 
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


//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
    //����LED0����
    xTaskCreate(Led_Task, "Led_Task", 256, NULL, 3, &LED_Task_Handler);
		xTaskCreate(IMU_Task, "IMU_Task", 256, NULL, 3, &IMU_Task_Handler);
    vTaskDelete(NULL);              //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}
