#ifndef ADC_LIB_H
#define ADC_LIB_H

// I2C 장치 및 ADC 주소 설정
#define I2C_DEVICE "/dev/i2c-1"
#define ADC1_ADDRESS 0x48
#define ADC2_ADDRESS 0x49

// ADC 설정
#define MAX_RETRIES 3
#define SAMPLE_COUNT 5
#define FILTER_SIZE 30

// ADC 함수
int initialize_adc(const char *i2c_device, int i2c_address);
int get_filtered_adc_value(int channel);

#endif

