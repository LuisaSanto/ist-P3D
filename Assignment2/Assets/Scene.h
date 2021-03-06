#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <tuple>

#include "Camera.h"
#include "Color.h"
#include "Cylinder.h"
#include "Light.h"
#include "Material.h"
#include "Point.h"
#include "Sphere.h"
#include "Plane.h"
#include "Polygon.h"
#include "Grid.h"
#include "LensCamera.h"

const float kInfinity = numeric_limits<float>::max();

using namespace std;

class Scene {
	private:
		Color _bgColor;
		Camera _camera;
		LensCamera _lensCamera;
		vector<Material> materials;
		vector<Light*> lights;
		vector<Object*> objects;
		Grid grid;

	public:
		//Constructor
		Scene();

		//Getters
		Color getBgColor() { return _bgColor; }
		Camera getCamera() { return _camera; }
		LensCamera getLensCamera() { return _lensCamera; }
		vector<Material> getMaterials() { return materials; }
		vector<Light*> getLights() { return lights; }
		vector<Object*> getObjects() { return objects; }

		//Setters
		void addBgColor(Color color) { _bgColor = color; }
		void addCamera(Camera camera) { _camera = camera; }
		void addMaterial(Material material) { materials.push_back(material); }
		void addLight(Light* light) { lights.push_back(light); }
		void addObject(Object* object) { objects.push_back(object); }
		void addLensCamera(LensCamera camera) {_lensCamera = camera; }



		//Parsing
		void parse_nff(string fp);
		void do_background(stringstream& line);
		void do_camera(stringstream& line);
		void do_cylinder(stringstream& line);
		void do_light(stringstream& line);
		void do_material(stringstream& line);
		void do_sphere(stringstream& line);
		void do_plane(stringstream& line);
		void do_polygon(stringstream& line);

		//Whitted Ray-Tracing Algorithm
		Color trace(Ray ray, int depth, float , bool insideObject, int softShadows, int acc_mode);


		//Auxiliar Methods
		float get_float(stringstream& line);
		Point create_Point(stringstream& line);
		Color getLocal(Material material, Color lightColor, Point hitPoint, Point L, Point normal);
		Object* getClosestIntersection(Ray ray);
		Object* checkInShadow(Ray ray);
		Point refract(Point i, Point n, float ior1, float ior2, bool insideObject);
		void createGrid();

		void print();
};

#endif