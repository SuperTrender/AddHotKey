// AddHotKeyMFC.h : main header file for the AddHotKeyMFC application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CAddHotKeyMFCApp:
// See AddHotKeyMFC.cpp for the implementation of this class
//

class CAddHotKeyMFCApp : public CWinApp
{
public:
	CAddHotKeyMFCApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAddHotKeyMFCApp theApp;