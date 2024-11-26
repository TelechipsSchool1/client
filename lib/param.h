//*******************************************************
// 파일명 : param.h
// 작성자 : 문찬호
// 작성일 : 24.11.07
// 수정일 : 24.11.21 (jude kwon)
// 
// 파일설명 : 센서 제어를 위한 파라미터들을 정의
//			 ex) 센서 별 어떤 핀을 사용할 것인지 에 대한 설정
//*******************************************************

#ifndef PARAM_H
#define PARAM_H

// GPIO 설정
#define TRIG_PIN 83  // 초음파 TRIGER 사용할 핀
#define ECHO_PIN 84  // 초음파 ECHO 사용할 핀
#define SYSFS_GPIO_DIR "/sys/class/gpio/"
#define BUFFER_SIZE 128
#define LED_GPIO_PIN 85 // LED 토글을 위한 GPIO 핀 번호

// ADC 설정
#define I2C_DEVICE "/dev/i2c-1"
#define ADC1_ADDRESS 0x48
#define ADC2_ADDRESS 0x49

// PWM 설정
#define PWM1_CHANNEL_PATH "/sys/class/pwm/pwmchip0/pwm0"
#define PWM_PERIOD 20000000 // 20ms (50Hz 주기)
#define PWM_MAX_DUTY_CYCLE 2000000 // 2ms (SG90-HV의 최대 듀티 사이클)

// 서보모터 값 
#define SERVO_NEUTRAL_DUTY_CYCLE 1200000 // 중립값 (정지 상태)
#define SERVO_MAX_DUTY_CYCLE 1600000    // 최대 시계 방향 속도
#define SERVO_MIN_DUTY_CYCLE 800000    // 최대 반시계 방향 속도

// 심박수 센서 설정
#define SENSOR_ADDRESS 0x57     // MAX30102 I2C 주소
#define FIFO_CONFIG       0x08 // FIFO 설정
#define FIFO_WR_PTR       0x04 // FIFO Write Pointer
#define FIFO_RD_PTR       0x06 // FIFO Read Pointer
#define OVF_COUNTER       0x05 // FIFO Overflow Counter
#define INTERRUPT_ENABLE  0x02 // 인터럽트 설정
#define SPO2_CONFIG       0x0A // SpO2 설정
#define LED1_PA           0x0C // Red LED Pulse Amplitude
#define LED2_PA           0x0D // IR LED Pulse Amplitude
#define INTERRUPT_STATUS  0x00 // 인터럽트 상태 레지스터
#define FIFO_DATA         0x07 // FIFO 데이터 레지스터

#endif // PARAM_H
