#include "Polygon.h"

Polygon::Polygon (Point p1, Point p2, Point p3, Material material) {
	_point1 = p1;
	_point2 = p2;
	_point3 = p3;
	_material = material;

	_normal = (p2 - p1).cross(p3 - p1);
	_normal.normalize();

}

void Polygon::print() {
	cout << "======== Polygon Info =======" << endl;
	_point1.print();
	_point2.print();
	_point3.print();
	_normal.print();
	_material.print();
	cout << "END" << endl;
}

float Polygon::intersectPolygon(Ray ray) {
	//Declare variables
	float tNear = numeric_limits<float>::max();
	float t, innerVert, invInnerVert, u, v;
	Point crossDir, ori, q;

	Point normal = getNormal();
	Point rayOrigin = ray.getOrigin();
	Point rayDirection = ray.getDirection();
	

	crossDir = rayDirection.cross((_point3 - _point1));
	innerVert = (_point2 - _point1).inner(crossDir);

	if(innerVert < 0.0000001){
		return tNear;
	}

	ori = rayOrigin - _point1;

	u = ori.inner(crossDir) * (1/innerVert);

	if(u < 0.0 || u > 1){
		return tNear;
	}

	q = ori.cross(_point2 - _point1);
	v = rayDirection.inner(q) * (1/innerVert);

	if(v < 0.0 || u + v > 1){
		return tNear;
	}

	t = (_point3 - _point1).inner(q) * (1/innerVert);

	if(t < 0){
		return tNear;
	}

	/*if(innerVert < 0.0000001 && innerVert > -0.0000001){
		return tNear;
	}

	invInnerVert = 1.0 / innerVert;

	ori = rayOrigin.sub(_point1);

	u = invInnerVert * (ori.inner(crossDir));

	if(u < 0.0 || u > 1.0){
		return tNear;
	}

	q = ori.cross(_point2.sub(_point1));
	v = invInnerVert * (rayDirection.inner(q));

	if(v < 0.0 || u + v > 1.0){
		return tNear;
	}

	t = invInnerVert * ((_point3.sub(_point1)).inner(q));*/


	return t;


}