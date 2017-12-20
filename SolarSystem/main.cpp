#include "stdafx.h"
#include <math.h>
#include <GL/glut.h>	

#ifndef M_PI
#define M_PI 3.141592
#endif

void init();
void display();

float planetorb = 0.0f, const degInRad = M_PI / 180;

// TODO: add to planet class
float mercuryX, mercuryY;
float venusX, venusY;
float earthX, earthY;
float marsX, marsY;
float jupiterX, jupiterY;
float saturnX, saturnY;
float uranusX, uranusY;
float neptuneX, neptuneY;

int counterForMercury = 0;
int counterForVenus = 0;
int counterForEarth = 0;
int counterForMars = 0;
int counterForJupiter = 0;
int counterForSaturn = 0;
int counterForUranus = 0;
int counterForNeptune = 0;

int width = 1000, height = 1000, segments;

void drawEllipse(float, float, float, float);
void timer(int);

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("SolarSystem");

	init();

	glutDisplayFunc(display);
	glutTimerFunc(100, timer, 20);

	glutMainLoop();
	return 0;
}

void drawEllipse(float radiusX, float radiusY, float eccentricity, float segments)
{
	glColor3f(0.2, 0.3, 0.5);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 360; i += 360 / segments)
	{
		float radians = i * degInRad;
		glVertex2f(cos(radians) * radiusX + eccentricity, sin(radians) * radiusY);
	}

	glEnd();
}

void timer(int val)
{
	planetorb += 0.5f;
	glutTimerFunc(val, timer, val);
	glutPostRedisplay();
}

void init()
{
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, width / 2, height / 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -300.0, 200);

	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// TODO: add to planet class
void display(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// making the sun
	glColor3f(1, 1, 0);
	glutSolidSphere(109 / 30, 20, 20);

	//making the orbits
	drawEllipse(152 * 0.05, 147 * 0.05, 0.0167, 40);

	//making earth
	if (counterForEarth > 359)
		counterForEarth = 0;//reset at 360
	else
		counterForEarth++; //speed control

	earthX = cos(counterForEarth*degInRad) * 152 * 0.05 + 0.0167;
	earthY = sin(counterForEarth*degInRad) * 147 * 0.05;
	glPushMatrix();
	glTranslatef(earthX, earthY, 0.0f);
	glRotatef(planetorb, 0, 1, 0);
	glColor3f(0, 1, 0);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();

	glutSwapBuffers();
}
