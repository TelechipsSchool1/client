#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "init_device.h"
#include "servo.h"
#include "zone_data.h"
#include "vibrator.h"

#define SERVER_PORT 12345
#define SERVER_IP "192.168.137.5"

// 글로벌 변수
Zone1_3_Data zone1_3_data = {0};
pthread_mutex_t data_mutex; // 센서 데이터 보호를 위한 뮤텍스

Zone1_3_Receive_Data receive_data = {0}; // 서버로부터 받은 창문 제어 명령
pthread_mutex_t command_mutex;           // 명령 보호를 위한 뮤텍스

// 센서 데이터 출력 함수
void print_sensor_data() {
    pthread_mutex_lock(&data_mutex);
    printf("\n======================================\n");
    printf("          Sensor Data Output          \n");
    printf("======================================\n");
    printf(" ID:                      %4d\n", zone1_3_data.ID);
    printf(" Ultrasonic Distance: %6.2f cm\n", zone1_3_data.ultrasonic_distance);
    printf(" Temperature:          %6.2f °C\n", zone1_3_data.temperature);
    printf(" Humidity:             %6.2f %%\n", zone1_3_data.humidity);
    printf(" Pressure:                %4d\n", zone1_3_data.pressure);
    printf(" Door Status:              %4d\n", zone1_3_data.door_status); // 버튼에 의해 토글됨
    printf(" Window Status:            %4d\n", zone1_3_data.window_status);
    printf("======================================\n");
    pthread_mutex_unlock(&data_mutex);
}

// 데이터 수집 스레드
void *sensor_data_task(void *arg) {
    int client_sock = *(int *)arg;
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    while (1) {
        pthread_mutex_lock(&data_mutex);
        // `collect_zone1_3_data` 함수 호출로 데이터를 수집(압력, 초음파, 부저, 버튼)
        perror("111");
        zone1_3_data = collect_zone1_3_data();

        pthread_mutex_unlock(&data_mutex);

        perror("222");

        // 서버로 데이터 전송
        if (send(client_sock, &zone1_3_data, sizeof(zone1_3_data), 0) < 0) {
            perror("Send failed, closing connection");
            break;
        }

        print_sensor_data();

        sleep(1); // 데이터 갱신 주기
    }
    return NULL;
}

// 데이터 수신 스레드 함수
void *command_receive_task(void *arg) {
    int client_sock = *(int *)arg; // 클라이언트 소켓 디스크립터
    Zone1_3_Receive_Data buffer;  // 수신 데이터를 저장할 구조체
    while (1) {
        if (recv(client_sock, &buffer, sizeof(buffer), 0) < 0) {
            perror("Recv failed, closing connection");
            break;
        }

        pthread_mutex_lock(&command_mutex);
        receive_data = buffer;
        pthread_mutex_unlock(&command_mutex);

        sleep(1); // 다음 데이터 수신까지 대기
    }
    return NULL;
}

// 창문 제어 스레드 함수
void *window_control_task(void *arg) {
    int previous_command = -1; // 이전 창문 명령 상태 (-1: 초기 상태)

    while (1) {
        pthread_mutex_lock(&command_mutex);
        int window_command = receive_data.window_command; // 현재 창문 명령
        pthread_mutex_unlock(&command_mutex);

        // 창문 상태 처리
        if (window_command != previous_command) {
            if (window_command == 1) {
                printf("[main.c] Received Command: OPENING Window\n");
                pthread_mutex_lock(&data_mutex);
                zone1_3_data.window_status = 1; // 창문 상태 갱신
                pthread_mutex_unlock(&data_mutex);

                servo_set_speed(1, 100);        // 시계 방향, 최대 속도로 회전
                sleep(2);                       // 2초 대기
                servo_set_speed(0, 0);          // 서보모터 정지
            } else if (window_command == 0) {
                printf("[main.c] Received Command: CLOSING Window\n");
                pthread_mutex_lock(&data_mutex);
                zone1_3_data.window_status = 0; // 창문 상태 갱신
                pthread_mutex_unlock(&data_mutex);

                servo_set_speed(-1, 100);       // 반시계 방향, 최대 속도로 회전
                sleep(2);                       // 2초 대기
                servo_set_speed(0, 0);          // 서보모터 정지
            }
            previous_command = window_command; // 현재 명령을 이전 명령으로 저장
        }

        sleep(1); // 다음 명령까지 대기
    }
    return NULL;
}

// 부저 및 진동모터 제어 스레드
void *alert_task(void *arg) {
    int previous_sleep_alert = -1; // 이전 sleep_alert 상태 (-1: 초기 상태)

    while (1) {

        // 초음파 센서 값이 56cm 이하이고 도어 상태가 1일 때 작동
        if (zone1_3_data.door_status == 1 && zone1_3_data.ultrasonic_distance > 0 && zone1_3_data.ultrasonic_distance <= 56) {
            printf("ALERT! Door is open, and distance below 50 cm.\n");

            buzzer_on();
            vibrator_on();
            usleep(500000); // 0.5초 대기

            buzzer_off();
            vibrator_off();
            usleep(500000); // 0.5초 대기
        }

        // 압력 센서 알림
        if (zone1_3_data.pressure >= 240) {
            printf("ALERT! Pressure value exceeds 240.\n");
            buzzer_on();
            vibrator_on();
            usleep(500000);
            buzzer_off();
            vibrator_off();
            usleep(500000);
        }


        // sleep_alert 상태 처리
        if (receive_data.sleep_alert == 1) {
            printf("[main.c] ALERT: Sleep Alert Received!\n");
            buzzer_on();
            vibrator_on();
            usleep(500000); // 0.5초 대기
            buzzer_off();
            vibrator_off();
            usleep(500000); // 0.5초 대기
        }

        usleep(100000); // 0.1초 대기
    }
    return NULL;
}

int main() {
    pthread_t sensor_thread, alert_thread, window_thread, command_thread;
    initialize_zone1_3();

    // 뮤텍스 초기화
    if (pthread_mutex_init(&data_mutex, NULL) != 0) {
        fprintf(stderr, "Failed to initialize mutex.\n");
        return -1;
    }

    if (pthread_mutex_init(&command_mutex, NULL) != 0) {
        fprintf(stderr, "Failed to initialize mutex.\n");
        return -1;
    }

    // 소켓 초기화 및 서버 연결
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    struct sockaddr_in client_addr, server_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(11111);
    client_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0) {
        perror("Client bind failed");
        close(sockfd);
        return -1;
    }
    printf("Client bound to port 11111\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed");
        close(sockfd);
        return -1;
    }

    printf("Connected to server\n");

    // 스레드 생성
    pthread_create(&sensor_thread, NULL, sensor_data_task, (void *)&sockfd);
    pthread_create(&alert_thread, NULL, alert_task, NULL);
    pthread_create(&window_thread, NULL, window_control_task, NULL);
    pthread_create(&command_thread, NULL, command_receive_task, (void *)&sockfd);

    // 메인 스레드 대기
    pthread_join(sensor_thread, NULL);
    pthread_join(alert_thread, NULL);
    pthread_join(window_thread, NULL);
    pthread_join(command_thread, NULL);

    // 뮤텍스 제거
    pthread_mutex_destroy(&data_mutex);
    pthread_mutex_destroy(&command_mutex);

    return 0;
}