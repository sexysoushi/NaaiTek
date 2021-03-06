//
//  main.cpp
//  InGameMenu
//
//  Created by João Carreira on 13/01/14.
//  Copyright (c) 2014 João Carreira. All rights reserved.
//


#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "text3d.h"

using namespace std;


//************************************************************************
// global variables
//************************************************************************

// rotation angle
float g_angle = -30.0f;
float g_cameraAngle = 0.0f;

// scale for drawing text
float g_scale;

// text to be written on rotating cube
const char *stringVectorForRotatingCube[4] = { "NaaiTek", "NaaiTek", "NaaiTek", "NaaiTek" };

// text to be displayed in a "label"
const char *stringForLabel = "GAME PAUSED";

// windows
int mainWindow;

// "button" strongest path
float xMinStrongestPath = 308;
float xMaxStrongestPath = 514;
float yMinStrongestPath = 280;
float yMaxStrongestPath = 308;

// "button" shortest path
float xMinShortestPath = 319;
float xMaxShortestPath = 507;
float yMinShortestPath = 334;
float yMaxShortestPath = 361;

// "button" add friend
float xMinAddFriend = 344;
float xMaxAddFriend = 484;
float yMinAddFriend = 395;
float yMaxAddFriend = 413;

// "button" show friends in common
float xMinShowFriends = 242;
float xMaxShowFriends = 576;
float yMinShowFriends = 430;
float yMaxShowFriends = 474;

// "button" resume game
float xMinResume = 319;
float xMaxResume = 503;
float yMinResume = 500;
float yMaxResume = 524;
 

//************************************************************************
// forward declarations of OpenGL callback functions
//************************************************************************
void handleKeypress(unsigned char key, int x, int y);
void handleMouseButtonClicks(int button, int state, int x, int y);
void handleMouseMovement(int x, int y);
void initRendering();
void handleResize(int w, int h);
void drawScene();
void update(int value);
float computeScaleForSquareSize(const char* strs[], int numberOfStrings, float squareSize);
void cleanUp();

// drawing subrotines
void drawRotatingCubeAtScreenPosition(float x, float y, float z);
void drawLabelWithTextAtScreenPosition(float x, float y, float z);
void setupAmbientLight();
void setupPositionedLight();
void drawBackgroundAtScreenPosition(float x, float y, float z);
void drawSolidWithTextAtScreenPosition(float w, float h, float x, float y, float z);
void drawTextAtScreenPositionWithColor(char *str, float x, float y, float z, float color[]);


/**
 * main
 */
int main(int argc, char *argv[])
{
	// initializing GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
    
	// creating the main window
	mainWindow = glutCreateWindow("InGame Menu");
	
    initRendering();
    
    g_scale = computeScaleForSquareSize(stringVectorForRotatingCube, 3, 3.0);
    
	// setting handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
    glutMouseFunc(handleMouseButtonClicks);
    glutMotionFunc(handleMouseMovement);
    glutReshapeFunc(handleResize);
    
	// adding a timer
	glutTimerFunc(25, update, 0);
    
	glutMainLoop();
    
	return 0;
}


/**
 * called when a key is pressed
 * key is the keyboard key
 * x and y are mouse coordinates
 */
void handleKeypress(unsigned char key, int x, int y)
{
    // ONLY MOUSE CLICKS
}


/**
 * This funcion is invoked when the user presses a mouse button on the current window.
 * Each press and release action will generate an event.
 * int button will be one of GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON.
 * int state will be either GLUT_DOWN, or GLUT_UP indicating whether the event was a pressed, or released event.
 * int x, int y store the position of the mouse relative to the current window.
 */
