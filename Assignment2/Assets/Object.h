#ifndef OBJECT_H
#define OBJECT_H

#include "Material.h"
#include "Point.h"
#include "Ray.h"
#include "BoundingBox.h"

using namespace std;

class Object {
    protected:
        Point _normal;
        Point _rayHitPoint;
        Material _material;
        BoundingBox box;

    public:
        //Constructors
        Object() = default;

        Object(Material material);

        //Getters
        Material getMaterial() { return _material; }
        Point getNormal() { return _normal; }
        Point getRayHitPoint() { return _rayHitPoint; }
        BoundingBox getBoundingBox(){return box;}


        Point setNormal(Point normal) { _normal = normal; }
        Point setRayHitPoint(Ray ray, float t);

        //Virtual
        virtual float checkRayCollision (Ray ray) = 0;
        virtual void print() = 0;
        virtual bool CheckRayCollision(const Ray &Ray, float *distance, Point *hitpoint) = 0;

};

#endif
