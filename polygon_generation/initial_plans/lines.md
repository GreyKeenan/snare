Lines
==================================================

> GreyKeenan/snare/brainstorming

Some sort of underlying module which
handles basic line & polygon representations/functionality.

<br>

<!-- INDEX -->
* Representing segments and lines
  * Experimenting with representations

<br>

Representing segments and lines
==================================================

Experimenting with representations
--------------------------------------------------

There are different ways to represent segments and lines.
Here, I am thinking through some options.

Terminology:

* "south" and "north" are two different points along the mathematical line.
  They are used to accurately represent the slope.
  When the code counts from one point to another,
  it goes from south to north.
* "segment" is a single, unbending line with two vertices.
* "head" and "tail" are the two vertices of a segment.
  They are the actual starting and ending points of the rasterized line.

---

First, defining a point is pretty simple.

~~~
[int, int] is a point
~~~

Then, in their rawest forms,
a line is just a series of points,
and a segment is just a line of 2 points.
In these raw segments, head/tail and south/north are interchangeable

Its worth mentioning that a raw\_polygon is just a line,
with the assertion that the first/last elements are connected.

~~~
[point:south, point:north] is a raw_segment
[point, point ... point] is a raw_line
~~~

---

So, when rasterizing the line,
we might not want it to start on the same pixel
that defines the slope accurately.

One way to differentiate the head/tail from north/south
is to use an offset value.
The offset is the number of pixels to continue along the line,
from south/north respectively
(using a line-drawing algorithm to rasterize)
before you reach the head/tail.

~~~
[point:south, uint:offset, point:north, uint:offset] is a segment
[segment, segment ... ] is a line
~~~

Notice here that a line is an array of segments, rather than of points.

First, that means that a polygon cannot be identical to a line.
It needs to have an additional segment listed which connects the
otherwise first/last points of the line.

Also, with an array of segments representing a line,
some information is duplicated.
In a line, segment A's tail should be the same as segment B's head.

The layout below allows this information to be shared.
Only the first segment needs a south-offset value.
After that, each segment's head is just carried-over
as the tail of the previous segment.

Unfortunately, this means that the segments can no longer be
arbitrarily indexed,
since each needs information from the previous,
stemming back to the first-segment's offset value.
It has to be read from the start.

~~~
[south,offset,north,offset, south,north,offset, south,north,offset ... ]
~~~

Alternatively, instead of using an offset integer,
the head could be denoted with an actual point.

~~~
[point:head, point:south, point:north, point:tail] is a segment
~~~

With this approach,
the tail of a previous segment
can overlap with the head of the following segment.
Because the points are absolute,
the segments can be arbitrarily indexed as well.

~~~
[ head1, south1, north1, tail1_and_head2, south2, north2, tail2 ]
~~~

Unfortunately, this isn't actually that useful.
Because the points are larger than offsets,
each new segment still adds 6 ints.
With the indexable offset-segment array above,
that was the same.
So, this isn't really better except for very specific circumstances.


Finally, we could also indicate the tail as an offset from south,
rather than an offset from north.
I'm not really sure why this would be useful though?

~~~
[point:south, uint:offset, uint:length, point:north] is a segment
~~~


Deciding on representations
==================================================

First of all, I think having some basic functionality available
for the raw-segments/lines is a good idea on the face of it,
although I'm not sure that I actually need them to be honest.
Still, providing them means I can potentially use them
if I want to restrict the other stuff to working with raw-lines like that.

Next, I think the offset-segment option is the best I have so far.
The offsets are going to be counted anyways as the line is drawn,
so its not introducing as much of a new check as the
absolute head/tail points would.
Also, its a bit more flexible since it has the non-indexable, smaller lines.

---

Finally, if future-me is wondering why I didn't just use floating points
and sub-pixel line algorithms,
I, uh, I honestly didn't want to mess with floating-point arithmetic and stuff.
Call me a coward. Its okay.

To be fair, I don't think I really need to though for what I'm doing.


Naming my decisions
==================================================

Okay, so in the code, what should I call it?
This might not seem like a priority,
but I think its really helpful to head into prototyping with names in mind.

rsegm = raw segment \
rline = raw line \
rpoly = raw polygon \
\
segm = offset segment \
line = array-of-segments \
uline = procedural line \
\
poly = line + 1 segment \
upoly = procedural line + 1 segment
