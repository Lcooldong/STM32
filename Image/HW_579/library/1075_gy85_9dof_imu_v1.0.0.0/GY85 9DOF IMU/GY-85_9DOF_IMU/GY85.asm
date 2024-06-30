
_accel_Read_Byte:

;GY85.c,39 :: 		unsigned short accel_Read_Byte(unsigned short address_sensor,unsigned short register_address) {
;GY85.c,40 :: 		unsigned short Data_Read = 0;
	CLRF        accel_Read_Byte_Data_Read_L0+0 
;GY85.c,42 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;GY85.c,43 :: 		I2C1_Wr(address_sensor);
	MOVF        FARG_accel_Read_Byte_address_sensor+0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,44 :: 		I2C1_Wr(register_address);
	MOVF        FARG_accel_Read_Byte_register_address+0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,46 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;GY85.c,47 :: 		I2C1_Wr(address_sensor+1);
	MOVF        FARG_accel_Read_Byte_address_sensor+0, 0 
	ADDLW       1
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,48 :: 		Data_Read = I2C1_Rd(0);
	CLRF        FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       accel_Read_Byte_Data_Read_L0+0 
;GY85.c,49 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;GY85.c,51 :: 		return Data_Read;
	MOVF        accel_Read_Byte_Data_Read_L0+0, 0 
	MOVWF       R0 
;GY85.c,52 :: 		}
	RETURN      0
; end of _accel_Read_Byte

_Acc_Init:

;GY85.c,54 :: 		void Acc_Init(){
;GY85.c,55 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;GY85.c,56 :: 		I2C1_Wr(ACCEL_ADDRESS);
	MOVLW       166
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,57 :: 		I2C1_Wr(0X2D);// Power register
	MOVLW       45
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,58 :: 		I2C1_Wr(0X00); // standbay mode
	CLRF        FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,59 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;GY85.c,61 :: 		Delay_ms(5);
	MOVLW       78
	MOVWF       R12, 0
	MOVLW       235
	MOVWF       R13, 0
L_Acc_Init0:
	DECFSZ      R13, 1, 1
	BRA         L_Acc_Init0
	DECFSZ      R12, 1, 1
	BRA         L_Acc_Init0
;GY85.c,63 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;GY85.c,64 :: 		I2C1_Wr(ACCEL_ADDRESS);
	MOVLW       166
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,65 :: 		I2C1_Wr(0X31);// Data format register
	MOVLW       49
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,66 :: 		I2C1_Wr(0X08); // Set to full resolution
	MOVLW       8
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,67 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;GY85.c,69 :: 		Delay_ms(5);
	MOVLW       78
	MOVWF       R12, 0
	MOVLW       235
	MOVWF       R13, 0
L_Acc_Init1:
	DECFSZ      R13, 1, 1
	BRA         L_Acc_Init1
	DECFSZ      R12, 1, 1
	BRA         L_Acc_Init1
;GY85.c,71 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;GY85.c,72 :: 		I2C1_Wr(ACCEL_ADDRESS);
	MOVLW       166
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,73 :: 		I2C1_Wr(0X2C);// Data format register
	MOVLW       44
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,74 :: 		I2C1_Wr(0X09); // Set to full resolution
	MOVLW       9
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,75 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;GY85.c,77 :: 		Delay_ms(5);
	MOVLW       78
	MOVWF       R12, 0
	MOVLW       235
	MOVWF       R13, 0
L_Acc_Init2:
	DECFSZ      R13, 1, 1
	BRA         L_Acc_Init2
	DECFSZ      R12, 1, 1
	BRA         L_Acc_Init2
;GY85.c,78 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;GY85.c,79 :: 		I2C1_Wr(ACCEL_ADDRESS);
	MOVLW       166
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,80 :: 		I2C1_Wr(0X2D);// Power register
	MOVLW       45
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,81 :: 		I2C1_Wr(0X08); // measure mode
	MOVLW       8
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,82 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;GY85.c,83 :: 		}
	RETURN      0
; end of _Acc_Init

_Acc_Read:

