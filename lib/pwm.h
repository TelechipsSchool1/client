//*********************//
// 파일명 : pwm.h
// 작성자 : jude.kwon
// 작성일 : 24.11.07
// edit date : 24.11.11
//*********************//


#ifndef PWM_H
#define PWM_H

#include <stdio.h>
#include <stdlib.h>
#include "param.h"  // param.h에서 PWM 설정 사용

// PWM 함수
int initialize_pwm(const char *channel_path);
void update_pwm_duty_cycle(const char *channel_path, int duty_cycle);

#endif // PWM_H

