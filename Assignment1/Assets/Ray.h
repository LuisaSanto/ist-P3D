#ifndef RAY_H
#define RAY_H

#include "Point.h"

using namespace std;

//Class to represent a Ray
class Ray {
	private:
		Point _origin;
		Point _direction;

	public:
		//Constructor
		Ray(Point origin, Point direction);

		//Getters

		Point getOrigin() { return _origin; }
		Point getDirection() { return _direction; }

		//Get a Ray from origin to a point
		Point pointAtParameter(float t);
};

#endif