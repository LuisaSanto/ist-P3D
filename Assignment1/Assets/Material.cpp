#include "Material.h"


Material::Material (Color color, float Kd, float Ks, float shine, float T, float refr_index) {
	_color = color;
	_Kd = Kd;
	_Ks = Ks;
	_shine = shine;
	_T = T;
	_refr_index = refr_index;
} 

void Material::print() {
	cout << "======== Material Info =======" << endl;
	_color.print();
	cout << "Diffuse component: " << _Kd << endl;
	cout << "Specular component: " << _Ks << endl;
	cout << "Shine: " << _shine << endl; 
	cout << "Transmittance: " << _T << endl;
	cout << "Refaction index: " << _refr_index << endl;

}