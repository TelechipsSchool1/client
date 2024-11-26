//*********************//
// 파일명 : heart.h
// 작성자 : jude.kwon
// 작성일 : 24.11.26
// 수정일 : -
//*********************//

#ifndef HEART_RATE_H
#define HEART_RATE_H

#include <stdint.h> // uint32_t 사용을 위해
#include <stdio.h>

// 초기화 함수
int initialize_max30102();

// 심박수 계산 함수
double calculate_heart_rate();

#endif // HEART_RATE_H
