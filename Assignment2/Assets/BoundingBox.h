#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Point.h"
#include "Material.h"
#include "Ray.h"
#include <math.h>
#include <limits>

using namespace std;

class BoundingBox {
	private:
		Point _point1;
		Point _point2;
		Material _material;	
	public:
		//Constructors
		BoundingBox() {}
		BoundingBox(Point , Point ,Material material);

		//Getters
		Material getMaterial() { return _material; }
		
		void print();

		//Intersection of a ray
		float intersectBoundingBox(Ray ray);


};

#endif