~~~

site1 = (a,b)
site2 = (c,d)
midpoints = (x,y)

root((a-c)^2 + (b-d)^2)/2 = root((a-x)^2 + (b-y)^2) = root((c-x)^2 + (d-y)^2)


root((a-x)^2 + (b-y)^2) = root((c-x)^2 + (d-y)^2)
(a-x)^2 + (b-y)^2 = (c-x)^2 + (d-y)^2
(a-x)(a-x) + (b-y)(b-y) = (c-x)(c-x) + (d-y)(d-y)
aa + -2ax + xx + bb + -2by + yy = cc + -2cx + xx + dd + -2dy + yy
aa + -2ax + bb + -2by = cc + -2cx + dd + -2dy
aa + bb + -cc + -dd = 2ax + 2by + -2cx + -2dy
(aa + bb + -cc + -dd)/2 = ax + by + -cx + -dy
x(a - c) + y(b - d) = (aa + bb + -cc + -dd)(1/2)

x(a - c) + y(b - d) = (aa + bb + -cc + -dd)(1/2)
x(a - c) = (aa + bb + -cc + -dd)(1/2) - y(b - d)
/              aa + bb + -cc + -dd     -y(b - d)
:  x(a - c) = --------------------- + -----------
\                       2                 1
/              aa + bb + -cc + -dd     -2y(b - d)
:  x(a - c) = --------------------- + ------------
\                       2                 2
/              aa + bb + -cc + -dd + -2y(b - d)
:  x(a - c) = ----------------------------------
\                             2
/       aa + bb + -cc + -dd + -2y(b - d)       1
:  x = ---------------------------------- * --------
\                     2                      a + -c
/       aa + bb + -cc + -dd + -2y(b - d)
:  x = ----------------------------------
\                     2(a + -c)


(transforming to check my work with symbolab)

/       (aa + bb + -cc + -dd + -2y(b - d))(-1)
:  x = ----------------------------------------
\                     2(a + -c)(-1)
/       -aa + -bb + cc + dd + 2y(b - d)
:  x = ---------------------------------
\                     2(-a + c)

yep!

so then:

x(a - c) + y(b - d) = (aa + bb + -cc + -dd)(1/2)
/    -aa + -bb + cc + dd + 2y(b - d)                      aa + bb + -cc + -dd
:  (---------------------------------)(a - c) + y(b-d) = ---------------------
\               2(-a + c)                                          2
/            aa + bb + -cc + -dd        -aa + -bb + cc + dd + 2y(b - d)
:  y(b-d) = --------------------- + -1(---------------------------------)(a - c)
\                     2                           2(-a + c)
/            aa + bb + -cc + -dd      -aa + -bb + cc + dd + 2y(b - d)
:  y(b-d) = --------------------- + (---------------------------------)(-a + c)
\                     2                         2(-a + c)
/            aa + bb + -cc + -dd     -aa + -bb + cc + dd + 2y(b - d)
:  y(b-d) = --------------------- + ---------------------------------
\                     2                            2
/            aa + bb + -cc + -dd     -aa + -bb + cc + dd     2y(b - d)
:  y(b-d) = --------------------- + --------------------- + -----------
\                     2                            2           2
y(b-d) = y(b-d)
oops crap

/    -aa + -bb + cc + dd + 2y(b - d)                      aa + bb + -cc + -dd
:  (---------------------------------)(a - c) + y(b-d) = ---------------------
\               2(-a + c)                                          2
/      -aa + -bb + cc + dd + 2y(b - d)                       aa + bb + -cc + -dd
:  -1(---------------------------------)(a - c) + -y(b-d) = ---------------------
\                2(-a + c)                                          -2
/    -aa + -bb + cc + dd + 2y(b - d)                aa + bb + -cc + -dd
:  (---------------------------------) + -y(b-d) = ---------------------
\              2                                           -2
/   -aa + -bb + cc + dd     2y(b - d)               aa + bb + -cc + -dd
:  --------------------- + ----------- + -y(b-d) = ---------------------
\             2                 2                           -2
/   -aa + -bb + cc + dd                        aa + bb + -cc + -dd
:  --------------------- + y(b-d) + -y(b-d) = ---------------------
\             2                                             -2
/                      aa + bb + -cc + -dd     -aa + -bb + cc + dd
:  y(b-d) + -y(b-d) = --------------------- + ---------------------
\                                -2                  -2
0 = 0
fuck I'm so dumb of course this is how this works


