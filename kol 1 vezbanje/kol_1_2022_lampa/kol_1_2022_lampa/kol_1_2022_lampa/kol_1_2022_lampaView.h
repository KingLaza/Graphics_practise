
// kol_1_2022_lampaView.h : interface of the Ckol12022lampaView class
//

#pragma once
#include "DImage.h"


class Ckol12022lampaView : public CView
{
protected: // create from serialization only
	Ckol12022lampaView() noexcept;
	DECLARE_DYNCREATE(Ckol12022lampaView)

// Attributes
public:
	Ckol12022lampaDoc* GetDocument() const;
	DImage base;
	DImage arm1;
	DImage arm2;
	DImage head;
	DImage pozadina;
	DImage base_shadow;
	DImage arm1_shadow;
	DImage arm2_shadow;
	DImage head_shadow;
	float angle12;
	float angle34;
	float angle56;
	XFORM mainForm;
	BOOL rightMultiply;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawBackground(CDC* pDC);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void DrawLampBase(CDC* pDC, bool blsShadow);
	void DrawLampArm1(CDC* pDC, bool blsShadow);
	void DrawLampArm2(CDC* pDC, bool blsShadow);
	void DrawLampHead(CDC* pDC, bool blsShadow);
	void DrawLamp(CDC* pDC, bool blsShadow);
	void DrawLampShadow(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	void Translate(CDC* pDC, float dx, float dy, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Ckol12022lampaView();
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

#ifndef _DEBUG  // debug version in kol_1_2022_lampaView.cpp
inline Ckol12022lampaDoc* Ckol12022lampaView::GetDocument() const
   { return reinterpret_cast<Ckol12022lampaDoc*>(m_pDocument); }
#endif

