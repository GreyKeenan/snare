
#include "./diagram.h"
#include "gu/echo.h"

#include "SDL2/SDL.h"
#include <unistd.h>
#include <stdlib.h>


void atoll_DEBUG_drawcircle(SDL_Renderer *rdr, int cx, int cy, int r)
{ //https://stackoverflow.com/questions/38334081/how-to-draw-circles-arcs-and-vector-graphics-in-sdl
   const int diameter = (r * 2);

   int x = (r - 1);
   int y = 0;
   int tx = 1;
   int ty = 1;
   int error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(rdr, cx + x, cy - y);
      SDL_RenderDrawPoint(rdr, cx + x, cy + y);
      SDL_RenderDrawPoint(rdr, cx - x, cy - y);
      SDL_RenderDrawPoint(rdr, cx - x, cy + y);
      SDL_RenderDrawPoint(rdr, cx + y, cy - x);
      SDL_RenderDrawPoint(rdr, cx + y, cy + x);
      SDL_RenderDrawPoint(rdr, cx - y, cy - x);
      SDL_RenderDrawPoint(rdr, cx - y, cy + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}




/*heap*/ struct gu_echo *atoll_DEBUG_display(struct atoll_diagram diagram[static 1], double scale, double offset)
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

	for (unsigned int i = 0; i < diagram->hedges_length; i += 2) {

		e = SDL_SetRenderDrawColor(renderer,
			(rand() & 0xff) | 0x20,
			(rand() & 0xff) | 0x20,
			(rand() & 0xff) | 0x20,
			0xff);
		// if (e < 0) { }

		if (diagram->hedges[i].head == atoll_INDULL
			|| diagram->hedges[i].tail == atoll_INDULL
		) {

			atoll_DEBUG_drawcircle(renderer,
				offset + scale * (diagram->sites[diagram->hedges[i].cell].x + diagram->sites[diagram->hedges[i^1].cell].x) / 2,
				offset + scale * (diagram->sites[diagram->hedges[i].cell].y + diagram->sites[diagram->hedges[i^1].cell].y) / 2,
				2
			);

			continue;
		}

		e = SDL_RenderDrawLine(renderer,
			offset + scale * diagram->vertices[diagram->hedges[i].head].x,
			offset + scale * diagram->vertices[diagram->hedges[i].head].y,
			offset + scale * diagram->vertices[diagram->hedges[i].tail].x,
			offset + scale * diagram->vertices[diagram->hedges[i].tail].y
		);
		// if (e) { }
	}



	e = SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	// if (e < 0)
	for (unsigned int i = 0; i < diagram->site_count; ++i) {
		atoll_DEBUG_drawcircle(renderer,
			offset + scale * diagram->sites[i].x,
			offset + scale * diagram->sites[i].y,
			4
		);
		/*
		e = SDL_RenderDrawPoint(renderer,
			scale * diagram->sites[i].x,
			scale * diagram->sites[i].y);
		*/
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
