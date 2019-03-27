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
	_material.print();
}

void Sphere::setNormalIntersectionPoint(Point p, float d) {
    Point center = getPosition();
    float radius = getRadius();
    Point result = (p - center) / radius;

    /*if ((d * d) >= (radius * radius)) {
        _normal = result;
    } else {
        _normal = -result;
    }*/
    _normal = result;
}

float Sphere::intersectSphere(Ray ray) {
	//Declare variables
	float tNear = numeric_limits<float>::max();

	float radius = getRadius();
	Point rayOrigin = ray.getOrigin();
	Point rayDirection = ray.getDirection();
	Point sphereCenter = getPosition();


	Point L = sphereCenter - rayOrigin;
	float d = sphereCenter.dist(rayOrigin);


	//Get b
	float b = rayDirection.inner(L);
	//Get c
	float c = d * d - radius * radius;
	
	if (c > 0 and b < 0) {
		return tNear;
	}

	float r = pow(b, 2) - c;

	if (r < 0) {
		return tNear;
	}

	float t;
	if (c > 0) {
		t = b - sqrt(r);
	}
	else {
		t = b + sqrt(r);
	}

	setNormalIntersectionPoint(ray.pointAtParameter(t), d);
	return t;
}