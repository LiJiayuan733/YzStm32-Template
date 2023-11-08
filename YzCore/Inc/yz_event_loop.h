//
// Created by 32827 on 2023/11/5.
//

#ifndef REYZ_YZ_EVENT_LOOP_H
#define REYZ_YZ_EVENT_LOOP_H
#include "stm32f1xx.h"
#include "yz_config.h"

#define YZ_LOOP_EVENT_SIZE 32
#define YZ_LOOP_POINTER_SIZE 64

void yz_loop_act();
void yz_loop_init();
///@return 表索引
uint8_t yz_loop_add_event_handle(HAL_StatusTypeDef (*p)(uint32_t pointer1));
///@return 表索引
uint8_t yz_loop_add_pointer(uint32_t pointer1);
uint32_t yz_loop_get_pointer(uint8_t index);
#endif //REYZ_YZ_EVENT_LOOP_H
