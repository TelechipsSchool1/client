#include "air_quality.h"

#define ADC_RESOLUTION 255.0 // 8비트 해상도
#define V_REF 3.3            // ADC 참조 전압

// 공기질 센서 초기화
int air_quality_init(const char *i2c_device, int i2c_address) {
    // ADC 초기화
    if (initialize_adc(i2c_device, i2c_address) < 0) {
        fprintf(stderr, "Failed to initialize ADC.\n");
        return -1;
    }

    //printf("Air Quality Sensor initialized successfully.\n");
    return 0;
}

// 공기질 데이터 읽기 (ADC 값 반환)
int air_quality_read() {
    int adc_value = read_adc(0); // ADC 채널 0 읽기
    if (adc_value < 0) {
        fprintf(stderr, "Failed to read ADC value.\n");
        return -1; // 실패 시 음수 반환
    }
    return adc_value;
}

