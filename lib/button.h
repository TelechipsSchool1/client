#ifndef BUTTON_H
#define BUTTON_H

#include "gpio.h" // GPIO 관련 함수 포함

// 버튼 초기화 함수
int button_init();

// 버튼 상태를 감지하고 데이터를 토글하는 함수
int monitor_button_and_toggle_data(int *data);

#endif // BUTTON_H