void handleMouseButtonClicks(int button, int state, int x, int y)
{
    /*
    cout << "Button: " << button << endl;
    cout << "State:" << state << endl;
    cout << "X = " << x << endl;
    cout << "Y = " << y << endl;
    */
     
    // strongest path "button"
    if(x > xMinStrongestPath && x < xMaxStrongestPath)
    {
        if(y > yMinStrongestPath && y < yMaxStrongestPath)
        {
            // add code to get strongest path
            cout << "strongest path" << endl;
        }
    }
    
    // shortest path "button"
    if(x > xMinShortestPath  && x < xMaxShortestPath)
    {
        if(y > yMinShortestPath && y < yMaxShortestPath)
        {
            // add code to shortest path
            cout << "shortest path" << endl;
        }
    }
    
    // add friend "button"
    if(x > xMinAddFriend && x < xMaxAddFriend)
    {
        if(y > yMinAddFriend && y < yMaxAddFriend)
        {
            // add code to submit freind request
            cout << "add friend" << endl;
        }
    }
    
    // show friend in common "button"
    if(x > xMinShowFriends && x < xMaxShowFriends)
    {
        if(y > yMinShowFriends && y < yMaxShowFriends)
        {
            // add code to show friends in common
            cout << "show friends" << endl;
        }
    }
    
    // resume game button "button"
    if(x > xMinResume && x < xMaxResume)
    {
        cout << "inside x " << endl;
        if(y > yMinResume && y < yMaxResume)
        {
            cout << "inside y" << endl;
            cout << "resume game" << endl;
            exit(0);
        }
    }
}


/** This method is invoked when the mouse moves within the window while one or more mouse buttons are pressed.
 * int x, int y store the position of the mouse relative to the current window.
 */
void handleMouseMovement(int x, int y)
{
    // NO MOUSE MOVEMENT
}


/**
 * initializes 3D rendering
 */
void initRendering()
{
	// allows 3D drawing when objects are in front of other objects
	glEnable(GL_DEPTH_TEST);
    
	// enabling color
	glEnable(GL_COLOR_MATERIAL);
    
	// enable lightning
	glEnable(GL_LIGHTING);
    
	// enabling 2 light sources
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
    
	// normalizing normals
	glEnable(GL_NORMALIZE);
    
	// enabling smooth shading
	glShadeModel(GL_SMOOTH);
    
    t3dInit();
}


/**
 * called when a window is resized
 * (w e h is the window width and height)
 */
void handleResize(int w, int h)
{
	// converting coordinates to pixel values
	glViewport(0, 0, w, h);
    
	// switch to and setting camera perspective
	glMatrixMode(GL_PROJECTION);
    
	// setting the camera perspective
	// reseting the camera
	glLoadIdentity();
	// camera angle, width-to-heigth ration, near z clipping coordinate, far z clipping coordinate
	gluPerspective(45.0, (double) w / (double) h, 1.0, 200.0);
}


/**
 * draws a scene
 */
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
    
    // enabling lighting
    setupAmbientLight();
    setupPositionedLight();
    
    // drawing rotating cube with "NaaiTek Presents"
    drawRotatingCubeAtScreenPosition(0.0, 5.0, -15.0);
    
    // drawing "Graphs4Social" label
    drawLabelWithTextAtScreenPosition(0.0, 2.0, -10.0);
    
    // colors
    float whiteColor[3] = { 1.0f, 1.0f, 1.0f };
    float brickColor[3] = {0.58f, 0.2f, 0.2f};
    
    // text with game modes
    drawTextAtScreenPositionWithColor("Strongest Path", 0.0, 0.5, -15.0, brickColor);
    drawTextAtScreenPositionWithColor("Shortest Path", 0.0, -0.5, -15.0, brickColor);
    drawTextAtScreenPositionWithColor("Add Friend", 0.0, -1.5, -15.0, brickColor);
    drawTextAtScreenPositionWithColor("Show Friends in Common", 0.0, -2.5, -15.0, brickColor);
    drawTextAtScreenPositionWithColor("Resume Game", 0.0, -3.5, -15.0, whiteColor);
    
    glutSwapBuffers();
}


void setupAmbientLight()
{
    glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -8.0f);
	
    // ambient light
	GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
}


