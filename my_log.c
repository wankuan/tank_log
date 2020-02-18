#include "my_log.h"
#include <sys/time.h>
#include <time.h>
#include <stdarg.h>


static log_status_t get_log_level_str(uint32_t level, uint8_t *p_level)
{
    if(p_level==NULL_PTR)
        return LOG_FAIL;
    strncpy(p_level, g_tank_log_level_str[level],1024);
    return LOG_SUCCESS;
}

static log_status_t get_current_time(uint8_t *p_timer)
{
    struct timeval tv;
    struct tm  *p;
    if(p_timer==NULL_PTR)
        return LOG_FAIL;
    gettimeofday(&tv, NULL);
    p = localtime(&tv.tv_sec);
    sprintf((char*)p_timer,"%04d-%02d-%02d %02d:%02d:%02d.%03lu", 1900+p->tm_year, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec/1000);
    return LOG_SUCCESS;
}
log_status_t tank_log_constructor(tank_log_t *tank_log_handler, uint8_t *file_name, uint32_t file_size)
{
    log_file_t *file_handler = NULL;
    FILE *pfile = NULL;
    file_handler = (tank_log_t*)malloc(sizeof(tank_log_t));
    if(file_handler==NULL_PTR)
        return LOG_FAIL;
    file_handler = &tank_log_handler->file_handler;

    file_handler->size = file_size;
    //file_handler->path = NULL_PTR;
    strncpy(file_handler->name, file_name, LOG_FILE_NAME_MAX_SIZE);
    pfile = fopen(file_handler->name, "a+");
    if(pfile==NULL_PTR)
        return LOG_FAIL;
    file_handler->FILE_handler = pfile;
    // TODO:文件路径后续加入
}
log_status_t tank_log_destructor(tank_log_t *tank_log_handler)
{
    fclose(tank_log_handler->file_handler.FILE_handler);
    free(tank_log_handler);
}
// #define LOG_INFO_TIME_WIDTH 30
// #define LOG_INFO_APP_WIDTH 30
// #define LOG_INFO_FUN_WIDTH 100
// #define LOG_INFO_FILE_WIDTH 100
// #define LOG_INFO_LINE_WIDTH 100
// #define LOG_INFO_LEVEL_WIDTH 30

log_status_t tank_log_write_file(tank_log_t *log_file_handler, uint8_t *write_buffer)
{
    FILE *fp = log_file_handler->file_handler.FILE_handler;
    if(fp==NULL_PTR)
        return LOG_FAIL;
    fprintf(fp, "%s", write_buffer);
    fflush(fp);
}

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

void write_buffer(const char *fmt, ...)
{
    FILE *file_fp;
    char fmt_str[1024];
    char time_buf[30];
    get_current_time(time_buf);
    snprintf(fmt_str, 1024, "[%s] ",time_buf);


    va_list ap;
    va_start(ap, fmt);
    vsnprintf(&fmt_str[strlen(fmt_str)], sizeof(fmt_str), fmt, ap);
    va_end(ap);

    printf("%s",fmt_str);
    file_fp = fopen("./test.log", "a");

    // 写入到日志文件中
    if (file_fp != NULL)
    {
        fprintf(file_fp, "%s", fmt_str);
        //fflush(file_fp);
        fclose(file_fp);
    }
}

       char *
       make_message(const char *fmt, ...)
       {
           int size = 0;
           char *p = NULL;
           va_list ap;

           /* Determine required size */

           va_start(ap, fmt);
           size = vsnprintf(p, size, fmt, ap);
           va_end(ap);
            //
           if (size < 0)
               return NULL;

           size++;             /* For '\0' */
           p = malloc(size);
           if (p == NULL)
               return NULL;

           va_start(ap, fmt);
           size = vsnprintf(p, size, fmt, ap);
           if (size < 0) {
               free(p);
               return NULL;
           }
           va_end(ap);

           return p;
       }

char* my_printf(char *fmt,...)
{
    va_list ap;
    va_start(ap, fmt);
    char *buf = malloc(3);
    int size = 3;
    printf("before size:%d\n",size);
    size = vsnprintf(buf, size, fmt, ap);
    printf("after size:%d\n",size);
    va_end(ap);
    return buf;
}