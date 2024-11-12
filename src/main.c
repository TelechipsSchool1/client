#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


#include "data_collect.h"
#include "adc.h"
#include "pwm.h"
#include "sonic.h"
#include "gpio.h"
#include "param.h"


#define LED_GPIO_PIN 85 // LED 토글을 위한 GPIO 핀 번호
#define SERVER_IP "192.168.0.245"  // 서버의 IP 주소 10.42.0.4
#define SERVER_PORT 12345          // 서버의 포트 번호


<<<<<<< HEAD
// 핀설정
//adc : i2c0 사용 중   (pin header 3, 5번 사용 )
//pwm : pwm0 사용중 (pin header 12번 사용)\
//초음파 센서 (pin header 7, 11 번 사용)
//led (pin header 13번 사용)


=======
int setup_server_connection();
int send_data_to_server(int sock, DataPacket *packet);
>>>>>>> a3a6eeea6c2c57d12476010570c034613fc312fe

int main() {
    // 서버 연결 설정
    int sock = setup_server_connection();
    if (sock < 0) {
        fprintf(stderr, "Failed to connect to server\n");
        return -1;
    }

    printf("hello\n");
    int led_state = 0;

<<<<<<< HEAD
    // LED GPIO 핀 초기화
    if (export_gpio(LED_GPIO_PIN) < 0 || set_gpio_direction(LED_GPIO_PIN, "out") < 0) {
        fprintf(stderr, "Failed to initialize GPIO for LED\n");
        return -1;
    }


    // 초음파 센서 핀 초기화
    if (export_gpio(TRIG_PIN) < 0 || set_gpio_direction(TRIG_PIN, "out") < 0) {
        fprintf(stderr, "Failed to initialize TRIG_PIN for ultrasonic sensor\n");
        return -1;
    }
    
    if (export_gpio(ECHO_PIN) < 0 || set_gpio_direction(ECHO_PIN, "in") < 0) {
        fprintf(stderr, "Failed to initialize ECHO_PIN for ultrasonic sensor\n");
        return -1;
    }
    
    int led_state = 0; // LED의 초기 상태 (LOW)

    // 주기적으로 데이터를 수집하고 구조체를 통해 출력
=======
>>>>>>> a3a6eeea6c2c57d12476010570c034613fc312fe
    while (1) {
        led_state = !led_state;
        set_gpio_value(LED_GPIO_PIN, led_state);

        DataPacket packet = collect_data(LED_GPIO_PIN, led_state);

<<<<<<< HEAD
        // 수집한 데이터를 같은 줄에 출력 (캐리지 리턴 사용)
        printf("\rADC Value: %d | PWM Duty Cycle: %d | Distance: %ld cm | LED GPIO (PIN %d): %s",
               packet.adc_value, 
               packet.pwm_duty_cycle, 
               packet.distance == -1 ? 0 : packet.distance,
               LED_GPIO_PIN, 
               packet.led_state ? "HIGH" : "LOW");
=======
        // 수집한 데이터 출력
        printf("ADC Value: %d\n", packet.adc_value);
        printf("PWM Duty Cycle: %d\n", packet.pwm_duty_cycle);

        if (packet.distance == -1) {
            printf("Distance: Ultrasonic sensor not detected or timeout occurred.\n");
        } else {
            printf("Distance: %ld cm\n", packet.distance);
        }
>>>>>>> a3a6eeea6c2c57d12476010570c034613fc312fe

        fflush(stdout); // 출력 버퍼를 강제로 비워 화면에 즉시 표시

<<<<<<< HEAD
        usleep(100000); 
=======
        // 서버에 데이터 전송
        if (send_data_to_server(sock, &packet) < 0) {
            fprintf(stderr, "Connection lost. Reconnecting...\n");
            close(sock);
            sock = setup_server_connection();  // 재연결 시도
            if (sock < 0) {
                fprintf(stderr, "Reconnection failed. Exiting...\n");
                break;
            }
        }

        sleep(1); // 1초 간격으로 데이터 수집 및 전송
>>>>>>> a3a6eeea6c2c57d12476010570c034613fc312fe
    }

    close(sock); // 프로그램 종료 시 소켓 닫기
    return 0;
}
// 서버에 대한 소켓 연결을 설정하는 함수
int setup_server_connection() {
    int sock;
    struct sockaddr_in server_addr;

    // 소켓 생성
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    // IP 주소 변환 및 설정
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sock);
        return -1;
    }

    // 서버에 연결
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed");
        close(sock);
        return -1;
    }

    printf("Connected to server\n");
    return sock;
}

// 데이터 패킷을 서버에 전송하는 함수
int send_data_to_server(int sock, DataPacket *packet) {
    if (send(sock, packet, sizeof(DataPacket), 0) < 0) {
        perror("Failed to send data");
        return -1;
    }
    printf("Data sent to server\n");
    return 0;
}
