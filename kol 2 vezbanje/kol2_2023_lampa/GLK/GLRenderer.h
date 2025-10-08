#pragma once

class CGLRenderer
{
public:
	CGLRenderer(void);
	virtual ~CGLRenderer(void);
		
	bool CreateGLContext(CDC* pDC);			// kreira OpenGL Rendering Context
	void PrepareScene(CDC* pDC);			// inicijalizuje scenu,
	void Reshape(CDC* pDC, int w, int h);	// kod koji treba da se izvrsi svaki put kada se promeni velicina prozora ili pogleda i
	void DrawScene(CDC* pDC);				// iscrtava scenu
	void DestroyScene(CDC* pDC);			// dealocira resurse alocirane u drugim funkcijama ove klase,
	UINT LoadTexture(char* fileName);
	void DrawAxes();

	void DrawEnvCube(double a);

	void DrawSingleCube(double a, UINT texture);

	void DrawCylinder(double r1, double r2, double h, int nSeg, int texMode, bool bIsOpen);

	void DrawLampBase();

	void DrawLampArm();

	void DrawLampHead();

	void DrawLamp();

	void UpdateCamera();

protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 

public:
	double dis_z = 0, angX = 0, angY = 0;
	UINT lamp, side, top, bot;

};
