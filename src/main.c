#include <stdio.h>
#include <unistd.h>
#include "socket.h"
#include "gpio.h"
#include "adc.h"
#include "pwm.h"
#include "param.h"
#include "device_init.h"


int main(int argc, char* argv[]) {

    if(argc > 2) {
        fprintf(stderr, "Wrong Server IP addresses\n");
        return -1;
    }

    // 서버 연결 설정
    int sock = setup_server_connection(argv[1]);
    if (sock < 0) {
        fprintf(stderr, "Failed to connect to server\n");
        return -1;
    }

    // 장치 초기화
    if (initialize_devices() < 0) {
        fprintf(stderr, "Device initialization failed. Exiting...\n");
        return -1;
    }

    int led_state = 0; // LED의 초기 상태 (LOW)

    // 주기적으로 데이터를 수집하고 구조체를 통해 출력
    while (1) {
        // LED 상태를 토글
        led_state = !led_state;
        set_gpio_value(LED_GPIO_PIN, led_state);

        // 데이터 수집
        DataPacket packet = collect_data(LED_GPIO_PIN, led_state);

        // 수집한 데이터를 출력
        print_data(&packet);

        // 서버에 데이터 전송
        if (send_data_with_reconnect(sock, &packet, argv[1]) < 0) {
            fprintf(stderr, "Reconnection failed. Exiting...\n");
            break;
        }

        usleep(1000000); // 1초 대기
    }

    close(sock); // 프로그램 종료 시 소켓 닫기
    return 0;
}