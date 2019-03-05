#include "Scene.h"

Scene::Scene() {}

void Scene::parse_nff(string fileName) {
	
	ifstream file;
	string lineContent;

	file.open(fileName.c_str());
		
	while (!file.eof()) {
		getline(file, lineContent);	
		cout << lineContent << endl;

	}
	file.close();
}