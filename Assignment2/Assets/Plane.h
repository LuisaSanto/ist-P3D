#ifndef PLANE_H
#define PLANE_H

#include "Object.h"
#include "Point.h"
#include "Material.h"
#include "Ray.h"
#include <math.h>
#include <limits>

using namespace std;

class Plane : public Object {
	private:
		Point _point1;
		Point _point2;
		Point _point3;
		float _focalDistance;

	public:
		//Constructors
		Plane();

		Plane(Point p1, Point p2, Point p3, Material material);

		Plane(Point normal, float d);

		//Getters
		// Point getNormal() { return _normal; }
		// Material getMaterial() { return _material; }
		float getFocalDistance() { return _focalDistance; }


		void print();

		//Intersection of a ray
		//virtual float checkRayCollision(Ray ray);
		float checkRayCollision(Ray ray);
		void computeBoundingBox() {};

};

#endif