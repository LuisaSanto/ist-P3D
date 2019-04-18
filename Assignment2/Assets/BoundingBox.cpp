#include "BoundingBox.h"

BoundingBox::BoundingBox (Point p1, Point p2) {
	_point1 = p1;
	_point2 = p2;

}

void BoundingBox::print() {
	cout << "======== Bounding Box Info =======" << endl;
	_point1.print();
	_point2.print();
	cout << "END" << endl;
}

float BoundingBox::intersectBoundingBox(Ray ray) {
	//Declare variables
	float tNear = numeric_limits<float>::max();
	float t, tx_min, tx_max, ty_min, ty_max, tz_min, tz_max, t0, t1;

	float ox = ray.getOrigin().x();
	float oy = ray.getOrigin().y();
	float oz = ray.getOrigin().z();

	float dx = ray.getDirection().x();
	float dy = ray.getDirection().y();
	float dz = ray.getDirection().z();

	float x0 = _point1.x();
	float y0 = _point1.y();
	float z0 = _point1.z();

	float x1 = _point2.x();
	float y1 = _point2.y();
	float z1 = _point2.z();

	float a = 1.0 / dx;
	if(a >= 0){
		tx_min = (x0 - ox) * a;
		tx_max = (x1 - ox) * a;
	}
	else{
		tx_min = (x1 - ox) * a;
		tx_max = (x0 - ox) * a;
	}

	float b = 1.0 / dy;
	if(b >= 0){
		ty_min = (y0 - oy) * b;
		ty_max = (y1 - oy) * b;
	}
	else{
		ty_min = (y1 - oy) * b;
		ty_max = (y0 - oy) * b;
	}

	float c = 1.0 / dz;
	if(c >= 0){
		tz_min = (z0 - oz) * c;
		tz_max = (z1 - oz) * c;
	}
	else{
		tz_min = (z1 - oz) * c;
		tz_max = (z0 - oz) * c;
	}
	
	//find largest entering t value
	if(tx_min > ty_min){
		t0 = tx_min;
	}
	else{
		t0 = ty_min;
	}
	if(tz_min > t0){
		t0 = tz_min;
	}

	//find smallest exiting t value
	if(tx_max < ty_max){
		t1 = tx_max;
	}
	else{
		t1 = ty_max;
	}
	if(tz_max < t1){
		t1 = tz_max;
	}


	//NOT SURE AFTER THIS. NEED TO TAKE A LOOK AT IT
	// !!!!!!!!!!!!!!!!!!!!!!!
	if(t0 > t1){
		return tNear;
	}
	if(t1 < 0){
		return tNear;
	}


	return t0;


}