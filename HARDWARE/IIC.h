#ifndef __IIC_H
#define __IIC_H

#include "sys.h"

//************************************
/*ģ��IIC�˿�������붨��*/
#define SCL_H         GPIOB->BSRR = GPIO_Pin_8
#define SCL_L         GPIOB->BRR  = GPIO_Pin_8
   
#define SDA_H         GPIOB->BSRR = GPIO_Pin_9
#define SDA_L         GPIOB->BRR  = GPIO_Pin_9

#define SCL_read      GPIOB->IDR  & GPIO_Pin_8
#define SDA_read      GPIOB->IDR  & GPIO_Pin_9

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��			
int IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
int IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

uint8_t Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);

#endif
