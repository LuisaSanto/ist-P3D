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
	public:
		//Constructors
		BoundingBox() {}
		BoundingBox(Point p1, Point p2);

		//Getters
		Point getMin(){return _point1;}
		Point getMax(){return _point2;}
		
		void print();

		//Intersection of a ray
		float intersectBoundingBox(Ray ray);

		bool inside(Point p);


};

#endif