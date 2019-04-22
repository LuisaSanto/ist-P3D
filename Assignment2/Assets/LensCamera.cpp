//
// Created by Luisa Santo on 2019-04-21.
//

#include "LensCamera.h"

//Point LensCamera::getFocalPoint(float psx,float  psy) {
//    // TODO
//    //==========ISTO SUPOSTAMENTE NAO PODE SER CALCULADO USANDO O RAIO COMO ARGUMENTO============//
//    /*Point hitpoint = Point(0.0, 0.0, 0.0);
//    hitpoint = focalPlane.getRayHitPoint();
//    //cout << "Focal Plane" << endl;
//    //focalPlane.print();
//    focalPlane.checkRayCollision(r);
//    return hitpoint;*/
//
//    //==========Se souberes o centro da lente, consegues atraves da trigonometria calcular o ponto focal=======000
//    //==========    Slide 35 do Distribution RayTracing
//    float px = psx * focalPlane.getFocalDistance() / getNear();
//    float py = psy * focalPlane.getFocalDistance() / getNear();
//    Point focalPoint = Point(px, py, -focalPlane.getFocalDistance());
//    return focalPoint;
//}
//
//Point LensCamera::getLenseSamplePoint() {
//    Point randomPoint = Point(0.0, 0.0, 0.0);
//    float k1, k2;
//    bool inside = false;
//    while (!inside) {
//        //random between [-aperture, +aperture]
//        k1 = aperture * 2 * (((double)rand() / (RAND_MAX)) - 0.5);
//        k2 = aperture * 2 * (((double)rand() / (RAND_MAX)) - 0.5);
//
//        randomPoint = getEye() + getXe()*k1 + getYe()*k2;
//
//
//        if ((randomPoint - getEye()).norma() < aperture * aperture) {
//            //randomPoint.print();
//            inside = true;
//        }
//    }
//    //cout << "sai" << endl;
//    return randomPoint;
//}

Ray LensCamera::getPrimaryRay(float x, float y) {
    Point p = getEye() -getAt()*focalDistance + x*getResX()*getXe() + y*getResY()*getYe();
    float r1 = sqrtf(random())*aperture;
    float r2 = random()*2.0f*pi;
    Point center2 = getEye() + getXe()*r1*cosf(r2) + getUp()*r1*sinf(r2);
    return Ray(center2, (p-center2).normalize());
}