
// kol_1_2023_scyfy_robotView.cpp : implementation of the Ckol12023scyfyrobotView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "kol_1_2023_scyfy_robot.h"
#endif

#include "kol_1_2023_scyfy_robotDoc.h"
#include "kol_1_2023_scyfy_robotView.h"
#include "corecrt_math_defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ckol12023scyfyrobotView

IMPLEMENT_DYNCREATE(Ckol12023scyfyrobotView, CView)

BEGIN_MESSAGE_MAP(Ckol12023scyfyrobotView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// Ckol12023scyfyrobotView construction/destruction

Ckol12023scyfyrobotView::Ckol12023scyfyrobotView() noexcept
{
	// TODO: add construction code here
	glava.Load(CString("./res/glava.png"));
	nadkolenica.Load(CString("./res/nadkolenica.png"));
	nadlaktica.Load(CString("./res/nadlaktica.png"));
	podkolenica.Load(CString("./res/podkolenica.png"));
	podlaktica.Load(CString("./res/podlaktica.png"));
	saka.Load(CString("./res/saka.png"));
	stopalo.Load(CString("./res/stopalo.png"));
	telo.Load(CString("./res/telo.png"));
	pozadina.Load(CString("./res/pozadina.jpg"));
	mainForma;
	centarX = pozadina.Width() / 2;
	centarY = pozadina.Height() / 2;
	rightMultiply = false;
	ASangle = 0;
	DFangle = 0;
	GHangle = 0;

}

Ckol12023scyfyrobotView::~Ckol12023scyfyrobotView()
{
}

BOOL Ckol12023scyfyrobotView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Ckol12023scyfyrobotView drawing

void Ckol12023scyfyrobotView::OnDraw(CDC* pDC)
{
	Ckol12023scyfyrobotDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//CDC* memDC = new CDC();
	//memDC->CreateCompatibleDC(pDC);
	

	//CBitmap memBitmap;
	//memBitmap.CreateCompatibleBitmap(pDC, r.Width(), r.Height());
	//memDC->SelectObject(&memBitmap);

	//// Fill the memory DC with white background
	//memDC->FillSolidRect(0, 0, r.Width(), r.Height(), RGB(255, 255, 255));


	auto oldGM = pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);

	CRect r;
	GetClientRect(&r);

	DrawBackground(pDC);
	DrawRobot(pDC);

	pDC->SetWorldTransform(&oldForm);
	pDC->SetGraphicsMode(oldGM);


	//pDC->BitBlt(0, 0, r.Width(), r.Height(), memDC, 0, 0, SRCCOPY);

}

void Ckol12023scyfyrobotView::DrawBackground(CDC* pDC) {
	CRect rec;
	//rec = { 0,0, pozadina.Width(), pozadina.Height() };
	GetClientRect(&rec);
	pozadina.Draw(pDC, rec, rec);
	
}

void Ckol12023scyfyrobotView::DrawImgTransparent(CDC* pDC, DImage* pImage) {
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	CBitmap* bitmapa = pImage->GetBitmap();
	memDC->SelectObject(bitmapa);
	auto color = memDC->GetPixel(0, 0);

	pDC->TransparentBlt(0, 0, pImage->Width(), pImage->Height(), memDC, 0, 0, pImage->Width(), pImage->Height(), color);
	memDC->DeleteDC();
	delete memDC;
	memDC = nullptr;
}

void Ckol12023scyfyrobotView::DrawHalf(CDC* pDC) {
	//leva bez glave
	XFORM oldOld;
	pDC->GetWorldTransform(&oldOld);

	Translate(pDC, -telo.Width(), -telo.Height(), rightMultiply);
	DrawImgTransparent(pDC, &telo);

	XFORM oldZaTelo; 
	pDC->GetWorldTransform(&oldZaTelo);

	//crtanje ruke (3 dela)
	Translate(pDC, 25, 65, rightMultiply); //telo, rot1
	Rotate(pDC, GHangle, rightMultiply);
	Translate(pDC, -35, -35, rightMultiply);
	DrawImgTransparent(pDC, &nadlaktica);

	Translate(pDC, 22, 167, rightMultiply);
	Rotate(pDC, DFangle, rightMultiply);
	Translate(pDC, -30, -33, rightMultiply);
	DrawImgTransparent(pDC, &podlaktica);

	Translate(pDC, 30, 140, rightMultiply);
	Rotate(pDC, ASangle, rightMultiply);
	Translate(pDC, -25, -3, rightMultiply);
	DrawImgTransparent(pDC, &saka);

	pDC->SetWorldTransform(&oldZaTelo);

	//sad, crtamo noge
	Translate(pDC, 61, 262, rightMultiply);
	Translate(pDC, -29, -20, rightMultiply);
	DrawImgTransparent(pDC, &nadkolenica);

	Translate(pDC, 30, 184, rightMultiply);
	Translate(pDC, -25, -37, rightMultiply);
	DrawImgTransparent(pDC, &podkolenica);

	Translate(pDC, 25, 248, rightMultiply);
	Translate(pDC, -20, -16, rightMultiply);
	DrawImgTransparent(pDC, &stopalo);

	pDC->SetWorldTransform(&oldOld);
}

