//Material.cpp
#include "Material.h"


Material::Material (float r, float g, float b, float Kd, float Ks, float shine, float T, float refr_index) {
	_r = r;
	_g = g;
	_b = b;
	_Kd = Kd;
	_Ks = Ks;
	_shine = shine;
	_T = T;
	_refr_index = refr_index;
}