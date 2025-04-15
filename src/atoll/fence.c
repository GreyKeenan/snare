#include "./fence.h"

#include "gumetry/point.h"
#include "./diagram.h"

#include "gu/echo.h"


/*heap*/ struct gu_echo *atoll_fence(
	struct atoll_diagram *diagram,
	struct gumetry_point *polygon,
	unsigned int vertex_count
)
{
	if (diagram == NULL || polygon == NULL || vertex_count < 3) {
		return gu_echo_new(0, "bad inputs: diagram:%p polygon:%p vertex_count:%u",
			(void*)diagram, (void*)polygon, vertex_count);
	}

	return gu_echo_new(1, "TODO");
}

/*
Laying Out the Approach
==================================================

<br>

<!-- INDEX -->
* Terms
* What I need
* The plan
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
  their corresponding `cell` entry should be NADA.
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
set the cell to NADA.
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
  in which case you set the cell-entry to NADA, remember.)
* what should happen when a voronoi-line intersects the polygon
  directly on a polygon-vertex?
  Creating a 0-length edge might be the most consistent,
  since fortuntune's algorithm creates those too.
  However, they might be easier to avoid in this case.

---

But, yeah, I think thats pretty much the bulk
of the line-clipping logic.


Geometry notes
==================================================

This stuff may be offloaded to the `gumetry` module instead of `atoll`.


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
