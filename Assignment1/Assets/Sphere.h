#ifndef SPHERE_H
#define SPHERE_H

#include "Point.h"
#include "Material.h"

class Sphere {
	private:
		Point _pos;
		float _radius;
		Material _material;	
	public:
		//Constructors
		Sphere() {}
		Sphere(Point , float radius, Material material);

		//Getters
		Point getPosition() { return _pos; }
		float getRadius() { return _radius; }

		void print();


};

#endif