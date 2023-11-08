//
// Created by 32827 on 2023/10/31.
//

#ifndef REYZ_YZ_MAIN_H
#define REYZ_YZ_MAIN_H
#include "stm32f1xx.h"
#include "yz.h"
#include "stdio.h"
#include "string.h"

///修复printf
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

#ifdef __GNUC__
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif

#define BUFFER_SIZE 32

void yz_init(UART_HandleTypeDef *mu1,UART_HandleTypeDef *mu4,I2C_HandleTypeDef *mi1);
void yz_main();
#endif //REYZ_YZ_MAIN_H
