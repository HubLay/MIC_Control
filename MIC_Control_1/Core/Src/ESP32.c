#include "ESP32.h"

uint8_t ESP32_Data[10]; // ESP32发送的数据会传入到这里
uint8_t flag_Mode = 0;		//用于记录自动模式，是否开启，NowMode因为记录两方，用于ROS数据发送会有问题
char Test_Data[50];

uint8_t NowMode = 0;    //模式切换，1代表ESP32手动操控模式，0代表导航等自动模式

// ESP32数据包解析

uint16_t ABS(int16_t Data){
	return Data > 0? Data : -Data;
}

uint16_t X_N = 0,Y_N = 0;
float Ax = 0.0, Ay = 0.0;


uint8_t ESP32_Analysis()
{

  if (ESP32_Data[0] == 0xA5 && ESP32_Data[4] == 0x5A)
  {
		// 模式切换
		if(ESP32_Data[1] & (0x01 << 5) ){
				NowMode = 1;      //手动模式开启

		}
		else{
				NowMode = 0;      //循迹模式开启
				//HAL_UART_Receive_DMA(&huart3,ROS_ReceiveData,100);	//开启ROS的接收通道
		}

		if(NowMode == 0) return 0; 			//当为自动模式下，不对处理，也不控制小车运行

		//前进后退左右控制
		
		X_N = (1-Ax)*ESP32_Data[3] + Ax * X_N;
		Y_N = (1-Ay)*ESP32_Data[2] + Ay * Y_N;
		YaoKong_Move(X_N,Y_N);
		
		//手臂恢复初始状态
		if(ESP32_Data[1] & (0x01 << 2)){
			Stop_Arm();
		}

		if(ESP32_Data[1] & (0x01 << 0)){
			Putdown_prveArm();

		}
		else if(ESP32_Data[1] & (0x01 << 1)){
			Getup_prveArm();
		}

		else if(ESP32_Data[1] & (0x01 << 4)){
			Putdown_backArm();
		}
		else if(ESP32_Data[1] & (0x01 << 3)){
			Getup_backArm();

		}
		return 1;
  }
	return 0;
}
