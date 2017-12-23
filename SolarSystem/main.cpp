#include "stdafx.h"
#include <math.h>
#include <GL/glut.h>
#include <soil.h>

#ifndef M_PI
#define M_PI 3.141592
#endif

void init();
void display();

float axisRotation = 5.0f, const degInRad = M_PI / 180, milisecs = 20.0f;;

// TODO: add as a member of planet class
float mercuryX, mercuryY;
float venusX, venusY;
float earthX, earthY;
float marsX, marsY;
float jupiterX, jupiterY;
float saturnX, saturnY;
float uranusX, uranusY;
float neptuneX, neptuneY;

// TODO: add as a member of planet class
float counterForMercury = 0;
float counterForVenus = 0;
float counterForEarth = 0;
float counterForMars = 0;
float counterForJupiter = 0;
float counterForSaturn = 0;
float counterForUranus = 0;
float counterForNeptune = 0;

//TODO: add as a member of planet class
GLUquadric *sun, *mercury, *venus, *earth, *mars, *jupiter, *saturn, *uranus, *neptune;
GLuint sunTexture, mercuryTexture, venusTexture, earthTexture, marsTexture, jupiterTexture, saturnTexture, uranusTexture, neptuneTexture;

int width = 1000, height = 1000, segments;

void keyboard(unsigned char key, int x, int y);
void drawEllipse(float, float, float, float);
void timer(int);
GLuint LoadTexture(const char* texture);

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

GLuint LoadTexture(const char* texture)
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

void timer(int val)
{
	axisRotation += 5.0f;
	glutPostRedisplay();
	glutTimerFunc(milisecs, timer, val);
}

