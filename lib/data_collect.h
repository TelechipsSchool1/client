//*******************************************
// 파일명 : data_collect.h
// 작성자 : jude.kwon
// 작성일 : 24.11.11
// 수정일 : -
// 파일설명 : 센서4가지 데이터 취합struct
//********************************************




#ifndef DATA_COLLECT_H
#define DATA_COLLECT_H

typedef struct {
    int adc_value;          // ADC 값
    int pwm_duty_cycle;     // PWM Duty Cycle 값
    long distance;          // 초음파 거리 측정 값
    int led_state;          // LED GPIO 상태
} DataPacket;

DataPacket collect_data(int led_gpio_pin, int current_led_state);

#endif // DATA_COLLECT_H

