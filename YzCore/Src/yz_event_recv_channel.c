//
// Created by 32827 on 2023/11/7.
//
#include "yz_event_recv_channel.h"
uint32_t data=0;
uint8_t data_index;
HAL_StatusTypeDef yz_event_recv_init(uint32_t pointer1){
    data_index=yz_loop_add_pointer((uint32_t) &data);
    yz_loop_add_event_handle(yz_event_recv_handler);
    return HAL_OK;
}
uint8_t yz_event_recv_get_data_index(){
    return data_index;
}
HAL_StatusTypeDef yz_event_recv_1306_image(uint32_t pointer1){
    I2C_HandleTypeDef *mi2c1 =yz_port_getI2C1();
    uint16_t size;
    yz_recv_get_size(YZ_EVENT_RECV_AREA_USE,&size);
    if(size>=1024){
        for (int i = 0; i < 8; i++) {
            yz_1306_page_set(mi2c1,i);
            yz_1306_col_low_set(mi2c1,2);
            yz_1306_col_high_set(mi2c1,0);
            yz_1306_date_write_by_recv(mi2c1,YZ_EVENT_RECV_AREA_USE,128);
        }
        YZ_EVENT_RECV_DATA_RESET
    }
    return HAL_BUSY;
}
HAL_StatusTypeDef yz_event_recv_bluetooch_debug(uint32_t pointer1){
    UART_HandleTypeDef *mu2=yz_port_getUart2();
    char *str="AT";
    HAL_UART_Transmit(mu2,(uint8_t *)str,strlen(str),1000);
    uint16_t size;
    while ((yz_recv_get_size(yz_recv_get_uart2_area(),&size),size)<2){

    }
    for(uint16_t i=0;i<size;i++){
        printf("%c",yz_get_recv(yz_recv_get_uart2_area()));
    }
    fflush(stdout); //刷新缓冲区，以发送数据
    YZ_EVENT_RECV_DATA_RESET
}
HAL_StatusTypeDef yz_event_recv_test(uint32_t pointer1){
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitTypeDef gpio;
    gpio.Pin=GPIO_PIN_10;
    gpio.Mode=GPIO_MODE_OUTPUT_PP;
    gpio.Pull=GPIO_NOPULL;
    gpio.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOC,&gpio);
    gpio.Pin=GPIO_PIN_9;
    HAL_GPIO_Init(GPIOC,&gpio);
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_RESET);

    I2C_HandleTypeDef *ic=yz_port_getI2C1();
    yz_mpu6050_open(ic);
    int16_t z;
    for(int i=0;i<10;i++) {
        HAL_Delay(200);
        yz_mpu6050_get_reg16_data(ic, YZ_MPU6050_REG_GYROSCOPE_Z_ADDRESS, (uint16_t *) &z);
        printf("A(Z): %d\n", z);
        fflush(stdout);
    }
    char c;
    do{
        c=getchar();
    } while (c == '\377');
    printf("发送成功%c\n",c);
    fflush(stdout);
    YZ_EVENT_RECV_DATA_RESET
}
HAL_StatusTypeDef yz_event_recv_handler(uint32_t pointer1){
    if(YZ_EVNET_RECV_DATA_VALUE==YZ_EVENT_RECV_DATA_HANDLER){
        uint16_t size;
        yz_recv_get_size(YZ_EVENT_RECV_AREA_USE,&size);
        if(size>=4){
            data=*((uint32_t *)yz_recv_get_read_ptr(YZ_EVENT_RECV_AREA_USE));
            yz_recv_del(YZ_EVENT_RECV_AREA_USE,4);
            switch (data) {
                case YZ_EVENT_RECV_DATA_1306_IMAGE:
                    yz_loop_add_event_handle(yz_event_recv_1306_image);
                    break;
                case YZ_EVENT_RECV_DATA_BLUETOOCH_DEBUG:
                    yz_loop_add_event_handle(yz_event_recv_bluetooch_debug);
                    break;
                case YZ_EVENT_RECV_DATA_TEST:
                    yz_loop_add_event_handle(yz_event_recv_test);
                    break;
                default:
                    data=YZ_EVENT_RECV_DATA_HANDLER;
            }
        }
    }
    return HAL_BUSY;
}