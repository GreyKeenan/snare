#include "./fence.h"

#include "./diagram.h"

#include "gumetry/line.h"

#include "gu/gu.h"
#include "gu/echo.h"
#include "gu/intlist.h"

#include <stdint.h>


#define EV (d->hedges[edge].vertex)
#define PV (d->hedges[pedge].vertex)


static inline /*heap*/ struct gu_echo *atoll_fence_clipEdge(
	struct atoll_diagram * /*nonull*/ diagram,

	struct gumetry_point center,
	unsigned int edge
);
static inline /*heap*/ struct gu_echo *atoll_fence_clipEdge_getSides(
	const struct atoll_diagram * /*nonull*/ d,
	struct gumetry_point center,
	unsigned int edge, unsigned int pedge,
	uint8_t edge_side[static 2],
	uint8_t poly_side[static 2],
	uint8_t in_side[static 1]
);
static inline /*heap*/ struct gu_echo *atoll_fence_clipEdge_getIntersect(
	struct atoll_diagram * /*nonull*/ d,
	unsigned int edge, unsigned int pedge,
	const uint8_t edge_side[static 2],
	const uint8_t poly_side[static 2],
	unsigned int dest[static 1]
);
static inline /*heap*/ struct gu_echo *atoll_fence_clipEdge_bringEdgeToVertex(
	struct atoll_diagram * /*nonull*/ d,
	unsigned int edge,
	const uint8_t edge_side[static 2],
	uint8_t in_side,
	unsigned int intersect
);


/*heap*/ struct gu_echo *atoll_fence(
	struct atoll_diagram * /*nonull*/ diagram,

	struct gumetry_point * /*nonull*/ polygon,
	unsigned int polygon_length
)
{
	if (diagram == NULL || polygon == NULL || polygon_length < 3) {
		return gu_echo_new(1, "bad inputs: diagram:(%p) polygon:(%p) polygon_length:(%u)",
			(void*)diagram, (void*)polygon, polygon_length);
	}

	int e = 0;
	/*heap*/ struct gu_echo *echo = NULL;

	e = atoll_diagram_addPolygon(diagram, polygon, polygon_length, diagram->site_count, atoll_NADA);
	if (e) return gu_echo_new(e, "failed to add the bounding polygon to the diagram");


	struct gumetry_point center = gumetry_point_average(polygon, polygon_length);

	for (unsigned int i = 0; i < diagram->cells[diagram->site_count]; i += 2) {
		echo = atoll_fence_clipEdge(diagram, center, i);
		if (echo != NULL) return gu_echo_wrap(echo, 0, "clipEdge #%u failed", i);
	}


	return gu_echo_new(0, "TODO: follow-up by setting inside-cell of unset pedges");
}

// ==========

static inline /*heap*/ struct gu_echo *atoll_fence_clipEdge(
	struct atoll_diagram * /*nonull*/ d,

	struct gumetry_point center,
	unsigned int edge
)
{
	//int e = 0;

	if (EV[0] == atoll_NADA || EV[1] == atoll_NADA) {
		return gu_echo_new(0, "TODO: infinite edge case");
	}
	if (
		d->vertices[EV[0]].x == d->vertices[EV[1]].x
		&& d->vertices[EV[0]].y == d->vertices[EV[1]].y
	) return gu_echo_new(0, "TODO: degenerate zero-length edges");

	/*heap*/ struct gu_echo *echo = NULL;

	uint8_t pedge = d->cells[d->site_count];
	uint8_t edge_side[2] = {0};
	uint8_t poly_side[2] = {0};
	uint8_t in_side = 0;

	unsigned int intersect = 0;
	unsigned int intersect_count = 0;

	do {
		pedge = d->hedges[pedge].nigh[1];

		if (
			d->vertices[PV[0]].x == d->vertices[PV[1]].x
			&& d->vertices[PV[0]].y == d->vertices[PV[1]].y
		) return gu_echo_new(0, "TODO: degenerate zero-length edges");

		echo = atoll_fence_clipEdge_getSides(
			d, center, edge, pedge,
			edge_side, poly_side, &in_side
		);
		if (echo != NULL) return gu_echo_wrap(echo, 0, "unable to get side codes");

		if (edge_side[0] & edge_side[1]) continue;
		if (poly_side[0] & poly_side[1]) continue;
		intersect_count += 1;

		/*

		remaining cases:

		* 1 vertex inside, other outside
		  * find intersection
		  * update outside-vertex
		  * split poly-edge
		* 1 on the line, one inside
		  * set on-line vertex as intersection
		  * split poly-edge
		* 1 on the line, one outside
		  * set on-line vertex as intersection
		  * update outside-vertex
		  * split poly-edge

		  > ~~can maybe create zero-length edges in this case?
		    For now, at least.~~
			No, can delete that edge.

		*/

		echo = atoll_fence_clipEdge_getIntersect(
			d, edge, pedge,
			edge_side, poly_side,
			&intersect
		);
		if (echo != NULL) return gu_echo_wrap(echo, 0, "unable to get intersection");

		echo = atoll_fence_clipEdge_bringEdgeToVertex(
			d, edge,
			edge_side, in_side,
			intersect
		);
		if (echo != NULL) return gu_echo_wrap(echo, 0, "unable to set the edge-end to a new vertex");

		/*
		
		create a new edge
			cell: external_cell
			cell: NADA for now
			vertex: the intersection
			vertex: the second of the pedge's vertices
		update the old & new pedges
			their NADA cell needs to be set to the appropriate inside-cell
		update the linked list
			insert the new edge after the old
			update *all three* of the linked lists: outside, one-side of inside, other-side of inside

		*/

	} while (pedge != d->cells[d->site_count]);

	if (intersect_count != 0) return NULL;

	if (edge_side[0] & in_side) return NULL; //entirely inside

	return gu_echo_new(0, "TODO: entirely-outside edges");
}

