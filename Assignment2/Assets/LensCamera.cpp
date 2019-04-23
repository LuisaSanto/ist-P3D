//
// Created by Luisa Santo on 2019-04-21.
//

#include "LensCamera.h"

Ray LensCamera::computePrimaryRay(Point focalp) {
    Point origin = originDOF();
    //Point * direction = new Point(focalp);
    Point direction = Point(focalp);
    direction-origin;
    return Ray(origin, direction);
}

Point LensCamera::originDOF() {
    float r = sqrtf(RAND);
    float theta = 2*PIRAND;

    Point u = getXe()*(aperture * r * cosf(theta)) + getYe()*(aperture * r * sinf(theta)) + getEye();

    return u;
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