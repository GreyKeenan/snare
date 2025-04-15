#include "./debug_paint.h"

#include "./diagram.h"
#include "./coast.h"

#include "./breakpoint.h"

#include "gumetry/parabola.h"

#include "gu/gu.h"

#include "SDL2/SDL.h"
#include <unistd.h>
#include <stdlib.h>


#define GRAY 0x60, 0x60, 0x60, 0xff
#define WHITE 0xff, 0xff, 0xff, 0xff
#define BLACK 0, 0, 0, 0xff
#define MINCOL 0x20

#define ARC_C 0x00, 0xff, 0xff, 0xff
#define CARC_C 0xff, 0x00, 0x00, 0xff
#define CIRC_C GRAY
#define DX_C GRAY
#define HIGH_C 0, 0xff, 0, 0xff
#define SITE_C WHITE
#define INHEDGE_C 0x00,0x40,0x40,0xff

#define R atoll_DEBUG_renderer
#define W atoll_DEBUG_window

#define SCALE atoll_DEBUG_scale
#define OFFSET atoll_DEBUG_offset

SDL_Renderer *atoll_DEBUG_renderer = NULL;
SDL_Window *atoll_DEBUG_window = NULL;

double atoll_DEBUG_scale = 1;
double atoll_DEBUG_offset = 0;



void atoll_DEBUG_drawarc(int dx, int fx, int fy, int left, int right);
void atoll_DEBUG_drawcircle(int cx, int cy, int r);
int atoll_DEBUG_paint_highlight(double directix[static 1], struct atoll_diagram *diagram, struct atoll_coast *coast);
void atoll_DEBUG_paint_diagram(struct atoll_diagram *diagram);
void atoll_DEBUG_paint_coast(struct atoll_diagram *diagram, struct atoll_coast *coast, double *directix);


#define LOWERX 0x01
#define GREATERX 0x02
#define LOWERY 0x04
#define GREATERY 0x08
uint8_t atoll_DEBUG_whichSide(struct atoll_podouble a, struct atoll_podouble b, struct atoll_podouble p)
{
	if (a.x - b.x == 0) return (p.x < a.x)? LOWERX:GREATERX; //a->b is vertical

	const double m = (a.y - b.y) / (a.x - b.x);
	if (m == 0) return (p.y < a.y)? LOWERY:GREATERY; //a->b is horizontal

	const double bb = a.y - m*a.x;

	uint8_t out = 0;
	const double y = m*p.x + bb;
	out |= (p.y < y)? LOWERY:GREATERY;
	const double x = (y - bb)/m;
	out |= (p.x < x)? LOWERX:GREATERX;

	return out;
}


void atoll_DEBUG_setscale(double scale, double offset)
{
	SCALE = scale;
	OFFSET = offset;
}


int atoll_DEBUG_initSDL(void)
{
	int e = 0;

	e = SDL_InitSubSystem(SDL_INIT_VIDEO);
	if (e) return e;

	W = SDL_CreateWindow("hopefully a voronoi diagram",
		//SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		0, 0,
		500, 500,
		0 /*flags*/
	);
	if (W == NULL) return 1;

	R = SDL_CreateRenderer(W, -1, 0);
	if (R == NULL) return 1;

	return 0;
}
void atoll_DEBUG_endSDL(void)
{
	if (R != NULL) SDL_DestroyRenderer(R);
	if (W != NULL) SDL_DestroyWindow(W);
	SDL_Quit();
}

void atoll_DEBUG_paint(struct atoll_diagram *diagram, struct atoll_coast *coast)
{
	if (R == NULL || W == NULL) return;

	SDL_SetRenderDrawColor(R, BLACK);
	SDL_RenderClear(R);

	double dx = 0;
	int directixExists = atoll_DEBUG_paint_highlight(&dx, diagram, coast);

	atoll_DEBUG_paint_diagram(diagram);
	atoll_DEBUG_paint_coast(diagram, coast,
		directixExists? &dx:NULL
	);


	SDL_RenderPresent(R);

	if (atoll_DEBUG_wait() == EOF) exit(0);
}

