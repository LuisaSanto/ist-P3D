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

void Sphere::setNormalIntersectionPoint(Point p, int i) {
    Point center = getPosition();
    float radius = getRadius();
    float d = (center - p).norma();
    //cout << "ola" << endl;
    Point result = (p - center) / radius;
    //cout << "ola2" << endl;

    if (d >= radius * radius) {
        //cout << "ola3" << endl;
        _normal = result;
    } else {
        //cout << "ola4" << endl;
        _normal = result * (-1);
    }
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

	//Point L = sphereCenter.sub(rayOrigin);
	Point L = sphereCenter - rayOrigin;

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
		//cout << "adeus" << endl;
	}
	else {
		t = b + sqrt(r);
		setNormalIntersectionPoint(ray.pointAtParameter(t), 1);
		//cout << "adeus2" << endl;
	}
	//t = 0;
	//_normal = Point(1, 0, 0);
	//cout << "YAYYYYYYYY" << endl;
	return t;
}