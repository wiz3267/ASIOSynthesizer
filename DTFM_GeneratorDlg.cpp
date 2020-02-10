// DTFM_GeneratorDlg.cpp : implementation file
//
#include "stdafx.h"
#include "DTFM_Generator.h"
#include "DTFM_GeneratorDlg.h"

#include <atlbase.h>
#include <math.h>
#include "inifile.h"

const double PI=3.1415926;

int NeedUpdateMidiEvent=1;	//îáíîâëÿòü Midi ñîîáùåíèÿ
int NeedUpdateBaseFreq=0;	//ìåíÿòü áàçîâóþ ÷àñòîòó ïðè èçìåíåíèÿ ñëàéäåðà

int NeedUpdateModulation=1;	//ðåàãèðîâàòü íà ñëàéäåð ìîäóëÿöèè

//double modulation=0;
double step_modulation=0;	//ñêîðîñòü ìîäóëÿöèè
double ModulationWheel=0;
int m_modulation_wheel_2=0;	//çíà÷åíèÿ êîëåñà ìîäóëÿöèè

CString m_edit_list_midi;

double scale;//=pow(2.0,1.0/12.0);
//double scale;//=pow(2.0,1.0/SCALE);


//TIME_CRITICAL
//#import "D:\Program Files\Microsoft Visual Studio\VC98\Lib\winmm.lib"


HWAVEOUT hWaveOut_global=0;
CString m_amplitude_global="";

void MidiKeyPress2(BYTE key, BYTE value);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void DrawButton(CDC *dc, int x, int y, int start);

CINIFiles ini;

void SetKeys(int n, int vol);

int BaseKeyboard=59;
double BASE_A;

int change=true;

HMIDIIN hmidiIn;

CString ENDL="\r\n";

CFile file;

BYTE *PlayWriten=NULL;
DWORD PlayWritenSize=0;
WORD PlayWritenPosition=0;

bool write=false; //íóæíî ëè çàïèñûâàòü â ôàéë

int CurrentAmplitude=0;

bool Overload=false; //ïåðåãðóçêà çâóêîâ. óðîâíÿ >32767 OR <-32767

union DWORD_BYTES
{
	DWORD data;
	BYTE b[4];
};

struct MIDI_DATA
{
	BYTE key;
	BYTE status;
	BYTE reserv1,reserv2;
	DWORD time;
};

double MaxSound=0;	//ìàêñèìàëüíûé óðîâåíü çâóêà íà äàííûé ìîìåíò (äî 32768)

#define GetData UpdateData(true)
#define PutData UpdateData(false)

double Piano(double Ampl, double freq, double t, double phase);

static int _time_;

const double
	
	AMPLITUDE_START=6000;

double	AMPLITUDE_DECREMENT;//5/2048.0;

int IdMidiOpen=-1;

int 
	SAMPLE_RATE=44100,
	BUFFER_MAX=60,
	BUFFER_SIZE=200;

struct KEY
{
	UINT press;
	double decrement;
	double Ampl;

	double t;	//âðåìÿ(â óñëîâíûõ åäèíèöàõ) ñèãíàëà
	double A,D,S,R;	//áëîê ADSR (Attack-Decay-Sustain-Release)
	double A_add;	//ñêîðîñòü óâåëè÷åíèÿ A

	KEY() { press=0; decrement=0; Ampl=0; t=0; A=D=S=R=0; A_add=0;}
} Keys[256];


KEY KeysOld[256];

int KEY_L=14;
int KEY_H=65;

int KEY_X=10;
int KEY_Y=200;


struct _KEYSA_
{
	BYTE code;
	char * help;
};

_KEYSA_ Keysa[]=
{
	{9, "TAB"},
	{'Q', "Q"},
	{'2', "2"},
	{'W', "W"},
	{'3', "3"},
	{'E', "E"},
	{'R', "R"},
	{'5', "5"},
	{'T', "T"},
	{'6', "6"},
	{'Y', "Y"},
	{'7', "7"},
	{'U', "U"},
//	{'8', "8"},
	{'I', "I"},
	{'9', "9"},
	{'O', "O"},
	{'0', "0"},
	{'P', "P"},
	{219, "{"},
	{187, "+"},
	{221, "}"},
	{220, "|"},
	{13, "EN"},
	{8,"BK"},
	{46,"DEL"},
	{35,"END"},
	{36,"HM"},
	{34,"PD"},
	{33,"PU"},
	{103,"7"},
	{104,"8"},
	{111,"/"},
	{105,"9"},
	{106,"*"},
	{107,"+"},
	{109,"-"},
	{'M', "M"},
	{0,0}
};

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDTFM_GeneratorDlg dialog

CDTFM_GeneratorDlg::CDTFM_GeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDTFM_GeneratorDlg::IDD, pParent)
{

	//{{AFX_DATA_INIT(CDTFM_GeneratorDlg)
	i_buffer_count = 0;
	m_blockcounter = 0;
	m_edit = _T("");
	m_midi_open_str = _T("3");
	m_amplitude = _T("32767");
	m_edit_freq = 0.0;
	m_bufer_total_count = 20;
	m_buffer_size = 200;
	m_midi_name = _T("");
	m_slider_decrement_double = 0.0;
	m_base_a = 440.0;
	m_scale = 12;
	m_wave_len = 0.0;
	m_edit_modilation = _T("1");
	m_modulation_wheel = 0;
	m_asio_device = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	BlockCounter=0;
	hWaveOut=0;
	NeedClose=false;
	CurrentDigit=' ';
}

