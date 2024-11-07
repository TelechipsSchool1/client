//*********************//
// 파일명 : gpio.h
// 작성자 : 문찬호
// 작성일 : 24.10.31
//*********************//

#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void int_quit(int sig);
int export_gpio(int gpio);
int set_gpio_direction(int gpio, const char *direction);
int set_gpio_value(int gpio, int value);
int get_gpio_value(int gpio);

#endif // GPIO_H
