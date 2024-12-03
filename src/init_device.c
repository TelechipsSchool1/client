#include "init_device.h"
#include "servo.h"
#include "sonic.h"
#include "buzzer.h"
#include "vibrator.h"
#include "heart.h"
#include "air_quality.h"
#include "button.h" 
#include "pressure.h" 

int initialize_zone1_3() {
    // 서보모터 초기화
    if (servo_initialize() < 0) {
        fprintf(stderr, "Failed to initialize servo motor.\n");
        return -1;
    }

    //압력 센서
    if (initialize_fsr406() < 0) {
        fprintf(stderr, "Failed to initialize pressure sensor.\n");
        return -1;
    }

    // 초음파 센서 
    if (sonic_init() < 0) {
        fprintf(stderr, "Failed to initialize ultrasonic sensor.\n");
        return -1;
    }

    //부저 
    if (buzzer_init() < 0) {
        fprintf(stderr, "Failed to initialize buzzer.\n");
        return -1;
    }

    //진동 모터
    if (vibrator_init() < 0) {
        fprintf(stderr, "Failed to initialize vibrator motor.\n");
        return -1;
    }

    //버튼(창문 상태)
    if (button_init() < 0) {
        fprintf(stderr, "Failed to initialize button.\n");
        return -1;
    }

    printf("Zone 1, 3 initialized successfully.\n");
    return 0;
}

int initialize_zone2() {
    // 심박수 센서 초기화
    if (initialize_max30102() < 0) {
        fprintf(stderr, "Failed to initialize heart rate sensor.\n");
        return -1;
    }

    // 공기질 센서 초기화
    if (air_quality_init(I2C_DEVICE, ADC1_ADDRESS) < 0) {
        fprintf(stderr, "Failed to initialize air quality sensor.\n");
        return -1;
    }

    printf("Zone 2 initialized successfully.\n");
    return 0;
}