;GY85.c,86 :: 		void Acc_Read(){
;GY85.c,88 :: 		buffer[0]=accel_Read_Byte(ACCEL_ADDRESS,_X_LOW);  // low_x
	MOVLW       166
	MOVWF       FARG_accel_Read_Byte_address_sensor+0 
	MOVLW       50
	MOVWF       FARG_accel_Read_Byte_register_address+0 
	CALL        _accel_Read_Byte+0, 0
	MOVF        R0, 0 
	MOVWF       Acc_Read_buffer_L0+0 
;GY85.c,89 :: 		buffer[1]=accel_Read_Byte(ACCEL_ADDRESS,_X_HIG); //  high_x
	MOVLW       166
	MOVWF       FARG_accel_Read_Byte_address_sensor+0 
	MOVLW       51
	MOVWF       FARG_accel_Read_Byte_register_address+0 
	CALL        _accel_Read_Byte+0, 0
	MOVF        R0, 0 
	MOVWF       Acc_Read_buffer_L0+1 
;GY85.c,91 :: 		buffer[2]=accel_Read_Byte(ACCEL_ADDRESS,_Y_LOW);  // low_y
	MOVLW       166
	MOVWF       FARG_accel_Read_Byte_address_sensor+0 
	MOVLW       52
	MOVWF       FARG_accel_Read_Byte_register_address+0 
	CALL        _accel_Read_Byte+0, 0
	MOVF        R0, 0 
	MOVWF       Acc_Read_buffer_L0+2 
;GY85.c,92 :: 		buffer[3]=accel_Read_Byte(ACCEL_ADDRESS,_Y_HIG); //  high_y
	MOVLW       166
	MOVWF       FARG_accel_Read_Byte_address_sensor+0 
	MOVLW       53
	MOVWF       FARG_accel_Read_Byte_register_address+0 
	CALL        _accel_Read_Byte+0, 0
	MOVF        R0, 0 
	MOVWF       Acc_Read_buffer_L0+3 
;GY85.c,94 :: 		buffer[4]=accel_Read_Byte(ACCEL_ADDRESS,_Z_LOW);  // low_y
	MOVLW       166
	MOVWF       FARG_accel_Read_Byte_address_sensor+0 
	MOVLW       54
	MOVWF       FARG_accel_Read_Byte_register_address+0 
	CALL        _accel_Read_Byte+0, 0
	MOVF        R0, 0 
	MOVWF       Acc_Read_buffer_L0+4 
;GY85.c,95 :: 		buffer[5]=accel_Read_Byte(ACCEL_ADDRESS,_Z_HIG); //  high_y
	MOVLW       166
	MOVWF       FARG_accel_Read_Byte_address_sensor+0 
	MOVLW       55
	MOVWF       FARG_accel_Read_Byte_register_address+0 
	CALL        _accel_Read_Byte+0, 0
	MOVF        R0, 0 
	MOVWF       Acc_Read_buffer_L0+5 
;GY85.c,97 :: 		accel[0] = (((int) buffer[1]) << 8) | buffer[0];  // X axis
	MOVF        Acc_Read_buffer_L0+1, 0 
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	MOVF        R4, 0 
	MOVWF       R2 
	CLRF        R1 
	MOVF        Acc_Read_buffer_L0+0, 0 
	IORWF       R1, 0 
	MOVWF       _accel+0 
	MOVF        R2, 0 
	MOVWF       _accel+1 
	MOVLW       0
	IORWF       _accel+1, 1 
;GY85.c,98 :: 		accel[1] = (((int) buffer[3]) << 8) | buffer[2];  // Y axis
	MOVF        Acc_Read_buffer_L0+3, 0 
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	MOVF        R4, 0 
	MOVWF       R2 
	CLRF        R1 
	MOVF        Acc_Read_buffer_L0+2, 0 
	IORWF       R1, 0 
	MOVWF       _accel+2 
	MOVF        R2, 0 
	MOVWF       _accel+3 
	MOVLW       0
	IORWF       _accel+3, 1 
;GY85.c,99 :: 		accel[2] = (((int) buffer[5]) << 8) | buffer[4];  // Z axis
	MOVF        R0, 0 
	MOVWF       R3 
	MOVLW       0
	MOVWF       R4 
	MOVF        R3, 0 
	MOVWF       R1 
	CLRF        R0 
	MOVF        Acc_Read_buffer_L0+4, 0 
	IORWF       R0, 0 
	MOVWF       _accel+4 
	MOVF        R1, 0 
	MOVWF       _accel+5 
	MOVLW       0
	IORWF       _accel+5, 1 
;GY85.c,100 :: 		}
	RETURN      0
; end of _Acc_Read

_HMC5883L_write:

;GY85.c,103 :: 		void HMC5883L_write(unsigned char reg_address, unsigned char value)
;GY85.c,105 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;GY85.c,106 :: 		I2C1_Wr(HMC5883L_WRITE_ADDR);
	MOVLW       60
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,107 :: 		I2C1_Wr(reg_address);
	MOVF        FARG_HMC5883L_write_reg_address+0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,108 :: 		I2C1_Wr(value);
	MOVF        FARG_HMC5883L_write_value+0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,109 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;GY85.c,110 :: 		}
	RETURN      0
; end of _HMC5883L_write

_Magneto_Init:

;GY85.c,111 :: 		void Magneto_Init()
;GY85.c,113 :: 		unsigned char value = 0;
;GY85.c,114 :: 		HMC5883L_write(Config_Reg_A, 0b00011000);
	CLRF        FARG_HMC5883L_write_reg_address+0 
	MOVLW       24
	MOVWF       FARG_HMC5883L_write_value+0 
	CALL        _HMC5883L_write+0, 0