int atoll_DEBUG_paint_highlight(double directix[static 1], struct atoll_diagram *diagram, struct atoll_coast *coast)
{
	if (coast == NULL || diagram == NULL) return 0;
	if (coast->nextSite >= diagram->site_count && coast->circles_length == 0) {
		return 0;
	}
	SDL_SetRenderDrawColor(R, DX_C);
	if (coast->nextSite >= diagram->site_count) {
	} else if (coast->circles_length == 0
		|| diagram->sites[coast->nextSite].y
		< coast->circles[coast->circles_length - 1].center.y
		+ coast->circles[coast->circles_length - 1].radius
	) {
		*directix = diagram->sites[coast->nextSite].y;

		SDL_RenderDrawLine(R,
			0,
			OFFSET + SCALE * (*directix),
			500,
			OFFSET + SCALE * (*directix)
		);
		SDL_SetRenderDrawColor(R, HIGH_C);
		atoll_DEBUG_drawcircle(
			OFFSET + SCALE * diagram->sites[coast->nextSite].x,
			OFFSET + SCALE * diagram->sites[coast->nextSite].y,
			9
		);
		
		return 1;
	}

	*directix = coast->circles[coast->circles_length - 1].center.y
		+ coast->circles[coast->circles_length - 1].radius;

	SDL_RenderDrawLine(R,
		0,
		OFFSET + SCALE * (*directix),
		500,
		OFFSET + SCALE * (*directix)
	);
	SDL_SetRenderDrawColor(R, HIGH_C);
	//atoll_DEBUG_drawcircle(
	//	OFFSET + SCALE * coast->circles[coast->circles_length - 1].center.x,
	//	OFFSET + SCALE * coast->circles[coast->circles_length - 1].center.y,
	//	SCALE * coast->circles[coast->circles_length - 1].radius
	//);
	atoll_DEBUG_drawcircle(
		OFFSET + SCALE * coast->circles[coast->circles_length - 1].center.x,
		OFFSET + SCALE * coast->circles[coast->circles_length - 1].center.y,
		4
	);
	atoll_DEBUG_drawcircle(
		OFFSET + SCALE * coast->circles[coast->circles_length - 1].center.x,
		OFFSET + SCALE *
			(coast->circles[coast->circles_length - 1].center.y
			+ coast->circles[coast->circles_length - 1].radius),
		4
	);

	return 1;
}

void atoll_DEBUG_paint_hedge(struct atoll_diagram *diagram, unsigned int hedge)
{
	if (R == NULL || W == NULL || diagram == NULL) return;
	if (hedge >= diagram->hedges_length) return;

	if (diagram->hedges[hedge].head == atoll_INDULL
		|| diagram->hedges[hedge].tail == atoll_INDULL
	) return;


	const double mix = (diagram->vertices[diagram->hedges[hedge].head].x
	+ diagram->vertices[diagram->hedges[hedge].tail].x) / 2;
	const double miy = (diagram->vertices[diagram->hedges[hedge].head].y
	+ diagram->vertices[diagram->hedges[hedge].tail].y) / 2;
	SDL_RenderDrawLine(R,
		OFFSET + SCALE * mix,
		OFFSET + SCALE * miy,
		OFFSET + SCALE * diagram->sites[diagram->hedges[hedge].cell].x,
		OFFSET + SCALE * diagram->sites[diagram->hedges[hedge].cell].y
	);
	return;


	uint8_t ws = atoll_DEBUG_whichSide(
		diagram->vertices[diagram->hedges[hedge].head],
		diagram->vertices[diagram->hedges[hedge].tail],
		diagram->sites[diagram->hedges[hedge].cell]
	);

	int offx = 0;
	int offy = 0;
	
	#define OFF 2.5

	if (ws & LOWERX) offx -= OFF;
	if (ws & GREATERX) offx += OFF;
	if (ws & LOWERY) offy -= OFF;
	if (ws & GREATERY) offy += OFF;
	// TODO to be accurate these should be relative to the perp slope

	#undef OFF

	SDL_RenderDrawLine(R,
		offx + OFFSET + SCALE * diagram->vertices[diagram->hedges[hedge].head].x,
		offy + OFFSET + SCALE * diagram->vertices[diagram->hedges[hedge].head].y,
		offx + OFFSET + SCALE * diagram->vertices[diagram->hedges[hedge].tail].x,
		offy + OFFSET + SCALE * diagram->vertices[diagram->hedges[hedge].tail].y
	);

}