void Ckol12023scyfyrobotView::DrawRobot(CDC* pDC) {
	Translate(pDC, centarX, centarY, rightMultiply);
	XFORM old;
	pDC->GetWorldTransform(&old);
	DrawHalf(pDC);
	Scale(pDC, -1, 1, rightMultiply);
	DrawHalf(pDC);
	pDC->SetWorldTransform(&old);
	Translate(pDC, -glava.Width() / 2, -telo.Height() - glava.Height(), rightMultiply);
	DrawImgTransparent(pDC, &glava);
}

void Ckol12023scyfyrobotView::Translate(CDC* pDC, float dX, float dY, bool rightMultiply) {
	mainForma.eDx = dX;
	mainForma.eDy = dY;
	mainForma.eM11 = 1;
	mainForma.eM12 = 0;
	mainForma.eM21 = 0;
	mainForma.eM22 = 1;
	rightMultiply ? pDC->ModifyWorldTransform(&mainForma, MWT_RIGHTMULTIPLY) : pDC->ModifyWorldTransform(&mainForma, MWT_LEFTMULTIPLY);
}
void Ckol12023scyfyrobotView::Rotate(CDC* pDC, float angle, bool rightMultiply) {
	float rad = angle / 180 * M_PI;
	mainForma.eDx = 0;
	mainForma.eDy = 0;
	mainForma.eM11 = cos(rad);
	mainForma.eM12 = sin(rad);
	mainForma.eM21 = -sin(rad);
	mainForma.eM22 = cos(rad);
	rightMultiply ? pDC->ModifyWorldTransform(&mainForma, MWT_RIGHTMULTIPLY) : pDC->ModifyWorldTransform(&mainForma, MWT_LEFTMULTIPLY);
}
void Ckol12023scyfyrobotView::Scale(CDC* pDC, float sX, float sY, bool rightMultiply) {
	mainForma.eDx = 0;
	mainForma.eDy = 0;
	mainForma.eM11 = sX;
	mainForma.eM12 = 0;
	mainForma.eM21 = 0;
	mainForma.eM22 = sY;
	rightMultiply ? pDC->ModifyWorldTransform(&mainForma, MWT_RIGHTMULTIPLY) : pDC->ModifyWorldTransform(&mainForma, MWT_LEFTMULTIPLY);
}


// Ckol12023scyfyrobotView printing

BOOL Ckol12023scyfyrobotView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Ckol12023scyfyrobotView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Ckol12023scyfyrobotView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Ckol12023scyfyrobotView diagnostics

#ifdef _DEBUG
void Ckol12023scyfyrobotView::AssertValid() const
{
	CView::AssertValid();
}

void Ckol12023scyfyrobotView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ckol12023scyfyrobotDoc* Ckol12023scyfyrobotView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ckol12023scyfyrobotDoc)));
	return (Ckol12023scyfyrobotDoc*)m_pDocument;
}
#endif //_DEBUG


// Ckol12023scyfyrobotView message handlers


void Ckol12023scyfyrobotView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	switch (nChar) {
	case 'G':
		GHangle += 10;
		break;
	case 'H':
		GHangle -= 10;
		break;
	case 'D':
		DFangle += 10;
		break;
	case 'F':
		DFangle -= 10;
		break;
	case 'A':
		ASangle += 10;
		break;
	case 'S':
		ASangle -= 10;
		break;
	}

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL Ckol12023scyfyrobotView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}
