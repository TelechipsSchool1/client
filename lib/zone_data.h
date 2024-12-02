#ifndef ZONE_DATA_H
#define ZONE_DATA_H

#include <stdint.h>

// Zone 1,3 데이터 구조체 및 함수 선언
typedef struct {
    float ultrasonic_distance;  // 초음파 거리
    float temperature;          // 온도
    float humidity;             // 습도
    float pressure;             // 압력 센서  
    uint8_t door_status;        //  문 상태 
    uint8_t window_status;      // 창문 상태 (0: 닫힘, 1: 열림)
} Zone1_3_Data;

Zone1_3_Data collect_zone1_3_data();

// Zone 2 데이터 구조체 및 함수 선언
typedef struct {
    double heart_rate;          // 심박수
    float air_quality;          // 공기질
} Zone2_Data;

Zone2_Data collect_zone2_data();

#endif // ZONE_DATA_H
