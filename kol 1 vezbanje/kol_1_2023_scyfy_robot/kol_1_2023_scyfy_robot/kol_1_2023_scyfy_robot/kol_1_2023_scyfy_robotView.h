
// kol_1_2023_scyfy_robotView.h : interface of the Ckol12023scyfyrobotView class
//

#pragma once
#include "DImage.h"


class Ckol12023scyfyrobotView : public CView
{
protected: // create from serialization only
	Ckol12023scyfyrobotView() noexcept;
	DECLARE_DYNCREATE(Ckol12023scyfyrobotView)

// Attributes
public:
	Ckol12023scyfyrobotDoc* GetDocument() const;
	DImage glava;
	DImage nadkolenica;
	DImage nadlaktica;
	DImage podkolenica;
	DImage podlaktica;
	DImage saka;
	DImage stopalo;
	DImage telo;
	DImage pozadina;
	float ASangle;
	float DFangle;
	float GHangle;
	int centarX;
	int centarY;
	XFORM mainForma;
	bool rightMultiply;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawBackground(CDC* pDC);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void DrawHalf(CDC* pDC);
	void DrawRobot(CDC* pDC);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Ckol12023scyfyrobotView();
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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in kol_1_2023_scyfy_robotView.cpp
inline Ckol12023scyfyrobotDoc* Ckol12023scyfyrobotView::GetDocument() const
   { return reinterpret_cast<Ckol12023scyfyrobotDoc*>(m_pDocument); }
#endif

