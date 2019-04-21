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

	    Color operator+(Color c);
	    Color operator-(Color c);
	    Color operator*(Color c);
	    Color operator*(float t);
		Color operator/(float t);

	    Color add(Color c);
	    Color sub(Color c);
	    Color mul(Color c);

	    Color mul(float t);

	    void print();
};

#endif