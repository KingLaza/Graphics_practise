
// kol_1_2023_scyfy_robot.h : main header file for the kol_1_2023_scyfy_robot application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Ckol12023scyfyrobotApp:
// See kol_1_2023_scyfy_robot.cpp for the implementation of this class
//

class Ckol12023scyfyrobotApp : public CWinApp
{
public:
	Ckol12023scyfyrobotApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ckol12023scyfyrobotApp theApp;