static inline /*heap*/ struct gu_echo *atoll_fence_clipEdge_getSides(
	const struct atoll_diagram * /*nonull*/ d,

	struct gumetry_point center,
	unsigned int edge, unsigned int pedge,
	uint8_t edge_side[static 2],
	uint8_t poly_side[static 2],
	uint8_t in_side[static 1]
)
{

		in_side[0] = gumetry_line_side(d->vertices[PV[0]], d->vertices[PV[1]], center);
		if (in_side == 0) return gu_echo_new(0, "the center should never be on the polygon");

		edge_side[0] = gumetry_line_side(d->vertices[PV[0]], d->vertices[PV[1]], d->vertices[EV[0]]);
		edge_side[1] = gumetry_line_side(d->vertices[PV[0]], d->vertices[PV[1]], d->vertices[EV[1]]);
		if ((edge_side[0] | edge_side[1]) == 0) return gu_echo_new(0, "TODO: collinear case");
		//if (edge_side[0] & edge_side[1]) continue; // no intersection

		poly_side[0] = gumetry_line_side(d->vertices[EV[0]], d->vertices[EV[1]], d->vertices[PV[0]]);
		poly_side[1] = gumetry_line_side(d->vertices[EV[0]], d->vertices[EV[1]], d->vertices[PV[1]]);
		//if (poly_side[0] & poly_side[1]) continue; // no intersection

		return NULL;
}
static inline /*heap*/ struct gu_echo *atoll_fence_clipEdge_getIntersect(
	struct atoll_diagram * /*nonull*/ d,
	unsigned int edge, unsigned int pedge,
	const uint8_t edge_side[static 2],
	const uint8_t poly_side[static 2],
	unsigned int dest[static 1]
)
{
		if      (edge_side[0] == 0) *dest = EV[0];
		else if (edge_side[1] == 0) *dest = EV[1];
		else if (poly_side[0] == 0) *dest = PV[0];
		else if (poly_side[1] == 0) *dest = PV[1];
		else {

			struct gumetry_point intersect_point = {0};
			int e = gumetry_line_intersection(
				&intersect_point,
				d->vertices[EV[0]], d->vertices[EV[1]],
				d->vertices[PV[0]], d->vertices[PV[1]]
			);
			if (e != gumetry_INTERSECT) return gu_echo_new(e, "should always be an intersection here. Rounding error?");

			const unsigned int new_vertex = d->vertices_length;
			e = gu_unstable_intlist_push(
				&d->vertices, &d->vertices_length, &d->vertices_allocation, &intersect_point
			);
			if (e) return gu_echo_new(e, "unable to push new vertex");

			*dest = new_vertex;
		}
		return NULL;
}

