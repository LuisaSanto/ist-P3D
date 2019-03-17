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

void Sphere::setNormalIntersectionPoint(Point p, int i) {
	_normal = p.sub(getPosition()).divide(getRadius());
	if (i == 1) {
		_normal.multiply(-1);
	}
	_normal.normalize();
}

float Sphere::intersectSphere(Ray ray) {
	//Declare variables
	float tNear = numeric_limits<float>::max();

	float radius = getRadius();
	Point rayOrigin = ray.getOrigin();
	Point rayDirection = ray.getDirection();
	Point sphereCenter = getPosition();

	//print();
	//rayDirection.print();

	Point L = sphereCenter.sub(rayOrigin);

	//cout << "L: " << L.inner(L) << endl;

	//Get b
	float b = rayDirection.inner(L);
	//Get c
	float c = L.inner(L) - pow(radius, 2);

	//cout << "c: " << c << endl;
	//cout << "b: " << b << endl;
	
	if (c > 0 and b < 0) {
		//cout << "No Intersection!!!!!!" << endl;
		return tNear;
	}

	float r = pow(b, 2) - c;

	if (r < 0) {
		//cout << "r: " << r << endl;
		//cout << "No Intersection!!" << endl;	
		return tNear;
	}

	float t;
	if (c > 0) {
		t = b - sqrt(r);
		setNormalIntersectionPoint(ray.pointAtParameter(t), 0);
	}
	else {
		t = b + sqrt(r);
		setNormalIntersectionPoint(ray.pointAtParameter(t), 1);
	}
	return t;
}