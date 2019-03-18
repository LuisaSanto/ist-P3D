#ifndef POLYGON_H
#define POLYGON_H

#include "Point.h"
#include "Material.h"
#include "Ray.h"
#include <math.h>
#include <limits>

using namespace std;

class Polygon {
	private:
		Point _point1;
		Point _point2;
		Point _point3;
		Point _normal;
		Material _material;	
	public:
		//Constructors
		Polygon() {}
		Polygon(Point , Point ,Point ,Material material);

		//Getters
		//Getters
		Point getNormal() { return _normal; }
		Material getMaterial() { return _material; }
		
		void print();

		//Intersection of a ray
		float intersectPolygon(Ray ray);


};

#endif