static inline /*heap*/ struct gu_echo *atoll_fence_clipEdge_bringEdgeToVertex(
	struct atoll_diagram * /*nonull*/ d,
	unsigned int edge,
	const uint8_t edge_side[static 2],
	uint8_t in_side,
	unsigned int intersect
)
{
		int e = 0;

		if (edge_side[0] != 0 && edge_side[0] != in_side) {
			e = atoll_edge_replaceVertex(d->hedges, edge, EV[0], intersect);
			if (e) return gu_echo_new(e, "unable to replace with new vertex (0)");
		} else if (edge_side[1] != 0 && edge_side[1] != in_side) {
			e = atoll_edge_replaceVertex(d->hedges, edge, EV[1], intersect);
			if (e) return gu_echo_new(e, "unable to replace with new vertex (1)");
		}

		return NULL;
}






/*
Laying Out the Approach
==================================================

<br>

<!-- INDEX -->
* Terms
* What I need
* The plan
  * Elaborating on looping through voronoi-edges
* Geometry notes
  * Line Segment Intersections

<br>


Terms
==================================================

* "*border cell*":
  If we consider the voronoi diagram as a collection of cells,
  once bounded within a polygon,
  it would have a definitive "outside of the boundaries" region.
  That region could be considered as an additional,
  external cell, or the "border cell".
  In this implementation, the border cell index is `site_count`,
  and the half-edges defining the border are at `hedges[cells[site_count]]`.
* ...


What I need
==================================================

(this version of) Fortune's Algorithm results in a diagram which
has unterminated voronoi-edges.
Additionally, it does not restrict the range of voronoi-vertex placement.
So, if I want to fit the generated diagram within a boundary,
I need to clip both of these types of lines.

So, given a generated diagram and a bounding-polygon,
this function should clip the voronoi-edges so that it fits within the polygon.

As for output format, the resulting clipped-diagram
should match the existing diagram storage structure.

* The bounding-polygon will be stored in the `hedges`
  and `vertices` lists of the diagram.
* `cell[site_count]` is an index to a hedge in the
  border-polygon's linked-list of the half-edges.
* The bounding-polygon may (and certainly does) have more
  edges/vertices than the initial input polygon.
  This is because, at each point that a voronoi-line
  intersects a polygon-edge, a vertex is created.
* The half-edges of the bounding-polygon will have
  their associated cells properly set.
  The cell for the outside-half of the bounding edges is `site_count`.
* If any sites are outside of the diagram,
  their corresponding `cell` entry should be INDULL.
* Any removed edges will not only be unreferenced by the diagram's elements,
  but also removed from the `hedges` list.
  This ensures that you can still loop through all of the
  edges for rendering purposes, without encountering extraneous ones.

  > Note: I'll probably have to set these with NULL vertex-indices,
    since truly removing them would add a bunch of ordering issues.
* The removed vertices, on the other hand, may be left behind in the list.
  They are instead removed just by lacking any hedges which reference them.


The plan
==================================================

First, add the polygon edges and vertices to the hedges & vertices lists.
With the polygon as a linked list of edges,
I can easily bisect edges where voronoi-lines cross them.
For the inside-half of the new border-edges,
set the cell to INDULL.
This indicates that the cell has not-yet been assigned, for later checks.
Set `diagram->cells[site_count]` to a border-edge.

Keep track of which hedges have been newly added for the border.
We need to loop through them & the old edges separately.

With that setup out of the way,
loop through all of the voronoi-lines.
If the line is completely outside of the polygon,
remove it (& update its neighbors).
If the line crosses a polygon-edge, split that edge.
Set the inside-half-cells of the newly bisected edge pieces accordingly.
(TODO: elaborate)
If the line is entirely inside the polygon, do nothing of course.

Finally, we have to update the polygon edges which had no intersections.
Loop through all of the initial polygon-edges.
If their inside-half's cell has not been set,
set it as the same as one of their neighbors.
(They should be the same.)

---

Additional details to consider:

* Both ends of a voronoi-line may be unterminated.
  This line may or may not be within the bounding polygon.
* When deleting/fiddling-with hedges,
  make sure to check when
  you are removing an edge that the `cell[]` list points to.
  If you are, update it to point one of the right hedges still.
  (Unless you are removing that cell entirely,
  in which case you set the cell-entry to INDULL, remember.)
* what should happen when a voronoi-line intersects the polygon
  directly on a polygon-vertex?
  Creating a 0-length edge might be the most consistent,
  since fortuntune's algorithm creates those too.
  However, they might be easier to avoid in this case.

---

But, yeah, I think thats pretty much the bulk
of the line-clipping logic.


Elaborating on looping through voronoi-edges
--------------------------------------------------

cases:

* 2 inf
  * partially-inside or entirely-outside
* 2 inside
  * entirely-inside
    (because convex)
* 2 outside
  * ~~entirely outside~~
  * partially-inside or entirely-outside
* 1 inf 1 outside
  * partially-inside or entirely-outside
* 1 inf 1 inside
  * partially-inside
* 1 outside 1 inside
  * partially-inside

For simplification purposes,
it may be worth it to first bound infinite edges within a rectangle
that we know the entire bounding-polygon fits within.
Then, there are fewer cases to worry about.
If I'm doing that, I already have a list of only the infinite edges:
the beachline.

Hm. That isnt *strictly* necessary though.
Instead, I can treat all infinite edges like outside-vertices,
and calculate on-the-spot.

* 2 outside
  * entirely outside /or/ partially inside
  * intersects 0 or 2 polygon-edges
* 1 outside 1 inside
  * partially inside
  * intersects 1 polygon-edge
* 2 inside
  * entirely inside
  * intersects 0 polygon-edges

---

	for each voronoi-line:
	for each intersection between the voronoi-line and any polygon-edge:

	* find which vertex of the voronoi-line is on the
	  outside-side of the intersecting polygon-edge.
	* set that outside-vertex to the intersection instead.
	* split the polygon-edge at the intersection
	* update the cell-records of the affected hedges

---

Oh, wait.
I also have to catch the case when a line is colinear with the border.
Annoying.


Geometry notes
==================================================

This stuff may be offloaded to the `gumetry` module
instead of ~~`atoll`~~ `corn`.


Line Segment Intersections
--------------------------------------------------

I think this holds true: \
For either line segment, if both end-points of segment B
are on the same side of the line-of-segment-A,
the segments do not intersect.

Obviously, another way to do it is to find the intersection of the full lines,
and then checking if that intersection is within the segments.


Inside/outside the polygon
--------------------------------------------------

Start with 1 point which we know to be inside the polygon.

> Since we are assuming it is a convex polygon,
  this can be the average of the points.

We could draw a line segment from one point to that inside-point.
If the segment crosses any polygon-edge, the point is outside the polygon.

Alternatively,
we can just check if the point is on the same side of every polygon-edge
as the known-inside-point is.



*/






