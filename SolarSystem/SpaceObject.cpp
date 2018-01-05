#include "stdafx.h"
#include "LUtil.h"
#include "SpaceObject.h"
#include "OrbitingObject.h"
#include <vector>

float SpaceObject::rotationAngle = 5.0f;

SpaceObject::SpaceObject(float x, float y, float counter, float dimension, float _axisRotationPedriod, const char* texturePath)
{
	objectX = x;
	objectY = y;
	objectCounter = counter;
	objectDimension = dimension;
	axisRotationPedriod = _axisRotationPedriod;

	object = gluNewQuadric();
	objectTexture = loadTexture(texturePath);
}

SpaceObject::SpaceObject(float x, float y, float counter, float dimension, float _axisRotationPedriod, const char* texturePath, std::vector<SpaceObject*> inputOrbitingBodies)
{
	objectX = x;
	objectY = y;
	objectCounter = counter;
	objectDimension = dimension;
	axisRotationPedriod = _axisRotationPedriod;
	orbitingBodies = inputOrbitingBodies;

	object = gluNewQuadric();
	objectTexture = loadTexture(texturePath);
}

SpaceObject::SpaceObject(const char* texturePath)
{
	object = gluNewQuadric();
	objectTexture = loadTexture(texturePath);
}

void SpaceObject::drawObject()
{
	glPushMatrix(); //save identity matrix
	glRotatef(rotationAngle/axisRotationPedriod, 0, 0, 1); //rotate the sun around its axis

	displayObject();

	for (unsigned i = 0; i < orbitingBodies.size(); ++i)
	{
		orbitingBodies[i]->drawObject();
	}

	glPopMatrix(); //prepare identity matrix for planet drawing
}

void SpaceObject::displayObject()
{
	gluQuadricDrawStyle(object, GLU_FILL);
	gluQuadricOrientation(object, GLU_OUTSIDE);
	gluQuadricTexture(object, GL_TRUE);
	gluQuadricNormals(object, GLU_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, objectTexture);
	gluSphere(object, objectDimension, 20, 20);
	glDisable(GL_TEXTURE_2D);
}

GLuint SpaceObject::loadTexture(const char* texture)
{
	GLuint textureID = SOIL_load_OGL_texture(texture, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}
