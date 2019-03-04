#ifndef CAMERA_H
#define CAMERA_H

#include "Point.h"

//Class to represent a Camera
class Camera {
	private:
		Point _eye, _at, _up;
		float _fovy;
		float _near, _far;
		int _ResX, _ResY;

		float _w, _h;
		Point _xe, _ye, _ze; //??


	public:
		Camera(Point eye, Point at, Point up, double fovy, double near, double far, int ResX, int ResY);
};

#endif