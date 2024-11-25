//*******************************************
// 파일명 : servo.c
// 작성자 : jude.kwon
// 작성일 : 24.11.21
// 수정일 : -
// 
//********************************************

#include "servo.h"



int servo_initialize() {
    return initialize_pwm(PWM1_CHANNEL_PATH);
}

void servo_set_speed(int direction, int speed) {
    if (speed < 0) speed = 0;
    if (speed > 100) speed = 100; // 속도는 0~100%로 제한

    int duty_cycle;
    if (direction > 0) { // 시계 방향
        duty_cycle = SERVO_NEUTRAL_DUTY_CYCLE +
                     ((SERVO_MAX_DUTY_CYCLE - SERVO_NEUTRAL_DUTY_CYCLE) * speed / 100);
    } else if (direction < 0) { // 반시계 방향
        duty_cycle = SERVO_NEUTRAL_DUTY_CYCLE -
                     ((SERVO_NEUTRAL_DUTY_CYCLE - SERVO_MIN_DUTY_CYCLE) * speed / 100);
    } else { // 정지
        duty_cycle = SERVO_NEUTRAL_DUTY_CYCLE;
    }

    printf("Direction: %d, Speed: %d, Duty Cycle: %d\n", direction, speed, duty_cycle);
    update_pwm_duty_cycle(PWM1_CHANNEL_PATH, duty_cycle);
}
