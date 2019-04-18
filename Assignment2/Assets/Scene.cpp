#include "Scene.h"
#include <string.h>
#include <string>

Scene::Scene() {}




//=================Whitted Ray Tracing Algorithm============
Color Scene::trace(Ray ray, int depth, float refrIndex, bool insideObject, int softShadows) {


	//Save the nearest object intersected by the ray and what type of object
	Object* nearestObject;


	//Get some info about the closest intersection Object
	nearestObject = getClosestIntersection(ray);

	//Check if there isn't nearest object then return bColor
	
	if (nearestObject == nullptr) {
		return getBgColor();
	}
	else {
		Material material = nearestObject->getMaterial();
		Color colorFinal = Color(0.0f, 0.0f, 0.0f);


		//Get the hitPoint from the Nearest Intersection tNear
		Point hitPoint = nearestObject->getRayHitPoint();
		
		//Get the Normal at that Hit Point
		Point normal = nearestObject->getNormal();

		//Local Color and illumination
		for (Light* l : getLights()) {

            //Unit Vector from the hit Point to Light source position
			Point L;

			if (softShadows == 0) {
				//No soft shadows
                L = l->getPos() - hitPoint;
            }
            else {
                //With soft shadows
                L = l->getJitterPoint() - hitPoint;
            }
            L.normalize();

            if (L.inner(normal) > 0) {
                //Trace Shadow Ray
                Point shadowHitPoint = hitPoint + L * 0.001; // add an offset
                Ray shadowRay = Ray(shadowHitPoint, L);
                bool inShadow = checkInShadow(shadowRay);
                //If point is not in shadow
                if (!inShadow) {
                    colorFinal = colorFinal + getLocal(material, l->getColor(), hitPoint, L, normal);
                }
            }
        }
		if (depth >= 3) { //maxDepth
			return colorFinal;
		}

		//Reflective object
            if (insideObject) {
            normal = - normal;
        }

		if (material.getSpecular() != 0) {
			Point rRayDirection = normal * ray.getDirection().inner(normal);
			rRayDirection = rRayDirection * (-2);
			rRayDirection = rRayDirection + ray.getDirection();
			rRayDirection.normalize();
			Point rRayOrigin = hitPoint + rRayDirection * 0.001;


			Ray rRay = Ray(rRayOrigin, rRayDirection);
			depth = depth + 1;
			Color rColor = trace(rRay, depth, refrIndex, insideObject, softShadows);
			colorFinal = colorFinal + rColor * material.getSpecular();
		}

		//Translucid object

		if (material.getTransmittance() != 0) {
		    Point tRayDirection;
		    if (insideObject) {
                tRayDirection = refract(-ray.getDirection(), normal, material.getRefrIndex(), refrIndex, insideObject);
		    }
			else
                tRayDirection = refract(-ray.getDirection(), normal, refrIndex, material.getRefrIndex(), insideObject);
			if (!tRayDirection.isEqual(Point(0,0,0))) {
                tRayDirection.normalize();
                Point tRayOrigin = hitPoint + tRayDirection * 0.001;
                Ray tRay = Ray(tRayOrigin, tRayDirection);
                depth = depth + 1;
                insideObject = !insideObject;
                Color tColor = trace(tRay, depth, refrIndex, insideObject, softShadows);
                colorFinal = colorFinal + tColor * material.getTransmittance();
            }
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
	Light *l = new Light(p, color);
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
	Sphere* s = new Sphere(p, radius, material);
	//addSphere(s);
	addObject(s);
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
	Polygon* p = new Polygon(point1, point2, point3, material);
	//addPolygon(p);
    addObject(p);
}

void Scene::do_plane(stringstream& line) {

	//Create Points

	Point p1 = create_Point(line);
	Point p2 = create_Point(line);
	Point p3 = create_Point(line);

	//Get material

	Material material = materials.back();


	//Create Plane
	Plane* plane = new Plane(p1, p2, p3, material);
	//addPlane(plane);
    addObject(plane);
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
		value->print();
	}
	for (auto value : getObjects()) {
	    value->print();
	}
}


//===================== Whitted Ray Tracer auxiliar methods ==============

//Compute the refracted ray Direction
Point Scene::refract(Point i, Point normal, float ioRin, float ioRout, bool insideObject) {

	// 1st way
	Point v, t, r;
	float sin, cos;

	v = normal * i.inner(normal) - i;
	sin = v.norma();
	sin = sin * ioRin / ioRout;
	if ((sin * sin) <= 1) {
        cos = float(sqrt(1 - pow(sin, 2)));

        t = v;
        t.normalize();


        r = t * sin + (-normal) * cos;
        r.normalize();
        return r;
    }
	return Point(0, 0, 0);
}

Color Scene::getLocal(Material material, Color lightColor, Point hitPoint, Point L, Point normal) {

	//Diffuse color

	Color diffuseColor = material.getColor() * material.getDiffuse() * L.inner(normal);



	//Specular color
	Point r = normal * L.inner(normal);
	r = r * (2);
	r = r - L;
	r.normalize();

	Point v = -(hitPoint - getCamera().getEye());
	v.normalize();
	Color specularColor = Color(0,0,0);
	if (r.inner(v) > 0) {
        specularColor = lightColor * (material.getSpecular() * pow(r.inner(v), material.getShine()));
    }

	return diffuseColor + specularColor;
}

Object* Scene::getClosestIntersection(Ray ray) {
	float tNear = kInfinity;
	float tNearK;
	Object* closestObj = nullptr;

	//Intersect with all objects of the scene
	for (auto obj : getObjects()) {
        tNearK = obj->checkRayCollision(ray);
        if (tNearK < tNear) {
            tNear = tNearK;
            closestObj = obj;
            closestObj->setRayHitPoint(ray, tNear);
        }
	}
	return closestObj;
}

bool Scene::checkInShadow(Ray ray) {
    float tNear = kInfinity;
    float tNearK;
    //Intersect with all objects of the scene
    for (auto obj : getObjects()) {
        tNearK = obj->checkRayCollision(ray);
        if (tNearK < tNear) {
            return true;
        }
    }
    return false;
}

void Scene::createGrid(){
	this->grid = Grid(this->objects);
}