// shadow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <iostream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "imageloader.h"

using namespace std;

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		exit(0);
	}
}

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
						  //as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureDoor; //The id of the texture
GLuint _textureGrass; //The id of the texture
GLuint _textureRoof; //The id of the texture
GLuint _textureBrick; //The id of the texture
GLuint _textureSky; //The id of the texture
GLuint _textureWindow; //The id of the texture
Image* image;
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	 image = loadBMP("sky2.bmp");
	_textureSky = loadTexture(image);

	 image = loadBMP("grass.bmp");
	 _textureGrass = loadTexture(image);

	 image = loadBMP("bricks.bmp");
	 _textureBrick = loadTexture(image);

	 image = loadBMP("lif7e06.bmp");
	 _textureRoof = loadTexture(image);

	 image = loadBMP("door.bmp");
	 _textureDoor = loadTexture(image);

	 image = loadBMP("window.bmp");
	 _textureWindow = loadTexture(image);
	
	delete image;
	
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}
float _angle = 0.0;
void mySpecialFunc(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		_angle += 1;
		if (_angle > 360) _angle = 0.0;
		break;
	case GLUT_KEY_LEFT:
		_angle -= 1;
		if (_angle > 360) _angle = 0.0;
		break;
	}
	glutPostRedisplay();
}



