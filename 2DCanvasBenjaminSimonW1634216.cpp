

#include "include\freeglut.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>

//Constants For Window
#define X_CENTRE 0.0      
#define Y_CENTRE 0.0
#define LENGTH   1.0  
#define WIDTH 20.0
#define HEIGTH 20.0

using namespace std;

//State
int STATE = 0, window;

//Animation
bool animation = false;

//Mouse
GLfloat mouseX;
GLfloat mouseY;

GLfloat point1x = 20, point1y = 20, point2x = 20, point2y = 20;

std::string last;

//Math Constants
GLdouble PI = 3.14159;	    
GLfloat angle = 2.0 * PI;

GLfloat red = 1.0, green = 1.0, blue = 1.0;

GLsizei wh = 400, ww = 400;

vector<GLfloat> points;

//Line Storage
class Line
{
private:
	//Constant Details
	GLfloat x1, y1, x2, y2;
	bool stopx = false, stopy = false;
	GLfloat r = 0.0;
	GLfloat g = 0.0;
	GLfloat b = 0.0;

public:
	//Create
	Line(GLfloat xx1, GLfloat yy1, GLfloat xx2, GLfloat yy2)
	{

		x1 = xx1;
		y1 = yy1;

		x2 = xx2;
		y2 = yy2;
	}
	Line()
	{

	}

	//Movement
	void Move(GLfloat xin, GLfloat yin) 
	{
		if ((x1 <= -7 || x2 <= -7) && xin < 0)
		{
			stopx = true;
		}
		else
		{
			stopx = false;
		}

		if ((y1 >= 7 || y2 >= 7) && yin > 0)
		{
			stopy = true;
		}
		else
		{
			stopy = false;
		}

		if (!stopx)
		{
			x1 += xin;
			x2 += xin;
		}

		if (!stopy)
		{
			y1 += yin;
			y2 += yin;
		}

	}

	//Draw
	void draw()
	{
		glColor3f(r, g, b);
		glLineWidth(0);

		//std::cout << "DRAW" << "\n";

		glBegin(GL_LINE_LOOP);

		glVertex2f(x1, y1); //LINE
		glVertex2f(x2, y2);

		glEnd();
	}
};

std::vector <Line> vectorLines(0);

//Point Storage
class Point
{
private:
	GLfloat centreX, centreY, length;
	bool polygon;
	GLfloat r = 0.0;
	GLfloat g = 0.0;
	GLfloat b = 0.0;

public:
	Point(GLfloat cx, GLfloat cy, bool poly, GLfloat l)
	{
		centreX = cx;
		centreY = cy;
		polygon = poly;
		length = l;
	}
	Point()
	{

	}

	void Move(GLfloat xin, GLfloat yin)
	{
		centreY += yin;
		centreX += xin;
	}

	void draw()
	{
		GLfloat x1, y1, x2, y2, x3, y3, x4, y4;
		GLfloat thickness = 2;

		if (centreX <= -7)
		{
			centreX = -6.9;
		}
		if (centreY >= 7)
		{
			centreY = 6.9;
		}

		x1 = centreX - length / 2;
		y1 = centreY + length / 2;

		x2 = centreX + length / 2;
		y2 = centreY + length / 2;

		x3 = centreX + length / 2;
		y3 = centreY - length / 2;

		x4 = centreX - length / 2;
		y4 = centreY - length / 2;

		glColor3f(r, g, b);
		glLineWidth(thickness);


		if (polygon)
		{
			glBegin(GL_POLYGON);
		}
		else
		{
			glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_LINE_LOOP);
		}

		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
		glVertex2f(x4, y4);

		glEnd();
	}
};

std::vector <Point> vectorPoints(0);

//Circle Storage
class Circle
{
private:

	bool polygon, ran = false;
	GLfloat rad;
	GLfloat r = 1.0;
	GLfloat g = 0.0;
	GLfloat b = 0.0;

	//Random Speed For Animation
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = 0.5 - 0.01;
	float ra = random * diff;

	float random2 = ((float)rand()) / (float)RAND_MAX;
	float diff2 = 0.00001 - 0.0000001;
	float ra2 = random * diff;

public:

	GLfloat centreX, centreY, spd = 0.0001;

