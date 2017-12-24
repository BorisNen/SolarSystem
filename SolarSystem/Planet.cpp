#include "stdafx.h"
#include <GL/glut.h>
#include "Planet.h"

#ifndef M_PI
#define M_PI 3.141592
#endif

const float Planet::DEG_IN_RAD = M_PI / 180;

Planet::Planet(float x, float y, float counter, float dimension, const char* texturePath, float _orbitalPeriod, float _eccentricity, float _radiusX, float _radiusY)
	: SpaceObject(x, y, counter, dimension, texturePath)
{
	orbitalPeriod = _orbitalPeriod;
	eccentricity = _eccentricity;
	radiusX = _radiusX;
	radiusY = _radiusY;
}

void Planet::drawObject()
{
	drawOrbit();

	// calculate planet position on orbital path 
	if (objectCounter > 359)
		objectCounter = 0;//reset at 360
	else
		objectCounter += 1 / orbitalPeriod; //speed control divide by orbital period

	objectX = cos(objectCounter*Planet::DEG_IN_RAD) * radiusX + eccentricity;
	objectY = sin(objectCounter*Planet::DEG_IN_RAD) * radiusY;
	glPushMatrix();
	glTranslatef(objectX, objectY, 0.0f);

	// draw planet
	SpaceObject::displayObject();

	glPopMatrix();
}

void Planet::drawOrbit()
{
	//glColor3f(0.2, 0.3, 0.5);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 360; i += 360 / 40)
	{
		float radians = i * Planet::DEG_IN_RAD;
		glVertex2f(cos(radians) * radiusX + eccentricity, sin(radians) * radiusY);
	}

	glEnd();
}