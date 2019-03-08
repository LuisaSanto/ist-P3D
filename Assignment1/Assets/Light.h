#ifndef LIGHT_H
#define LIGHT_H

#include "Point.h"

using namespace std;

//Class to represent a Light
class Light {
	private:
		Point _pos;
		float _r;
		float _g;
		float _b;

	public:
		Light() {}
		Light(Point pos, float r, float g, float b);

		//Getters
		Point getPos() { return _pos; }
		float getRedColor() { return _r; } 
		float getGreenColor() { return _g; } 
		float getBlueColor() { return _b; } 

		void print();
};

#endif
