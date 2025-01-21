#ifndef GUNC_file_logger_h
#define GUNC_file_logger_h

#include <stdio.h>
#include <stdarg.h>

#include "./iLog.h"

int Gunc_File_iLog_raw(FILE *self,
	const char *s,
	int arg_count,
	va_list arg_list
);
int Gunc_File_iLog_pin(FILE *self,
	const char *file_name,
	const char *function_name,
	int line_number,
	const char *type
);

static inline int Gunc_File_as_iLog(FILE *self, struct Gunc_iLog *log) {
	return Gunc_iLog_init(log, self,
		(int(*)(void*, const char*, int, va_list))Gunc_File_iLog_raw,
		(int(*)(void*, const char*, const char*, int, const char*))Gunc_File_iLog_pin
	);
}

#endif
