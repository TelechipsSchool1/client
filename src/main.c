//*********************//
// 파일명 : main.c
// 작성자 : jude.kwon
// 작성일 : 24.11.07
//*********************//



#include <stdio.h>
#include <unistd.h>
#include "adc.h"
#include "pwm.h"
#include "gpio.h"

int main() {
    // ADC 초기화
    if (initialize_adc(I2C_DEVICE, ADC1_ADDRESS) < 0) {
        printf("Failed to initialize ADC\n");
        return 1;
    }

    // PWM 초기화
    if (initialize_pwm(PWM1_CHANNEL_PATH) < 0) {
        printf("Failed to initialize PWM\n");
        return 1;
    }

    // GPIO 초기화 및 방향 설정
    if (export_gpio(TEST_PIN) < 0) {
        printf("Failed to export GPIO pin\n");
        return 1;
    }
    if (set_gpio_direction(TEST_PIN, "out") < 0) {
        printf("Failed to set GPIO direction\n");
        return 1;
    }

    while (1) {
        // ADC 채널의 필터링된 값 가져오기
        int adc_value = get_filtered_adc_value(0);
        if (adc_value < 0) {
            printf("Failed to read from ADC\n");
            continue;
        }

        // PWM 듀티 사이클 설정
        int duty_cycle = (adc_value * PWM_MAX_DUTY_CYCLE) / 255;
        update_pwm_duty_cycle(PWM1_CHANNEL_PATH, duty_cycle);

        // GPIO 핀 값 토글
        static int gpio_value = 0;
        if (set_gpio_value(TEST_PIN, gpio_value) < 0) {
            printf("Failed to set GPIO value\n");
        }
        gpio_value = !gpio_value;

        // 출력 정보 표시
        printf("ADC Value: %d, Duty Cycle: %d\n", adc_value, duty_cycle);
        printf("GPIO Pin %d is set to %d\n", TEST_PIN, gpio_value);
        
        // 출력 버퍼 즉시 플러시
        fflush(stdout);

	// 100ms 대기
	usleep(100000);
    }

    return 0;
}

