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
	df = eye.sub(at).norma();

	//Calculate height
	_h = 2 * df * tan((_fovy / 2) * M_PI / 180);

	//Calculate width
	_w = _h * ResX / ResY;

	//Calculate ze
	
	//aux = eye.sub(at);
	//_ze = Point(aux.x() / df, aux.y() / df, aux.z() / df);
	_ze = _eye.sub(at);
	_ze.normalize();
	//Calculate xe
	/*Point cross = up.cross(_ze);
	float norm = cross.norm();
	_xe = Point(cross.x() / norm, cross.y() / norm, cross.z() / norm);*/

	_xe = _up.cross(_ze);
	_xe.normalize();
	
	//Calculate ye
	_ye = _ze.cross(_xe); 
	_ye.normalize();
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

Ray Camera::computePrimaryRay(float x, float y) {
	Point origin = getEye();

	//We assume the left-bottom corner of the unit square pixel??
	//Compute direction
	float df;
	df = getEye().sub(getAt()).norma();
	Point ze = getZe().multiply(-df);
	Point ye = getYe().multiply(getHeight() * (y / getResY() - 0.5));
	Point xe = getXe().multiply(getWidth() * (x / getResX() - 0.5));  
	

	//ze.norma();
	//ye.norma();
	//xe.norma();
	
	Point direction = ze.add(ye.add(xe)); 

	//float Px = (2 * ((x + 0.5) / getWidth()) - 1) * tan(getFovy() / 2 * M_PI / 180); /** imageAspectRatio*/
	//float Py = (1 - 2 * ((y + 0.5) / getHeight())) * tan(getFovy() / 2 * M_PI / 180);

	//Point direction = Point(Px, Py, -1); 

	return Ray(origin, direction);

}

	
