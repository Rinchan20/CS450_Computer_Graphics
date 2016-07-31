#ifndef LAB_SOLAR_H
#define LAB_SOLAR_H


#define PI 3.1415


//Global Variables
const int screenWidth = 500;	   // width of screen window in pixels
const int screenHeight = 500;	   // height of screen window in pixels

const float worldWidth = 500.0;
const float worldHeight = 500.0;

// Initial values
GLdouble scale=1.0;

//Used for translation
GLdouble earth_x = 0.0, earth_y = 0.0, earth_z = 0.0;
GLdouble moon_x = 0.0, moon_y = 0.0, moon_z = 0.0;
GLdouble mars_x = 0.0, mars_y = 0.0, mars_z = 0.0;

//Used for rotation
GLdouble sun_rotation_angle = 0.0;
GLdouble earth_rotation_angle = 0.0;
GLdouble moon_rotation_angle = 0.0;
GLdouble mars_rotation_angle = 0.0;

//To be used as the intermediate 't' value used to compute points in earlier assignments
GLdouble earth_orbit = 0.0;
GLdouble moon_orbit_around_sun = 0.0;
GLdouble mars_orbit = 0.0;

GLdouble earth_orbit_around_sun = 0.0;
GLdouble mars_orbit_around_sun = 0.0;
GLdouble moon_orbit_around_earth = 0.0;

GLdouble x;
GLdouble y;

GLdouble center_x = 0;
GLdouble center_y = 0;

GLdouble earth_orbit_width = 2;
GLdouble earth_orbit_height = 2;

// global values for camera
GLdouble eyex=25.0, eyey=25.0, eyez=25.0;
GLdouble lookx=0.0, looky=0.0, lookz=0.0;

int view=0;

// global values for shading
GLfloat ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat shininess[] = {50.0f};

GLfloat position[] = {2.0f, 6.0f, 3.0f, 0.0f};
GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};

boolean rotate = false;
void cameraRotation(boolean rotate);

#endif