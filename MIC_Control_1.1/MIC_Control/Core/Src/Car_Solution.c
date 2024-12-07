#include "stm32f1xx_hal.h"
#include "Motor.h"
#include "tim.h"

//W-> 轮距，机器人左右麦轮的距离，单位：m。
//H-> 轴距，机器人前后麦轮的距离，单位：m，
#define Car_H 0.01950
#define Car_W 0.01858
#define X_static 100
#define Y_static 100


//ROS下整车移动量转换为单轮速度  x:前+后-  y:左+右-  z:逆+顺-
void Move_Transfrom(float Vx,float Vy,float Vz)
{
	M1.Expect_Speed= 22.1868f * (float)(Vx-Vy-Vz*(Car_H/2+Car_W/2));                //将速度转换为 10ms内应捕获到的脉冲数
	M2.Expect_Speed= -22.1868f * (float)(Vx+Vy+Vz*(Car_H/2+Car_W/2));                //209*0.01*4/（0.03*2*3.14）
	M3.Expect_Speed= 22.1868f * (float)(Vx-Vy+Vz*(Car_H/2+Car_W/2));
  M4.Expect_Speed= -22.1868f * (float)(Vx+Vy-Vz*(Car_H/2+Car_W/2));
  
} 

//遥感下，小车速度映射
void YaoKong_Move(uint8_t X, uint8_t Y){
    float x = (float)(X - X_static) / 100.00;          //将遥感上的数据映射，100 --- 2m/s
    float y = -(float)(Y - Y_static) / 100.00;
		
		
    Move_Transfrom(x,y,0);
}

//舵机PWM启动
void Servo_Init(){
  __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,150);
  __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,50);      //初始-90度，后臂
  __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_4,150);

  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_ALL);
}

//前臂下降    设为目标180度，手动到了预期按键停止
void Putdown_prveArm(){
  __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,0);
  __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_4,0);
}

//前臂回收,回到竖直状态，0度
void Getup_prveArm(){
  __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,150);
  __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_4,150);
}

//后臂下降      初始位置为-90度
void Putdown_backArm(){
  __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,150);
}

//后臂回收      回收后为90度
void Getup_backArm(){
  __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,250);
}

//手臂恢复初始状态   
void Stop_Arm(){
  __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,150);
  __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,50);      //初始-90度，后臂
  __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_4,150);
}

       