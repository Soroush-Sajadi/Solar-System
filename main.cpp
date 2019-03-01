#include<stdio.h>
#include<stdlib.h>
#include <GL/glut.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include "imageloader.h"
#include <iostream>

using namespace std;

//--------------------------------------------------------------------------------------------------------------------------------------------------
//Global values

#define PI 3.14159265
float angleMoon = 0.0, angleEarth = 0.0, angleAstroid = 0.0,
angleMars = 0.0, angleMercury = 0.0, angleVenus = 0.0, angleJupiter = 0.0,
angleSaturn = 0.0, angleUranus = 30.0, angleNeptune = 60.0;

float width = 600.0;
float height = 480.0;
float angle = 0.0;
float deltaAngle = 0.0f;
int xOrigin = -1;
float xl = 0.0199987f, zl = -0.9998f;
float x = 0.00299985f, z = 1.99994f;
float y = 0.6, yl = -0.99;

GLfloat  yRotated;
GLfloat  xRotated;

GLfloat sx = 0.2, sy = 0.2, sz = 0.2;
GLfloat black[] = { 0.0f,0.0f,0.0f,1.0f };
GLfloat yellow[] = { 0.7f,0.2f,0.0f,1.0f };
GLfloat qAmb[] = { 0.1,0.1,0.1,1.0 };
GLfloat qDif[] = { 1.0,1.0,1.0,1.0 }; 
GLfloat qSpec[] = { .50,.50,.50,.10 };
GLfloat qPos[] = { 0.0,0.0,0.0,0.5 };
GLfloat sc[8] = { 0.295 , 0.40,0.50, 0.60,0.80,1.0,1.05,1.13 };
double ang = 2 * PI / 300;
double angular = 2 * PI / 50;

GLuint EarthTexture;	GLUquadric *quad_er;
GLuint SunTexture;		GLUquadric *quad_sun;
GLuint MoonTexture;		GLUquadric *quad_moon;
GLuint MarsTexture;		GLUquadric *quad_mar;
GLuint MercuryTexture;  GLUquadric *quad_mer;
GLuint VenusTexture;	GLUquadric *quad_ven;
GLuint JupiterTexture;	GLUquadric *quad_jup;
GLuint SaturnTexture;	GLUquadric *quad_sat;
GLuint UranusTexture;   GLUquadric *quad_ura;
GLuint NeptuneTexture;	GLUquadric *quad_nep;
//---------------------------------------------------------------------------------------------------------------------------------------------
//functions declaration

void draw(void);
void initRenderingEarth();
void initRenderingSun();
void initRenderingJupiter();
void initRenderingMars();
void initRenderingMercury();
void initRenderingMoon();
void initRenderingUranus();
void initRenderingVenus();
void initRenderingNeptune();
void initRenderingSaturn();
void myinit();
void initLighting();
void background();
void idle();
void orbit();
void handleResize(int w, int h);
void update(int value);
void processSpecialKeys(int key, int xx, int yy);
void mouseMove(int x, int yy);


//-------------------------------------------------------------------------------------------------------------------------------------------------
GLuint loadTexture(Image *image)   //function to load the image for texturing
{
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;

}


void initRenderingEarth() {   //loading the image for Earth and returns a pointer to a new quadrics object 

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	quad_er = gluNewQuadric();
	Image* image = loadBMP("earth.bmp"); EarthTexture = loadTexture(image); delete image;
	
}

void initRenderingSun() {     //loading the image for Sun and returns a pointer to a new quadrics object

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	quad_sun = gluNewQuadric();


	Image *image = loadBMP("sun.bmp"); SunTexture = loadTexture(image); delete image;


}

void initRenderingVenus() {			//loading the image for Venus and returns a pointer to a new quadrics object

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	quad_ven = gluNewQuadric();


	Image *image = loadBMP("venus.bmp"); VenusTexture = loadTexture(image); delete image;

}

void initRenderingMercury() {		//loading the image for Mercury and returns a pointer to a new quadrics object

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	quad_mer = gluNewQuadric();


	Image *image = loadBMP("mercury.bmp"); MercuryTexture = loadTexture(image); delete image;

}

void initRenderingJupiter() {		//loading the image for Jupiter and returns a pointer to a new quadrics object

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	quad_jup = gluNewQuadric();


	Image *image = loadBMP("jupiter.bmp"); JupiterTexture = loadTexture(image); delete image;

}

