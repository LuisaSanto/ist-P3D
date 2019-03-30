#ifndef POLYGON_H
#define POLYGON_H

#include "Object.h"
#include "Point.h"
#include "Material.h"
#include "Ray.h"
#include <math.h>
#include <limits>

using namespace std;

class Polygon : public Object {
	private:
		Point _point1;
		Point _point2;
		Point _point3;

	public:
		//Constructors
		Polygon() {}
		Polygon(Point p1, Point p2, Point p3, Material material) : Object(material) {
			_point1 = p1;
			_point2 = p2;
			_point3 = p3;
			_material = material;

			_normal = (p2 - p1).cross(p3 - p1);
			_normal.normalize();
		};

		//Getters
		//Point getNormal() { return _normal; }
		//Material getMaterial() { return _material; }
		
		void print();

		//Intersection of a ray
		float checkRayCollision(Ray ray);


};

#endif