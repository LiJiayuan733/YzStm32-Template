//
// Created by 32827 on 2023/10/30.
//
#include "yz_main.h"

PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit((UART_HandleTypeDef *) YZ_EVENT_RECV_AREA_USE->instance, (uint8_t *)&ch, 1, 0x1000);//阻塞方式打印,串口1
    return ch;
}
GETCHAR_PROTOTYPE
{
    uint16_t size;
    yz_recv_get_size(YZ_EVENT_RECV_AREA_USE, &size);
    if(size==0){
        return EOF;
    }
    return yz_get_recv(YZ_EVENT_RECV_AREA_USE);
}
void yz_init(UART_HandleTypeDef *mu1,UART_HandleTypeDef *mu2,I2C_HandleTypeDef *mi1,SPI_HandleTypeDef *spi1){
    yz_port_setUart1(mu1);
    yz_port_setUart2(mu2);
    yz_port_setI2C1(mi1);
    yz_port_setSpi1(spi1);
    yz_led_init();
    yz_key_init();
    yz_loop_init();
}
void yz_recv_update(struct yz_recv_area *area,uint16_t size){
//    if(size==8||size==16){
//        yz_recv_uart_tran(musart1,size);
//    }
}
HAL_StatusTypeDef yz_event_1306_load(uint32_t pointer1){
    I2C_HandleTypeDef *mi2c1=yz_port_getI2C1();
    yz_1306_close(mi2c1);
    yz_1306_light_screen(mi2c1);
    yz_1306_light_level_screen(mi2c1,128);
    yz_1306_ram_inc_set(mi2c1,YZ_1306_RAM_INC_MODE_PAGE);
    yz_1306_direction_set(mi2c1,YZ_1306_DIRECTION_LEFT_TO_RIGHT);
    yz_1306_direction_set(mi2c1,YZ_1306_DIRECTION_BOTTOM_TO_TOP);
    yz_1306_content_screen(mi2c1);
    yz_1306_clock_set(mi2c1,YZ_1306_LED_CLOCK_MAX);
    yz_1306_open(mi2c1);
    for (int i = 0; i < 8; i++) {
        yz_1306_page_set(mi2c1,i);
        yz_1306_col_low_set(mi2c1,2);
        yz_1306_col_high_set(mi2c1,0);
        for (int j = 0; j < 128; ++j) {
            yz_1306_date_write(mi2c1,j);
        }
    }
    yz_lcd1306_init();
    yz_lcd1306_clear();
    return HAL_OK;
}
void yz_main(){
    yz_recv_init(yz_port_getUart2(),yz_recv_get_uart2_area());
    yz_recv_init(yz_port_getUart1(),yz_recv_get_uart1_area());
    const char *p="测试数据";
    printf("程序进行中...\n");
    //添加任务/事件
//    yz_loop_add_event_handle(yz_event_recv_update);
    yz_loop_add_event_handle(yz_event_1306_load);
    //yz_loop_add_event_handle(yz_event_recv_init);
}