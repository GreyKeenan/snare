
<br>

<!-- INDEX -->
* Background Information
  * Voronoi Diagrams
  * Directix-Focus Parabolas
* Introducting Fortune's Algorithm
  * The Sweepline
  * The Beachline
  * Events
* Implementing the Algorithm
  * State
  * Inputs
  * Handling Site Events
  * Handling Edge Events
  * Cleanup

* References

<br>

Background Information
==================================================

Voronoi Diagrams
--------------------------------------------------

Say you have two or more points on a graph.
Call them 'sites'.
For all *other* points on the graph,
there is 1 site they are nearest to.
A Voronoi Diagram organizes all points into 'regions',
where every point in a region has a common nearest-site.

There are two main ways to conceptualize/represent the diagram.

1. Regions are defined as a collection of every point/pixel within them,
  and the diagram as a whole is a collection of regions.
2. Regions are defined by their dividing lines,
  and the diagram stores vertices to represent the bounding-polygons.

Each of these can be useful,
and the second is what I am more concerned with for my use case.

Here are some interesting/useful properties of voronoi diagrams:

* dividing lines lay exactly along the points which are equally-distant
  between two or more sites.
* Because voronoi diagrams are defined using a distance calculation,
  you can substitute alternative formulas to Euclidian Distance
  to get different results.
* Using euclidian distance, though, regions always form convex polygons.
* The number of regions is the same as the number of sites.
* A Voronoi has a unique relationship to a Delauney Triangulation.
  For any 3 sites whose boundaries meet in a voronoi vertex,
  the circumcircle of those sites contains no other sites.
  I realize this is confusing in text-only.

There are a few different ways to create Voronoi Diagrams.

* One approach is to loop through every singe coordinate point,
  and then check for every site which it is closest to.
  This is very slow.
* Another approach is to start at every site,
  and then "grow" them all outwards at a steady rate
  by claiming adjacent points,
  until you run into another region.
  This is also pretty slow, but easily parallelized.
  This is how Voronoi Diagram-like patterns generally form
  in the natural world as well.
* Because you can convert between Delauney Triangulations
  and Voronoi Diagrams,
  you can use a Delauney-creation technique
  and make a Voronoi Diagram from it.
* And finally, Fortune's Algorithm is an approach
  which creates the diagram by drawing its lines.
  This is the optimal approach, and when written optimally,
  it performs in O(nlogn) time, worst-case.


Directix-Focus Parabolas
--------------------------------------------------

Generally parabolas are represented in the form `y = ax^2 + bx + c`.
There is an alternative approach we will be using, though.

If you have a single point (the focus),
and a straight line (the directix),
a parabola can be defined as all points
which are equidistant from both the line and the point.
Our formula, then, is derived from this relationship.

~~~

(a, b) = focus point
(x, y) = point-in-parabola
l = directix (y value variant)

:length:((x,l), (x,y)) == :length:((a,b), (x,y))
OR (because l will always be >= y)
l - y = :VRAD:( (a - x)^2 + (b - y)^2 )

solve for y:

l - y = :VRAD:( (a - x)^2 + (b - y)^2 )
(l - y)^2 = (a - x)^2 + (b - y)^2
ll + (-y)^2 + -2ly = aa + (-x)^2 + -2ax + bb + (-y)^2 + -2by
ll + -2ly = aa + (-x)^2 + -2ax + bb + -2by
-2ly = (a - x)^2 + bb + -2by + -ll
-2ly + 2by = (a - x)^2 + bb + -ll
y(-2l + 2b) =
/      (a - x)^2 + bb + -ll
:  y = --------------------
\          (-2l + 2b)

/      (a - x)^2 + bb - ll
:  y = --------------------
\          2(b - l)

The storage size need for this formula at its largest point is

a = m; x = -m; b = m; l = 0;
(m - (-m))^2 + mm - 0(0)
(m + m)^2 + mm
5mm

where m = the maximum value of the type of {a,b, x, l}.
If m = 2^15 - 1,
the maximum size is 5_368_381_445.
I'll just be lazy and cast them up to int64 values
and catch the oversized value afterwards.

~~~

The relevant property of parabolas of this form is that it represents distance.
Because the parabola is directly between the focus & directix-line,
all points on the focus-side of the parabola are closer to the focus,
and vice-versa for the line-side.


Introducting Fortune's Algorithm
==================================================

Fortune's Algorithm is the optimal alg for creating a Voronoi Diagram.

At a high level, these are the steps of the algorithm:

1. Recieve sites as input, and sort them into the event queue.
1. Loop through the queue, popping events in order.
  1. if its a site event:
    1. Add it to the "beachline", update the beachline
    1. Check for new edge events & add them to the queue
  1. if its an edge event:
    1. Confirm the event
    1. Finish edges & remove them from the beachline.
    1. ?check for new edge events & add them to the queue.
1. cleanup
  1. ...

So, let's go through what these steps mean.


The Sweepline
--------------------------------------------------

The algorithm uses a "sweepline" approach.

Conceptually, this mans the algorithm operates as a line
which moves/sweeps through the diagram from one side to another.
In practice, this just means that the input & events are handled in a sorted order,
typically by ascending-Y.


As the sweepline sweeps,
it divides the diagram into 3 sections.
In front of the sweepline,
you have sites/events which are not-yet relevant or known to the algorithm;
directly behind the sweepline,
there sites whose regions are currently being outlined;
and further behind the sweepline,
there are sites whose regions have already been completed,
so are no longer relevant.
Dividing the sites in this way is useful because
the algorithm doesn't have to sub-iterate through every site every time.


The Beachline
--------------------------------------------------

The beachline is the name for
the set of regions/edges which are currently being drawn by the algorithm.
As the sweepline encounters new sites, it adds them to the beachline,
and as it finishes drawing their boundaries, it removes them.

So, as the sweepline moves past sites,
it begins to define their regions.
Recall that regions consist of every point
which is nearer to a given site than any other.
This is where the parabolas come in.
Using the directix-focus parabola form,
we can easily distinguish which points are closer
to the fucus (a given site),
and which are nearer to the line (sweepline).
Points nearer to a site than the sweepline
are *guaranteed* to be part of that site's region,
since new sites can only appear *after* the sweepline.

So, with that in mind,
the parabolas represent the regions growing,
and the intersection-points of sites' parabolas (called "breakpoints")
will trace the outlines of their regions.


Events
--------------------------------------------------

So, conceptually, the sweepline moves up through the diagram.
In practice, though,
the algorithm doesnt iterate for *every* Y value.
Instead, it only 'stops' at relevant positions
where important events occur.

There are 2 kinds of events:

1. **Site Events**
2. **Edge Events** (also called *circle events*)

Site events correspond 1:1 with the diagram's sites.
They add new sites to the beachline & begin tracing new regions.

Edge events are potential instances where
regions' boundaries meet at a vertex.
At this point, a parabola is closed
as its neighbors converge over it.
This completes regions and removes them from the beachline.
These events are anticipated as the algorithm runs
and added to the event queue in the proper ascending-Y order.

Because Edge Events are only *potential* convergences,
they must be confirmed.
Confirming Edge Events is better understood by considering
the relationship between Voronoi Diagrams and Delauney Triangulations.
The vertices of a Delauney Triangulation
are the sites of a corresponding Voronoi Diagram.
Similarly, the centers of circumcircles in the Delauney
will be the voronoi-vertrices of the corresponding diagram.
Since, by definition with a Delauney,
these circumcircles contain no other vertices (voronoi sites),
the creation of voronoi vertices with edge events
can be validated by creating a circumcircle
and confirming that no other sites occur within it.

I will discuss edge events in more detail later,
as they are one of the main thingies of the algorithm.


Implementing the Algorithm
==================================================

State
--------------------------------------------------

### The Event Queue

The event queue will need to:

* contain both site and edge events
* present events in ascending-Y order
* allow you to insert events in the sorted-position

I think the best way to do this is to have 2 separate "queues".
One is just the array of input-sites, sorted.
The other is a list which can be populated with edge events.
The site events are static, after all,
and this way the sorted edge-event insertions
dont need to also iterate through the site events.
You just need to check which topmost-event between the two queues is first,
and whether one or both are empty.


### The Beachline

The beachline needs to represent/support:

* parabolas
* breakpoints between two parabolas
* searching between breakpoints
* inserting new and removing completed parabolas
* breakpoints changing for different directix-es

The recommended (by Fortune) data structure is a balanced binary tree.
Leaves of the tree are sites, with corresponding parabolas.
Internal nodes are the breakpoints which lie between their respective site-branches.
This is optimal for lookup & insertions.

Alternatively, you could use a list of sites.
Breakpoints are implied between list items.
This is slower for insertions, but lazier.


### The Ouptut Diagram

* move from 1 region to its neighbors
* get the polygon-boundaries of a region

~~~
...
~~~


Inputs
--------------------------------------------------

The input is the set of sites to create regions from.
In a pure-mathematical representation of the algorithm, that is all.

In a program, you typically also need to define
a bounding box or other boundary to terminate infinite edges.


Handling Site Events
--------------------------------------------------

Handling Edge Events
--------------------------------------------------

Cleanup
--------------------------------------------------