void initRenderingUranus() {		//loading the image for Uranus and returns a pointer to a new quadrics object

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	quad_ura = gluNewQuadric();
	Image *image = loadBMP("uranus.bmp"); UranusTexture = loadTexture(image); delete image; 


}

void initRenderingNeptune() {		//loading the image for Neptune and returns a pointer to a new quadrics object

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	quad_nep = gluNewQuadric();


	Image *image = loadBMP("neptune.bmp"); NeptuneTexture = loadTexture(image); delete image;

}

void initRenderingSaturn() {		//loading the image for Saturn and returns a pointer to a new quadrics object

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	quad_sat = gluNewQuadric();


	Image *image = loadBMP("saturn.bmp"); SaturnTexture = loadTexture(image); delete image;

}

void initRenderingMoon() {			//loading the image for Moon and returns a pointer to a new quadrics object

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	quad_moon = gluNewQuadric();


	Image *image = loadBMP("pluto.bmp"); MoonTexture = loadTexture(image); delete image;

}

void initRenderingMars() {		//loading the image for Mars and returns a pointer to a new quadrics object

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	quad_mar = gluNewQuadric();


	Image *image = loadBMP("mars.bmp"); MarsTexture = loadTexture(image); delete image;

}

void idle(void)
{
	 yRotated += 0.1;
	 draw();
}



void initLighting()				//Creating the light source
{
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT7);

	glLightfv(GL_LIGHT7, GL_AMBIENT, qAmb);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, qDif);
	glLightfv(GL_LIGHT7, GL_SPECULAR, qSpec);
	
}

void myinit()
{
	glClearColor(0.0, 0.0, 0.0, 0.0); //backgroundcolor is green
									  //gluOrtho2D(0,699,0,699);
	glPointSize(1.0);
	glLineWidth(2.0);

}

void background()		
{
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.00, 0.00);
	glVertex3f(-01.00, 01.00, 1);
	glColor3f(.20, 0.0, 0.70);
	glVertex3f(01.00, 1.00, 1);
	glColor3f(0, 0.0, 0.0);
	glVertex3f(1.00, -1.00, 1);
	glColor3f(.70, .10, .20);
	glVertex3f(-1.00, -1.00, 1);
	glEnd();
}

void orbit()		//function for orbits
{
	glColor3f(0.5, 0.5, 0.5);


	int i = 0;
	for (i = 0; i<8; i++) {
		glPushMatrix();
		if (i == 5)
		{
			glRotatef(45, 1.0, 0.0, 0.0);
		}
		else
		{
			glRotatef(63, 1.0, 0.0, 0.0);
		}
		glScalef(sc[i], sc[i], sc[i]);
		glBegin(GL_POINTS);
		double ang1 = 0.0;
		int i = 0;
		for (i = 0; i<300; i++)
		{
			glVertex2d(cos(ang1), sin(ang1));
			ang1 += ang;
		}
		glEnd();
		glPopMatrix();
	}
}

void handleResize(int w, int h) {

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(45.0, w / h, 1.0, 200.0);

}

