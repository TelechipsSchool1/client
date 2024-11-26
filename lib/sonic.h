//*******************************************************
// 파일명 : sonic.h
// 작성자 : 문찬호
// 작성일 : 24.11.07
// 수정일 : 24-11.07
// 
// 파일설명 : 초음파 센서 제어함수 해더파일
//*******************************************************

#ifndef SONIC_H
#define SONIC_H

#include <sys/time.h>
#include "gpio.h"

int sonic_init();
long get_distance(void);

#endif // SONIC_H
