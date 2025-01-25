Polygon Generation
==================================================

> GreyKeenan/snare/brainstorming

Thinking through how I want polygon generation to go.

<br>

<!-- INDEX -->
* Approaches
  * Line-walking
  * Deforming a grid
  * Voronoi Diagrams
  * Delaunay Triangulation

<br>

Approaches
==================================================

* line-walking with heuristics

  > Could start with a boundary (or use rectangle)
    and then generate shapes inwards,
    or could start with a single shape & build off of it outwards.

  > Creating a set of heuristics for drawing the lines
    is potentially really annoying.

* deforming a grid

  > Start with a perfect grid,
    then move vertices around to deform it.
    Cells may be joined or cut
    to create polygons with different numbers of sides.

* Voronoi Diagrams

  > From a random distribution of points,
    regions are drawn by grouping all pixels
    which are closest to a given point.

  > Different distance-calculations can be used to alter the shapes.

* Delaunay Triangulation

  > Method of connecting a random set of points to form a grid-of-traingles.

* using random noise functions
* ...?


Deforming a Grid
==================================================

This approach seems like about what I want.
Its fairly simple/straightforward. (I think?)
I'm just outlining a naive approach.

NVM:
I implemtented it (see `expl_warped` branch).
Its *alright*, but a little more regular
than I wanted out-the-gate.
Ik i could iterate over it with other operations,
but after messing with some voronoi-diagram-generation sites,
I think that is closer to the shape that I want.

1. Start with a grid of non-adjacent points.
  Lets call the gap between each point `g`.
1. Apply a random integer offset to each point in the grid.
  It should be between `0` and `(g - minimum_width) / 2`.
  This prevents offset-points from crossing over other lines.
1. go through and randomly remove sides/vertices to join some cells.
  This is the part that I'm not entirely sure how to handle yet.
  It depends on how I lay out the grid of pixels in memory.

Ideas for memory layout

* literally a grid of (x,y) pairs.
  `grid[0][0]`, `grid[0][1]`, `grid[1][0]`, and `grid[1][1]`
  together represent a cell.

  > When removing vertices, you can replace them with a `NULL` value.
    NULL vertices redirect to the prior point perhaps?
    Or do they get removed entirely?

  > Hm. This means that territories always meet up at corners, though.
    I don't really like how that behaves.
    Really, I want to be able to remove lines *and/or* vertices.
    With a grid of points, that doesn't really work
    since the lines themselves are the implied connections between points
    rather than actually encoded somewhere.

  > I could add a byte between every point to indicate the status of the line.
    That's annoying though.
    Similarly, maybe points could be like 12 bits,
    and the remaining bits could carry more information?
    12 is plenty.

could save space if each point in the grid
is an offset from that-point's index,
rather than an absolute value itself.
Then, each point in the grid could be 2 bytes or even less

~~~
XxxxYyyy

(actually, `xxxXYyyy` moving the sign bits makes it easier to bitshift)
~~~

Then, all I have to do to generate a width * height array of random bytes,
and thats the warped grid.
(the gap is still `max_random_offset * 2 + min_width`,
so in this case `16 + min_width`)

Let's look at this a different way.
Is it even necessary to store in the grid when vertices/sides are absent?
What if the grid is just used to generate starting lines,
and then they are converted into another form,
such as an array of polygon-pointers like I was originally thinking.
That would take up much more space than a grid thing, probably,
but it could include the existence of lines more easily.

...