void CDTFM_GeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDTFM_GeneratorDlg)
	DDX_Control(pDX, IDC_SLIDER_TOTAL_VOLUME, m_slider_total_volume);
	DDX_Control(pDX, IDC_EDIT_BASE_A, m_edit_base_a);
	DDX_Control(pDX, IDC_EDIT_STATUS_TEXT, m_status_text);
	DDX_Control(pDX, IDC_AMPLITUDE, m_amplitude_edit);
	DDX_Control(pDX, IDC_EDIT_TOTAL_BUFFER_COUNT, m_edit_total_buffer_count);
	DDX_Control(pDX, IDC_EDIT_BUFFER_SIZE, m_buffer_size_edit);
	DDX_Control(pDX, IDC_EDIT_BUFFER_COUNT, m_buffer_count);
	DDX_Control(pDX, IDC_SLIDERM6, m_slm6);
	DDX_Control(pDX, IDC_SLIDERM5, m_slm5);
	DDX_Control(pDX, IDC_SLIDER6, m_sl6);
	DDX_Control(pDX, IDC_SLIDER5, m_sl5);
	DDX_Control(pDX, IDC_SLIDER_DECREMENT, m_slider_decrement);
	DDX_Control(pDX, IDC_EDIT_MIDI_NAME2, m_midi_name_ctrl);
	DDX_Control(pDX, IDC_STOP_PLAY, m_stop_play);
	DDX_Control(pDX, IDC_BUTTON_PLAY_WRITEN, m_play_writen);
	DDX_Control(pDX, IDC_BUTTON_WRITE_STOP, m_button_write_stop);
	DDX_Control(pDX, IDC_BUTTON_WRITE, m_button_write);
	DDX_Control(pDX, IDC_BUTTON_MIDI_OPEN, m_midi_open);
	DDX_Control(pDX, IDC_BUTTON_MIDI_CLOSE, m_midi_close);
	DDX_Control(pDX, IDC_SLIDERM4, m_slm4);
	DDX_Control(pDX, IDC_SLIDERM3, m_slm3);
	DDX_Control(pDX, IDC_SLIDERM2, m_slm2);
	DDX_Control(pDX, IDC_SLIDER4, m_sl4);
	DDX_Control(pDX, IDC_SLIDER3, m_sl3);
	DDX_Control(pDX, IDC_SLIDER2, m_sl2);
	DDX_Control(pDX, IDC_SLIDER1, m_sl1);
	DDX_Control(pDX, IDC_STOP, m_stop);
	DDX_Control(pDX, IDOK, m_generate);
	DDX_Text(pDX, IDC_EDIT_BUFFER_COUNT, i_buffer_count);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	DDX_Text(pDX, IDC_EDIT_MIDI_OPEN, m_midi_open_str);
	DDX_Text(pDX, IDC_AMPLITUDE, m_amplitude);
	DDX_Text(pDX, IDC_EDIT_FREQ, m_edit_freq);
	DDX_Text(pDX, IDC_EDIT_TOTAL_BUFFER_COUNT, m_bufer_total_count);
	DDX_Text(pDX, IDC_EDIT_BUFFER_SIZE, m_buffer_size);
	DDX_Text(pDX, IDC_EDIT_MIDI_NAME2, m_midi_name);
	DDX_Text(pDX, IDC_EDIT_SLIDER_DECREMENT, m_slider_decrement_double);
	DDX_Text(pDX, IDC_EDIT_BASE_A, m_base_a);
	DDX_Text(pDX, IDC_EDIT_SCALE, m_scale);
	DDX_Text(pDX, IDC_EDIT_WAVE_LEN, m_wave_len);
	DDX_Text(pDX, IDC_EDIT_MODULATION, m_edit_modilation);
	DDX_Text(pDX, IDC_EDIT_MODULATION_WHEEL, m_modulation_wheel);
	DDX_Text(pDX, IDC_EDIT_ASIO_DEVICE, m_asio_device);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDTFM_GeneratorDlg, CDialog)
	//{{AFX_MSG_MAP(CDTFM_GeneratorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_PLAY_STRING, OnPlayString)
	ON_BN_CLICKED(IDC_ABORT, OnAbort)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MIDI_CLOSE, OnButtonMidiClose)
	ON_BN_CLICKED(IDC_BUTTON_MIDI_OPEN, OnButtonMidiOpen)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, OnButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_STOP, OnButtonWriteStop)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_WRITEN, OnButtonPlayWriten)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_CLOSE, OnClose2)
	ON_WM_CHAR()
	ON_BN_CLICKED(IDC_STOP_PLAY, OnStopPlay)
	ON_BN_CLICKED(IDC_HIDE, OnHide)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDTFM_GeneratorDlg message handlers


























































int sl1, sl2, sl3, sl4, sl5, sl6;
int slm2, slm3, slm4, slm5, slm6;
int slvolume;

//ôóíêöèÿ âû÷èñëÿåò ñóììó ñèíóñîâ 
//ñèãíàë â ñîîòâåòñòâèè ñ ýêâàëàéçåðîì â ãðàôè÷åñêîì èíòåðôåéñå ïðîãðàììû
//Ampl àìïëèòóäà
//freq ÷àñòîòà
//flag_one ÷èñëî èñïîëüçóåìûõ è âû÷èñëåííûõ ãàðìîíèê

//freq_actual çàïèñûâàåòñÿ ïîñëåäíÿÿ âû÷èñëåííàÿ ÷àñòîòà
//åñëè flag_one==1, çíà÷èò áûëà èñïîëüçîâàíà òîëüêî îäíà ãàðìîíèêà,
//à îñòàëüíûå ñëàéäåðû îïóùåíû âíèç
double Piano(double Ampl, double freq, double t, double phase, int & flag_one, double & freq_actual)
{

	flag_one=0;

	if (sl1) {flag_one++;freq_actual=freq;}	//base frequency
	if (sl2) {flag_one++;freq_actual=freq*2;}
	if (sl3) {flag_one++;freq_actual=freq*3;}
	if (sl4) {flag_one++;freq_actual=freq*4;}
	if (sl5) {flag_one++;freq_actual=freq*5;}
	if (sl6) {flag_one++;freq_actual=freq*6;}

	if (slm2) {flag_one++;freq_actual=freq/2;}
	if (slm3) {flag_one++;freq_actual=freq/3;}
	if (slm4) {flag_one++;freq_actual=freq/4;}
	if (slm5) {flag_one++;freq_actual=freq/5;}
	if (slm6) {flag_one++;freq_actual=freq/6;}

	double k=0;	//èòîãîâàÿ âû÷èñëåííàÿ ñóììà 

	double limit=20000;	//îãðàíè÷åíèå ÷àñòîòû

	double AMP=Ampl;
	AMP+=30000*sin(modulation);

	double f;	//÷àñòîòà

	//åñëè ïîäíÿò ïåðâûé ñëàéäåð (áàçîâàÿ ãàðìîíèêà)
	if (sl1)
	{
		//f=1*freq;
		//if (f<limit) k+=sl1/100.0*AMP*sin(f*t);
		k+=sl1/100.0*sin(freq*t);
	}

	//åñëè ïîäíÿò âòîðîé ñëàéäåð (âòîðàÿ ãàðîìíèêà, â 2 ðàçà âûøå áàçîâîé)
	if (sl2)
	{
		f=2*freq;
		if (f<limit) k+=sl2/100.0*sin(f*t);
	}

	if (sl3)
	{
		f=3*freq;
		if (f<limit) k+=sl3/100.0*sin(f*t);
	}

	if (sl4)
	{
		f=4*freq;
		if (f<limit) k+=sl4/100.0*sin(f*t);
	}

	if (sl5)
	{
		f=5*freq;
		if (f<limit) k+=sl5/100.0*sin(f*t);
	}

	if (sl6)
	{
		f=6*freq;
		if (f<limit) k+=sl6/100.0*sin(f*t);
	}


	//â äâà è áîëåå ðàçà ìåíüøèå ãàðìîíèêè
	if(slm2) k+=slm2/100.0*sin(freq/2*t);
	if(slm3) k+=slm3/100.0*sin(freq/3*t);
	if(slm4) k+=slm4/100.0*sin(freq/4*t);
	if(slm5) k+=slm5/100.0*sin(freq/5*t);
	if(slm6) k+=slm6/100.0*sin(freq/6*t);

	
/*for(int i=2; i<2; i++)
	{
		k+=Ampl/i*sin(i*freq*t+0.3*i);
	}

	for(i=2; i<2; i++)
	{
		k+=Ampl/i*sin(freq/i*t+0.3*i);
	}
*/

	return k *  (slvolume/100.0) * AMP  ;
}







































































