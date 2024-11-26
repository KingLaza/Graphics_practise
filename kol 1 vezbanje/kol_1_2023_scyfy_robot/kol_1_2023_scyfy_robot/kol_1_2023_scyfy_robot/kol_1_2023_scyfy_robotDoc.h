
// kol_1_2023_scyfy_robotDoc.h : interface of the Ckol12023scyfyrobotDoc class
//


#pragma once


class Ckol12023scyfyrobotDoc : public CDocument
{
protected: // create from serialization only
	Ckol12023scyfyrobotDoc() noexcept;
	DECLARE_DYNCREATE(Ckol12023scyfyrobotDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~Ckol12023scyfyrobotDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
