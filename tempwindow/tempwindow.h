// tempwindow.h : main header file for the TEMPWINDOW application
//

#if !defined(AFX_TEMPWINDOW_H__95873992_B22E_43F8_AE76_30AA8EF41481__INCLUDED_)
#define AFX_TEMPWINDOW_H__95873992_B22E_43F8_AE76_30AA8EF41481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTempwindowApp:
// See tempwindow.cpp for the implementation of this class
//

class CTempwindowApp : public CWinApp
{
public:
	CTempwindowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTempwindowApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTempwindowApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEMPWINDOW_H__95873992_B22E_43F8_AE76_30AA8EF41481__INCLUDED_)
