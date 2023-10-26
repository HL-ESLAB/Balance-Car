#include "control.h"
#include "filter.h"	
#include "exti.h"

int Balance_Pwm,Velocity_Pwm,Turn_Pwm;
u8 Flag_Target;
u32 Flash_R_Count;
int Voltage_Temp,Voltage_Count,Voltage_All;
/**************************************************************************
函数功能：所有的控制代码都在这里面
         5ms定时中断由MPU6050的INT引脚触发
         严格保证采样和数据处理的时间同步				 
**************************************************************************/

int EXTI15_10_IRQHandler(void) 
{
	if(INT == 0)
	{
		EXTI->PR = 1 << 15;																					//清除中断标志位
		Flag_Target = !Flag_Target;
		if(Flag_Target ==  1)																				//5ms读取一次陀螺仪和加速度计的值，更高的采样频率可以改善卡尔曼滤波和互补滤波的效果
		{
			Get_Angle(Way_Angle);																			//===更新姿态
			return 0;
		}																														//10ms控制一次，为了保证M法测速的时间基准，首先读取编码器数据
		Encoder_Left = Read_Encoder(2);															//===读取编码器的值
		Encoder_Right = Read_Encoder(4);														//===读取编码器的值
		Get_Angle(Way_Angle);																				//===更新姿态	
		Balance_Pwm = balance(Angle_Balance, Gyro_Balance); 				//===平衡PID控制
		Velocity_Pwm = velocity(Encoder_Left, Encoder_Right);				//===速度环PID控制	 记住，速度反馈是正反馈，就是小车快的时候要慢下来就需要再跑快一点		
		Moto1 = Balance_Pwm + Velocity_Pwm - Turn_Pwm;							//===计算左轮电机最终PWM
		Moto2 = Balance_Pwm + Velocity_Pwm + Turn_Pwm;							//===计算右轮电机最终PWM
		Xianfu_Pwm();																								//===PWM限幅
		Set_Pwm(Moto1, Moto2);																			//===赋值给PWM寄存器
		
	}
	return 0;
}

/**************************************************************************
函数功能：直立PD控制
入口参数：角度、角速度
返回  值：直立控制PWM
**************************************************************************/
int balance(float Angle, float Gyro)
{
	float Bias;
	int balance;
	Bias = Angle - 0;					//===求出平衡的角度中值 和机械相关
	balance = Balance_Kp * Bias + Gyro * Balance_Kd;		//===计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数 
	return balance;
}

/**************************************************************************
函数功能：速度PI控制 修改前进后退速度，请修Target_Velocity，比如，改成60就比较慢了
入口参数：左轮编码器、右轮编码器
返回  值：速度控制PWM
**************************************************************************/
int velocity(int encoder_left, int encoder_right)
{
	static float Velocity,Encoder_Least, Encoder,Movement;
	static float Encoder_Integral;
	//=============速度PI控制器=======================//
	Encoder_Least = (encoder_left + encoder_right) - 0;				//===获取最新速度偏差==测量速度（左右编码器之和）-目标速度（此处为零）//===获取最新速度偏差==测量速度（左右编码器之和）-目标速度（此处为零）
	Encoder *= 0.8;																						//===一阶低通滤波器
	Encoder += Encoder_Least * 0.2;														//===一阶低通滤波器
	Encoder_Integral += Encoder;															//===积分出位移 积分时间：10ms
	Encoder_Integral = Encoder_Integral - Movement;						//===接收遥控器数据，控制前进后退
	if(Encoder_Integral>10000)  	Encoder_Integral=10000;			//===积分限幅
	if(Encoder_Integral<-10000)	Encoder_Integral=-10000;			//===积分限幅	
	Velocity = Encoder * Velocity_Kp + Encoder_Integral * Velocity_Ki;		//===速度控制	
	return Velocity;
}

/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：左轮PWM、右轮PWM
返回  值：无
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
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=6900;    //===PWM满幅是7200 限制在6900
		if(Flag_Qian==1)  Moto1+=DIFFERENCE;  //DIFFERENCE是一个衡量平衡小车电机和机械安装差异的一个变量。直接作用于输出，让小车具有更好的一致性。
	  if(Flag_Hou==1)   Moto2-=DIFFERENCE;
    if(Moto1<-Amplitude) Moto1=-Amplitude;	
		if(Moto1>Amplitude)  Moto1=Amplitude;	
	  if(Moto2<-Amplitude) Moto2=-Amplitude;	
		if(Moto2>Amplitude)  Moto2=Amplitude;		
	
}
/**************************************************************************
函数功能：获取角度 三种算法经过我们的调校，都非常理想 
入口参数：获取角度的算法 1：DMP  2：卡尔曼 3：互补滤波
返回  值：无
**************************************************************************/
void Get_Angle(u8 way)
{ 
	    if(way==1)                           //===DMP的读取在数据采集中断读取，严格遵循时序要求
			{	
					Read_DMP();                      //===读取加速度、角速度、倾角
					Angle_Balance=-Roll;             //===更新平衡倾角
					Gyro_Balance=-gyro[0];            //===更新平衡角速度
					Gyro_Turn=gyro[2];               //===更新转向角速度
			}			
}
/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}