;GY85.c,115 :: 		HMC5883L_write(Config_Reg_B, 0xA0);
	MOVLW       1
	MOVWF       FARG_HMC5883L_write_reg_address+0 
	MOVLW       160
	MOVWF       FARG_HMC5883L_write_value+0 
	CALL        _HMC5883L_write+0, 0
;GY85.c,116 :: 		HMC5883L_write(Mode_Reg, 0x00);
	MOVLW       2
	MOVWF       FARG_HMC5883L_write_reg_address+0 
	CLRF        FARG_HMC5883L_write_value+0 
	CALL        _HMC5883L_write+0, 0
;GY85.c,117 :: 		}
	RETURN      0
; end of _Magneto_Init

_Magneto_Read:

;GY85.c,119 :: 		void Magneto_Read(){
;GY85.c,121 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;GY85.c,122 :: 		I2C1_Wr(HMC5883L_WRITE_ADDR);
	MOVLW       60
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,123 :: 		I2C1_Wr(X_MSB_Reg);
	MOVLW       3
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,124 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;GY85.c,125 :: 		I2C1_Wr(HMC5883L_READ_ADDR);
	MOVLW       61
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,126 :: 		buffer[0]=I2C1_Rd(1);
	MOVLW       1
	MOVWF       FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       Magneto_Read_buffer_L0+0 
;GY85.c,127 :: 		buffer[1]=I2C1_Rd(1);
	MOVLW       1
	MOVWF       FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       Magneto_Read_buffer_L0+1 
;GY85.c,128 :: 		buffer[2]=I2C1_Rd(1);
	MOVLW       1
	MOVWF       FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       Magneto_Read_buffer_L0+2 
;GY85.c,129 :: 		buffer[3]=I2C1_Rd(1);
	MOVLW       1
	MOVWF       FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       Magneto_Read_buffer_L0+3 
;GY85.c,130 :: 		buffer[4]=I2C1_Rd(1);
	MOVLW       1
	MOVWF       FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       Magneto_Read_buffer_L0+4 
;GY85.c,131 :: 		buffer[5]=I2C1_Rd(0);
	CLRF        FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       Magneto_Read_buffer_L0+5 
;GY85.c,132 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;GY85.c,134 :: 		magnetom[1] = 1 * ((((int) buffer[0]) << 8) | buffer[1]);  // X axis (internal sensor -y axis)
	MOVF        Magneto_Read_buffer_L0+0, 0 
	MOVWF       R3 
	MOVLW       0
	MOVWF       R4 
	MOVF        R3, 0 
	MOVWF       R1 
	CLRF        R0 
	MOVF        Magneto_Read_buffer_L0+1, 0 
	IORWF       R0, 0 
	MOVWF       _magnetom+2 
	MOVF        R1, 0 
	MOVWF       _magnetom+3 
	MOVLW       0
	IORWF       _magnetom+3, 1 
;GY85.c,135 :: 		magnetom[0] = 1 * ((((int) buffer[4]) << 8) | buffer[5]);  // Y axis (internal sensor -x axis)
	MOVF        Magneto_Read_buffer_L0+4, 0 
	MOVWF       R3 
	MOVLW       0
	MOVWF       R4 
	MOVF        R3, 0 
	MOVWF       R1 
	CLRF        R0 
	MOVF        Magneto_Read_buffer_L0+5, 0 
	IORWF       R0, 0 
	MOVWF       _magnetom+0 
	MOVF        R1, 0 
	MOVWF       _magnetom+1 
	MOVLW       0
	IORWF       _magnetom+1, 1 
;GY85.c,136 :: 		magnetom[2] = 1 * ((((int) buffer[2]) << 8) | buffer[3]);  // Z axis (internal sensor -z axis)
	MOVF        Magneto_Read_buffer_L0+2, 0 
	MOVWF       R3 
	MOVLW       0
	MOVWF       R4 
	MOVF        R3, 0 
	MOVWF       R1 
	CLRF        R0 
	MOVF        Magneto_Read_buffer_L0+3, 0 
	IORWF       R0, 0 
	MOVWF       _magnetom+4 
	MOVF        R1, 0 
	MOVWF       _magnetom+5 
	MOVLW       0
	IORWF       _magnetom+5, 1 
;GY85.c,138 :: 		}
	RETURN      0
; end of _Magneto_Read

_Gyro_Init:

