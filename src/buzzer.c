//*******************************************************
// 파일명 : buzzer.c
// 작성자 : jude kwon
// 작성일 : 24.11.26
// 
// 파일설명 : 부저 제어를 위한 함수 구현
//*******************************************************

#include "buzzer.h"
#include "gpio.h"

// 부저 초기화
int buzzer_init() {
    if (export_gpio(BUZZER_PIN) < 0) {
        return -1;
    }
    if (set_gpio_direction(BUZZER_PIN, "out") < 0) {
        return -1;
    }
    return 0;
}

// 부저 켜기
int buzzer_on() {
    if (set_gpio_value(BUZZER_PIN, 1) < 0) {
        return -1;
    }
    return 0;
}

// 부저 끄기
int buzzer_off() {
    if (set_gpio_value(BUZZER_PIN, 0) < 0) {
        return -1;
    }
    return 0;
}
