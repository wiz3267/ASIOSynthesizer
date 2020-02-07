// DTFM_Generator.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DTFM_Generator.h"
#include "DTFM_GeneratorDlg.h"
#include "dialogasioconnect.h"

/////////////////////////////////////////////////////////////////////////////
// CDTFM_GeneratorApp

BEGIN_MESSAGE_MAP(CDTFM_GeneratorApp, CWinApp)
	//{{AFX_MSG_MAP(CDTFM_GeneratorApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDTFM_GeneratorApp construction

CDTFM_GeneratorApp::CDTFM_GeneratorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDTFM_GeneratorApp object

CDTFM_GeneratorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDTFM_GeneratorApp initialization

int main(int argc, char **argv);

void StopAsio();

void Msg(char * txt)
{
	AfxMessageBox(txt,MB_OK,0);
}

BOOL CDTFM_GeneratorApp::InitInstance()
{
	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CDialogASIOConnect d;
	if (d.DoModal() == FALSE)
	{
		AfxMessageBox("ASIO Init Error. Programm can not to be continue",MB_OK,0);
		return 0;
	}

	CDTFM_GeneratorDlg dlg;
	//m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	StopAsio();
	return FALSE;
}
