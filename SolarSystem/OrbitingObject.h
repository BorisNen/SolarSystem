#ifndef OrbitingObject_H
#define OrbitingObject_H

#include "SpaceObject.h"
#include <math.h>

class OrbitingObject : public SpaceObject
{
	// Orbit info
	float orbitalPeriod;
	float eccentricity;
	float inclination; //Equatorial Inclination
	float radiusX;
	float radiusY;
	BOOLEAN isMoon;

public:
	OrbitingObject(float x, float y, float counter, float dimension, float axisRotationPedriod, const char* texturePath, float _orbitalPeriod, float _eccentricity, float inclination, float _radiusX, float _radiusY, BOOLEAN isMoon);
	virtual void drawObject();
private:
	void drawOrbit();
	void drawPlanetObject();
	void drawMoonObject();
	static float const DEG_IN_RAD;
};

#endif