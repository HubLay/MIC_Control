#ifndef __CAR_SOLUTION_H
#define __CAR_SOLUTION_H


void Move_Transfrom(float Vx,float Vy,float Vz);
void YaoKong_Move(uint8_t X, uint8_t Y);

#ifdef __cplusplus
extern "C" {
#endif

void Getup_prveArm();
void Putdown_prveArm();
void Getup_backArm();
void Putdown_backArm();
void Servo_Init();
void Stop_Arm();

#ifdef __cplusplus
}
#endif

#endif