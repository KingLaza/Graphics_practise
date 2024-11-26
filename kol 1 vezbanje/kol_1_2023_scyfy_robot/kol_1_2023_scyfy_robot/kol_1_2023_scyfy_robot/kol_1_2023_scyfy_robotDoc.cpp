
// kol_1_2023_scyfy_robotDoc.cpp : implementation of the Ckol12023scyfyrobotDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "kol_1_2023_scyfy_robot.h"
#endif

#include "kol_1_2023_scyfy_robotDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Ckol12023scyfyrobotDoc

IMPLEMENT_DYNCREATE(Ckol12023scyfyrobotDoc, CDocument)

BEGIN_MESSAGE_MAP(Ckol12023scyfyrobotDoc, CDocument)
END_MESSAGE_MAP()


// Ckol12023scyfyrobotDoc construction/destruction

Ckol12023scyfyrobotDoc::Ckol12023scyfyrobotDoc() noexcept
{
	// TODO: add one-time construction code here

}

Ckol12023scyfyrobotDoc::~Ckol12023scyfyrobotDoc()
{
}

BOOL Ckol12023scyfyrobotDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Ckol12023scyfyrobotDoc serialization

void Ckol12023scyfyrobotDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void Ckol12023scyfyrobotDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void Ckol12023scyfyrobotDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Ckol12023scyfyrobotDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Ckol12023scyfyrobotDoc diagnostics

#ifdef _DEBUG
void Ckol12023scyfyrobotDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Ckol12023scyfyrobotDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Ckol12023scyfyrobotDoc commands