// this is brainstorming stuff that I'm holding on to for the moment:

// trying to think through how it'll work
/*

terms

* "border cell" if we conceptualize a bounded-voronoi-diagram as a collection of cells,
  you could consider all space *outside* of the diagram to be a single exterior-cell.
  I might call that the "border cell" below.
* "pedge" an edge of the border polygon
* "pertex" a vertex of the border polygon
* "vine" a line/edge of the voronoi diagram. (an edge that's not a pedge)

---

(remember that we are presupposing that all sites are within the bounds)

Okay, so, there are at least these cases:

* both ends of the edge are infinite
  * the entire line is out of bounds
  * part of the line is in-bounds
* 1 end of the edge is infinite

Additionally, a *vertex* can be out of bounds.
if this is the case, we have to clip its edges which are partially in-bounds,
and destroy its edges which are entirely out of bounds.

> how do degenerate zero-length edges factor in to this?
  I don't think they matter for my plans so far, but keep them in mind.

As for our outputs,
keep in mind that when we clip edges,
we need to form new vertices & edges,
as well as associate the outside-half of the new edges with the border-cell.

---

naively,
we could loop through all vertices and
mark the out-of-bounds ones with {NAN, NAN}.
Then, we could loop through the edges and remove all of them
which have both ends out-of-bounds,
~~or 1 end out of bounds and the other unterminated.~~

Wait, could we?
Are all out-of-bounds vertices known to be out of bounds?
Can double-unterminated edges be completely out of bounds?

Also, for the 1-end out of bounds and other unterminated,
is that always entirely out of bounds?
I think not, since it could have an unterminated edge across the in-bounds space.

so, we *could* remove edges which are double-ended out of bounds,
but for the others we have to additionally check if they cross through the in-bounds.

---

Okay, so that has some rough edges,
but it does hit on an important point.
We only need to modify those edges which
1) have at least 1 out-of-bounds vertex
or 2) have an unterminated end.

So, we don't need to check for every edge if it intersects with the polygon-borders.
But, we do need to check for every vertex, which isn't really better I suppose?

we could *maybe* go through them on an edge-by-edge basis,
but that could make it more difficult to associate the newly-created border-edges
with their proper half-edge linked lists.

...
*/
