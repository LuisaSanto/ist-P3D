#include "Scene.h"
#include <string.h>
#include <string>

Scene::Scene() {}




//=================Whitted Ray Tracing Algorithm============
Color Scene::trace(Ray ray, int depth, float refrIndex) {


	//Save the nearest object intersected by the ray and what type of object
	tuple<float, Material, Point> nearestObject;


	//Get some info about the closest intersection Object
	//Returns Tuple with closest Intersection, closest object's material and closest object's normal;
	nearestObject = getClosestIntersection(ray);

	//Check if there isn't nearest object then return bColor
	
	if (get<0>(nearestObject) == kInfinity) {
		return getBgColor();
	}
	else {
		Material material = get<1>(nearestObject);
		Color colorFinal = Color(0.0f, 0.0f, 0.0f);


		//Get the hitPoint from the Nearest Intersection tNear
		Point hitPoint = ray.pointAtParameter(get<0>(nearestObject));
		
		//Get the Normal at that Hit Point
		Point normal = get<2>(nearestObject);

		//Local Color and illumination
		for (Light l : getLights()) {

			//Unit Vector from the hit Point to Light source position
			Point L = l.getPos() - hitPoint;
			L.normalize();

			if (L.inner(normal) > 0) {
			    //Trace Shadow Ray
			    Point shadowHitPoint = hitPoint + L * 0.001; // add an offset
			    Ray shadowRay = Ray(shadowHitPoint, L);
			    tuple<float, Material, Point> shadow = getClosestIntersection(shadowRay);
			    //If point is not in shadow
			    if (get<0>(shadow) == kInfinity) {
			        colorFinal = colorFinal + getLocal(material, hitPoint, L, normal);
			    }
			}
		}

		if (depth >= 3) { //maxDepth
			return colorFinal;
		}

		//Reflective object

		if (material.getSpecular() != 0) {
			Point rRayDirection = normal * ray.getDirection().inner(normal);
			rRayDirection = rRayDirection * (-2);
			rRayDirection = rRayDirection + ray.getDirection();
			rRayDirection.normalize();
			Point rRayOrigin = hitPoint + rRayDirection * 0.001;


			Ray rRay = Ray(rRayOrigin, rRayDirection);
			depth = depth + 1;
			Color rColor = trace(rRay, depth, refrIndex);
			colorFinal = colorFinal + rColor * material.getSpecular();
		}

		//Translucid object

		if (material.getTransmittance() != 0) {
			Point tRayDirection = refract(-ray.getDirection(), normal, material.getRefrIndex(), refrIndex);
			tRayDirection.normalize();
			Point tRayOrigin = hitPoint + tRayDirection * 0.001;
			Ray tRay = Ray(tRayOrigin, tRayDirection);
			depth = depth + 1;
			Color tColor = trace(tRay, depth, material.getRefrIndex());
			colorFinal = colorFinal + tColor * material.getTransmittance();
		}


		return colorFinal;

		
	}

	 
}



//=================Parsing NFF Methods============
void Scene::parse_nff(string fileName) {
	
	ifstream file;
	int auxNumber;
	string nextLine,nextLine1, token, auxStr;
	stringstream lineContent, auxLine, auxLine1;

	file.open(fileName.c_str());
		
	while (getline(file, nextLine)) {

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
			auxLine << nextLine;
			for (int i = 0; i < 5; i++) {
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
			auxStr = lineContent.str();
			auxNumber = stoi(auxStr.substr(auxStr.find(' ')+ 1,2));

			auxLine1.str("");
			auxLine1.clear();
			
			auxLine << nextLine;
			for (int i = 0; i < auxNumber; i++) {
				getline(file, nextLine1);
				auxLine1 << nextLine1 + '\n';
				auxLine1 << '\n';
			}
			
			do_polygon(auxLine1);
		}
	}
	file.close();
}

void Scene::do_background(stringstream& line) {

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
	string myString = line.str();
	stringstream p1, p2, p3;


	string aux = line.str().substr(0,line.str().find('\n'));
	myString.erase(0,myString.find('\n')+2);
	string aux1 = myString.substr(0, myString.find('\n'));
	myString.erase(0,myString.find('\n')+2);
	string aux2 = myString.substr(0,myString.find('\n'));

	p1 << aux;
	p2 << aux1;
	p3 << aux2;

	//From at up 
	Point point1 = create_Point(p1);
	Point point2 = create_Point(p2);
	Point point3 = create_Point(p3);

	//Get material
	Material material = materials.back();


	//Create Polygon
	Polygon p = Polygon(point1, point2, point3, material);
	addPolygon(p);
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
	}for (auto value : getPolygons()) {
		value.print();
	}
}


