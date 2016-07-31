#ifdef _WIN32
#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include "glut.h"
#elif __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/Gl.h>
#include <GLUT/GLUT.h>
#endif

#include <iostream>

#include "Lab5.h"

float vertexSize = 3.0;


void myInit(int shadingChoice, int colorChoice)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

	if(shadingChoice == 0) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	}
	else if(shadingChoice == 1) {
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	}

	if(colorChoice == 1) {
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
	}


	glClearColor(0.0f, 0.0f, 0.0f,0.0f);  // background is white

	glMatrixMode(GL_PROJECTION); // set the view volume shape
	glLoadIdentity();
	glOrtho(-3.5*worldWidth/worldHeight, 3.5*worldWidth/worldHeight, -3.5, 3.5, 0.1, 100);
}


void drawAxes()
{
	glBegin(GL_LINES);
		//x
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0,0,0);
		glVertex3f(100,0,0);
		//y
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0,0,0);
		glVertex3f(0,100,0);
		//z
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0,0,0);
		glVertex3f(0,0,100);
	glEnd();
	glutPostRedisplay();
}

void drawSun()
{	// Sun
	glColor3f(1.0f, 0.5f, 0.0f);    // sun is orange
	//Rotate about axis
	glPushMatrix();
		glRotated(sun_rotation_angle, 0, 1, 0);
		glutSolidSphere(0.5, 20, 16);	// locate the sun at the origin
	glPopMatrix();
	glutPostRedisplay();
}

void drawEarthAndMoon()
{
	// Earth
	glPointSize(vertexSize);
	glBegin(GL_LINE_LOOP);
	for (GLfloat t = 0; t <= 1; t += 0.01)
	{
		GLfloat thetaX = 2 * 3.14 * t; //2*(pi)*t
		GLfloat thetaY = 2 * 3.14 * t; //2*(pi)*t

		x = center_x + (earth_orbit_width * cosf(thetaX));
		y = center_y + (earth_orbit_height * sinf(thetaY));

		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(y, 0, x);
	}
	glEnd();
	glPushMatrix();
		earth_orbit_around_sun += 0.01;
		glRotated(earth_orbit_around_sun, 0, 1, 0);
		glTranslated(0, 0, 2);
		glRotated(earth_rotation_angle, 0, 1, 0);
		glColor3f(0.0f, 1.0f, 0.0f); // earth is green
		glutSolidSphere(0.2, 20, 8);
	glPopMatrix();

	// Moon
	glColor3f(0.5f, 0.5f, 0.5f);
	glPushMatrix();
		moon_orbit_around_sun += 0.01;
		glRotated(moon_orbit_around_sun, 0, 1, 0);
		glTranslated(0,0,2);
		moon_orbit_around_earth += 0.1;
		glRotated(moon_orbit_around_earth, 0, 1, 0);
		glTranslated(0, 0, 0.3);
		glRotated(moon_rotation_angle, 0, 1, 0);
		glutSolidSphere(0.05, 10, 4);
	glPopMatrix();
	glutPostRedisplay();
}

void drawMars()
{
	// Mars
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
		mars_orbit_around_sun += 0.005;
		glRotated(mars_orbit_around_sun, 0, 1, 0);
		glTranslated(0,0,3);
		glRotated(mars_rotation_angle, 0, 1, 0);
		glutSolidSphere(0.15, 20, 8);
	glPopMatrix();
	glutPostRedisplay();
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displaySolarSystem()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // clear the screen
	glMatrixMode(GL_MODELVIEW); // position and aim the camera
	glLoadIdentity();
	if (rotate)
	{
		gluLookAt(cosf(eyex), sinf(eyey), eyez, lookx, looky, lookz, 0.0, 1.0, 0.0);
	}else
	{
		gluLookAt(eyex, eyey, eyez, lookx, looky, lookz, 0.0, 1.0, 0.0);
	}
	

	//Planet, moon, and star rotation angles
	sun_rotation_angle += 0.05;
	earth_rotation_angle += 0.09;
	moon_rotation_angle += 0.1;
	mars_rotation_angle += 0.04;

	//Calculate the elliptical orbit of the earth around the sun
	//drawAxes();
	drawSun();
	drawEarthAndMoon();
	drawMars();

	glutSwapBuffers();
}

void cameraRotation(boolean rotate)
{
	if (rotate)
	{
		rotate = false;
	}else
	{
		rotate = true;	
	}
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch(key) {
		case 'v':
			view++;
			view %= 3;
			if(view == 0) {
				eyex=25;
				eyey=25;
				eyez=25;
			}
			else if(view == 1) {
				eyex=25;
				eyey=0;
				eyez=0;
			}
			else if(view == 2) {
				eyex=0;
				eyey=25;
				eyez=25;
			}
			break;
		case 'r':
			eyex *= cosf(eyex);
			eyey *= sinf(eyey);
			break;
		default:
			break;
	}

	glutPostRedisplay();

}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Inner Solar System"); // open the screen window


	int shadingChoice=0;
	int colorChoice = 0;
	std::cout << "Enter Shading Choice (0 for Diffuse, 1 for Specular):\n" ;
	std::cin >> shadingChoice;

	std::cout << "Enter Color Option (0 for No Color, 1 for Color):\n" ;
	std::cin >> colorChoice;

	myInit(shadingChoice, colorChoice);

	glutDisplayFunc(displaySolarSystem);
	glutKeyboardFunc(myKeyboard);

	glutMainLoop();

	return( 0 );
}
