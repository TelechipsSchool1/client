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


int setup_server_connection();
int send_data_to_server(int sock, DataPacket *packet);

int main() {
    // 서버 연결 설정
    int sock = setup_server_connection();
    if (sock < 0) {
        fprintf(stderr, "Failed to connect to server\n");
        return -1;
    }

    printf("hello\n");
    int led_state = 0;

    while (1) {
        led_state = !led_state;
        set_gpio_value(LED_GPIO_PIN, led_state);

        DataPacket packet = collect_data(LED_GPIO_PIN, led_state);

        // 수집한 데이터 출력
        printf("ADC Value: %d\n", packet.adc_value);
        printf("PWM Duty Cycle: %d\n", packet.pwm_duty_cycle);

        if (packet.distance == -1) {
            printf("Distance: Ultrasonic sensor not detected or timeout occurred.\n");
        } else {
            printf("Distance: %ld cm\n", packet.distance);
        }

        printf("LED GPIO (PIN %d): %s\n", LED_GPIO_PIN, packet.led_state ? "HIGH" : "LOW");

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
