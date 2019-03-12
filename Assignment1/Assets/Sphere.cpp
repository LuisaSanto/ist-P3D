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

	float xo = ray.getOrigin().x();
	float yo = ray.getOrigin().y();
	float zo = ray.getOrigin().z();
	
	float xd = ray.getDirection().x();
	float yd = ray.getDirection().y();
	float zd = ray.getDirection().z();

	float xc = getPosition().x();
	float yc = getPosition().y();
	float zc = getPosition().z();

	//Get b
	float b = xd * (xc - xo) + yd * (yc - yo) + zd * (zd - zo);
	//Get c
	float c = pow((xc - xo), 2) + pow((yc - yo), 2) + pow((zc - zo), 2) - pow(radius, 2);


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

	return t;




	

}