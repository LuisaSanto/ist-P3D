#include "Sphere.h"

Sphere::Sphere (Point pos, float radius, Material material) {
	_pos = pos;
	_radius = radius;
	_material = material;
}

void Sphere::print() {
	cout << "======== Sphere Info =======" << endl;
	_pos.print();
	cout << "radius: " << _radius << endl;
}

float Sphere::intersectSphere(Ray ray) {
	//Declare variables
	float tNear = numeric_limits<float>::max();

	float radius = getRadius();
	Point rayOrigin = ray.getOrigin();
	Point rayDirection = ray.getDirection();
	Point sphereCenter = getPosition();

	//print();

	Point L = sphereCenter.sub(rayOrigin);

	//Get b
	float b = rayDirection.inner(L);
	//Get c
	float c = L.inner(L) - pow(radius, 2);

	if (c > 0 and b < 0) {
		//cout << "c: " << c << endl;
		//cout << "b: " << b << endl;
		return tNear;
	}

	float r = pow(b, 2) - c;

	if (r < 0) {
		//cout << "r: " << r << endl;
		//cout << "BUAHHHH" << endl;	
		return tNear;
	}

	float t;
	if (c > 0) {
		t = b - sqrt(r);
	}
	else {
		t = b + sqrt(r);
	}

	return t;




	

}