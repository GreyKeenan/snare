
#include "gunc/iLog.h"

extern struct Gunc_iLog *global_logger;

#define log_msg(...) Gunc_iLog_msg(global_logger, __VA_ARGS__)
#define log_err(...) Gunc_iLog_err(global_logger, __VA_ARGS__)
#define log_TODO(...) Gunc_iLog_TODO(global_logger, __VA_ARGS__)

#define log_raw(...) Gunc_iLog_raw(global_logger, __VA_ARGS__)
#define log_pin(...) Gunc_iLog_pin(global_logger, __VA_ARGS__)

#define log_say(...) Gunc_iLog_msg(global_logger, "INFO", __VA_ARGS__)
