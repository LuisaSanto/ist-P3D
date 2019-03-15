#include "Light.h"

Light::Light(Point pos, Color color) {
	_pos = pos;
	_color = color;
}

void Light::print() {
	cout << "======== Light Info =======" << endl;
	_pos.print();
	_color.print();
}