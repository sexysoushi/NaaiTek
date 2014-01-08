#define _USE_MATH_DEFINES
#include <SWI-cpp.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <stdlib.h>    
#include <GL\glut.h>
//#include <SWI-cpp.h>
#include <iostream>


#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

using namespace std;

/*struct with game usefull data*/
typedef struct
{
	char wrongChar[9];
	char writeChar[25];
	bool endGame;
	bool userWin;
	int numErrors;
	string categories[20];
}Game;

/*global variables*/
int WindowWidth = 800;
int WindowHeight = 600;
const float DEG2RAD = 314159 / 180;
int GLUTWindowHandle = 0;
Game game;

/*instructions to hide console when the project are executing*/
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

/*initial declaration of some importante functions*/
void drawScene();
void display();
void resizeWindow(int x, int y);
void mouse(int btn, int mouseState, int x, int y);
void keyboard(int key, int x, int y);
void drawCircle(float centerX, float centerY, float radius, int num, GLfloat lineWidth);
void drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat lineWidth);
void drawChar(int x, int y, char c);
void initGameData();
void drawErrorChar();
void drawWord(string word);
void drawHangman();

/*function to init game data*/

void initGameData()
{
	for (int i = 0; i < 9; i++)
	{
		game.wrongChar[i] = NULL;
	}
	for (int i = 0; i < 25; i++)
	{
		game.writeChar[i] = NULL;
	}
	game.endGame = false;
	game.userWin = false;
	game.numErrors = 0;
	for (int i = 0; i < 20; i++)
	{
		game.categories[i]="";
	}
}

/*function when the window is resixed*/
void handleResize(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	gluPerspective(45.0, (double)x / (double)y, 1.0, 1.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawScene();
	glFlush();
}
/*function to initialize OpenGL*/
void myInit()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glViewport(0, 0, WindowWidth, WindowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)WindowWidth, (GLdouble)WindowHeight, 0.0);
}

/*function to draw circles with center (x,y) and radius (radius)*/
void drawCircle(float centerX, float centerY, float radius, int num, GLfloat lineWidth)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < num; i++)
	{
		float angle = 2.0f * 3.1415926f * float(i) / float(num);

		float x = radius * cosf(angle);
		float y = radius * sinf(angle);

		glVertex2f(x + centerX, y + centerY);
	}
	glEnd();
}
/*function to draw line starting on some point and finishing on other point*/
void drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat lineWidth)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINES);

	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

/*function to draw a character c into a specific position (x,y)*/
void drawChar(int x, int y, char c)
{
	glRasterPos2d(x, y);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

/*function to draw char that does not belong in the word*/
void drawErrorChar()
{
	int cont = 0;
	for (int i = 0; i < 8; i++)
	{
		if (game.wrongChar[i] != NULL)
		{
			cont++;
		}
	}
	for (int i = 0; i < cont; i++)
	{
		if (i < 4)
		{
			if (i == 0)
			{
				drawChar(100, 100, game.wrongChar[i]);
			}
			else
			if (i<8)
				drawChar(100 + (50 * i), 100, game.wrongChar[i]);
		}
		else
		for (int j = 0; j < 5; j++){
			if (j<4)
			drawChar(100 + (50 * j), 130, game.wrongChar[i]);
		}
	}

}
/*function to draw char lines of a word*/
void drawWord(string word)
{
	int wordSize = word.length();
	for (int i = 0; i < wordSize; i++)
	{
		drawLine(20 + (i * 60), 550, 60 + (i * 60), 550, 3.0);
	}
}
/*function to draw hangman parts*/
void drawHangman()
{
	if (game.numErrors == 1)
	{
		drawLine(WindowWidth / 2.0 - 100, WindowHeight - 100, WindowWidth / 2.0 - 50, WindowHeight - 200, 4.0);
		drawLine(WindowWidth / 2.0 - 50, WindowHeight - 200, WindowWidth / 2.0, WindowHeight - 100, 4.0);
	}
	else
	if (game.numErrors == 2){

		drawLine(WindowWidth / 2.0 - 50, WindowHeight - 200, WindowWidth / 2.0 - 50, 100, 4.0);
	}
	else
	if (game.numErrors == 3){

		drawLine(WindowWidth / 2.0 - 50, 100, WindowWidth - 200, 100, 4.0);
		drawLine(WindowWidth - 200, 100, WindowWidth - 200, 150, 4.0);
	}
	else
	if (game.numErrors == 4){
		drawCircle(WindowWidth - 200, 180, 30, 1000, 4.0);
	}
	else
	if (game.numErrors == 5){
		drawLine(WindowWidth - 200, 210, WindowWidth - 200, 280, 4.0);
	}
	else
	if (game.numErrors == 6)
	{

		drawLine(WindowWidth - 200, 230, WindowWidth - 235, 260, 4.0);
	}
	else
	if (game.numErrors == 7){
		drawLine(WindowWidth - 200, 230, WindowWidth - 165, 260, 4.0);
	}
	else
	if (game.numErrors == 8){
		drawLine(WindowWidth - 200, 280, WindowWidth - 235, 320, 4.0);
	}
	else
	if (game.numErrors == 9)
	{
		drawLine(WindowWidth - 200, 280, WindowWidth - 165, 320, 4.0);
	}
	glFlush();

}
/*function to draw the main scene*/
void drawScene()
{
	glColor3b(1.0, 0.0, 0.0);
	drawHangman();

}

/*callback special key of keyobard*/
void keyBoard(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_F1:
		glutPostRedisplay();
		initGameData();
		break;
	case GLUT_KEY_F10:
		game.numErrors++;
		drawHangman();
		break;
	}

}

void IAGetCategories()
{
	int i = 0;
	char *plargv[] = { "swipl.dll", "-s", "h-off.pl", NULL };
	PlEngine e(3, plargv);
	PlTermv av(1);
	PlQuery q("category", av);
	try{
		while (q.next_solution()){
			game.categories[i] = (string)av[0];
			i++;
		}
	}
	catch (PlException &ex){
		cout << (char *)ex << endl;
	}
	cin.get();
}
void IAGetPhrases(char *category)
{
	char *plargv[] = { "swipl.dll", "-s", "h-off.pl", NULL };
	PlEngine e(3, plargv);
	PlTermv av(2);
	av[0] = PlTerm(category);
	PlQuery q("getPhrase", av);
	try{
		while (q.next_solution()){
			cout << (string)av[1] << endl;
		}
	}
	catch (PlException &ex){
		cout << (char *)ex << endl;
	}
	cin.get();
}
void IACheckIfBelongs(char *c, char *word)
{
	char *plargv[] = { "swipl.dll", "-s", "h-off.pl", NULL };
	PlEngine e(3, plargv);
	PlTermv av(3);
	char *a= {"a"};
	char *b = { "arroz" };
	av[0] = PlTerm(a);
	av[1] = PlTerm(b);

	PlQuery q("getPhrase", av);
	try{
		while (q.next_solution()){
			cout << (string)av[2] << endl;
		}
	}
	catch (PlException &ex){
		cout << (char *)ex << endl;
	}
	cin.get();
}

int main(int argc, char**argv)
{
	IACheckIfBelongs("a", "arroz");
	initGameData();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow("HANGMAN");
	glutDisplayFunc(display);
	glutSpecialFunc(keyBoard);
	myInit();
	glutMainLoop();	
	return 0;
}









