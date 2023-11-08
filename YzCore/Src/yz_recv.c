//
// Created by 32827 on 2023/11/8.
//
#include "yz_recv.h"

#if YZ_RECV_USART1
struct yz_recv_area USART1_RECV_AREA={0};
struct yz_recv_area * yz_recv_get_uart1_area(){
    return &USART1_RECV_AREA;
}
#endif

#if YZ_RECV_USART2
struct yz_recv_area USART2_RECV_AREA={0};
struct yz_recv_area * yz_recv_get_uart2_area(){
    return &USART2_RECV_AREA;
}
#endif

__weak void yz_recv_update(struct yz_recv_area *area,uint16_t size);
__weak void yz_recv_tran_finish();

///------------- YZ 基础中断 ---------------
void YZ_RECV_HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
#if YZ_RECV_USART1
    if(huart==(UART_HandleTypeDef *)USART1_RECV_AREA.instance){
        yz_add_recv(&USART1_RECV_AREA,&USART1_RECV_AREA.yz_recv_ch);
        uint16_t size;
        yz_recv_get_size(&USART1_RECV_AREA,&size);
        yz_recv_update(&USART1_RECV_AREA,size);
        HAL_UART_Receive_IT(huart,&USART1_RECV_AREA.yz_recv_ch,1);
    }
#endif
#if YZ_RECV_USART2
    if(huart==(UART_HandleTypeDef *)USART2_RECV_AREA.instance){
        yz_add_recv(&USART2_RECV_AREA,&USART2_RECV_AREA.yz_recv_ch);
        uint16_t size;
        yz_recv_get_size(&USART2_RECV_AREA,&size);
        yz_recv_update(&USART2_RECV_AREA,size);
        HAL_UART_Receive_IT(huart,&USART2_RECV_AREA.yz_recv_ch,1);
    }
#endif
}

void YZ_RECV_HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){

}

void yz_recv_init(UART_HandleTypeDef *huart,struct yz_recv_area *area){
    area->instance= (uint32_t) huart;
    HAL_UART_Receive_IT(huart,&area->yz_recv_ch,1);
}
uint8_t yz_read_recv(struct yz_recv_area *area,uint16_t offset){
    if(area->yz_recv_size==0||offset>=area->yz_recv_size){
        return 0;
    }
    return area->yz_recv[(area->yz_recv_write_ptr+offset)%YZ_RECV_AREA_SIZE];
}
void yz_add_recv(struct yz_recv_area *area,uint8_t *t){
    if(area->yz_recv_size==YZ_RECV_AREA_SIZE+1){
        printf("RECV AREA FULL: %d\n",t);
    }
    area->yz_recv[area->yz_recv_write_ptr] = *t;
    area->yz_recv_write_ptr=(area->yz_recv_write_ptr+1)%YZ_RECV_AREA_SIZE;
    area->yz_recv_size++;
}
void yz_recv_get_size(struct yz_recv_area *area,uint16_t *size){
    *size=area->yz_recv_size;
}
uint8_t yz_get_recv(struct yz_recv_area *area){
    if(area->yz_recv_size==0){
        return 0;
    }
    uint8_t re=area->yz_recv[area->yz_recv_read_ptr];
    area->yz_recv_read_ptr=(area->yz_recv_read_ptr+1)%YZ_RECV_AREA_SIZE;
    area->yz_recv_size--;
    return re;
}
uint8_t * yz_recv_get_read_ptr(struct yz_recv_area *area){
    return &area->yz_recv[area->yz_recv_read_ptr];
}
void yz_recv_del(struct yz_recv_area *area,uint16_t len){
    area->yz_recv_read_ptr=(area->yz_recv_read_ptr+len)%YZ_RECV_AREA_SIZE;
    area->yz_recv_size-=len;
}
#if YZDMA
HAL_StatusTypeDef yz_recv_uart_tran(UART_HandleTypeDef *uartHandle,struct yz_recv_area *area,uint16_t size){
    HAL_StatusTypeDef status;
    if(area->yz_recv_read_ptr+size>=YZ_RECV_AREA_SIZE){
        uint16_t tran_part_1=(YZ_RECV_AREA_SIZE-area->yz_recv_read_ptr);
        status=yz_dma_m2p_uart_start(uartHandle, (uint32_t) yz_recv_get_read_ptr(area), tran_part_1);
        area->yz_recv_read_ptr=0;
        area->yz_recv_size-=tran_part_1;
        if(size-tran_part_1==0||area->yz_recv_size==0){
            return HAL_OK;
        }
        status=yz_dma_m2p_uart_start(uartHandle, (uint32_t) yz_recv_get_read_ptr(area), size-tran_part_1);
        area->yz_recv_read_ptr+=(size-tran_part_1);
        area->yz_recv_size-=(size-tran_part_1);
    }else{
        status=yz_dma_m2p_uart_start(uartHandle, (uint32_t) yz_recv_get_read_ptr(area), size);
        area->yz_recv_read_ptr+=size;
        area->yz_recv_size-=size;
    }
    return status;
}
#endif
#if YZLED1306
HAL_StatusTypeDef yz_recv_i2c_tran(I2C_HandleTypeDef *i2cHandle,struct yz_recv_area *area,uint16_t DevAddress, uint16_t MemAddress,uint16_t size){
    HAL_StatusTypeDef status;
    if(area->yz_recv_read_ptr+size>=YZ_RECV_AREA_SIZE){
        uint16_t tran_part_1=(YZ_RECV_AREA_SIZE-area->yz_recv_read_ptr);
        status=HAL_I2C_Mem_Write(i2cHandle,DevAddress,MemAddress,1,yz_recv_get_read_ptr(area),tran_part_1,1000);
        area->yz_recv_read_ptr=0;
        area->yz_recv_size-=tran_part_1;
        if(size-tran_part_1==0||area->yz_recv_size==0){
            return HAL_OK;
        }
        status=HAL_I2C_Mem_Write(i2cHandle,DevAddress,MemAddress,1,yz_recv_get_read_ptr(area),size-tran_part_1,1000);
        area->yz_recv_read_ptr+=(size-tran_part_1);
        area->yz_recv_size-=(size-tran_part_1);
    }
    else{
        status=HAL_I2C_Mem_Write(i2cHandle,DevAddress,MemAddress,1,yz_recv_get_read_ptr(area),size,1000);
        area->yz_recv_read_ptr+=size;
        area->yz_recv_size-=size;
    }
    return status;
}
#endif
///---------------------------------------