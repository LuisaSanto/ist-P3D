//Camera.cpp
#include "Camera.h"


Camera::Camera (Vector eye, Vector at, Vector up, double fovy, double near, double far, int ResX, int ResY) {
	_eye = eye;
	_at = at;
	_up = up;
	_fovy = fovy;
	_near = near;
	_far = far;
	_ResX = ResX;
	_ResY = ResY;

	//TO DO, calculate h, w, and the vectors ze, xe, ye
}