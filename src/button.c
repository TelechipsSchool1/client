#include <stdio.h>
#include "button.h"
#include "param.h"

// 버튼 초기화 함수
int button_init() {
    // 버튼 GPIO 핀 export 및 방향 설정
    if (export_gpio(DOOR_STATUS_PIN) < 0) {
        fprintf(stderr, "Failed to export GPIO for button.\n");
        return -1;
    }
    if (set_gpio_direction(DOOR_STATUS_PIN, "in") < 0) {
        fprintf(stderr, "Failed to set GPIO direction for button.\n");
        return -1;
    }
    return 0;
}

// 버튼 상태를 감지하고 데이터를 토글하는 함수
int monitor_button_and_toggle_data(int *data) {
    static int previous_state = -1; // 버튼의 이전 상태 저장
    int current_state;

    // 버튼 상태 읽기
    current_state = get_gpio_value(DOOR_STATUS_PIN);

    // 버튼 상태가 변경되었을 때만 처리
    if (current_state != previous_state) {
        previous_state = current_state;

        // 버튼이 눌렸을 때(1)
        if (current_state == 1) {
            *data = !(*data); // 데이터 값을 토글
            printf("Button pressed! Data toggled to: %d\n", *data);
        }
    }

    return 0;
}