BOOL CDTFM_GeneratorDlg::OnInitDialog()
{
	InitToneData();
	CDialog::OnInitDialog();



	OnOK();

	m_sl1.SetScrollRange(SB_CTL,0,100);
	m_sl2.SetScrollRange(SB_CTL,0,100);
	m_sl3.SetScrollRange(SB_CTL,0,100);
	m_sl4.SetScrollRange(SB_CTL,0,100);
	m_sl5.SetScrollRange(SB_CTL,0,100);
	m_sl6.SetScrollRange(SB_CTL,0,100);


	m_slm2.SetScrollRange(SB_CTL,0,100);
	m_slm3.SetScrollRange(SB_CTL,0,100);
	m_slm4.SetScrollRange(SB_CTL,0,100);
	m_slm5.SetScrollRange(SB_CTL,0,100);
	m_slm6.SetScrollRange(SB_CTL,0,100);


	m_slider_decrement.SetScrollRange(SB_CTL,0, 100);
	m_slider_total_volume.SetScrollRange(SB_CTL,0, 100);

	if (ini.IsExist())
//	if (0)
	{

	m_sl1.SetPos(100-ini.QueryValue("sl1"));
	m_sl2.SetPos(100-ini.QueryValue("sl2"));
	m_sl3.SetPos(100-ini.QueryValue("sl3"));
	m_sl4.SetPos(100-ini.QueryValue("sl4"));
	m_sl5.SetPos(100-ini.QueryValue("sl5"));
	m_sl6.SetPos(100-ini.QueryValue("sl6"));


	m_slm2.SetPos(100-ini.QueryValue("slm2"));
	m_slm3.SetPos(100-ini.QueryValue("slm3"));
	m_slm4.SetPos(100-ini.QueryValue("slm4"));
	m_slm5.SetPos(100-ini.QueryValue("slm5"));
	m_slm6.SetPos(100-ini.QueryValue("slm6"));


	m_slider_decrement.SetPos(100-ini.QueryValue("sldecrement"));
	m_slider_total_volume.SetPos(ini.QueryValue("sltotalvolume"));

	}
	else
	{
		m_sl1.SetPos(0);
		m_sl2.SetPos(100);
		m_sl3.SetPos(100);
		m_sl4.SetPos(100);
		m_sl5.SetPos(100);
		m_sl6.SetPos(100);


		m_slm2.SetPos(100);
		m_slm3.SetPos(100);
		m_slm4.SetPos(100);
		m_slm5.SetPos(100);
		m_slm6.SetPos(100);

		m_slider_decrement.SetPos(10);
		m_slider_total_volume.SetPos(100);

	}
	

	SetTimer(0,500,NULL);
	//SetTimer(1,100,NULL);

	OnButtonMidiOpen();

	SetWindowText("Midi In Piano");

	if (ini.QueryValue("HideWindow")==1)
	{
		ShowWindow(SW_HIDE);
	}


//BOOL SetPriorityClass(
//  HANDLE hProcess,        // handle to process
//  DWORD dwPriorityClass   // priority class
//);
	HANDLE hProcess=GetCurrentProcess();
	SetPriorityClass(hProcess,HIGH_PRIORITY_CLASS);

	//HANDLE hThread=GetCurrentThread();

	//SetThreadPriority(hThread, THREAD_PRIORITY_HIGHEST);
	
	return FALSE;
}














































void CDTFM_GeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}






















































void CDTFM_GeneratorDlg::OnPaint() 
{

	change=true;

	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}






























// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDTFM_GeneratorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




























































void CDTFM_GeneratorDlg::OnOK() 
{
	if (!GetData) return;

	scale=pow(2.0,1.0/m_scale);

	BASE_A=m_base_a;

	mode=0;
	
	int channels=1;	//÷èñëî êàíàëîâ
	samplerate=SAMPLE_RATE;	//÷àñòîòà äèñêðåòèçàöèè
	//ïî çàêîíó äîëæíà áûòü êàê ìèíèìóì â äâà ðàçà âûøå ìàêñèìàëüíî èñïîëüçóåìîé

	WAVEFORMATEX wform;	//ôîðìàò äàííûõ óñòðîéñòâà
	wform.wFormatTag=WAVE_FORMAT_PCM;	//èñïîëüçóåòñÿ PCM-äàííû
	wform.nChannels=WORD(channels);			 //ìîíî (1 êàíàë)
	wform.nSamplesPerSec=samplerate;	//÷àñòîòà äèñêðåòèàçàöèè
	wform.nAvgBytesPerSec=samplerate*channels;	//ñêîðîñòü ïîòîêà äàííûõ (äëÿ ìîíî
	//wform.nBlockAlign=(1*8)/8;	//âûðàâíèâàíèå áëîêà äàííûõ
	wform.nBlockAlign=2;	//âûðàâíèâàíèå áëîêà äàííûõ
	wform.wBitsPerSample=16;		//÷èñëî áèòîâ íà âûáîðêó

	//ïûòàåìñÿ îòêðûòü wave-device
	UINT rc=waveOutOpen(&hWaveOut, WAVE_MAPPER, &wform, (DWORD) m_hWnd,0, CALLBACK_WINDOW);

	//íåóäà÷à ?
	if (rc) {
		TextError(rc);
		return;
	}

	BUFFER_MAX=m_bufer_total_count;
	BUFFER_SIZE=m_buffer_size;
	//waveOutPause(hWaveOut);
	for(int i=0; i<BUFFER_MAX; i++) AddBuffer(0,0,0, BUFFER_SIZE);
	//waveOutRestart(hWaveOut);

	m_generate.EnableWindow(false);
	m_stop.EnableWindow();

	m_buffer_size_edit.EnableWindow(false);
	m_edit_total_buffer_count.EnableWindow(false);
	m_amplitude_edit.EnableWindow(false);
	m_edit_base_a.EnableWindow(false);

	SetFocus();
}


























