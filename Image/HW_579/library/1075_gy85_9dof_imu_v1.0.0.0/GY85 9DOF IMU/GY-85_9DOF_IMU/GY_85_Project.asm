
_UART1_Printf:

;GY_85_Project.c,19 :: 		void UART1_Printf(int value){
;GY_85_Project.c,21 :: 		IntToStr(value, txt);
	MOVF        FARG_UART1_Printf_value+0, 0 
	MOVWF       FARG_IntToStr_input+0 
	MOVF        FARG_UART1_Printf_value+1, 0 
	MOVWF       FARG_IntToStr_input+1 
	MOVLW       UART1_Printf_txt_L0+0
	MOVWF       FARG_IntToStr_output+0 
	MOVLW       hi_addr(UART1_Printf_txt_L0+0)
	MOVWF       FARG_IntToStr_output+1 
	CALL        _IntToStr+0, 0
;GY_85_Project.c,22 :: 		UART1_Write_Text(txt);
	MOVLW       UART1_Printf_txt_L0+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(UART1_Printf_txt_L0+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;GY_85_Project.c,23 :: 		}
	RETURN      0
; end of _UART1_Printf

_printf_result:

;GY_85_Project.c,25 :: 		void printf_result(){
;GY_85_Project.c,26 :: 		UART1_Write_Text("X_acc:");UART1_Printf(accel[0]); UART1_Write_Text("  ");
	MOVLW       ?lstr1_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr1_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
	MOVF        _accel+0, 0 
	MOVWF       FARG_UART1_Printf_value+0 
	MOVF        _accel+1, 0 
	MOVWF       FARG_UART1_Printf_value+1 
	CALL        _UART1_Printf+0, 0
	MOVLW       ?lstr2_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr2_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;GY_85_Project.c,27 :: 		UART1_Write_Text("Y_acc:");UART1_Printf(accel[1]); UART1_Write_Text("  ");
	MOVLW       ?lstr3_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr3_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
	MOVF        _accel+2, 0 
	MOVWF       FARG_UART1_Printf_value+0 
	MOVF        _accel+3, 0 
	MOVWF       FARG_UART1_Printf_value+1 
	CALL        _UART1_Printf+0, 0
	MOVLW       ?lstr4_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr4_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;GY_85_Project.c,28 :: 		UART1_Write_Text("Z_acc:");UART1_Printf(accel[2]); UART1_Write_Text("  ");
	MOVLW       ?lstr5_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr5_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
	MOVF        _accel+4, 0 
	MOVWF       FARG_UART1_Printf_value+0 
	MOVF        _accel+5, 0 
	MOVWF       FARG_UART1_Printf_value+1 
	CALL        _UART1_Printf+0, 0
	MOVLW       ?lstr6_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr6_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;GY_85_Project.c,29 :: 		UART1_Write_Text("\r\n");
	MOVLW       ?lstr7_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr7_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;GY_85_Project.c,31 :: 		UART1_Write_Text("X_mag:");UART1_Printf(magnetom[0]); UART1_Write_Text("  ");
	MOVLW       ?lstr8_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr8_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
	MOVF        _magnetom+0, 0 
	MOVWF       FARG_UART1_Printf_value+0 
	MOVF        _magnetom+1, 0 
	MOVWF       FARG_UART1_Printf_value+1 
	CALL        _UART1_Printf+0, 0
	MOVLW       ?lstr9_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr9_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;GY_85_Project.c,32 :: 		UART1_Write_Text("Y_mag:");UART1_Printf(magnetom[1]); UART1_Write_Text("  ");
	MOVLW       ?lstr10_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr10_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
	MOVF        _magnetom+2, 0 
	MOVWF       FARG_UART1_Printf_value+0 
	MOVF        _magnetom+3, 0 
	MOVWF       FARG_UART1_Printf_value+1 
	CALL        _UART1_Printf+0, 0
	MOVLW       ?lstr11_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr11_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;GY_85_Project.c,33 :: 		UART1_Write_Text("Z_mag:");UART1_Printf(magnetom[2]); UART1_Write_Text("  ");
	MOVLW       ?lstr12_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr12_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
	MOVF        _magnetom+4, 0 
	MOVWF       FARG_UART1_Printf_value+0 
	MOVF        _magnetom+5, 0 
	MOVWF       FARG_UART1_Printf_value+1 
	CALL        _UART1_Printf+0, 0
	MOVLW       ?lstr13_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr13_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;GY_85_Project.c,34 :: 		UART1_Write_Text("\r\n");
	MOVLW       ?lstr14_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr14_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;GY_85_Project.c,36 :: 		UART1_Write_Text("X_gyro:");UART1_Printf(gyro[0]); UART1_Write_Text("  ");
	MOVLW       ?lstr15_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr15_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
	MOVF        _gyro+0, 0 
	MOVWF       FARG_UART1_Printf_value+0 
	MOVF        _gyro+1, 0 
	MOVWF       FARG_UART1_Printf_value+1 
	CALL        _UART1_Printf+0, 0
	MOVLW       ?lstr16_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr16_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;GY_85_Project.c,37 :: 		UART1_Write_Text("Y_gyro:");UART1_Printf(gyro[1]); UART1_Write_Text("  ");
	MOVLW       ?lstr17_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr17_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
	MOVF        _gyro+2, 0 
	MOVWF       FARG_UART1_Printf_value+0 
	MOVF        _gyro+3, 0 
	MOVWF       FARG_UART1_Printf_value+1 
	CALL        _UART1_Printf+0, 0
	MOVLW       ?lstr18_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr18_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;GY_85_Project.c,38 :: 		UART1_Write_Text("Z_gyro:");UART1_Printf(gyro[2]); UART1_Write_Text("  ");
	MOVLW       ?lstr19_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr19_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
	MOVF        _gyro+4, 0 
	MOVWF       FARG_UART1_Printf_value+0 
	MOVF        _gyro+5, 0 
	MOVWF       FARG_UART1_Printf_value+1 
	CALL        _UART1_Printf+0, 0
	MOVLW       ?lstr20_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr20_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;GY_85_Project.c,39 :: 		UART1_Write_Text("\r\n");
	MOVLW       ?lstr21_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr21_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;GY_85_Project.c,40 :: 		}
	RETURN      0
; end of _printf_result

_GY_85_Init:

;GY_85_Project.c,42 :: 		void GY_85_Init(){
;GY_85_Project.c,43 :: 		Acc_Init();
	CALL        _Acc_Init+0, 0
;GY_85_Project.c,44 :: 		Magneto_Init();
	CALL        _Magneto_Init+0, 0
;GY_85_Project.c,45 :: 		Gyro_Init();
	CALL        _Gyro_Init+0, 0
;GY_85_Project.c,46 :: 		}
	RETURN      0
; end of _GY_85_Init

_GY_85_Read:

;GY_85_Project.c,48 :: 		void GY_85_Read(){
;GY_85_Project.c,49 :: 		Acc_Read();
	CALL        _Acc_Read+0, 0
;GY_85_Project.c,50 :: 		Magneto_Read();
	CALL        _Magneto_Read+0, 0
;GY_85_Project.c,51 :: 		Gyro_Read();
	CALL        _Gyro_Read+0, 0
;GY_85_Project.c,52 :: 		}
	RETURN      0
; end of _GY_85_Read

_main:

;GY_85_Project.c,54 :: 		void main() {
;GY_85_Project.c,55 :: 		TRISC=0;
	CLRF        TRISC+0 
;GY_85_Project.c,56 :: 		TRISC7_bit=1;
	BSF         TRISC7_bit+0, 7 
;GY_85_Project.c,57 :: 		UART1_Init(115200);
	MOVLW       25
	MOVWF       SPBRG+0 
	BSF         TXSTA+0, 2, 0
	CALL        _UART1_Init+0, 0
;GY_85_Project.c,58 :: 		Delay_ms(100);
	MOVLW       7
	MOVWF       R11, 0
	MOVLW       23
	MOVWF       R12, 0
	MOVLW       106
	MOVWF       R13, 0
L_main0:
	DECFSZ      R13, 1, 1
	BRA         L_main0
	DECFSZ      R12, 1, 1
	BRA         L_main0
	DECFSZ      R11, 1, 1
	BRA         L_main0
	NOP
;GY_85_Project.c,59 :: 		UART1_Write_Text("GY-85 Start\r\n");
	MOVLW       ?lstr22_GY_85_Project+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr22_GY_85_Project+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;GY_85_Project.c,60 :: 		I2C1_Init(100000);
	MOVLW       120
	MOVWF       SSPADD+0 
	CALL        _I2C1_Init+0, 0
;GY_85_Project.c,61 :: 		Delay_ms(100);
	MOVLW       7
	MOVWF       R11, 0
	MOVLW       23
	MOVWF       R12, 0
	MOVLW       106
	MOVWF       R13, 0
L_main1:
	DECFSZ      R13, 1, 1
	BRA         L_main1
	DECFSZ      R12, 1, 1
	BRA         L_main1
	DECFSZ      R11, 1, 1
	BRA         L_main1
	NOP
;GY_85_Project.c,62 :: 		GY_85_Init(); // Init GY-85 sensor
	CALL        _GY_85_Init+0, 0
;GY_85_Project.c,63 :: 		Delay_ms(100);
	MOVLW       7
	MOVWF       R11, 0
	MOVLW       23
	MOVWF       R12, 0
	MOVLW       106
	MOVWF       R13, 0
L_main2:
	DECFSZ      R13, 1, 1
	BRA         L_main2
	DECFSZ      R12, 1, 1
	BRA         L_main2
	DECFSZ      R11, 1, 1
	BRA         L_main2
	NOP
;GY_85_Project.c,65 :: 		do{
L_main3:
;GY_85_Project.c,66 :: 		GY_85_Read(); // Read GY-85 sensor
	CALL        _GY_85_Read+0, 0
;GY_85_Project.c,67 :: 		printf_result();// Send the data to the USART
	CALL        _printf_result+0, 0
;GY_85_Project.c,68 :: 		Delay_ms(1000);
	MOVLW       61
	MOVWF       R11, 0
	MOVLW       225
	MOVWF       R12, 0
	MOVLW       63
	MOVWF       R13, 0
L_main6:
	DECFSZ      R13, 1, 1
	BRA         L_main6
	DECFSZ      R12, 1, 1
	BRA         L_main6
	DECFSZ      R11, 1, 1
	BRA         L_main6
	NOP
	NOP
;GY_85_Project.c,69 :: 		}while(1);
	GOTO        L_main3
;GY_85_Project.c,70 :: 		}
	GOTO        $+0
; end of _main
