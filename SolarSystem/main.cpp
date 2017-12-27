#include "stdafx.h"
#include <math.h>
#include <GL/glut.h>
#include <soil.h>
#include <vector>
#include "SpaceObject.h"
#include "OrbitingObject.h"
#include "DiskShapedObject.h"

#ifndef M_PI
#define M_PI 3.141592
#endif

std::vector<SpaceObject*> spaceObjects;
int width = 1000, height = 1000, segments, pause = 1, milisecs = 21;
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

	glViewport(0, 0, width / 2, height / 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1500.0, 1500.0, -1500.0, 1500.0, -60.0, 60);

	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();

	initSpaceObjects();
}

void initSpaceObjects()
{
	spaceObjects.push_back(new SpaceObject(0, 0, 0, 109 / 12, 25, "Textures/Sun.bmp")); 															  // the Sun
	//TODO: find a working texture
	//spaceObjects.push_back(new DiskShapedObject("Textures/AsteroidBelt.jpg", 300 * 0.3, 500 * 0.3));												  // Asteroid ring
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.38f, 58, "Textures/Mercury.bmp", 0.240f, 0.2056f, 0, 57 * 0.3, 55 * 0.3, false));			  // Mercury
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.94f, 243, "Textures/Venus.bmp", 0.615f, 0.0067f, 177, 108 * 0.3, 107 * 0.3, false)); 		  // Venus
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 1.0f, 1, "Textures/Earth.bmp", 1, 0.0167f, 23, 149 * 0.3, 148 * 0.3, false)); 				  // Earth
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.18f, 27, "Textures/Moon.jpg", 0.07f, 0.0554f, 0, 0.4844f / 0.3, 0.4838f / 0.3, true));		  // Earth's moon
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.53f, 1, "Textures/Mars.bmp", 1.880f, 0.0933f, 25, 227 * 0.3, 225 * 0.3, false)); 			  // Mars
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.18f, 27, "Textures/GenericMoon.jpg", 0.07f, 0.0554f, 0, 0.4844f / 0.3, 0.4838f / 0.3, true));// Phobos
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 10.97f, 0.4f, "Textures/Jupiter.bmp", 11.861f, 0.0483f, 3, 778 * 0.3, 777 * 0.3, false));	  // Jupiter
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.48f, 27, "Textures/GenericMoon.jpg", 2.0f, 0.0554f, 0, 16.2844f, 16.2838f, true));			  //Callisto
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.38f, 27, "Textures/GenericMoon.jpg", 10.10f, 0.0554f, 40, 14.4844f, 14.4838f, true));		  //Io
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.38f, 27, "Textures/Europa.jpg", 3.10f, 0.0554f, 90, 20.4844f, 20.4838f, true));			  //Europa
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 9.14f, 0.44f, "Textures/Saturn.bmp", 29.457f, 0.0538f, 26, 1433 * 0.3, 1430 * 0.3, false));	  // Saturn
	spaceObjects.push_back(new DiskShapedObject("Textures/SaturnRing.jpg", 64*0.3, 96 *0.3));														  // Saturn's rings
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.25f, 27, "Textures/GenericMoon.jpg", 16.0f, 0.0554f, 0, 46.2844f, 46.2838f, true));		  //Titan
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 3.98f, 0.71f, "Textures/Uranus.bmp", 84.016f, 0.0472f, 97, 2872 * 0.3, 2868 * 0.3, false));	  // Uranus
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.08f, 27, "Textures/GenericMoon.jpg", 13.0f, 0.0554f, 0, 1.4844f / 0.3, 1.4838f / 0.3, true));		  // Oberon
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 3.86f, 0.67f, "Textures/Neptune.bmp", 164.8f, 0.0085f, 28, 4495 * 0.3, 4494 * 0.3, false));	  // Neptune
	spaceObjects.push_back(new OrbitingObject(0, 0, 0, 0.14f, 27, "Textures/GenericMoon.jpg", 6.0f, 0.0554f, 0, 1.4844f / 0.3, 1.4838f / 0.3, true));		  // Triton
}

void display(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPopMatrix();

	for (unsigned i = 0; i < spaceObjects.size(); ++i) {
		spaceObjects[i]->drawObject();
	}

	glutSwapBuffers();
}