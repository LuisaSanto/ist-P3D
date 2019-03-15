#ifndef LIGHT_H
#define LIGHT_H

#include "Point.h"
#include "Color.h"

using namespace std;

//Class to represent a Light
class Light {
	private:
		Point _pos;
		Color _color;

	public:
		Light() {}
		Light(Point pos, Color color);

		//Getters
		Point getPos() { return _pos; }
		Color getColor() {return _color; }

		void print();
};

#endif
