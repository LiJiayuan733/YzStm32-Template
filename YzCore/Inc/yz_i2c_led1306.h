//
// Created by 32827 on 2023/11/5.
//

#ifndef REYZ_YZ_I2C_LED1306_H
#define REYZ_YZ_I2C_LED1306_H
#include "stm32f1xx.h"
#include "yz_config.h"

#if YZLED1306
#include "yz_irq.h"

#define YZ_1306_I2C_TIMEOUT 1000

#define YZ_1306_LED_ADDRESS 0x7A
#define YZ_1306_LED_ADDRESS2 0x78

/**
 * 定义使用的led1306地址
 * */
#define YZ_1306_ADDRESS_USE YZ_1306_LED_ADDRESS2

#define YZ_1306_OPEN 0xAF
#define YZ_1306_CLOSE 0xAE
#define YZ_1306_CONTENT_SCREEN 0xA4
#define YZ_1306_LIGHT_SCREEN 0xA5
#define YZ_1306_LIGHT_LEVEL_SCREEN 0x81

#define YZ_1306_LIGHT_BY_0 0xA7
#define YZ_1306_LIGHT_BY_1 0xA6

#define YZ_1306_RAM_SET_INC_MODE 0x20
#define YZ_1306_RAM_INC_MODE_HOR 0x00
#define YZ_1306_RAM_INC_MODE_VER 0x01
#define YZ_1306_RAM_INC_MODE_PAGE 0x02

#define YZ_1306_SET_LINE_START_END 0x21
#define YZ_1306_SET_PAGE_START_END 0x22

#define YZ_1306_DYNAMIC_SCREEN 0xA4
#define YZ_1306_STATIC_SCREEN 0xA5

#define YZ_1306_DIRECTION_LEFT_TO_RIGHT 0xa1
#define YZ_1306_DIRECTION_RIGHT_TO_LEFT 0xa0

#define YZ_1306_DIRECTION_TOP_TO_BOTTOM 0xc0
#define YZ_1306_DIRECTION_BOTTOM_TO_TOP 0xc8

#define YZ_1306_LED_LINES 0xA8
#define YZ_1306_LED_CLOCK 0xD5
#define YZ_1306_LED_CLOCK_MAX 0b11110000

#define YZ_1306_LED_Y_OFFSET 0xD3

#define YZ_1306_COMMAND 0b00000000
#define YZ_1306_DATA 0b01000000
#define YZ_1306_PAGE_BASE 0xB0
#define YZ_1306_COL_LOW_BASE 0x00
#define YZ_1306_COL_HIGH_BASE 0x10

HAL_StatusTypeDef yz_1306_open(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef yz_1306_close(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef yz_1306_light_screen(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef yz_1306_content_screen(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef yz_1306_light_level_screen(I2C_HandleTypeDef *hi2c, uint8_t level);
HAL_StatusTypeDef yz_1306_light_by_1(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef yz_1306_light_by_0(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef yz_1306_ram_inc_set(I2C_HandleTypeDef *hi2c, uint8_t mode);
HAL_StatusTypeDef yz_1306_ram_line_start_end_set(I2C_HandleTypeDef *hi2c, uint8_t start, uint8_t end);
HAL_StatusTypeDef yz_1306_ram_page_start_end_set(I2C_HandleTypeDef *hi2c, uint8_t start, uint8_t end);
HAL_StatusTypeDef yz_1306_col_low_set(I2C_HandleTypeDef *hi2c, uint8_t col_low);
HAL_StatusTypeDef yz_1306_col_high_set(I2C_HandleTypeDef *hi2, uint8_t col_high);
HAL_StatusTypeDef yz_1306_date_write(I2C_HandleTypeDef *hi2c, uint8_t data);
HAL_StatusTypeDef yz_1306_date_write_by_recv(I2C_HandleTypeDef *hi2c,struct yz_recv_area *area,uint16_t len);
HAL_StatusTypeDef yz_1306_page_set(I2C_HandleTypeDef *hi2c, uint8_t page);
HAL_StatusTypeDef yz_1306_lines_set(I2C_HandleTypeDef *hi2c, uint8_t level);
HAL_StatusTypeDef yz_1306_clock_set(I2C_HandleTypeDef *hi2c, uint8_t reg_data);
HAL_StatusTypeDef yz_1306_y_offset_set(I2C_HandleTypeDef *hi2c,uint8_t offset);
///屏幕是否和内存同步
HAL_StatusTypeDef yz_1306_dynamic_screen(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef yz_1306_static_screen(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef yz_1306_direction_set(I2C_HandleTypeDef *hi2c, uint8_t direction);
#endif

#endif //REYZ_YZ_I2C_LED1306_H
