//
// Created by Luisa Santo on 2019-04-21.
//

#include "LensCamera.h"

Ray LensCamera::(Point focalp) {
    Point origin = originDOF();
    Point direction = Point(focalp);
    Point newDirection = direction-origin
    return Ray(origin, newDirection.normalize());
}

Point LensCamera::originDOF() {
    float k1, k2; Point origin;

    float r = sqrtf(RAND);
    float theta = 2*PIRAND;
    boot insideCircle = false;

    while (!insideCircle) {
        k1 = aperture * r * cosf(theta);
        k2 = aperture * r * sinf(theta);

        origin = getXe()*k1 + getYe()*k2 + getEye();

        if ((origin - getEye()).norma() < aperture * aperture) {
            insideCircle = true
        }
    }

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


