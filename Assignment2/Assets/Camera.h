#ifndef CAMERA_H
#define CAMERA_H

#include "Point.h"
#include "Ray.h"

#include <math.h>
#define _USE_MATH_DEFINES

using namespace std;

//Class to represent a Camera
struct Camera {
	private:
		Point _eye, _at, _up;
		float _fovy;
		float _near, _far;
		int _ResX, _ResY;

		float _w, _h;
		Point _xe, _ye, _ze;


	public:
		//Constructors
		Camera() {}
		Camera(Point eye, Point at, Point up, int angle, float hither, int ResX, int ResY);

		//Getters

		Point getEye() { return _eye; }
		Point getAt() { return _at; }
		Point getUp() { return _up; }
		float getFovy() { return _fovy; }
		float getNear() { return _near; }
		float getFar() { return _far; }
		float getResX() { return _ResX; }
		float getResY() { return _ResY; }
		float getWidth() { return _w; }
		float getHeight() { return _h; }
		Point getXe() { return _xe; }
		Point getYe() { return _ye; }
		Point getZe() { return _ze; }

		//Print Camera Information
		void print();

		//Compute a Primary ray
		virtual Ray computePrimaryRay(float x, float y);

//		virtual Point getFocalPoint(Ray &r) { return Point(0.0, 0.0, 0.0); }
//		virtual Point getLenseSamplePoint() { return Point(0.0, 0.0, 0.0);  }
};

#endif