struct TONEDATA
{
	double f1;
	BYTE sym;
	int idc;
};


































const double DO=1, RE=9/8.0, ME=5/4.0, FA=4/3.0, SOL=3/2.0, LA=5/3.0, SI=15/8.0;

//const double DIES=6/5.0;	//=1.2

const DigitCount=250;
TONEDATA digit[DigitCount]=
{
	{ DO*1,		60,	IDC_DO },		//do
	{ DO*2,		61,	IDC_DO_DIES,},	//DO dies
	{ DO*3,		62,	IDC_RE},		//re
	{ DO*4,		63,	IDC_RE_DIES,},	//re dies
	{ DO*5,		64,	IDC_ME },		//me
	{ DO*6,		65,	IDC_FA },		//fa
	{ DO*7,		66,	IDC_FA_DIES,},	//fa dies
	{ DO*8,		67,	IDC_SOL },		//sol
	{ DO*9,		68,	IDC_SOL_DIES,},	//sol dies
	{ DO*10,	69,	IDC_LA },		//la
	{ DO*11,	70, IDC_LA_DIES,},	//la dies
	{ DO*12,	71,	IDC_SI },		//si

	{ DO*13, 72, IDC_DO2 },
	{ DO*14, 73, IDC_DO2_DIES,},	
	{ DO*15, 74, IDC_RE2 },
	{ DO*16, 75, IDC_RE2_DIES},
	{ DO*17, 76, IDC_ME2 },
	{ DO*18, 77, IDC_FA2 },
	{ DO*19, 78, IDC_SOL2 }
};













































BOOL CDTFM_GeneratorDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == MM_WOM_DONE)
	{
		WAVEHDR *wh=(WAVEHDR*) pMsg->lParam;
		TextError(waveOutUnprepareHeader(hWaveOut, wh,
			sizeof(WAVEHDR)));
		
		BlockCounter--;

		//GetData;
		i_buffer_count=BlockCounter;
		//PutData;

		int bufsize=wh->dwBufferLength;

		if (mode==MODE_NEED_CLOSE_WAVEOUT && !BlockCounter)
		{
			TextError(waveOutClose(hWaveOut));
			hWaveOut=0;
			
			//????????????
			m_stop.EnableWindow(false);
			m_generate.EnableWindow(true);

			m_buffer_size_edit.EnableWindow(true);
			m_edit_total_buffer_count.EnableWindow(true);
			m_amplitude_edit.EnableWindow(true);
			m_edit_base_a.EnableWindow(true);

			
			SetFocus();
		}

		if (BlockCounter==0 && NeedClose==true) 
		{
			OnClose();
		}
		delete wh->lpData;
		delete wh;

		//äîáàâëÿåì â î÷åðåäü íîâûé áóôåð!!!!!!!!!!!!
		//åñëè íå íóæíî çàêðûâàòü
		if (mode==0)
		{
			AddBuffer();
		}

	}

	UINT nChar=pMsg->wParam;


	
	if (pMsg->message == WM_KEYDOWN && hWaveOut)
	{

		// (nChar==VK_UP)
		//
		//etKeys(0, 4000);
		//}


		if (nChar==VK_LEFT)
		{

			if (BaseKeyboard>0) BaseKeyboard--;
		
			change=true;

			CDC *pdc=GetDC();
			DrawButton(pdc, 0,0, 60);
			ReleaseDC(pdc);
		}

		if (nChar==VK_RIGHT)
		{

			if (BaseKeyboard<127) BaseKeyboard++;

			change=true;
			CDC *pdc=GetDC();
			DrawButton(pdc, 0,0, 60);
			ReleaseDC(pdc);

		}

		//OnChar(nChar,0,0);
		for(int i=0; i<256; i++)
		{
			if (Keysa[i].code==0) break;
			if (Keysa[i].code==nChar)
			{
				int r=i+BaseKeyboard;

				MidiKeyPress(r,127);
			}

		}

		return 0;
	}

	if (pMsg->message == WM_KEYUP && hWaveOut)
	{
		//OnChar(nChar,0,0);
		for(int i=0; i<256; i++)
		{
			if (Keysa[i].code==0) break;
			if (Keysa[i].code==nChar)
			{
				int r=i+BaseKeyboard;
				MidiKeyPress(r,0);
			}

		}

		return 0;
	}


	//return CDialog::PreTranslateMessage(pMsg);

	return 0;
}















































double freq_1=0;
int freq_1_count=0;
double old_base_a=440;

void FillBuffer(short *plbuf, int size, int samplerate)
{

	freq_1=0;
	freq_1_count=0;
	static int last_z=0;
	int delta=0;

	double K=2*PI/samplerate;
	double t=_time_*K;


	double m=0;
	for(int i=0; i<size/2; i++, _time_++)
	{

		m=0;

		modulation+=step_modulation;

		for(int k=0; k<128; k++) 
		{
			if (Keys[k].press) 
			{
				double freq=BASE_A*pow(scale,k-60+3);
				

				int flag_one=1;

				double freq_actual=0;

				static double phase;
				phase=0;

				m+=Piano(Keys[k].Ampl,freq,Keys[k].t,phase, flag_one, freq_actual);
				
				Keys[k].t+=K;

				Keys[k].Ampl+=Keys[k].A_add;

				if (Keys[k].Ampl > Keys[k].A)
				{
					Keys[k].A_add=0;
				}
				
				Keys[k].Ampl-=Keys[k].decrement;

				if (flag_one==1)
				{
					if (Keys[k].Ampl)
					{
						freq_1=freq_actual;
						freq_1_count++;
					}

				}
			}
			
		}
		
		t+=K;


		static double CorrectAmplitude=1;

		m*=CorrectAmplitude;

		if (m>32767) 
		{
			m=32767;
			Overload=true;
			CorrectAmplitude-=0.01;
		}

		if (m < - 32767) 
		{
			m = -32767;
			Overload=true;
			CorrectAmplitude-=0.01;
		}

		if (Overload) 
		{

			if (CorrectAmplitude<0) CorrectAmplitude=0.1;
		}

		if (m>MaxSound) MaxSound=m;

		short int z=(short int)m;

		plbuf[i]=z;
	}

}


