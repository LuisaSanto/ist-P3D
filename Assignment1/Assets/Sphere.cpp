#include "Sphere.h"

Sphere::Sphere (Point pos, float radius) {
	_pos = pos;
	_radius = radius;
}

void Sphere::print() {
	cout << "======== Sphere Info =======" << endl;
	_pos.print();
	cout << "radius: " << _radius << endl;
}