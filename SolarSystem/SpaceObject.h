#ifndef SpaceObject_H
#define SpaceObject_H

#include <GL/glut.h>
#include "SOIL.h"

class SpaceObject
{
public:
	SpaceObject(float x, float y, float counter, float objectDimension, const char* texturePath);
	virtual void drawObject();

protected:
	float objectX;
	float objectY;
	float objectCounter;
	float objectDimension;
	GLUquadric *object;
	GLuint objectTexture;

	GLuint loadTexture(const char* texture);
	void displayObject();

};

#endif