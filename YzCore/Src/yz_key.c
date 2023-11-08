//
// Created by 32827 on 2023/11/1.
//
#include "yz_key.h"

void yz_key_init(void){
#if YZKEY
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitTypeDef keyInit;

    keyInit.Pin=KEY1_PIN;
    keyInit.Speed=GPIO_SPEED_FREQ_HIGH;
    //HAL库将EXTI配置集成进了GPIO_INIT
    keyInit.Mode=GPIO_MODE_IT_FALLING;
    keyInit.Pull=GPIO_NOPULL;
    HAL_GPIO_Init(KEY1_PIN_BASE,&keyInit);

    HAL_NVIC_SetPriority(EXTI15_10_IRQn,15,0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

    keyInit.Pin=KEY2_PIN;
    keyInit.Mode=GPIO_MODE_IT_FALLING;
    HAL_GPIO_Init(KEY2_PIN_BASE,&keyInit);
    HAL_NVIC_SetPriority(EXTI2_IRQn,15,0);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);
#endif
}
#if YZKEY
void yz_key_irq_handler(void){
    if(__HAL_GPIO_EXTI_GET_IT(KEY1_PIN)!=RESET){

#if YZLED
        HAL_GPIO_WritePin(LED_PIN_BASE,GREEN_LED_PIN,GPIO_PIN_SET);
#endif

    }
    if(__HAL_GPIO_EXTI_GET_IT(KEY2_PIN)!=RESET){

#if YZLED
        HAL_GPIO_WritePin(LED_PIN_BASE,BLUE_LED_PIN,GPIO_PIN_SET);
#endif

    }
}
#endif
