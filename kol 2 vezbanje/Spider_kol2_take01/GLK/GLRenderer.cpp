#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#include "DImage.h"
#include <corecrt_math_defines.h>
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
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_CULL_FACE);          // turn on face culling
	glCullFace(GL_BACK);             // cull (don’t draw) back faces
	glFrontFace(GL_CCW);

	spider = LoadTexture("res/spider.png");
	front = LoadTexture("res/front.jpg");
	left = LoadTexture("res/left.jpg");
	right = LoadTexture("res/right.jpg");
	back = LoadTexture("res/back.jpg");
	top = LoadTexture("res/top.jpg");
	bot = LoadTexture("res/bot.jpg");

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	//wglMakeCurrent(pDC->m_hDC, m_hrc);
	////---------------------------------
	//glClear(GL_COLOR_BUFFER_BIT);
	//glLoadIdentity();
	//gluLookAt(0, 49, 5, 0, 0, 0, 0, 1, 0);

	//glShadeModel(GL_SMOOTH);
	//glBegin(GL_TRIANGLES);
	//	glColor3f(1.0, 0.0, 0.0);
	//	glVertex3f(-1.0, -1.0, -5.0);
	//	glColor3f(0.0, 1.0, 0.0);
	//	glVertex3f(1.0, -1.0, -5.0);
	//	glColor3f(0.0, 0.0, 1.0);
	//	glVertex3f(1.0, 1.0, -5.0);
	//glEnd();
	//
	//
	//DrawEnvCube(100);

	////drawing spehere
	//glPushMatrix();
	//glTranslatef(0.0, 5.0, 0.0);
	////DrawSphere(10, 10, 0.25, 0.25, 0.25);
	////DrawCone(10, 20, 20, 0.75, 0.75, 0.25);
	////DrawLegSegment(5, 30, 10);
	////DrawSpiderBody();
	//DrawSpider();
	//glTranslatef(0.0, -5.0, 0.0);
	//glPopMatrix();

	//DrawAxes();
	//
	//glFlush();
	//SwapBuffers(pDC->m_hDC);
	////---------------------------------
	//wglMakeCurrent(NULL, NULL);

	wglMakeCurrent(pDC -> m_hDC, m_hrc);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0, 49, 5, 0, 0, 0, 0, 1, 0);

	UpdateCamera();
	
	DrawEnvCube(100);
	DrawSpider();
	DrawAxes();

	glFlush();
	SwapBuffers(pDC -> m_hDC);
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
	glDeleteTextures(1, &spider);
	glDeleteTextures(1, &left);
	glDeleteTextures(1, &right);
	glDeleteTextures(1, &top);
	glDeleteTextures(1, &bot);
	glDeleteTextures(1, &back);
	glDeleteTextures(1, &front);
	
	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

void CGLRenderer::DrawAxes()
{
	
	//---------------------------------

	
	//glLineWidth(2.0);
	glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(100.0, 0.0, 0.0);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 100.0, 0.0);

		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 100.0);
	glEnd();
	//---------------------------------
	
}

UINT CGLRenderer::LoadTexture(char* fileName) {
	UINT textID = 0;
	DImage img;

	if (img.Load(CString(fileName))) {

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glGenTextures(1, &textID);
		glBindTexture(GL_TEXTURE_2D, textID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(),
			GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());
	}
	return textID;
}

void CGLRenderer::DrawEnvCube(double a)
{
	glPushMatrix();
	glTranslatef(0.0, a / 2, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.0, -a / 2);
	DrawSquare(a, front);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, -a / 2);
	DrawSquare(a, back);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, -a / 2);
	DrawSquare(a, left);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, -a / 2);
	DrawSquare(a, right);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, -a);
	DrawSquare(a, top);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	
	DrawSquare(a, bot);
	glPopMatrix();

}

