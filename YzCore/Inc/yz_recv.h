//
// Created by 32827 on 2023/11/8.
//

#ifndef REYZ_YZ_RECV_H
#define REYZ_YZ_RECV_H
#include "stm32f1xx.h"
#include "yz_config.h"
#include "stdio.h"

///------------- YZ 基础中断 ---------------
void YZ_RECV_HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void YZ_RECV_HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
///---------------接收 配置----------------
#define YZ_RECV_USART1 ON
#define YZ_RECV_USART2 ON
#define YZ_RECV_AREA_SIZE 1024

struct  yz_recv_area {
    uint8_t yz_recv[YZ_RECV_AREA_SIZE];     //数据保存
    uint16_t yz_recv_write_ptr;             //写指针
    uint16_t yz_recv_read_ptr;              //读指针
    uint16_t yz_recv_size;                  //数据数量
    uint8_t yz_recv_ch;                     //数据中介，用于兼容HAL库
    uint32_t instance;                      //传输通道实例指针
};

#if YZ_RECV_USART1
struct yz_recv_area * yz_recv_get_uart1_area();
#endif

#if YZ_RECV_USART2
struct yz_recv_area * yz_recv_get_uart2_area();
#endif

///---- Need Override ----
void yz_recv_update(struct yz_recv_area *area,uint16_t size);
void yz_recv_tran_finish();
///-----------------------

///----    Method     ----
/// 获取缓存且不删除读取内容
/// @param offset 偏移量
uint8_t yz_read_recv(struct yz_recv_area *area,uint16_t offset);

/// 读取缓存并删除
uint8_t yz_get_recv(struct yz_recv_area *area);

void yz_add_recv(struct yz_recv_area *area,uint8_t *t);
void yz_recv_get_size(struct yz_recv_area *area,uint16_t *size);
void yz_recv_init(UART_HandleTypeDef *huart,struct yz_recv_area *area);
uint8_t * yz_recv_get_read_ptr(struct yz_recv_area *area);
void yz_recv_del(struct yz_recv_area *area,uint16_t len);
#if YZDMA
#include "yz_dma.h"
HAL_StatusTypeDef yz_recv_uart_tran(UART_HandleTypeDef *uartHandle,struct yz_recv_area *area,uint16_t size);
#endif
#if YZLED1306
HAL_StatusTypeDef yz_recv_i2c_tran(I2C_HandleTypeDef *i2cHandle,struct yz_recv_area *area,uint16_t DevAddress, uint16_t MemAddress,uint16_t size);
#endif
///-----------------------
///---------------------------------------

#endif //REYZ_YZ_RECV_H
