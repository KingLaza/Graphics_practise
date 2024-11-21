
// 2014_take_01View.cpp : implementation of the CMy2014take01View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "2014_take_01.h"
#endif

#include "2014_take_01Doc.h"
#include "2014_take_01View.h"
#include "corecrt_math_defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <vector>
#include "DImage.h"


// CMy2014take01View

IMPLEMENT_DYNCREATE(CMy2014take01View, CView)

BEGIN_MESSAGE_MAP(CMy2014take01View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMy2014take01View construction/destruction

CMy2014take01View::CMy2014take01View() noexcept
{
	// TODO: add construction code here
	tocak.Load(CString("./res/Wheel.png"));
	kola = GetEnhMetaFileW(CString("./res/clio.emf"));
	kola_w = 450;
	kola_h = 450/2.5;
	r = 38;
	kola_x = kola_w / 2;
	kola_y = Height - kola_h / 2 - r / 2;	//shit
	rotAngle = -20;
	tocak_l = kola_x - 155;
	tocak_r = kola_x + 135;
}

CMy2014take01View::~CMy2014take01View()
{
}

BOOL CMy2014take01View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMy2014take01View drawing

void CMy2014take01View::OnDraw(CDC* pDC)
{
	CMy2014take01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	CRect rect;
	GetClientRect(&rect);
	Width = rect.Width();
	Height = rect.Height();
	tocak_y = Height - 2 * r;
	CBrush *oldBrush;
	CBrush c01 = (BS_SOLID, 3, RGB(0, 100, 180));
	oldBrush = pDC->SelectObject(&c01);
	pDC->Rectangle(0, 0, Width, Height);
	DrawGround(pDC, -rotAngle);

	auto oldMode = pDC->SetGraphicsMode(GM_ADVANCED);
	
	DrawCar(pDC, kola_x, kola_y, kola_w, kola_h);
	DrawWheel(pDC, kola_x - 155 - r, tocak_y, r, 0);
	DrawWheel(pDC, kola_x + 135 - r, tocak_y, r, 0);
	pDC->SetGraphicsMode(oldMode);

}

void CMy2014take01View::DrawGround(CDC* pDC, float angle) {
	//ugao je u stepenima
	//donji levi ugao prozora
	//okriv: 3, braon, ispuna:srafura braon-svetlo-zelena
	//ostatak svetlo plavo
	auto angleRad = (angle * M_PI) / 180;
	int triangleHeight = Width * tan(angleRad);
	std::vector<CPoint> tacke;
	tacke.push_back({ 0, Height });
	tacke.push_back({ Width, Height });
	tacke.push_back({ Width, Height - triangleHeight });
	CBrush* oldBrush;
	CBrush n = (BS_SOLID, 3, RGB(0, 120, 0));
	oldBrush = pDC->SelectObject(&n);
	pDC->Polygon(tacke.data(), tacke.size());
	pDC->SelectObject(oldBrush);

}

void CMy2014take01View::DrawCar(CDC* pDC, int x, int y, int w, int h) {
	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);
	Translate(pDC, x, -kola_h / 2 - r / 2, true);
	Rotate(pDC, rotAngle, true);
	Translate(pDC, 0, Height, true);

	/*RECT rectt = { x + w / 2, y - h / 2, x - w / 2, y + h / 2 };*/
	RECT rectt = { w / 2, - h / 2, - w / 2, h / 2 };
	pDC->PlayMetaFile(kola, &rectt);
	pDC->SetWorldTransform(&oldForm);
	
}

void CMy2014take01View::DrawWheel(CDC* pDC, int x, int y, int r, float angle) {
	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);
	auto wheelAngle = 360 * kola_x / (2 * r * M_PI);
	Translate(pDC, -r, -r, true);
	Rotate(pDC, wheelAngle, true);
	Translate(pDC, r, r, true);

	Translate(pDC, x, -2*r, true);
	Rotate(pDC, rotAngle, true);
	Translate(pDC, 0, +2*r + y, true);

	DrawTransparentWheel(pDC, 0, 0, r);

	pDC->SetWorldTransform(&oldForm);

}

void CMy2014take01View::DrawTransparentWheel(CDC* pDC, int x, int y, int r) {
	int tocak_w = tocak.Width();
	int tocak_h = tocak.Height();
	CBitmap* pBitmap = tocak.GetBitmap();

	CDC memDC;
	if (!memDC.CreateCompatibleDC(pDC)) {
		return; // Failed to create compatible DC
	}

	CBitmap* pOldBitmap = memDC.SelectObject(pBitmap);


	pDC->SetStretchBltMode(HALFTONE); // Smooth the bitmap during stretching


	pDC->TransparentBlt(0, 0,
		2 * r, 2 * r,
		&memDC, 52, 15,
		376, 376,
		RGB(255, 255, 255));

	// Restore the old bitmap in the memory DC
	memDC.SelectObject(pOldBitmap);
}

void CMy2014take01View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply) {
	XFORM form;
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = dX;
	form.eDy = dY;
	rightMultiply ? pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY) : pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}

void CMy2014take01View::Rotate(CDC* pDC, float angle, bool rightMultiply) {
	XFORM form;
	float radians = angle * (3.14159265358979f / 180.0f);
	form.eM11 = cos(radians);
	form.eM12 = sin(radians);
	form.eM21 = -sin(radians);
	form.eM22 = cos(radians);
	form.eDx = 0.0;
	form.eDy = 0.0;
	rightMultiply ? pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY) : pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}

void CMy2014take01View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply) {
	XFORM form;
	form.eM11 = sX;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = sY;
	form.eDx = 0;
	form.eDy = 0;
	rightMultiply ? pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY) : pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}


// CMy2014take01View printing

BOOL CMy2014take01View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy2014take01View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy2014take01View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMy2014take01View diagnostics

#ifdef _DEBUG
void CMy2014take01View::AssertValid() const
{
	CView::AssertValid();
}

void CMy2014take01View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2014take01Doc* CMy2014take01View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2014take01Doc)));
	return (CMy2014take01Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy2014take01View message handlers


void CMy2014take01View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	/*CView::OnKeyDown(nChar, nRepCnt, nFlags);*/
	// TODO: Add your message handler code here and/or call default
	switch (nChar) {
	case VK_LEFT:
		kola_x -= 5;
		break;
	case VK_RIGHT:
		kola_x += 5;
		break;
	case VK_UP:		//Q, VK_KEY_Q doesn't work
		rotAngle -= 5;
		break;
	case VK_DOWN:		//E
		rotAngle += 5;
		break;
	}
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