	Circle(GLfloat cx, GLfloat cy, bool poly)
	{
		centreX = cx;
		centreY = cy;
		polygon = poly;
	}
	Circle(GLfloat cx, GLfloat cy, bool poly, bool random)
	{
		
		centreX = cx;
		centreY = cy;
		polygon = poly;
		ran = random;
	}
	Circle()
	{

	}

	void Move(GLfloat xin, GLfloat yin)
	{
		centreX += xin;
		centreY += yin;
	}

	//Animation Different Speed And Shapes
	void animate1()
	{
		spd = 0.1 + ra2;
		centreY += ((((spd) / 2) / 2) / 2) / 2; 
	}

	void draw()
	{

		if (centreX <= -7)
		{
			centreX = -6.9;
		}
		if (centreY >= 7)
		{
			centreY = 6.9;
		}

		if (ran == false)
		{
			rad = 1;
		}
		else
		{
			rad = 0.5 + ra;
		}

		GLfloat thickness = 2;

		if (!rand)
		{
			if (centreX <= -7)
			{
				centreX = -6.9;
			}
			if (centreY >= 7)
			{
				centreY = 6.9;
			}
		}
		glColor3f(1.0, 0.0, 0.0);
		glLineWidth(thickness);

		if (polygon)
		{
			glBegin(GL_POLYGON);
		}
		else
		{
			glBegin(GL_LINE_LOOP);
		}

		for (int i = 0; i < 360; i++)
		{
			GLfloat theta = 2.0f * 3.1415926f * GLfloat(i) / GLfloat(360);//get the current angle 
			GLfloat x = rad * cosf(theta);//calculate the x
			GLfloat y = rad * sinf(theta);//calculate the y 
			glVertex2f(x + centreX, y + centreY);//output vertex 
		}

		glEnd();
	}
};

std::vector <Circle> vectorCircles(0);

std::vector <Circle> vectorAnimation;

//Triangle Storage
class Triangle
{
private:
	GLfloat centreX, centreY;
	bool polygon;
	GLfloat r = 1.0;
	GLfloat g = 0.0;
	GLfloat b = 0.0;

public:
	Triangle(GLfloat cx, GLfloat cy, bool poly)
	{
		centreX = cx;
		centreY = cy;
		polygon = poly;
	}
	Triangle()
	{

	}

	void Move(GLfloat xin, GLfloat yin)
	{
		centreY += yin;
		centreX += xin;
	}

	void draw()
	{
		GLfloat x1, y1, x2, y2, x3, y3;
		GLfloat length = 2, thickness = 2;

		if (centreX <= -7)
		{
			centreX = -6.9;
		}
		if (centreY >= 7)
		{
			centreY = 6.9;
		}

		x1 = centreX + length / 2;
		y1 = centreY - length / 2;

		x2 = centreX + length / 2;
		y2 = centreY + length / 2;

		x3 = centreX - length / 2;
		y3 = centreY - length / 2;

		glColor3f(r, g, b);
		glLineWidth(thickness);


		if (polygon)
		{
			glBegin(GL_POLYGON);
		}
		else
		{
			glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_LINE_LOOP);
		}

		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);

		glEnd();
	}
};
std::vector <Triangle> vectorTriangles(0);

//Square Storage
class Square
{
private:
	GLfloat centreX, centreY, length;
	bool polygon;
	GLfloat r = 1.0;
	GLfloat g = 0.0;
	GLfloat b = 0.0;

public:
	Square(GLfloat cx, GLfloat cy, bool poly, GLfloat l)
	{
		centreX = cx;
		centreY = cy;
		polygon = poly;
		length = l;
	}
	Square()
	{

	}

	void Move(GLfloat xin, GLfloat yin)
	{
		centreY += yin;
		centreX += xin;
	}

	void draw()
	{
		GLfloat x1, y1, x2, y2, x3, y3, x4, y4;
		GLfloat thickness = 2;

		if (centreX <= -7)
		{
			centreX = -6.9;
		}
		if (centreY >= 7)
		{
			centreY = 6.9;
		}

		x1 = centreX - length / 2;
		y1 = centreY + length / 2;

		x2 = centreX + length / 2;
		y2 = centreY + length / 2;

		x3 = centreX + length / 2;
		y3 = centreY - length / 2;

		x4 = centreX - length / 2;
		y4 = centreY - length / 2;

		glColor3f(r, g, b);
		glLineWidth(thickness);


		if (polygon)
		{
			glBegin(GL_POLYGON);
		}
		else
		{
			glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_LINE_LOOP);
		}

		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
		glVertex2f(x4, y4);

