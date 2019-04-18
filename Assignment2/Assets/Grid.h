#ifndef GRID_H
#define GRID_H

#include "Object.h"
#include "Point.h"
#include "Ray.h"
#include "BoundingBox.h"
#include <vector>
#include <algorithm>

//#define EPSILON 0.00001

const float kMin = numeric_limits<float>::min();
const float kMax = numeric_limits<float>::max();


using namespace std;


class Grid
{
    public:
        BoundingBox box;
        int nx, ny, nz;
        int number_objects;
        float m = 2.0f;
        std::vector<std::vector<Object*>> cells;
        Grid() {};
        Grid(std::vector<Object*> objects) {
            number_objects = objects.size();
            computeBoundingBox(objects);
        }
    private:
            void computeBoundingBox(std::vector<Object*> objects);
            void initializeGridCells(std::vector<Object*> objects);
            float traverse(Ray ray);
            int clamp(float x, float a, float b) {
                return x < a ? a : (x > b ? b : x);
            }
};

#endif
