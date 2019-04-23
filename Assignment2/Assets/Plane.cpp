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

	if (ray.id == lastRay) {
		return _lastTNear;
	}

	Point normal = Object::getNormal();
	Point rayDirection = ray.getDirection();
	Point rayOrigin = ray.getOrigin();

	if(normal.inner(rayDirection) == 0){
		return tNear;
	}

	t = -((normal.inner((rayOrigin-_point1) / normal.inner(rayDirection))));
	if(t < 0){
		return tNear;
	}
	
	lastRay = ray.id;
	return t;
}

Plane::Plane() {}

Plane::Plane(Point normal, float d) {
	_normal = normal;
	_focalDistance = d;
}
//: _normal(normal), _d(d)

Plane::Plane(Point p1, Point p2, Point p3, Material material) : Object(material) {
	float z;

	_point1 = p1;
	_point2 = p2;
	_point3 = p3;
	_material = material;

	_normal = (p2-p1).cross(p3-p1);
	_normal.normalize();

	_focalDistance = _point1.inner(_normal) / _normal.norma();
}
