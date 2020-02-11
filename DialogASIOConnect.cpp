// DialogASIOConnect.cpp : implementation file
//

#include "stdafx.h"
#include "DTFM_Generator.h"
#include "DialogASIOConnect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogASIOConnect dialog


CDialogASIOConnect::CDialogASIOConnect(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogASIOConnect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogASIOConnect)
	m_asio_index = 0;
	//}}AFX_DATA_INIT
}


void CDialogASIOConnect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogASIOConnect)
	DDX_Text(pDX, IDC_EDIT_ASIO_DEVICE_INDEX, m_asio_index);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogASIOConnect, CDialog)
	//{{AFX_MSG_MAP(CDialogASIOConnect)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_BREAK, OnButtonBreak)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogASIOConnect message handlers


int main(int argc, char **argv);
BOOL CDialogASIOConnect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	SetTimer(1,5000,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogASIOConnect::OnOK() 
{
	//EndDialog(TRUE);
	UpdateData(1);
	int res=main(m_asio_index,0);
	EndDialog(res);
	
	//CDialog::OnOK();
}

void CDialogASIOConnect::OnClose() 
{
	EndDialog(FALSE);
	CDialog::OnClose();
}

void CDialogASIOConnect::OnTimer(UINT nIDEvent) 
{
	KillTimer(1);
	int res=main(1,0);	
	EndDialog(res);

	CDialog::OnTimer(nIDEvent);
}

void CDialogASIOConnect::OnButtonBreak() 
{
	EndDialog(FALSE);	
}
