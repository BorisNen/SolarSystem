#include "SpaceObject.h"

SpaceObject::SpaceObject(float x,float y, float counter, float dimension, char* texturePath)
{
    objectX = x;
    objectY = y;
    objectCounter = counter;
    objectDimension = dimension;

    object = gluNewQuadric();
    objectTexture = loadTexture(texturePath);
}

void SpaceObject::drawObject()
{
    displayObject();
}

void SpaceObject::displayObject()
{
    if(object == NULL && objectTexture == NULL){ //check if the textures are loaded and reuse them
		gluQuadricDrawStyle(object, GLU_FILL);
		gluQuadricOrientation(object, GLU_OUTSIDE);
		gluQuadricTexture(object, GL_TRUE);
		gluQuadricNormals(object, GLU_SMOOTH);
	}
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