#ifndef SPHERE_H
#define SPHERE_H

#include "Point.h"
#include "Material.h"
#include "Ray.h"
#include <math.h>
#include <limits>

using namespace std;

class Sphere {
	private:
		Point _pos;
		float _radius;
		Point _normal;
		Material _material;	
	public:
		//Constructors
		Sphere() {}
		Sphere(Point , float radius, Material material);

		//Getters
		Point getPosition() { return _pos; }
		float getRadius() { return _radius; }
		Material getMaterial() { return _material; }
		Point getNormal() { return _normal; }

		void print();

		//Intersection of a ray
		float intersectSphere(Ray ray);

		void setNormalIntersectionPoint(Point point);


};

#endif