;GY85.c,141 :: 		void Gyro_Init(){
;GY85.c,143 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;GY85.c,144 :: 		I2C1_Wr(GYRO_ADDRESS_Wr);
	MOVLW       208
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,145 :: 		I2C1_Wr(0X3E);
	MOVLW       62
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,146 :: 		I2C1_Wr(0X80);
	MOVLW       128
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,147 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;GY85.c,150 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;GY85.c,151 :: 		I2C1_Wr(GYRO_ADDRESS_Wr);
	MOVLW       208
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,152 :: 		I2C1_Wr(0X15);
	MOVLW       21
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,153 :: 		I2C1_Wr(0X0A); //SMPLRT_DIV = 10 (50Hz)
	MOVLW       10
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,154 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;GY85.c,158 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;GY85.c,159 :: 		I2C1_Wr(GYRO_ADDRESS_Wr);
	MOVLW       208
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,160 :: 		I2C1_Wr(0X16);
	MOVLW       22
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,161 :: 		I2C1_Wr(0X1B);
	MOVLW       27
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,162 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;GY85.c,165 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;GY85.c,166 :: 		I2C1_Wr(GYRO_ADDRESS_Wr);
	MOVLW       208
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,167 :: 		I2C1_Wr(0X3E);
	MOVLW       62
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,168 :: 		I2C1_Wr(0X03);
	MOVLW       3
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,169 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;GY85.c,172 :: 		}
	RETURN      0
; end of _Gyro_Init

_Gyro_Read:

;GY85.c,175 :: 		void Gyro_Read(){
;GY85.c,177 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;GY85.c,178 :: 		I2C1_Wr(GYRO_ADDRESS_Wr);
	MOVLW       208
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,179 :: 		I2C1_Wr(0X1D);
	MOVLW       29
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,180 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;GY85.c,181 :: 		I2C1_Wr(GYRO_ADDRESS_Rd);
	MOVLW       209
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;GY85.c,183 :: 		buffer[0]=I2C1_Rd(1);
	MOVLW       1
	MOVWF       FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       Gyro_Read_buffer_L0+0 
;GY85.c,184 :: 		buffer[1]=I2C1_Rd(1);
	MOVLW       1
	MOVWF       FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       Gyro_Read_buffer_L0+1 
;GY85.c,185 :: 		buffer[2]=I2C1_Rd(1);
	MOVLW       1
	MOVWF       FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       Gyro_Read_buffer_L0+2 
;GY85.c,186 :: 		buffer[3]=I2C1_Rd(1);
	MOVLW       1
	MOVWF       FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       Gyro_Read_buffer_L0+3 
;GY85.c,187 :: 		buffer[4]=I2C1_Rd(1);
	MOVLW       1
	MOVWF       FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       Gyro_Read_buffer_L0+4 
;GY85.c,188 :: 		buffer[5]=I2C1_Rd(0);
	CLRF        FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       Gyro_Read_buffer_L0+5 
;GY85.c,189 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;GY85.c,192 :: 		gyro[0] = 1 * ((((int) buffer[0]) << 8) | buffer[1]);    // X axis (internal sensor -y axis)
	MOVF        Gyro_Read_buffer_L0+0, 0 
	MOVWF       R3 
	MOVLW       0
	MOVWF       R4 
	MOVF        R3, 0 
	MOVWF       R1 
	CLRF        R0 
	MOVF        Gyro_Read_buffer_L0+1, 0 
	IORWF       R0, 0 
	MOVWF       _gyro+0 
	MOVF        R1, 0 
	MOVWF       _gyro+1 
	MOVLW       0
	IORWF       _gyro+1, 1 
;GY85.c,193 :: 		gyro[1] = 1 * ((((int) buffer[2]) << 8) | buffer[3]);    // Y axis (internal sensor -x axis)
	MOVF        Gyro_Read_buffer_L0+2, 0 
	MOVWF       R3 
	MOVLW       0
	MOVWF       R4 
	MOVF        R3, 0 
	MOVWF       R1 
	CLRF        R0 
	MOVF        Gyro_Read_buffer_L0+3, 0 
	IORWF       R0, 0 
	MOVWF       _gyro+2 
	MOVF        R1, 0 
	MOVWF       _gyro+3 
	MOVLW       0
	IORWF       _gyro+3, 1 
;GY85.c,194 :: 		gyro[2] = 1 * ((((int) buffer[4]) << 8) | buffer[5]);    // Z axis (internal sensor -z axis)
	MOVF        Gyro_Read_buffer_L0+4, 0 
	MOVWF       R3 
	MOVLW       0
	MOVWF       R4 
	MOVF        R3, 0 
	MOVWF       R1 
	CLRF        R0 
	MOVF        Gyro_Read_buffer_L0+5, 0 
	IORWF       R0, 0 
	MOVWF       _gyro+4 
	MOVF        R1, 0 
	MOVWF       _gyro+5 
	MOVLW       0
	IORWF       _gyro+5, 1 
;GY85.c,195 :: 		}
	RETURN      0
; end of _Gyro_Read
