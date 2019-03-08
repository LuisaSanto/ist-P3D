#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
using namespace std;

//Class to represent a Material
class Material {
	private:
		float _r;
		float _g;
		float _b;
		float _Kd, _Ks;
		float _shine;
		float _T;
		float _refr_index;

	public:
		//Constructors
		Material() {}
		Material(float r, float g, float b, float Kd, float Ks, float shine, float T, float refr_index);

		//Getters
		float getRedColor() { return _r; } 
		float getGreenColor() { return _g; } 
		float getBlueColor() { return _b; } 
		float getDiffuse() { return _Kd; }
		float getSpecular() { return _Ks; }
		float getShine() { return _shine; }
		float getTransmittance() { return _T; }
		float getRefrIndex() { return _refr_index; }

		void print();
};

#endif