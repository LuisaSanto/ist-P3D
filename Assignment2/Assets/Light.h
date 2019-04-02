#ifndef LIGHT_H
#define LIGHT_H

#include "Point.h"
#include "Color.h"
#include <vector>

using namespace std;

//Class to represent a Light
class Light {
	private:
		Point _pos;
		Color _color;


		//Defining area of light
		Point _a;
		Point _b;
		Point _normal;
		vector<Point> _jitteredPoints;

	public:
		Light() {}
		Light(Point pos, Color color);

		//Getters
		Point getPos() { return _pos; }
		Color getColor() {return _color; }

		Point getJitterPoint();

		void *addJitteredPoints(int N);

		void print();
};

#endif
