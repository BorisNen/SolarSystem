#include "stdafx.h"
#include <math.h>
#include <GL/glut.h>
#include "SOIL.h"
#include <vector>
#include "SpaceObject.h"
#include "OrbitingObject.h"
#include "DiskShapedObject.h"
#include "Camera.h"
#include <iostream>

#ifndef M_PI
#define M_PI 3.141592
#endif

float oldX, oldY = 0.0, trackedX, trackedY;

std::vector<SpaceObject*> spaceObjects;
SpaceObject* solarSystem;
int width = 1000, height = 1000, segments, pause = 1, milisecs = 21, isCameraFixed = 0;

Camera* camera;
const int ACCELERATE = 1;
const int ROTATE = 0;
int navigationMode = ROTATE;

void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);

void init();
void initSpaceObjects();
void display();
void keyboard(unsigned char key, int x, int y);
void timer(int);

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Solar System");

	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutTimerFunc(milisecs, timer, 0);

	glutMainLoop();
	return 0;
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '+':
		milisecs == 1 ? 1 : milisecs -= 10;
		break;
	case '-':
		milisecs > 90 ? 90 : milisecs += 10;
		break;
	case 'p':
		pause = abs(pause - 1);
		break;
	//case '3':
		//isCameraFixed = 1;
		//break;
	case '0':
		isCameraFixed = 0;
	}
}

void mouseMotion(int x, int y)
{
	float deltaX = x - oldX;
	float deltaY = y - oldY;

	if (navigationMode == ROTATE)
		camera->rotate(deltaX, deltaY);
	else
		camera->accelerate(deltaY);

	oldX = x;
	oldY = y;

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	oldX = x;
	oldY = y;

	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			navigationMode = ROTATE;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {
			navigationMode = ACCELERATE;
		}
	}
}

void timer(int val)
{
	if (pause) {
		SpaceObject::rotationAngle += 5.0f;
		glutPostRedisplay();
	}
	glutTimerFunc(milisecs, timer, val);
}

void init()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	glViewport(0, 0, width / 2, height / 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, (float)width / height, 0.01, 10000);
	glMatrixMode(GL_MODELVIEW);

	camera = new Camera();

	glPushMatrix();

	initSpaceObjects();
}

void initSpaceObjects()
{
	//TODO: find a working texture
	//spaceObjects.push_back(new DiskShapedObject("Textures/AsteroidBelt.jpg", 300 * 0.3, 500 * 0.3));												  // Asteroid ring
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.38f, 58, "Textures/Mercury.bmp", 0.240f, 0.2056f, 0, 570 * 0.3, 550 * 0.3, 0));			  // Mercury
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.94f, 243, "Textures/Venus.bmp", 0.615f, 0.0067f, 177, 1080 * 0.3, 1070 * 0.3, 0)); 		  // Venus
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 1.0f, 1, "Textures/Earth.bmp", 1, 0.0167f, 23, 1490 * 0.3, 1480 * 0.3, 0)); 				  // Earth
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.18f, 27, "Textures/Moon.jpg", 0.07f, 0.0554f, 0, 0.4844f / 0.3, 0.4838f / 0.3, 1));		  // Earth's moon
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.53f, 1, "Textures/Mars.bmp", 1.880f, 0.0933f, 25, 2270 * 0.3, 2250 * 0.3, 0)); 			  // Mars
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.18f, 27, "Textures/GenericMoon.jpg", 0.07f, 0.0554f, 0, 0.4844f / 0.3, 0.4838f / 0.3, 1));// Phobos
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 10.97f, 0.4f, "Textures/Jupiter.bmp", 11.861f, 0.0483f, 3, 7780 * 0.3, 7770 * 0.3, 0));	  // Jupiter
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.48f, 27, "Textures/GenericMoon.jpg", 2.0f, 0.0554f, 0, 16.2844f, 16.2838f, 1));			  //Callisto
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.38f, 27, "Textures/GenericMoon.jpg", 10.10f, 0.0554f, 40, 14.4844f, 14.4838f, 1));		  //Io
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.38f, 27, "Textures/Europa.jpg", 3.10f, 0.0554f, 90, 20.4844f, 20.4838f, 1));			  //Europa
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 9.14f, 0.44f, "Textures/Saturn.bmp", 29.457f, 0.0538f, 26, 14330 * 0.3, 14300 * 0.3, 0));	  // Saturn
	spaceObjects.push_back(new DiskShapedObject("Textures/SaturnRing.jpg", 64 * 0.3, 96 * 0.3));														  // Saturn's rings
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.25f, 27, "Textures/GenericMoon.jpg", 16.0f, 0.0554f, 0, 46.2844f, 46.2838f, 1));		  //Titan
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 3.98f, 0.71f, "Textures/Uranus.bmp", 84.016f, 0.0472f, 97, 28720 * 0.3, 28680 * 0.3, 0));	  // Uranus
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.08f, 27, "Textures/GenericMoon.jpg", 13.0f, 0.0554f, 0, 1.4844f / 0.3, 1.4838f / 0.3, 1));		  // Oberon
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 3.86f, 0.67f, "Textures/Neptune.bmp", 164.8f, 0.0085f, 28, 44950 * 0.3, 44940 * 0.3, 0));	  // Neptune
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.14f, 27, "Textures/GenericMoon.jpg", 6.0f, 0.0554f, 0, 1.4844f / 0.3, 1.4838f / 0.3, 1));		  // Triton

	solarSystem = new SpaceObject(0, 0, 0, 109, 25, "Textures/Sun.bmp", spaceObjects); // the Sun and all Planets
}

void display(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	//TODO make it work
	/*
	if (isCameraFixed) {
		trackedX = spaceObjects[2]->getPositionX();
		trackedY = spaceObjects[2]->getPositionY();
		camera->spaceObjectView(spaceObjects[2]->getPositionX(), spaceObjects[2]->getPositionY());
	}
	else
	{
	*/
		camera->pilotView();
	//}

	camera->move();

	solarSystem->drawObject();

	glutSwapBuffers();
}