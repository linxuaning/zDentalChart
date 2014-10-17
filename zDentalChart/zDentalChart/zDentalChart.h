// zDentalChart.h : main header file for the zDentalChart application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

#include<gdiPlus.h>
using namespace Gdiplus;

// CzDentalChartApp:
// See zDentalChart.cpp for the implementation of this class
//

class CzDentalChartApp : public CWinApp
{
public:
	CzDentalChartApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	virtual int ExitInstance();

private:
	GdiplusStartupInput m_gdiplusStartupInput;  
	ULONG_PTR    m_gdiplusToken;  
};

extern CzDentalChartApp theApp;