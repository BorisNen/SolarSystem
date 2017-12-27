#ifndef SpaceObject_H
#define SpaceObject_H

#include <GL/glut.h>
#include "SOIL.h"

class SpaceObject
{
public:
	SpaceObject(float x, float y, float counter, float objectDimension, float axisRotationPedriod, const char* texturePath);
	SpaceObject(const char* texturePath);
	virtual void drawObject();
	static float rotationAngle;

protected:
	float objectX;
	float objectY;
	float objectCounter;
	float objectDimension;
	float axisRotationPedriod; //speed of axis rotation
	GLUquadric *object;
	GLuint objectTexture;

	GLuint loadTexture(const char* texture);
	void displayObject();

};

#endif