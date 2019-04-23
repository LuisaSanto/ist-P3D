//
// Created by Luisa Santo on 2019-04-21.
//

#include "LensCamera.h"

Ray LensCamera::computePrimaryRay(Point focalp) {
    Point origin = originDOF();
    Point direction = Point(focalp);
    Point newDirection = direction-origin;
    newDirection.normalize();
    return Ray(origin, newDirection);
}

Point LensCamera::originDOF() {
    float k1, k2; Point origin;

<<<<<<< HEAD
    float r = sqrtf(RAND);
    float theta = 2*PIRAND;

    k1 = aperture * r * cosf(theta);
    k2 = aperture * r * sinf(theta);
=======
    //float r = rand()/
    //float theta = 2*PIRAND;
    bool insideCircle = false;

    while (!insideCircle) {
        k1 = aperture * 2 * (((double)rand() / (RAND_MAX)) - 0.5);
        k2 = aperture * 2 * (((double)rand() / (RAND_MAX)) - 0.5);
>>>>>>> 4c8658131f8b843f8cb59e3f4555b55e781fe884

    origin = getXe()*k1 + getYe()*k2 + getEye();

    return origin;
}

Point LensCamera::getFocalPoint(float x, float y) {
    float df;
    df = (getEye() - getAt()).norma();

    Point xe = getXe()*(focalDistance * getWidth() * ((x / getResX()) - 0.5f));
    Point ye = getYe()*(focalDistance * getHeight() * ((y / getResY()) - 0.5f));
    Point ze  = getZe() *(focalDistance * (-df));

    Point direction = ze + ye + xe;

    return direction;
}


