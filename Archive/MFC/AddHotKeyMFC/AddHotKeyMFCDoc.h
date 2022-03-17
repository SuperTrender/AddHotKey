// AddHotKeyMFCDoc.h : interface of the CAddHotKeyMFCDoc class
//


#pragma once


class CAddHotKeyMFCDoc : public CDocument
{
protected: // create from serialization only
	CAddHotKeyMFCDoc();
	DECLARE_DYNCREATE(CAddHotKeyMFCDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CAddHotKeyMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


