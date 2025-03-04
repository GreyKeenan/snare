initial exploration
==================================================

<br>

<!-- INDEX -->
* Objectives
* Exploration
  * Spitballing
  * Emerging questions/problems/etc
* Locking in
  * Addressing those questions

<br>

Okay, I've lost steam on implementing Fortune's Algorithm. Why?

I think It's because I don't have a framework to place it in yet.
Like, I still haven't worked through or even really approached
how the game itself will work.
And that's kind of important for motivation.

Okay, so, lets give this a shot.


Objectives
==================================================

### to incorporate uneven tiles

Inspired by the uneven territories of board games,
Risk in particular,
I want to make a strategy game which uses uneven tiles
rather than hexagons or a grid or whatever.
You could say its the underlying gimmick.

In exploring generating these uneven-polygon "grids" *randomly*,
I've landed on am algorithm which seems fun
or like a good experience for me to implement.
So, I also want to (eventually) add a random-generation variant,
if not have that be the default.


### to prioritize simplicity

For practicality and elegance,
I want to keep the mechanics as simple as possible,
while still providing depth of strategy ofc.
Ultimately, its just a little strategy game,
and I want to complete it shortly.


Exploration
==================================================

Okay, so, lets split this into some categories:

* mechanics
  * terrain
  * resources
  * movement
  * attacking
  * terraforming
  * game objective
  * information
* aesthetic
  * narrative
  * visual & audio

These dont encapsulate everything ofc ofc,
but there somewhere to start.


Spitballing
--------------------------------------------------

Okay, thinking about each of those,
Imma spitball some ideas:

* encouraging moving in formations somehow
* more-varied objectives than just "kill everything on the map"
  * escorting OR reaching a certain location.
    These are pretty similar.
  * escaping. Wait, no, thats just the same as the above
    dressed up in different language
  * Finding an unknown location?
    Thats a little different.
    Maybe you can find a map/guide or something.
    This could even be, like, fighting to get a macguffin.
    It could be like fantasy-archaeology indiana-jones style.
  * building something?
    Maybe you have to build a castle or network or something, catan style.
    Perhaps you need those artifacts as building material?
  * just, surviving long enough
  * ?? learning something ??
    How would that work in a way thats not just finding something, though.
    There could be some sort of randomized mechanic to trial-and-error for?
* basic terrain variations just as with any game like this
  * one you cant move on
  * one you can only move on under certain conditions
  * one you can only move on directionally
  * things that damage you
  * things one person can move on and not the other team
  * player-made structures
  * etc
* facilitating interesting combat strategy
  * directional abilities?
    This would be ... weird with uneven tiles, but maybe neat?
  * 'troops' boost each other by proximity?
  * army-mechanics.
    Does a single tile contain 1 unit,
    or does it contain an army?
    Is that army just a number,
    or can it contain unique units within it?
    * maybe it has, like, a "commander" which gives it unqiue abilities,
      and then a troop count for their soldiers.
    * or it has abilities depending on its makeup.
      Like, if it contains 1 artillery it can shoot a ranged attack,
      and if it has more artillery the attack is better.
      Then, it could have, say, shield bearers for better defense.
      Of course, you would want to limit this so its not just giant stacks.
    * army mechanics go against the fantasy-archaeology thing seemingly,
      but not necessarily.
      You could have both, and maybe that would make smaller limits make sense.
    * you can split the army into separate, weaker armies.
      In effect, this is a compromise.
      Rather than the space containing a single-number army,
      it contains a bunch of smaller-number, counts-of-units.
    * uneven movement capabilities forces you to decide between
      splitting the army or catering to the slowest units.
    * space-limitations.
      Potentially?
      These could be relative to tile-size or some sort of resource.
    * Along risk-inspiration lines,
      maybe its just artillery, cavalry, infantry.
      Artillery is a ranged attack
      and cavalry can "dash", where they move-then-attack.
      Maybe infantry has better defense or something,
      OR perhaps they defend first?
      So, if someone attacks a space containing all 3,
      they have to get through the infantry first before
      damaging the other two.
      Is that too strong though?
      It could be too much defense for the artillery.
      Who gets hit??
  * Rather than "training" troops,
    the primary method of gaining units is by finding or recruiting somehow.