I'm so overcomplicating this.
Ofc, the direct midpoint for two points is their average.
duh.

Then, the new slope is the old slope flipped & inverted.
x/y  ->  -(y/x)
and then (b = y - mx) ofc


~~~




Breakpoint identification
==================================================

Its the point equidistant to the liney, site a, and site b.

~~~

l = line y
(bx, by) = site b
(ax, ay) = site a
(cx, cy) = the target
e = a or b;

d = dist(a, c) = dist(b, c) = l - cy
cy = l - d

dist(e, c) = l - cy
root((ex - cx)^2 + (ey - cy)^2) = l - cy
(ex - cx)^2 + (ey - cy)^2 = ll + -2lcy + cycy
exex + -2excx + cxcx + eyey + -2eycy + cycy = ll + -2lcy + cycy
exex + -2excx + cxcx + eyey + -2eycy = ll + -2lcy

... this is just the parabola formula im dumb
/      (a + -x)^2 + bb + -ll
:  y = --------------------
\          2(b + -l)
/       (ex + -cx)^2 + eyey + -ll
:  cy = --------------------------
\          2(ey + -l)


midpoint((cx, l), e) can form a right triangle with c
or (mid(a, b), e, c)

I'm just trying to find a shortcut
instead of the circumcenter formula,
since I know other info abt it.

~~~

Testing my approach
--------------------------------------------------

~~~

c - y = bx + y = ay + x

c - y = bx + y
c - bx = 2y
(c - bx)/2 = y

bx + y = ay + x
-ay + y = -bx + x
(-a + 1)y = -bx + x
(-bx + x)/(-a + 1) = y

(c - bx)/2 = (-bx + x)/(-a + 1)
...
(c/2)/(b/2 + (b + 1)/(a + 1)) = x

~~~

TEMP
-------

~~~



root((ax - cx)^2 + (ay - cy)^2) = root((bx - cx)^2 + (by - cy)^2)
axax - 2axcx + cxcx + ayay + -2aycy + cycy = bxbx - 2bxcx + cxcx + byby + -2bycy + cycy
axax + -2axcx + ayay + -2aycy = bxbx + -2bxcx + byby + -2bycy
-2axcx + -2aycy + 2bxcx + 2bycy = -axax + -ayay + bxbx + byby
cx(-2ax + 2bx) + cy(-2ay + 2by) =
/       -cx(-2ax + 2bx) + -axax + -ayay + bxbx + byby
: cy = -----------------------------------------------
\                 2(by - ay)

/       (ex + -cx)^2 + eyey + -ll    -cx(-2ax + 2bx) + -axax + -ayay + bxbx + byby
:  cy = ------------------------- = ------------------------------------------------
\          2(ey + -l)                                  2(by - ay)

/  (ax + -cx)^2 + ayay + -ll    -cx(-2ax + 2bx) + -axax + -ayay + bxbx + byby
:  ------------------------- = ------------------------------------------------
\     2(ay + -l)                                  2(by - ay)
/  (ax + -cx)^2 + ayay + -ll    -cx(-2ax + 2bx) + -axax + -ayay + bxbx + byby
:  ------------------------- = ------------------------------------------------
\     ay + -l                                  by - ay
/  (ax + -cx)^2     ayay + -ll    -cx(-2ax + 2bx)     -axax + -ayay + bxbx + byby
:  ------------- + ------------ = ---------------- + -----------------------------
\   ay + -l          ay + -l         by - ay              by - ay
	
	/   (ax + -cx)^2
	:  --------------
	\     ay + -l
	/   axax + -2axcx + cxcx
	:  ----------------------
	\        ay + -l
	/   axax        -2axcx + cxcx
	:  --------- + ---------------
	\   ay + -l       ay + -l
