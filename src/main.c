// main.c

#include <stdio.h>
#include <unistd.h>
#include "data_collect.h"
#include "adc.h"
#include "pwm.h"
#include "sonic.h"
#include "gpio.h"
#include "param.h"

#define LED_GPIO_PIN 85 // LED 토글을 위한 GPIO 핀 번호


// 핀설정
//adc : i2c0 사용 중   (pin header 3, 5번 사용 )
//pwm : pwm0 사용중 (pin header 12번 사용)\
//초음파 센서 (pin header 7, 11 번 사용)
//led (pin header 13번 사용)








int main() {
    // ADC 초기화
    if (initialize_adc(I2C_DEVICE, ADC1_ADDRESS) < 0) {
        fprintf(stderr, "Failed to initialize ADC\n");
        return -1;
    }

    // PWM 초기화
    if (initialize_pwm(PWM1_CHANNEL_PATH) < 0) {
        fprintf(stderr, "Failed to initialize PWM\n");
        return -1;
    }

    // LED GPIO 핀 초기화
    if (export_gpio(LED_GPIO_PIN) < 0 || set_gpio_direction(LED_GPIO_PIN, "out") < 0) {
        fprintf(stderr, "Failed to initialize GPIO for LED\n");
        return -1;
    }

    int led_state = 0; // LED의 초기 상태 (LOW)

    // 주기적으로 데이터를 수집하고 구조체를 통해 출력
    while (1) {
        // LED 상태를 토글
        led_state = !led_state;
        set_gpio_value(LED_GPIO_PIN, led_state);

        // 데이터 수집
        DataPacket packet = collect_data(LED_GPIO_PIN, led_state);

        // 수집한 데이터 출력
        printf("ADC Value: %d\n", packet.adc_value);
        printf("PWM Duty Cycle: %d\n", packet.pwm_duty_cycle);
        
        if (packet.distance == -1) {
            printf("Distance: Ultrasonic sensor not detected or timeout occurred.\n");
        } else {
            printf("Distance: %ld cm\n", packet.distance);
        }

        printf("LED GPIO (PIN %d): %s\n", LED_GPIO_PIN, packet.led_state ? "HIGH" : "LOW");

        sleep(1); // 1초 간격으로 데이터 수집 및 출력
    }

    return 0;
}

