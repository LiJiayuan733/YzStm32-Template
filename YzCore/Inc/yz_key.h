//
// Created by 32827 on 2023/11/1.
//

#ifndef REYZ_YZ_KEY_H
#define REYZ_YZ_KEY_H
#include "stm32f1xx.h"
#include "yz_config.h"

#if YZKEY

#define KEY1_PIN GPIO_PIN_0
#define KEY2_PIN GPIO_PIN_13
#define KEY1_PIN_BASE GPIOA
#define KEY2_PIN_BASE GPIOC

#if  YZLED
#include "yz_led.h"
#endif

void yz_key_irq_handler(void);
#endif

void yz_key_init(void);
#endif //REYZ_YZ_KEY_H
