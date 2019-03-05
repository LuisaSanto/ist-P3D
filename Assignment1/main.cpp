#include "Assets/Scene.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main (int argc, char* argv[])
{	
	if (argc < 1) {
		cerr << "You need to put a nff file name" << endl;
		return 1;
	}
    Scene scene;
    //cout << argv[1] << endl;
    scene.parse_nff(argv[1]);
    return 0;
}