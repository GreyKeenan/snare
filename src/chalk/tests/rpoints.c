
#include "../random.h"

#include "../../bagel/bagel.h"
#include "../../bagel/xorshiftr128plus.h"

#include "SDL2/SDL.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

int main(int argc, char **argv)
{

	(void)argc;
	(void)argv;

	int e = 0;

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;


	e = SDL_InitSubSystem(SDL_INIT_VIDEO);
	if (e) {
		goto fin;
	}

	window = SDL_CreateWindow("random points in convex polygon",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		500, 500,
		0 /*flags*/
	);
	if (window == NULL) {
		e = 1;
		goto fin;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL) {
		e = 1;
		goto fin;
	}


	/*
	#define VERTICES 4
	struct Chalk_Point cvpoly[VERTICES] = {
		(struct Chalk_Point) {0, 0},
		(struct Chalk_Point) {300, 0},
		(struct Chalk_Point) {300, 300},
		(struct Chalk_Point) {0, 300}
	};
	*/
	#define VERTICES 6
	struct Chalk_Point cvpoly[VERTICES] = {
		(struct Chalk_Point) {50, 50},
		(struct Chalk_Point) {100, 75},
		(struct Chalk_Point) {200, 150},
		(struct Chalk_Point) {150, 200},
		(struct Chalk_Point) {125, 230},
		(struct Chalk_Point) {75, 175}
	};

	#define POINTS 100
	struct Chalk_Point random_points[POINTS] = {0};
	
	struct Bagel_xorshiftr128plus rand = Bagel_xorshiftr128plus_seed(1);


	e = Chalk_randomPoints_cvpoly(cvpoly, VERTICES, random_points, POINTS, &rand);
	fprintf(stderr, "randomPoints_cvpoly() exit status: %d\n", e);
	if (e) {
		goto fin;
	}


	SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);

	e = SDL_RenderDrawLine(renderer, cvpoly[0].x, cvpoly[0].y, cvpoly[VERTICES - 1].x, cvpoly[VERTICES - 1].y);
	if (e) {
		fprintf(stderr, "drawline error: %d. Continuing.\n", e);
	}
	for (int i = 1; i < VERTICES; ++i) {
		e = SDL_RenderDrawLine(renderer, cvpoly[i - 1].x, cvpoly[i - 1].y, cvpoly[i].x, cvpoly[i].y);
		if (e) {
			fprintf(stderr, "drawline error: %d. Continuing.\n", e);
		}
	}
	e = SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
	if (e < 0) {
		fprintf(stderr, "failed to change to red.\n");
	}
	for (int i = 0; i < POINTS; ++i) {
		printf("plotting point (%d, %d)\n", random_points[i].x, random_points[i].y);
		e = SDL_RenderDrawPoint(renderer, random_points[i].x, random_points[i].y);
		if (e) {
			fprintf(stderr, "failed to plot point %d\n", i);
		}
	}

	SDL_RenderPresent(renderer);



	for (uint32_t i = 1; i > 0; ++i) {
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
