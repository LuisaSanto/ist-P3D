//Camera.h
#ifndef CAMERA_H
#define CAMERA_H

class Camera {
	//Define Vector Class
	Vector _eye, _at, _up;
	float _fovy;
	float _near, _far;
	int _ResX, _ResY;

	float _w, _h;
	Vector _xe, _ye, _ze //??


public:
	Camera(Vector eye, Vector at, Vector up, double fovy, double near, double far, int ResX, int ResY);
}