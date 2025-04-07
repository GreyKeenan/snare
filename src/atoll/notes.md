Notes
==================================================

> greykeenan/snare.git

<br>

<!-- INDEX -->

<br>


Alg Steps
==================================================

Input: a *set* of points (sites).
(For our purposes, it is assumed that the set has 1 bottommost point.
Horizontally-aligned bottommost-points can be handled as a special case.)

Output: The vertices and the lines between them

Queue: a queue of points, ordered by ascending-y.
Points are labelled as corresponding either to a site or the center of a potential-circle-event.
Two points may be identical, with different labels.

Beachline: an ordered sequence of arcs, represented by their foci,
and separated by their breakpoints.
`TODO: EXPLAIN`

> i used "intersection event", "circle event", and "edge event" interchangeably

---

let S be the input sites
let Q be the queue
let B be the beachline

pop(Q) removes & yields the lowest-y point from the queue
Q[0] is the lowest-y point in the queue

leftbp(i)
rightbp(i)  give the left/right breakpoints of an index to B, respectively
	note that leftbp(i) == rightbp(i - 1)

so, the algorithm is roughly:

	Q += S
	assert(Q.length >= 1)

	bottom_site = pop(Q)
	assert(Q[0].y != bottom_site.y)

	B[0] = bottom_site

	while (Q.length > 0) {
		p = pop(Q)

		if (p is a site) {
			let (a) be the index of an arc in B where
			( leftbp(a).x < p.x < rightbp(a) ).

			create a the new edge who borders (p) and the site of (a)
				
			if (a) already has an associated intersection-event, delete it from Q

			insert ( B[a], p, B[a] ) in place of B[a]
				note that (a + 1) would be the index of the newly-inserted (p), then

			if an intersection exists between leftbp(a) and rightbp(a), insert it into Q
			if an intersection exists between leftbp(a + 2) and rightpb(a + 2), insert it into Q
		}

		if (p is a circle event) {
			let (a) be the index of an arc in B where
			(p) is the intersection of leftbp(a) and rightbp(a).

			create the new edge who borders the sites of B[a - 1] and B[a + 1]

			if (a - 1) has an associated intersection-event, delete it from Q
			if (a + 1) has an associated intersection-event, delete it from Q

			remove B[a]
				again, note how the index shifts

			if an intersection exists between leftbp(a - 1) and rightbp(a - 1), insert it into Q.
			if an intersection exists between leftbp(a) and rightbp(a), insert it into Q

			the point (p) becomes a vertex, on one end of these lines:
				* the line bordering the sites of (a - 1) & (a)
				* the line bordering the sites of (a) & (a + 1)
				* the line bordering the sites of (a - 1) & (a + 1)

		}
	}

