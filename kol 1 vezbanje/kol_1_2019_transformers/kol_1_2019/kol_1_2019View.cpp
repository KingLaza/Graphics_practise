
// kol_1_2019View.cpp : implementation of the Ckol12019View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "kol_1_2019.h"
#endif

#include "kol_1_2019Doc.h"
#include "kol_1_2019View.h"
#include "corecrt_math_defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ckol12019View

IMPLEMENT_DYNCREATE(Ckol12019View, CView)

BEGIN_MESSAGE_MAP(Ckol12019View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// Ckol12019View construction/destruction

Ckol12019View::Ckol12019View() noexcept
{
	// TODO: add construction code here
	rightMultiply = false;
	mainAngle = 0.0f;
	body1.Load(CString("./res/body1.png"));
	arm1.Load(CString("./res/arm1.png"));
	arm2.Load(CString("./res/arm2.png"));
	leg1.Load(CString("./res/leg1.png"));
	leg2.Load(CString("./res/leg2.png"));
	background.Load(CString("./res/background.jpg"));
	RFangle = 0;
	QAangle = 0;
	WSangle = 0;
	
}

Ckol12019View::~Ckol12019View()
{
}

BOOL Ckol12019View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Ckol12019View drawing

void Ckol12019View::OnDraw(CDC* pDC)
{
	Ckol12019Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	
	auto oldGraphics = pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);
	
	DrawTransformer(pDC);


	pDC->SetWorldTransform(&oldForm);
	pDC->SetGraphicsMode(oldGraphics);
	
}

void Ckol12019View::DrawBackground(CDC* pDC, CRect rc) {
	background.Draw(pDC, rc, rc);
}
void Ckol12019View::DrawImgTransparent(CDC* pDC, DImage* pImage) {
	
	int w = pImage->Width();
	int h = pImage->Height();
	CBitmap* pBitmap = pImage->GetBitmap();

	CDC memDC;
	if (!memDC.CreateCompatibleDC(pDC)) {
		return; // Failed to create compatible DC
	}

	CBitmap* pOldBitmap = memDC.SelectObject(pBitmap);
	auto pixel = memDC.GetPixel(0, 0);

	pDC->SetStretchBltMode(HALFTONE); // Smooth the bitmap during stretching


	pDC->TransparentBlt(0, 0,
		w, h,
		&memDC, 0, 0,
		w, h,
		pixel);

	// Restore the old bitmap in the memory DC
	memDC.SelectObject(pOldBitmap);

}
void Ckol12019View::DrawArm1(CDC* pDC) {
	
	rotate(pDC, WSangle, rightMultiply);
	translate(pDC, -34, -31, rightMultiply);
	DrawImgTransparent(pDC, &arm1);
	translate(pDC, 34, 31, rightMultiply);
	
}
void Ckol12019View::DrawArm2(CDC* pDC) {
	XFORM old;
	pDC->GetWorldTransform(&old);
	rotate(pDC, WSangle, rightMultiply);
	translate(pDC, 176, 71, rightMultiply);
	rotate(pDC, 180 + WSangle, rightMultiply);
	translate(pDC, -23, -61, rightMultiply);
	DrawImgTransparent(pDC, &arm2);
	pDC->SetWorldTransform(&old);
}
void Ckol12019View::DrawLeg1(CDC* pDC) {
	rotate(pDC, -RFangle, rightMultiply);
	translate(pDC, -30, -125, rightMultiply);

	DrawImgTransparent(pDC, &leg1);

	translate(pDC, 30, 125, rightMultiply);
	translate(pDC, 207, 0, rightMultiply);
	rotate(pDC, QAangle, rightMultiply);
	//namerno nisam stavio nazad na old form, jer hocu
	//da nova tacka crtanja bude desno + rotirano
}
void Ckol12019View::DrawLeg2(CDC* pDC) {

	XFORM old;
	pDC->GetWorldTransform(&old);				//bolje je prvo da se rotira, pa onda translira pa tek onda iscrtava
	rotate(pDC, RFangle, rightMultiply);
	translate(pDC, -35, -60, rightMultiply);
	DrawImgTransparent(pDC, &leg2);
	pDC->SetWorldTransform(&old);
}
void Ckol12019View::DrawBody1(CDC* pDC) {	
	//rotate(pDC, RFangle, rightMultiply);		//odgradjeno u leg1
	translate(pDC, -26, -133, rightMultiply);
	DrawImgTransparent(pDC, &body1);

	translate(pDC, 26, 133, rightMultiply);
	translate(pDC, 186, -47, rightMultiply);	//ova tacka blizu glave... nzm tacno da li je tu
	
}
void Ckol12019View::DrawTransformer(CDC* pDC) {
	CRect bk;
	GetClientRect(bk);
	Width = bk.Width();
	Height = bk.Height();
	DrawBackground(pDC, bk);

	translate(pDC, 250, Height / 2 + 100, rightMultiply);

	DrawLeg2(pDC);
	DrawLeg1(pDC);
	DrawBody1(pDC);
	DrawArm2(pDC);
	DrawArm1(pDC);
	
}

void Ckol12019View::translate(CDC* pDC, int Dx, int Dy, bool rightMultiply) {
	mainForm.eDx = Dx;
	mainForm.eDy = Dy;
	mainForm.eM11 = 1;
	mainForm.eM12 = 0;
	mainForm.eM21 = 0;
	mainForm.eM22 = 1;
	pDC->ModifyWorldTransform(&mainForm, rightMultiply? MWT_RIGHTMULTIPLY: MWT_LEFTMULTIPLY);

}

void Ckol12019View::scale(CDC* pDC, float sx, float sy, bool rightMultiply) {
	mainForm.eDx = 0;
	mainForm.eDy = 0;
	mainForm.eM11 = sx;
	mainForm.eM12 = 0;
	mainForm.eM21 = 0;
	mainForm.eM22 = sy;
	pDC->ModifyWorldTransform(&mainForm, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void Ckol12019View::rotate(CDC* pDC, float angle, bool rightMultiply) {
	auto radian = angle * M_PI / 180;
	mainForm.eDx = 0;
	mainForm.eDy = 0;
	mainForm.eM11 = cos(radian);
	mainForm.eM12 = sin(radian);
	mainForm.eM21 = -sin(radian);
	mainForm.eM22 = cos(radian);
	pDC->ModifyWorldTransform(&mainForm, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

// Ckol12019View printing

BOOL Ckol12019View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Ckol12019View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Ckol12019View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Ckol12019View diagnostics

#ifdef _DEBUG
void Ckol12019View::AssertValid() const
{
	CView::AssertValid();
}

void Ckol12019View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ckol12019Doc* Ckol12019View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ckol12019Doc)));
	return (Ckol12019Doc*)m_pDocument;
}
#endif //_DEBUG


// Ckol12019View message handlers


void Ckol12019View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	switch (nChar) {
	case VK_LEFT:
		RFangle -= 5;
		break;
	case VK_RIGHT:
		RFangle += 5;
		break;
	case VK_UP:		//Q, VK_KEY_Q doesn't work
		QAangle -= 5;
		break;
	case VK_DOWN:		//E
		QAangle += 5;
		break;
	case VK_TAB:		//Q, VK_KEY_Q doesn't work
		WSangle -= 5;
		break;
	case VK_SUBTRACT:		//E
		WSangle += 5;
		break;
	}

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
