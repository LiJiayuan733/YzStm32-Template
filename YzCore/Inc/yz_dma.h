//
// Created by 32827 on 2023/11/4.
//

#ifndef REYZ_YZ_DMA_H
#define REYZ_YZ_DMA_H
#include "stm32f1xx.h"
#include "yz_config.h"

#if YZLED
#include "yz_led.h"
#endif

#if YZDMA
///@deprecated 无需使用
void yz_dma_m2m_init(void);

///@param aSRC_Const_Buffer uint32_t *源地址
///@param aDST_Buffer uint32_t *目的地址
///@param BUFFER_SIZE uint32_t 数据长度
void yz_dma_m2m_start(uint32_t aSRC_Const_Buffer,uint32_t aDST_Buffer,uint32_t BUFFER_SIZE);

#define yz_m2p_uart_channel DMA1_Channel4
///@param uartHandle  UART_HandleTypeDef * 串口句柄
///@deprecated 无需调用
void yz_dma_m2p_uart_init(UART_HandleTypeDef *uartHandle);

///@param SendBuff uint8_t * 数据指针
///@param SENDBUFF_SIZE uint32_t 数据长度
///@return 是否发送成功
HAL_StatusTypeDef yz_dma_m2p_uart_start(UART_HandleTypeDef *uartHandle,uint32_t SendBuff,uint32_t SENDBUFF_SIZE);

DMA_HandleTypeDef* yz_dma_m2p_uart_handle_get();
#endif

#endif //REYZ_YZ_DMA_H
