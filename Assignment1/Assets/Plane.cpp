#include "Plane.h"

Plane::Plane (Point p1, Point p2, Point p3, Material material) {
	_point1 = p1;
	_point2 = p2;
	_point3 = p3;
	_material = material;

	_normal = (p2 - p1).cross(p3 - p1);
	_normal.normalize();
}

void Plane::print() {
	cout << "======== Plane Info =======" << endl;
	_point1.print();
	_point2.print();
	_point3.print();
	_normal.print();
	cout << "END" << endl;
}

float Plane::intersectPlane(Ray ray) {
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