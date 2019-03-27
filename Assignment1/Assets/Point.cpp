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
    return (float) sqrt(xval*xval + yval*yval + zval*zval);
}

bool Point::isEqual(Point b) {
    return xval == b.xval && yval == b.yval && zval == b.zval;
}

// Add or subtract two points.

Point Point::operator+(Point b) {
    return Point(xval + b.xval, yval + b.yval, zval + b.zval);
}


Point Point::operator-(Point b) {
    return Point(xval - b.xval, yval - b.yval, zval - b.zval);
}

Point Point::operator-() {
    return Point(-xval, -yval, -zval);
}

//Multiply by a fmake loat

Point Point::operator*(float a) {
    return Point(a * xval, a * yval, a * zval);
}

Point Point::operator*(Point b) {
    return Point(xval * b.xval, yval * b.yval, zval * b.zval);
}


//Divide by a float 

Point Point::operator/(float a) {
    return Point(xval / a, yval / a, zval / a);
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
    y = zval * b.xval - xval * b.zval;
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
    float norm = xval * xval + yval * yval + zval * zval;
    if (norm > 0) { 
        float invNorm = 1 / sqrt(norm);
        xval = xval * invNorm;
        yval = yval * invNorm;
        zval = zval * invNorm;
    }
}
