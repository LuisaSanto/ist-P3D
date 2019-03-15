#include "Scene.h"
#include <string>

Scene::Scene() {}




//=================Whitted Ray Tracing Algorithm============
Color Scene::trace(Ray ray, int depth) {
	//Set the Nearest Point to infinity
	float tNear = numeric_limits<float>::max();
	float tNearK;
	float k = 0;

	//Save the nearest object intersected by the ray and what type of object
	Sphere s;
	Plane p;
	int object; //0 for sphere, 1 for polygon and 2 for plane;
	Material material;

	//Intersect with all spheres of the scene
	for (Sphere sphere : getSpheres()) {
		tNearK = sphere.intersectSphere(ray);
		if (tNearK < tNear) {
			//cout << "Entrei!!" << endl;
			tNear = tNearK;
			//material = sphere.getMaterial();
			s = sphere;
			material = s.getMaterial();
			object = 0;
		}
	}

	//Intersect with all planes of the scene
	for (Plane plane : getPlanes()) {
		tNearK = plane.intersectPlane(ray);
		//cout << tNearK << endl;
		if (tNearK < tNear) {
			tNear = tNearK;
			k = 1;
			//material = plane.getMaterial();
			p = plane;
			material = p.getMaterial();
			object = 1;
		}
	}

	//Intersect with all polygons
	
	//Check if tNear is infinity then return bColor
	
	if (tNear == numeric_limits<float>::max()) {
		//cout << "Returning BG color" << endl;
		return getBgColor();
	}
	else {
		//Color 
		Color colorFinal = Color(0.0f, 0.0f, 0.0f);


		//Get the hitPoint from the Nearest Intersection tNear
		Point hitPoint = ray.pointAtParameter(tNear);
		
		//Get the Normal at that Hit Point
		Point normal;
		if (object == 0) //Sphere 
			normal = s.getNormal();
		else if (object == 1) //Plane
			normal = p.getNormal();


		//Local Color and illumination

		for (Light l : getLights()) {
			Point L = l.getPos().sub(hitPoint).norma();
			if (L.inner(normal) > 0) {
				//Trace Shadow Ray
				Color diffuseColor = l.getColor().mul(material.getDiffuse() * L.inner(normal));
				colorFinal = colorFinal.add(diffuseColor);
			}
		}

		if (depth >= 3) { //maxDepth
			return colorFinal;
		}

		//Reflective object

		//Translucid object

		return colorFinal;

		

















		/*if (k == 0)
			return Color(0.0f, 0.0f, 0.0f);
		else {
			return Color(0.0f, 1.0f, 0.0f);*/
		}

	 
}
	//return getBgColor();



//=================Parsing NFF Methods============
void Scene::parse_nff(string fileName) {
	
	ifstream file;
	string nextLine, token;
	stringstream lineContent, auxLine;

	file.open(fileName.c_str());
		
	while (getline(file, nextLine)) {		
		//cout << nextLine << endl;

		//Copy line to a string stream
		lineContent.str("");
		lineContent.clear();
		lineContent << nextLine;

		//Get first word of each line
		getline(lineContent, token, ' ');

		if (token.compare("b") == 0) {
			do_background(lineContent);
		}
		else if (token.compare("v") == 0) {	
			//Save the next 6 lines of the file
			for (int i = 0; i < 6; i++) {
				getline(file, nextLine);
				auxLine << nextLine;
				auxLine << '\n';
			}
			do_camera(auxLine);
		}
		
		else if (token.compare("l") == 0) {
			do_light(lineContent);
		}	
		else if (token.compare("f") == 0) {
			do_material(lineContent);
		}	
		else if (token.compare("s") == 0) {
			do_sphere(lineContent);
		}
		else if (token.compare("pl") == 0) {
			do_plane(lineContent);
		}
		else if (token.compare("p") == 0) {
			string auxLine = lineContent.str();
			int auxNumber = stoi(auxLine.substr(auxLine.find(' ')+ 1,2));
			for (int i = 0; i < auxNumber; i++) {
				getline(file, nextLine);
			}
			//doPolygon(nextLine);
		}
	}
	file.close();
}

void Scene::do_background(stringstream& line) {
	//string token;

	//Get rgb
	float r, g, b;
	r = get_float(line);
	g = get_float(line);
	b = get_float(line);

	Color color = Color(r, g, b);
	addBgColor(color);
}

void Scene::do_camera(stringstream& line) {
	string token;
	getline(line, token, ' ');
	
	//From at up 
	Point from = create_Point(line);
	Point at = create_Point(line);
	Point up = create_Point(line);

	//Angle
	float angle = get_float(line);

	//Hither
	float hither = get_float(line);

	//Resolution
	float ResX = get_float(line);
	float ResY = get_float(line);

	Camera camera = Camera(from, at, up, angle, hither, ResX, ResY);
	addCamera(camera);
}

void Scene::do_light(stringstream& line) {

	//Create Point
	
	Point p = create_Point(line);
	
	//Get rgb
	float r, g, b;
	r = get_float(line);
	g = get_float(line);
	b = get_float(line);

	Color color = Color(r, g, b);

	//Create Light
	Light l = Light(p, color);
	addLight(l);
}

void Scene::do_material(stringstream& line) {

	//Get Material components
	
	float r, g, b, Kd, Ks, shine, T, refr_index ;
	r = get_float(line);
	g = get_float(line);
	b = get_float(line);
	Color color = Color(r, g, b);
	Kd = get_float(line);
	Ks = get_float(line);
	shine = get_float(line);
	T = get_float(line);
	refr_index = get_float(line);

	//Create Light
	Material m = Material (color, Kd, Ks, shine, T, refr_index);
	addMaterial(m);
}

void Scene::do_sphere(stringstream& line) {

	//Create Point
	
	Point p = create_Point(line);
	
	//Get radius
	float radius;

	radius = get_float(line);

	//Get material

	Material material = materials.back();


	//Create Sphere
	Sphere s = Sphere(p, radius, material);
	addSphere(s);
}

void Scene::do_plane(stringstream& line) {

	//Create Points
	
	Point p1 = create_Point(line);
	Point p2 = create_Point(line);
	Point p3 = create_Point(line);
	

	//Get material

	Material material = materials.back();


	//Create Plane
	Plane plane = Plane(p1, p2, p3, material);
	addPlane(plane);
}

void Scene::do_point(stringstream& line) {

	//Create Point
	for (int i = 0; i < 3; i++) {
		Point p = create_Point(line);
		points.push_back(p);
	}
}

//=================Auxiliar Methods============
float Scene::get_float(stringstream& line) {
	string token;
	getline(line, token, ' ');
	return stof(token);
}

Point Scene::create_Point(stringstream& line) {
	float x, y, z;
	x = get_float(line);
	y = get_float(line);
	z = get_float(line);
	return Point(x, y, z);
}

void Scene::print() {
	getCamera().print();
	//cout << materials.size() << endl;
	for (auto value : getMaterials()) {
		value.print();
	}
	for (auto value : getLights()) {
		value.print();
	}
	for (auto value : getSpheres()) {
		value.print();
	}for (auto value : getPlanes()) {
		value.print();
	}for (auto value : getPoints()) {
		value.print();
	}
}