void draw(void)				//draw function
{
	
	glClearColor(0.0, 0.0, 0.0, 0.0);							// background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	background();

	glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, yl, z,				//setting up the camera
		x + xl, yl+y, z + zl,
		0.0f, 1.0f, 0.0f);
	orbit();													// recalling the orbit function , if you would like to not see the orbits just comment it!

	glPushMatrix();												// creating Sun with texture,size,postion and ...
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, SunTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glScalef(sx, sy, sz);										// Size of sún
	glLightfv(GL_LIGHT7, GL_POSITION, qPos);					// considering sun as source of light
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow);
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(quad_sun, 1);								// using sun texture
	gluSphere(quad_sun, 1, 50, 50);								// creating sun sphere
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
	glPopMatrix();												// closing the function
	glScalef(0.2, 0.2,0.2); 

	
	glPushMatrix();												// creating Mercury with texture,size,postion and ...
	glEnable(GL_TEXTURE_2D);					
	glBindTexture(GL_TEXTURE_2D, MercuryTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glRotatef(angleMercury, 0.0, 1.0, -0.5);					// Mercury rotation around the center.
	glTranslatef(1.5, 0.0, 0.0);								// Mercury psition
	glRotatef(yRotated, 0.0, 1.0, -0.5);						// Mercury rotation áround it's own axle
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.08, 0.08, 0.08);									// Mercury Size
	gluQuadricTexture(quad_mer, 1);								// using mercury texture
	gluSphere(quad_mer, 1, 50, 50);								// creating Mercury sphere
	glPopMatrix();												// closing the function

	glPushMatrix();												//creating Venus with texture,size,postion and ...
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, VenusTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glRotatef(angleVenus, 0.0, 1.0, -0.5);						// Venus rotation around the center			
	glTranslatef(2.0, 0.0, 0.0);								// Venus postion
	glColor3f(1.0, 1., 1.0);	
	glRotatef(yRotated, 0.0, 1.0, -0.5);						// Venus rotaion around it's own axle
	glScalef(0.1, 0.1, 0.1);									// Venus Size
	gluQuadricTexture(quad_ven, 1);								// using texture
	gluSphere(quad_ven, 1, 50, 50);								// creating Venus sphere
	glPopMatrix();												// closing the function

	glPushMatrix();												// creating Earth with texture,size,postion and ...
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, EarthTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glRotatef(angleEarth, 0.0, 1.0, -0.5);
	glTranslatef(2.5, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);  
	glRotatef(yRotated, 0.0, 1.0, -0.5);
	glScalef(0.23, 0.23, 0.23);  
	gluQuadricTexture(quad_er, 1);
	gluSphere(quad_er, 1, 50, 50);

	glPushMatrix();												// creating Moon with texture,size,postion and ...
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, MoonTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glRotatef(angleMoon, 0.0, 0.1, 0.05);
	glTranslatef(1.3, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.5, 0.5, 0.5);
	gluQuadricTexture(quad_moon, 1);
	gluSphere(quad_moon,0.5, 50, 50);
	glPopMatrix();//moon made
	glPopMatrix();//earth made

	


	glPushMatrix();												// creating Astroid belt with ,size,postion and ...
	glColor3f(3.30, 3.30, 3.30);
	glRotatef(63, 1.0, 0.0, 0.0);
	int j = 0, i = 0, div = 90; float siz = 2;
	float scl[4] = { 3.3,3.4,3.35,3.2 };
	for (j = 0; j<4; j++)
	{
		glPushMatrix(); siz -= 0.3;
		glPointSize(siz);
		glScalef(scl[j], scl[j], scl[j]);
		glBegin(GL_POINTS);
		double ang1 = 0.0 - angleAstroid, a = (2 * PI) / div;
		for (i = 0; i<div; i++)
		{
			glVertex2d(cos(ang1), sin(ang1));
			ang1 += a;
		}
		div += 10;
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();//astroid made

	glPushMatrix();												// creating Jupiter with texture,size,postion and ...
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, JupiterTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glRotatef(angleJupiter, 0.0, 1.0, -0.5);
	glTranslatef(-4.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glRotatef(yRotated, 0.5, 1.0, -0.5);
	glScalef(0.5, 0.5, 0.5);
	gluQuadricTexture(quad_jup, 1);
	gluSphere(quad_jup, 1, 50, 50);
	glPushMatrix();

	glRotatef(angleMoon, 1.0, -0.5, 0.0);
	glTranslatef(0.0, 0, 1.1);
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.1, 0.1, 0.1);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();//moon made
	glPopMatrix();

	glPushMatrix();												// creating Saturn with texture,size,postion and ...
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,SaturnTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glRotatef(angleSaturn, 0.0, 1.0, -1.0);
	glTranslatef(-5.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glRotatef(yRotated, 0.0, 1.0, -1.0);
	glScalef(0.4, 0.4, 0.4);
	gluQuadricTexture(quad_sat, 1);
	gluSphere(quad_sat, 1, 50, 50);

	glPushMatrix();												// creating Saturns ring with size,postion 
	glRotatef(45, 1.0, 0.0, 0.0);
	glPointSize(3);
	glColor3f(5.0, 3.0, 1.0);
	glScalef(1.2, 1.2, 1.2);
	glBegin(GL_POINTS);
	double ang1 = 0.0;
	i = 0;
	for (i = 0; i<50; i++)
	{
		glVertex2d(cos(ang1), sin(ang1));
		ang1 += angular;
	}
	glEnd();

	glPointSize(2);
	glPopMatrix();//ring made
	glPopMatrix();

	glPushMatrix();												// creating Uranus with texture,size,postion and ...
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, UranusTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glRotatef(angleUranus, 0.0, 1.0, -0.5);
	glTranslatef(5.2, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glRotatef(yRotated, 0.0, 1.0, -0.5);
	glScalef(0.23, 0.23, 0.23);
	gluQuadricTexture(quad_ura, 1);
	gluSphere(quad_ura, 1, 50, 50);
	glPopMatrix();

	glPushMatrix();												// creating Neptune with texture,size,postion and ...
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, NeptuneTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glRotatef(angleNeptune, 0.0, 1.0, -0.5);
	glTranslatef(-5.7, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glRotatef(yRotated, 0.0, 1.0, -0.5);
	glScalef(0.2, 0.2, 0.2);
	gluQuadricTexture(quad_nep, 1);
	gluSphere(quad_nep, 1, 50, 50);
	glPopMatrix();

	glPushMatrix();												// creating Mars with texture,size,postion and ...
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, MarsTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glRotatef(angleMars, 0.0, 1.0, -0.5);
	glTranslatef(-3.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glRotatef(yRotated, 0.0, 1.0, -0.5);
	glScalef(0.17, 0.17, 0.17);
	gluQuadricTexture(quad_mar, 1);
	gluSphere(quad_mar, 1, 50, 50);
	glPopMatrix();
	glPopMatrix();

	glFlush();
	glTranslatef(1.0f, 1.0f, -200000.0f);
	glutSwapBuffers();
}


void update(int value) {										// Updating angles of planets for rotation

	if ((angleMoon >= 0 && angleMoon<180))
	{
		sx -= 0.0003; sy -= 0.0003; sz -= 0.0003;
	}
	else { sx += 0.0003; sy += 0.0003; sz += 0.0003; }


	angleMoon += 2;
	if (angleMoon>360) {
		angleMoon -= 360;
		
	}
	angleEarth += 0.7;
	if (angleEarth>360) {
		angleEarth -= 360;
	}
	angleMercury += 2;
	if (angleMercury>360) {
		angleMercury -= 360;
	}
	angleVenus += 0.9;
	if (angleVenus>360) {
		angleVenus -= 360;
	}
	angleMars += 0.5;
	if (angleMars>360) {
		angleMars -= 360;
	}
	angleJupiter += 0.2;
	if (angleJupiter>360) {
		angleJupiter -= 360;
	}
	angleSaturn += 0.1;
	if (angleSaturn>360) {
		angleSaturn -= 360;
	}


	angleUranus += 0.05;
	if (angleUranus>360) {
		angleUranus -= 360;
	}


	angleNeptune += 0.02;
	if (angleNeptune>360) {
		angleNeptune -= 360;
	}


	angleAstroid += 0.002;
	if (angleAstroid>360) {
		angleAstroid -= 360;
	}


	glutPostRedisplay();
	glutTimerFunc(20, update, 0);
}
void processSpecialKeys(int key, int xx, int yy) {					 // controling the camera's angle by keybords

	float fraction = 0.1f;

	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.01f;
		xl = sin(angle);
		zl = -cos(angle);
		cout << xl << endl;
		cout << zl << endl;
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.01f;
		xl = sin(angle);
		zl = -cos(angle);
		cout << xl << endl;
		cout << zl << endl;
		break;
	case GLUT_KEY_UP:
		x += xl * fraction;
		z += zl * fraction;
		cout << x << endl;
		cout << z << endl;
		break;
	case GLUT_KEY_DOWN:
		x -= xl * fraction;
		z -= zl * fraction;
		cout << x << endl;
		cout << z << endl;
		break;
	case GLUT_KEY_PAGE_DOWN:
		y -= -yl*fraction;
		cout << y << endl;
		break;
	case GLUT_KEY_PAGE_UP:
		y += -yl * fraction;
		cout << y << endl;
		break;
	
	}
}

void mouseMove(int x, int yy) {										//controling camera's angle by mouse path

																	// this will only be true when the left button is down
	if (xOrigin >= 0) {

																	// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

																	// update camera's direction
		xl = sin(angle + deltaAngle);
		zl = -cos(angle + deltaAngle);
		y += yl * deltaAngle;
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char **argv)										// main function.
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(290, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("SOLAR SYSTEM 2018");
	initLighting();
	initRenderingEarth();
	initRenderingSun();
	initRenderingVenus();
	initRenderingMercury();
	initRenderingJupiter();
	initRenderingUranus();
	initRenderingNeptune();
	initRenderingSaturn();
	initRenderingMoon();
	initRenderingMars();
	glutIdleFunc(idle);
	glutTimerFunc(25, update, 0);
	glutReshapeFunc(handleResize);
	glutDisplayFunc(draw);
	glutSpecialFunc(processSpecialKeys);
	glutMotionFunc(mouseMove);

	//myinit();
	glutMainLoop();
	return 0;
}

