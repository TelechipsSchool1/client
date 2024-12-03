#include "zone_data.h"
#include "sonic.h"
#include "heart.h"
#include "air_quality.h"

// Zone 1,3 데이터 수집 함수 정의
Zone1_3_Data collect_zone1_3_data() {
    Zone1_3_Data data;

    // 초음파 센서 거리 측정
    data.ultrasonic_distance = get_distance();

    // 온도와 습도는 추후 작성될 코드로 대체 예정
    data.temperature = 0.0f; // 임시 값
    data.humidity = 0.0f;    // 임시 값

    // 창문 상태 확인 (임시 값, GPIO 또는 다른 입력값으로 대체 가능)
    data.window_status = 1; // 1: 열림, 0: 닫힘

    return data;
}

// Zone 1,3 데이터 수집 함수 정의
Zone1_3_Receive_Data collect_zone1_3_receive_data() {
    Zone1_3_Receive_Data receive_data;

    receive_data.window_command = 1; // 1: 열림 명령, 0: 닫힘 명령 

    return receive_data;
}