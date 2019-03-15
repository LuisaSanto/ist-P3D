#include "Scene.h"
#include <string>

Scene::Scene() {}




//=================Whitted Ray Tracing Algorithm============
vector<float> Scene::trace(Ray ray, int depth) {
	//Set the Nearest Point to infinity
	float tNear = numeric_limits<float>::max();
	float tNearK;

	//Intersect with all spheres of the scene
	for (auto sphere : getSpheres()) {
		tNearK = sphere.intersectSphere(ray);
		//cout << "tNearK: " << tNearK << endl;

		/*if (tNearK == numeric_limits<float>::max())
			//cout << "No intersection for this sphere!" << endl;
		else {
			//cout << "There's an intersection!!" << endl;
			//cout << tNearK << endl;
		}*/

		if (tNearK < tNear) {
			//cout << "Entrei!!" << endl;
			tNear = tNearK;
		}
	}

	//Intersect with all planes
	/*for (auto plane : getPlanes()) {
		tNearK = plane.intersectPlane(ray);
		cout << tNearK << endl;
		if (tNearK < tNear) {
			tNear = tNearK;
		}
	}*/

	//Intersect with all polygons
	
	//Check if tNear is infinity then return bColor
	
	if (tNear == numeric_limits<float>::max()) {
		//cout << "Returning BG color" << endl;
		return getBgColor();
	}
	else {
		Point hitPoint = ray.pointAtParameter(tNear);
		//cout << "Returning intersection color" << endl;
		return vector<float>(3, 0.0f); 
	 
	}
	return getBgColor();

}


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
	string token;

	for (int i = 0; i < 3; i++) {
		getline(line, token, ' ');
		bgColor.push_back(stof(token));
	}
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

	//Create Light
	Light l = Light(p, r, g, b);
	addLight(l);
}

void Scene::do_material(stringstream& line) {

	//Get Material components
	
	float r, g, b, Kd, Ks, shine, T, refr_index ;
	r = get_float(line);
	g = get_float(line);
	b = get_float(line);
	Kd = get_float(line);
	Ks = get_float(line);
	shine = get_float(line);
	T = get_float(line);
	refr_index = get_float(line);

	//Create Light
	Material m = Material (r, g, b, Kd, Ks, shine, T, refr_index);
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