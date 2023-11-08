//
// Created by 32827 on 2023/11/5.
//
#include "yz_i2c_led1306.h"

HAL_StatusTypeDef yz_1306_open(I2C_HandleTypeDef *hi2c){
    uint8_t cmd=YZ_1306_OPEN;
    return HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_close(I2C_HandleTypeDef *hi2c){
    uint8_t cmd=YZ_1306_CLOSE;
    return HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_light_screen(I2C_HandleTypeDef *hi2c){
    uint8_t cmd=YZ_1306_LIGHT_SCREEN;
    return HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_content_screen(I2C_HandleTypeDef *hi2c){
    uint8_t cmd=YZ_1306_CONTENT_SCREEN;
    return HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_light_level_screen(I2C_HandleTypeDef *hi2c, uint8_t level){
    uint8_t cmd=YZ_1306_LIGHT_LEVEL_SCREEN;
    HAL_StatusTypeDef status;
    status=HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
    if(status!=HAL_OK){
        return status;
    }
    return HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&level,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_light_by_1(I2C_HandleTypeDef *hi2c){
    uint8_t cmd=YZ_1306_LIGHT_BY_1;
    return HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_light_by_0(I2C_HandleTypeDef *hi2c){
    uint8_t cmd=YZ_1306_LIGHT_BY_0;
    return HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_ram_inc_set(I2C_HandleTypeDef *hi2c, uint8_t mode){
    uint8_t cmd=YZ_1306_RAM_SET_INC_MODE;
    HAL_StatusTypeDef status;
    status=HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
    if(status!=HAL_OK){
        return status;
    }
    return HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&mode,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_ram_line_start_end_set(I2C_HandleTypeDef *hi2c, uint8_t start, uint8_t end){
    uint8_t cmd=YZ_1306_SET_LINE_START_END;
    HAL_StatusTypeDef status;
    status=HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
    if(status!=HAL_OK){
        return status;
    }
    status=HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&start,1,YZ_1306_I2C_TIMEOUT);
    if (status!=HAL_OK){
        return status;
    }
    return HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&end,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_ram_page_start_end_set(I2C_HandleTypeDef *hi2c, uint8_t start, uint8_t end){
    uint8_t cmd=YZ_1306_SET_PAGE_START_END;
    HAL_StatusTypeDef status;
    status=HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
    if(status!=HAL_OK){
        return status;
    }
    status=HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&start,1,YZ_1306_I2C_TIMEOUT);
    if (status!=HAL_OK){
        return status;
    }
    return HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&end,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_col_low_set(I2C_HandleTypeDef *hi2c, uint8_t col_low){
    uint8_t cmd=YZ_1306_COL_LOW_BASE+col_low;
    return  HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_col_high_set(I2C_HandleTypeDef *hi2c, uint8_t col_high){
    uint8_t cmd=YZ_1306_COL_HIGH_BASE+col_high;
    return  HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_date_write(I2C_HandleTypeDef *hi2c, uint8_t data){
    return  HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_DATA,1,&data,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_date_write_by_recv(I2C_HandleTypeDef *hi2c,struct yz_recv_area *area,uint16_t len){
    HAL_StatusTypeDef status;
    status=yz_recv_i2c_tran(hi2c,area,YZ_1306_ADDRESS_USE,YZ_1306_DATA,len);
    return status;
}
HAL_StatusTypeDef yz_1306_page_set(I2C_HandleTypeDef *hi2c, uint8_t page){
    uint8_t cmd=YZ_1306_PAGE_BASE+page;
    return  HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_lines_set(I2C_HandleTypeDef *hi2c, uint8_t level){
    uint8_t cmd=YZ_1306_LED_LINES;
    HAL_StatusTypeDef status;
    status=HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
    if(status!=HAL_OK){
        return status;
    }
    return HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&level,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_y_offset_set(I2C_HandleTypeDef *hi2c,uint8_t offset){
    uint8_t cmd=YZ_1306_LED_Y_OFFSET;
    HAL_StatusTypeDef status;
    status=HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
    if(status!=HAL_OK){
        return status;
    }
    return HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&offset,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_clock_set(I2C_HandleTypeDef *hi2c, uint8_t reg_data){
    uint8_t cmd=YZ_1306_LED_CLOCK;
    HAL_StatusTypeDef status;
    status=HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
    if(status!=HAL_OK){
        return status;
    }
    return HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&reg_data,1,YZ_1306_I2C_TIMEOUT);
}
///屏幕是否和内存同步
HAL_StatusTypeDef yz_1306_dynamic_screen(I2C_HandleTypeDef *hi2c){
    uint8_t cmd=YZ_1306_DYNAMIC_SCREEN;
    return HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_static_screen(I2C_HandleTypeDef *hi2c){
    uint8_t cmd=YZ_1306_STATIC_SCREEN;
    return HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
}
HAL_StatusTypeDef yz_1306_direction_set(I2C_HandleTypeDef *hi2c, uint8_t direction){
    uint8_t cmd=direction;
    return  HAL_I2C_Mem_Write(hi2c,YZ_1306_ADDRESS_USE,YZ_1306_COMMAND,1,&cmd,1,YZ_1306_I2C_TIMEOUT);
}