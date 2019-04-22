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
    float r, theta, x, y;
    Point u, v, w;
    r = sqrtf(RAND); theta = 2*PIRAND;
    x = aperture * r * cosf(theta);
    y = aperture * r * sinf(theta);

    u = Point(getXe());
    v = Point(getYe());
    w = Point(getZe());

    u*x; u*y; u+v; u+getEye();

    //delete w; delete v;
    return u;
}

Point LensCamera::getFocalPoint(float x, float y) {
    Point u, v, w;

    u = Point(getXe());
    v = Point(getYe());
    w = Point(getZe());

    u*(focalDistance * getWidth() * ((x / getResX()) - 0.5f));
    v*(focalDistance * getHeight() * ((y / getResY()) - 0.5f));
    w*(focalDistance * (getEye() - getAt()).norma());

    u+v; u+w; u+getEye();

    //delete v; delete u;
    return u;
}