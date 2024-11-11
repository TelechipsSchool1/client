//*******************************************
// 파일명 : data_collect.c
// 작성자 : jude.kwon
// 작성일 : 24.11.11
// 수정일 : -
// 파일설명 : 센서4가지 데이터 취합
//********************************************



#include "data_collect.h"
#include "adc.h"
#include "pwm.h"
#include "sonic.h"
#include "gpio.h"
#include "param.h"

DataPacket collect_data(int led_gpio_pin, int current_led_state) {
    DataPacket packet;
    
    // ADC 값 읽기
    packet.adc_value = get_filtered_adc_value(0);

    // ADC 값을 바탕으로 PWM Duty Cycle 계산 및 설정
    packet.pwm_duty_cycle = (packet.adc_value * PWM_MAX_DUTY_CYCLE) / 255;
    update_pwm_duty_cycle(PWM1_CHANNEL_PATH, packet.pwm_duty_cycle);

    // 초음파 거리 측정
    packet.distance = get_distance();

    // LED 상태 (현재 상태를 수집)
    packet.led_state = current_led_state;

    return packet;
}

