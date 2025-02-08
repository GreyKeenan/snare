
working it out
==================================================

~~~

(a, b) = site point
(x, y) = point-in-parabola
l = height of the sweepline(ascendingY)

length((x,l), (x,y)) == length((a,b), (x,y))
| l - y | = sqrt( (a - x)^2 + (b - y)^2 )

solve for y:


(From fortunes_alg_presentation.pdf & online solution solver.
I'm lazy, sue me.):

    /  -2ax + xx + aa + bb + ll  \
y = |  ------------------------  |   &&   (l != b)
    \          2(-l + b)         /

~~~


storage
==================================================

if points are int16s, the top has a max size of roughly:
`-2 * 2^30 + 4(2^30) = 2^31 + 2^32`.
So, could bound it or could use an int64.

> more precisely:
  `(2^15 - 1)^2 * 6 = 6_442_057_734`.