		glEnd();
	}
};

std::vector <Square> vectorSquares(0);

//Initialise all functions
void drawSquare(GLfloat length, GLfloat x, GLfloat y);
void drawRect(GLfloat lengthX, GLfloat lengthY, GLfloat x, GLfloat y);
void drawTriangle(GLfloat length, GLfloat x, GLfloat y);
void drawCircle(GLfloat rad, GLfloat x, GLfloat y);
void drawPoint(GLfloat x, GLfloat y);
void  drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
void drawText(char *string, float x, float y, GLfloat r, GLfloat g, GLfloat b);
void drawGrid();
bool gridActive = true;

//Animation
void animate2()
{
	if (animation)
	{
		//Clears window
		vectorLines.clear();
		vectorPoints.clear();
		vectorTriangles.clear();
		vectorCircles.clear();
		vectorSquares.clear();

		while (vectorAnimation.size() < 200)
		{
			float random = ((float)rand()) / (float)RAND_MAX;
			float diff = 10 - -10;
			float ra = random * diff;
			float randX = -10 + ra; 

			//Creates Circle for animation
			Circle c = Circle(randX, -10, true, true);
			vectorAnimation.push_back(c);
		}

		//Calls up each circle
		for (int i = 0; i < vectorAnimation.size(); i++) 
		{
			vectorAnimation[i].animate1(); 
			vectorAnimation[i].draw(); 

			//Sets 9 as max amount and deletes circles
			if (vectorAnimation[i].centreY > 9) 
			{
				std::vector<Circle>::iterator it = vectorAnimation.begin();
				vectorAnimation.erase(it + i); 
			}
		}

	}
	else
	{
		vectorAnimation.clear();
	}
}

//Create Shapes
void Create()
{
	//Circle Create
	if (STATE == 1)
	{
		Circle c = Circle(mouseX, mouseY, true, false);
		last = "circle";
		vectorCircles.push_back(c);
	}

	//Square Create
	if (STATE == 2)
	{
		Square s = Square(mouseX, mouseY, true, 2);
		last = "square";
		vectorSquares.push_back(s);
	}

	//Square Outline Create
	if (STATE == 6) 
	{
		Square s = Square(mouseX, mouseY, false, 2);
		last = "square outline";
		vectorSquares.push_back(s);
	}

	//Point Create
	if (STATE == 4) 
	{
		Point p = Point(mouseX, mouseY, true, 0.1);
		last = "point";
		vectorPoints.push_back(p);
	}

	//Triangle Create
	if (STATE == 3)
	{
		Triangle t = Triangle(mouseX, mouseY, true);
		last = "triangle";
		vectorTriangles.push_back(t);
	}

	//Triangle Outline Create
	if (STATE == 7) 
	{
		Triangle t = Triangle(mouseX, mouseY, false);
		last = "triangle outline";
		vectorTriangles.push_back(t);
	}

	//Line
	if (STATE == 5) 
	{
		if (point1x == 20)
		{
			point1x = mouseX;
			point1y = mouseY;
		}
		else
		{
			point2x = mouseX;
			point2y = mouseY;

			Line l = Line(point1x, point1y, point2x, point2y); 
			last = "line";
			vectorLines.push_back(l); 

			point1x = 20;
			point1y = 20;

			point2x = 20;
			point2y = 20;
		}
	}
	else
	{
		point1x = 2;
		point1y = 2;

		point2x = 2;
		point2y = 2;
	}

}

//Draw New Shape
void DrawNewShape()
{
	for (int i = 0; i < vectorLines.size(); i++) //LINES
	{
		vectorLines[i].draw();
	}

	for (int i = 0; i < vectorSquares.size(); i++) //SQUARE
	{
		vectorSquares[i].draw();
	}

	for (int i = 0; i < vectorPoints.size(); i++) //POINTS
	{
		vectorPoints[i].draw();
	}

	for (int i = 0; i < vectorTriangles.size(); i++) //TRIANGLE
	{
		vectorTriangles[i].draw();
	}

	for (int i = 0; i < vectorCircles.size(); i++) //CIRCLE
	{
		vectorCircles[i].draw();
	}
}

