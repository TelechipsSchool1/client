#ifndef ZONE_DATA_H
#define ZONE_DATA_H

#include <stdint.h>
#include "pressure.h"
#include "sonic.h"
#include "buzzer.h"
#include "button.h"

// Zone 1,3 데이터 구조체 및 함수 선언
typedef struct {
    int ID; //zone ID
    float ultrasonic_distance;  // 초음파 거리
    float temperature;          // 온도
    float humidity ;             // 습도
    int pressure ;             // 압력 센서  
    int door_status;        //  문 상태 
    int window_status;      // 창문 상태 (0: 닫힘, 1: 열림)
} Zone1_3_Data;

typedef struct {
    int window_command; // 창문 여닫기 여부
    int sleep_alert;
} Zone1_3_Receive_Data;

Zone1_3_Data collect_zone1_3_data();
Zone1_3_Receive_Data collect_zone1_3_receivce_data();
#endif // ZONE_DATA_H