void setupPositionedLight()
{
    glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -8.0f);
    
    // positioned light
	GLfloat lightColor0[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightPos0[] = {0.5f, 0.5f, 1.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
}


void drawRotatingCubeAtScreenPosition(float x, float y, float z)
{
	glLoadIdentity();
	glTranslatef(x, y, z);
	
    // "inclining" the camera to see from above
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    
    // rotation animation
	glRotatef(-g_angle, 0.0f, 1.0f, 0.0f);
	
	//setting up the correct scale for the text
	glScalef(g_scale, g_scale, g_scale);
	
    // text color
    glColor3f(0.58f, 0.2f, 0.2f);
    
    // drawing 4 strings
	for(int i = 0; i < 4; i++)
    {
		glPushMatrix();
		glRotatef(90 * i, 0, 1, 0);
		glTranslatef(0, 0, 1.5f / g_scale);
		t3dDraw3D(stringVectorForRotatingCube[i], 0, 0, 0.2f);
		glPopMatrix();
	}
}


void drawLabelWithTextAtScreenPosition(float x, float y, float z)
{
    glLoadIdentity();
	glTranslatef(x, y, z);
    
    // "inclining" the camera to see from above
	glRotatef(20.0f, 0.0f, 0.0f, 0.0f);
    
    //setting up the correct scale for the text
	glScalef(g_scale, g_scale, g_scale);
	
    // text color
    glColor3f(0.0f, 0.0f, 0.0f);
    
    glPushMatrix();
    glTranslatef(0, 0, 1.5f / g_scale);
    t3dDraw3D(stringForLabel, 0, 0, 0.2f);
    glPopMatrix();
}


void drawSolidWithTextAtScreenPosition(float w, float h, float x, float y, float z)
{
    glLoadIdentity();
	glTranslatef(x, y, z);
    
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);
    
    // putting the box in the correct position
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    
    // drawing the faces
    glBegin(GL_QUADS);
    
    // Text face (normal color)
    glColor3f(0.7f, 0.0f, 0.0f);
    glNormal3f(0.0, 0.7f, 0.0f);
    glVertex3f(-w / 2, w / 2, -h / 2);
    glVertex3f(-w / 2, w / 2, h / 2);
    glVertex3f(w / 2, w / 2, h / 2);
    glVertex3f(w / 2, w / 2, -h / 2);
    
    // Left face (establishing a gradient)
    glNormal3f(-1.0, 0.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-w / 2, -w / 2, -h / 2);
    glVertex3f(-w / 2, -w / 2, h / 2);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-w / 2, w / 2, h / 2);
    glVertex3f(-w / 2, w / 2, -h / 2);
    
    glEnd();
}


void drawTextAtScreenPositionWithColor(char *str, float x, float y, float z, float color[])
{
    glLoadIdentity();
	glTranslatef(x, y, z);
    
    // "inclining" the camera to see from above
	glRotatef(20.0f, 1.5f, 1.0f, 0.0f);
    
    //setting up the correct scale for the text
	glScalef(g_scale * 0.9, g_scale * 0.9, g_scale * 0.9);
	
    // text color
    glColor3f(color[0], color[1], color[2]);
    
    glPushMatrix();
    glTranslatef(0, 0, 1.5f / g_scale);
    t3dDraw3D(str, 0, 0, 0.2f);
    glPopMatrix();
}


void update(int value)
{
	// rotates the shapes 1.5 degrees in every 25 miliseconds
	g_angle += 1.5f;
	if (g_angle > 360)
	{
		g_angle = 0;
	}
    
	// informing GLUT that the scene has changed
	glutPostRedisplay();
    
	// calling this method in every 25 ms
	glutTimerFunc(25, update, 0);
}


float computeScaleForSquareSize(const char* strs[], int numberOfStrings, float squareSize)
{
	float maxWidth = 0;
	for(int i = 0; i < squareSize; i++)
    {
		float width = t3dDrawWidth(strs[i]);
		if (width > maxWidth)
        {
			maxWidth = width;
		}
	}
	return (0.8 * squareSize) / maxWidth;
}


void cleanUp()
{
    t3dCleanup();
}