* Resources
  * In the interest of simplicity,
    I think there should be 1 resource at most, if even.
    Maybe not, since troops are a resource.


Emerging questions/problems/etc
--------------------------------------------------

### attack range

How does a ranged attack work with uneven tiles?

* multiple tile long range, simple as that.

  > This would be really weird and broken for large tiles.
* radius-ranges

  > This kind of just is anachronistic with the tile system.
    That's not *necessarily* awful, but I dont like the idea in this case.

Why isnt this an issue with Risk?
Well, every attack has the same range.
It just can hit adjacent tiles.

Okay, well, what if a ranged attack wasn't actually a loner reach?
Or, maybe a better way to conceptualize what I mean is:
a melee attack has a range of `0`,
and a ranged attack is a range of `1`.
So, when you melee attack, you move into that space,
and when you ranged attack, you still just attack adjacent squares,
but you don't move there.


Locking in
==================================================

The fantasy-archaeology approach is cool thematically,
but I think the simpler risk-inspired idea is better for this project.

So, what do we have so far?

* uneven tile map, etc etc
* 3 types of unit
  * Infantry, perhaps with some sort of defense benefit,
    although maybe theyre better defenders just because theyre less expensive.
  * Cavalry, with some sort of movement benefit
  * Artillery, with a ranged attack
* Ranged attacks are "strikes",
  in that they hit an adjacent territory without moving into it.
* *maybe* the 3 types can cohabitate a single territory,
  or maybe they stay separated by type,
  but a given type can stack to create a larger-count of that type.

There's some potential there, at least for something simple!
It does leave some important questions though:

* How are the attacks calculated?
* Where do you get troops from?
  * and how/when do you get different types?
    I like the idea of maintaining the 1/5/10 ratio from Risk somehow.
* Defense benefit?
* Movement benefit?
* Cohabitation?
  If so, who is hurt by attacks?


Addressing those questions
--------------------------------------------------

### Where do you get troops from?

### How are attacks calculated?

**this doesnt work**

For simplicity & experimentation purposes,
I want the outcome to be
purely a function of attack & defense force counts/weights.

~~~
bool battle(uint8_t *attacker, uint8_t *defender);
~~~

Then, the calculation can be swapped easily.
For defense or attack bonuses,
a multiplier can be applied before calling `battle()`.

**WAIT**

that doesnt work for everything
because artillery needs to be different.

Unless?
Maybe the artillery *does* work this way,
its just that they don't take damage for the losses.


### If cohabitation, who is hit?

Maybe troops are placed along a specific edge of the territory.
When you attack from a given direction, you attack that edge first.
If you defeat that edge, or if nothing was along that edge,
you can then proceed to attack *any* other edge.
(or maybe just adjacent ones? idk.

This is interesting,
although it means the territory shapes cant be *too* complex/natural.

Also, is this cumbersome?
Like, will it be annoying to allocate your troops every time?

Also also,
how does this affect attacking?
Can you only attack from the edge you started along?
Maybe you can place troops in the center,
and they can attack *any* edge but not defend?

How free are you to allocate troops along edges?
I was thinking it would be any number of troops to any edge,
but maybe its just 1 unit type to an edge?
Or maybe just the infantry can do this?

Maybe its out of your control.
Maybe when infantry enter a territory,
they are automatically guarding against
the exactly-opposite edge from the one they entered through.
Then, when they attack (?or move?),
they pivot to face whatever direction that was.
When facing a direction,
they get a defense bonus & take damage first!

This could be extended to the artillery in a similar way.
They are placed along the edge they entered *from*.
If attacked from that direction,
they get 0 defense.

**hold up!**
This is quickly getting more complicated.
For now, lets just say that there is no cohabitation,
EXCEPT in cities/forts or whatever they are.
Then, *that* can be the defense bonus of forts!
Then, in forts, damage goes to
infantry, then cavalry, then artillery.


Misc
--------------------------------------------------

* If you try to move onto your own unit, they swap places.
  Unless theyre of the same type.
  Then they add together, unless theyre at the max,
  in which case they merge as much as possible then swap.
