#include "tank_log_api.h"


tank_status_t tank_log_init(tank_log_t *log_handler, char *filename, uint32_t size, log_info_type info_type)
{
    log_status_t status;
    log_handler->file_handler.size = size;
    log_handler->info_handler.type = info_type;
    strncpy(log_handler->file_handler.name, filename, LOG_FILE_NAME_MAX_SIZE);
    status = tank_log_constructor(log_handler);
    if (status != LOG_SUCCESS){
        return TANK_FAIL;
    }
    return TANK_SUCCESS;
}
tank_status_t tank_log_denint(tank_log_t *log_handler)
{
    log_status_t status;
    status = tank_log_destructor(log_handler);
    if (status == LOG_SUCCESS){
        return TANK_SUCCESS;
    }else{
        return TANK_FAIL;
    }
}

