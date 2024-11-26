//*******************************************************
// 파일명 : fan.h
// 작성자 : jude kwon
// 작성일 : 24.11.26
// 
// 파일설명 : 팬 제어를 위한 함수 선언
//*******************************************************

#ifndef FAN_H
#define FAN_H

#include "param.h"

// 팬 초기화
int fan_init();

// 팬 속도 설정 (1단계, 2단계, 3단계)
void fan_set_speed(int speed);

// 팬 종료
void fan_stop();

#endif // FAN_H
