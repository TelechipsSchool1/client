//*******************************************
// 파일명 : button.c
// 작성자 : jude.kwon 
// 작성일 : 24.11.02
// 수정일 : 24.12.02
// 
// 파일설명 : 버튼  제어 기능을 위한 함수들을 구현 
//********************************************


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
int monitor_button_and_toggle_data() {
    static int previous_state = -1;
    static int toggle_state = 0;
    int current_state = get_gpio_value(DOOR_STATUS_PIN);

    if (current_state != previous_state) {
        previous_state = current_state;
        if (current_state == 1) {
            toggle_state = !toggle_state; // 토글 상태 변경
            printf("Button pressed! Toggle state: %d\n", toggle_state);
        }
    }

    return toggle_state;
}

