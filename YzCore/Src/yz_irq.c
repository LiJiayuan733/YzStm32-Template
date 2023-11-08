//
// Created by 32827 on 2023/11/1.
//
#include "yz_irq.h"

void EXTI2_IRQHandler(){
    #if YZKEY
    yz_key_irq_handler();
    #endif
}
void EXTI15_10_IRQHandler(){
    #if YZKEY
    yz_key_irq_handler();
    #endif
}

///------------- YZ »ù´¡ÖÐ¶Ï ---------------
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    YZ_RECV_HAL_UART_RxCpltCallback(huart);
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
    YZ_RECV_HAL_UART_TxCpltCallback(huart);
}
///---------------------------------------
