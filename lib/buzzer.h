//*******************************************************
// 파일명 : buzzer.h
// 작성자 : jude kwon
// 작성일 : 24.11.26
// 
// 파일설명 : 부저 제어를 위한 함수 선언
//*******************************************************

#ifndef BUZZER_H
#define BUZZER_H

#include "param.h"

// 부저 초기화
int buzzer_init();

// 부저 켜기
int buzzer_on();

// 부저 끄기
int buzzer_off();

#endif // BUZZER_H
