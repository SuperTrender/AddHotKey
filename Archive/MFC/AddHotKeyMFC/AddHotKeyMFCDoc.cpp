// AddHotKeyMFCDoc.cpp : implementation of the CAddHotKeyMFCDoc class
//

#include "stdafx.h"
#include "AddHotKeyMFC.h"

#include "AddHotKeyMFCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAddHotKeyMFCDoc

IMPLEMENT_DYNCREATE(CAddHotKeyMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CAddHotKeyMFCDoc, CDocument)
END_MESSAGE_MAP()


// CAddHotKeyMFCDoc construction/destruction

CAddHotKeyMFCDoc::CAddHotKeyMFCDoc()
{
	// TODO: add one-time construction code here

}

CAddHotKeyMFCDoc::~CAddHotKeyMFCDoc()
{
}

BOOL CAddHotKeyMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CAddHotKeyMFCDoc serialization

void CAddHotKeyMFCDoc::Serialize(CArchive& ar)
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


// CAddHotKeyMFCDoc diagnostics

#ifdef _DEBUG
void CAddHotKeyMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAddHotKeyMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAddHotKeyMFCDoc commands
