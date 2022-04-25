#line 1 "D:/bibliothque_publie_dans_mikroc/GY_85/GY85 9DOF IMU/GY-85_9DOF_IMU/GY85.c"
#line 1 "d:/bibliothque_publie_dans_mikroc/gy_85/gy85 9dof imu/gy-85_9dof_imu/gy85.h"


 unsigned short Read_Byte(unsigned short address_sensor,unsigned short register_address);
 void Acc_Init();
 void Acc_Read();
 void Magneto_Init();
 void Magneto_Read();
 void Gyro_Init();
 void Gyro_Read();
#line 34 "D:/bibliothque_publie_dans_mikroc/GY_85/GY85 9DOF IMU/GY-85_9DOF_IMU/GY85.c"
extern volatile int accel[3];
extern volatile int magnetom[3];
extern volatile int gyro[3];


unsigned short accel_Read_Byte(unsigned short address_sensor,unsigned short register_address) {
 unsigned short Data_Read = 0;

 I2C1_Start();
 I2C1_Wr(address_sensor);
 I2C1_Wr(register_address);

 I2C1_Start();
 I2C1_Wr(address_sensor+1);
 Data_Read = I2C1_Rd(0);
 I2C1_Stop();

 return Data_Read;
}

void Acc_Init(){
 I2C1_Start();
 I2C1_Wr( 0xA6 );
 I2C1_Wr(0X2D);
 I2C1_Wr(0X00);
 I2C1_Stop();

 Delay_ms(5);

 I2C1_Start();
 I2C1_Wr( 0xA6 );
 I2C1_Wr(0X31);
 I2C1_Wr(0X08);
 I2C1_Stop();

 Delay_ms(5);

 I2C1_Start();
 I2C1_Wr( 0xA6 );
 I2C1_Wr(0X2C);
 I2C1_Wr(0X09);
 I2C1_Stop();

 Delay_ms(5);
 I2C1_Start();
 I2C1_Wr( 0xA6 );
 I2C1_Wr(0X2D);
 I2C1_Wr(0X08);
 I2C1_Stop();
 }


void Acc_Read(){
 unsigned short buffer[6];
 buffer[0]=accel_Read_Byte( 0xA6 , 0x32 );
 buffer[1]=accel_Read_Byte( 0xA6 , 0x33 );

 buffer[2]=accel_Read_Byte( 0xA6 , 0x34 );
 buffer[3]=accel_Read_Byte( 0xA6 , 0x35 );

 buffer[4]=accel_Read_Byte( 0xA6 , 0x36 );
 buffer[5]=accel_Read_Byte( 0xA6 , 0x37 );

 accel[0] = (((int) buffer[1]) << 8) | buffer[0];
 accel[1] = (((int) buffer[3]) << 8) | buffer[2];
 accel[2] = (((int) buffer[5]) << 8) | buffer[4];
 }


 void HMC5883L_write(unsigned char reg_address, unsigned char value)
{
 I2C1_Start();
 I2C1_Wr( 0x3C );
 I2C1_Wr(reg_address);
 I2C1_Wr(value);
 I2C1_Stop();
}
 void Magneto_Init()
{
 unsigned char value = 0;
 HMC5883L_write( 0x00 , 0b00011000);
 HMC5883L_write( 0x01 , 0xA0);
 HMC5883L_write( 0x02 , 0x00);
}

void Magneto_Read(){
 unsigned short buffer[6];
 I2C1_Start();
 I2C1_Wr( 0x3C );
 I2C1_Wr( 0x03 );
 I2C1_Start();
 I2C1_Wr( 0x3D );
 buffer[0]=I2C1_Rd(1);
 buffer[1]=I2C1_Rd(1);
 buffer[2]=I2C1_Rd(1);
 buffer[3]=I2C1_Rd(1);
 buffer[4]=I2C1_Rd(1);
 buffer[5]=I2C1_Rd(0);
 I2C1_Stop();

 magnetom[1] = 1 * ((((int) buffer[0]) << 8) | buffer[1]);
 magnetom[0] = 1 * ((((int) buffer[4]) << 8) | buffer[5]);
 magnetom[2] = 1 * ((((int) buffer[2]) << 8) | buffer[3]);

 }


void Gyro_Init(){

 I2C1_Start();
 I2C1_Wr( 0xD0 );
 I2C1_Wr(0X3E);
 I2C1_Wr(0X80);
 I2C1_Stop();


 I2C1_Start();
 I2C1_Wr( 0xD0 );
 I2C1_Wr(0X15);
 I2C1_Wr(0X0A);
 I2C1_Stop();



 I2C1_Start();
 I2C1_Wr( 0xD0 );
 I2C1_Wr(0X16);
 I2C1_Wr(0X1B);
 I2C1_Stop();


 I2C1_Start();
 I2C1_Wr( 0xD0 );
 I2C1_Wr(0X3E);
 I2C1_Wr(0X03);
 I2C1_Stop();


 }


 void Gyro_Read(){
 unsigned short buffer[6];
 I2C1_Start();
 I2C1_Wr( 0xD0 );
 I2C1_Wr(0X1D);
 I2C1_Start();
 I2C1_Wr( 0xD1 );

 buffer[0]=I2C1_Rd(1);
 buffer[1]=I2C1_Rd(1);
 buffer[2]=I2C1_Rd(1);
 buffer[3]=I2C1_Rd(1);
 buffer[4]=I2C1_Rd(1);
 buffer[5]=I2C1_Rd(0);
 I2C1_Stop();


 gyro[0] = 1 * ((((int) buffer[0]) << 8) | buffer[1]);
 gyro[1] = 1 * ((((int) buffer[2]) << 8) | buffer[3]);
 gyro[2] = 1 * ((((int) buffer[4]) << 8) | buffer[5]);
 }
