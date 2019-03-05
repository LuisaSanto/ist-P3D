#ifndef SPHERE_H
#define SPHERE_H

#include "Point.h"

class Sphere {
	private:
		Point _pos;
		float _radius;	
	public:
		Sphere() {}
		Sphere(Point , float radius);
};

#endif