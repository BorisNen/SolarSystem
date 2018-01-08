#include "stdafx.h"
#include <GL/glut.h>
#include "DiskShapedObject.h"

DiskShapedObject::DiskShapedObject(const char* texturePath, float _innerRadius, float _outterRadius)
	: SpaceObject(texturePath)
{
	innerRadius = _innerRadius;
	outterRadius = _outterRadius;
}

void DiskShapedObject::drawObject(int displayOrbits)
{
	gluQuadricDrawStyle(object, GLU_FILL);
	gluQuadricOrientation(object, GLU_OUTSIDE);
	gluQuadricTexture(object, GL_TRUE);
	gluQuadricNormals(object, GLU_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, objectTexture);
	gluDisk(object, innerRadius, outterRadius, 100, 1);
	glDisable(GL_TEXTURE_2D);
}
