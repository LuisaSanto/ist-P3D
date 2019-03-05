#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <fstream>
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
		Camera camera;
		vector<Material> materials;
		vector<Light> lights;
		vector<Sphere> spheres;
		vector<Cylinder> cylinders;
		vector<Point> points;

	public:
		//Constructor
		Scene();



		//
		void parse_nff(string fp);
		void do_camera(string line);
		void do_cylinder(string line);
		void do_light(string line);
		void do_material(string line);
		void do_sphere(string line);
		void do_point(string line);
};

#endif