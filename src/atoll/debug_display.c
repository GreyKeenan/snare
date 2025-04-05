
#include "./diagram.h"
#include "gu/echo.h"

#include "SDL2/SDL.h"
#include <unistd.h>


/*heap*/ struct gu_echo *atoll_DEBUG_display(struct atoll_diagram diagram[static 1], double scale)
{

	int e = 0;
	/*heap*/ struct gu_echo *echo = NULL;

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	e = SDL_InitSubSystem(SDL_INIT_VIDEO);
	if (e) {
		echo = gu_echo_new(e, "unable to init SDL");
		goto fin;
	}

	window = SDL_CreateWindow("hopefully a voronoi diagram",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		500, 500,
		0 /*flags*/
	);
	if (window == NULL) {
		echo = gu_echo_new(0, "unable to create window");
		goto fin;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL) {
		echo = gu_echo_new(0, "unable to create renderer");
		goto fin;
	}

	// ==========

	e = SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	// if (e < 0) { }
	for (unsigned int i = 0; i < diagram->hedges_length; i += 2) {

		if (diagram->hedges[i].head == atoll_INDULL
			|| diagram->hedges[i].tail == atoll_INDULL
		) {
			continue;
		}

		e = SDL_RenderDrawLine(renderer,
			scale * diagram->vertices[diagram->hedges[i].head].x,
			scale * diagram->vertices[diagram->hedges[i].head].y,
			scale * diagram->vertices[diagram->hedges[i].tail].x,
			scale * diagram->vertices[diagram->hedges[i].tail].y
		);
		// if (e) { }
	}



	e = SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
	// if (e < 0)
	for (unsigned int i = 0; i < diagram->site_count; ++i) {
		e = SDL_RenderDrawPoint(renderer,
			scale * diagram->sites[i].x,
			scale * diagram->sites[i].y);
		/*if (e) {
			echo = gu_echo_new(0, "failed to draw point #%u", i);
			goto fin;
		}*/
	}


	SDL_RenderPresent(renderer);
	sleep(30);


	// ==========

	fin:

	if (renderer != NULL) SDL_DestroyRenderer(renderer);
	if (window != NULL) SDL_DestroyWindow(window);

	SDL_Quit();

	return echo;
}
