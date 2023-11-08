//
// Created by 32827 on 2023/11/7.
//

#ifndef REYZ_YZ_EVENT_RECV_CHANNEL_H
#define REYZ_YZ_EVENT_RECV_CHANNEL_H
#include "stm32f1xx.h"
#include "yz_irq.h"
#include "yz_event_loop.h"
#include "yz_port.h"
#include "stdio.h"
#include "string.h"

/**
 * 集中处理Recv中接收到的数据
 * 数据约定:
 *  - 32bits 程序选择
 *      0x00000000 为主处理程序，分支程序处理时，主程序不处理数据，分支处理完后，分支程序需将DATA标志复位位 0x00000000 ，重新开启此程序，并清除自身(返回HAL_OK)
 *      0x00000001 为led1306图片传输分支处理程序
 *  - 不限数据长度 程序处理数据
 * */

#if YZLED1306
#include "yz_i2c_led1306.h"
#endif
#define YZ_EVENT_RECV_DATA_HANDLER 0x00000000
#define YZ_EVENT_RECV_DATA_1306_IMAGE 0x00000001
#define YZ_EVENT_RECV_DATA_BLUETOOCH_DEBUG 0x00000002
#define YZ_EVENT_RECV_DATA_RESET YZ_EVNET_RECV_DATA_VALUE=YZ_EVENT_RECV_DATA_HANDLER;return HAL_OK;

#define YZ_EVNET_RECV_DATA_POINTER (uint32_t *)yz_loop_get_pointer(yz_event_recv_get_data_index())
#define YZ_EVNET_RECV_DATA_VALUE *(YZ_EVNET_RECV_DATA_POINTER)
///初始化程序，初始完后自动加载yz_event_recv_handler，并结束自身
HAL_StatusTypeDef yz_event_recv_init(uint32_t pointer1);
HAL_StatusTypeDef yz_event_recv_handler(uint32_t pointer1);
///获取数据索引，可在yz_loop pointer表中获取到data数据指针,从而从外部有修改
uint8_t yz_event_recv_get_data_index();
HAL_StatusTypeDef yz_event_recv_1306_image(uint32_t pointer1);
#endif //REYZ_YZ_EVENT_RECV_CHANNEL_H