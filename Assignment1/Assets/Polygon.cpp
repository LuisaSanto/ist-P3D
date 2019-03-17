#include "Polygon.h"

Polygon::Polygon (Point points, Material material) {
	//cout << "======== Polygon Info =======" << sizeof(array)/sizeof(array[0]) << endl;
	//_points[] = points;
	_material = material;

}

void Polygon::print() {
	cout << "======== Polygon Info =======" << endl;
	
	cout << "END OF Polygon" << endl;
}

float Polygon::intersectPolygon(Ray ray) {
	//Declare variables
	float tNear = numeric_limits<float>::max();
	float t;

	Point rayDirection = ray.getDirection();
	Point rayOrigin = ray.getOrigin();

	
	return tNear;

}