//===================== Whitted Ray Tracer auxiliar methods ==============

//Compute the refracted ray Direction
Point Scene::refract(Point i, Point normal, float ior1, float ior2) {

    //cout << "Norma v: " << i.norma() << endl;
    //cout << "Norma normal: " << normal.norma() << endl;
	// 1st way
	Point v, t, r;
	float sin, cos;

	//float etai = 1;
	//float etat = ior;

	//v = normal.multiply(i.inner(normal)).sub(i);
	v = normal * i.inner(normal) - i;
	sin = v.norma();
	sin = sin * ior2 / ior1;
	cos = float (sqrt(1 - pow(sin, 2)));

	/*if (cos < 0) {
		cos = -cos;

	}
	else {
		swap(etai, etat);
		normal = -normal;
	}*/


	t = v;
	t.normalize();


	//r = t.multiply(sin).add(normal.multiply(-cos));
	r = t * sin + (-normal) * cos;
	r.normalize();
	return r;


	// 2nd way
	/*float cosi = i.inner(normal);
	float etai = 1, etat = ior;
	Point n = normal;
	if (cosi < 0) { cosi = -cosi; } else { swap(etai, etat); n= normal.operator*(-1); }
	float eta = etai / etat;
	float k = 1 - eta * eta * (1 - cosi * cosi);
	return k < 0 ? Point() : i * (eta) + n * ((eta * cosi - sqrtf(k)));*/





	// 3rd way
	/*float eta = 1 / ior;

	float N_dot_I = normal.inner(i);
	float k = 1 - pow(eta, 2) * (1 - pow(N_dot_I, 2));
	if (k < 0)
		return Point();
	else 
		return i * eta - normal * (eta * N_dot_I + sqrt(k));*/
}

Color Scene::getLocal(Material material, Point hitPoint, Point L, Point normal) {

	//Diffuse color

	Color diffuseColor = material.getColor() * material.getDiffuse() * L.inner(normal);



	//Specular color
	Point r = normal * L.inner(normal);
	r = r * (-2);
	r = r - L;
	r.normalize();

	Point v = hitPoint - getCamera().getEye();
	v.normalize();

	Color specularColor = material.getColor() * (material.getSpecular() * pow(r.inner(v), 25));


	return diffuseColor + specularColor;
}

tuple<float, Material, Point> Scene::getClosestIntersection(Ray ray) {
	int closestObject;
	Sphere closestSphere;
	Plane closestPlane;
	Polygon closestPolygon;
	float tNear = kInfinity;
	float tNearK;

	//cout << "ANTES" << endl;

	//Intersect with all spheres of the scene
	for (Sphere sphere : getSpheres()) {
		//cout << "ANTES2" << endl;
		tNearK = sphere.intersectSphere(ray);
		//cout << "DEPOIS" << endl;
		if (tNearK < tNear) {
			tNear = tNearK;
			closestSphere = sphere;
			closestObject = 0;
		}
	}

	//cout << "BOM DIAAAAA" << endl;

	
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
	for (Polygon polygon : getPolygons()) {
		tNearK = polygon.intersectPolygon(ray);
		//cout << tNearK << endl;
		if (tNearK < tNear) {
			tNear = tNearK;
			closestPolygon = polygon;
			closestObject = 2;
		}
	}
	//cout << "================= CLOSEST OBJECT ================" << endl;
	if (tNear != kInfinity) {
		if (closestObject == 0) { //closestObject is a sphere
			//cout << "===SPHERE===" << endl;
			//closestSphere.print();
			return make_tuple(tNear, closestSphere.getMaterial(), closestSphere.getNormal());
		} 
		else if (closestObject == 1) { //closestObjcect is a plane
			//cout << "===PLANE===" << endl;
			//closestPlane.print();
			return make_tuple(tNear, closestPlane.getMaterial(), closestPlane.getNormal());
		}
		else if (closestObject == 2) { //closestObjcect is a plane
			//cout << "===POLYGON===" << endl;
			//closestPolygon.print();
			return make_tuple(tNear, closestPolygon.getMaterial(), closestPolygon.getNormal());
		}
	}
	else {
		return make_tuple(tNear, Material(), Point());
	}
}