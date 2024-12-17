//*******************************************
// 파일명 : adc.c
// 작성자 : jude.kwon 
// 작성일 : 24.10.31
// 수정일 : 24.12.02
// 
// 파일설명 : ADC 제어 기능을 위한 함수들을 정의
//********************************************

#include "adc.h"

static int i2c_fd = -1;
//초기화 진행 
int initialize_adc(const char *i2c_device, int i2c_address) {
    i2c_fd = open(i2c_device, O_RDWR);
    if (i2c_fd < 0) {
        perror("Failed to open I2C device");
        return -1;
    }

    if (ioctl(i2c_fd, I2C_SLAVE, i2c_address) < 0) {
        perror("Failed to acquire bus access or talk to slave");
        close(i2c_fd);
        return -1;
    }

    return 0;
}

//adc 데이터값 수신
int read_adc(int channel) {
    if (i2c_fd < 0) {
        fprintf(stderr, "ADC not initialized\n");
        return -1;
    }

    char config = 0x40+channel;
    if (write(i2c_fd, &config, 1) != 1) {
        perror("ADC write failed");
        return -1;
    }

    char data;
    if (read(i2c_fd, &data, 1) != 1) {
        perror("PCF8591 read failed");
        return -1;
    }

    return data;
}
