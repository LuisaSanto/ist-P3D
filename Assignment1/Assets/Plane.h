#ifndef PLANE_H
#define PLANE_H

#include "Point.h"
#include "Material.h"
#include "Ray.h"
#include <math.h>
#include <limits>

using namespace std;

class Plane {
	private:
		Point _point1;
		Point _point2;
		Point _point3;
		Point _normal;
		Material _material;	
	public:
		//Constructors
		Plane() {}
		Plane(Point , Point ,Point ,Material material);

		//Getters
		Point getNormal() { return _normal; }

		void print();

		//Intersection of a ray
		float intersectPlane(Ray ray);


};

#endif