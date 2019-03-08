#ifndef SPHERE_H
#define SPHERE_H

#include "Point.h"

class Sphere {
	private:
		Point _pos;
		float _radius;	
	public:
		//Constructors
		Sphere() {}
		Sphere(Point , float radius);

		//Getters
		Point getPosition() { return _pos; }
		float getRadius() { return _radius; }

		void print();


};

#endif