void CGLRenderer::DrawSphere(double r, int nSeg, double texU, double texV, double texR)
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, spider);
	glColor4f(0.5, 0.5, 0.5, 1);

	double alphaPlank = M_PI / nSeg;
	double betaPlank = (M_PI) / (nSeg);
	double alpha = -M_PI/2;
	double beta = 0.0f;
	double x1, x2, y1, y2, z1, z2, tu1, tu2, tv1, tv2 = 0.0f;

	for (int i = 0; i < nSeg; i++) {
		beta = 0;
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= 2 * nSeg; j++) {
			x1 = r * cos(alpha) * cos(beta);
			y1 = r * sin(alpha);
			z1 = r * cos(alpha) * sin(beta);

			x2 = r * cos(alpha + alphaPlank) * cos(beta);
			y2 = r * sin(alpha + alphaPlank);
			z2 = r * cos(alpha + alphaPlank) * sin(beta);

			tu1 = texU + (x1 / r) * texR;
			tv1 = texV + (z1 / r) * texR;

			tu2 = texU + (x2 / r) * texR;
			tv2 = texV + (z2 / r) * texR;

			glTexCoord2d(tu1, tv1);
			glVertex3f(x1, y1, z1);
			glTexCoord2d(tu2, tv2);
			glVertex3f(x2, y2, z2);


			beta += betaPlank;
		}
		glEnd();
		alpha += alphaPlank;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void CGLRenderer::DrawCone(double r, double h, int nSeg, double texU, double texV, double texR)
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, spider);
	glColor4f(0.5, 0.5, 0.5, 1);

	double alphaPlank = 2*M_PI / nSeg;
	double alpha = 2*M_PI;
	double x1, x2, z1, z2, tu1, tu2, tv1, tv2 = 0.0f;

	glBegin(GL_TRIANGLE_FAN);		//omotac
	glTexCoord2d(texU, texV);
	glVertex3f(0, h, 0);
	for (int i = 0; i <= nSeg; i++) {

		x1 = r * cos(alpha);
		z1 = r * sin(alpha);

		/*x2 = r * cos(alpha + alphaPlank);
		z2 = r * sin(alpha + alphaPlank);*/

		tu1 = texU + (x1 / r) * texR;
		tv1 = texV + (z1 / r) * texR;

		/*tu2 = texU + (x2 / r) * texR;
		tv2 = texV + (z2 / r) * texR;*/

		/*glTexCoord2d(texU, texV);
		glVertex3f(0, h, 0);*/
		glTexCoord2d(tu1, tv1);
		glVertex3f(x1, 0, z1);
		/*glTexCoord2d(tu2, tv2);
		glVertex3f(x2, 0, z2);*/
		
		alpha -= alphaPlank;
	}
	glEnd();

	/*alpha = 2*M_PI;
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2d(texU, texV);
	glVertex3f(0, 0, 0);
	for (int i = 0; i <= nSeg; i++) {
		x1 = r * cos(alpha);
		z1 = r * sin(alpha);
		tu1 = texU + (x1 / r) * texR;
		tv1 = texV + (z1 / r) * texR;

		glTexCoord2d(tu1, tv1);
		glVertex3f(x1, 0, z1);

		alpha += alphaPlank;
	}
	glEnd();*/


	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void CGLRenderer::DrawLegSegment(double r, double h, int nSeg)
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, spider);
	glColor4f(1, 1, 1, 1);
	
	DrawSphere(r, 2 * nSeg, 0.25, 0.25, 0.25);
	DrawCone(r, h, nSeg, 0.75, 0.75, 0.25);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void CGLRenderer::DrawLeg()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, spider);
	glColor4f(1, 1, 1, 1);

	DrawLegSegment(1, 10, 5);
	glTranslatef(0, 10, 0);
	glRotatef(85.0f, 1, 0, 0);
	DrawLegSegment(1, 15, 5);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void CGLRenderer::DrawSpiderBody()
{
	//3 sfere, r = 2,3,5, nseg = 10, glava = txt glava, ostale = 0.25, 
	//glava i grudni deo spljosteni 50% a dupe na 80%

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, spider);
	glColor4f(1, 1, 1, 1);

	glPushMatrix();
	glScalef(1, 0.5, 1);
	glTranslatef(-5.0, 0, 0);
	DrawSphere(2, 10, 0.75, 0.25, 0.25);
	glTranslatef(5.0, 0, 0);
	DrawSphere(3, 10, 0.25, 0.25, 0.25);
	glPopMatrix();

	glScalef(1, 0.80, 1);
	glTranslatef(8.0, 0, 0);
	DrawSphere(5, 10, 0.25, 0.25, 0.25);


	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
}

void CGLRenderer::DrawSpider()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, spider);
	glColor4f(1, 1, 1, 1);

	DrawSpiderBody();

	/*glPushMatrix();
	glRotatef(45.0f, 1.0, 0, 0);
	glRotatef(45.0f, 0, 0, 1);
	DrawLeg();
	glRotatef(-30.0f, 0, 0, 1);
	DrawLeg();
	glRotatef(-30.0f, 0, 0, 1);
	DrawLeg();
	glRotatef(-30.0f, 0, 0, 1);
	DrawLeg();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45.0f, 1.0, 0, 0);
	glRotatef(180.0f, 0, 1.0, 0);
	glRotatef(45.0f, 0, 0, 1);
	DrawLeg();
	glRotatef(-30.0f, 0, 0, 1);
	DrawLeg();
	glRotatef(-30.0f, 0, 0, 1);
	DrawLeg();
	glRotatef(-30.0f, 0, 0, 1);
	DrawLeg();
	glPopMatrix();*/

	

	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glRotatef(i * 30 - 45, 0.0, 1.0, 0.0);
		glRotatef(45, 1.0, 0.0, 0.0);
		DrawLeg();
		glPopMatrix();
	}

	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glRotatef(i * 30 - 45 + 180, 0.0, 1.0, 0.0);
		glRotatef(45, 1.0, 0.0, 0.0);
		DrawLeg();
		glPopMatrix();
	}

	// body anchor


	

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void CGLRenderer::DrawSquare(double side, UINT texture)
{
	glDisable(GL_LIGHTING);                 // optional: avoid lighting dimming your tex
	glEnable(GL_TEXTURE_2D);                // 1) turn on texturing
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(1.f, 1.f, 1.f);

	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f); glVertex3f(-side / 2, -side/2, 0);
	glTexCoord2f(1.f, 1.f); glVertex3f(side / 2, -side/2, 0);
	glTexCoord2f(1.f, 0.f); glVertex3f(side / 2, side/2, 0);
	glTexCoord2f(0.f, 0.f); glVertex3f(-side / 2, side/2, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void CGLRenderer::UpdateCamera()
{
	/*double toDeg = 57.29577951308;*/
	double toDeg = 1;
	glTranslatef(0, 0, -m_CamDist);
	glRotatef(m_CamAlpha * toDeg, 1, 0, 0);
	glRotatef(-m_CamBeta * toDeg, 0, 1, 0);
}
