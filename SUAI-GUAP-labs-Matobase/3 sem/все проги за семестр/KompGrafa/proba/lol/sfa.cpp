#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include "GLee.h"
#include <glut.h>
#include "Maths.h"
#include "TIMER.h"
#include "scene.h"
#include "main.h"

TIMER timer;
VECTOR3D cameraPosition(0.0f, 4.5f, 4.0f);
VECTOR3D lightPosition(0.0f, 6.0f, -1.0f);
const int shadowMapSize = 512;
GLuint shadowMapTexture;
int windowWidth, windowHeight;
MATRIX4X4 lightProjectionMatrix, lightViewMatrix;
MATRIX4X4 cameraProjectionMatrix, cameraViewMatrix;

bool Init(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
	glGenTextures(1, &shadowMapTexture);
	glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapSize, shadowMapSize, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 32.0f);
	glPushMatrix();
	gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, cameraViewMatrix);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 2.0f, 8.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, lightProjectionMatrix);
	glLoadIdentity();
	gluLookAt(lightPosition.x, lightPosition.y, lightPosition.z,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, lightViewMatrix);
	glPopMatrix();
	return true;
}

void Display(void)
{
	glClearColor(0.80, 0.80, 0.80, 0.0);
	float angle = timer.GetTime() / -40;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(lightProjectionMatrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(lightViewMatrix);
	glViewport(0, 0, shadowMapSize, shadowMapSize);
	glCullFace(GL_FRONT);
	glColorMask(0, 0, 0, 0);
	DrawScene(angle);
	glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowMapSize, shadowMapSize);
	glCullFace(GL_BACK);
	glColorMask(1, 1, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(cameraProjectionMatrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(cameraViewMatrix);
	glViewport(0, 0, windowWidth, windowHeight);
	glLightfv(GL_LIGHT1, GL_POSITION, VECTOR4D(lightPosition));
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white * 0.2f);
	glLightfv(GL_LIGHT1, GL_SPECULAR, black);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	DrawScene(angle);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);///////////////////////////////////////////
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);
	static MATRIX4X4 biasMatrix(0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f);
	MATRIX4X4 textureMatrix = biasMatrix * lightProjectionMatrix * lightViewMatrix;
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_S, GL_EYE_PLANE, textureMatrix.GetRow(0));
	glEnable(GL_TEXTURE_GEN_S);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_T, GL_EYE_PLANE, textureMatrix.GetRow(1));
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_R, GL_EYE_PLANE, textureMatrix.GetRow(2));
	glEnable(GL_TEXTURE_GEN_R);
	glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_Q, GL_EYE_PLANE, textureMatrix.GetRow(3));
	glEnable(GL_TEXTURE_GEN_Q);
	glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);
	glAlphaFunc(GL_GEQUAL, 0.99f);
	glEnable(GL_ALPHA_TEST);
	DrawScene(angle);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);
	glDisable(GL_LIGHTING);
	glDisable(GL_ALPHA_TEST);
	glutSwapBuffers();
	glutPostRedisplay();
}

void Reshape(int w, int h)
{
	windowWidth = w, windowHeight = h;
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(45.0f, (float)windowWidth / windowHeight, 1.0f, 100.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, cameraProjectionMatrix);
	glPopMatrix();
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Лабораторная работа №5");
	if (!Init()) return 0;
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return 0;
}
Scene.cpp

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <glut.h>
#include "Maths/Maths.h"
#include "scene.h"

void DrawScene(float angle)
{
	static GLuint figures = 0, scene2 = 0;
	if (!figures)
	{
		figures = glGenLists(1);
		glNewList(figures, GL_COMPILE);
		{
			glPushMatrix();
			glColor3f(0.0f, 1.39f, 2.55f);
			glTranslatef(-0.55f, 1.4f, 0.45f);
			glutWireTeapot(0.3);
			glPopMatrix();
			glPushMatrix();
			glColor3f(2.55f, 0.0f, 0.0f);
			glTranslatef(0.45f, 2.0f, -0.45f);
			glutSolidCube(0.55);
			glPopMatrix();
		}
		glEndList();
	}
	if (!scene2)
	{
		scene2 = glGenLists(1);
		glNewList(scene2, GL_COMPILE);
		{
			glColor3f(0.76f, 0.88f, 0.00f);
			glPushMatrix();
			glTranslatef(0.0f, -0.5f, 0.45f);
			glutSolidSphere(1, 50, 50);
			glPopMatrix();
		}
		glEndList();
	}
	glCallList(scene2);
	glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glCallList(figures);
	glPopMatrix();
}

Timer.cpp

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include "TIMER.h"



double TIMER::GetTime()
{
	if (isPaused)
		return pauseTime - startTime;
	else
		return ((double)timeGetTime()) - startTime;
}

Main.h

#ifndef MAIN_H
#define MAIN_H
bool Init(void);
void Display(void);
void Reshape(int w, int h);
int main(int argc, char** argv);
#endif	//MAIN_H

Scene.h

#ifndef SCENE_H
#define SCENE_H
void DrawScene(float angle);
#endif	//SCENE_H

Timer.h

#ifndef TIMER_H
#define TIMER_H
class TIMER
{
public:
	TIMER() : isPaused(false)
	{		}
	~TIMER() {}
	double GetTime();
protected:
	double startTime;
	bool isPaused;
	double pauseTime;
};
#endif	//TIMER_H
