#ifndef POINT_H
#define POINT_H

#include <math.h>
#include <iostream>

using namespace std;

// Class to represent points.
class Point {
	private:
	    float xval, yval, zval;
	public:
		Point() : xval(0.0f), yval(0.0f), zval(0.0f) {}
		Point(const float x = 0.0, const float y = 0.0) {}
	    Point(const float x = 0.0, const float y = 0.0, const float z = 0.0);

	    // Extractors.
	    float x() { return xval; }
	    float y() { return yval; }
	    float z() { return zval; }

	    // Distance to another point.  Pythagorean thm.
	    float dist(Point other);

	    // Add and subtract two Points
	    Point operator+(Point b);
	    Point operator-(Point b);
	    Point operator*(Point b);
	    Point operator-();

	    //Multiply Point by a Float
	    Point operator*(float a);
	    Point operator/(float a);

		bool isEqual(Point b);


	    // Move the existing point.
	    void move(float a, float b, float c);


	    // Inner Product
	    float inner(Point b);
	    // Cross Product
	    Point cross(Point b);

	    //norm
	    float norma();
	    void normalize();

	    void print();
};

#endif