extern int ASIO_buflen;
extern DWORD ASIO_PROC_BUFLEN;

void CDTFM_GeneratorDlg::AddBuffer()
{
	WAVEHDR * wh1=new WAVEHDR;
	WAVEHDR& wh=*wh1;

	int size=BUFFER_SIZE;
	BYTE *plbuf=new BYTE[size];


	ZeroMemory(plbuf,size);

	double m=0;

	//MaxSound=0;
	//Overload=0;

	/*
	for(int i=0; i<size; i+=2, _time_++)
	{
		double t=_time_*2*PI/samplerate;

		m=0;
		for(int k=0; k<256; k++) 
		{
			if (Keys[k].press) 
			{
				double freq=BASE_A*pow(scale,k-60+3);
				

				int flag_one=0;

				double freq_actual=0;

				static double phase;
				phase=0;
				m+=Piano(Keys[k].Ampl,freq,t,phase, flag_one, freq_actual);
				//m+=0;

				if (flag_one==1)
				{
					if (Keys[k].Ampl)
					{
						freq_1=freq_actual;
						freq_1_count++;
					}

				}
			}
		}


		//m*=2;

		if (m>32767) 
		{
			m=32767;
			Overload=true;
		}

		if (m < - 32767) 
		{
			m = -32767;
			Overload=true;
		}

		if (m>MaxSound) MaxSound=m;

		short int z=(short int)m;

		BYTE *s=(BYTE*)&z;

		plbuf[i+0]=s[0];
		plbuf[i+1]=s[1];
	}


	*/

//	double SumAmpl=0;

	for(int i=0; i<256; i++)
	{
//		SumAmpl+=Keys[i].Ampl;

//		if (Keys[i].Ampl>0) 
//		{
//			Keys[i].Ampl-=Keys[i].decrement;
//		}

		if (Keys[i].Ampl<=0) 
		{
			Keys[i].Ampl=0;
			Keys[i].decrement=0;
			Keys[i].press=0;
			Keys[i].t=0;
		}
	}
	
//	if (fabs(SumAmpl)<1) 
//	{
//		_time_=0;
//	}

	wh.dwFlags=0;
	wh.dwBufferLength=size;
	wh.dwLoops=1;
	wh.lpData=(char*)plbuf;
	wh.dwUser='b';

	int rc;
	
	rc=waveOutPrepareHeader(hWaveOut, &wh, sizeof(wh));
	TextError(rc);

	rc=waveOutWrite(hWaveOut, &wh, sizeof(wh));
	TextError(rc);

	BlockCounter++;

//	GetData;

	m_blockcounter=BlockCounter;

	//åñëè ãåíåðèðóåòñÿ ÷èñòî ñèíóñîèäàëüíûé ñèãíàî
	if (freq_1_count==int(ASIO_PROC_BUFLEN/2)) 
	{
		m_edit_freq=freq_1;
		m_wave_len=330.0/freq_1;//äëèíà âîëíû
	}
	else 
	{
		m_edit_freq=-1;
		m_wave_len=-1;
	}
	
	PutData;

	if (Keys[60].press && Keys[60+12].press)
	{
		ini.SetValue(0,"HideWindow");
	}
}













































































void CDTFM_GeneratorDlg::AddBuffer(double freq1, double freq2, char sym, int size)
{
	WAVEHDR * wh1=new WAVEHDR;
	WAVEHDR& wh=*wh1;

//	int size=1024;
	BYTE *plbuf=new BYTE[size];

	for(int i=0; i<size; i++)
	{
		plbuf[i]=0;
	}

	wh.dwFlags=0;//WHDR_BEGINLOOP | WHDR_ENDLOOP;
	wh.dwBufferLength=size;
	wh.dwLoops=1;
	wh.lpData=(char*)plbuf;
	wh.dwUser=sym;

	int rc=waveOutPrepareHeader(hWaveOut, &wh, sizeof(wh));
	TextError(rc);

	rc=waveOutWrite(hWaveOut, &wh, sizeof(wh));

	TextError(rc);

	BlockCounter++;
}





































void CDTFM_GeneratorDlg::OnClose() 
{
	if (!BlockCounter) 
	{

		OnButtonMidiClose();

		ExitDialog();
	}
	else
	{
		mode=MODE_NEED_CLOSE_WAVEOUT;
		NeedClose=true;
	}
}



















































void CDTFM_GeneratorDlg::OnStop() 
{
	if (BlockCounter) mode=MODE_NEED_CLOSE_WAVEOUT;

	GetData;
	i_buffer_count=BlockCounter;
	PutData;

	if (BlockCounter==0)
	{
		//m_generate.EnableWindow();
		//m_stop.EnableWindow(false);

		//m_buffer_size_edit.ShowWindow(SW_HIDE);
		//m_edit_total_buffer_count.ShowWindow(0);


		SetFocus();
		TextError(waveOutClose(hWaveOut));

		hWaveOut=0;
	}
}







































int CDTFM_GeneratorDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

// TODO: Add your specialized creation code here
//	CheckRadioButton(IDC_RADIO_CONSTANT,IDC_RADIO_CONSTANT,IDC_RADIO_CONSTANT);
	
	return 0;
}































BOOL CDTFM_GeneratorDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	return CDialog::Create(IDD, pParentWnd);
}

//void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//}













































void CDTFM_GeneratorDlg::ExitDialog()
{
	GetData;


	ini.SetValue(100-m_sl1.GetPos(),"sl1");
	ini.SetValue(100-m_sl2.GetPos(),"sl2");
	ini.SetValue(100-m_sl3.GetPos(),"sl3");
	ini.SetValue(100-m_sl4.GetPos(),"sl4");
	ini.SetValue(100-m_sl5.GetPos(),"sl5");
	ini.SetValue(100-m_sl6.GetPos(),"sl6");


	ini.SetValue(100-m_slm2.GetPos(),"slm2");
	ini.SetValue(100-m_slm3.GetPos(),"slm3");
	ini.SetValue(100-m_slm4.GetPos(),"slm4");
	ini.SetValue(100-m_slm5.GetPos(),"slm5");
	ini.SetValue(100-m_slm6.GetPos(),"slm6");


	ini.SetValue(100-m_slider_decrement.GetPos(), "sldecrement");

	//????
	ini.SetValue(m_slider_total_volume.GetPos(), "sltotalvolume");

	
	EndDialog(0);
}




















