void atoll_DEBUG_paint_site(struct atoll_diagram *diagram, unsigned int site)
{
	if (R == NULL || W == NULL || diagram == NULL) return;
	if (site >= diagram->site_count) return;

	unsigned int h = diagram->cells[site];
	if (h == atoll_INDULL) return;

	SDL_SetRenderDrawColor(R,
		(rand() & 0x7f) | MINCOL,
		( 0     & 0x7f) | MINCOL,
		(rand() & 0x7f) | MINCOL,
		0xff);

	while (1) {
		atoll_DEBUG_paint_hedge(diagram, h);
		h = diagram->hedges[h].next;

		if (h == diagram->cells[site]) break;
	}
	
}

void atoll_DEBUG_paint_diagram(struct atoll_diagram *diagram)
{
	if (R == NULL || W == NULL || diagram == NULL) return;

	//SDL_SetRenderDrawColor(R, SITE_C);
	for (unsigned int i = 0; i < diagram->site_count; ++i) {
		atoll_DEBUG_paint_site(diagram, i);
		atoll_DEBUG_drawcircle(
			OFFSET + SCALE * diagram->sites[i].x,
			OFFSET + SCALE * diagram->sites[i].y,
			7
		);
	}

	for (unsigned int i = 0; i < diagram->hedges_length; i += 2) {

		/*
		SDL_SetRenderDrawColor(R,
			(rand() & 0xff) | MINCOL,
			(rand() & 0xff) | MINCOL,
			(rand() & 0xff) | MINCOL,
			0xff);
		*/
		SDL_SetRenderDrawColor(R, WHITE);

		if (diagram->hedges[i].head == atoll_INDULL
			|| diagram->hedges[i].tail == atoll_INDULL
		) {

			atoll_DEBUG_drawcircle(
				OFFSET + SCALE * (diagram->sites[diagram->hedges[i].cell].x + diagram->sites[diagram->hedges[i^1].cell].x) / 2,
				OFFSET + SCALE * (diagram->sites[diagram->hedges[i].cell].y + diagram->sites[diagram->hedges[i^1].cell].y) / 2,
				3
			);

			SDL_SetRenderDrawColor(R, INHEDGE_C);
			SDL_RenderDrawLine(R,
				OFFSET + SCALE * diagram->sites[diagram->hedges[i].cell].x,
				OFFSET + SCALE * diagram->sites[diagram->hedges[i].cell].y,
				OFFSET + SCALE * diagram->sites[diagram->hedges[i^1].cell].x,
				OFFSET + SCALE * diagram->sites[diagram->hedges[i^1].cell].y
			);

			continue;
		}

		SDL_RenderDrawLine(R,
			OFFSET + SCALE * diagram->vertices[diagram->hedges[i].head].x,
			OFFSET + SCALE * diagram->vertices[diagram->hedges[i].head].y,
			OFFSET + SCALE * diagram->vertices[diagram->hedges[i].tail].x,
			OFFSET + SCALE * diagram->vertices[diagram->hedges[i].tail].y
		);
	}
}

