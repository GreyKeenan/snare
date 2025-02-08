
<br>

<!-- INDEX -->
* About Voronoi Diagrams
  * Creating Voronoi Diagrams
* Fortune's Algorithm
  * Input
  * The Sweepline
  * Events
  * The Beachline

* TODO

<br>


About Voronoi Diagrams
==================================================

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


Creating Voronoi Diagrams
--------------------------------------------------

There are a few different ways to create Voronoi Diagrams.

One approach is to loop through every singe coordinate point,
and then check for every site which it is closest to.
This is very slow.

Another approach is to start at every site,
and then "grow" them all outwards at a steady rate
by claiming adjacent points,
until you run into another region.
This is also pretty slow, but easily parallelized.
This is how Voronoi Diagram-like patterns generally form
in the natural world as well.

Because you can convert between Delauney Triangulations
and Voronoi Diagrams,
you can use a Delauney-creation technique
and make a Voronoi Diagram from it.

Fortune's Algorithm is an approach
which creates the diagram by drawing its lines.
This is the optimal approach, and when written optimally,
it performs in O(nlogn) time, worst-case.


Fortune's Algorithm
==================================================

Input
--------------------------------------------------

The input to Fortune's Algorithm is the set of sites
that regions will be outlined for.
In a pure-mathematical representation of the algorithm, that is all.
In a program, you typically also need to define
a bounding box or other boundary to terminate infinite lines.


The Sweepline
--------------------------------------------------

The algorithm uses a "sweepline" approach.
This is just a fancy way of saying that the input-sites
are given in a sorted order,
and the algorithm prioritizes them (and other events)
in that order, rather than jumping around haphazardly.

Traditionally, this order is based on ascending-Y values of sites.
You could use something else,
but I will be referring to the algorithm's operation in these terms
for consistency with other sources.
(Also, I will be considering y0 as the bottom and y(infinity) as the top.)

So, as the sweepline moves up through sites in order,
it splits the diagram in half.
Below the sweepline,
we have everything that the algorithm has already seen
and can therefore draw conclusions about.
This side is further split conceptually
into a part of the diagram which has been completed and will not change,
and a part of the diagram that is currently being constructed
(the "beachline").
Above the sweepline,
we have unknown-land and upcoming events to be processed.

The power of this is that the algorithm often
doesnt need to sub-iterate through all of the sites in the diagram,
for each site in the diagram.
Instead, it can separate not-yet relevant and no-longer relevant sites
from the currently-relevant "beachline".


Events
--------------------------------------------------

So, conceptually, the sweepline moves up
with an ascending Y value across the diagram.
In practice, the algorithm doesn't run an iteration for every single
'y' value that the sweepline passes through.
So, if the diagram were 10 pixels tall,
you wouldn't necessarily have 10 iterations of the algorithm,
for each 'y' value as the sweepline moves upwards.

Instead, the sweepline only 'stops' at the relevant positions
where important events occur.
There are 2 kinds of events:

1. **Site Events**
2. **Edge Events** (also called *circle events*)

Site events correspond 1:1 with the input sites.
They are all known before the algorithm begins.
Edge Events are identified & anticipated as the algorithm runs,
and added to the queue with the Site Events.
Events are always processed in order,
abiding by the rules of the sweepline.
This means that Edge Events of course
have a corresponding (x, y)
position on the diagram, so they can be sorted.

Edge Events correspond to *potential* instances where
Voronoi-Vertexes can be formed.
A voronoi vertex is where the boundaries
of 3+ regions meet at a point.
This "ends" some lines/edges being drawn,
as the angle changes,
and new ones begin.
Edge Events do not *always* result in a new vertex, though,
so they must be verified as new information is revealed.

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


The Beachline
--------------------------------------------------

So, we have a broad idea of the driving-force of the algorithm:
the Event Queue.
Next, let's talk about the Beachline.

The Beachline is the representation of the sites/regions
which are currently being outlined.
Each Site Event adds a new site to the beachline.
Edge Events, in turn,
complete edges and thereby regions,
and remove sites from the beachline.

If you've looked at visual representations of Fortune in progress,
you've certainly seen the beachline represented as a series of parabolas.
Though this is a technically-accurate representation,
I think it makes it seem more confusing than it really is,
so stick with me as I explain the parabolas.

Generally, parabolas can be represented with a formula like: `y = x^2`.
However, there is an alternative used here.
If you have a single point (a site),
and a straight line (the sweepline),
a parabola can be defined as all points
which are equidistant from both the line and the point.
`length((parabola.x, parabola.y), (parabola.x, line.y))
= length((parabola.x, parabola.y), (site.x, site.y))
, solve for parabola.y`

Thus, each site in the beachline has a corresponding parabola.
At the point where the sweepline touches the site,
the parabola is just a straight line going down
After that, it opens/grows as the sweepline moves further away.

So, again, I found this to be confusing at first.
*Why* are parabolas formed as we trace the regions?
Think of it this way.
Remember that regions are defined as the set of all points
which are closer to a given site than any other site.
Because the parabola is exactly between the line and site,
everything below it is closer to the site than the sweepline.
In other words, everything below it is closer to the site
than any new sites could be (above or at the line).
Everything below the parabola
is *guaranteed* to be part of that region.
So, the parabola represents the region growing as sites are revealed,
and the "ends" of the parabola
(where it meets another) (also called "breakpoints")
are where the edges will be, so they trace the lines.






~~~
...
~~~

1. Recieve sites as input, and sort them into the event queue.
1. loop through the queue, popping events by ascending-Y
  1. if its a site event:
    1. Identify which parabola to split
	1. ...
  1. if its an edge event:
    1. ...
1. cleanup
  1. terminate any remaining edges
  1. ...






TODO
==================================================

Why fortunes algorithm has parabolas:
The parabola is defined as the boundary between
where given points are closer to a site vs closer to the sweepline.
The voronoi diagram regions are defined as a collection of all points
which are closer to a specific site than any other.
The parabola grows as the sweepline advances
because it is no longer possible for any new sites to appear behind that line,
so the parabola defines all points which we currently-know to be closer
to its site than any other point!

defining:
* points
* sites
* region
* parabolas
* breakpoints
* beachline
* sweepline
* event points
* site events
* edge events

The relationship btwn voronoi diagrams & delaunay triangulations

references
