//
// Created by vasco on 02-04-2019.
//

#ifndef LIGHTAREA_H
#define LIGHTAREA_H


class LightArea : public Light {
    private:
        Point a;
        Point b;

    public:
        LightArea(Point pos, Color color) : Light(pos, color) {

        }



};


#endif