void atoll_DEBUG_paint_coast(struct atoll_diagram *diagram, struct atoll_coast *coast, double *directix)
{
	if (R == NULL || W == NULL || diagram == NULL || coast == NULL) return;

	SDL_SetRenderDrawColor(R, CIRC_C);
	for (unsigned int i = 0; i < coast->circles_length; ++i) {
		atoll_DEBUG_drawcircle(
			OFFSET + SCALE * coast->circles[i].center.x,
			OFFSET + SCALE * coast->circles[i].center.y,
			SCALE * coast->circles[i].radius
		);
		atoll_DEBUG_drawcircle(
			OFFSET + SCALE * coast->circles[i].center.x,
			OFFSET + SCALE * coast->circles[i].center.y,
			3
		);
		atoll_DEBUG_drawcircle(
			OFFSET + SCALE * coast->circles[i].center.x,
			OFFSET + SCALE *
				(coast->circles[i].center.y
				+ coast->circles[i].radius),
			3
		);
	}

	//TODO draw the parabolas ugh
	if (directix == NULL) return;
	SDL_SetRenderDrawColor(R, ARC_C);
	struct atoll_podouble left = {0};
	struct atoll_podouble right = {0};
	for (unsigned int j = 0; j < coast->foci_length; ++j) {

		SDL_SetRenderDrawColor(R, ARC_C);
		for (unsigned int i = 0; i < coast->circles_length; ++i) {
			if (coast->circles[i].arc == j) {

				/*
				left = atoll_breakpoint(
					*directix,
					diagram->sites[coast->foci[j - 1]],
					diagram->sites[coast->foci[j]]
				);
				right = atoll_breakpoint(
					*directix,
					diagram->sites[coast->foci[j]],
					diagram->sites[coast->foci[j + 1]]
				);

				SDL_SetRenderDrawColor(R, 0x00, 0xff, 0x00, 0xff);
				SDL_RenderDrawLine(R,
					OFFSET + SCALE * coast->circles[i].center.x,
					OFFSET + SCALE * coast->circles[i].center.y,
					OFFSET + SCALE * left.x,
					OFFSET + SCALE * left.y
				);
				SDL_RenderDrawLine(R,
					OFFSET + SCALE * coast->circles[i].center.x,
					OFFSET + SCALE * coast->circles[i].center.y,
					OFFSET + SCALE * right.x,
					OFFSET + SCALE * right.y
				);
				*/

				SDL_SetRenderDrawColor(R, CARC_C);
				break;
			}
		}

		if (j == 0) {
			left.x = (0.0 - OFFSET) / SCALE;
		} else {
			left = atoll_breakpoint(
				*directix,
				diagram->sites[coast->foci[j - 1]],
				diagram->sites[coast->foci[j]]
			);

			atoll_DEBUG_drawcircle(
				OFFSET + SCALE * left.x,
				OFFSET + SCALE * left.y,
				2
			);
		}
		if (j == coast->foci_length - 1) {
			right.x = (500.0 - OFFSET) / SCALE;
		} else {
			right = atoll_breakpoint(
				*directix,
				diagram->sites[coast->foci[j]],
				diagram->sites[coast->foci[j + 1]]
			);
		}
		atoll_DEBUG_drawarc(
			OFFSET + SCALE * (*directix),
			OFFSET + SCALE * diagram->sites[coast->foci[j]].x,
			OFFSET + SCALE * diagram->sites[coast->foci[j]].y,
			OFFSET + SCALE * left.x,
			OFFSET + SCALE * right.x
		);
	}


}




void atoll_DEBUG_drawarc(int dx, int fx, int fy, int left, int right)
{

	if (fy == dx) {
		SDL_RenderDrawLine(R, fx,fy, fx,0);
		return;
	}

	for (int i = left + 1; i < right; i += 1) {
		SDL_RenderDrawPoint(R, i, gumetry_parabolaV_y(i, (struct gumetry_point){fx, fy}, dx));
	}
}





void atoll_DEBUG_drawcircle(int cx, int cy, int r)
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
      SDL_RenderDrawPoint(R, cx + x, cy - y);
      SDL_RenderDrawPoint(R, cx + x, cy + y);
      SDL_RenderDrawPoint(R, cx - x, cy - y);
      SDL_RenderDrawPoint(R, cx - x, cy + y);
      SDL_RenderDrawPoint(R, cx + y, cy - x);
      SDL_RenderDrawPoint(R, cx + y, cy + x);
      SDL_RenderDrawPoint(R, cx - y, cy - x);
      SDL_RenderDrawPoint(R, cx - y, cy + x);

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



