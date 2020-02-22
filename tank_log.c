#include "tank_log.h"
#include <sys/time.h>
#include <time.h>
#include <stdarg.h>


// static log_status_t get_log_level_str(uint32_t level, uint8_t *p_level)
// {
//     if(p_level==NULL_PTR)
//         return LOG_FAIL;
//     //strncpy(p_level, g_tank_log_level_str[level],1024);
//     return LOG_SUCCESS;
// }

// static log_status_t get_current_time(uint8_t *p_timer)
// {
//     struct timeval tv;
//     struct tm  *p;
//     if(p_timer==NULL_PTR)
//         return LOG_FAIL;
//     gettimeofday(&tv, NULL);
//     p = localtime(&tv.tv_sec);
//     sprintf((char*)p_timer,"%04d-%02d-%02d %02d:%02d:%02d.%03lu", 1900+p->tm_year, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec/1000);
//     return LOG_SUCCESS;
// }




log_status_t tank_log_constructor(tank_log_t *log_handler)
{
    FILE *pfile = NULL;
    log_file_t *file_handler = NULL;

    file_handler = &log_handler->file_handler;
    debug_printf("log file name:%s\n", file_handler->name);

    pfile = fopen(file_handler->name, "a+");
    if(pfile==NULL_PTR)
        return LOG_FAIL;
    file_handler->FILE_IO = pfile;
    debug_printf("success open file\n");
    return LOG_SUCCESS;
    // TODO:文件路径后续加入
}
log_status_t tank_log_destructor(tank_log_t *log_handler)
{
    log_handler->file_handler.size = 0;
    log_handler->file_handler.name[0] = '\0';
    fclose(log_handler->file_handler.FILE_IO);
}
// [时间][输出人][函数信息][文件信息][行号][日志等级]:日志
log_status_t tank_log_write(tank_log_t *log_handler, char *filename, char *fun, char *line, log_level_t level, char *content)
{
    write_file(log_handler->file_handler.FILE_IO, content);
}



// #define LOG_INFO_TIME_WIDTH 30
// #define LOG_INFO_APP_WIDTH 30
// #define LOG_INFO_FUN_WIDTH 100
// #define LOG_INFO_FILE_WIDTH 100
// #define LOG_INFO_LINE_WIDTH 100
// // #define LOG_INFO_LEVEL_WIDTH 30
// log_status_t tank_log_output(tank_log_t* log_file_handler,uint32_t info,uint32_t app, uint32_t level, char* fmt, ...)
// {
//     uint32_t log_info;
//     uint32_t write_len = 0;
//     uint8_t log_buffer[LOG_SINGLE_WIDTH];
//     log_info = info&LOG_INFO_MASK;
//     if(log_info&LOG_INFO_TIME){
//         uint8_t time_buffer[LOG_INFO_TIME_WIDTH];
//         get_current_time(time_buffer);
//         snprintf(&log_buffer[write_len], LOG_INFO_TIME_WIDTH, "[%s] ",time_buffer);
//         write_len = strlen(log_buffer);
//     }
//     if(log_info&LOG_INFO_OUTAPP){
//         uint8_t app_buffer[LOG_INFO_APP_WIDTH];
//         snprintf(&log_buffer[write_len], LOG_INFO_APP_WIDTH, "[%d] ",app);
//         write_len = strlen(log_buffer);
//     }
//     if(log_info&LOG_INFO_TIME){
//         snprintf(&log_buffer[write_len], LOG_INFO_TIME_WIDTH, "[%s] ",FUN);
//         write_len = strlen(log_buffer);
//     }
//     FILE *file_fp;
//     char time_buf[30];
//     get_current_time(time_buf);
//     va_list ap;
//     va_start(ap, fmt);
//     vsnprintf(&fmt_str[strlen(fmt_str)], sizeof(fmt_str), fmt, ap);
//     va_end(ap);
// }

static log_status_t write_file(FILE *fp, char *buffer)
{
    if (fp == NULL_PTR){
        return LOG_FAIL;
    }
    fprintf(fp, "%s", buffer);
    fflush(fp);
    return LOG_SUCCESS;
}

//        char *
//        make_message(const char *fmt, ...)
//        {
//            int size = 0;
//            char *p = NULL;
//            va_list ap;

//            /* Determine required size */

//            va_start(ap, fmt);
//            size = vsnprintf(p, size, fmt, ap);
//            va_end(ap);
//             //
//            if (size < 0)
//                return NULL;

//            size++;             /* For '\0' */
//            p = malloc(size);
//            if (p == NULL)
//                return NULL;

//            va_start(ap, fmt);
//            size = vsnprintf(p, size, fmt, ap);
//            if (size < 0) {
//                free(p);
//                return NULL;
//            }
//            va_end(ap);

//            return p;
//        }

// char* my_printf(char *fmt,...)
// {
//     va_list ap;
//     va_start(ap, fmt);
//     char *buf = malloc(3);
//     int size = 3;
//     printf("before size:%d\n",size);
//     size = vsnprintf(buf, size, fmt, ap);
//     printf("after size:%d\n",size);
//     va_end(ap);
//     return buf;
// }