void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(0.0f, 1.0f, -6.0f);

	GLfloat ambientLight[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat directedLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat directedLightPos[] = { -16.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);


	
	glEnable(GL_TEXTURE_2D);
	
	// Grass
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureGrass);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -6);
	glRotatef(_angle, 0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 70.0, 1);  glVertex3f(-50, -1.5, 50);
	glTexCoord3f(0.0, 0.0, -1);  glVertex3f(-50, -1.5, -50);
	glTexCoord3f(70.0, 0.0, -1);  glVertex3f(50, -1.5, -50);
	glTexCoord3f(70.0, 70.0, 1);  glVertex3f(50, -1.5, 50);
	glEnd();
	glPopMatrix();


	// Sky
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureSky);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -10);
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 1.0, 0.1);  glVertex3f(-50, 10, 0);
	glTexCoord3f(1.0, 1.0, 0.1);  glVertex3f(50, 10, 0);
	glTexCoord3f(1.0, 0.0, 0.1);  glVertex3f(50, -10, 0);
	glTexCoord3f(0.0, 0.0, 0.1);  glVertex3f(-50, -10, 0);
	glEnd();
	glPopMatrix();


	// Front side
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -6);
	glRotatef(_angle, 0.0, 1.0, 0.0);
	glBegin(GL_QUADS);  // Wall
	glNormal3f(-16, 0, 0);
	glTexCoord3f(0.0, 2.0, 0.1);  glVertex3f(-2, 0, 1);
	glTexCoord3f(4.0, 2.0, 0.1);  glVertex3f(2, 0, 1);
	glTexCoord3f(4.0, 0.0, 0.1);  glVertex3f(2, -1.5, 1);
	glTexCoord3f(0.0, 0.0, 0.1);  glVertex3f(-2, -1.5, 1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _textureRoof);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);  // Roof
	//glNormal3f(-19.36,0,0);
	glTexCoord3f(0.0, 1.0, 0); glVertex3f(-2.2, 0.5, 0);
	glTexCoord3f(1.0, 1.0, 0); glVertex3f(2.2, 0.5, 0);
	glTexCoord3f(1.0, 0.0, 1.25); glVertex3f(2.2, -0.1, 1.25);
	glTexCoord3f(0.0, 0.0, 1.25); glVertex3f(-2.2, -0.1, 1.25);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _textureDoor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);  // Door
	glTexCoord3f(0.0, 1.0, 1.0001); glVertex3f(-0.3, -0.4, 1.0001);
	glTexCoord3f(1.0, 1.0, 1.0001); glVertex3f(0.3, -0.4, 1.0001);
	glTexCoord3f(1.0, 0.0, 1.0001); glVertex3f(0.3, -1.5, 1.0001);
	glTexCoord3f(0.0, 0.0, 1.0001); glVertex3f(-0.3, -1.5, 1.0001);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _textureWindow);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);  // Window Left
	glTexCoord3f(0.0, 1.0, 1.0001); glVertex3f(-1.5, -0.3, 1.0001);
	glTexCoord3f(1.0, 1.0, 1.0001); glVertex3f(-0.75, -0.3, 1.0001);
	glTexCoord3f(1.0, 0.0, 1.0001); glVertex3f(-0.75, -0.8, 1.0001);
	glTexCoord3f(0.0, 0.0, 1.0001); glVertex3f(-1.5, -0.8, 1.0001);
	glEnd();

	glBegin(GL_QUADS);  // Window Right
	glTexCoord3f(0.0, 1.0, 1.0001); glVertex3f(1.5, -0.3, 1.0001);
	glTexCoord3f(1.0, 1.0, 1.0001); glVertex3f(0.75, -0.3, 1.0001);
	glTexCoord3f(1.0, 0.0, 1.0001); glVertex3f(0.75, -0.8, 1.0001);
	glTexCoord3f(0.0, 0.0, 1.0001); glVertex3f(1.5, -0.8, 1.0001);
	glEnd();
	glPopMatrix();

	// Back side
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -6);
	glRotatef(_angle, 0.0, 1.0, 0.0);
	glBegin(GL_QUADS);  // Wall
	glTexCoord3f(0.0, 2.0, -1);  glVertex3f(-2, 0, -1);
	glTexCoord3f(4.0, 2.0, -1);  glVertex3f(2, 0, -1);
	glTexCoord3f(4.0, 0.0, -1);  glVertex3f(2, -1.5, -1);
	glTexCoord3f(0.0, 0.0, -1);  glVertex3f(-2, -1.5, -1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _textureRoof);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);  // Roof
	//glNormal3f(-19.36, 0, 0);
	glTexCoord3f(0.0, 1.0, 0); glVertex3f(-2.2, 0.5, 0);
	glTexCoord3f(1.0, 1.0, 0); glVertex3f(2.2, 0.5, 0);
	glTexCoord3f(1.0, 0.0, -1.25); glVertex3f(2.2, -0.1, -1.25);
	glTexCoord3f(0.0, 0.0, -1.25); glVertex3f(-2.2, -0.1, -1.25);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _textureWindow);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);  // Window Left
	glTexCoord3f(0.0, 1.0, -1.0001); glVertex3f(-1.5, -0.3, -1.0001);
	glTexCoord3f(1.0, 1.0, -1.0001); glVertex3f(-0.75, -0.3, -1.0001);
	glTexCoord3f(1.0, 0.0, -1.0001); glVertex3f(-0.75, -0.8, -1.0001);
	glTexCoord3f(0.0, 0.0, -1.0001); glVertex3f(-1.5, -0.8, -1.0001);
	glEnd();

	glBegin(GL_QUADS);  // Window Right
	glTexCoord3f(0.0, 1.0, 1.0001); glVertex3f(1.5, -0.3, -1.0001);
	glTexCoord3f(1.0, 1.0, 1.0001); glVertex3f(0.75, -0.3, -1.0001);
	glTexCoord3f(1.0, 0.0, 1.0001); glVertex3f(0.75, -0.8, -1.0001);
	glTexCoord3f(0.0, 0.0, 1.0001); glVertex3f(1.5, -0.8, -1.0001);
	glEnd();
	glPopMatrix();

	// Right side
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -6);
	glRotatef(_angle, 0.0, 1.0, 0.0);
	glBegin(GL_QUADS);  // Wall
	glTexCoord3f(0.0, 2.0, 1); glVertex3f(2, 0, 1);
	glTexCoord3f(2.0, 2.0, -1); glVertex3f(2, 0, -1);
	glTexCoord3f(2.0, 0.0, -1); glVertex3f(2, -1.5, -1);
	glTexCoord3f(0.0, 0.0, 1); glVertex3f(2, -1.5, 1);
	glEnd();

	glBegin(GL_TRIANGLES);  // Wall Upper
	glTexCoord3f(0.0, 1.0, 0); glVertex3f(2, 0.5, 0);
	glTexCoord3f(1.0, 0.0, 1); glVertex3f(2, 0, 1);
	glTexCoord3f(-1.0, 0.0, -1); glVertex3f(2, 0, -1);
	glEnd();
	glPopMatrix();

	// Left side
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -6);
	glRotatef(_angle, 0.0, 1.0, 0.0);
	
	glBegin(GL_QUADS);  // Wall
	glTexCoord3f(0.0, 2.0, 1);    glVertex3f(-2, 0, 1);
	glTexCoord3f(2.0, 2.0, -1);    glVertex3f(-2, 0, -1);
	glTexCoord3f(2.0, 0.0, -1);    glVertex3f(-2, -1.5, -1);
	glTexCoord3f(0.0, 0.0, 1);    glVertex3f(-2, -1.5, 1);
	glEnd();

	glBegin(GL_TRIANGLES);  // Wall Upper
	glTexCoord3f(0.0, 1.0, 0);    glVertex3f(-2, 0.5, 0);
	glTexCoord3f(1.0, 0.0, 1);    glVertex3f(-2, 0, 1);
	glTexCoord3f(-1.0, 0.0, -1);    glVertex3f(-2, 0, -1);
	glEnd();
	glPopMatrix();

	
	glutSwapBuffers();

	glFlush();
	//Left
	glDisable(GL_TEXTURE_2D);
}

int main(int argc, char** argv) {
	

	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Textured House");
	initRendering();

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutSpecialFunc(mySpecialFunc);
	

	glutMainLoop();
	return 0;
}
