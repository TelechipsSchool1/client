#include <stdio.h>
#include <unistd.h>
#include "socket.h"
#include "data_collect.h"
#include "gpio.h"

#define LED_GPIO_PIN 85 // LED 토글을 위한 GPIO 핀 번호

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
        // LED 상태 변경 및 설정
        led_state = !led_state;
        set_gpio_value(LED_GPIO_PIN, led_state);

        // 데이터 수집
        DataPacket packet = collect_data(LED_GPIO_PIN, led_state);

        // 데이터 출력
        print_data(&packet, LED_GPIO_PIN);

        // 데이터 전송 및 재연결 로직
        sock = send_data_with_reconnect(sock, &packet);
        if (sock < 0) {
            fprintf(stderr, "Reconnection failed. Exiting...\n");
            break;
        }

        sleep(1); // 1초 간격으로 데이터 수집 및 전송
    }

    close(sock); // 프로그램 종료 시 소켓 닫기
    return 0;
}
