
// kol_1_2022_lampaView.cpp : implementation of the Ckol12022lampaView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "kol_1_2022_lampa.h"
#endif

#include "kol_1_2022_lampaDoc.h"
#include "kol_1_2022_lampaView.h"
#include "corecrt_math_defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <iostream>


// Ckol12022lampaView

IMPLEMENT_DYNCREATE(Ckol12022lampaView, CView)

BEGIN_MESSAGE_MAP(Ckol12022lampaView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// Ckol12022lampaView construction/destruction

Ckol12022lampaView::Ckol12022lampaView() noexcept
{
	// TODO: add construction code here
	base.Load(CString("./res/base.png"));
	arm1.Load(CString("./res/arm1.png"));
	arm2.Load(CString("./res/arm2.png"));
	head.Load(CString("./res/head.png"));
	pozadina.Load(CString("./res/pozadina.jpg"));
	base_shadow.Load(CString("./res/base_shadow.png"));
	arm1_shadow.Load(CString("./res/arm1_shadow.png"));
	arm2_shadow.Load(CString("./res/arm2_shadow.png"));
	head_shadow.Load(CString("./res/head_shadow.png"));
	angle12 = -45;
	angle34 = -90;
	angle56 = 180;
	mainForm;
	rightMultiply = false;

}

Ckol12022lampaView::~Ckol12022lampaView()
{
}

BOOL Ckol12022lampaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Ckol12022lampaView drawing

void Ckol12022lampaView::OnDraw(CDC* pDC)
{
	Ckol12022lampaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	auto oldGM = pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);

	DrawLamp(pDC, false);

	pDC->SetWorldTransform(&oldForm);
	pDC->SetGraphicsMode(oldGM);

}

void Ckol12022lampaView::DrawBackground(CDC* pDC) {
	CRect rec;
	CRect rec2 = { 0,0, pozadina.Width(), pozadina.Height() };
	GetClientRect(&rec);
	auto br = rec.BottomRight();
	auto x = br.x;
	auto y = br.y;
	pozadina.Draw(pDC, rec2, rec);
	//Translate(pDC, -(pozadina.Width() - x) / 2, -(pozadina.Height() - y), false);
	//pozadina.Draw(pDC, rec2, rec2);
}

void Ckol12022lampaView::DrawImgTransparent(CDC* pDC, DImage* pImage) {

	CBitmap *bitmap = pImage->GetBitmap();
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	memDC.SelectObject(bitmap);
	auto color = memDC.GetPixel(0, 0);
	pDC->SetStretchBltMode(HALFTONE); 
	pDC->TransparentBlt(0, 0, pImage->Width(), pImage->Height(), &memDC, 0, 0, pImage->Width(), pImage->Height(), color);
	memDC.DeleteDC();
}

void Ckol12022lampaView::DrawLampBase(CDC* pDC, bool blsShadow) {
	Translate(pDC, -base.Width() / 2, -base.Height() / 2, rightMultiply);
	if (blsShadow) {
		DrawImgTransparent(pDC, &base_shadow);
	}
	else {
		DrawImgTransparent(pDC, &base);
	}
	Translate(pDC, base.Width()/2 + 20, +  20, rightMultiply);
	
}
void Ckol12022lampaView::DrawLampArm1(CDC* pDC, bool blsShadow) {
	Rotate(pDC, angle12, rightMultiply);
	Translate(pDC, -58, -61, rightMultiply);
	if (blsShadow) {
		DrawImgTransparent(pDC, &arm1_shadow);
	}
	else {
		DrawImgTransparent(pDC, &arm1);
	}

	Translate(pDC, 367 - 58, 122 - 61, rightMultiply);
}
void Ckol12022lampaView::DrawLampArm2(CDC* pDC, bool blsShadow) {
	Rotate(pDC, angle34, rightMultiply);
	Translate(pDC, -36, -40, rightMultiply);
	if (blsShadow) {
		DrawImgTransparent(pDC, &arm2_shadow);
	}
	else {
		DrawImgTransparent(pDC, &arm2);
	}

	Translate(pDC, 308 - 36, 80 - 40, rightMultiply);
}
void Ckol12022lampaView::DrawLampHead(CDC* pDC, bool blsShadow) {
	Rotate(pDC, angle56, rightMultiply);
	Translate(pDC, -178, -100, rightMultiply);
	if (blsShadow) {
		DrawImgTransparent(pDC, &head_shadow);
	}
	else {
		DrawImgTransparent(pDC, &head);
	}
}

