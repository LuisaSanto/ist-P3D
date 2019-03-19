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

#define INFINITE numeric_limits<float>::max()

using namespace std;

/*typedef std::vector<Light> lights;
typedef std::vector<int> bgColor;
typedef std::vector<Material> materials;
typedef std::vector<Cylinder> cylinder;
typedef std::vector<Sphere> spheres;*/

class Scene {
	private:
		Color _bgColor;
		Camera _camera;
		vector<Material> materials;
		vector<Light> lights;
		vector<Sphere> spheres;
		vector<Cylinder> cylinders;
		vector<Plane> planes;
		vector<Polygon> polygons;
		vector<Point> points;   //Create plane class

	public:
		//Constructor
		Scene();

		//Getters
		Color getBgColor() { return _bgColor; }
		Camera getCamera() { return _camera; }
		vector<Material> getMaterials() { return materials; }
		vector<Light> getLights() { return lights; }
		vector<Sphere> getSpheres() { return spheres; }
		vector<Plane> getPlanes() { return planes; }
		vector<Point> getPoints() { return points; }
		vector<Polygon> getPolygons() { return polygons; }

		//Setters
		void addBgColor(Color color) { _bgColor = color; }
		void addCamera(Camera camera) { _camera = camera; }
		void addMaterial(Material material) { materials.push_back(material); }
		void addLight(Light light) { lights.push_back(light); }
		void addSphere(Sphere sphere) { spheres.push_back(sphere); }
		void addCylinder(Cylinder cylinder) { cylinders.push_back(cylinder); }
		void addPoint(Point point) { points.push_back(point); }
		void addPlane(Plane plane) { planes.push_back(plane); }
		void addPolygon(Polygon polygon) { polygons.push_back(polygon); }



		//Parsing
		void parse_nff(string fp);
		void do_background(stringstream& line);
		void do_camera(stringstream& line);
		void do_cylinder(stringstream& line);
		void do_light(stringstream& line);
		void do_material(stringstream& line);
		void do_sphere(stringstream& line);
		void do_point(stringstream& line);
		void do_plane(stringstream& line);
		void do_polygon(stringstream& line);

		//Whitted Ray-Tracing Algorithm
		Color trace(Ray ray, int depth);


		//Auxiliar Methods
		float get_float(stringstream& line);
		Point create_Point(stringstream& line);
		tuple<float, Material, Point> getClosestIntersection(Ray ray, float tNear, int i);
		Point refract(Point i, Point n, float ior);

		void print();
};

#endif