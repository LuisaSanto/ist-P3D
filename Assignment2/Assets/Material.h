#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
using namespace std;

#include "Color.h"

//Class to represent a Material
class Material {
	private:
		Color _color;
		float _Kd, _Ks;
		float _shine;
		float _T;
		float _refr_index;

	public:
		//Constructors
		Material() {}
		Material(Color color, float Kd, float Ks, float shine, float T, float refr_index);

		//Getters
		Color getColor() { return _color; }
		float getDiffuse() { return _Kd; }
		float getSpecular() { return _Ks; }
		float getShine() { return _shine; }
		float getTransmittance() { return _T; }
		float getRefrIndex() { return _refr_index; }

		void print();
};

#endif