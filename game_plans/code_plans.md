Code Plans
==================================================

<br>

<!-- INDEX -->
* Armies

<br>


Armies
==================================================

~~~

#define INFANTRY
#define CAVALRY
#define ARTILLERY

struct company {
	uint unit;
	uint count;
	
	uint energy;
	uint loyalty;
};

struct unit { // in the interest of future expansion
	uint value;

	uint range;
	uint energy;   // how many moves it can make each turn

	float attack;  // >= 0
	float defense; // >= 0
};

const struct unit units[3];

units[INFANTRY ] = { 1,  0, 1, 1, 1    };
units[CAVALRY  ] = { 5,  0, 3, 1, 1    };
units[ARTILLERY] = { 10, 1, 1, 1, 0.5f };

//note: multiple arrays might be more effective than an array of structs

~~~


Map
==================================================

Say the map is a "complete", doubly-linked etc, Voronoi Diagram.
What subsection of that information do different modules need,
and how does that info need to be traversed?

Rendering & Input

* info
  * vertices
  * site points
* traversal
  * loop through regions to draw them
  * given an arbitrary coordinate,
    identify the region it falls within.

Game logic:

* from a given territory, iterate through its neighbors
* loop through territories within a continent

Uhh ... I think thats it?
