Lines
==================================================

> GreyKeenan/snare/brainstorming

Some sort of underlying module which
handles basic line & polygon representations/functionality.

<br>

<!-- INDEX -->
* Main Types/Representations
  * Point
  * Lines

<br>

Main Types/Representations
==================================================

Point
--------------------------------------------------

~~~ c
struct Point {
	short x;
	short y;
};
~~~


Lines
--------------------------------------------------

Lines are just arrays of points.

A polygon is just a line, with the implication that
the first and last points are connected.
Ideally, the order of the points is clockwise around the polygon.
Some functions may assume this.


Other Functions
==================================================

* detect whether currently inside a polygon
* ? detect inside a set of a polygons ?
* detect collision with a line
  * How to handle rounding?


