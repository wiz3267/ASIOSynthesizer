// DTFM_Generator.h : main header file for the DTFM_GENERATOR application
//

#if !defined(AFX_DTFM_GENERATOR_H__62077E0A_1287_4EAC_8CD6_9A1D82B726F7__INCLUDED_)
#define AFX_DTFM_GENERATOR_H__62077E0A_1287_4EAC_8CD6_9A1D82B726F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDTFM_GeneratorApp:
// See DTFM_Generator.cpp for the implementation of this class
//

class CDTFM_GeneratorApp : public CWinApp
{
public:
	CDTFM_GeneratorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDTFM_GeneratorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDTFM_GeneratorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DTFM_GENERATOR_H__62077E0A_1287_4EAC_8CD6_9A1D82B726F7__INCLUDED_)
