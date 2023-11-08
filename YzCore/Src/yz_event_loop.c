//
// Created by 32827 on 2023/11/5.
//
#include "yz_event_loop.h"

HAL_StatusTypeDef (*p_event[YZ_LOOP_EVENT_SIZE])(uint32_t pointer1)={NULL_PTR};
uint32_t pointer[YZ_LOOP_POINTER_SIZE]={NULL_PTR};
void yz_loop_act(){
    HAL_StatusTypeDef status;
    //检查是否有要处理的事件
    for (int i = 0; i < YZ_LOOP_EVENT_SIZE; ++i) {
        if(p_event[i]!=NULL_PTR){
            status=p_event[i]((uint32_t)&pointer);
            if(status==HAL_OK){
                p_event[i]=NULL_PTR;
            }
        }
    }
}
void yz_loop_init(){
    //为后期做保留
}
uint8_t yz_loop_add_event_handle(HAL_StatusTypeDef (*p)(uint32_t pointer1)){
    for(int i=0;i<YZ_LOOP_EVENT_SIZE;i++){
        if(p_event[i]==NULL_PTR){
            p_event[i]=p;
            return i;
        }
    }
    return NULL_PTR;
}
uint8_t yz_loop_add_pointer(uint32_t pointer1){
    for(int i=0;i<YZ_LOOP_POINTER_SIZE;i++){
        if(pointer[i]==NULL_PTR){
            pointer[i]=pointer1;
            return i;
        }
    }
    return NULL_PTR;
}
uint32_t yz_loop_get_pointer(uint8_t index){
    return pointer[index];
}