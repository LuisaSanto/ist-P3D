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

#define M_PI (float) 3.1415926535


struct LensCamera : public Camera {
private:
    float focalDistance;
    float aperture;

public:
    LensCamera() = default;

    LensCamera(Point eye, Point at, Point up, int angle, float hither,
            int ResX, int ResY, float focalDistance, float aperture)
            : Camera(eye, at, up, angle, hither, ResX, ResY), focalDistance(focalDistance), aperture(aperture){}

    LensCamera(Camera camera, float focalDistance, float aperture) : Camera(camera.getEye(), camera.getAt(),
            camera.getUp(), camera.getFovy(), camera.getNear(), camera.getResX(), camera.getResY()) ,
            focalDistance(focalDistance), aperture(aperture) {}



    virtual Ray computePrimaryRay(Point focalp);
    Point originDOF();
    Point getFocalPoint(float x, float y);



};


#endif //IST_P3D_LENSCAMERA_H
