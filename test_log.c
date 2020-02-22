#include "tank_log_api.h"


#define my_log(fmt) tank_log_output(&mylog, fmt)



int main(int argv, char*args[])
{
    tank_log_t mylog;
    tank_log_init(&mylog, "logfile.log",2048,
                LOG_INFO_TIME|LOG_INFO_OUTAPP|LOG_INFO_FUNC|LOG_INFO_FILE|LOG_INFO_LINE|LOG_INFO_LEVEL
                );
    my_log("test write into log file\n");
    tank_log_output(&mylog, "test2\n");
    // tank_log_destructor(&mylog);
    return 0;
}