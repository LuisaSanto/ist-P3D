//Material.h
#ifndef MATERIAL_H
#define MATERIAL_H

class Light {
	float _r, _g, _b;
	float _Kd, _Ks;
	float _shine;
	float _T;
	float _refr_index;




public:
	Material(float r, float g, float b, float Kd, float Ks, float shine, float T, float refr_index);
}