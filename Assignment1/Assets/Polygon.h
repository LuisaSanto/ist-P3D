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
		Point _points[];
		Material _material;	
	public:
		//Constructors
		Polygon() {}
		Polygon(Point ,Material material);

		//Getters

		void print();

		//Intersection of a ray
		float intersectPolygon(Ray ray);


};

#endif