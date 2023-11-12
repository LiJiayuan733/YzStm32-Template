//
// Created by 32827 on 2023/11/11.
//

#ifndef REYZ_YZ_SPI_MICROCARD_H
#define REYZ_YZ_SPI_MICROCARD_H
#include "stm32f1xx.h"
#include "yz_port.h"
#include "yz_config.h"
/**
 * PA5 --> SPI1_SCK --> SCL
 * PA7 --> SPI1_MOSI --> SDA
 * PA4 --> RST  复位
 * PE5 --> RS   数据命令选择端
 * PE6 --> CS   片选
 * */
#if YZLCD9648
#define YZ_LCD1306_PIN_RST GPIO_PIN_4
#define YZ_LCD1306_PIN_RS GPIO_PIN_5
#define YZ_LCD1306_PIN_CS GPIO_PIN_6
#define YZ_LCD1306_BASE_RST GPIOA
#define YZ_LCD1306_BASE_RS GPIOE
#define YZ_LCD1306_BASE_CS GPIOE
HAL_StatusTypeDef yz_lcd1306_init();
HAL_StatusTypeDef yz_lcd1306_clear();
HAL_StatusTypeDef yz_lcd1306_write_command(uint8_t data);
HAL_StatusTypeDef yz_lcd1306_write_data(uint8_t data);
#endif
#endif //REYZ_YZ_SPI_MICROCARD_H
