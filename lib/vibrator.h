//*******************************************************
// 파일명 : vibrator.h
// 작성자 : jude kwon
// 작성일 : 24.11.20
// 
// 파일설명 : 진동 모터 제어를 위한 함수 선언
//*******************************************************

#ifndef VIBRATOR_H
#define VIBRATOR_H

#include "param.h"

// 진동 모터 초기화
int vibrator_init();

// 진동 모터 켜기
int vibrator_on();

// 진동 모터 끄기
int vibrator_off();

#endif // VIBRATOR_H