void CDTFM_GeneratorDlg::OnPlayString() 
{
}

void CDTFM_GeneratorDlg::OnAbort() 
{
	OnButtonMidiClose();
	CDialog::OnOK();
}

void CDTFM_GeneratorDlg::TextError(MMRESULT rc)
{
	if (!rc) return;
	char buf[8192];
	waveOutGetErrorText(rc, buf,8192);
	//MessageBox(buf);
}	

BOOL CDTFM_GeneratorDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	return CDialog::OnCommand(wParam, lParam);
}










































LRESULT CDTFM_GeneratorDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	
	return CDialog::WindowProc(message, wParam, lParam);
}






























void CDTFM_GeneratorDlg::InitToneData()
{
}























































void DrawButton(CDC *dc, int x, int y, int start)
{
	CBrush br_level,br2;
	br2.CreateSolidBrush(RGB(250,250,250));
	//br_level.CreateSolidBrush(RGB(255*MaxSound/32768.0,0,0));
	br_level.CreateSolidBrush(RGB(255,0,0));
	dc->SelectObject(br_level);

	int L;
	int H;

	x=10;
	y=180;

	L=300;
	H=10;

	if (Overload)
	{
		dc->SelectObject(br_level);
		dc->Rectangle(x+L+2,y,x+L+2+10,y+H);	
	}
	else
	{
		dc->SelectObject(br2);
		dc->Rectangle(x+L+2,y,x+L+2+10,y+H);	
	}

	//if (MaxSound)
	{
		int k=int(MaxSound/32768.0*L);

		dc->SelectObject(br_level);
		dc->Rectangle(x,y,x+k,y+H);
		dc->SelectObject(br2);
		dc->Rectangle(x+k,y,x+L,y+H);
	}


	for(int i=0; i<256; i++)
	{
		if ( (KeysOld[i].press!=Keys[i].press) 
			|| KeysOld[i].Ampl != Keys[i].Ampl) change=true;
	}

	if (change)
	{
		for(i=0; i<256; i++) KeysOld[i]=Keys[i];
	}
	else return;

	change=false;


	L=KEY_L;
	H=KEY_H;

	y=KEY_Y;
	x=KEY_X;


	CBrush br_red,br_bl;
	br_red.CreateSolidBrush(RGB(0,250,200));
	
	br_bl.CreateSolidBrush(RGB(10,10,10));



	int Z[]={0,2,4,5,7,9,11};
	int R[]={1,3,6,8,10};

	/*CFont font;
	LOGFONT lf={0};
	lf.lfWidth=L-5;
	lf.lfHeight=lf.lfWidth*2;
	font.CreateFontIndirect(&lf);
	dc->SelectObject(font);

	dc->SetBkMode(TRANSPARENT);
	*/

	start=12;

//	CBrush * oldbr=dc->SelectObject(&br_red);

	for(int T=0; T<10; T++)
	{
		for(int i=0; i<7; i++)
		{
			CBrush bra;
			int RR=start+ Z[i];
			if (RR>127) continue;
			int ampl=int(Keys[RR].Ampl);

			int a=250*ampl/4000;
			if (a>250) a=250;
			int b=200*ampl/4000;
			if (b>200) b=200;

			bra.CreateSolidBrush(RGB(0,a,b));

			if (Keys[RR].press)
				dc->SelectObject(bra);
			else
				dc->SelectObject(br2);

			int x1=x+L*i;

			dc->Rectangle(x1,y,x+L*i+L, y+H);

			if ( RR==BaseKeyboard)
			{
				dc->Ellipse(x1+3, y+H-1, x1+L-6, y+H-8);
			}

			//dc->TextOut(x1+1,y+H-lf.lfHeight,"A");
		}

		int p=0;
		for(i=0; i<7; i++)
		{
			int RR=start+ R[p];
			if (RR>127) continue;

			int L2=int(L*0.6);
			int H2=int(H*0.6);
			if (scale != pow(2,1/12.0)) H2=H;
			if (i==2 || i==6) continue;
			int s=(2*L-L2)/2;

			if (Keys[RR].press)
				dc->SelectObject(br_red);
			else
				dc->SelectObject(br_bl);

			int x1=x+s+L*i;


			dc->Rectangle(x1,y,x+s+L*i+L2, y+H2);

			if ( RR==BaseKeyboard)
			{
				dc->SelectObject(br2);
				dc->Ellipse(x1+1, y+H-1, x1+L2, y+H-8);
			}

			p++;

		}

		x+=L*7;
		
		start+=12;
	}

//	dc->SelectObject(oldbr);
}







































void CDTFM_GeneratorDlg::OnTimer(UINT nIDEvent) 
{

	GetData;

	CString s=m_edit_modilation;
	
	
	double modul=strtod(s.GetBuffer(0),NULL);

	ModulationWheel=modul;

	m_modulation_wheel=m_modulation_wheel_2;
	

	if (NeedUpdateMidiEvent)
	{
		//îáíîâëÿåì åñëè åñòü èçìåíåíèÿ
		if (m_edit!=m_edit_list_midi)
		{
			m_edit=m_edit_list_midi;
			PutData;
		}
	}

	hWaveOut_global=hWaveOut;
	m_amplitude_global=m_amplitude;


	CurrentAmplitude=atoi(m_amplitude);

	sl1=100-m_sl1.GetPos();
	sl2=100-m_sl2.GetPos();
	sl3=100-m_sl3.GetPos();
	sl4=100-m_sl4.GetPos();
	sl5=100-m_sl5.GetPos();
	sl6=100-m_sl6.GetPos();


	slm2=100-m_slm2.GetPos();
	slm3=100-m_slm3.GetPos();
	slm4=100-m_slm4.GetPos();
	slm5=100-m_slm5.GetPos();
	slm6=100-m_slm6.GetPos();
	slvolume=m_slider_total_volume.GetPos();


	AMPLITUDE_DECREMENT=(m_slider_decrement.GetPos()*2+1)/128.0;

	m_slider_decrement_double=AMPLITUDE_DECREMENT;


	CDC *pdc=GetDC();
	DrawButton(pdc, 0,0, 60);
	ReleaseDC(pdc);



	if (ini.QueryValue("HideWindow")) ShowWindow(SW_HIDE);
	else ShowWindow(SW_SHOW);

	CDialog::OnTimer(nIDEvent);

	MaxSound=0;
	Overload=0;

}








































