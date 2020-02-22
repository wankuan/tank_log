#ifndef __TANK_LOG_API_H__
#define __TANK_LOG_API_H__

#include "tank_pub_type.h"
#include "tank_log.h"

tank_status_t tank_log_init(tank_log_t *log_handler, char *filename, uint32_t size, log_info_type info_type, log_out_port port);
tank_status_t tank_log_denint(tank_log_t *log_handler);

#define tank_log_output(log_handler,app,level,fmt,...) \
    do{\
        char file_str[32];\
        char function_str[32];\
        char app_str[32];\
        snprintf(app_str, 32, "%s",app);\
        snprintf(file_str, 32, "%s",__FILE__);\
        snprintf(function_str, 32, "%s",__func__);\
        tank_log_write(log_handler,app_str, file_str, function_str,level,fmt,##__VA_ARGS__);\
    }while(0)


#endif