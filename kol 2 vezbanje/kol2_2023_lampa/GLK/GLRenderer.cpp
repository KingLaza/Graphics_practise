#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#include "DImage.h"
#include "corecrt_math_defines.h"
//#pragma comment(lib, "GL\\glut32.lib")

CGLRenderer::CGLRenderer(void)
{
}

CGLRenderer::~CGLRenderer(void)
{
}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd ;
   	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
   	pfd.nSize  = sizeof(PIXELFORMATDESCRIPTOR);
   	pfd.nVersion   = 1; 
   	pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;   
   	pfd.iPixelType = PFD_TYPE_RGBA; 
   	pfd.cColorBits = 32;
   	pfd.cDepthBits = 24; 
   	pfd.iLayerType = PFD_MAIN_PLANE;
	
	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);
	
	if (nPixelFormat == 0) return false; 

	BOOL bResult = SetPixelFormat (pDC->m_hDC, nPixelFormat, &pfd);
  	
	if (!bResult) return false; 

   	m_hrc = wglCreateContext(pDC->m_hDC); 

	if (!m_hrc) return false; 

	return true;	
}

void CGLRenderer::PrepareScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClearColor(1, 1, 1, 1);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);          // turn on face culling
	//glCullFace(GL_BACK);             // cull (don’t draw) back faces
	//glFrontFace(GL_CCW);	

	lamp = LoadTexture("./res/lamp.jpg");
	side = LoadTexture("./res/side.jpg");
	top = LoadTexture("./res/top.jpg");
	bot = LoadTexture("./res/bot.jpg");

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0, 75, 30, 0, 20, 0, 0, 1, 0);
	UpdateCamera();

	DrawEnvCube(100);
	//DrawCylinder(10, 10, 10, 10, 0, false);
	//DrawLampBase();
	//DrawLampArm();
	
	//DrawLampHead();
	DrawLamp();

	DrawAxes();



	glFlush();
	SwapBuffers(pDC->m_hDC);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Reshape(CDC *pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, (double)w / (double)h, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 
	glDeleteTextures(1, &lamp);
	glDeleteTextures(1, &top);
	glDeleteTextures(1, &bot);
	glDeleteTextures(1, &side);

	wglMakeCurrent(NULL,NULL); 
	if(m_hrc) 
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

UINT CGLRenderer::LoadTexture(char* fileName) {
	UINT textID = 0;
	DImage img;

	if (img.Load(CString(fileName))) {

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glGenTextures(1, &textID);
		glBindTexture(GL_TEXTURE_2D, textID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(),
			GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());
	}
	return textID;
}

void CGLRenderer::DrawAxes()
{
	glPushMatrix();

	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(50, 0, 0);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 50, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 50);
	glEnd();

	glPopMatrix();

}

void CGLRenderer::DrawEnvCube(double a) {

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glTranslatef(0, a / 2, 0);

	glPushMatrix();
	glTranslatef(0, 0, -a / 2);
	DrawSingleCube(a, side);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(0, 0, -a / 2);
	DrawSingleCube(a, side);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, -a / 2);
	DrawSingleCube(a, side);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(0, 0, -a / 2);
	DrawSingleCube(a, side);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, -a/2);
	DrawSingleCube(a, top);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, 0, -a / 2);
	DrawSingleCube(a, bot);
	glPopMatrix();


	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void CGLRenderer::DrawSingleCube(double a, UINT texture) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(-a / 2, -a/2, 0);
	glTexCoord2f(1, 1);
	glVertex3f(a / 2, -a / 2, 0);
	glTexCoord2f(1, 0);
	glVertex3f(a / 2, a/2, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-a / 2, a/2, 0);

	glEnd();


	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

}

void CGLRenderer::DrawCylinder(double r1, double r2, double h, int
	nSeg, int texMode, bool bIsOpen) {

	double nPlank = 2 * M_PI / nSeg;
	double angle = 0;
	double x = 0, z = 0, x2 = 0, z2 = 0;
	double u, v;
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lamp);
	
	if (!bIsOpen) {
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2d(0.5, 0.25);
		glVertex3f(0, h, 0);
		angle = 0;
		for (int i = 0; i <= nSeg; i++) {
			x = r1 * cos(angle);
			z = r1 * sin(angle);
			u = 0.5 + (x / r1) * 0.25;
			v = 0.25 + (z / r1) * 0.25;
			glTexCoord2d(u, v);
			glVertex3f(x, h, z);
			angle += nPlank;
		}
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2d(0.5, 0.25);
		glVertex3f(0, 0, 0);
		angle = 0;
		for (int i = 0; i <= nSeg; i++) {
			x = r2 * cos(angle);
			z = r2 * sin(angle);
			u = 0.5 + (x / r2) * 0.25;
			v = 0.25 + (z / r2) * 0.25;
			glTexCoord2d(u, v);
			glVertex3f(x, 0, z);
			angle += nPlank;
		}
		glEnd();
	}

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lamp);
	double U1 = 0, V1 = 0, U2 = 0, V2 = 0;
	if (texMode == 0) {
		U1 = 0;
		V1 = 0;
		U2 = 1;
		V2 = 0.5;
	}
	else {
		U1 = 0;
		V1 = 0.5;
		U2 = 1;
		V2 = 1;
	}


	
	glBegin(GL_QUAD_STRIP);
	angle = 0;
	for (int i = 0; i <= nSeg; i++) {
		x = r1 * cos(angle);
		z = r1 * sin(angle);
		x2 = r2 * cos(angle);
		z2 = r2 * sin(angle);
		u = U2 - angle / (2 * M_PI);
		glTexCoord2d(u, V1);
		glVertex3f(x, h, z);
		glTexCoord2d(u, V2);
		glVertex3f(x2, 0, z2);
		angle += nPlank;
	}
	glEnd();


}

void CGLRenderer::DrawLampBase() {
	DrawCylinder(7, 8, 2, 20, 0, false);
}

void CGLRenderer::DrawLampArm() {
	glPushMatrix();
	glRotatef(90, 1.0, 0, 0);
	glTranslatef(0, 0, -3);
	DrawCylinder(3, 3, 2, 20, 0, false);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 6, 0);
	DrawCylinder(1, 1, 15, 20, 0, false);
	glPopMatrix();
}

void CGLRenderer::DrawLampHead() {
	//r, 2,3 ili 6 / h - 1,2 ili 5 
	glPushMatrix();
	glRotatef(90, 1.0, 0, 0);
	glTranslatef(0, 0, -3);
	DrawCylinder(2, 2, 1, 20, 0, false);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 5, 0);
	glTranslated(-3, 0, 0);
	glRotatef(-90, 0, 0, 1);
	DrawCylinder(3, 2, 1, 20, 0, false);

	glTranslatef(0, 1, 0);
	DrawCylinder(3, 3, 5, 20, 0, false);

	glTranslatef(0, 5, 0);
	DrawCylinder(6, 3, 5, 20, 0, true);

	glPopMatrix();



}

void CGLRenderer::DrawLamp() {

	glPushMatrix();
	DrawLampBase();
	glRotatef(30, 0, 0, 1);
	DrawLampArm();

	glTranslatef(0, 20, 0);
	glRotatef(-60, 0, 0, 1);
	DrawLampArm();

	glTranslatef(0, 20, 0);
	DrawLampHead();

	glPopMatrix();

}

void CGLRenderer::UpdateCamera()
{
	glTranslatef(0, 0, -dis_z);
	glRotatef(angX, 1, 0, 0);
	glRotatef(angY, 0, 1, 0);

}

