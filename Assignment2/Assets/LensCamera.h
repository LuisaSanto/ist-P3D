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


// The epsilon value adjustment for precision errors.
static const float epsilon = 0.000001f;

// The mathematical pi constant
static const float pi = 3.141592f;


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

//    Point getFocalPoint(float x, float y);
//    Point getLenseSamplePoint();
    virtual Ray computePrimaryRay(float x, float y);
    //Ray getPrimaryRay(float x, float y);


};


#endif //IST_P3D_LENSCAMERA_H
