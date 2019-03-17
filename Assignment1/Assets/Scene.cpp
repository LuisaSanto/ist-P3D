#include "Scene.h"
#include <string.h>
#include <string>

Scene::Scene() {}




//=================Whitted Ray Tracing Algorithm============
Color Scene::trace(Ray ray, int depth) {



	//Save the nearest object intersected by the ray and what type of object
	tuple<float, Material, Point> nearestObject;



	//Get some info about the closest intersection Object
	//Returns Tuple with closest Intersection, closest object's material and closest object's normal;
	nearestObject = getClosestIntersection(ray, INFINITE, 0);
	

	//Check if there isn't nearest object then return bColor
	
	if (get<0>(nearestObject) == INFINITE) {
		return getBgColor();
	}
	else {
		Material material = get<1>(nearestObject);
		//Color colorFinal = material.getColor(); //What is the ambient color;
		Color colorFinal = Color(0.0f, 0.0f, 0.0f);
		//Color ambientColor = Color(0.0f, 0.0f, 0.0f);
		//Color specularColor = Color(0.0f, 0.0f, 0.0f);
		//Color diffuseColor = Color(0.0f, 0.0f, 0.0f);

		//Get the hitPoint from the Nearest Intersection tNear
		Point hitPoint = ray.pointAtParameter(get<0>(nearestObject));
		
		//Get the Normal at that Hit Point
		Point normal = get<2>(nearestObject);
		//cout << normal.norma() << endl;
		//normal.print();

		//Local Color and illumination

		for (Light l : getLights()) {


			//Unit Vector from the hit Point to Light source position
			//Light l = getLights()[0];
			Point L = l.getPos().sub(hitPoint);
			//Point L = hitPoint.sub(l.getPos());
			//L.print();
			L.normalize();
			//cout << L.norma() << endl;
			if (L.inner(normal) > 0) {
				//Trace Shadow Ray
				Point shadowHitPoint = hitPoint.add(normal.multiply(0.001)); // add an offset
				Ray shadowRay = Ray(shadowHitPoint, L); 
				tuple<float, Material, Point> shadow = getClosestIntersection(shadowRay, INFINITE, 1);
				
				if (get<0>(shadow) == INFINITE) {
					//cout << "Point not in shadow!!" << endl;
					//cout << "Entrei!" << endl;
					//cout << get<1>(shadow).getSpecular() << endl;
					

					//Ambient Color
					//ambientColor = ambientColor.add(L.inner(normal));



					//Diffuse color
					//Color diffuseColor = material.getColor().mul(material.getDiffuse() * L.inner(normal));
					Color diffuseColor = material.getColor().mul(material.getDiffuse() * L.inner(normal));
					//Multiply by color intensity
					//diffuseColorLight = diffuseColor.mul(0.1);

					//diffuseColor = diffuseColor.add(diffuseColorLight);
					

					//Specular color
					Point r = normal.multiply(L.inner(normal));
					r = r.multiply(-2);
					r = r.sub(L);
					r.normalize();

					Point v = hitPoint.sub(getCamera().getEye());
					v.normalize();

					Color specularColor = material.getColor().mul(material.getSpecular() * pow(r.inner(v), 25));
					//specularColor = specularColor.add(specularColorLight);
					//diffuseColor.print();	
					//specularColor.print();

					colorFinal = colorFinal.add(diffuseColor).add(specularColor);

					
				}
				/*else {
					cout << "Point in shadow!!" << endl;
				}		*/
			}
		}

		//colorFinal = colorFinal.add(ambientColor).add(diffuseColor).add(specularColor);

		if (depth >= 3) { //maxDepth
			colorFinal.print();
			return colorFinal;
		}

		//Reflective object

		if (material.getSpecular() != 0) {
			Point rRayOrigin = hitPoint.add(normal.multiply(0.001));
			Point rRayDirection = normal.multiply(ray.getDirection().inner(normal));
			rRayDirection = rRayDirection.multiply(-2);
			rRayDirection = rRayDirection.add(ray.getDirection());

			Ray rRay = Ray(rRayOrigin, rRayDirection);
			Color rColor = trace(rRay, depth++);
			colorFinal = colorFinal.add(rColor.mul(material.getSpecular()));
		}

		//Translucid object

		//colorFinal.print();
		return colorFinal;

	
	}

	 
}
	//return getBgColor();



//=================Parsing NFF Methods============
void Scene::parse_nff(string fileName) {
	
	ifstream file;
	int auxNumber;
	string nextLine,nextLine1, token, auxStr;
	stringstream lineContent, auxLine, auxLine1;

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
		else if (token.compare("from") == 0) {	
			//Save the next 6 lines of the file
			cout << "Entrei" << endl;
			auxLine << nextLine;
			for (int i = 0; i < 5; i++) {
				getline(file, nextLine);
				auxLine << nextLine;
				auxLine << '\n';
			}
			do_camera(auxLine);
		}
		
		else if (token.compare("l") == 0) {
			cout << "Doing light" << endl;
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
			auxStr = lineContent.str();
			auxNumber = stoi(auxStr.substr(auxStr.find(' ')+ 1,2));

			auxLine1.str("");
			auxLine1.clear();

			for (int i = 0; i < auxNumber; i++) {
				getline(file, nextLine1);
				auxLine1 << nextLine1;
				auxLine1 << '\n';
			}
			do_polygon(auxLine1);
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

void Scene::do_polygon(stringstream& line) {
	string token;
	//string lineAux = line.str();

	//getline(line, token, '\n');
	//token = strtok ((char *)lineAux.c_str(),"\n");

	

	//cout << line.str() << endl;

	Point p1 = create_Point(line);
	//cout << line.str() << endl;
	//Point p2 = create_Point(line);
	//Point p3 = create_Point(line);

	//cout << p1.print() << endl;
	//cout << p2.print() << endl;
	//cout << p3.print() << endl;
	cout << "======== Another one =======" << endl;

	//Get material
	Material material = materials.back();


	//Create Sphere
	//Polygon p = Polygon(p, radius, material);
	//addPolygon(s);
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
	/*for (auto value : getSpheres()) {
		value.print();
	}*/for (auto value : getPlanes()) {
		value.print();
	}for (auto value : getPoints()) {
		value.print();
	}for (auto value : getPolygons()) {
		value.print();
	}
}

tuple<float, Material, Point> Scene::getClosestIntersection(Ray ray, float tNear, int i) {
	int closestObject;
	Sphere closestSphere;
	Plane closestPlane;
	float tNearK;

	//Intersect with all spheres of the scene
	for (Sphere sphere : getSpheres()) {
		tNearK = sphere.intersectSphere(ray);
		if (tNearK < tNear) {
			tNear = tNearK;
			closestSphere = sphere;
			closestObject = 0;
		}
	}

	
	//Intersect with all planes of the scene
	for (Plane plane : getPlanes()) {
		tNearK = plane.intersectPlane(ray);
		//cout << tNearK << endl;
		if (tNearK < tNear) {
			tNear = tNearK;
			closestPlane = plane;
			closestObject = 1;
		}
	}
	


	//Intersect with all polygons

	//======TO DO======

	if (tNear != INFINITE) {
		if (closestObject == 0) { //closestObject is a sphere
			return make_tuple(tNear, closestSphere.getMaterial(), closestSphere.getNormal());
		} 
		else if (closestObject == 1) { //closestObjcect is a plane
			//closestPlane.print();
			return make_tuple(tNear, closestPlane.getMaterial(), closestPlane.getNormal());
		}
		// TO DO: else if for polygons
	}
	else {
		return make_tuple(tNear, Material(), Point());
	}
}