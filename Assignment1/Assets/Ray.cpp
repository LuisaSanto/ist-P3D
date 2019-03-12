#include "Ray.h"

Ray::Ray(Point origin, Point direction) {
	_origin = origin;
	//Normalize vector
	direction.normalize();
	_direction = direction;
}

Point Ray::pointAtParameter(float t) {

	// o + d * t
	Point origin = getOrigin();
	Point direction = getDirection();
	return origin.add(direction.multiply(t));
}