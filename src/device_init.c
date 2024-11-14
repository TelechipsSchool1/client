#include <stdio.h>
#include "gpio.h"
#include "adc.h"
#include "pwm.h"
#include "param.h" // 핀 번호를 가져옴

int initialize_devices() {
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

    // 초음파 센서 핀 초기화
    if (export_gpio(TRIG_PIN) < 0 || set_gpio_direction(TRIG_PIN, "out") < 0) {
        fprintf(stderr, "Failed to initialize TRIG_PIN for ultrasonic sensor\n");
        return -1;
    }
    if (export_gpio(ECHO_PIN) < 0 || set_gpio_direction(ECHO_PIN, "in") < 0) {
        fprintf(stderr, "Failed to initialize ECHO_PIN for ultrasonic sensor\n");
        return -1;
    }

    return 0; // 성공
}