void CDTFM_GeneratorDlg::OnButtonMidiClose() 
{
	if (hmidiIn!=NULL)
	{
		int err=midiInStop(hmidiIn);

		if (err!=MMSYSERR_NOERROR) 
		{
			m_midi_name="Îøèáêà midiInStop";
			return;
		}

		err=midiInClose(hmidiIn);
		if (err!=MMSYSERR_NOERROR) 
		{
			m_midi_name="Îøèáêà midiInClose";
		}

		m_midi_close.EnableWindow(false);
		m_midi_open.EnableWindow(true);
		SetFocus();

		m_midi_name="midi close";

		PutData;

		hmidiIn=NULL;

		OnStop();

	}
	
}


























//ïðèåì ìèäè ñîîáùåíèé
void CALLBACK MidiInProc(
   HMIDIIN   hMidiIn,
   UINT      wMsg,
   DWORD  dwInstance,
   DWORD dwParam1,
   DWORD dwParam2
)
{
	if (wMsg == MM_MIM_DATA)
	{
		DWORD_BYTES mm;
		mm.data=dwParam1;

		if (mm.b[0] != 254)
		{
			//GetData;
			
			if (NeedUpdateMidiEvent)
			{
				CString s;
				s.Format("%i,%i\t%i\t%i\t%i",mm.b[0]>>4,mm.b[0]&15,mm.b[1],mm.b[2],mm.b[3]);

				static counter=0;
				counter++;
				if ( (counter %10) == 0)
				{
					m_edit_list_midi="";
				}

				m_edit_list_midi += s+ENDL;
			}

			//CDC *dc;//new CDC;
			//dc->TextOut(0,0,s);

			BYTE nChar=mm.b[1];
			BYTE Volume=mm.b[2];

			int z=mm.b[0]>>4;


			if (NeedUpdateModulation)
			{
				if (z==11 && nChar==1)
				{
					//??????ÂÀÆÍÎ
					//step_modulation=ModulationWheel * Volume/127.0/2048.0;
					step_modulation=ModulationWheel * Volume/127.0/512;
					m_modulation_wheel_2=Volume;
				}
			}

			if (NeedUpdateBaseFreq)
			{
				if (z==11 && nChar==7)
				{
					//????????
					BASE_A=440+Volume;
				}
			}

			if ((mm.b[0]>>4) == 9 || (mm.b[0]>>4) == 8)
			{
				if (nChar<256) 
				{
					MidiKeyPress2(nChar, Volume);
				}
			}
			//UpdateData(false);
		}
		//return 1;

	}

	if (wMsg == MM_MIM_LONGDATA)
	{
		int b=3;
		b++;
	}


}












void CDTFM_GeneratorDlg::OnButtonMidiOpen() 
{
	GetData;

	if (hmidiIn!=NULL) return;

	int err;

	int midicount=midiInGetNumDevs();

	MIDIINCAPS mic={0};

	
	IdMidiOpen=atoi(m_midi_open_str);

	
	m_midi_open_str.Format("%i",IdMidiOpen);

	midiInGetDevCaps(IdMidiOpen,&mic,sizeof(mic));

	//err=midiInOpen(&hmidiIn, IdMidiOpen, (DWORD) this->m_hWnd, 0, CALLBACK_WINDOW);
	err=midiInOpen(&hmidiIn, IdMidiOpen, (DWORD)MidiInProc, 0, CALLBACK_FUNCTION);

	if (err==MMSYSERR_NOERROR)
	{
		m_midi_name=mic.szPname;
		PutData;
	}

	if (err!=MMSYSERR_NOERROR)
	{
		m_midi_name="MidiInOpen error";

		PutData;

		//midiInClose(hmidiIn);
		hmidiIn=NULL;
		return;
	}

	err=midiInStart(hmidiIn);
	if (err!=MMSYSERR_NOERROR)
	{
		m_midi_name="MidiInStart error";
		PutData;

		midiInClose(hmidiIn);
		hmidiIn=NULL;
		return;
	}


	m_midi_open.EnableWindow(false);
	m_midi_close.EnableWindow(true);
	OnOK();
	SetFocus();

	PutData;
}















































void CDTFM_GeneratorDlg::OnButtonWrite() 
{
	DeleteFile("midi.dat");
	if (file.Open("midi.dat",file.modeWrite|file.modeCreate))
	{
		m_button_write.EnableWindow(false);
		m_button_write_stop.EnableWindow(true);
		SetFocus();
		write=true;


		CStdioFile f;
		f.Open("notes.h", file.modeWrite | file.modeCreate);
		f.WriteString("int KEYS[][2]={\n");
		f.Close();

	}
	else
	{
		//MessageBox("File busy");
	}
	
}



























































void CDTFM_GeneratorDlg::OnButtonWriteStop() 
{
	m_button_write.EnableWindow(true);
	m_button_write_stop.EnableWindow(false);
	SetFocus();
	write=false;
	file.Close();


	CStdioFile f;
	if (f.Open("notes.h", file.modeWrite))
	{
		f.SeekToEnd();

	
		
		f.WriteString("{255, 0}\n};");
		
		
		f.Close();
	}




	
}

DWORD START_TIME;





























































void CALLBACK TimerProc_PlayMidi(
  HWND hwnd,         // handle to window
  UINT uMsg,         // WM_TIMER message
  UINT_PTR idEvent,  // timer identifier
  DWORD dwTime       // current system time
)
{
/* 	if (PlayWritenPosition*sizeof(MIDI_DATA)>=PlayWritenSize)
	{
		//KillTimer(5555);
		//::KillTimer(NULL,5555);
		PlayWritenPosition=0;
		START_TIME=GetTickCount();
		return;
	}

	int j=PlayWritenPosition;
	//MIDI_DATA *md=(MIDI_DATA*) &PlayWriten;
	MIDI_DATA *md=(MIDI_DATA*) PlayWriten;
	//md+=PlayWritenPosition;

	double K=1;
	double delta=(md[j].time - md[0].time)*K;
	double delta2=GetTickCount()-START_TIME;
	if ( delta <= delta2)
	{
		BYTE nChar=md[j].key;
		if (md[j].status>0)
		{

			Keys[nChar].press=1;
			Keys[nChar].Ampl=md[j].status*CurrentAmplitude/127;
			Keys[nChar].decrement=0;
		}
		else
		{
			Keys[nChar].decrement=AMPLITUDE_DECREMENT;
		}
		PlayWritenPosition++;

	}
*/	
}



































































