//
// Created by 32827 on 2023/11/10.
//
#include "yz_i2c_mpu6050.h"

HAL_StatusTypeDef yz_mpu6050_open(I2C_HandleTypeDef *hi2c){
    HAL_StatusTypeDef state;
    uint8_t cmd=YZ_MPU6050_REG_POWER1_RESET_VALUE;
    state=HAL_I2C_Mem_Write(hi2c,YZ_MPU6050_WRITE_ADDRESS,YZ_MPU6050_REG_POWER1_ADDRESS,1,&cmd,1,YZ_MPU6050_I2C_TIMEOUT);
    if(state!=HAL_OK){
        return state;
    }
    HAL_Delay(100);
    cmd=YZ_MPU6050_REG_POWER1_CLK_VALUE;
    state=HAL_I2C_Mem_Write(hi2c,YZ_MPU6050_WRITE_ADDRESS,YZ_MPU6050_REG_POWER1_ADDRESS,1,&cmd,1,YZ_MPU6050_I2C_TIMEOUT);
    if(state!=HAL_OK){
        return state;
    }
    cmd=YZ_MPU6050_REG_POWER2_RESET_VALUE;
    state= HAL_I2C_Mem_Write(hi2c,YZ_MPU6050_WRITE_ADDRESS,YZ_MPU6050_REG_POWER2_ADDRESS,1,&cmd,1,YZ_MPU6050_I2C_TIMEOUT);
    if(state!=HAL_OK){
        return state;
    }
    cmd=YZ_MPU6050_REG_INT_CLOSE_VALUE;
    state= HAL_I2C_Mem_Write(hi2c,YZ_MPU6050_WRITE_ADDRESS,YZ_MPU6050_REG_INT_ADDRESS,1,&cmd,1,YZ_MPU6050_I2C_TIMEOUT);
    if(state!=HAL_OK){
        return state;
    }
    cmd=YZ_MPU6050_REG_SIMPLE_RATE_MOST_VALUE;
    state= HAL_I2C_Mem_Write(hi2c,YZ_MPU6050_WRITE_ADDRESS,YZ_MPU6050_REG_SIMPLE_RATE_ADDRESS,1,&cmd,1,YZ_MPU6050_I2C_TIMEOUT);
    if(state!=HAL_OK){
        return state;
    }
    cmd=YZ_MPU6050_REG_DLPF_NORMAL_SET_VALUE;
    state= HAL_I2C_Mem_Write(hi2c,YZ_MPU6050_WRITE_ADDRESS,YZ_MPU6050_REG_DLPF_ADDRESS,1,&cmd,1,YZ_MPU6050_I2C_TIMEOUT);
    if(state!=HAL_OK){
        return state;
    }
    cmd=YZ_MPU6050_REG_GYROSCOPE_NORMAL_SET_VALUE;
    state= HAL_I2C_Mem_Write(hi2c,YZ_MPU6050_WRITE_ADDRESS,YZ_MPU6050_REG_GYROSCOPE_ADDRESS,1,&cmd,1,YZ_MPU6050_I2C_TIMEOUT);
    if(state!=HAL_OK){
        return state;
    }
    cmd=YZ_MPU6050_REG_ACCELEROMETER_NORMAL_SET_VALUE;
    state= HAL_I2C_Mem_Write(hi2c,YZ_MPU6050_WRITE_ADDRESS,YZ_MPU6050_REG_ACCELEROMETER_ADDRESS,1,&cmd,1,YZ_MPU6050_I2C_TIMEOUT);
    if(state!=HAL_OK){
        return state;
    }
    cmd=YZ_MPU6050_REG_INT_PIN_CFG_NORMAL_SET_VALUE;
    state= HAL_I2C_Mem_Write(hi2c,YZ_MPU6050_WRITE_ADDRESS,YZ_MPU6050_REG_INT_PIN_CFG_ADDRESS,1,&cmd,1,YZ_MPU6050_I2C_TIMEOUT);
    return state;
}
HAL_StatusTypeDef yz_mpu6050_get_reg8_data(I2C_HandleTypeDef *hi2c,uint8_t address,uint8_t *data){
    return HAL_I2C_Mem_Read(hi2c,YZ_MPU6050_READ_ADDRESS,address,1,data,1,YZ_MPU6050_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_mpu6050_get_reg16_data(I2C_HandleTypeDef *hi2c,uint8_t address,uint16_t *data){
    HAL_StatusTypeDef state;
    state=HAL_I2C_Mem_Read(hi2c,YZ_MPU6050_READ_ADDRESS,address,1,(uint8_t *)data,1,YZ_MPU6050_I2C_TIMEOUT);
    if(state!=HAL_OK){
        return state;
    }
    return  HAL_I2C_Mem_Read(hi2c,YZ_MPU6050_READ_ADDRESS,address+1,1,((uint8_t *)data)+1,1,YZ_MPU6050_I2C_TIMEOUT);
}