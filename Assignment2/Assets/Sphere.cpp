#include "Sphere.h"

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
    setNormal(result);
}

float Sphere::checkRayCollision(Ray ray) {
	//Declare variables
	float tNear = numeric_limits<float>::max();

	if (ray.getRayID() == lastRay) {
		//cout << "Second" << lastRay << endl;
		return _lastTNear;
	}

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
	lastRay = ray.getRayID();
    _lastTNear = t;
	return t;
}



void Sphere::computeBoundingBox() {
	Point p1 = Point(_pos.x() - _radius, _pos.y() - _radius, _pos.z() - _radius);
	Point p2 = Point(_pos.x() + _radius, _pos.y() + _radius, _pos.z() + _radius);
	box = BoundingBox(p1, p2);

}