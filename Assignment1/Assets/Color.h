#ifndef COLOR_H
#define COLOR_H

#include <math.h>
#include <iostream>

using namespace std;

// Class to represent color.
class Color {
	private:
	    float _r, _g, _b;
	public:
	    Color(float r = 0.0, float g = 0.0, float b = 0.0);

	    // Extractors.
	    float r() { return _r; }
	    float g() { return _g; }
	    float b() { return _b; }

	    // Distance to another point.  Pythagorean thm.
	    //float dist(Point other);

	    // Add and subtract color
	    Color add(Color c);
	    Color mul(Color c);
	    Color mul(float t);
	    //Point sub(Point b);

	    //Multiply Point by a Float
	    //Point multiply(float a);


	    // Move the existing point.
	    //void move(float a, float b, float c);


	    // Inner Product
	    //float inner(Point b);
	    // Cross Product
	    //Point cross(Point b);

	    //norm
	    //float norma();
	    //void normalize();

	    void print();
};

#endif