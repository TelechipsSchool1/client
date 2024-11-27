//*******************************************************
// 파일명 : vibrator.c
// 작성자 : jude kwon
// 작성일 : 24.11.26
// 
// 파일설명 : 진동 모터 제어를 위한 함수 구현
//*******************************************************

#include "vibrator.h"
#include "gpio.h"

// 진동 모터 초기화
int vibrator_init() {
    if (export_gpio(VIBRATOR_PIN) < 0) {
        return -1;
    }
    if (set_gpio_direction(VIBRATOR_PIN, "out") < 0) {
        return -1;
    }
    return 0;
}

// 진동 모터 켜기
int vibrator_on() {
    if (set_gpio_value(VIBRATOR_PIN, 1) < 0) {
        return -1;
    }
    return 0;
}

// 진동 모터 끄기
int vibrator_off() {
    if (set_gpio_value(VIBRATOR_PIN, 0) < 0) {
        return -1;
    }
    return 0;
}
