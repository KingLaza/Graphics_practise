
// kol_1_2022_lampa.h : main header file for the kol_1_2022_lampa application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Ckol12022lampaApp:
// See kol_1_2022_lampa.cpp for the implementation of this class
//

class Ckol12022lampaApp : public CWinApp
{
public:
	Ckol12022lampaApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ckol12022lampaApp theApp;
