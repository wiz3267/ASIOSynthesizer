#if !defined(AFX_DIALOGASIOCONNECT_H__164C2BE9_8DAD_4040_BAF7_18B60D6AAC91__INCLUDED_)
#define AFX_DIALOGASIOCONNECT_H__164C2BE9_8DAD_4040_BAF7_18B60D6AAC91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogASIOConnect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogASIOConnect dialog

class CDialogASIOConnect : public CDialog
{
// Construction
public:
	CDialogASIOConnect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogASIOConnect)
	enum { IDD = IDD_DIALOG_ASIO_CONNECT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogASIOConnect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogASIOConnect)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonBreak();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGASIOCONNECT_H__164C2BE9_8DAD_4040_BAF7_18B60D6AAC91__INCLUDED_)
