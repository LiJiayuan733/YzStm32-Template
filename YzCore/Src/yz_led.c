//
// Created by 32827 on 2023/10/31.
//
#include "yz_led.h"
void yz_led_green(void){
    HAL_GPIO_WritePin(LED_PIN_BASE,GREEN_LED_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_PIN_BASE,BLUE_LED_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_PIN_BASE,RED_LED_PIN,GPIO_PIN_SET);
}
void yz_led_red(void){
    HAL_GPIO_WritePin(LED_PIN_BASE,GREEN_LED_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_PIN_BASE,BLUE_LED_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_PIN_BASE,RED_LED_PIN,GPIO_PIN_RESET);
}
void yz_led_blue(void){
    HAL_GPIO_WritePin(LED_PIN_BASE,GREEN_LED_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_PIN_BASE,BLUE_LED_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_PIN_BASE,RED_LED_PIN,GPIO_PIN_SET);
}
void yz_led_init(void){
#if YZLED
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Pin = RED_LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED_PIN_BASE, &GPIO_InitStruct);
    HAL_GPIO_WritePin(LED_PIN_BASE, RED_LED_PIN, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = GREEN_LED_PIN;
    HAL_GPIO_Init(LED_PIN_BASE,&GPIO_InitStruct);
    HAL_GPIO_WritePin(LED_PIN_BASE, GREEN_LED_PIN, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = BLUE_LED_PIN;
    HAL_GPIO_Init(LED_PIN_BASE,&GPIO_InitStruct);
    HAL_GPIO_WritePin(LED_PIN_BASE,BLUE_LED_PIN,GPIO_PIN_RESET);
#endif
}