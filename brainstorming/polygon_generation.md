Polygon Generation
==================================================

> GreyKeenan/snare/brainstorming

Thinking through how I want polygon generation to go.

<br>

<!-- INDEX -->
* Overall Approach

<br>

Overall Approach
==================================================

Ideally:

1. generate continent borders
1. fill it in

However, it might be easier to balloon from the inside out:

1. Generate 'center' shape
1. store shape
1. add bordering shape
1. store shape
1. Update 'center' shape as combined border of both shapes
1. repeat

Alternatively, could:

1. do method 2 above
1. Generate a large random polygon
1. overlay polygon on the map from step 1
  removing stuff that doesnt fit inside, given a minimum size

I'll try to proceed with the first method for now.
I know its *possible*, so lets give it a shot.


Configuration
--------------------------------------------------

I want to be able to configure max-width and min-width values,
so the shapes arent super thin.
Also, a minimum-bordering-amount should be in place,
so you can tell visually when things border each other.


Outwards-in
==================================================

The steps would look something like:

1. Generate a random polygon.
  I'll call it 'George'.
1. Pick a point along George.
1. Walk (a distance) along the border from that point to the next.
1. Create a new point there. This is 1 border of our inner shape.
1. Create a line/point INSIDE the polygon.

  > You can know which side of the line is the inside based on
    when you generated the original polygon.
    HOWEVER, you still need to verify that its inside with other info,
    since you could overshoot the opposite wall of the polygon
    or go too low/high and go past the next line in the sequence.
    Everything to the left (or right) of the original line,
    considering the order of the points,
    should be inside (or outside).
    Then, when you add new shapes to it (later),
    everything outside of them becomes the new inside of George,
    as long as you add their points in the correct order.

1. connect the ends of the new point & the bordering line together.
1. Update George's borders with the new inner bounds from the polygon.
1. repeat

This has some edge cases though:

* What happens when the new polygon would
  collide with George's borders another time?
  If this is disallowed, territories would have
  at most 1 border with George, which is odd.
  If allowed, additional collisions with George
  need to be registered somehow so George's internal bounds can be updated.
  Also, the new polygon's shape has to follow along George's bounds.
* Gaps are possible.
  If disallowed, ... how?
  If allowed, need to be weighted really well,
  otherwise there could be a tendency for donut-like shapes,
  OR there could be incomplete connections.

