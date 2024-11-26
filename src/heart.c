//*******************************************
// 파일명 : heart.c
// 작성자 : jude.kwon
// 작성일 : 24.11.26
// 수정일 : -
//*******************************************


#include "heart.h"
#include "param.h"
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>

static int i2c_fd = -1;

// I2C 레지스터 쓰기
static int i2c_write_register(int reg, char value) {
    char buffer[2] = {reg, value};
    if (write(i2c_fd, buffer, 2) != 2) {
        perror("Failed to write to register");
        return -1;
    }
    return 0;
}

// I2C 레지스터 읽기
static int i2c_read_register(int reg, char *buffer, int length) {
    if (write(i2c_fd, &reg, 1) != 1) {
        perror("Failed to set register");
        return -1;
    }

    if (read(i2c_fd, buffer, length) != length) {
        perror("Failed to read from register");
        return -1;
    }

    return 0;
}

// MAX30102 초기화
int initialize_max30102() {
    i2c_fd = open(I2C_DEVICE, O_RDWR);
    if (i2c_fd < 0) {
        perror("Failed to open I2C device");
        return -1;
    }

    if (ioctl(i2c_fd, I2C_SLAVE, SENSOR_ADDRESS) < 0) {
        perror("Failed to set I2C address");
        close(i2c_fd);
        return -1;
    }

    // FIFO 포인터 초기화
    if (i2c_write_register(FIFO_WR_PTR, 0x00) < 0 ||
        i2c_write_register(FIFO_RD_PTR, 0x00) < 0 ||
        i2c_write_register(OVF_COUNTER, 0x00) < 0) {
        return -1;
    }

    // FIFO 설정
    if (i2c_write_register(FIFO_CONFIG, 0x4F) < 0) {
        return -1;
    }

    // SpO2 설정
    if (i2c_write_register(SPO2_CONFIG, 0x27) < 0) {
        return -1;
    }

    // LED 설정
    if (i2c_write_register(LED1_PA, 0x24) < 0 || i2c_write_register(LED2_PA, 0x24) < 0) {
        return -1;
    }

    // 인터럽트 설정
    if (i2c_write_register(INTERRUPT_ENABLE, 0xC0) < 0) {
        return -1;
    }

    printf("MAX30102 initialized successfully\n");
    return 0;
}

// 심박수 계산
double calculate_heart_rate() {
    char buffer[6];
    uint32_t ir_values[100];
    int sample_count = 0, peak_count = 0;

    while (sample_count < 100) {
        if (i2c_read_register(FIFO_DATA, buffer, 6) < 0) {
            return -1;
        }

        uint32_t ir_data = ((buffer[0] << 16) | (buffer[1] << 8) | buffer[2]) >> 6;
        ir_values[sample_count++] = ir_data;

        usleep(10000); // 10ms 대기
    }

    for (int i = 1; i < sample_count - 1; i++) {
        if (ir_values[i] > ir_values[i - 1] && ir_values[i] > ir_values[i + 1]) {
            peak_count++;
        }
    }

    return (peak_count / 10.0) * 60.0; // BPM 계산
}
