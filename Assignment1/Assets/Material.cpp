#include "Material.h"


Material::Material (float r, float g, float b, 
	float Kd, float Ks, float shine, float T, float refr_index) {
	_r = r;
	_g = g;
	_b = b;
	_Kd = Kd;
	_Ks = Ks;
	_shine = shine;
	_T = T;
	_refr_index = refr_index;
} 

void Material::print() {
	cout << "======== Material Info =======" << endl;
	cout << "r color: " << _r << endl;
	cout << "g color: " << _g << endl;
	cout << "b color: " << _b << endl;
	cout << "Diffuse component: " << _Kd << endl;
	cout << "Specular component: " << _Ks << endl;
	cout << "Shine: " << _shine << endl; 
	cout << "Transmittance: " << _T << endl;
	cout << "Refaction index: " << _refr_index << endl;

}