//
// Created by Luisa Santo on 2019-04-21.
//

#include "LensCamera.h"

Point LensCamera::getFocalPoint(Ray &r) {
    // TODO
    Point hitpoint = Point(0.0, 0.0, 0.0);
    hitpoint = focalPlane.getRayHitPoint()
    focalPlane.checkRayCollision(r);
    return hitpoint;
}

Point LensCamera::getLenseSamplePoint() {
    Point randomPoint = Point(0.0, 0.0, 0.0);
    float k1, k2;
    bool inside = false;
    while (!inside) {
        //random between [-aperture, +aperture]
        k1 = aperture * 2 * (((double)rand() / (RAND_MAX)) - 0.5);
        k2 = aperture * 2 * (((double)rand() / (RAND_MAX)) - 0.5);

        randomPoint = getEye() + getXe()*k1 + getYe()*k2;

        if ((randomPoint - getEye()).norma() < aperture * aperture) {
            inside = true;
        }
    }

    return randomPoint;
}