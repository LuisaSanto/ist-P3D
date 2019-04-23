//
// Created by Luisa Santo on 2019-04-21.
//

#include "LensCamera.h"

Ray LensCamera::computePrimaryRay(Point focalp) {
    Point origin = originDOF();
    Point direction = Point(focalp);
    Point newDirection = direction-origin;
    newDirection.normalize();
    return Ray(origin + getEye(), newDirection);
}

Point LensCamera::originDOF() {
    float k1, k2; Point origin;
    float lensX = 1;
    float lensY = 1;

    while (lensX*lensX + lensY*lensY > 1){
        lensX = (float)rand()/RAND_MAX;
        lensY = (float)rand()/RAND_MAX;

        lensX = (lensX * 2) - 1;
        lensY = (lensY * 2) - 1;
    }

    k1 = lensX * aperture;
    k2 = lensY * aperture;

    origin = getXe()*k1 + getYe()*k2;

    return origin;
}

Point LensCamera::getFocalPoint(float x, float y) {
    float df;
    df = (getEye() - getAt()).norma();

    Point xe = getXe()*(fdRatio * getWidth() * ((x / getResX()) - 0.5f));
    Point ye = getYe()*(fdRatio * getHeight() * ((y / getResY()) - 0.5f));
    Point ze  = getZe() *(fdRatio * (-df));

    Point direction = ze + ye + xe;

    return direction;
}


