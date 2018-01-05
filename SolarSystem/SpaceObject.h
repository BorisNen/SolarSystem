#ifndef SpaceObject_H
#define SpaceObject_H

#include <GL/glut.h>
#include "SOIL.h"
#include <vector>

class SpaceObject
{

public:
	SpaceObject(float x, float y, float counter, float objectDimension, float axisRotationPedriod, const char* texturePath);
	SpaceObject(float x, float y, float counter, float dimension, float _axisRotationPedriod, const char* texturePath, std::vector<SpaceObject*> inputOrbitingBodies);
	SpaceObject(const char* texturePath);
	virtual void drawObject();
	static float rotationAngle;
	float getPositionX();
	float getPositionY();

protected:
	std::vector<SpaceObject*> orbitingBodies;
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
