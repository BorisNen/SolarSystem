#ifndef Planet_H
#define Planet_H

#include "SpaceObject.h"
#include <math.h>

class Planet : public SpaceObject
{   
    // Orbit info
    float orbitalPeriod;
    float eccentricity;
    float radiusX;
    float radiusY;

    public:
        Planet(float x,float y, float counter, float dimension, char* texturePath, float _orbitalPeriod, float _eccentricity, float _radiusX, float _radiusY);
        virtual void drawObject();
    private:
        void drawOrbit();
        static float const DEG_IN_RAD = M_PI / 180;
};

#endif