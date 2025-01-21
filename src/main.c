
#include "gunc/file_logger.h"

#include "log.h"

struct Gunc_iLog logger = {0};
struct Gunc_iLog *global_logger = &logger;

//int main(int argc, const char **argv) {
int main() {

	int e = 0;

	// initialize global logger
	e = Gunc_File_as_iLog(stderr, global_logger);
	if (e) {
		fprintf(stderr, "UNABLE TO INIT LOGGER. e(%d) ABORTING.\n", e);
		return 1;
	}

	log_say("Hello World!");

	return (_Bool)e;
}
