//
// Created by 32827 on 2023/10/31.
//

#ifndef REYZ_YZ_LED_H
#define REYZ_YZ_LED_H
#include "stm32f1xx.h"
#include "yz_config.h"

#if YZLED
#define RED_LED_PIN GPIO_PIN_5
#define GREEN_LED_PIN GPIO_PIN_0
#define BLUE_LED_PIN GPIO_PIN_1
#define LED_PIN_BASE GPIOB
void yz_led_green(void);
void yz_led_red(void);
void yz_led_blue(void);
#endif

void yz_led_init(void);
#endif //REYZ_YZ_LED_H
