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
	    Point(float x = 0.0, float y = 0.0, float z = 0.0);

	    // Extractors.
	    float x() { return xval; }
	    float y() { return yval; }
	    float z() { return zval; }

	    // Distance to another point.  Pythagorean thm.
	    float dist(Point other);

	    // Add or subtract two points.
	    Point add(Point b);
	    Point sub(Point b);

	    // Move the existing point.
	    void move(float a, float b, float c);

	    // Cross Product
	    Point cross(Point b);

	    //norm
	    float norm();

	    void print();
};

#endif