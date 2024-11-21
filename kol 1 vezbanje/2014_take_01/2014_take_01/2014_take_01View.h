
// 2014_take_01View.h : interface of the CMy2014take01View class
//

#pragma once
#include "DImage.h"


class CMy2014take01View : public CView
{
protected: // create from serialization only
	CMy2014take01View() noexcept;
	DECLARE_DYNCREATE(CMy2014take01View)

// Attributes
public:
	CMy2014take01Doc* GetDocument() const;
	int Height;
	int Width;
	DImage tocak;
	HENHMETAFILE kola;
	float kola_w;
	float kola_h;
	float r;
	float kola_x;
	float kola_y;
	float rotAngle;
	float tocak_y;
	float tocak_l;
	float tocak_r;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawGround(CDC* pDC, float angle);
	void DrawCar(CDC* pDC, int x, int y, int w, int h);
	void DrawWheel(CDC* pDC, int x, int y, int r, float angle);
	void DrawTransparentWheel(CDC* pDC, int x, int y, int r);
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
	virtual ~CMy2014take01View();
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

#ifndef _DEBUG  // debug version in 2014_take_01View.cpp
inline CMy2014take01Doc* CMy2014take01View::GetDocument() const
   { return reinterpret_cast<CMy2014take01Doc*>(m_pDocument); }
#endif

