 //============================================================================
// Project: GY-85 9DOF IMU
// Author : Arezki YOUYOU
//Date: 20/09/2014
//============================================================================
//How to Read the data From the sensor of the GY-85 9DOF IMU "Accelerometer ADXL345, Magnetometer HMC5883L and Gyroscope ITG3205"
//============================================================================
// PLL Used CPU frequncy = 48 MHZ, Crystal FOSC = 20MHZ see Edit Project
//============================================================================
// Contact me:
// email: arezkiyouyou@gmail.com
//facebook page: https://www.facebook.com/pages/Elektronik-Design/1399880610289755
//============================================================================
#include <GY85.h>
volatile int accel[3];
volatile int magnetom[3];
volatile int gyro[3];

  void UART1_Printf(int value){
   char txt[7];
   IntToStr(value, txt);
   UART1_Write_Text(txt);
                              }

void printf_result(){
UART1_Write_Text("X_acc:");UART1_Printf(accel[0]); UART1_Write_Text("  ");
UART1_Write_Text("Y_acc:");UART1_Printf(accel[1]); UART1_Write_Text("  ");
UART1_Write_Text("Z_acc:");UART1_Printf(accel[2]); UART1_Write_Text("  ");
UART1_Write_Text("\r\n");

UART1_Write_Text("X_mag:");UART1_Printf(magnetom[0]); UART1_Write_Text("  ");
UART1_Write_Text("Y_mag:");UART1_Printf(magnetom[1]); UART1_Write_Text("  ");
UART1_Write_Text("Z_mag:");UART1_Printf(magnetom[2]); UART1_Write_Text("  ");
UART1_Write_Text("\r\n");

UART1_Write_Text("X_gyro:");UART1_Printf(gyro[0]); UART1_Write_Text("  ");
UART1_Write_Text("Y_gyro:");UART1_Printf(gyro[1]); UART1_Write_Text("  ");
UART1_Write_Text("Z_gyro:");UART1_Printf(gyro[2]); UART1_Write_Text("  ");
UART1_Write_Text("\r\n");
                               }

void GY_85_Init(){
Acc_Init();
Magneto_Init();
Gyro_Init();
                 }
                 
void GY_85_Read(){
Acc_Read();
Magneto_Read();
Gyro_Read();
                 }
                 
void main() {
      TRISC=0;
      TRISC7_bit=1;
      UART1_Init(115200);
      Delay_ms(100);
      UART1_Write_Text("GY-85 Start\r\n");
      I2C1_Init(100000);
      Delay_ms(100);
      GY_85_Init(); // Init GY-85 sensor
      Delay_ms(100);
      
      do{
      GY_85_Read(); // Read GY-85 sensor
      printf_result();// Send the data to the USART
      Delay_ms(1000);
         }while(1);
            }