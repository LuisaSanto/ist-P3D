#include "Plane.h"



void Plane::print() {
	cout << "======== Plane Info =======" << endl;
	_point1.print();
	_point2.print();
	_point3.print();
	_normal.print();
	cout << "END" << endl;
}

float Plane::checkRayCollision(Ray ray) {
	//Declare variables
	float tNear = numeric_limits<float>::max();
	float t;

	Point normal = getNormal();
	Point rayDirection = ray.getDirection();
	Point rayOrigin = ray.getOrigin();

	if(normal.inner(rayDirection) == 0){
		return tNear;
	}

	t = -((normal.inner((rayOrigin - _point1) / normal.inner(rayDirection))));
	if(t < 0){
		return tNear;
	}
	
	return t;

}