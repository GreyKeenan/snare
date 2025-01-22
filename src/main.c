
#include "log.h"

#include "carrie/boint.h"
#include "carrie/carrie.h"

#include "bagel/xorshiftr128plus.h"

#include "gunc/file_logger.h"

#include "SDL2/SDL.h"

#include <stdlib.h>

struct Gunc_iLog logger = {0};
struct Gunc_iLog *global_logger = &logger;


int draw_SkewGrid(SDL_Renderer *renderer, const struct Carrie_SkewGrid *sg);


int main(int argc, const char **argv)
{
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

	/*
	e = SDL_RenderDrawLine(renderer, 0, 0, 500, 500);
	if (e < 0) {
		log_err("failed to draw line: %d", e);
		goto fin;
	}
	*/


	struct Bagel_xorshiftr128plus rstate = Bagel_xorshiftr128plus_seed(1);

	uint64_t data64[8] = {
		Bagel_xorshiftr128plus_run(&rstate),
		Bagel_xorshiftr128plus_run(&rstate),
		Bagel_xorshiftr128plus_run(&rstate),
		Bagel_xorshiftr128plus_run(&rstate),
		Bagel_xorshiftr128plus_run(&rstate),
		Bagel_xorshiftr128plus_run(&rstate),
		Bagel_xorshiftr128plus_run(&rstate),
		Bagel_xorshiftr128plus_run(&rstate)
	};

	struct Carrie_SkewGrid sg = {0};
	e = Carrie_SkewGrid_init(&sg, (unsigned char *)data64, 8, 8, 8);
	if (e) {
		log_err("unable to init skewgrid: %d", e);
		goto fin;
	}

	e = draw_SkewGrid(renderer, &sg);
	log_say("skew grid ended with status: %d", e);

	SDL_RenderPresent(renderer);



	for (int i = 0; i != -1; ++i) {
	}



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

int draw_SkewGrid(SDL_Renderer *renderer, const struct Carrie_SkewGrid *sg)
{

	int e = 0;

	struct Chalk_Point a = {0};
	struct Chalk_Point b = {0};

	for (unsigned int i = 0; i < sg->width * sg->height; ++i) {
		log_say("i: %d", i);
		e = Carrie_SkewGrid_index_i(sg, i, &a);
		if (e) {
			log_err("skewgrid index failed (a1): %d", e);
			return 1;
		}

		e = Carrie_SkewGrid_index_i(sg, i + sg->width, &b); //can serve as a for next
		if (e) {
			log_err("skewgrid index failed (b1): %d / index: %d width: %d height: %d", e, i, sg->width, sg->height);
			//return 1;
			continue;
		}

		e = SDL_RenderDrawLine(renderer, a.x + 32, a.y + 32, b.x + 32, b.y + 32);
		if (e < 0) {
			log_err("failed to draw line: %d", e);
			return 2;
		}

		e = Carrie_SkewGrid_index_i(sg, i + 1, &b); //can serve as a for next
		if (e) {
			log_err("skewgrid index failed (b2): %d", e);
			//return 1;
			continue;
		}

		e = SDL_RenderDrawLine(renderer, a.x + 32, a.y + 32, b.x + 32, b.y + 32);
		if (e < 0) {
			log_err("failed to draw line: %d", e);
			return 2;
		}
	}

	return 0;
}
