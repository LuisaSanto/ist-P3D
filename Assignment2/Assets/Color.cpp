#include "Color.h"

Color::Color(float red, float green, float blue) {
        _r = red;
        _g = green;
        _b = blue;
}

// Add or subtract two points.
Color Color::add(Color c) {
    return Color(r() + c.r(), g() + c.g(), b() + c.b());
}

Color Color::operator+(Color c) {
    return Color(r() + c.r(), g() + c.g(), b() + c.b());
}

Color Color::sub(Color c) {
    return Color(r() - c.r(), g() - c.g(), b() - c.b());
}

Color Color::operator-(Color c) {
    return Color(r() - c.r(), g() - c.g(), b() - c.b());
}

Color Color::mul(Color c) {
    return Color(r() * c.r(), g() * c.g(), b() * c.b());
}

Color Color::operator*(Color c) {
    return Color(r() * c.r(), g() * c.g(), b() * c.b());
}

Color Color::mul(float t) {
	return Color(r() * t, g() * t, b() * t);
}

Color Color::operator*(float t) {
    return Color(r() * t, g() * t, b() * t);
}


void Color::print() {
	cout << "======== Color Info =======" << endl;
	cout << "r color: " << r() << endl;
	cout << "g color: " << g() << endl;
	cout << "b color: " << b() << endl;
}