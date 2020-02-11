// DTFM_GeneratorDlg.h : header file
//
#include <mmsystem.h>

#if !defined(DTFM_GENERATORDLG_H)
#define DTFM_GENERATORDLG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDTFM_GeneratorDlg dialog

class CDTFM_GeneratorDlg : public CDialog
{
// Construction
public:
	void MidiKeyPress(BYTE key, BYTE value);
	void SetFocus();
	void InitToneData();
	void TextError(MMRESULT);
	void ExitDialog();
	//void OnChar(UINT sym);
	UINT samplerate;

	#define MODE_NEED_CLOSE_WAVEOUT 1	
	int mode;
	bool NeedClose;
	void AddBuffer(double freq1, double freq2, char sym, int size);
	void AddBuffer();

	HWAVEOUT hWaveOut;
	CDTFM_GeneratorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDTFM_GeneratorDlg)
	enum { IDD = IDD_DTFM_GENERATOR_DIALOG };
	CSliderCtrl	m_slider_total_volume;
	CEdit	m_edit_base_a;
	CEdit	m_status_text;
	CEdit	m_amplitude_edit;
	CEdit	m_edit_total_buffer_count;
	CEdit	m_buffer_size_edit;
	CEdit	m_buffer_count;
	CSliderCtrl	m_slm6;
	CSliderCtrl	m_slm5;
	CSliderCtrl	m_sl6;
	CSliderCtrl	m_sl5;
	CSliderCtrl	m_slider_decrement;
	CEdit	m_midi_name_ctrl;
	CButton	m_stop_play;
	CButton	m_play_writen;
	CButton	m_button_write_stop;
	CButton	m_button_write;
	CButton	m_midi_open;
	CButton	m_midi_close;
	CSliderCtrl	m_slm4;
	CSliderCtrl	m_slm3;
	CSliderCtrl	m_slm2;
	CSliderCtrl	m_sl4;
	CSliderCtrl	m_sl3;
	CSliderCtrl	m_sl2;
	CSliderCtrl	m_sl1;
	CEdit	m_cwnd_digit;
	CButton	m_stop;
	CButton	m_generate;
	UINT	i_buffer_count;
	int		m_blockcounter;
	CString	m_edit;
	CString	m_midi_open_str;
	CString	m_amplitude;
	double	m_edit_freq;
	int		m_bufer_total_count;
	UINT	m_buffer_size;
	CString	m_midi_name;
	double	m_slider_decrement_double;
	double	m_wave_len;
	CString	m_edit_modilation;
	int		m_modulation_wheel;
	int		m_asio_device;
	CString	m_edit_scale;
	CString	m_string_base_a;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDTFM_GeneratorDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDTFM_GeneratorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPlayString();
	afx_msg void OnAbort();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonMidiClose();
	afx_msg void OnButtonMidiOpen();
	afx_msg void OnButtonWrite();
	afx_msg void OnButtonWriteStop();
	afx_msg void OnButtonPlayWriten();
	afx_msg void OnButtonReset();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnClose2();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnStopPlay();
	afx_msg void OnHide();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
