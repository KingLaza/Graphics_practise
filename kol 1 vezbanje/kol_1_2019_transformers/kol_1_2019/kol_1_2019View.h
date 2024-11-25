
// kol_1_2019View.h : interface of the Ckol12019View class
//

#pragma once
#include "DImage.h"

class Ckol12019View : public CView
{
protected: // create from serialization only
	Ckol12019View() noexcept;
	DECLARE_DYNCREATE(Ckol12019View)

// Attributes
public:
	Ckol12019Doc* GetDocument() const;
	bool rightMultiply;
	float mainAngle;
	DImage body1;
	DImage arm1;
	DImage arm2;
	DImage leg1;
	DImage leg2;
	DImage background;
	XFORM mainForm;
	float Width;
	float Height;
	float RFangle;
	float WSangle;
	float QAangle;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawBackground(CDC* pDC, CRect rc);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void DrawArm1(CDC* pDC);
	void DrawArm2(CDC* pDC);
	void DrawLeg1(CDC* pDC);
	void DrawLeg2(CDC* pDC);
	void DrawBody1(CDC* pDC);
	void DrawTransformer(CDC* pDC);
	void translate(CDC* pDC, int Dx, int Dy, bool rightMultiply);
	void scale(CDC* pDC, float sx, float sy, bool rightMultiply);
	void rotate(CDC* pDC, float angle, bool rightMultiply);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Ckol12019View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in kol_1_2019View.cpp
inline Ckol12019Doc* Ckol12019View::GetDocument() const
   { return reinterpret_cast<Ckol12019Doc*>(m_pDocument); }
#endif