//Key Input
void SpecialInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:

		if (last == "square")
		{
			vectorSquares.back().Move(0, 1);
		}

		else if (last == "circle")
		{
			vectorCircles.back().Move(0, 1);
		}

		else if (last == "triangle")
		{
			vectorTriangles.back().Move(0, 1);
		}

		else if (last == "square outline")
		{
			vectorSquares.back().Move(0, 1);
		}

		else if (last == "triangle outline")
		{
			vectorTriangles.back().Move(0, 1);
		}

		else if (last == "point")
		{
			vectorPoints.back().Move(0, 1);
		}

		else if (last == "line")
		{
			vectorLines.back().Move(0, 1);
		}
		break;

	case GLUT_KEY_DOWN:

		if (last == "square")
		{
			vectorSquares.back().Move(0, -1);
		}

		else if (last == "circle")
		{
			vectorCircles.back().Move(0, -1);
		}

		else if (last == "triangle")
		{
			vectorTriangles.back().Move(0, -1);
		}

		else if (last == "square outline")
		{
			vectorSquares.back().Move(0, -1);
		}

		else if (last == "triangle outline")
		{
			vectorTriangles.back().Move(0, -1);
		}

		else if (last == "point")
		{
			vectorPoints.back().Move(0, -1);
		}

		else if (last == "line")
		{
			vectorLines.back().Move(0, -1);
		}
		break;

	case GLUT_KEY_LEFT:

		if (last == "square")
		{
			vectorSquares.back().Move(-1, 0);
		}
		else if (last == "circle")
		{
			vectorCircles.back().Move(-1, 0);
		}

		else if (last == "triangle")
		{
			vectorTriangles.back().Move(-1, 0);
		}

		else if (last == "square outline")
		{
			vectorSquares.back().Move(-1, 0);
		}

		else if (last == "triangle outline")
		{
			vectorTriangles.back().Move(-1, 0);
		}

		else if (last == "point")
		{
			vectorPoints.back().Move(-1, 0);
		}

		else if (last == "line")
		{
			vectorLines.back().Move(-1, 0);
		}
		break;

	case GLUT_KEY_RIGHT:

		if (last == "square")
		{
			vectorSquares.back().Move(1, 0);
		}
		else if (last == "circle")
		{
			vectorCircles.back().Move(1, 0);
		}
		else if (last == "triangle")
		{
			vectorTriangles.back().Move(1, 0);
		}
		else if (last == "square outline")
		{
			vectorSquares.back().Move(1, 0);
		}

		else if (last == "triangle outline")
		{
			vectorTriangles.back().Move(1, 0);
		}

		else if (last == "point")
		{
			vectorPoints.back().Move(1, 0);
		}

		else if (last == "line")
		{
			vectorLines.back().Move(1, 0);
		}
		break;
	}
	glutPostRedisplay();
}


//Delete Drawn Shape from canvas
void DeleteShape(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's': vectorSquares.clear(); break;
	case 'c': vectorCircles.clear(); break;
	case 't': vectorTriangles.clear();  break;
	case 'p': vectorPoints.clear(); break;
	case 'l': vectorLines.clear(); break;
	case 27:

		glutDestroyWindow(window);
		exit(0);
		break;

	case 32:
		vectorLines.clear();
		vectorPoints.clear();
		vectorTriangles.clear();
		vectorCircles.clear();
		vectorSquares.clear();
		break;
	}

	last = "";
	glutPostRedisplay(); //Refresh
}