/   axax        -2axcx + cxcx     ayay + -ll    -cx(-2ax + 2bx)     -axax + -ayay + bxbx + byby
:  --------- + --------------- + ------------ = ---------------- + -----------------------------
\   ay + -l       ay + -l          ay + -l         by - ay              by - ay

	/  -cx(-2ax + 2bx)
	:  ----------------
	\     by - ay
	/           cx
	:  --------------------------
	\   (by - ay) / -(-2ax + 2bx)
	/           cx
	:  --------------------------
	\   (by - ay) / 2(ax + -bx)
/   axax        -2axcx + cxcx     ayay + -ll     -axax + -ayay + bxbx + byby             cx
:  --------- + --------------- + ------------ = ----------------------------- +  -------------------------
\   ay + -l       ay + -l          ay + -l           by - ay                      (by - ay) / 2(ax + -bx)
/   axax        -2axcx + cxcx     ayay + -ll        -axax + -ayay + bxbx + byby             cx
:  --------- + --------------- + ------------ + -1(-----------------------------) = -------------------------
\   ay + -l       ay + -l          ay + -l             by - ay                       (by - ay) / 2(ax + -bx)
/   axax           ayay + -ll        -axax + -ayay + bxbx + byby             cx                    -2axcx + cxcx
:  --------- +  + ------------ + -1(-----------------------------) = ------------------------- + -(---------------)
\   ay + -l         ay + -l             by - ay                       (by - ay) / 2(ax + -bx)        ay + -l
/          cx                    -2axcx + cxcx
:  ------------------------- + -(---------------) = ...
\   (by - ay) / 2(ax + -bx)        ay + -l
/          cx                   -2axcx + cxcx
:  ------------------------- + --------------- = ...
\   (by - ay) / 2(ax + -bx)       -ay + l
/          cx(-ay + l)                    (-2axcx + cxcx)((by - ay) / 2(ax + -bx))
:  ----------------------------------- + ------------------------------------------ = ...
\   ((by - ay) / 2(ax + -bx))(-ay + l)       (-ay + l)((by - ay) / 2(ax + -bx))
/          cx(-ay + l) + (-2axcx + cxcx)((by - ay) / 2(ax + -bx))
:  --------------------------------------------------------------- = ...
\            ((by - ay) / 2(ax + -bx))(-ay + l)


~~~



~~~

sqrt((a-x)^2+(b-y)^2)= sqrt((c-x)^2+(d-y)^2); solve for y
->
\frac{c^2-2cx+d^2-a^2+2ax-b^2}{2\left(-b+d\right)}

sqrt((a-x)^2+(b-y)^2)= l-y; solve for y;
->
\frac{l^2-a^2+2ax-x^2-b^2}{2\left(l-b\right)}

\frac{c^2-2cx+d^2-a^2+2ax-b^2}{2\left(-b+d\right)} = \frac{l^2-a^2+2ax-x^2-b^2}{2\left(l-b\right)}
->
x=\frac{-da+la-lc+cb+\sqrt{d^3b-ld^3+l^2d^2+ld^2b-2d^2b^2+db^3+c^2db+da^2b+ldb^2+2lcda-lc^2d-lda^2-2l^2db-2cdab+l^2c^2+l^2a^2+l^2b^2+2lcab-2l^2ca-lb^3-lc^2b-la^2b}}{-d+b},\:
x=\frac{-da+la-lc+cb-\sqrt{d^3b-ld^3+l^2d^2+ld^2b-2d^2b^2+db^3+c^2db+da^2b+ldb^2+2lcda-lc^2d-lda^2-2l^2db-2cdab+l^2c^2+l^2a^2+l^2b^2+2lcab-2l^2ca-lb^3-lc^2b-la^2b}}{-d+b};
\quad \:-d+b\ne \:0


~~~




FURCKL

The center of 3 points is just their average?


root((ax - cx)^2 + (ay - cy)^2) = root((bx - cx)^2 + (by - cy)^2)
axax + -2axcx + ayay + -2aycy = bxbx + -2bxcx + byby + -2bycy
0 = -axax + 2axcx + -ayay + 2aycy + bxbx + -2bxcx + byby + -2bycy
0 = -axax + -ayay + bxbx + byby + cx(2ax + -2bx) + cy(2ay + -2by)
cx(2ax - 2bx) + cy(2ay - 2by) = axax + ayay - bxbx - byby
dejavu


~~~


Finding it by perpendicular intersection
==================================================

~~~

