#include "Light.h"

Light::Light(Point pos, float r, float g, float b) {
	_pos = pos;
	_r = r;
	_g = g;
	_b = b;
}

void Light::print() {
	cout << "======== Light Info =======" << endl;
	_pos.print();
	cout << "r color: " << _r << endl;
	cout << "g color: " << _g << endl;
	cout << "b color: " << _b << endl;
}