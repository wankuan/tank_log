#ifndef __TANK_LOG_API_H__
#define __TANK_LOG_API_H__

#include "tank_pub_type.h"
#include "tank_log.h"

tank_status_t tank_log_init(tank_log_t *log_handler, char *filename, uint32_t size, log_info_type info_type);
tank_status_t tank_log_denint(tank_log_t *log_handler);

#define tank_log_output(log_handler, fmt, ...) \
    do{\
        char fmt_str[1024];\
        snprintf(fmt_str,1024,"File:%s, Line:%04d, "fmt"",__FILE__,__LINE__, ##__VA_ARGS__);\
        tank_log_write(log_handler, NULL, NULL, NULL, 0, fmt_str);\
    }while(0)

// #define LOG_S(fmt, ...)\
//     do{\
//         char fmt_str[1024];\
//         char time_buf[30];\
//         get_current_time(time_buf);\
//         snprintf(fmt_str,1024,"%s %s",time_buf,fmt,__VA_ARGS__);\
//         printf("%s\n",fmt_str);\
//     }while(0)

#endif