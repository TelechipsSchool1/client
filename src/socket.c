//*******************************************************
// 파일명 : socket.c
// 작성자 : 조경훈
// 작성일 : 24.11.13
// 수정일 : 24.11.13
//
// 파일설명 : 소켓 데이터 전송을 위한 함수
//           
//*******************************************************

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "socket.h"

#define SERVER_IP "192.168.137.4"  // 서버의 IP 주소
#define SERVER_PORT 12345          // 서버의 포트 번호

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

// 데이터 전송 및 재연결 로직 함수
int send_data_with_reconnect(int sock, DataPacket *packet) {
    if (send_data_to_server(sock, packet) < 0) {
        fprintf(stderr, "Connection lost. Reconnecting...\n");
        close(sock);
        sock = setup_server_connection(); // 재연결 시도
        if (sock < 0) {
            fprintf(stderr, "Reconnection failed.\n");
            return -1;
        }
    }
    return sock; // 성공적으로 연결 유지
}

// 데이터 출력 함수
void print_data(const DataPacket *packet, int gpio_pin) {
    printf("ADC Value: %d\n", packet->adc_value);
    printf("PWM Duty Cycle: %d\n", packet->pwm_duty_cycle);

    if (packet->distance == -1) {
        printf("Distance: Ultrasonic sensor not detected or timeout occurred.\n");
    } else {
        printf("Distance: %ld cm\n", packet->distance);
    }

    printf("LED GPIO (PIN %d): %s\n", gpio_pin, packet->led_state ? "HIGH" : "LOW");
}