void Ckol12022lampaView::DrawLamp(CDC* pDC, bool blsShadow) {
	DrawBackground(pDC);
	bool shadow = false;
	CRect rect;
	GetClientRect(&rect);
	Translate(pDC, 0.55 * rect.Width() + base.Width()/2, 0.70 * rect.Height() + base.Height()/2, rightMultiply);
	XFORM oldForm;
	shadow = true;
	pDC->GetWorldTransform(&oldForm);
	Scale(pDC, 1, 0.25, rightMultiply);
	Rotate(pDC, -90, rightMultiply);
	DrawLampBase(pDC, shadow);
	DrawLampArm1(pDC, shadow);
	DrawLampArm2(pDC, shadow);
	DrawLampHead(pDC, shadow);
	pDC->SetWorldTransform(&oldForm);
	shadow = false;
	DrawLampBase(pDC, shadow);
	DrawLampArm1(pDC, shadow);
	DrawLampArm2(pDC, shadow);
	DrawLampHead(pDC, shadow);
	
	
}
void Ckol12022lampaView::DrawLampShadow(CDC* pDC) {

}


//base functions (tranlsate, rotate, scale)

void Ckol12022lampaView::Translate(CDC* pDC, float dx, float dy, bool rightMultiply) {
	mainForm.eDx = dx;
	mainForm.eDy = dy;
	mainForm.eM11 = 1;
	mainForm.eM12 = 0;
	mainForm.eM21 = 0;
	mainForm.eM22 = 1;
	rightMultiply ? pDC->ModifyWorldTransform(&mainForm, MWT_RIGHTMULTIPLY) :
		pDC->ModifyWorldTransform(&mainForm, MWT_LEFTMULTIPLY);
}

void Ckol12022lampaView::Rotate(CDC* pDC, float angle, bool rightMultiply) {
	float rad = angle / 180 * M_PI;
	mainForm.eDx = 0;
	mainForm.eDy = 0;
	mainForm.eM11 = cos(rad);
	mainForm.eM12 = sin(rad);
	mainForm.eM21 = -sin(rad);
	mainForm.eM22 = cos(rad);
	rightMultiply ? pDC->ModifyWorldTransform(&mainForm, MWT_RIGHTMULTIPLY) :
		pDC->ModifyWorldTransform(&mainForm, MWT_LEFTMULTIPLY);
}

void Ckol12022lampaView::Scale(CDC* pDC, float sX, float sY, bool rightMultiply) {
	mainForm.eDx = 0;
	mainForm.eDy = 0;
	mainForm.eM11 = sX;
	mainForm.eM12 = 0;
	mainForm.eM21 = 0;
	mainForm.eM22 = sY;
	rightMultiply ? pDC->ModifyWorldTransform(&mainForm, MWT_RIGHTMULTIPLY) :
		pDC->ModifyWorldTransform(&mainForm, MWT_LEFTMULTIPLY);
}

// Ckol12022lampaView printing

BOOL Ckol12022lampaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Ckol12022lampaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Ckol12022lampaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Ckol12022lampaView diagnostics

#ifdef _DEBUG
void Ckol12022lampaView::AssertValid() const
{
	CView::AssertValid();
}

void Ckol12022lampaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ckol12022lampaDoc* Ckol12022lampaView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ckol12022lampaDoc)));
	return (Ckol12022lampaDoc*)m_pDocument;
}
#endif //_DEBUG


// Ckol12022lampaView message handlers


void Ckol12022lampaView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar) {
	case '1':
		angle12 += 5;
		break;
	case '2':
		angle12 -= 5;
		break;
	case '3':
		angle34 += 5;
		break;
	case '4':
		angle34 -= 5;
		break;
	case '5':
		angle56 += 5;
		break;
	case '6':
		angle56 -= 5;
		break;
	}
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
