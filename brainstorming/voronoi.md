Voronoi Generation
==================================================

> GreyKeenan/snare/brainstorming

About options for generating a Voronoi Diagram.

<br>

<!-- INDEX -->
* Laying out how Fortune's Algorithm works
  * Overview of algorithm operation

* References

<br>


Okay, so I have decided to go with a Voronoi Diagram
to create a random mesh of polygons.

There are 2 main ways to approach this that I'm considering.

* Fortune's Algorithm
* Creating a Delaunay Triangulation, then ~~inverting~~ it

Fortune's Algorithm is optimal but involved,
and I'm feeling lazy right now.

A Delaunay Triangulation can be created from any
existing triangulation in (at most) O(n^2) time.
Creating a simple, bad triangulation is easy.
Then, creating the Voronoi from the Delaunay is O(n).
(compute circumcenters, connect circumcenters of adjacent triangles)

Fortune's would be better,
but a dumb Delaunay approach would be easier,
especially since its way simpler to wrap my head around.
Also, I'm dealing with relatively small numbers of points.

Idk. I'll go with Fortune's Algo.
Its more direct for what I'm trying to accomplish here.


Laying out how Fortune's Algorithm works
==================================================

Overview of algorithm operation
--------------------------------------------------

Fortune's algorithm is a "sweep line" algorithm.
It maintains a logical sweepline,
processing the 'sites'
(the points that the voronoi diagram is constructed around)
in order.
Everything in front of the sweepline can be left out
of iterations until it is reached.
Behind the sweepline, there is a collection of sites
whose regions are currently being defined.
These current sites are iterated through as the algorithm runs,
and are referred to as the "beachline".
Finally, the rest of the sites behind the sweepline
and not part of the beachline have already been processed,
and need not participate in the algorithm anymore. They're done.

The sweepline moves in one direction,
typically TOP-to-BOTTOM or LEFT-to-RIGHT.
Importantly, the algorithm doesnt actually
run over every single Y/X value as it goes.
Instead, it jumps from event to event in order,
and performs calculations at each one.

There are two different types of events.

* **Site Events** are identified by the x/y coordinates
  of a corresponding site.
  So, there is 1 site event for each site,
  and they are all given/set as input before the algorithm begins.
* **Edge Events** (or *circle* events)
  are created and inserted into the event queue as the alg runs.
  They correspond to *potential* instances where
  voronoi-vertexes may be formed.
  They do not *always* result in the creation of a vertex,
  but they must each be checked to see if a vertex needs to be added.

Events are always processed in order of the direction of the sweepline,
regardless of which type of event it is.

edge/circle events can better be understood if
you understand the relationship between
Voronoi Diagrams and Delaunay Triangulations.
See the definition of Delaunay Triangulations that uses a circumcircle.

~~~
...

* parabolas
* boundaries
* actual operation
~~~


Storing information
--------------------------------------------------

The algorithm needs to store/access the following information.


### Output format of the Voronoi Diagram:

A linked list (or a graph).
Nodes are 'regions' of the diagram, associated with a single site.
Logically, nodes consist of:

* the origin site
* a list of pointers to adjacent nodes
* a list of vertices defining its polygon boundary


### a queue of events

A queue of site events & edge events, processed in order.
Because site events are static, while edge events are dynamic,
I decided to keep separate lists for each,
and checking both list-heads to process them in order.
This also separates sorting the edge-events.


### The Beachline

The optimal way of representing the beachline is as a balanced binary tree.
(see the powerpoint for a good explanation of why.)
I didn't do this (maybe later).

Alternatively, you can just keep a list of bounded parabolas/sites,
and linearly go through it to check collision.

I'm planning to use a list of elements.
Elements contain:

* originating-site
* ptr of where to write the x,y to, when breakpoint closes.
  This is for the breakpoint between this segment & the next.
* indication of NULL breakpoint.
  Relevant because the parabolas dont always meet somewhere,
  since the diagram has a bounding box.

The list needs to be sorted in a direction
perpendicular to the direction the sweepline moves.
Eg, if the sweepline moves `W->E`,
the list could be `N->S` or `S->N`.
Then, to check which parabola a new site interrupts,
you can check each list-item.


References
==================================================

good fortunes alg sources

* <https://jacquesheunis.com/post/fortunes-algorithm/>
* <https://blog.ivank.net/fortunes-algorithm-and-implementation.html>

> also, see the `voronoi_powerpoint.ppt` in this same dir.

fortune's alg demonstration

* <http://www.raymondhill.net/voronoi/rhill-voronoi.html>

a rly good delaunay source

* <https://ianthehenry.com/posts/delaunay/>

other stuff misc

* <https://www.cise.ufl.edu/~ungor/delaunay/delaunay/node5.html>
* <https://codeforces.com/blog/entry/85638>
* <https://paulbourke.net/papers/triangulate/>
