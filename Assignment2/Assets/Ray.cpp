#include "Ray.h"

Ray::Ray(Point origin, Point direction) {
	_origin = origin;
	//Normalize vector
	//When creating a ray it will always be normalized!
	direction.normalize();
	_direction = direction;
	_id = ++numRay;
	//cout << "Norma: " << _direction.norma() << endl;
}


Point Ray::pointAtParameter(float t) {

	// o + d * t
	Point origin = getOrigin();
	Point direction = getDirection();
	return origin + direction * t;
}

void Ray::print() {
	cout << "======== Ray Info =======" << endl;
	cout << "Origin: " << endl;
	getOrigin().print();
	cout << "Direction: " << endl;
	getDirection().print();
}

int Ray::numRay = 0;