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

	//new methods
	void DrawAxes();
	UINT LoadTexture(char* fileName);
	void DrawEnvCube(double a);
	void DrawSphere(double r, int nSeg, double texU,
		double texV, double texR);
	void DrawCone(double r, double h, int nSeg, double
		texU, double texV, double texR);
	void DrawLegSegment(double r, double h, int nSeg);
	void DrawLeg();
	void DrawSpiderBody();
	void DrawSpider();
	void UpdateCamera();

	//helpers
	void DrawSquare(double side, UINT texture);
	

public:
	HGLRC	 m_hrc; //OpenGL Rendering Context 
	UINT spider, front, left, right, back, top, bot;
	/*double m_CamDist = 50;
	double m_CamBeta = 0;
	double m_CamAlpha = 45;*/
	double m_CamDist = 0;
	double m_CamBeta = 0;
	double m_CamAlpha = 0;


};
