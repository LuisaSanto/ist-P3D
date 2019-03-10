#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Camera.h"
#include "Cylinder.h"
#include "Light.h"
#include "Material.h"
#include "Point.h"
#include "Sphere.h"

using namespace std;

/*typedef std::vector<Light> lights;
typedef std::vector<int> bgColor;
typedef std::vector<Material> materials;
typedef std::vector<Cylinder> cylinder;
typedef std::vector<Sphere> spheres;*/

class Scene {
	private:
		vector<float> bgColor;
		Camera _camera;
		vector<Material> materials;
		vector<Light> lights;
		vector<Sphere> spheres;
		vector<Cylinder> cylinders;
		vector<Point> points;

	public:
		//Constructor
		Scene();

		//Getters
		vector<float> getBgColor() { return bgColor; }
		Camera getCamera() { return _camera; }
		vector<Material> getMaterials() { return materials; }
		vector<Light> getLights() { return lights; }
		vector<Sphere> getSpheres() { return spheres; }
		vector<Point> getPoints() { return points; }

		//Setters
		void addCamera(Camera camera) { _camera = camera; }
		void addMaterial(Material material) { materials.push_back(material); }
		void addLight(Light light) { lights.push_back(light); }
		void addSphere(Sphere sphere) { spheres.push_back(sphere); }
		void addCylinder(Cylinder cylinder) { cylinders.push_back(cylinder); }
		void addPoint(Point point) { points.push_back(point); }



		//Parsing
		void parse_nff(string fp);
		void do_background(stringstream& line);
		void do_camera(stringstream& line);
		void do_cylinder(stringstream& line);
		void do_light(stringstream& line);
		void do_material(stringstream& line);
		void do_sphere(stringstream& line);
		void do_point(stringstream& line);


		//Auxiliar Methods
		float get_float(stringstream& line);
		Point create_Point(stringstream& line);

		void print();
};

#endif