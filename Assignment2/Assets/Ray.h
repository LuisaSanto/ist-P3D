#ifndef RAY_H
#define RAY_H

#include "Point.h"

using namespace std;

//Class to represent a Ray
class Ray {
	private:
		Point _origin;
		Point _direction;
		static int numRay;

	public:

		int id;

		//Constructor
		
		Ray(Point origin, Point direction);
		Ray(Point origin, Point direction, int numRay){numRay++;};

		//Getters

		Point getOrigin() { return _origin; }
		Point getDirection() { return _direction; }

		//Get a Ray from origin to a point
		Point pointAtParameter(float t);


		void print();
};

#endif