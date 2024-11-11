//*********************//
// 파일명 : adc.h
// 작성자 : jude.kwon
// 작성일 : 24.11.07
// edit date : 24.11.11
//*********************//


#ifndef ADC_H
#define ADC_H

#include <stdio.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include "param.h"  // param.h에서 I2C와 ADC 설정 사용

// ADC 함수
int initialize_adc(const char *i2c_device, int i2c_address);
int get_filtered_adc_value(int channel);

#endif // ADC_H
