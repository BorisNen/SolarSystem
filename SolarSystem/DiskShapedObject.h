#ifndef DiskShapedObject_H
#define DiskShapedObject_H

#include "SpaceObject.h"
#include <math.h>

class DiskShapedObject : public SpaceObject
{
	// Disk size info
	float innerRadius;
	float outterRadius;

public:
	DiskShapedObject(const char* texturePath, float _innerRadius, float _outterRadius);
private:
	void drawObject();
};

#endif