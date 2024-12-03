//*******************************************************
// 파일명 : pressure.h
// 작성자 : jude.kwon
// 작성일 : 24.12.02
// 수정일 : 없음
//
// 파일설명 : FSR406 압력 센서를 제어하기 위한 함수 선언
//*******************************************************

#ifndef PRESSURE_H
#define PRESSURE_H

#include <stdio.h>
#include <stdlib.h>
#include "adc.h"
#include "param.h"


// FSR406 함수 선언
int initialize_fsr406();
int read_fsr406_value();

#endif // PRESSURE_H