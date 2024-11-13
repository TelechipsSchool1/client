//*******************************************************
// 파일명 : param.h
// 작성자 : 문찬호
// 작성일 : 24.11.07
// 수정일 : 24.11.11 (jude kwon)
// 
// 파일설명 : 센서 제어를 위한 파라미터들을 정의
//			 ex) 센서 별 어떤 핀을 사용할 것인지 에 대한 설정
//*******************************************************


#define TRIG_PIN 83  // 초음파 TRIGER 사용할 핀
#define ECHO_PIN 84  // 초음파 ECHO 사용할 핀
#define SYSFS_GPIO_DIR "/sys/class/gpio/"
#define BUFFER_SIZE 128

// adc param
#define I2C_DEVICE "/dev/i2c-1"
#define ADC1_ADDRESS 0x48
#define ADC2_ADDRESS 0x49

// pwm param
#define PWM1_CHANNEL_PATH "/sys/class/pwm/pwmchip0/pwm0"
#define PWM2_CHANNEL_PATH "/sys/class/pwm/pwmchip0/pwm1"
#define PWM_PERIOD 1000000
#define PWM_MAX_DUTY_CYCLE PWM_PERIOD