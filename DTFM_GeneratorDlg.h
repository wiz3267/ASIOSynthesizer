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
	int SavePresets(char *fname=NULL);
	void SetIniValue(char *fname=NULL);
	void ShowGarmonicStatus(int param);
	void ShowGarmonics();
	int ChangeGarmonicMouse(UINT nFlags, CPoint point, bool ShowGraphic);
	void MidiKeyPress(BYTE key, BYTE value);
	void SetFocus();
	void InitToneData();
	void TextError(MMRESULT);
	void ExitDialog();
	//void OnChar(UINT sym);
	UINT samplerate;

	CDTFM_GeneratorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDTFM_GeneratorDlg)
	enum { IDD = IDD_DTFM_GENERATOR_DIALOG };
	CListBox	m_list_preset;
	CStatic	m_static_sin_saw_mode;
	CStatic	m_static_slider10;
	CStatic	m_static_slider9;
	CEdit	m_global_filter2;
	CEdit	m_global_ss2;
	CEdit	m_global_rez2;
	CStatic	m_static_slider8;
	CStatic	m_static_slider7;
	CStatic	m_static_slider6;
	CEdit	m_tick_count_fill_buffer;
	CStatic	m_static_slider5;
	CStatic	m_static_slider4;
	CStatic	m_static_sslider3;
	CStatic	m_static_slider3;
	CStatic	m_static_slider2;
	CStatic	m_static_slider1;
	CEdit	m_level_control;
	CEdit	m_pianoroll;
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
	int		m_asio_device;
	CString	m_edit_scale;
	CString	m_string_base_a;
	CString	m_modulation_amplitude;
	CString	m_string_status_text;
	int		m_size_asio_buffer;
	CString	m_garmonic_5;
	CString	m_garmonic_6;
	CString	m_attack;
	CString	m_edit_modulation_wheel;
	BOOL	m_use_velocity;
	BOOL	m_no_sustain;
	BOOL	m_piano_mouse_click;
	BOOL	m_ctrl_key_use;
	BOOL	m_check_saw;
	BOOL	m_check_saw2;
	BOOL	m_check_saw3;
	int		m_sample_rate;
	CString	m_rez_min;
	CString	m_rez_max;
	BOOL	m_check_filter2;
	BOOL	m_garmonic_mode;
	CString	m_garmonic_base_freq;
	BOOL	m_write_wav;
	BOOL	m_check_filter1;
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
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonMidiClose();
	afx_msg void OnButtonMidiOpen();
	afx_msg void OnButtonWrite();
	afx_msg void OnButtonWriteStop();
	afx_msg void OnButtonPlayWriten();
	afx_msg void OnButtonReset();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnStopPlay();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetfocusEditModulation();
	afx_msg void OnKillfocusEditStatusText();
	afx_msg void OnKillfocusEditModulation();
	afx_msg void OnSetfocusEditScale();
	afx_msg void OnKillfocusEditScale();
	afx_msg void OnButtonAsioControlPanel();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSettingsSetasiodevice();
	afx_msg void OnFileExit();
	afx_msg void OnButtonDemo();
	afx_msg void OnKeyboardKeysMenu();
	afx_msg void OnButtonRndGarmonic();
	afx_msg void OnButtonPlusXscaleWavegraphic();
	afx_msg void OnButtonMinusXscaleWavegraphic();
	afx_msg void OnCheckGarmonicMode();
	afx_msg void OnCheckWriteWavdata();
	afx_msg void OnCheckSaw();
	afx_msg void OnSettingsLoadpresets();
	afx_msg void OnSettingsSavepresets();
	afx_msg void OnSelchangeListPreset();
	afx_msg void OnDblclkListPreset();
	afx_msg void OnButtonSavePreset();
	afx_msg void OnButtonLoadPreset();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
