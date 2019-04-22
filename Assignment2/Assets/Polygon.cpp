#include "Polygon.h"



void Polygon::print() {
	cout << "======== Polygon Info =======" << endl;
	_point1.print();
	_point2.print();
	_point3.print();
	_normal.print();
	_material.print();
	cout << "END" << endl;
}

float Polygon::checkRayCollision(Ray ray) {
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

	return t;


}


void Polygon::computeBoundingBox() {
	Point p1 = Point(pMax,pMax,pMax);
	Point p2 = Point(pMin,pMin,pMin);

	Point points[] = { _point1, _point2, _point3 };

	for(int i = 0; i < 3; i++){
		if(points[i].x() < p1.x()){
			p1.setX(points[i].x());
		}
		if(points[i].x() > p2.x()){
			p2.setX(points[i].x());
		}
		if(points[i].y() < p1.y()){
			p1.setY(points[i].y());
		}
		if(points[i].y() > p2.y()){
			p2.setY(points[i].y());
		}
		if(points[i].z() < p1.z()){
			p1.setZ(points[i].z());
		}
		if(points[i].z() > p2.z()){
			p2.setZ(points[i].z());
		}

	}

	box = BoundingBox(p1, p2);
}