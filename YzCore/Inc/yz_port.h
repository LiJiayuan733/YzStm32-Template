//
// Created by 32827 on 2023/11/7.
//

#ifndef REYZ_YZ_PORT_H
#define REYZ_YZ_PORT_H

#include "stm32f1xx.h"
/**
 * 同一给框架提供，输入输出
 * 在yz_main#yz_init初始化
 * */
//TODO: Finish the init for only one line
UART_HandleTypeDef *yz_port_getUart1();
UART_HandleTypeDef *yz_port_getUart2();
I2C_HandleTypeDef *yz_port_getI2C1();
SPI_HandleTypeDef *yz_port_getSpi1();
void yz_port_setUart1(UART_HandleTypeDef *uart1);
void yz_port_setUart2(UART_HandleTypeDef *usart2);
void yz_port_setI2C1(I2C_HandleTypeDef *i2c1);
void yz_port_setSpi1(SPI_HandleTypeDef *spi1);
#endif //REYZ_YZ_PORT_H