intersection:
(yint[1] - yint[2])/(slope[2] - slope[1]) = x
(-yint[1]slope[2] + yint[2]slope[1])/(slope[1] - slope[2]) = y




~~~





UHH
======

~~~

/      (a + -x)^2 + bb + -ll
:  y = --------------------
\          2(b + -l)

sites: a,b & c,d

/       (a + -x)^2 + bb + -ll     (c + -x)^2 + dd + -ll
:  y = ----------------------- = -----------------------
\          2(b + -l)                 2(d + -l)
/   (a + -x)^2 + bb + -ll     (c + -x)^2 + dd + -ll
:  ----------------------- - ----------------------- = 0
\      2(b + -l)                 2(d + -l)
/   ((a + -x)^2 + bb + -ll)2(d-l)       ((c + -x)^2 + dd + -ll)2(b-l)
:  ------------------------------- + -(-------------------------------)
\      4(b - l)(d - l)                    4(b - l)(d - l)
/   ((a + -x)^2 + bb + -ll)2(d-l) - ((c + -x)^2 + dd + -ll)2(b-l)
:  ---------------------------------------------------------------
\                4(b - l)(d - l)
/   (((a + -x)^2 + bb + -ll)(d-l) - ((c + -x)^2 + dd + -ll)(b-l))2
:  ----------------------------------------------------------------
\                4(b - l)(d - l)
/   ((a + -x)^2 + bb + -ll)(d-l) - ((c + -x)^2 + dd + -ll)(b-l)
:  --------------------------------------------------------------
\                2(b - l)(d - l)
	((a + -x)^2 + bb + -ll)(d-l)
	(aa + -2ax + xx + bb + -ll)(d - l)
	(aa + -2ax + xx)(d - l) + (d - l)bb + (d - l)(-ll)
	(aa + -2ax + xx)(d - l) + bbd + -bbl + -dll + lll

	-((c + -x)^2 + dd + -ll)(b-l)
	-(cc + -2cx + xx + dd + -ll)(b - l)
	(-cc + 2cx + -xx + -dd + ll)(b - l)
	(-cc + 2cx + -xx)(b - l) + -ddb + ddl + llb + -lll
/   (aa + -2ax + xx)(d - l) + bbd + -bbl + -dll + lll + (-cc + 2cx + -xx)(b - l) + -ddb + ddl + llb + -lll
:  --------------------------------------------------------------------------------------------------------
\                             2(b - l)(d - l)
/   (aa + -2ax + xx)(d - l) + bbd + -bbl + -dll + (-cc + 2cx + -xx)(b - l) + -ddb + ddl + llb
:  -------------------------------------------------------------------------------------------
\                             2(b - l)(d - l)
/   (aa + -2ax + xx)(d - l) + (-cc + 2cx + -xx)(b - l) + bbd + -bbl + -dll + -ddb + ddl + llb
:  -------------------------------------------------------------------------------------------
\                             2(b - l)(d - l)
	(aa + -2ax + xx)(d - l)
	aad + -aal + -2axd + 2axl + xxd + -xxl

	(-cc + 2cx + -xx)(b - l)
	-ccb + ccl + 2cxb + -2cxl + -xxb + xxl
/   aad + -aal + -2axd + 2axl + xxd + -xxl + -ccb + ccl + 2cxb + -2cxl + -xxb + xxl + bbd + -bbl + -dll + -ddb + ddl + llb
:  ------------------------------------------------------------------------------------------------------------------------
\                             2(b - l)(d - l)
/   aad + -aal + -2axd + 2axl + xxd + -ccb + ccl + 2cxb + -2cxl + -xxb + bbd + -bbl + -dll + -ddb + ddl + llb
:  -----------------------------------------------------------------------------------------------------------
\                             2(b - l)(d - l)
/   -2axd + 2axl + 2cxb + -2cxl + -xxb + xxd + aad + -aal + -ccb + ccl + bbd + -bbl + -dll + -ddb + ddl + llb
:  -----------------------------------------------------------------------------------------------------------
\                             2(b - l)(d - l)
/   x(-2ad + 2al + 2cb + -2cl) + xx(d + -b) + aad + -aal + -ccb + ccl + bbd + -bbl + -dll + -ddb + ddl + llb
:  ----------------------------------------------------------------------------------------------------------
\                             2(b - l)(d - l)

	s = aad + -aal + -ccb + ccl + bbd + -bbl + -dll + -ddb + ddl + llb
	u = 2(b - l)(d - l)

