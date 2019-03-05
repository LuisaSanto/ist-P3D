#include "Point.h"

Point::Point(double x, double y, double z) {
        xval = x;
        yval = y;
        zval = z;
}


// Distance to another point.  Pythagorean thm.
double Point::dist(Point other) {
    double xd = xval - other.xval;
    double yd = yval - other.yval;
    double zd = zval - other.zval;
    return sqrt(xd*xd + yd*yd + zd*zd);
}

// Add or subtract two points.
Point Point::add(Point b) {
    return Point(xval + b.xval, yval + b.yval, zval + b.zval);
}
Point Point::sub(Point b) {
    return Point(xval - b.xval, yval - b.yval, zval - b.zval);
}

// Move the existing point.
void Point::move(double a, double b, double c) {
    xval += a;
    yval += b;
    zval += c;
}