//Click Top/Side Menu
bool boxClick(GLfloat length, GLfloat x, GLfloat y)
{
	GLfloat x1, y1, x2, y2, x3, y3, x4, y4;

	x1 = x - length / 2;
	y1 = y + length / 2;
	x2 = x + length / 2;
	y2 = y + length / 2;
	x3 = x + length / 2;
	y3 = y - length / 2;
	x4 = x - length / 2;
	y4 = y - length / 2;

	if (mouseX > x1 && mouseX < x2 && mouseY < y1 && mouseY > y3)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void stateChange()
{
	if (boxClick(2, -3, 9))
	{
		STATE = 1;
		animation = false;
		return;
	}

	if (boxClick(2, -5, 9))
	{
		STATE = 2;
		animation = false;
		return;
	}

	if (boxClick(2, -7, 9))
	{
		STATE = 3;
		animation = false;
		return;
	}

	if (boxClick(2, -9, 7))
	{
		STATE = 4;
		animation = false;
		return;
	}

	if (boxClick(2, -9, 5))
	{
		STATE = 5;
		animation = false;
		return;
	}

	if (boxClick(2, -9, 3))
	{
		STATE = 6;
		animation = false;
		return;
	}

	if (boxClick(2, -9,	1))
	{
		STATE = 7;
		animation = false;
		return;
	}

	if (boxClick(2, -10 + 1, 10 - 1))
	{
		STATE = 0;
		animation = false;
		return;
	}

	for (GLfloat i = 9; i < 21; i += 2)
	{
		if (boxClick(2, -10 + i, 10 - 1))
		{
			STATE = 0;
			cout << "000" << endl;
			return;
		}
	}

	for (GLfloat i = 11; i < 21; i += 2)
	{
		if (boxClick(2, -10 + 1, 10 - i))
		{
			STATE = 0;
			return;
		}
	}
	Create();
}

//Reshape Window
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);
}

//Display of Window
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 1.0);  
	
	if (gridActive == true) {

		drawGrid();
	}

	if (animation)
	{
		animate2();
	}
	else
	{
		vectorAnimation.clear();
	}

	glColor3f(0.0, 0.0, blue);        /* white drawing objects */

	//Rect
	//UpperMenu
	drawRect(2, 18, -9, -1);
	//SideMenu
	drawRect(18, 2, 1, 9);

	//Square
	glColor3f(0.0, 1.0, 1.0);
	//UpperMenuButt
	drawSquare(2, -7, 9);
	drawSquare(2, -5, 9);
	drawSquare(2, -3, 9);
	//SideMenuButt
	drawSquare(2, -9, 7);
	drawSquare(2, -9, 5);
	drawSquare(2, -9, 3);
	drawSquare(2, -9, 1);

	//Outline
	glColor3f(0.0, 0.0, 0.0);
	//SideMenu
	drawLine(-10, 8, -8, 8);
	drawLine(-8, 8, -8, -10);
	drawLine(-10, 0, -8, 0);
	drawLine(-10, 2, -8, 2);
	drawLine(-10, 4, -8, 4);
	drawLine(-10, 6, -8, 6);
	//UpMenu
	drawLine(-8, 10, -8, 8);
	drawLine(-8, 8, 10, 8);
	drawLine(-6, 8, -6, 10);
	drawLine(-4, 8, -4, 10);
	drawLine(-2, 8, -2, 10);



	//InnerButtonStyle
	glColor3f(1.0, 0.0, 0.0);
	//UpperButtons
	drawTriangle(1, -7, 9);
	drawSquare(1, -5, 9);
	drawCircle(0.5, -3, 9);
	//SideButtons
	glColor3f(0.0, 0.0, 0.0);
	drawPoint(-9, 7);
	drawLine(-9.5, 4.5, -8.5, 5.5);
	//SquareLine
	drawLine(-9.5, 2.5, -9.5, 3.5);
	drawLine(-9.5, 3.5, -8.5, 3.5);
	drawLine(-8.5, 3.5, -8.5, 2.5);
	drawLine(-8.5, 2.5, -9.5, 2.5);
	//TriangleLine
	drawLine(-9.5, 0.5, -8.5, 0.5);
	drawLine(-8.5, 0.5, -8.5, 1.5);
	drawLine(-8.5, 1.5, -9.5, 0.5);

	if (STATE == 1) 
	{
		glColor3f(0.0, 0.5, 0.5);
		drawSquare(2, -3, 9);
		glColor3f(1.0, 0.0, 0.0);
		drawCircle(0.5, -3, 9);
	}

	if (STATE == 2)
	{
		glColor3f(0.0, 0.5, 0.5);
		drawSquare(2, -5, 9);
		glColor3f(1.0, 0.0, 0.0);
		drawSquare(1, -5, 9);
	}

	if (STATE == 3) 
	{
		glColor3f(0.0, 0.5, 0.5);
		drawSquare(2, -7, 9);
		glColor3f(1.0, 0.0, 0.0);
		drawTriangle(1, -7, 9);
	}

	if (STATE == 4)
	{
		glColor3f(0.0, 0.5, 0.5);
		drawSquare(2, -9, 7);
		glColor3f(0.0, 0.0, 0.0);
		drawPoint(-9, 7);
	}

	if (STATE == 5)
	{
		glColor3f(0.0, 0.5, 0.5);
		drawSquare(2, -9, 5);
		glColor3f(0.0, 0.0, 0.0);
		drawLine(-9.5, 4.5, -8.5, 5.5);
	}

	if (STATE == 6)
	{
		glColor3f(0.0, 0.5, 0.5);
		drawSquare(2, -9, 3);
		glColor3f(0.0, 0.0, 0.0);
		drawLine(-9.5, 2.5, -9.5, 3.5);
		drawLine(-9.5, 3.5, -8.5, 3.5);
		drawLine(-8.5, 3.5, -8.5, 2.5);
		drawLine(-8.5, 2.5, -9.5, 2.5);
	}

	if (STATE == 7)
	{
		glColor3f(0.0, 0.5, 0.5);
		drawSquare(2, -9, 1);
		glColor3f(0.0, 0.0, 0.0);
		drawLine(-9.5, 0.5, -8.5, 0.5);
		drawLine(-8.5, 0.5, -8.5, 1.5);
		drawLine(-8.5, 1.5, -9.5, 0.5);
	}

	DrawNewShape(); //Draw shapes

	drawText("2D Drawing Canvas", -3, -9, 0.0, 0.0, 0.0);

	if (animation)
		glutPostRedisplay();

	glFlush();     
}

