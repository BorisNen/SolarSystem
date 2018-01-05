#include "stdafx.h"
#include "LUtil.h"
#include "OrbitingObject.h"

#ifndef M_PI
#define M_PI 3.141592
#endif

const float OrbitingObject::DEG_IN_RAD = M_PI / 180;

OrbitingObject::OrbitingObject(float x, float y, float counter, float dimension, float axisRotationPedriod, const char* texturePath, float _orbitalPeriod, float _eccentricity, float _inclination, float _radiusX, float _radiusY, int _isMoon)
	: SpaceObject(x, y, counter, dimension, axisRotationPedriod, texturePath)
{
	orbitalPeriod = _orbitalPeriod;
	eccentricity = _eccentricity;
	inclination = _inclination;
	radiusX = _radiusX;
	radiusY = _radiusY;
	isMoon = _isMoon;
}

void OrbitingObject::drawObject()
{
	if (isMoon) {
		drawMoonObject();
	} else {
		drawPlanetObject();
	}
}

void OrbitingObject::drawPlanetObject()
{
	glPopMatrix(); //get the identity matrix before drawing a new planet
	glPushMatrix(); //and save it

	drawOrbit();
	//TODO: fix path after tilt
	//glRotated(inclination, 1, 0, 0); //axis tilt

	// calculate planet position on orbital path
	if (objectCounter > 359)
		objectCounter = 0;//reset at 360
	else
		objectCounter += 1 / orbitalPeriod; //speed control divide by orbital period

	objectX = cos(objectCounter*OrbitingObject::DEG_IN_RAD) * radiusX + eccentricity;
	objectY = sin(objectCounter*OrbitingObject::DEG_IN_RAD) * radiusY;
	glTranslatef(objectX, objectY, 0.0f);

	glPushMatrix(); //save the planet matrix to draw the moon without unnecessary rotation

	glRotatef(rotationAngle/axisRotationPedriod, 0, 0, 1); //axis rotation

	// draw planet
	SpaceObject::displayObject();
	
	glPopMatrix(); //get planet matrix for moon drawing
}

void OrbitingObject::drawMoonObject()
{
	glPushMatrix(); //save the planet matrix to draw other moons
	glRotatef(inclination, 1, 0, 0);
	drawOrbit();

	// calculate moon position on orbital path 
	if (objectCounter > 359)
		objectCounter = 0;//reset at 360
	else
		objectCounter += 1 / orbitalPeriod; //speed control divide by orbital period
		
	objectX = cos(objectCounter*OrbitingObject::DEG_IN_RAD) * radiusX + eccentricity;
	objectY = sin(objectCounter*OrbitingObject::DEG_IN_RAD) * radiusY;
	glTranslatef(objectX, objectY, 0.0f);

	// draw moon
	SpaceObject::displayObject();

	glPopMatrix(); //get planet matrix for moon drawing
}

void OrbitingObject::drawOrbit()
{
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 360; i += 360 / 40)
	{
		float radians = i * OrbitingObject::DEG_IN_RAD;
		glVertex2f(cos(radians) * radiusX + eccentricity, sin(radians) * radiusY);
	}

	glEnd();
}
