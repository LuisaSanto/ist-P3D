#include "Light.h"

Light::Light(Point pos, Color color) {
	_pos = pos;
	_color = color;

	//Define area of light
	_a = _pos - Point(1,0,0);
	_b = _pos - Point(0,1,0);
	_normal = _a.cross(_b);
	_normal.normalize();


}

void Light::print() {
	cout << "======== Light Info =======" << endl;
	_pos.print();
	_color.print();
}

void *Light::addJitteredPoints(int N) {

    /*float epsilon1 = ((float) rand() / (RAND_MAX));
    float epsilon2 = ((float) rand() / (RAND_MAX));
    Point randomSample = _pos + _a * epsilon1 + _b * epsilon2;*/
    Point randomSample;

    float epsilon = ((float) rand() / (RAND_MAX));
    for (int p = 0; p < N; p++) {
        for (int q = 0; q < N; q++) {
            float i = (p + epsilon) / N;
            float j = (q + epsilon) / N;

            //randomSample = Point(i,j, randomSample.z());
            randomSample = _pos + _a * i + _b * j;
            _jitteredPoints.push_back(randomSample);
        }
    }
}

Point Light::getJitterPoint() {
    //cout << "ola2" << endl;
	int size = _jitteredPoints.size();
	//cout << size << endl;
	int i = rand()%(size);
	return _jitteredPoints[i];


}