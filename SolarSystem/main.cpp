#include "stdafx.h"
#include <math.h>
#include <GL/glut.h>
#include <soil.h>
#include <vector>
#include "SpaceObject.h"
#include "Planet.h"

#ifndef M_PI
#define M_PI 3.141592
#endif

std::vector<SpaceObject*> spaceObjects;
float axisRotation = 5.0f;
float milisecs = 20.0f;
int width = 1000, height = 1000, segments;
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

//TODO: fix to work in all cases
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '+':
		milisecs -= 1;
		break;
	case '-':
		milisecs += 1;
		break;
	}
}

void timer(int val)
{
	axisRotation += 5.0f;
	glutPostRedisplay();
	glutTimerFunc(milisecs, timer, val);
}

void init()
{
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, width / 2, height / 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1500.0, 1500.0, -1500.0, 1500.0, -30.0, 20);

	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	initSpaceObjects();
}

void initSpaceObjects()
{
	spaceObjects.push_back(new SpaceObject(0, 0, 0, 109 / 30, "Textures/Sun.bmp")); 										// the Sun
	spaceObjects.push_back(new Planet(0, 0, 0, 0.38f, "Textures/Mercury.bmp", 0.240f, 0.2056f, 57 * 0.3, 55 * 0.3)); 	// Mercury
	spaceObjects.push_back(new Planet(0, 0, 0, 0.94f, "Textures/Venus.bmp", 0.615f, 0.0067f, 108 * 0.3, 107 * 0.3)); 	// Venus
	spaceObjects.push_back(new Planet(0, 0, 0, 1.0f, "Textures/Earth.bmp", 1, 0.0167f, 149 * 0.3, 148 * 0.3)); 			// Earth
	spaceObjects.push_back(new Planet(0, 0, 0, 0.53f, "Textures/Mars.bmp", 1.880f, 0.0933f, 227 * 0.3, 225 * 0.3)); 		// Mars
	spaceObjects.push_back(new Planet(0, 0, 0, 10.97f, "Textures/Jupiter.bmp", 11.861f, 0.0483f, 778 * 0.3, 777 * 0.3));	// Jupiter
	spaceObjects.push_back(new Planet(0, 0, 0, 9.14f, "Textures/Saturn.bmp", 29.457f, 0.0538f, 1433 * 0.3, 1430 * 0.3)); // Saturn
	spaceObjects.push_back(new Planet(0, 0, 0, 3.98f, "Textures/Uranus.bmp", 84.016f, 0.0472f, 2872 * 0.3, 2868 * 0.3));	// Uranus
	spaceObjects.push_back(new Planet(0, 0, 0, 3.86f, "Textures/Neptune.bmp", 164.8f, 0.0085f, 4495 * 0.3, 4494 * 0.3));	// Neptune
}

void display(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (unsigned i = 0; i < spaceObjects.size(); ++i) {
		spaceObjects[i]->drawObject();
	}

	glutSwapBuffers();
}