// AddHotKeyMFCView.h : interface of the CAddHotKeyMFCView class
//


#pragma once


class CAddHotKeyMFCView : public CView
{
protected: // create from serialization only
	CAddHotKeyMFCView();
	DECLARE_DYNCREATE(CAddHotKeyMFCView)

// Attributes
public:
	CAddHotKeyMFCDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CAddHotKeyMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AddHotKeyMFCView.cpp
inline CAddHotKeyMFCDoc* CAddHotKeyMFCView::GetDocument() const
   { return reinterpret_cast<CAddHotKeyMFCDoc*>(m_pDocument); }
#endif

