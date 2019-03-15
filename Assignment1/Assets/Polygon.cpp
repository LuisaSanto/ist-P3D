#include "Polygon.h"

Polygon::Polygon (Point points, Material material) {
	_points = points;
	_material = material;

}

void Polygon::print() {
	cout << "======== Polygon Info =======" << endl;
	_point1.print();
	_point2.print();
	_point3.print();
	_normal.print();
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