//Draws Grid in RightClick Menu
void drawGrid()
{
	GLfloat x1, y1, x2, y2, x3, y3, x4, y4;
	GLfloat x, y, lengthOfCube;
	int height = 1, length = 1;

	x = -7;
	y = 7;
	lengthOfCube = 2;

	for (height; height <= 9; height++) {
		for (length; length <= 9; length++) {

			x1 = x - lengthOfCube / 2;
			y1 = y + lengthOfCube / 2;
			x2 = x + lengthOfCube / 2;
			y2 = y + lengthOfCube / 2;
			x3 = x + lengthOfCube / 2;
			y3 = y - lengthOfCube / 2;
			x4 = x - lengthOfCube / 2;
			y4 = y - lengthOfCube / 2;

			glColor3f(0.8, 0.8, 0.8);
			glLineWidth(0.01f);

			glBegin(GL_LINE_LOOP);
			glVertex2f(x1, y1);
			glVertex2f(x2, y2);
			glVertex2f(x3, y3);
			glVertex2f(x4, y4);
			glEnd();

			x = x + 2;

		}
		length = 1;
		x = -7;
		y = y - 2;
	}
}

//Draws a square using polygons
void drawSquare(GLfloat length, GLfloat x, GLfloat y)
{

	GLfloat x1, y1, x2, y2, x3, y3, x4, y4;

	x1 = x - length / 2;
	y1 = y + length / 2;
	x2 = x + length / 2;
	y2 = y + length / 2;
	x3 = x + length / 2;
	y3 = y - length / 2;
	x4 = x - length / 2;
	y4 = y - length / 2;

	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();

	glFlush();
}


//Draws a Rectangle
void drawRect(GLfloat lengthX, GLfloat lengthY, GLfloat x, GLfloat y)
{
	//x1,y1 is the top left-hand corner coordinate
	GLfloat x1, y1, x2, y2, x3, y3, x4, y4;

	//This example is for a rectangle 
	x1 = x - lengthX / 2;
	y1 = y + lengthY / 2;
	x2 = x + lengthX / 2;
	y2 = y + lengthY / 2;
	x3 = x + lengthX / 2;
	y3 = y - lengthY / 2;
	x4 = x - lengthX / 2;
	y4 = y - lengthY / 2;

	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();

	glFlush();
}

