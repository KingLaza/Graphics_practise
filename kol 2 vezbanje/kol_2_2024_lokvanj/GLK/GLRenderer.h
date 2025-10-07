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

	void UpdateCamera();	//nije jos gotovo, treba sa osvetljenjem da se prilagodi kasnije
	void DrawAxes();
	UINT LoadTexture(char* fileName);
	void PolarToCartesian(double R, double phi, double theta, double& x, double& y, double& z);
	void DrawSphere(float R, int n, int m);
	void CalcRotAxis(double x1, double y1, double z1, double x2, double y2, double z2, double& x3, double& y3, double& z3);
	void DrawSphFlower(float R, int n, int m, float factor, unsigned char R1, unsigned char G1, unsigned char B1, unsigned char R2, unsigned char G2, unsigned char B2);
	void DrawFlower();
	//sranje oko osvetljenja treba takodje ovde..

protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 
	UINT env;

public:
	double distanceZ = 0, angX = 0, angY = 0;
	double rotA = 5, rotAspeed = 2;

};
