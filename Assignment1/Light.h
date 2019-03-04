#ifndef LIGHT_H
#define LIGHT_H

#include "Point.h"

//Class to represent a Light
class Light {
	private:
		Point _pos;
		float _r, _g, _b;

	public:
		Light(Point pos, float r, float g, float b);
};

#endif
