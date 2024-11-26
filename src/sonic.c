//*******************************************************
// 파일명 : sonic.c
// 작성자 : 문찬호
// 작성일 : 24.11.07
// 수정일 : -
// 
// 파일설명 : 초음파 함수를 정의
//*******************************************************

#include "sonic.h"
#include "param.h"
#include "gpio.h"
#include <stddef.h>

int sonic_init() {
    if (export_gpio(TRIG_PIN) < 0 || set_gpio_direction(TRIG_PIN, "out") < 0) {
        fprintf(stderr, "Failed to initialize TRIG_PIN for ultrasonic sensor\n");
        return -1;
    }
    if (export_gpio(ECHO_PIN) < 0 || set_gpio_direction(ECHO_PIN, "in") < 0) {
        fprintf(stderr, "Failed to initialize ECHO_PIN for ultrasonic sensor\n");
        return -1;
    }
    return 0;
}

long get_distance(void) {
    struct timeval start, end;
    long duration;

    set_gpio_value(TRIG_PIN, 0);
    usleep(2);
    set_gpio_value(TRIG_PIN, 1);
    usleep(10);
    set_gpio_value(TRIG_PIN, 0);

    while (get_gpio_value(ECHO_PIN) == 0);
    gettimeofday(&start, NULL);

    while (get_gpio_value(ECHO_PIN) == 1);
    gettimeofday(&end, NULL);

    duration = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    return duration / 58;  // cm 단위 거리 반환
}