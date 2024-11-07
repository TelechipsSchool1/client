//*******************************************
// 파일명 : adc.c
// 작성자 : jude.kwon 
// 작성일 : 24.10.31
// 수정일 : 24.11.07
// 
// 파일설명 : ADC 제어 기능을 위한 함수들을 정의
//********************************************


#include "adc.h"

static int i2c_fd = -1;
static int filter[FILTER_SIZE] = {0};
static int filter_index = 0;
static int sum = 0;

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

static int read_adc(int channel) {
    if (channel < 0 || channel > 3) return -1;

    char config[1] = {channel};  
    if (write(i2c_fd, config, 1) != 1) return -1;

    char data[2] = {0};
    int retries = 0;
    while (retries < MAX_RETRIES) {
        if (read(i2c_fd, data, 2) == 2) {
            int adc_value = data[0];
            return adc_value;
        }
        retries++;
        usleep(1000);
    }
    return -1;
}

static int get_average_adc_value(int channel) {
    int sum = 0, value;
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        value = read_adc(channel);
        if (value >= 0) {
            sum += value;
        } else {
            return -1;
        }
        usleep(1000);
    }
    return sum / SAMPLE_COUNT;
}

int get_filtered_adc_value(int channel) {
    int adc_value = get_average_adc_value(channel);
    if (adc_value < 0) {
        return -1;
    }

    sum -= filter[filter_index];
    filter[filter_index] = adc_value;
    sum += adc_value;
    filter_index = (filter_index + 1) % FILTER_SIZE;

    return sum / FILTER_SIZE;
}

