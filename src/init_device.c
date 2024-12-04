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

    //버튼(문 상태)
    if (button_init() < 0) {
        fprintf(stderr, "Failed to initialize button.\n");
        return -1;
    }

    printf("Zone 1, 3 initialized successfully.\n");
    return 0;
}

