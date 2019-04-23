#include "Object.h"

Object::Object (Material material) {
    _material = material;
}

Point Object::setRayHitPoint(Ray ray, float t) {
    _rayHitPoint = ray.pointAtParameter(t);
}
