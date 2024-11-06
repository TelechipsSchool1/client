//*******************************************
// 파일명 : gpio.c
// 작성자 : 문찬호
// 작성일 : 24.10.31
// 수정일 : 24.11.06
// 
// 파일설명 : GPIO 제어 기능을 위한 함수들을 정의
//********************************************

#include "gpio.h"

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
