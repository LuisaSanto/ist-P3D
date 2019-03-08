#include "Camera.h"


Camera::Camera(Point eye, Point at, Point up, int angle, float hither, int ResX, int ResY) {
	_eye = eye;
	_at = at;
	_up = up;
	_fovy = angle;
	_near = hither;
	//far infinity??
	_ResX = ResX;
	_ResY = ResY;

	//Calculate df
	float df;
	df = eye.dist(at);

	//Calculate height
	_h = 2 * df * tan(_fovy / 2);

	//Calculate width
	_w = _h * ResX / ResY;

	//Calculate ze
	Point aux;
	Point _ze;
	aux = eye.sub(at);
	_ze = Point(aux.x() / df, aux.y() / df, aux.z() / df);

	//Calculate xe
	Point cross = up.cross(_ze);
	float norm = cross.norm();
	_xe = Point(cross.x() / norm, cross.y() / norm, cross.z() / norm);
	
	//Calculate ye
	_ye = _ze.cross(_xe); 
}

void Camera::print() {
	cout << "======== Camera Info =======" << endl;
	cout << "Eye position " << endl;
	_eye.print();
	cout << "At position " << endl;
	_at.print();
	cout << "Up position " << endl;
	_up.print();
	cout << "Field of view: " << _fovy << endl;
	cout << "Near: " << _near << endl;
	cout << "Resolution: " << " x - " << _ResX << " ; y - " << _ResY << endl;
	cout << "Height: " << _h << " ; Width: " << _w << endl;
	cout << "xe position " << endl;
	_xe.print();
	cout << "ye position " << endl;
	_ye.print();
	cout << "ze position " << endl;
	_ze.print();
}

	
