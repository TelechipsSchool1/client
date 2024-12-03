#ifndef BUTTON_H
#define BUTTON_H

#include "gpio.h" // GPIO 관련 함수 포함

// 버튼 초기화 함수
int button_init();

// 버튼 상태를 감지하고 토글된 상태를 반환하는 함수
int monitor_button_and_toggle_data();

#endif // BUTTON_H

