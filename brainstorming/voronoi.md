Voronoi Generation
==================================================

> GreyKeenan/snare/brainstorming

About options for generating a Voronoi Diagram.

<br>

<!-- INDEX -->

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


References (TODO list organize)
==================================================

good fortunes alg sources

* https://jacquesheunis.com/post/fortunes-algorithm/
* https://blog.ivank.net/fortunes-algorithm-and-implementation.html

fortune's alg demonstration

* http://www.raymondhill.net/voronoi/rhill-voronoi.html

a rly good delaunay source

* https://ianthehenry.com/posts/delaunay/

other stuff misc

* https://www.cise.ufl.edu/~ungor/delaunay/delaunay/node5.html
* https://codeforces.com/blog/entry/85638
* https://paulbourke.net/papers/triangulate/
