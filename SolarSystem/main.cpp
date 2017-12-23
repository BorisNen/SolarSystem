#include "stdafx.h"
#include <math.h>
#include <GL/glut.h>	

#ifndef M_PI
#define M_PI 3.141592
#endif

void init();
void display();

float planetorb = 5.0f, const degInRad = M_PI / 180, milisecs = 10.0f;;

// TODO: add to planet class
float mercuryX, mercuryY;
float venusX, venusY;
float earthX, earthY;
float marsX, marsY;
float jupiterX, jupiterY;
float saturnX, saturnY;
float uranusX, uranusY;
float neptuneX, neptuneY;

// TODO: add to planet class
float counterForMercury = 0;
float counterForVenus = 0;
float counterForEarth = 0;
float counterForMars = 0;
float counterForJupiter = 0;
float counterForSaturn = 0;
float counterForUranus = 0;
float counterForNeptune = 0;

int width = 1000, height = 1000, segments;

void keyboard(unsigned char key, int x, int y);
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
	planetorb += 5.0f;
	glutPostRedisplay();
	glutTimerFunc(milisecs, timer, val);
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

void init()
{
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, width / 2, height / 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1500.0, 1500.0, -1500.0, 1500.0, -300.0, 200);

	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
	drawEllipse(57 * 0.3, 55 * 0.3, 0.2056, 40);//mercury
	drawEllipse(108 * 0.3, 107 * 0.3, 0.0067, 40);//venus
	drawEllipse(149 * 0.3, 148 * 0.3, 0.0167, 40);//earth
	drawEllipse(227 * 0.3, 225 * 0.3, 0.0933, 40);//mars
	drawEllipse(778 * 0.3, 777 * 0.3, 0.0483, 40);//jupiter
	drawEllipse(1433 * 0.3, 1430 * 0.3, 0.0538, 40);//saturn
	drawEllipse(2872 * 0.3, 2868 * 0.3, 0.0472, 40);//uranus
	drawEllipse(4495 * 0.3, 4494 * 0.3, 0.0085, 40);//neptune

	//making mercury
	if (counterForMercury > 359)
		counterForMercury = 0;//reset at 360
	else
		counterForMercury += 1/0.240; //speed control divide by orbital period

	mercuryX = cos(counterForMercury*degInRad) * 57 * 0.3 + 0.2056;
	mercuryY = sin(counterForMercury*degInRad) * 55 * 0.3;
	glPushMatrix();
	glTranslatef(mercuryX, mercuryY, 0.0f);
	glRotatef(planetorb, 0, 1, 0);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.38, 20, 20);
	glPopMatrix();

	//making venus
	if (counterForVenus > 359)
		counterForVenus = 0;//reset at 360
	else
		counterForVenus += 1/ 0.615; //speed control divide by orbital period

	venusX = cos(counterForVenus*degInRad) * 108 * 0.3 + 0.0067;
	venusY = sin(counterForVenus*degInRad) * 107 * 0.3;
	glPushMatrix();
	glTranslatef(venusX, venusY, 0.0f);
	glRotatef(planetorb, 0, 1, 0);
	glColor3f(1, 0.25, 0);
	glutSolidSphere(0.94, 20, 20);
	glPopMatrix();

	//making earth
	if (counterForEarth > 359)
		counterForEarth = 0;//reset at 360
	else
		counterForEarth++; //main speed control

	earthX = cos(counterForEarth*degInRad) * 149 * 0.3 + 0.0167;
	earthY = sin(counterForEarth*degInRad) * 148 * 0.3;
	glPushMatrix();
	glTranslatef(earthX, earthY, 0.0f);
	glRotatef(planetorb, 0, 1, 0);
	glColor3f(0, 1, 0);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();

	//making mars
	if (counterForMars > 359)
		counterForMars = 0;//reset at 360
	else
		counterForMars+=1/ 1.880; //speed control divide by orbital period

	marsX = cos(counterForMars*degInRad) * 227 * 0.3 + 0.0933;
	marsY = sin(counterForMars*degInRad) * 225 * 0.3;
	glPushMatrix();
	glTranslatef(marsX, marsY, 0.0f);
	glRotatef(planetorb, 0, 1, 0);
	glColor3f(1, 0, 0);
	glutSolidSphere(0.53, 20, 20);
	glPopMatrix();

	//TODO: make asteroid belt

	//making jupiter
	if (counterForJupiter > 359)
		counterForJupiter = 0;//reset at 360
	else
		counterForJupiter += 1/ 11.861; //speed control divide by orbital period

	jupiterX = cos(counterForJupiter*degInRad) * 778 * 0.3 + 0.0483;
	jupiterY = sin(counterForJupiter*degInRad) * 777 * 0.3;
	glPushMatrix();
	glTranslatef(jupiterX, jupiterY, 0.0f);
	glRotatef(planetorb, 0, 1, 0);
	glColor3f(0.65, 0.16, 0.16);
	glutSolidSphere(10.97, 20, 20);
	glPopMatrix();

	//making saturn
	if (counterForSaturn > 359)
		counterForSaturn = 0;//reset at 360
	else
		counterForSaturn += 1 / 29.457; //speed control divide by orbital period

	saturnX = cos(counterForSaturn*degInRad) * 1433 * 0.3 + 0.0538;
	saturnY = sin(counterForSaturn*degInRad) * 1430 * 0.3;
	glPushMatrix();
	glTranslatef(saturnX, saturnY, 0.0f);
	glRotatef(planetorb, 0, 1, 0);
	glColor3f(0.52, 0.37, 0.26);
	glutSolidSphere(9.14, 20, 20);
	glPopMatrix();

	//making uranus
	if (counterForUranus > 359)
		counterForUranus = 0;//reset at 360
	else
		counterForUranus += 1 / 84.016; //speed control divide by orbital period

	uranusX = cos(counterForUranus*degInRad) * 2872 * 0.3 + 0.0472;
	uranusY = sin(counterForUranus*degInRad) * 2868 * 0.3;
	glPushMatrix();
	glTranslatef(uranusX, uranusY, 0.0f);
	glRotatef(planetorb, 0, 1, 0);
	glColor3f(0.5, 0.5, 1);
	glutSolidSphere(3.98, 20, 20);
	glPopMatrix();

	//making neptune
	if (counterForNeptune > 359)
		counterForNeptune = 0;//reset at 360
	else
		counterForNeptune += 1 / 164.8; //speed control divide by orbital period

	neptuneX = cos(counterForNeptune*degInRad) * 4495 * 0.3 + 0.0085;
	neptuneY = sin(counterForNeptune*degInRad) * 4494 * 0.3;
	glPushMatrix();
	glTranslatef(neptuneX, neptuneY, 0.0f);
	glRotatef(planetorb, 0, 1, 0);
	glColor3f(0.2, 0.2, 1);
	glutSolidSphere(3.86, 20, 20);
	glPopMatrix();

	glutSwapBuffers();
}
