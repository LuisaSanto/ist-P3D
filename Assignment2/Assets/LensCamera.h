//
// Created by Luisa Santo on 2019-04-21.
//

#ifndef IST_P3D_LENSCAMERA_H
#define IST_P3D_LENSCAMERA_H

#include "Camera.h"
#include "Point.h"
#include "Plane.h"
#include "Ray.h"
#include "Object.h"


struct LensCamera : public Camera {
private:
    Plane focalPlane;
    float aperture;

public:
    LensCamera() = default;

    LensCamera(Point eye, Point at, Point up, int angle, float hither,
            int ResX, int ResY, float focalDistance, float aperture)
            : Camera(eye, at, up, angle, hither, ResX, ResY), focalPlane(getZe(), focalDistance), aperture(aperture){}

    LensCamera(Camera* camera, float focalDistance, float aperture) : Camera(camera->getEye(), camera->getAt(),
            camera->getUp(), camera->getFovy(), camera->getNear(), camera->getResX(), camera->getResY()) ,
            focalPlane(getZe(), focalDistance), aperture(aperture) {}

    Point getFocalPoint(Ray &r);
    virtual Point getLenseSamplePoint();
};


#endif //IST_P3D_LENSCAMERA_H