void drawEllipse(float radiusX, float radiusY, float eccentricity, float segments)
{
	//glColor3f(0.2, 0.3, 0.5);
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
	glOrtho(-1500.0, 1500.0, -1500.0, 1500.0, -30.0, 20);

	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// TODO: add to planet class
void display(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// making the sun
	if(sun == NULL && sunTexture == NULL){ //check if the textures are loaded and reuse them
		sun = gluNewQuadric();
		sunTexture = LoadTexture("Textures/Sun.bmp");
		gluQuadricDrawStyle(sun, GLU_FILL);
		gluQuadricOrientation(sun, GLU_OUTSIDE);
		gluQuadricTexture(sun, GL_TRUE);
		gluQuadricNormals(sun, GLU_SMOOTH);
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sunTexture);
	gluSphere(sun, 109 / 30, 20, 20);
	glDisable(GL_TEXTURE_2D);

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
	if (mercury == NULL && mercuryTexture == NULL) {//check if the textures are loaded and reuse them
		mercury = gluNewQuadric();
		mercuryTexture = LoadTexture("Textures/Mercury.bmp");
		gluQuadricDrawStyle(mercury, GLU_FILL);
		gluQuadricOrientation(mercury, GLU_OUTSIDE);
		gluQuadricTexture(mercury, GL_TRUE);
		gluQuadricNormals(mercury, GLU_SMOOTH);
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mercuryTexture);
	gluSphere(mercury, 0.38, 20, 20);
	glDisable(GL_TEXTURE_2D);
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
	//glRotatef(axisRotation, 1, 0, 0);
	if (venus == NULL && venusTexture == NULL) {//check if the textures are loaded and reuse them
		venus = gluNewQuadric();
		venusTexture = LoadTexture("Textures/Venus.bmp");
		gluQuadricDrawStyle(venus, GLU_FILL);
		gluQuadricOrientation(venus, GLU_OUTSIDE);
		gluQuadricTexture(venus, GL_TRUE);
		gluQuadricNormals(venus, GLU_SMOOTH);
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, venusTexture);
	gluSphere(venus, 0.94, 20, 20);
	glDisable(GL_TEXTURE_2D);
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
	//glRotatef(axisRotation, 1, 0, 0);
	if (earth == NULL && earthTexture == NULL) {//check if the textures are loaded and reuse them
		earth = gluNewQuadric();
		earthTexture = LoadTexture("Textures/Earth.bmp");
		gluQuadricDrawStyle(earth, GLU_FILL);
		gluQuadricOrientation(earth, GLU_OUTSIDE);
		gluQuadricTexture(earth, GL_TRUE);
		gluQuadricNormals(earth, GLU_SMOOTH);
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, earthTexture);
	gluSphere(earth, 1, 20, 20);
	glDisable(GL_TEXTURE_2D);
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
	//glRotatef(axisRotation, 1, 0, 0);
	if (mars == NULL && marsTexture == NULL) {//check if the textures are loaded and reuse them
		mars = gluNewQuadric();
		marsTexture = LoadTexture("Textures/Mars.bmp");
		gluQuadricDrawStyle(mars, GLU_FILL);
		gluQuadricOrientation(mars, GLU_OUTSIDE);
		gluQuadricTexture(mars, GL_TRUE);
		gluQuadricNormals(mars, GLU_SMOOTH);
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, marsTexture);
	gluSphere(mars, 0.53, 20, 20);
	glDisable(GL_TEXTURE_2D);
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
	//glRotatef(axisRotation, 1, 0, 0);
	if (jupiter == NULL && jupiterTexture == NULL) {//check if the textures are loaded and reuse them
		jupiter = gluNewQuadric();
		jupiterTexture = LoadTexture("Textures/Jupiter.bmp");
		gluQuadricDrawStyle(jupiter, GLU_FILL);
		gluQuadricOrientation(jupiter, GLU_OUTSIDE);
		gluQuadricTexture(jupiter, GL_TRUE);
		gluQuadricNormals(jupiter, GLU_SMOOTH);
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, jupiterTexture);
	gluSphere(jupiter, 10.97, 20, 20);
	glDisable(GL_TEXTURE_2D);
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
	//glRotatef(axisRotation, 1, 0, 0);
	if (saturn == NULL && saturnTexture == NULL) {//check if the textures are loaded and reuse them
		saturn = gluNewQuadric();
		saturnTexture = LoadTexture("Textures/Saturn.bmp");
		gluQuadricDrawStyle(saturn, GLU_FILL);
		gluQuadricOrientation(saturn, GLU_OUTSIDE);
		gluQuadricTexture(saturn, GL_TRUE);
		gluQuadricNormals(saturn, GLU_SMOOTH);
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, saturnTexture);
	gluSphere(saturn, 9.14, 20, 20);
	glDisable(GL_TEXTURE_2D);
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
	//glRotatef(axisRotation, 1, 0, 0);
	if (uranus == NULL && uranusTexture == NULL) {//check if the textures are loaded and reuse them
		uranus = gluNewQuadric();
		uranusTexture = LoadTexture("Textures/Uranus.bmp");
		gluQuadricDrawStyle(uranus, GLU_FILL);
		gluQuadricOrientation(uranus, GLU_OUTSIDE);
		gluQuadricTexture(uranus, GL_TRUE);
		gluQuadricNormals(uranus, GLU_SMOOTH);
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, uranusTexture);
	gluSphere(uranus, 3.98, 20, 20);
	glDisable(GL_TEXTURE_2D);
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
	//glRotatef(axisRotation, 1, 0, 0);
	if (neptune == NULL && neptuneTexture == NULL) {//check if the textures are loaded and reuse them
		neptune = gluNewQuadric();
		neptuneTexture = LoadTexture("Textures/Neptune.bmp");
		gluQuadricDrawStyle(neptune, GLU_FILL);
		gluQuadricOrientation(neptune, GLU_OUTSIDE);
		gluQuadricTexture(neptune, GL_TRUE);
		gluQuadricNormals(neptune, GLU_SMOOTH);
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, neptuneTexture);
	gluSphere(neptune, 3.86, 20, 20);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glutSwapBuffers();
}
