#ifndef POINT_H
#define POINT_H

#include <math.h>

// Class to represent points.
class Point {
	private:
	    double xval, yval, zval;
	public:
	    Point(double x = 0.0, double y = 0.0, double z = 0.0);

	    // Extractors.
	    double x() { return xval; }
	    double y() { return yval; }
	    double z() { return zval; }

	    // Distance to another point.  Pythagorean thm.
	    double dist(Point other);

	    // Add or subtract two points.
	    Point add(Point b);
	    Point sub(Point b);

	    // Move the existing point.
	    void move(double a, double b, double c);
};

#endif