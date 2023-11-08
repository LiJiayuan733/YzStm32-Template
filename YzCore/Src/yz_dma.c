//
// Created by 32827 on 2023/11/4.
//
#include "yz_dma.h"
#if YZDMA
DMA_HandleTypeDef hdma_memtomem;
DMA_HandleTypeDef hdma_memtoper_uart;
#endif
void yz_dma_m2m_init(void){
    __DMA2_CLK_ENABLE();
    hdma_memtomem.Instance= DMA2_Channel1;
    hdma_memtomem.Init.Direction=DMA_MEMORY_TO_MEMORY;
    hdma_memtomem.Init.PeriphInc=DMA_PINC_ENABLE;
    hdma_memtomem.Init.MemInc=DMA_MINC_ENABLE;
    hdma_memtomem.Init.PeriphDataAlignment=DMA_PDATAALIGN_WORD;
    hdma_memtomem.Init.MemDataAlignment=DMA_MDATAALIGN_WORD;
    hdma_memtomem.Init.Mode=DMA_NORMAL;
    hdma_memtomem.Init.Priority=DMA_PRIORITY_HIGH;

    HAL_DMA_Init(&hdma_memtomem);
}
void yz_dma_m2m_start(uint32_t aSRC_Const_Buffer,uint32_t aDST_Buffer,uint32_t BUFFER_SIZE){
#if YZLED
    yz_led_blue();
#endif

    HAL_StatusTypeDef DMA_status;
    DMA_status = HAL_DMA_Start(&hdma_memtomem,aSRC_Const_Buffer,
                               aDST_Buffer,BUFFER_SIZE);
#if YZLED
    if(DMA_status != HAL_OK){
        yz_led_red();
    }else{
        yz_led_green();
    }
#endif
}

void yz_dma_m2p_uart_init(UART_HandleTypeDef *uartHandle){
    __DMA1_CLK_ENABLE();
    hdma_memtoper_uart.Instance=yz_m2p_uart_channel;
    hdma_memtoper_uart.Init.Mode=DMA_NORMAL;
    hdma_memtoper_uart.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;
    hdma_memtoper_uart.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;
    hdma_memtoper_uart.Init.PeriphInc=DMA_PINC_DISABLE;
    hdma_memtoper_uart.Init.MemInc=DMA_MINC_ENABLE;
    hdma_memtoper_uart.Init.Direction=DMA_MEMORY_TO_PERIPH;
    hdma_memtoper_uart.Init.Priority=DMA_PRIORITY_HIGH;

    HAL_DMA_Init(&hdma_memtoper_uart);
    __HAL_LINKDMA(uartHandle,hdmatx,hdma_memtoper_uart);
}

HAL_StatusTypeDef yz_dma_m2p_uart_start(UART_HandleTypeDef *uartHandle,uint32_t SendBuff,uint32_t SENDBUFF_SIZE){
#if YZLED
    yz_led_blue();
#endif
    HAL_StatusTypeDef DMA_status=HAL_UART_Transmit_DMA(uartHandle, (uint8_t *)SendBuff ,
                          SENDBUFF_SIZE);
#if YZLED
    if(DMA_status != HAL_OK){
        yz_led_red();
    }else{
        yz_led_green();
    }
#endif
}
DMA_HandleTypeDef* yz_dma_m2p_uart_handle_get(){
    return &hdma_memtoper_uart;
}
