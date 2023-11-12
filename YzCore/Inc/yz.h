//
// Created by 32827 on 2023/11/1.
//

#ifndef REYZ_YZ_H
#define REYZ_YZ_H

///硬件配置和包装
#include "yz_led.h"
#include "yz_key.h"
#include "yz_dma.h"

///led1306驱动
#include "yz_i2c_led1306.h"
///lcd9648驱动
#include "yz_spi_lcd9648.h"

///中断处理以及数据接收
#include "yz_irq.h"
///程序事件循环相关
#include "yz_event_loop.h"
///数据接受处理相关
#include "yz_event_recv_channel.h"
///通信相关
#include "yz_port.h"
#endif //REYZ_YZ_H
