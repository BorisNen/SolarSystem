#ifndef _CAMERA_H
#define _CAMERA_H

#include "Vector3D.h"

class Camera
{
public:
	Camera();
	~Camera();

	void spaceObjectView(float x, float y, float distX, float distY);
	void pilotView();
	void move();
	void rotate(float deltaX, float deltaY);
	void accelerate(float deltaY);

private:
	void calcViewDirection();

	Vector3D mPosition;       // aktuelle Position
	float mSpeed;             // aktuelle Geschwindigkeit
	float mTheta;             // Blickrichtung als (theta,phi) Winkel
	float mPhi;
	Vector3D mDir;            // Blickrichtung als Vektor (wird mehrfach gebraucht, deshalb speichern) 
	Vector3D mUp;
	float mThetaSens;         // Empfindlichkeit Rotation
	float mPhiSens;
	float mAccSens;           // Empfindlichkeit Beschleunigung
};

#endif

