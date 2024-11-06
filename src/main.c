//*********************//
// 파일명 : main.c
// 작성자 : 문찬호
// 작성일 : 24.10.31
//*********************//

#include "gpio.h"

volatile sig_atomic_t quit = 0;  // 종료 플래그

// 종료 시그널 처리 함수
void int_quit(int sig) {
    quit = 1;
    set_gpio_value(TEST_PIN, 0);  // 프로그램 종료 시 핀 출력 0으로 설정
    printf("Exiting...\n");
}

int main() {
    struct sigaction sa;
    sa.sa_handler = int_quit;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    if (export_gpio(TEST_PIN) == -1) return -1;
    if (set_gpio_direction(TEST_PIN, "out") == -1) return -1;

    printf("Starting GPIO test. Press Ctrl+C to exit.\n");

    int state = 0;
    while (!quit) {
        set_gpio_value(TEST_PIN, state);
        state = !state;  // 상태 토글 (0 또는 1)
        sleep(1);  // 1초 대기
    }

    printf("Cleanup done. Exiting.\n");
    return 0;
}
