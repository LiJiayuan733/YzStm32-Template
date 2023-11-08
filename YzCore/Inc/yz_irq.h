//
// Created by 32827 on 2023/11/1.
//

#ifndef REYZ_YZ_IRQ_H
#define REYZ_YZ_IRQ_H
#include "yz_config.h"
#include "yz_recv.h"
#include "stdio.h"

#if YZKEY
#include "yz_key.h"
#endif

void EXTI2_IRQHandler();
void EXTI15_10_IRQHandler();

///------------- YZ 基础中断 ---------------
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
///---------------------------------------

#endif //REYZ_YZ_IRQ_H
