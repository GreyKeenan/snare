#include "./file_logger.h"

#include <stdbool.h>

int Gunc_File_iLog_raw(FILE *self,
	const char *s,
	int _,
	va_list arg_list
) {
	(void)_;
	vfprintf(self, s, arg_list);
	return 0;
}
int Gunc_File_iLog_pin(FILE *self,
	const char *file_name,
	const char *function_name,
	int line_number,
	const char *type
) {
	fprintf(self, "\n\n%s:\n[%04d] %s\n%s()\n\n",
		type, line_number, file_name, function_name);
	return 0;
}
