Order of Events
==================================================

<br>

<!-- INDEX -->
* Site Events
  * insert into the beachline
  * Initialize an empty edge
  * Initialize the new site's voronoi region
  * Identify and add new circle events
* Circle Events aka Edge Events
  * Confirm the circle event
  * Complete the in-progress edges

<br>


Site Events
==================================================

1. Insert the new site into the beachline.
1. Initialize & reference the new edge.
1. Initialize the voronoi region.
1. Identify and add new circle events.

insert into the beachline
--------------------------------------------------

The beachline is an ordered list of sites, each representing a parabola.
They are organized by increasing-x of their breakpoints.

> Given the beachline `{ a b a c a }`,
  `(ab) < (ba) < (ac) < (ca)`.

When inserting a new site,
it must be inserted at the proper location to uphold this rule.
Also, it will bisect one of the existing parabolas.


### CASE: there are existing breakpoints

The parabola `p` to bisect with site `s`
is `p` where `(<p-1>p).x < s.x < (p<p+1>).x`.

> * This can be found with a binary search.
> * any two breakpoints should never have the same `x`,
    as that is when a circle event occurs to remove the site between them.

At the parabola to intersect,
insert a copy of itself,
and then the new site between those two.

> `{ a b c } -> { a b new_site b c }`


### CASE: there are no existing breakpoints

There may be no existing breakpoints if:

1. `beachline_length == 0`
2. for all events in the beachline, their `y` equals the event site's `y`.
  At this point, *all parabolas* are just vertical lines,
  so there are no breakpoints to check/sort by.

In the first situation,
the new site becomes the only site in the beachline ofc.
No bisection occurs ofc ofc.

In the second,
the beachline is instead sorted by the sites' `x` values in ascending order.
No bisection occurs.


Initialize an empty edge
--------------------------------------------------

The breakpoints trace out the midpoints between 2 given sites.
All of those midpoints together trace a straight line,
which is the shared edge between those sites' regions.
So, if we take the first of those midpoints and the last,
we have 2 vertices of the diagram.

Generally, when we add a new site, 2 new edge-ends are created, or 1 edge.
However edges are being stored, we need to initialize an empty-edge
and then store a reference to it so that,
whenever the final-resting-places of the breakpoints
aka the edge-ends are known, (at circle events aka edge events)
we can write the vertices to the proper place.

> Each breakpoint is moving towards a corresponding vertex,
  and multiple will converge at that 1 vertex.
  Depending on how you decide to represent the finished Voronoi Diagram
  and what data you duplicate in doing so,
  you may need to initialze or update the edges in different ways.
>
> I am going to have edges consist of 2 coordinates, their vertices.
  Then, rather than using a half-edge system, there will just be 1 edge
  that both regions on either side of it have a reference to.
  Then, edges will have to duplicate their vertices between each other
  even if they meet at some point. \
> Actually, that was my plan,
  but as I'm thinking this through,
  it might be simpler to have a single list of vertices,
  and then have edges consist of 2 pointers/indexes of vertices.
>
> Other options would include:
>
> * having a single entry for each vertex.
    Edges consist of 2 references to a vertex.
    The advantage of this would be that you can alter vertices
    and have the diagram remain consistent.
> * using the half-edge system outlined in the powerpoint example.
    I'm actually not entirely sure when that would be best?
    I suppose if you needed to walk the borders of diagrams
    with extreme performance in mind, that would be useful?
    **OH!** maybe it's for making the edges wider/warped for visual effects?
>
>   > No, I get it now. Its just a cleaner way to organize it.
      TODO: explain

So, uh, yeah.
you need 1 edge-end for each new breakpoint you added,
and they will be forming a line between themselves.

When handling the case of no existing breakpoints,
adjacent parabolas which will *eventually* have a breakpoint between them
(all adjacent parabolas)
still need to initialize a single edge between them for that future breakpoint.

Also, when adding the first parabola,
still initialize a single edge for it to be drawing.


Initialize the new site's voronoi region
--------------------------------------------------

So, ofc, each site has a corresponding region,
and we need to initialize the new site's region.

You can choose to represent regions in a bunch of different ways.
Generally you might/probably want:

* its site
* a list of its edges so you know its bounds
* a list of its neighbors
* uh ... yeah?

You'll need to store it in a way that you can find it again later
to add more edges and/or neighbors to it.


Identify and add new circle events
--------------------------------------------------

As you add new parabolas to the beachline,
and as those parabolas advance with the sweepline/directix,
some of them are "squeezed out".
This happens when breakpoints converge and meet at a point,
and that is where vertices are placed,
thereby finalizing breakpoint positions & allowing you to complete edges.

So, we need to predict circle events so potential ones can be handled later.
We can do this by first identifying which parabolas are converging.

* a parabola where `focus.y == directix` is not converging
* the leftmost and rightmost parabolas are never converging

Otherwise, the parabolas to either side of the new parabola,
aka the 2 parabolas that were a result of the bisect,
are converging & need corresponding circle events.

A circle event is essentially just saying,
"if no new site events are encountered within this circle,
*these* breakpoints will converge *here*."
Then, we use the highest-y point of the circle as the event,
because after that *nothing* is inside the circle,
so we know the breakpoints do actually converge.

> As for why that works, see Delaunay Triangulations and all that jazz.

Now we want to locate the center of the circle event.
We have a couple options.

Consider the 3 sites we have.

* (c) the new site,
* (b) the site creating the breakpoint with the new site that will converge
* (a) the site creating the *other* converging breakpoint with (b).

The center is the circumcenter of the triangle formed by these three points,
or in other words, its equidistant to all 3 sites.
We can find it by:

* circumcenter formula ofc
* finding the intersection of the middle-perpendiculars of `c->b` and `a->b`
* other triangulation stuff whatever imma do the perpendiculars

Once we have the circumcenter,
we know the highest-y point on that circle is
`circumcenter + (distance from any of those 3 sites to the circumcenter)`.
That's the `y` of the circle event, and the `x` is just the circumcenter.

> Hm. I've been assuming the directix is always a whole number,
  which it is for site events if `site.y`-es are always whole numbers,
  but that isnt necessarily the case for circle events.
  Is it worth rounding up?


Circle Events aka Edge Events
==================================================

1. Confirm the circle event (if not doing so elsewhere)
1. record the finalized-breakpoints at the proper vertex
1. remove the disappearing arc from the beachline

  > The powerpoint says,
    "and [remove] its associated circle events in the event queue."
    How exactly does that occur, where it has other circle events?
1. Initialize a new edge, starting at the convergence point
1. Identify & add new circle events.


Confirm the circle event
--------------------------------------------------

So, rememver, the circle events are potential events,
since new sites can appear inside the circle and interrupt them.
Basically, just make sure any new sites that appeared aren't within the circle.

You can do this step when handling the site events instead if you want.

> That might be easier, honestly.
  Especially since I have a separate event queue for the circle events.

If the event is no longer valid, just discard it.


Complete the in-progress edges
--------------------------------------------------


