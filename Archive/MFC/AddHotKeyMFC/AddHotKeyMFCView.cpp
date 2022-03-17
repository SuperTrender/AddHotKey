// AddHotKeyMFCView.cpp : implementation of the CAddHotKeyMFCView class
//

#include "stdafx.h"
#include "AddHotKeyMFC.h"

#include "AddHotKeyMFCDoc.h"
#include "AddHotKeyMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAddHotKeyMFCView

IMPLEMENT_DYNCREATE(CAddHotKeyMFCView, CView)

BEGIN_MESSAGE_MAP(CAddHotKeyMFCView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CAddHotKeyMFCView construction/destruction

CAddHotKeyMFCView::CAddHotKeyMFCView()
{
	// TODO: add construction code here

}

CAddHotKeyMFCView::~CAddHotKeyMFCView()
{
}

BOOL CAddHotKeyMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CAddHotKeyMFCView drawing

void CAddHotKeyMFCView::OnDraw(CDC* /*pDC*/)
{
	CAddHotKeyMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CAddHotKeyMFCView printing

BOOL CAddHotKeyMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAddHotKeyMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAddHotKeyMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CAddHotKeyMFCView diagnostics

#ifdef _DEBUG
void CAddHotKeyMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CAddHotKeyMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAddHotKeyMFCDoc* CAddHotKeyMFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAddHotKeyMFCDoc)));
	return (CAddHotKeyMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CAddHotKeyMFCView message handlers
