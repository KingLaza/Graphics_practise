#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#include "DImage.h"
#include "corecrt_math_defines.h";
//#pragma comment(lib, "GL\\glut32.lib")

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

CGLRenderer::CGLRenderer(void)
{
	distanceZ = 0;
	angX = 0;
	angY = 0;
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
	glFrontFace(GL_CCW);

	env = LoadTexture("./res/Env.jpg");

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	// basic white light
	GLfloat lightPos[] = { 0.3f, 1.0f, 0.8f, 0.0f };   // directional light
	GLfloat lightAmb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat lightDiff[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat lightSpec[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);


	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);*/
	gluLookAt(0, 49, 5, 0, 0, 0, 0, 1, 0);
	UpdateCamera();
	// …
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, env);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-5, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(5, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(5, 5, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-5, 5, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	//glTranslatef(0, 5, 0);
	//DrawSphere(5, 20, 20);
	//DrawSphFlower(5, 10, 20, 1, 100, 0, 0, 150, 0, 50);
	DrawFlower();
	//glTranslatef(0, -5, 0);

	DrawAxes();

	glFlush();
	SwapBuffers(pDC -> m_hDC);
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
	gluPerspective(50, (double)w / (double)h, 0.1, 2000);
	glMatrixMode(GL_MODELVIEW);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 
	wglMakeCurrent(NULL,NULL); 
	if(m_hrc) 
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

void CGLRenderer::UpdateCamera()
{	
	glTranslatef(0, -distanceZ, 0);
	glRotatef(angX, 1.0, 0, 0);
	glRotatef(-angY, 0, 1.0, 0);
	
}

void CGLRenderer::DrawAxes()
{
	glDisable(GL_TEXTURE_2D);
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
}

UINT CGLRenderer::LoadTexture(char* fileName)
{
	UINT texID;
	DImage img;
	img.Load(CString(fileName));
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(),
		GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());
	return texID;
}

void CGLRenderer::PolarToCartesian(double R, double phi, double theta, double& x, double& y, double& z)
{
	x = R * sin(theta) * cos(phi);
	y = R * sin(theta) * sin(phi);
	z = R * cos(theta);
}

void CGLRenderer::DrawSphere(float R, int n, int m)
{
	//R - poluprecnik, n - segmenti oko ekvatora, m - segmenti oko meridijana
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, env);
	double betaPlank = (2 * M_PI) / n;
	double alphaPlank = M_PI / m;
	double alpha = -M_PI/2;
	double beta = 0.0f;
	double x1 = 0, x2 = 0, y1 = 0, y2 = 0, z1 = 0, z2 = 0, u1 = 0, u2 = 0, v1 = 0, v2 = 0;
	double U = 0.5, V = 0.5, UVR = 0.5;

	for (int i = 0; i < m; i++) {
		beta = 0;
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= n; j++) {
			x1 = R * cos(alpha) * cos(beta);
			y1 = R * sin(alpha);
			z1 = R * cos(alpha) * sin(beta);

			x2 = R * cos(alpha + alphaPlank) * cos(beta);
			y2 = R * sin(alpha + alphaPlank);
			z2 = R * cos(alpha + alphaPlank) * sin(beta);

			u1 = U + (x1 / R) * UVR;
			v1 = V + (z1 / R) * UVR;

			u2 = U + (x2 / R) * UVR;
			v2 = V + (z2 / R) * UVR;

			glTexCoord2f(u1, v1);
			glVertex3f(x1, y1, z1);
			glTexCoord2f(u2, v2);
			glVertex3f(x2, y2, z2);

			beta += betaPlank;
		}
		glEnd();
		alpha += alphaPlank;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

}

void CGLRenderer::CalcRotAxis(double x1, double y1, double z1, double x2, double y2, double z2, double& x3, double& y3, double& z3)
{
	double dx = x2 - x1;
	double dy = y2 - y1;
	double dz = z2 - z1;

	// dužina vektora
	double L = sqrt(dx * dx + dy * dy + dz * dz);

	if (L == 0) { // ako su tačke iste, nema smera
		x3 = y3 = z3 = 0;
		return;
	}

	// normalizacija
	x3 = dx / L;
	y3 = dy / L;
	z3 = dz / L;
}

