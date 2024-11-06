//*********************//
// 파일명 : gpio_test.c
// 작성자 : 문찬호
// 작성일 : 24.10.31
//*********************//

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define SYSFS_GPIO_DIR "/sys/class/gpio/"
#define BUFFER_SIZE 128

// 핀 정의
#define TEST_PIN 84  // 테스트용 GPIO 핀 (예: GPIO 84)

// 전역 변수
volatile sig_atomic_t quit = 0;  // 종료 플래그

// 함수 선언
void int_quit(int sig);
int export_gpio(int gpio);
int set_gpio_direction(int gpio, const char *direction);
int set_gpio_value(int gpio, int value);

// 종료 시그널 처리 함수
void int_quit(int sig) {
    quit = 1;
    set_gpio_value(TEST_PIN, 0);  // 프로그램 종료 시 핀 출력 0으로 설정
    printf("Exiting...\n");
}

// GPIO 핀 export 함수
int export_gpio(int gpio) {
    char path[BUFFER_SIZE];
    snprintf(path, BUFFER_SIZE, SYSFS_GPIO_DIR "export");
    FILE *file = fopen(path, "w");
    if (!file) {
        perror("Failed to open GPIO export");
        return -1;
    }
    fprintf(file, "%d", gpio);
    fclose(file);
    return 0;
}

// GPIO 방향 설정 함수
int set_gpio_direction(int gpio, const char *direction) {
    char path[BUFFER_SIZE];
    snprintf(path, BUFFER_SIZE, SYSFS_GPIO_DIR "gpio%d/direction", gpio);
    FILE *file = fopen(path, "w");
    if (!file) {
        perror("Failed to set GPIO direction");
        return -1;
    }
    fprintf(file, "%s", direction);
    fclose(file);
    return 0;
}

// GPIO 값 설정 함수
int set_gpio_value(int gpio, int value) {
    char path[BUFFER_SIZE];
    snprintf(path, BUFFER_SIZE, SYSFS_GPIO_DIR "gpio%d/value", gpio);
    FILE *file = fopen(path, "w");
    if (!file) {
        perror("Failed to write GPIO value");
        return -1;
    }
    fprintf(file, "%d", value);
    fclose(file);
    return 0;
}

// 메인 함수
int main() {
    struct sigaction sa;
    sa.sa_handler = int_quit;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    // GPIO 설정
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
