#ifndef __MY_LOG_H__
#define __MY_LOG_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LOG_FILE_NAME_MAX_SIZE 256
#define LOG_FILE_PATH_MAX_SIZE 256
#define LOG_FILE_MAX_SIZE (1024*1024)  // 1M byte
// 日志格式 可配置 6种信息
//[时间][输出人][函数信息][文件信息][行号][日志等级]:日志

#define LOG_SINGLE_WIDTH 1024

#define LOG_INFO_TIME_WIDTH 30
#define LOG_INFO_APP_WIDTH 30
#define LOG_INFO_FUN_WIDTH 100
#define LOG_INFO_FILE_WIDTH 100
#define LOG_INFO_LINE_WIDTH 100
#define LOG_INFO_LEVEL_WIDTH 30
// #define LOG_RECORD(logLev, fmt, ...)
//     printf(fmt, __VA_ARGS__)


#ifndef NULL
#define NULL 0
#endif
#ifndef NULL_PTR
#define NULL_PTR ((void*)0)
#endif
#ifndef NULL_BYTE
#define NULL_BYTE (uint8_t)0xFF
#endif
#ifndef NULL_BYTE_WORD
#define NULL_BYTE_WORD (uint16_t)0xFFFF
#endif
#ifndef NULL_BYTE_DWORD
#define NULL_BYTE_DWORD (uint32_t)0xFFFFFFFF
#endif


#define LOG_INFO_MASK (uint32_t)(0x0000003F)

#define LOG_MAX_LEVEL_SIZE (sizeof(g_tank_log_level_str)/sizeof(g_tank_log_level_str[0]))

typedef enum _log_status_t{
    LOG_SUCCESS = 0,
    LOG_FAIL = 1,
}log_status_t;

typedef enum _log_level_t{
    LEVEL_DEBUG = 0,
    LEVEL_INFO = 1,
    LEVEL_NOTIFICATION = 2,
    LEVEL_WARNING = 3,
    LEVEL_ERROR = 4,
    LEVEL_CRITICAL = 5,
    LEVEL_ALERT = 6,
    LEVEL_EMERGENCY = 7
}log_level_t;

uint8_t* g_tank_log_level_str[] = {
        "LEVEL_DEBUG",
        "LEVEL_INFO",
        "LEVEL_NOTIFICATION",
        "LEVEL_WARNING",
        "LEVEL_ERROR",
        "LEVEL_CRITICAL",
        "LEVEL_ALERT",
        "LEVEL_EMERGENCY"
};


#define LOG_INFO_TIME    (uint32_t)0x01<<0,
#define LOG_INFO_OUTAPP  (uint32_t)0X01<<1,
#define LOG_INFO_FUNC    (uint32_t)0X01<<2,
#define LOG_INFO_FILE    (uint32_t)0X01<<3,
#define LOG_INFO_LINE    (uint32_t)0X01<<4,
#define LOG_INFO_LEVEL   (uint32_t)0X01<<5

typedef struct _log_info_t{
    
    log_file_t file_handler;
}log_info_t;

typedef struct _log_file_t{
    FILE* FILE_handler;
    uint8_t name[LOG_FILE_NAME_MAX_SIZE];
    uint8_t path[LOG_FILE_PATH_MAX_SIZE];
    uint32_t size;
}log_file_t;


typedef struct _tank_log_t{
    log_file_t file_handler;
}tank_log_t, *tank_log_handler;




log_status_t tank_log_constructor(tank_log_t *tank_log_handler, uint8_t *file_name, uint32_t file_size);
log_status_t tank_log_destructor(tank_log_t* log_file_handler);
log_status_t tank_log_output(tank_log_t* log_file_handler,uint32_t info,uint32_t app, uint32_t level, char* fmt, ...);

static log_status_t get_current_time_str(uint8_t *p_timer);
static log_status_t get_log_level_str(uint32_t level, uint8_t *p_level);


// void write_buffer(const char *fmt, ...);
// char *make_message(const char *fmt, ...);
// #define LOG_S(fmt, ...) write_buffer(fmt,__VA_ARGS__)


// char* my_printf(char *fmt,...);

// #define LOG_S(fmt, ...)\
//     do{\
//         char fmt_str[1024];\
//         char time_buf[30];\
//         get_current_time(time_buf);\
//         snprintf(fmt_str,1024,"%s %s",time_buf,fmt,__VA_ARGS__);\
//         printf("%s\n",fmt_str);\
//     }while(0)



#endif