void CGLRenderer::DrawSphFlower(float R, int n, int m, float factor, unsigned char R1, unsigned char G1, unsigned char B1, unsigned char R2, unsigned char G2, unsigned char B2)
{

	glPushMatrix();
	glDisable(GL_TEXTURE_2D);

	// --- NEW: enable lighting and set base material ---
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);           // because we rotate/translate, maybe scale later
	glShadeModel(GL_SMOOTH);

	const GLfloat kdSouth[4] = { R1 / 255.f, G1 / 255.f, B1 / 255.f, 1.f };
	const GLfloat kdNorth[4] = { R2 / 255.f, G2 / 255.f, B2 / 255.f, 1.f };
	const GLfloat ka[4] = { 0.2f * kdSouth[0], 0.2f * kdSouth[1], 0.2f * kdSouth[2], 1.f }; // 20% south
	const GLfloat ksWhite[4] = { 1.f, 1.f, 1.f, 1.f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ksWhite);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 30.f);

	// (make sure a light is enabled somewhere in your init, e.g. GL_LIGHT0)

	double betaPlank = (2 * M_PI) / n;
	double alphaPlank = M_PI / m;
	double beta = 2 * M_PI;

	for (int i = 0; i < n; i++) {
		// hinge at first ring above south pole
		double alphaAxis = -M_PI / 2 + alphaPlank;

		// hinge points P1 (left) and P2 (right)
		double p1x = R * cos(alphaAxis) * cos(beta);
		double p1y = R * sin(alphaAxis);
		double p1z = R * cos(alphaAxis) * sin(beta);

		double p2x = R * cos(alphaAxis) * cos(beta - betaPlank);
		double p2y = R * sin(alphaAxis);
		double p2z = R * cos(alphaAxis) * sin(beta - betaPlank);

		// unit axis direction
		double ax = p2x - p1x, ay = p2y - p1y, az = p2z - p1z;
		double L = sqrt(ax * ax + ay * ay + az * az);
		if (L > 0) { ax /= L; ay /= L; az /= L; }
		else { ax = ay = az = 0; }

		glPushMatrix();
		{
			// move hinge to origin → rotate → move back
			glTranslated(p1x, p1y, p1z);
			glRotated(rotA * factor, ax, ay, az);
			glTranslated(-p1x, -p1y, -p1z);

			// draw petal as a vertical strip in theta
			double alpha = -M_PI / 2;

			glBegin(GL_QUAD_STRIP);
			for (int j = 0; j <= m; j++) {
				// --- NEW: per-ring diffuse color (south→north gradient) ---
				float t = (float)j / (float)m;   // 0 at south, 1 at north
				GLfloat kd[4] = {
					kdSouth[0] * (1.f - t) + kdNorth[0] * t,
					kdSouth[1] * (1.f - t) + kdNorth[1] * t,
					kdSouth[2] * (1.f - t) + kdNorth[2] * t,
					1.f
				};
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd);

				// left edge at φ = beta
				double lx = R * cos(alpha) * cos(beta);
				double ly = R * sin(alpha);
				double lz = R * cos(alpha) * sin(beta);

				// right edge at φ = beta - betaPlank
				double rx = R * cos(alpha) * cos(beta - betaPlank);
				double ry = R * sin(alpha);
				double rz = R * cos(alpha) * sin(beta - betaPlank);

				// --- NEW: per-vertex normals (sphere) ---
				glNormal3d(lx / R, ly / R, lz / R);
				glVertex3d(lx, ly, lz);

				glNormal3d(rx / R, ry / R, rz / R);
				glVertex3d(rx, ry, rz);

				alpha += alphaPlank;
			}
			glEnd();
		}
		glPopMatrix();

		beta -= betaPlank;
	}

	glPopMatrix();
}

void CGLRenderer::DrawFlower()
{
	glPushMatrix();
	
	//3 sfera, spoljasnja - r=2, f=1, 0,192,0  i 0,255,0
	//srednja r- 0.75*r, f=0.5, 0,0,255 i 255,0,0
	//unutrasnaj r-0.5*r, f= 0.25, 192,192,0 i 192,192,192
	//n=36, m = 18


	DrawSphFlower(2, 36, 18, 1, 0, 192, 0, 0, 255, 0);
	DrawSphFlower(0.75*2, 36, 18, 0.5, 0, 0, 255, 255, 0, 0);
	DrawSphFlower(0.5*2, 36, 18, 0.25, 192, 192, 0, 192, 192, 192);


	glPopMatrix();

}
