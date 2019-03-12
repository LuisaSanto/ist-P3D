#include "Point.h"

Point::Point(float x, float y, float z) {
        xval = x;
        yval = y;
        zval = z;
}


// Distance to another point.  Pythagorean thm.
float Point::dist(Point other) {
    float xd = xval - other.xval;
    float yd = yval - other.yval;
    float zd = zval - other.zval;
    return sqrt(xd*xd + yd*yd + zd*zd);
}

float Point::norma() {
    return sqrt(xval*xval + yval*yval + zval*zval);
}

// Add or subtract two points.
Point Point::add(Point b) {
    return Point(xval + b.xval, yval + b.yval, zval + b.zval);
}
Point Point::sub(Point b) {
    return Point(xval - b.xval, yval - b.yval, zval - b.zval);
}

//Multiply by a float
Point Point::multiply(float a) {
    return Point(a * xval, a * yval, a * zval);
}

// Move the existing point.
void Point::move(float a, float b, float c) {
    xval += a;
    yval += b;
    zval += c;
}

//Inner Product
float Point::inner(Point b) {
    return xval * b.xval + yval * b.yval + zval * b.zval;
}

// Cross Product
Point Point::cross(Point b) {
    float x, y, z;
    x = yval * b.zval - zval * b.yval;
    y = xval * b.zval - zval * b.xval;
    z = xval * b.yval - yval * b.xval;
    return Point(x, y, z); 
}

//Print point
void Point::print() {
    cout << "x: " << xval << endl;
    cout << "y: " << yval << endl;
    cout << "z: " << zval << endl;
}

void Point::normalize() {
    float norm = norma();
    xval = xval / norm;
    yval = yval / norm;
    zval = zval / norm;
}
