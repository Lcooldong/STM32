 //============================================================================
// Project: GY-85 9DOF IMU
// Author : Arezki YOUYOU
//Date: 20/09/2014
//============================================================================
//How to Read the data From the sensor of the GY-85 9DOF IMU "Accelerometer ADXL345, Magnetometer HMC5883L and Gyroscope ITG3205"
//============================================================================
// Contact me:
// email: arezkiyouyou@gmail.com
//facebook page: https://www.facebook.com/pages/Elektronik-Design/1399880610289755
//============================================================================
#include <GY85.h>
#define ACCEL_ADDRESS  0xA6 // 0x53 = 0xA6 / 2
#define GYRO_ADDRESS_Wr   0xD0// 0x68 = 0xD0 / 2
#define GYRO_ADDRESS_Rd   0xD1
#define HMC5883L_READ_ADDR       0x3D
#define HMC5883L_WRITE_ADDR      0x3C
/***************zone accelerometre************/
#define _X_LOW         0x32
#define _X_HIG         0x33
#define _Y_LOW         0x34
#define _Y_HIG         0x35
#define _Z_LOW         0x36
#define _Z_HIG         0x37
/*************magneto*********************/
#define Config_Reg_A             0x00
#define Config_Reg_B             0x01
#define Mode_Reg                 0x02
#define X_MSB_Reg                0x03
/***************************/



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
////////////////////////////////////
void Acc_Init(){
    I2C1_Start();
    I2C1_Wr(ACCEL_ADDRESS);
    I2C1_Wr(0X2D);// Power register
    I2C1_Wr(0X00); // standbay mode
    I2C1_Stop();

    Delay_ms(5);

    I2C1_Start();
    I2C1_Wr(ACCEL_ADDRESS);
    I2C1_Wr(0X31);// Data format register
    I2C1_Wr(0X08); // Set to full resolution
    I2C1_Stop();

    Delay_ms(5);

    I2C1_Start();
    I2C1_Wr(ACCEL_ADDRESS);
    I2C1_Wr(0X2C);// Data format register
    I2C1_Wr(0X09); // Set to full resolution
    I2C1_Stop();

    Delay_ms(5);
    I2C1_Start();
    I2C1_Wr(ACCEL_ADDRESS);
    I2C1_Wr(0X2D);// Power register
    I2C1_Wr(0X08); // measure mode
    I2C1_Stop();
               }

// Reads x, y and z accelerometer registers
void Acc_Read(){
      unsigned short buffer[6];
      buffer[0]=accel_Read_Byte(ACCEL_ADDRESS,_X_LOW);  // low_x
      buffer[1]=accel_Read_Byte(ACCEL_ADDRESS,_X_HIG); //  high_x
      
      buffer[2]=accel_Read_Byte(ACCEL_ADDRESS,_Y_LOW);  // low_y
      buffer[3]=accel_Read_Byte(ACCEL_ADDRESS,_Y_HIG); //  high_y
      
      buffer[4]=accel_Read_Byte(ACCEL_ADDRESS,_Z_LOW);  // low_y
      buffer[5]=accel_Read_Byte(ACCEL_ADDRESS,_Z_HIG); //  high_y
      
    accel[0] = (((int) buffer[1]) << 8) | buffer[0];  // X axis
    accel[1] = (((int) buffer[3]) << 8) | buffer[2];  // Y axis
    accel[2] = (((int) buffer[5]) << 8) | buffer[4];  // Z axis
               }
  //============================================//
 /***********HMC5883L******************/
 void HMC5883L_write(unsigned char reg_address, unsigned char value)
{
   I2C1_Start();
   I2C1_Wr(HMC5883L_WRITE_ADDR);
   I2C1_Wr(reg_address);
   I2C1_Wr(value);
   I2C1_Stop();
}
 void Magneto_Init()
{
    unsigned char value = 0;
   HMC5883L_write(Config_Reg_A, 0b00011000);
   HMC5883L_write(Config_Reg_B, 0xA0);
   HMC5883L_write(Mode_Reg, 0x00);
}

void Magneto_Read(){
         unsigned short buffer[6];
    I2C1_Start();
    I2C1_Wr(HMC5883L_WRITE_ADDR);
    I2C1_Wr(X_MSB_Reg);
    I2C1_Start();
    I2C1_Wr(HMC5883L_READ_ADDR);
                  buffer[0]=I2C1_Rd(1);
                  buffer[1]=I2C1_Rd(1);
                  buffer[2]=I2C1_Rd(1);
                  buffer[3]=I2C1_Rd(1);
                  buffer[4]=I2C1_Rd(1);
                  buffer[5]=I2C1_Rd(0);
                   I2C1_Stop();
                   
    magnetom[1] = 1 * ((((int) buffer[0]) << 8) | buffer[1]);  // X axis (internal sensor -y axis)
    magnetom[0] = 1 * ((((int) buffer[4]) << 8) | buffer[5]);  // Y axis (internal sensor -x axis)
    magnetom[2] = 1 * ((((int) buffer[2]) << 8) | buffer[3]);  // Z axis (internal sensor -z axis)
    
                   }

/**********ITG3025**************/
void Gyro_Init(){
    // Power up reset defaults
    I2C1_Start();
    I2C1_Wr(GYRO_ADDRESS_Wr);
    I2C1_Wr(0X3E);
    I2C1_Wr(0X80);
    I2C1_Stop();

   // Set sample rato to 50Hz
    I2C1_Start();
    I2C1_Wr(GYRO_ADDRESS_Wr);
    I2C1_Wr(0X15);
    I2C1_Wr(0X0A); //SMPLRT_DIV = 10 (50Hz)
    I2C1_Stop();

  // Select full-scale range of the gyro sensors
  // Set LP filter bandwidth to 42Hz
    I2C1_Start();
    I2C1_Wr(GYRO_ADDRESS_Wr);
    I2C1_Wr(0X16);
    I2C1_Wr(0X1B);
    I2C1_Stop();

    // Set clock to PLL with z gyro reference
    I2C1_Start();
    I2C1_Wr(GYRO_ADDRESS_Wr);
    I2C1_Wr(0X3E);
    I2C1_Wr(0X03);
    I2C1_Stop();


                  }
                  
 // Reads x, y and z
 void Gyro_Read(){
                   unsigned short buffer[6];
   I2C1_Start();
   I2C1_Wr(GYRO_ADDRESS_Wr);
   I2C1_Wr(0X1D);
   I2C1_Start();
   I2C1_Wr(GYRO_ADDRESS_Rd);
   
                  buffer[0]=I2C1_Rd(1);
                  buffer[1]=I2C1_Rd(1);
                  buffer[2]=I2C1_Rd(1);
                  buffer[3]=I2C1_Rd(1);
                  buffer[4]=I2C1_Rd(1);
                  buffer[5]=I2C1_Rd(0);
                  I2C1_Stop();

      
    gyro[0] = 1 * ((((int) buffer[0]) << 8) | buffer[1]);    // X axis (internal sensor -y axis)
    gyro[1] = 1 * ((((int) buffer[2]) << 8) | buffer[3]);    // Y axis (internal sensor -x axis)
    gyro[2] = 1 * ((((int) buffer[4]) << 8) | buffer[5]);    // Z axis (internal sensor -z axis)
                 }