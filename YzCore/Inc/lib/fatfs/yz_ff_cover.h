//
// Created by 32827 on 2023/11/12.
//

#ifndef REYZ_YZ_FF_COVER_H
#define REYZ_YZ_FF_COVER_H
#include "stm32f1xx.h"
#include "yz_config.h"
#include "lib/fatfs/ff.h"
#include "lib/fatfs/diskio.h"

DSTATUS SDCARD_disk_status();
DSTATUS SDCARD_disk_initialize();
DSTATUS SDCARD_disk_read(BYTE *buff,LBA_t sector,UINT count);
DSTATUS SDCARD_disk_write(const BYTE *buff,LBA_t sector,UINT count);

#endif //REYZ_YZ_FF_COVER_H
