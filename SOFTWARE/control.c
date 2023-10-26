#include "control.h"
#include "filter.h"	
#include "exti.h"

int Balance_Pwm,Velocity_Pwm,Turn_Pwm;
u8 Flag_Target;
u32 Flash_R_Count;
int Voltage_Temp,Voltage_Count,Voltage_All;
/**************************************************************************
�������ܣ����еĿ��ƴ��붼��������
         5ms��ʱ�ж���MPU6050��INT���Ŵ���
         �ϸ�֤���������ݴ����ʱ��ͬ��				 
**************************************************************************/

int EXTI15_10_IRQHandler(void) 
{
	if(INT == 0)
	{
		EXTI->PR = 1 << 15;																					//����жϱ�־λ
		Flag_Target = !Flag_Target;
		if(Flag_Target ==  1)																				//5ms��ȡһ�������Ǻͼ��ٶȼƵ�ֵ�����ߵĲ���Ƶ�ʿ��Ը��ƿ������˲��ͻ����˲���Ч��
		{
			Get_Angle(Way_Angle);																			//===������̬
			return 0;
		}																														//10ms����һ�Σ�Ϊ�˱�֤M�����ٵ�ʱ���׼�����ȶ�ȡ����������
		Encoder_Left = Read_Encoder(2);															//===��ȡ��������ֵ
		Encoder_Right = Read_Encoder(4);														//===��ȡ��������ֵ
		Get_Angle(Way_Angle);																				//===������̬	
		Balance_Pwm = balance(Angle_Balance, Gyro_Balance); 				//===ƽ��PID����
		Velocity_Pwm = velocity(Encoder_Left, Encoder_Right);				//===�ٶȻ�PID����	 ��ס���ٶȷ�����������������С�����ʱ��Ҫ����������Ҫ���ܿ�һ��		
		Moto1 = Balance_Pwm + Velocity_Pwm - Turn_Pwm;							//===�������ֵ������PWM
		Moto2 = Balance_Pwm + Velocity_Pwm + Turn_Pwm;							//===�������ֵ������PWM
		Xianfu_Pwm();																								//===PWM�޷�
		Set_Pwm(Moto1, Moto2);																			//===��ֵ��PWM�Ĵ���
		
	}
	return 0;
}

/**************************************************************************
�������ܣ�ֱ��PD����
��ڲ������Ƕȡ����ٶ�
����  ֵ��ֱ������PWM
**************************************************************************/
int balance(float Angle, float Gyro)
{
	float Bias;
	int balance;
	Bias = Angle - 0;					//===���ƽ��ĽǶ���ֵ �ͻ�е���
	balance = Balance_Kp * Bias + Gyro * Balance_Kd;		//===����ƽ����Ƶĵ��PWM  PD����   kp��Pϵ�� kd��Dϵ�� 
	return balance;
}

/**************************************************************************
�������ܣ��ٶ�PI���� �޸�ǰ�������ٶȣ�����Target_Velocity�����磬�ĳ�60�ͱȽ�����
��ڲ��������ֱ����������ֱ�����
����  ֵ���ٶȿ���PWM
**************************************************************************/
int velocity(int encoder_left, int encoder_right)
{
	static float Velocity,Encoder_Least, Encoder,Movement;
	static float Encoder_Integral;
	//=============�ٶ�PI������=======================//
	Encoder_Least = (encoder_left + encoder_right) - 0;				//===��ȡ�����ٶ�ƫ��==�����ٶȣ����ұ�����֮�ͣ�-Ŀ���ٶȣ��˴�Ϊ�㣩//===��ȡ�����ٶ�ƫ��==�����ٶȣ����ұ�����֮�ͣ�-Ŀ���ٶȣ��˴�Ϊ�㣩
	Encoder *= 0.8;																						//===һ�׵�ͨ�˲���
	Encoder += Encoder_Least * 0.2;														//===һ�׵�ͨ�˲���
	Encoder_Integral += Encoder;															//===���ֳ�λ�� ����ʱ�䣺10ms
	Encoder_Integral = Encoder_Integral - Movement;						//===����ң�������ݣ�����ǰ������
	if(Encoder_Integral>10000)  	Encoder_Integral=10000;			//===�����޷�
	if(Encoder_Integral<-10000)	Encoder_Integral=-10000;			//===�����޷�	
	Velocity = Encoder * Velocity_Kp + Encoder_Integral * Velocity_Ki;		//===�ٶȿ���	
	return Velocity;
}

/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ���������PWM������PWM
����  ֵ����
**************************************************************************/
void Set_Pwm(int moto1, int moto2)
{
	if(moto1 > 0)	AIN2 = 0, AIN1 = 1;
	else					AIN2 = 1, AIN1 = 0;
	PWMA=myabs(moto1);
	if(moto2>0)	BIN1=0,			BIN2=1;
	else        BIN1=1,			BIN2=0;
	PWMB=myabs(moto2);
}

/**************************************************************************
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=6900;    //===PWM������7200 ������6900
		if(Flag_Qian==1)  Moto1+=DIFFERENCE;  //DIFFERENCE��һ������ƽ��С������ͻ�е��װ�����һ��������ֱ���������������С�����и��õ�һ���ԡ�
	  if(Flag_Hou==1)   Moto2-=DIFFERENCE;
    if(Moto1<-Amplitude) Moto1=-Amplitude;	
		if(Moto1>Amplitude)  Moto1=Amplitude;	
	  if(Moto2<-Amplitude) Moto2=-Amplitude;	
		if(Moto2>Amplitude)  Moto2=Amplitude;		
	
}
/**************************************************************************
�������ܣ���ȡ�Ƕ� �����㷨�������ǵĵ�У�����ǳ����� 
��ڲ�������ȡ�Ƕȵ��㷨 1��DMP  2�������� 3�������˲�
����  ֵ����
**************************************************************************/
void Get_Angle(u8 way)
{ 
	    if(way==1)                           //===DMP�Ķ�ȡ�����ݲɼ��ж϶�ȡ���ϸ���ѭʱ��Ҫ��
			{	
					Read_DMP();                      //===��ȡ���ٶȡ����ٶȡ����
					Angle_Balance=-Roll;             //===����ƽ�����
					Gyro_Balance=-gyro[0];            //===����ƽ����ٶ�
					Gyro_Turn=gyro[2];               //===����ת����ٶ�
			}			
}
/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}




