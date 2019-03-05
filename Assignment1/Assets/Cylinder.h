#ifndef CYLINDER_H
#define CYLINDER_H

#include "Point.h"

class Cylinder {
	private:
		Point _base, _apex;
		float _base_radius, _apex_radius;
	public:
		Cylinder() {}
		Cylinder(Point base, Point apex, float base_radius, float apex_radius);
};

#endif