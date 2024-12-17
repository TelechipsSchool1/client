//*******************************************************
// 파일명 : param.h
// 작성자 : 문찬호
// 작성일 : 24.11.07
// 수정일 : 24.11.26 (jude kwon)
// 
// 파일설명 : 센서 제어를 위한 파라미터들을 정의
//			 ex) 센서 별 어떤 핀을 사용할 것인지 에 대한 설정
//*******************************************************

#ifndef PARAM_H
#define PARAM_H

// GPIO 설정
#define SYSFS_GPIO_DIR "/sys/class/gpio/"
#define TRIG_PIN 83  // 초음파 TRIGER 사용할 핀
#define ECHO_PIN 84  // 초음파 ECHO 사용할 핀
#define VIBRATOR_PIN 112 // 진동 모터 사용 핀
#define BUZZER_PIN 117 // 부저 사용 핀
#define DOOR_STATUS_PIN 113 // 도어상태 핀 
#define DRIVING_PIN 85 // 운전상태 
#define BUFFER_SIZE 128

// ADC 설정
#define I2C_DEVICE "/dev/i2c-1"
#define ADC1_ADDRESS 0x48  //zone 1, 3 : 압력센서 , zone 2 : 공기질 센서 
#define PCF8591_AIN1 0x41
#define ADC2_ADDRESS 0x49

// PWM 설정
#define PWM1_CHANNEL_PATH "/sys/class/pwm/pwmchip0/pwm0"
#define PWM_PERIOD 20000000 // 20ms (50Hz 주기)
#define PWM_MAX_DUTY_CYCLE 2000000 // 2ms (SG90-HV의 최대 듀티 사이클)

// 서보모터 값 
#define SERVO_NEUTRAL_DUTY_CYCLE 1200000 // 중립값 (정지 상태)
#define SERVO_MAX_DUTY_CYCLE 1600000    // 최대 시계 방향 속도
#define SERVO_MIN_DUTY_CYCLE 800000    // 최대 반시계 방향 속도


//압력센서 
#define FSR406_ADC_CHANNEL 0 // FSR406이 연결된 ADC 채널

#endif // PARAM_H
