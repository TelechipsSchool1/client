#include "zone_data.h"


// Zone 1,3 데이터 수집 함수 정의
Zone1_3_Data collect_zone1_3_data() {
    Zone1_3_Data data;

    data.ID =1;

    // 초음파 센서 거리 측정
    data.ultrasonic_distance = get_distance();

    // 온도와 습도
    data.temperature = 22.5; // 온습도 센서 연동 시 수정
    data.humidity = 55.2;    // 온습도 센서 연동 시 수정

    // 압력 센서 데이터
    data.pressure = read_fsr406_value();

    // 도어 상태
    data.door_status = monitor_button_and_toggle_data();

    // 창문 상태 (임시 값, GPIO 또는 다른 입력값으로 대체 가능)
    data.window_status = 0; // 초기값: 닫힘

    return data;
}

// Zone 1,3 데이터 수집 함수 정의
Zone1_3_Receive_Data collect_zone1_3_receive_data() {
    Zone1_3_Receive_Data receive_data;

    receive_data.window_command ; // 1: 열림 명령, 0: 닫힘 명령 
    receive_data.sleep_alert;

    return receive_data;
}