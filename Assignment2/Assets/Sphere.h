#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "Point.h"
#include "Material.h"
#include "Ray.h"
#include <math.h>
#include <limits>

using namespace std;

class Sphere : public Object {
	private:
		Point _pos;
		float _radius;
		Material _material;	
		Point _normal;

	public:
		//Constructors
		Sphere() {}
		Sphere(Point pos, float radius, Material material) : Object(material) {
			_pos = pos;
			_radius = radius;
		}

		//Getters
		Point getPosition() { return _pos; }
		float getRadius() { return _radius; }
		//Material getMaterial() { return _material; }
		//Point getNormal() { return _normal; }

		void print();

		//Intersection of a ray
		float checkRayCollision(Ray ray);

		void setNormalIntersectionPoint(Point point, float d);
		void computeBoundingBox();


};

#endif