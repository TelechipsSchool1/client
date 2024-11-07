//*********************//
// 파일명 : main.c
// 작성자 : 문찬호
// 작성일 : 24.10.31
//*********************//

#include "gpio.h"
#include "param.h"
#include "sonic.h"

int main() {

    printf("Starting SONIC sensor test. Press Ctrl+C to exit.\n");

    export_gpio(TRIG_PIN);
    export_gpio(ECHO_PIN);

    set_gpio_direction(TRIG_PIN, "out");
    set_gpio_direction(ECHO_PIN, "in");
    
    while (1) {
        long distance = get_distance();
        printf("Distance: %ld cm\n", distance);
        usleep(200000);
    }

    printf("Cleanup done. Exiting.\n");
    return 0;
}
