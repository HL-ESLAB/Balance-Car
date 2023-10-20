#include "mpu6500.h"
#include "IIC.h"


//��ʼ��MPU9250��������Ҫ��ο�pdf�����޸�
void Init_MPU9250(void)
{
	IIC_Init();
	Single_Write(GYRO_ADDRESS, PWR_MGMT_1, 0x00);//�������״̬
	Single_Write(GYRO_ADDRESS, SMPLRT_DIV, 0x07);
	Single_Write(GYRO_ADDRESS, CONFIG, 0x06);
	Single_Write(GYRO_ADDRESS, GYRO_CONFIG, 0x18);
	Single_Write(GYRO_ADDRESS, ACCEL_CONFIG, 0x01);
}

//��ȡMPU9250����(���ٶȣ�������)
void Read_MPU9250_Data(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
												int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	uint8_t DataH, DataL;
	//���ٶȼƵ�x��y��z��
	DataH = Single_Read(ACCEL_ADDRESS, ACCEL_XOUT_H);
	DataL = Single_Read(ACCEL_ADDRESS, ACCEL_XOUT_L);
	*AccX = (DataH << 8) | DataL;
	*AccX /= 164;
	
	DataH = Single_Read(ACCEL_ADDRESS, ACCEL_YOUT_H);
	DataL = Single_Read(ACCEL_ADDRESS, ACCEL_YOUT_L);
	*AccY = (DataH << 8) | DataL;
	*AccY /= 164;

	DataH = Single_Read(ACCEL_ADDRESS, ACCEL_ZOUT_H);
	DataL = Single_Read(ACCEL_ADDRESS, ACCEL_ZOUT_L);
	*AccZ = (DataH << 8) | DataL;
	*AccZ /= 164;
	
	DataH = Single_Read(GYRO_ADDRESS, GYRO_XOUT_H);
	DataL = Single_Read(GYRO_ADDRESS, GYRO_XOUT_L);
	*GyroX = (DataH << 8) | DataL;
	*GyroX /= 16.4;
	
	DataH = Single_Read(GYRO_ADDRESS, GYRO_YOUT_H);
	DataL = Single_Read(GYRO_ADDRESS, GYRO_YOUT_L);
	*GyroY = (DataH << 8) | DataL;
	*GyroY /= 16.4;
	
	DataH = Single_Read(GYRO_ADDRESS, GYRO_ZOUT_H);
	DataL = Single_Read(GYRO_ADDRESS, GYRO_ZOUT_L);
	*GyroZ = (DataH << 8) | DataL;
	*GyroZ /= 16.4;
	
}
