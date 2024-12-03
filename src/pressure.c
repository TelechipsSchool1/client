//*******************************************************
// 파일명 : pressure.c
// 작성자 : jude.kwon
// 작성일 : 24.11.11
// 수정일 : 없음
//
// 파일설명 : FSR406 압력 센서를 제어하기 위한 함수 정의
//*******************************************************

#include "pressure.h"

int initialize_fsr406() {
    // ADC 초기화
    if (initialize_adc(I2C_DEVICE, ADC1_ADDRESS) < 0) {
        fprintf(stderr, "Failed to initialize ADC for FSR406\n");
        return -1;
    }
    printf("FSR406 initialized successfully\n");
    return 0;
}

int read_fsr406_value() {
    int value = read_adc(FSR406_ADC_CHANNEL);
    if (value < 0) {
        fprintf(stderr, "Failed to read FSR406 value\n");
        return -1;
    }

    printf("FSR406 raw value: %d\n", value);
    return value;
}