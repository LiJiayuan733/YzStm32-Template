//
// Created by 32827 on 2023/11/11.
//
#include "yz_spi_lcd9648.h"
#if YZLCD9648
HAL_StatusTypeDef yz_lcd1306_write_command(uint8_t data){
    SPI_HandleTypeDef *hspi1=yz_port_getSpi1();
    HAL_StatusTypeDef state;
    HAL_GPIO_WritePin(YZ_LCD1306_BASE_CS,YZ_LCD1306_PIN_CS, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(YZ_LCD1306_BASE_RS,YZ_LCD1306_PIN_RS, GPIO_PIN_RESET);
    state=HAL_SPI_Transmit(hspi1, &data, 1, 1000);
    HAL_GPIO_WritePin(YZ_LCD1306_BASE_CS,YZ_LCD1306_PIN_CS, GPIO_PIN_SET);
    if(state!=HAL_OK){
        return state;
    }
    return HAL_OK;
}
HAL_StatusTypeDef yz_lcd1306_write_data(uint8_t data){
    SPI_HandleTypeDef *hspi1=yz_port_getSpi1();
    HAL_StatusTypeDef state;
    HAL_GPIO_WritePin(YZ_LCD1306_BASE_CS,YZ_LCD1306_PIN_CS, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(YZ_LCD1306_BASE_RS,YZ_LCD1306_PIN_RS, GPIO_PIN_SET);
    state=HAL_SPI_Transmit(hspi1, &data, 1, 1000);
    HAL_GPIO_WritePin(YZ_LCD1306_BASE_CS,YZ_LCD1306_PIN_CS, GPIO_PIN_SET);
    if(state!=HAL_OK){
        return state;
    }
    return HAL_OK;
}
HAL_StatusTypeDef yz_lcd1306_clear(){
    /**
     *
{
	unsigned char i,j;
	WriteComm(0x40);
	for(i=0; i < 9; i++)//一共九页
	{
		WriteComm(0xb0+i);//页地址
		WriteComm(0x10);//列地址
		WriteComm(0x00);//列地址
		for(j = 0; j < 96; j++)
		 {
			 WriteData(0x00);
		  }
	}
     * */
    uint8_t i,j;
    HAL_StatusTypeDef status=HAL_OK;
    status+=yz_lcd1306_write_command(0x40);
    for(i=0; i < 6; i++){
        yz_lcd1306_write_command(0xb0+i);
        yz_lcd1306_write_command(0x10);
        yz_lcd1306_write_command(0x00);
        for(j=0;j<96;j++ ){
            status+=yz_lcd1306_write_data(j);
        }
    }
    return status;
}
HAL_StatusTypeDef yz_lcd1306_init(){
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef gpioInit;
    gpioInit.Pin=YZ_LCD1306_PIN_CS;
    gpioInit.Mode=GPIO_MODE_OUTPUT_PP;
    gpioInit.Speed=GPIO_SPEED_FREQ_HIGH;
    gpioInit.Pull=GPIO_NOPULL;
    HAL_GPIO_Init(YZ_LCD1306_BASE_CS,&gpioInit);
    gpioInit.Pin=YZ_LCD1306_PIN_RS;
    HAL_GPIO_Init(YZ_LCD1306_BASE_RS,&gpioInit);
    gpioInit.Pin=YZ_LCD1306_PIN_RST;
    HAL_GPIO_Init(YZ_LCD1306_BASE_RST,&gpioInit);


    HAL_GPIO_WritePin(YZ_LCD1306_BASE_RST,YZ_LCD1306_PIN_RST,GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(YZ_LCD1306_BASE_RST,YZ_LCD1306_PIN_RST,GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(YZ_LCD1306_BASE_RST,YZ_LCD1306_PIN_RST,GPIO_PIN_SET);

    HAL_StatusTypeDef status=HAL_OK;
    status+=yz_lcd1306_write_command(0xe2);
    status+=yz_lcd1306_write_command(0xc8);
    status+=yz_lcd1306_write_command(0xa0);
    status+=yz_lcd1306_write_command(0x2f);
    status+=yz_lcd1306_write_command(0x26);
    status+=yz_lcd1306_write_command(0x81);
    status+=yz_lcd1306_write_command(0x10);
    status+=yz_lcd1306_write_command(0xaf);
    return status;
}
#endif