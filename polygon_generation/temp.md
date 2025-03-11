TEMPORARY: understanding how edges behave when adding a new site to the beachline
==================================================

<br>

<!-- INDEX -->
* Formatting
* An example of edge behavior

<br>


Formatting
==================================================

I will denote the beachline as:
~~~
{ a b a c ... }
~~~
where single-letters represent sites.

> Remember that the beachline is sorted by ascending-x of breakpoints.

Breakpoints, edges, and vertices
between sites will be denoted with multiple-letters.

* breakpoints: `(ab)`

  > the points where parabolas meet,
    given a directix,
    while the algorithm is in operation.

  > Breakpoint names are order-dependent,
    since sites may have up to 2 breakpoints with another site.
    `(lower-site, higher-site)` is the leftmost breakpoint,
    while `(higher-site, lower-site)` is the rightmost breakpoint.
* vertices: `[ab]`

  > the final resting place of a breakpoint
    once the algorithm/sweepline has finished with it.
    A vertice will have at least 3 aliases,
    corresponding to the 3 breakpoints which landed there.
* edges: `(abba) or [abba]`

  > the lines drawn between breakpoints or vertices respectively.
    A `*` indicates that the line is unterminated on that side.
    Eg, `[*abba]` is the line `(ab) -> [ba]` where `(ab)` was never terminated.
    Alternatively, it could be `[abba*]` or something.
    The infinite-end may be omitted when it doesnt have
    an associated breakpoint,
    which may happen for the first and rightmost/leftmost sites.
    Specifying an unterminated edge for `(*abba)`
    unfinished edges is usually redundant,
    since they are by definition unterminated.


An example of edge behavior
==================================================

Consider the beachline `{ k l }`.

We encounter a site event for site `m`. \
`m.x` > `(kl).x`, so `m` will bisect parabola `l`.
(and `m.y > l.y`).

After inserting `m`, the beachline looks like this: \
`{ k l m l }`.

Remember that between each site in the beachline, there is a breakpoint,
and those breakpoints are drawing the edges.
To be precise, our beachline is: \
` { k (kl) l (lm) m (ml) l }`.
So, we also have to add two references to an edge being drawn elsewhere.

The final edges would be something like:
`[*kl], [lmkm*], [lmml*]`.
How do we get there?

Well, lets assume that there are no more site events after `m`,
and there were no sites before `k` and `l`.
That means there will be 1 more event in the queue:
the circle event which was created when we added `m`.

That circle event will be the convergence of the parabola
between `(kl)` and `(lm)`.
When that happens, `[kl] == [lm]`,
and the beachline would become:
`{ k m l }`.

Here, the edges/lines referenced by
`(kl)` and `(lm)` would have their respective ends set to the same value,
and `(kl) & (lm)` would be removed from the beachline,
meaning that end can no longer be altered.
Then, the new `(lmkm)` edge would be started,
where `(km)` points to its respective end of the edge to modify,
and `[lm]` is already known of course.


### an alternative

Let's say `m.x` < `(kl).x` instead,
so `m` bisects `k`.

~~~
{ k (kl)_0 l }
{ k m k (kl)_1 l }
{ k m l }

(kl)_0 = (kl)_1

[mk] = [kl]
[*kmmk]
[kl*]
[mkml*]
~~~

So here we can see that,
when we are bisecting something with an existing breakpoint to the right,
it moves to the right.
In hindsight, that makes total sense,
as its the same thing that happens to left-breakpoint.
I was just thinking of them differently
because I'm planning to store the right-breakpoint with its left-site.
