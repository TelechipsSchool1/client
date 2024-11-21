//*******************************************
// 파일명 : servo.h
// 작성자 : jude.kwon
// 작성일 : 24.11.21
// 수정일 : -
// 
// 서보모터 초기화 및 제어 함수 정의
//********************************************

#ifndef SERVO_H
#define SERVO_H

#include "pwm.h"

// 서보모터 초기화 및 속도 설정 함수
int servo_initialize();
void servo_set_speed(int direction, int speed);

#endif // SERVO_H