/   x(-2ad + 2al + 2cb + -2cl) + xx(d + -b) + s
:  ---------------------------------------------
\                      u
/   x(-2ad + 2al + 2cb + -2cl)     xx(d + -b)     s
:  ---------------------------- + ------------ + ---
\              u                        u         u
/      (-2ad + 2al + 2cb + -2cl)         (d + -b)     s
:  (x)--------------------------- + (xx)---------- + --- = 0
\                u                          u         u

	m = (-2ad + 2al + 2cb + -2cl)
	n = (d + -b)

/      m         n     s
:  (x)--- + (xx)--- + --- = 0
\      u         u     u
x(m/u) + xx(n/u) + s/u = 0
xx(n/u) + x(m/u) + s/u = 0
	axx + bx + c = 0

/       -(m/u) +/- root((m/u)^2 + 4(n/u)(s/u))
:  x = ------------------------------------
\                     2(n/u)

Okay so, like, that approach works I guess,
even if I made a small mistake somewhere.
BUT it creates a massive honkin formula.

How about we consider that we can get the slope of the line directly btwn both sites.

site = (c,d)

y = mx + b
/      (c + -x)^2 + dd + -ll
:  y = --------------------
\          2(d + -l)

/      (c + -x)^2 + dd + -ll
:  y = ---------------------- = mx + b
\          2(d + -l)
/   cc + -2cx + xx + dd + -ll
:  --------------------------- =
\          2(d + -l)


Okay, I just learnt about a bit of stuff thats probably important to know about parabolas.
Lets take the parabola in vertex form.

a(x-h)^2 + k = y
mx + b = y

a(x - h)^2 + k = mx + b
axx + -a2xh + ahh + k = mx + b
axx + -a2xh + ahh + k + -mx + -b = 0
axx + x(-a2h + -m) + (ahh + k + -b) = 0

/       -(-a2h - m) +/- root( (-a2h - m)^2 - 4(a)(ahh + k - b) )
:  x = ----------------------------------------------------------
\                             2a
/       2ah + m +/- root( 4aahh + 4ahm + mm + -4aahh + -4ak + 4ab )
:  x = -------------------------------------------------------------
\                             2a
/       2ah + m +/- root( 4ahm + mm + -4ak + 4ab )
:  x = --------------------------------------------
\                             2a
/       2ah + m +/- root( 4a(hm + b - k) + mm )
:  x = -----------------------------------------
\                      2a


alternatively:

a[1](x-h[1])^2 + k[1] = a[2](x-h[2])^2 + k[2]

1: a, h, k
2: b, i, j

https://www.symbolab.com/solver/equation-calculator/solve%20for%20x%3B%20a%5Cleft(x-h%5Cright)%5E%7B2%7D%20%2B%20k%20%3D%20b%5Cleft(x-i%5Cright)%5E%7B2%7D%20%2B%20j?or=input

/       ah - ib +/- root( kb + abhh + aiib - jb - 2aibh + aj - ak )
:  x = -------------------------------------------------------------
\                             a - b
	 kb + abhh + aiib - jb - 2aibh + aj - ak
	 b(ahh + -2aih + aii + -j) + a(j - k)
	 b(a(hh + -2ih + ii) + -j) + a(j - k)
	 ab(h - i)^2 + -jb + a(j - k)
	 a(j - k) + ab(h - i)^2 + -jb
/       ah - ib +/- root( a(j - k) + ab(h - i)^2 + -jb )
:  x = --------------------------------------------------
\                        a - b






Okay, so, using the perpendicular line & parabola intersection,
what do we need?

line_y 'l'
2 sites: d, e

midpoint = (d + e) / 2
perp_slope = -1 * (d.x - e.x)/(d.y - e.y)
perp_yintercept = midpoint.y - (perp_slope)midpoint.x

parab_vertex 'v' = d or e
a = 1/(4p)
p = (v.x - l)/2
h == v.x
k == v.y

Finally,
to confirm the resulting 'x' options,
pick the one which is between e.x and d.x
