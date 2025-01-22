
#include "log.h"

#include "gunc/file_logger.h"

#include "SDL2/SDL.h"

#include <stdlib.h>

struct Gunc_iLog logger = {0};
struct Gunc_iLog *global_logger = &logger;

int main(int argc, const char **argv) {

	(void)argc;
	(void)argv;

	int e = 0;

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	// initialize global logger
	e = Gunc_File_as_iLog(stderr, global_logger);
	if (e) {
		fprintf(stderr, "UNABLE TO INIT LOGGER. e(%d) ABORTING.\n", e);
		return 1;
	}


	e = SDL_InitSubSystem(SDL_INIT_VIDEO);
	if (e) {
		log_err("Unable to init SDL: %d", e);
		goto fin;
	}

	window = SDL_CreateWindow("Warped Grid!",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		500, 500,
		0 /*flags*/
	);
	if (window == NULL) {
		log_err("Unable to create window.");
		e = 1;
		goto fin;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL) {
		log_err("Unable to create renderer.");
		e = 1;
		goto fin;
	}


	e = SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	if (e < 0) {
		log_err("failed to set draw color: %d", e);
		goto fin;
	}
	e = SDL_RenderDrawLine(renderer, 0, 0, 500, 500);
	if (e < 0) {
		log_err("failed to draw line: %d", e);
		goto fin;
	}
	SDL_RenderPresent(renderer);



	//for (int i = 0; i != -1; ++i) {
	//}



	fin:

	if (renderer != NULL) {
		SDL_DestroyRenderer(renderer);
	}
	if (window != NULL) {
		SDL_DestroyWindow(window);
	}

	SDL_Quit();

	return (_Bool)e;
}