void CDTFM_GeneratorDlg::OnButtonPlayWriten() 
{
	if (PlayWriten) return;

/*	HRSRC hr=FindResource(NULL,"IDR_USER","USERDATA");
	int err=GetLastError();

	HGLOBAL hgl=LoadResource(NULL,hr);
	BYTE *bufz=(BYTE*)LockResource(hgl);

	int size2=SizeofResource(NULL,hr);

	
	PlayWriten=new BYTE[size2];
	PlayWritenSize=size2;
	memcpy(PlayWriten,bufz,size2);
	
	UnlockResource(bufz);
*/

	CFile f;
	if (!f.Open("midi.dat",file.modeRead)) return;
	int size=f.GetLength();
	PlayWriten=new BYTE[size];
	PlayWritenSize=size;
	if (PlayWriten==NULL)
	{
		PlayWritenSize=0;
		f.Close();
		return;
	}

	f.Read(PlayWriten, PlayWritenSize);
	f.Close();


	m_play_writen.EnableWindow(false);
	m_stop_play.EnableWindow(true);
	SetFocus();


	PlayWritenPosition=0;

	START_TIME=GetTickCount();

	SetTimer(5555,1, (TIMERPROC)TimerProc_PlayMidi);

}












































void CDTFM_GeneratorDlg::OnButtonReset() 
{
	for(int i=0; i<256; i++)
	{
		Keys[i].Ampl=0;
		Keys[i].press=0;
		Keys[i].t=0;
	}
}

void CDTFM_GeneratorDlg::OnMove(int x, int y) 
{
//	CDialog::OnMove(x, y);
	
	
}

void CDTFM_GeneratorDlg::OnClose2() 
{
	OnClose();
}

void CDTFM_GeneratorDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}




































void CDTFM_GeneratorDlg::OnStopPlay() 
{
	delete PlayWriten;
	PlayWriten=NULL;

	m_stop_play.EnableWindow(false);
	m_play_writen.EnableWindow(true);
	SetFocus();
	OnButtonReset();

	KillTimer(5555);
}





















































void CDTFM_GeneratorDlg::SetFocus()
{
	m_midi_name_ctrl.SetFocus();
}


















































void MidiKeyPress2(BYTE key, BYTE value)
{

	if (hWaveOut_global==NULL) return;

	if (value!=0)
	{
		Keys[key].press=true;
		Keys[key].Ampl=atoi(m_amplitude_global)*value/127.0;

		//????
		Keys[key].A=Keys[key].Ampl;
		Keys[key].A_add=5;//0.6;

		Keys[key].Ampl=1;

		Keys[key].decrement=0;
		Keys[key].t=0;	//âðåìÿ ôóíêöèè sin
		
	}
	else 
	{
		Keys[key].decrement=AMPLITUDE_DECREMENT;
	}


}


void CDTFM_GeneratorDlg::MidiKeyPress(BYTE key, BYTE value)
{

	MidiKeyPress2(key, value);

	if (write)
	{
			static last_time=0;
			MIDI_DATA md={0};
			md.key=key;
			md.status=value;
			md.time=GetTickCount();
			file.Write(&md, sizeof(md));

			CStdioFile file;

			//íàæàëè íà êëàâèøó
			if (value>0)
			{
				if (file.Open("notes.h", file.modeWrite))
				{
					file.SeekToEnd();

					CString s;
					//çàïèñûâàåì âðåìÿ îò îòïóñêàíèÿ ïðåäûäóùåé äî íàæàòèÿ ýòîé
					s.Format("{0, %i},\n", md.time-last_time);
					
					file.WriteString(s);
			
					file.Close();

					last_time=GetTickCount();
				}
	
			}


			//îòïóñòèëè êëàâèøó
			if (value==0)
			{

				if (file.Open("notes.h", file.modeWrite))
				{
					file.SeekToEnd();


					CString s;
					//çàïèñûâàåì äëèòåëüíîñòü íàæàòèÿ êëàâèøè
					s.Format("{%i, %i},",md.key, md.time-last_time);
					
					file.WriteString(s);
					file.WriteString("\n");
					
					file.Close();

					last_time=GetTickCount();
				}

			}

			

			
	}

}





































void CDTFM_GeneratorDlg::OnHide() 
{
	ini.SetValue(1,"HideWindow");
	ShowWindow(SW_HIDE);	
}





























int MouseMove=FALSE;

void CDTFM_GeneratorDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	Overload=false;
	CDialog::OnLButtonDown(nFlags, point);

	if (point.y<KEY_Y) return;
	if (point.y>KEY_Y+KEY_H) return;
	if (point.x<KEY_X) return;

	int key=(point.x-KEY_X)/KEY_L;
	int octave=key/7;
	key=key%7;
	//if (key<0) return;

	int key_real=key;

	if		(key_real==1) key_real+=1;
	else if (key_real==2) key_real+=2;
	else if (key_real==3) key_real+=2;
	else if (key_real==4) key_real+=3;
	else if (key_real==5) key_real+=4;
	else if (key_real==6) key_real+=5;
	
	key_real+=(octave+1)*12;

	if (key_real>=0 && key_real<=256)// && Keys[key_real].press==FALSE) 
	{
		if (MouseMove && Keys[key_real].press==TRUE) 
		{
			MouseMove=FALSE;
			return;
		}
		Keys[key_real].press=TRUE;
		Keys[key_real].Ampl=atoi(m_amplitude_global);
		Keys[key_real].decrement=AMPLITUDE_DECREMENT;
		Keys[key_real].t=0;
	}

	//OnMouseMove(nFlags,point);
}


void CDTFM_GeneratorDlg::OnMouseMove(UINT nFlags, CPoint point) 
{

	//int KEY_L=14;
	//int KEY_H=65;

	//int KEY_X=10;
	//int KEY_Y=200;


	//CString s;
	//s.Format("%i:%i %i", point.x, point.y, (point.x-KEY_X)/KEY_L);

	//m_status_text.SetWindowText(s);

	//??????????????????
	if (nFlags&MK_LBUTTON)
	{
		MouseMove=true;
		OnLButtonDown(nFlags, point);
	}
	
	
	CDialog::OnMouseMove(nFlags, point);
}

