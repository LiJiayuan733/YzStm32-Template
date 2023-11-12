//
// Created by 32827 on 2023/11/7.
//
#include "yz_port.h"
//--------------------------------------------------------
//                     --  Field  --
UART_HandleTypeDef *musart1;
UART_HandleTypeDef *musart2;
I2C_HandleTypeDef *mi2c1;
SPI_HandleTypeDef *mspi1;
//--------------------------------------------------------
UART_HandleTypeDef *yz_port_getUart1(){
    return musart1;
}
UART_HandleTypeDef *yz_port_getUart2(){
    return musart2;
}
I2C_HandleTypeDef *yz_port_getI2C1(){
    return mi2c1;
}
SPI_HandleTypeDef *yz_port_getSpi1(){
    return mspi1;
}
void yz_port_setUart2(UART_HandleTypeDef *usart2){
    musart2=usart2;
}
void yz_port_setUart1(UART_HandleTypeDef *uart1){
    musart1=uart1;
}
void yz_port_setI2C1(I2C_HandleTypeDef *i2c1){
    mi2c1=i2c1;
}
void yz_port_setSpi1(SPI_HandleTypeDef *spi1){
    mspi1=spi1;
}