//Draw Triangle
void drawTriangle(GLfloat length, GLfloat x, GLfloat y)
{
	//x1,y1 is the top left-hand corner coordinate
	GLfloat x1, y1, x2, y2, x3, y3;


	x1 = x + length / 2;
	y1 = y + length / 2;
	x2 = x + length / 2;
	y2 = y - length / 2;
	x3 = x - length / 2;
	y3 = y - length / 2;

	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glEnd();

	glFlush();
}

//Draws a circle using line
void drawCircle(GLfloat length, GLfloat x, GLfloat y)
{
	GLfloat i = 0.0f;
	GLfloat PI = 3.14159;
	GLfloat x1, y1;

	glBegin(GL_TRIANGLE_FAN);

	glVertex2f(x, y); // Center
	for (i = 0.0f; i <= 360; i++)
	{
		x1 = ((length * cos(PI * i / 180)) + x);
		y1 = ((length * sin(PI * i / 180)) + y);
		glVertex2f(x1, y1);
	}
	glEnd();
	glFlush();
}

//Draw a Point
void drawPoint(GLfloat x, GLfloat y)
{
	glPointSize(4.0);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

//Draw Line
void  drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

//Text Output in Windows
void drawText(char *string, float x, float y, GLfloat r, GLfloat g, GLfloat b)
{
	glColor3f(r, g, b);

	char * c;
	glRasterPos2f(x, y);

	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

//Mouse Function
void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		stateChange();
		//cout << "state" << endl;
	}
	glutPostRedisplay();

}

//Mouse Location
void mousePos(int x, int y)
{
	mouseX = (float(x / (float)200 - 1.0)) * 10;
	mouseY = (float(-(y / (float)200 - 1.0))) * 10;
}

//Right-Click Menu
void myFirstMenu(GLint id) {

	if (id == 1)
	{

		gridActive = true;
		animation = false;

	}
	else if (id == 2)
	{

		gridActive = false;
		animation = false;
	}
	else if (id == 3)
	{
		gridActive = false;
		animation = true;
	}
	glutPostRedisplay();
}

//Graphics
void init(void)
{
	glClearColor(red, green, blue, 0.0);   /* window will be cleared to red */
}

int main(int argc, char** argv)
{
	/* window management code ... */
	/* initialises GLUT and processes any command line arguments */
	glutInit(&argc, argv);
	/* use single-buffered window and RGBA colour model */
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	/* window width = 400 pixels, height = 400 pixels */
	glutInitWindowSize(400, 400);
	/* window upper left corner at (100, 100) */
	glutInitWindowPosition(100, 100);
	/* creates an OpenGL window with command argument in its title bar */
	int window;
	window = glutCreateWindow("2D Canvas Benjamin Simon w1634216");
	init();

	//Menu
	glutCreateMenu(myFirstMenu);
	glutAddMenuEntry("Grid on", 1);
	glutAddMenuEntry("Grid off", 2);
	glutAddMenuEntry("Animation", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//Console
	cout << " Instructions to use 2D Drawing Programme" << endl;
	cout << "" << endl;
	cout << " Basic Input " << endl;
	cout << " L = Clear all Lines From Canvas " << endl;
	cout << " T = Clear all Triangles From Canvas " << endl;
	cout << " P = Clear all Points From Canvas " << endl;
	cout << " C = Clear all Circles From Canvas " << endl;
	cout << " S = Clear all Squares From Canvas " << endl;
	cout << " ESC = Quit The Application " << endl;
	cout << " SPACE = Clear The Canvas " << endl;
	cout << "" << endl;
	cout << " Select and Movement " << endl;
	cout << " Arrow Keys = Move the Shapes " << endl;
	cout << " LEFT-CLICK = Select Shapes From Shape Menu " << endl;
	cout << " LEFT-CLICK = Draw on Drawing Area " << endl;
	cout << " RIGHT-CLICK = Menu Pop-Up " << endl;
	cout << "" << endl;
	
	glutMouseFunc(myMouse);
	glutPassiveMotionFunc(mousePos);
	glutKeyboardFunc(DeleteShape);
	glutSpecialFunc(SpecialInput);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
