#include "stdafx.h"
#include "Camera.h"
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

const float thetaEps = 0.01;
const float Pi = 3.141592;

// Konstruktor: Default Werte setzen
Camera::Camera()
{
	mPosition.setXYZ(0, 120, 0);  // irgendwo ueber dem Ursprung (hoffentlich ueber dem Berg...)
	mSpeed = 0.0;
	mTheta = Pi / 2.0;           // Kamera waagrecht
	mPhi = Pi / 4.0;             // schraeg durchs Gelaende schauen 
	calcViewDirection();       // mDir aus (theta,phi) initialisieren
	mUp.setXYZ(0, 1, 0);
	mThetaSens = -0.01;        // Empfindlichkeit der Steuerung
	mPhiSens = 0.01;
	mAccSens = -0.01;
}

Camera::~Camera()
{
}

// gluLookAt mit Kamera Parametern setzen
void Camera::spaceObjectView(float x, float y)
{
	gluLookAt(x, y, 0,
		x, y, 0,
		0, 1, 0);
}

// gluLookAt mit Kamera Parametern setzen
void Camera::pilotView()
{
	gluLookAt(mPosition.x(), mPosition.y(), mPosition.z(),
		mPosition.x() + mDir.x(), mPosition.y() + mDir.y(), mPosition.z() + mDir.z(),
		mUp.x(), mUp.y(), mUp.z());
}

// Kamera entlang der Blickrichtung mit aktueller Geschwindigkeit bewegen
void Camera::move()
{
	Vector3D delta = mSpeed * mDir;
	mPosition = mPosition + delta;
}

// Hilfsfunktion: Richtungsvektor aus (theta, phi) berechnen
void Camera::calcViewDirection()
{
	mDir.setXYZ(sin(mTheta) * cos(mPhi), cos(mTheta), sin(mTheta) * sin(mPhi));
}

// Kamera drehen
void Camera::rotate(float deltaX, float deltaY)
{
	float deltaTheta = mThetaSens * deltaY;        // Schrittwinkel fuer Theta
	mTheta += deltaTheta;
	if (mTheta < thetaEps) mTheta = thetaEps;      // Gueltigkeitsbereich testen
	else if (mTheta > Pi - thetaEps) mTheta = Pi - thetaEps; // nie entlang up-Vector fliegen

	float deltaPhi = mPhiSens * deltaX;        // Schrittwinkel fuer Phi
	mPhi += deltaPhi;
	if (mPhi < 0) mPhi += 2 * Pi;               // Gueltigkeitsbereich testen
	else if (mPhi > 2 * Pi) mPhi -= 2 * Pi;

	calcViewDirection();        // (theta,phi) in (x,y,z) umrechnen
}

// Kamera beschleunigen
void Camera::accelerate(float deltaY)
{
	float acceleration = mAccSens * deltaY;   // Geschwindigkeitsaenderung
	mSpeed += acceleration;                   // auf aktuelle Geschwindigkeit addieren 
}