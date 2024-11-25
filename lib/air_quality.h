#ifndef AIR_QUALITY_H
#define AIR_QUALITY_H

#include <stdio.h>
#include <unistd.h>
#include "adc.h"

// 함수 선언
int air_quality_init(const char *i2c_device, int i2c_address);
int air_quality_read();

#endif // AIR_QUALITY_H

