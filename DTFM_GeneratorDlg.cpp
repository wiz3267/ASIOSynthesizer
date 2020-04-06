// DTFM_GeneratorDlg.cpp : implementation file
// 
//добавить размер буфера ASIO
//запись/чтения номера ASIO, перевыбор ASIO через диалоговое окно


#include "stdafx.h"
#include "DTFM_Generator.h"
#include "DTFM_GeneratorDlg.h"

#include "BASSASIO\c\synth\bassasio.h"
#include "BASSASIO\c\synth\bass.h"

#include <atlbase.h>
#include <math.h>
#include "inifile.h"

#include "circleSlider.h"
#include "circleSliderIndicator.h"
#include "digIndicator.h"
#include "digIndicatorValue.h"


double garmonic_5=0;
double garmonic_6=0;
double ADSR_Attack=0;

double globalVolume=0.5;
//CircleSlider *cSlider1=NULL;
CircleSliderIndicator * cCircleSlider=NULL;
//DigIndicatorValue	*dInd1;

int m_modulation_amplitude_value;
int global_asio_index=0;

const double PI=3.1415926;

int NeedUpdateMidiEvent=1;	//обновлять Midi сообщения
int NeedUpdateBaseFreq=0;	//менять базовую частоту при изменения слайдера

int NeedUpdateModulation=1;	//реагировать на слайдер модуляции

double modulation=0;
double step_modulation=0;	//скорость модуляции
double ModulationWheel=0;
int m_modulation_wheel_2=0;	//значения колеса модуляции

CString m_edit_list_midi;

double scale;//=pow(2.0,1.0/12.0);

CString m_amplitude_global="";

void MidiKeyPress2(BYTE key, BYTE value);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


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

bool write=false; //нужно ли записывать в файл

int CurrentAmplitude=0;

int Overload=-100; //перегрузка звуков. уровня >32767 OR <-32767

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

double MaxSound=0;	//максимальный уровень звука на данный момент (до 32768)


//получить данные из формы в переменные
#define GetData UpdateData(true)

//положить (обновить) данные из переменных в форму
#define PutData UpdateData(false)

double Piano(double Ampl, double freq, double t, double phase);

static int _time_;

double	AMPLITUDE_DECREMENT;//5/2048.0;

int IdMidiOpen=-1;

int 
	SAMPLE_RATE=44100;

struct KEY
{
	UINT press;
	double decrement;
	double Ampl;

	double t;	//время(в условных единицах) сигнала
	double A,D,S,R;	//блок констант ADSR (Attack-Decay-Sustain-Release)
	double A_add;	//скорость увеличения A (атака)

	KEY() { press=0; decrement=0; Ampl=0; t=0; A=D=S=R=0; A_add=0;}
} Keys[256];


KEY KeysOld[256];

//////////////////////////////////////////////////////
//параметры отрисовки клавиш пианноролла			//
int KEY_L=14;										//
int KEY_H=65;										//

//координаты отрисовки пианно ролла					//
int KEY_X=0;										//
int KEY_Y=0;										//

int DrawPiannoRoll(CDC *dc, CEdit *dc_level, int x, int y, int start);//													//
//////////////////////////////////////////////////////

struct KEYSA
{
	BYTE code;
	char * help;
};

KEYSA Keysa[]=
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
	m_edit = _T("");
	m_midi_open_str = _T("3");
	m_amplitude = _T("32767");
	m_edit_freq = 0.0;
	m_midi_name = _T("");
	m_slider_decrement_double = 0.0;
	m_wave_len = 0.0;
	m_edit_modilation = _T("1");
	m_modulation_wheel = 0;
	m_asio_device = -1;
	m_edit_scale = _T("12");
	m_string_base_a = _T("440");
	m_modulation_amplitude = _T("10000");
	m_string_status_text = _T("");
	m_size_asio_buffer = 0;
	m_garmonic_5 = _T("1.25992");
	m_garmonic_6 = _T("1.49830");
	m_attack = _T("5");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDTFM_GeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDTFM_GeneratorDlg)
	DDX_Control(pDX, IDC_LEVEL_CONTROL, m_level_control);
	DDX_Control(pDX, IDC_EDIT_PIANOROLL, m_pianoroll);
	DDX_Control(pDX, IDC_SLIDER_TOTAL_VOLUME, m_slider_total_volume);
	DDX_Control(pDX, IDC_EDIT_BASE_A, m_edit_base_a);
	DDX_Control(pDX, IDC_EDIT_STATUS_TEXT, m_status_text);
	DDX_Control(pDX, IDC_AMPLITUDE, m_amplitude_edit);
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
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	DDX_Text(pDX, IDC_EDIT_MIDI_OPEN, m_midi_open_str);
	DDX_Text(pDX, IDC_AMPLITUDE, m_amplitude);
	DDX_Text(pDX, IDC_EDIT_FREQ, m_edit_freq);
	DDX_Text(pDX, IDC_EDIT_MIDI_NAME2, m_midi_name);
	DDX_Text(pDX, IDC_EDIT_SLIDER_DECREMENT, m_slider_decrement_double);
	DDX_Text(pDX, IDC_EDIT_WAVE_LEN, m_wave_len);
	DDX_Text(pDX, IDC_EDIT_MODULATION, m_edit_modilation);
	DDX_Text(pDX, IDC_EDIT_MODULATION_WHEEL, m_modulation_wheel);
	DDX_Text(pDX, IDC_EDIT_ASIO_DEVICE, m_asio_device);
	DDX_Text(pDX, IDC_EDIT_SCALE, m_edit_scale);
	DDX_Text(pDX, IDC_EDIT_BASE_A, m_string_base_a);
	DDX_Text(pDX, IDC_EDIT_MODULATION_FREQ, m_modulation_amplitude);
	DDX_Text(pDX, IDC_EDIT_STATUS_TEXT, m_string_status_text);
	DDX_Text(pDX, IDC_EDIT_SIZE_ASIO_BUFFER, m_size_asio_buffer);
	DDX_Text(pDX, IDC_EDIT_GARMONIC_5, m_garmonic_5);
	DDX_Text(pDX, IDC_EDIT_GARMONIC_6, m_garmonic_6);
	DDX_Text(pDX, IDC_EDIT_ATTACK, m_attack);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDTFM_GeneratorDlg, CDialog)
	//{{AFX_MSG_MAP(CDTFM_GeneratorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MIDI_CLOSE, OnButtonMidiClose)
	ON_BN_CLICKED(IDC_BUTTON_MIDI_OPEN, OnButtonMidiOpen)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, OnButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_STOP, OnButtonWriteStop)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_WRITEN, OnButtonPlayWriten)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_STOP_PLAY, OnStopPlay)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_EN_SETFOCUS(IDC_EDIT_MODULATION, OnSetfocusEditModulation)
	ON_EN_KILLFOCUS(IDC_EDIT_STATUS_TEXT, OnKillfocusEditStatusText)
	ON_EN_KILLFOCUS(IDC_EDIT_MODULATION, OnKillfocusEditModulation)
	ON_EN_SETFOCUS(IDC_EDIT_SCALE, OnSetfocusEditScale)
	ON_EN_KILLFOCUS(IDC_EDIT_SCALE, OnKillfocusEditScale)
	ON_BN_CLICKED(IDC_BUTTON_ASIO_CONTROL_PANEL, OnButtonAsioControlPanel)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDTFM_GeneratorDlg message handlers

int sl1, sl2, sl3, sl4, sl5, sl6;
int slm2, slm3, slm4, slm5, slm6;
int slvolume;


//функция используется для генерации звука

//сигнал в соответствии с эквалайзером в графическом интерфейсе программы
//Ampl амплитуда
//freq частота
//flag_one число используемых и вычисленных гармоник

//freq_actual записывается последняя вычисленная частота
//если flag_one==1, значит была использована только одна гармоника,
//а остальные слайдеры опущены вниз
double Piano(double Ampl, double freq, double t, double phase, int & flag_one, double & freq_actual)
{

	flag_one=0;

	if (sl1) {flag_one++;freq_actual=freq;}	//base frequency
	if (sl2) {flag_one++;freq_actual=freq*2;}
	if (sl3) {flag_one++;freq_actual=freq*3;}
	if (sl4) {flag_one++;freq_actual=freq*4;}
	
	//if (sl5) {flag_one++;freq_actual=freq*5;}
	if (sl5) {flag_one++;freq_actual=-1;}
	
	//if (sl6) {flag_one++;freq_actual=freq*6;}
	if (sl6) {flag_one++; freq_actual=-1;}

	if (slm2) {flag_one++;freq_actual=freq/2;}
	if (slm3) {flag_one++;freq_actual=freq/3;}
	if (slm4) {flag_one++;freq_actual=freq/4;}
	if (slm5) {flag_one++;freq_actual=freq/5;}
	if (slm6) {flag_one++;freq_actual=freq/6;}

	double k=0;	//итоговая вычисленная сумма 

	double limit=20000;	//ограничение частоты

	//амплитуда сигнала
	double AMP=Ampl;

	AMP+=
		m_modulation_amplitude_value//глубина модуляции
		*sin(modulation);

	double f;	//частота

	//если поднят первый слайдер (базовая гармоника)
	if (sl1) {						  k+=sl1/100.0*sin(freq*t); }

	//если поднят второй слайдер (вторая гаромника, в 2 раза выше базовой)
	if (sl2) { f=2*freq; if (f<limit) k+=sl2/100.0*sin(f*t); }
	if (sl3) { f=3*freq; if (f<limit) k+=sl3/100.0*sin(f*t); }
	if (sl4) { f=4*freq; if (f<limit) k+=sl4/100.0*sin(f*t); }
	
	//if (sl5) { f=5*freq; if (f<limit) k+=sl5/100.0*sin(f*t); }
	if (sl5) { f=garmonic_5*freq; if (f<limit) k+=sl5/100.0*sin(f*t); }

	//if (sl6) { f=6*freq; if (f<limit) k+=sl6/100.0*sin(f*t); }
	if (sl6) { f=garmonic_6*freq; if (f<limit) k+=sl6/100.0*sin(f*t); }


	//в два и более раза меньшие гармоники
	if(slm2) k+=slm2/100.0*sin(freq/2*t);
	if(slm3) k+=slm3/100.0*sin(freq/3*t);
	if(slm4) k+=slm4/100.0*sin(freq/4*t);
	if(slm5) k+=slm5/100.0*sin(freq/5*t);
	if(slm6) k+=slm6/100.0*sin(freq/6*t);

	if (m_modulation_amplitude_value)
	{
		return k *  (slvolume/100.0) * AMP  ;
	}
	else
	{
		return k *  (slvolume/100.0);
	}
}

extern int ASIO_buflen;

BOOL CDTFM_GeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//cSlider1 = new CircleSlider( 32, 360,50, 5.14 );

	cCircleSlider = new CircleSliderIndicator(360,50, CircleSliderIndicator::typeOfElem1, 0,100, 50, true, 4);
	
	//bool isSmallInd=1;
	//BYTE c=0xf0;
	//dInd1 = new DigIndicatorValue( 360, 85, RGB(c, c,c), RGB(0x00, 0x00, 0x00), isSmallInd );		
	//dInd1->SetIntValue( 35,  4, 0, 0 );

	m_asio_device=global_asio_index;
	m_size_asio_buffer=ASIO_buflen;

	PutData;

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
		m_sl1.SetPos(50);
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
	

	SetTimer(0,100,NULL);	//для обновления отрисовки клавиш

	//открываем MIDI-устройство
	OnButtonMidiOpen();

	if (ini.QueryValue("HideWindow")==1)
	{
		ShowWindow(SW_HIDE);
	}

	HANDLE hProcess=GetCurrentProcess();
	SetPriorityClass(hProcess,HIGH_PRIORITY_CLASS);

	
	//m_asio_device
	//m_control_asio_device.SetFocus();
	SetFocus();
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
		CDC *dc=GetDC();
		//cSlider1->Draw(dc);

		cCircleSlider->OnPaint(dc);
		
		//?????
		//dDig1=;
		//dInd1->OnPaint(dc,1);
		
		//?????
		//???????
		//ReleaseDC(dc);

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDTFM_GeneratorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
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
	UINT nChar=pMsg->wParam;

	if (pMsg->message == WM_KEYDOWN)
	{

		if (nChar==VK_LEFT)
		{

			if (BaseKeyboard>0) BaseKeyboard--;
		
			change=true;

		}

		if (nChar==VK_RIGHT)
		{

			if (BaseKeyboard<127) BaseKeyboard++;

			change=true;
		}

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

	if (pMsg->message == WM_KEYUP) // && hWaveOut)
	{
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


//самая важная функция - заполнение буфера звуковыми сгенерированными данными
void FillBuffer(short *plbuf, int size, int samplerate)
{

	freq_1 = 0;
	freq_1_count = 0;
	static int last_z =	0;
	int	delta =	0;

	double	K =	2*PI/samplerate;
	double	t =	_time_*K;
	double	m =	0;

	int OverloadCount=0;	//сколько раз был клиппинг (за пределы 32767...32767)
	
	for(int i=0; i<size/2; i++, _time_++)
	{
		m=0;

		modulation	+=	step_modulation;

		//проходимся по массиву клавиш MIDI-клавиатуры
		for(int k=0; k<128; k++) 
		{
			if (Keys[k].press) 
			{
				//считаем частоту базовой гармоники для нажатой клавиши
				double		freq	=	BASE_A * pow(scale, k-60+3 - 12);
				
				//сколько чистых гармоник было в сигнале
				int			flag_one=	1;

				//частота сигнала, если была только одна гармоника
				double		freq_actual=0;
				
				static double phase;
				
				phase=0;

				m			+=Piano(Keys[k].Ampl,freq,Keys[k].t,phase, flag_one, freq_actual);
				
				Keys[k].t	+=K;

				Keys[k].Ampl+=Keys[k].A_add;	//attack

				if (Keys[k].Ampl > Keys[k].A)
				{
					Keys[k].A_add=0;
				}
				
				if (Keys[k].Ampl-=Keys[k].decrement)

				if (Keys[k].Ampl<=0)
				{
					Keys[k].press=false;
					Keys[k].Ampl=0;
				}

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


		//static double CorrectAmplitude=1;
		//m*=CorrectAmplitude;

		//m - получаемое значение выборки
		//диапазон от -32767 до +32767

		//если выходит за пределы
		if (m>32767) 
		{
			m=32767;		//установка максимального значения
			Overload=-10;	//установка флага перегрузки
			OverloadCount++;
			//CorrectAmplitude-=0.01;
		}

		//если выходит за пределы
		else if (m < -32767) 
		{
			m = -32767;		//установка максимального значения
			Overload=-10;	//установка флага перегрузки
			OverloadCount++;
			//CorrectAmplitude-=0.01;
		}

		if (Overload<0) 
		{

			//if (CorrectAmplitude<0) CorrectAmplitude=0.1;
		}

		//устанавливаем уровень максимума за этот звуковой блок
		if (abs(int(m)) > MaxSound) MaxSound=abs(int(m));	//округляем double в int. все рассчеты ведутся в double, а здесь округление

		//short int z=(short int)(m*globalVolume);
		short int z=(short int)(m);

		plbuf[i]=z;
	}

	if (OverloadCount==0) Overload++;
}

extern int ASIO_buflen;
extern DWORD ASIO_PROC_BUFLEN;


void CDTFM_GeneratorDlg::OnClose() 
{
	OnButtonMidiClose();
	ExitDialog();
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


void CDTFM_GeneratorDlg::ExitDialog()
{
	GetData;

	//save data to .ini file
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
	ini.SetValue(m_slider_total_volume.GetPos(), "sltotalvolume");

	
	EndDialog(0);
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

int DrawPiannoRoll(CDC *dc, CEdit *level_control, int x, int y, int start)
{
	CBrush br_level,br_white, brush_red;

	br_white.CreateSolidBrush(RGB(250,250,250));

	brush_red.CreateSolidBrush(RGB(255,0,0));
	
	br_level.CreateSolidBrush(RGB(0,255,0));
	
	dc->SelectObject(br_level);

	RECT rt;
	level_control->GetClientRect(&rt);

	CDC *dc_level=level_control->GetDC();

	int L=rt.right;	//длина level_control
	int H=rt.bottom;	//высота level_control

	int delta_l=4;	//разница между уровнем звука и значком перегрузки

		//если перегрузка
	if (Overload<0)
	{
		//красный квадратик
		dc_level->SelectObject(brush_red);
		dc_level->Rectangle(L-H,0, L,H);	
	}
	else
	{
		//
		dc_level->SelectObject(br_white);
		dc_level->Rectangle(L-H,0,L,H);	
	}
	
	//if (MaxSound)
	{
		int k=int(MaxSound/32768.0*(L-delta_l-H));

		dc_level->SelectObject(br_level);
		dc_level->Rectangle(0,0, k,H);

		dc_level->SelectObject(br_white);
		dc_level->Rectangle(k,0,L-H-delta_l,H);
	}

	level_control->ReleaseDC(dc_level);
	



	//проверяем, были ли изменения в нажатиях клавиш на MIDI-клавиатуре
	for(int i=0; i<128; i++)
	{
		if ( (KeysOld[i].press!=Keys[i].press) 
			|| KeysOld[i].Ampl != Keys[i].Ampl) change=true;
	}

	//если есть изменения, продолжим рисование
	//иначе возврат для экономии ресурсов,
	//т.к. функция вызываеться циклически по таймеру
	if (change)
	{
		//копируем массив "новых" в массивых "старых" клавиш
		for(i=0; i<128; i++) KeysOld[i]=Keys[i];
	}
	else return 0;

	change=false;


	L=KEY_L;
	H=KEY_H;

	//y=0;

	CBrush br_red,br_bl;
	br_red.CreateSolidBrush(RGB(0,250,200));
	
	br_bl.CreateSolidBrush(RGB(10,10,10));


	int Z[]={0,2,4,5,7,9,11};
	int R[]={1,3,6,8,10};

	start=12;
	x=0;

	for(int T=0; T<10; T++)
	{
		for(int i=0; i<7; i++)
		{
			CBrush bra;
			int RR=start+ Z[i];
			if (RR>127) continue;
			int ampl=int(Keys[RR].Ampl);

			//int a=250*ampl/4000;
			int a=255*ampl/32767;
			//if (a>250) a=250;

			//int b=200*ampl/4000;
			int b=255*ampl/32767;
			//if (b>200) b=200;

			bra.CreateSolidBrush(RGB(0,a,b));

			if (Keys[RR].press)
				dc->SelectObject(bra);
			else
				dc->SelectObject(br_white);

			int x1=x+L*i;

			dc->Rectangle(x1,y,x+L*i+L, y+H);

			if ( RR==BaseKeyboard)
			{
				dc->Ellipse(x1+3, y+H-1, x1+L-6, y+H-8);
			}

		}

		int p=0;
		for(i=0; i<7; i++)
		{
			int RR=start+ R[p];
			if (RR>127) continue;

			int L2=int(L*0.6);
			int H2=int(H*0.6);
			if (scale != pow(2,1/12.0)) 
			{
				H2=H;
			}
			else
			{
				//!!!!!!!!!!!!!!!!
				//H2=H;
			}
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
				dc->SelectObject(br_white);
				dc->Ellipse(x1+1, y+H-1, x1+L2, y+H-8);
			}

			p++;

		}

		x+=L*7;
		
		start+=12;
	}


	return 1;
}

void CDTFM_GeneratorDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == 5555)
	{
		//проиграть записанные данные
	}



	GetData;


	CString s = m_garmonic_5;
	garmonic_5=strtod(s.GetBuffer(0),NULL);

	s = m_garmonic_6;
	garmonic_6=strtod(s.GetBuffer(0),NULL);

	s = m_attack;
	ADSR_Attack = strtod(s.GetBuffer(0),NULL);


	m_modulation_amplitude_value = atoi(m_modulation_amplitude.GetBuffer(0));

	s =	m_edit_modilation;
	double m_scale = atoi(m_edit_scale.GetBuffer(0));
	
	if (m_scale<2 || m_scale>48) m_scale = 12;
	scale = pow(2.0,1.0/m_scale);

	double m_base_a	= atoi(m_string_base_a.GetBuffer(0));

	BASE_A = m_base_a;

	ModulationWheel	= strtod(s.GetBuffer(0),NULL);
	
	m_modulation_wheel=	m_modulation_wheel_2;

	if (NeedUpdateMidiEvent)
	{
		//обновляем если есть изменения
		if (m_edit!=m_edit_list_midi)
		{
			m_edit=m_edit_list_midi;
		}
	}

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


	AMPLITUDE_DECREMENT=(m_slider_decrement.GetPos()*3+1)/128.0;

	m_slider_decrement_double=AMPLITUDE_DECREMENT;

	m_edit_freq=freq_1*2;
	if (freq_1 != 0) m_wave_len = 330/m_edit_freq;
	else	m_wave_len = 0;

	PutData;

	//????
	RECT rt;
	m_pianoroll.GetWindowRect(&rt);
	
	KEY_X=rt.left;
	KEY_Y=rt.top;
	
	//перересовка пианоролла
	RECT rtwin;
	GetWindowRect(&rtwin);
	int x=rtwin.left;
	int y=rtwin.top;
	
	KEY_X-=x;
	KEY_Y-=y;

	CDC *pdc=m_pianoroll.GetDC();
	//DrawPiannoRoll(pdc, &m_level_control, pianoroll_x-x, 0, 60);
	DrawPiannoRoll(pdc, &m_level_control, 0, 0, 60);
	ReleaseDC(pdc);


	CDialog::OnTimer(nIDEvent);

	MaxSound=0;
	//Overload=0;

}


void CDTFM_GeneratorDlg::OnButtonMidiClose() 
{
	if (hmidiIn!=NULL)
	{
		int err=midiInStop(hmidiIn);

		if (err!=MMSYSERR_NOERROR) 
		{
			m_midi_name="Ошибка midiInStop";
			return;
		}

		err=midiInClose(hmidiIn);
		if (err!=MMSYSERR_NOERROR) 
		{
			m_midi_name="Ошибка midiInClose";
		}

		m_midi_close.EnableWindow(false);
		m_midi_open.EnableWindow(true);
		SetFocus();

		m_midi_name="midi close";

		PutData;

		hmidiIn=NULL;

	}
	
}
//прием миди сообщений
void CALLBACK MidiInProc(
   HMIDIIN   hMidiIn,
   UINT      wMsg,
   DWORD  dwInstance,
   DWORD dwParam1,
   DWORD dwParam2
)
{



	if (write && (wMsg == MM_MIM_DATA))
	{

			DWORD_BYTES mm;
			mm.data=dwParam1;

			BYTE nChar=mm.b[1];
			BYTE Volume=mm.b[2];


			static last_time=0;
			MIDI_DATA md={0};
			//md.key=key;
			//md.status=value;
			md.key=nChar;
			md.status=Volume;
			md.time=GetTickCount();
			file.Write(&md, sizeof(md));

			CStdioFile file;

			//нажали(отпустили) midi клавишу
			if (nChar>=0)
			{
				if (file.Open("midi.dat", file.modeWrite))
				{
					file.SeekToEnd();

					//CString s;
					//s.Format("{0, %i},\n", md.time-last_time);
					file.Write(&md,sizeof(md));
					

					file.Close();

					last_time=GetTickCount();
				}
	
			}
	}



	if (wMsg == MM_MIM_DATA)
	{
		DWORD_BYTES mm;
		mm.data=dwParam1;

		if (mm.b[0] != 254)
		{
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

			BYTE nChar=mm.b[1];
			BYTE Volume=mm.b[2];

			int z=mm.b[0]>>4;


			if (NeedUpdateModulation)
			{
				if (z==11 && nChar==1)
				{
					//step_modulation=ModulationWheel * Volume/127.0/2048.0;
					//step_modulation=ModulationWheel * Volume/127.0/512;
					step_modulation=ModulationWheel * Volume/127.0/ASIO_buflen;
					m_modulation_wheel_2=Volume;
				}
			}

			if (NeedUpdateBaseFreq)
			{
				if (z==11 && nChar==7)
				{
					BASE_A=440+Volume;
				}
			}

			if ((mm.b[0]>>4) == 9 || (mm.b[0]>>4) == 8)
			{
				if (nChar<256) 
				{
					MidiKeyPress2(nChar, Volume);
					//MidiKeyPress(nChar, Volume);
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

//открытие миди-устройства
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
 	if (PlayWritenPosition*sizeof(MIDI_DATA)>=PlayWritenSize)
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
	if (value!=0)
	{
		//if (Keys[key].press==true) return;

		//if (Keys[key].press==1) return;


		Keys[key].press=true;

		Keys[key].Ampl=atoi(m_amplitude_global)*value/127.0;

		//????
		Keys[key].A=Keys[key].Ampl;
		Keys[key].A_add=ADSR_Attack;//0.6;

		Keys[key].Ampl=0;

		Keys[key].decrement=0;
		Keys[key].t=0;	//время функции sin
		
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

			//нажали на клавишу
			if (value>0)
			{
				if (file.Open("notes.h", file.modeWrite))
				{
					file.SeekToEnd();

					CString s;
					//записываем время от отпускания предыдущей до нажатия этой
					s.Format("{0, %i},\n", md.time-last_time);
					
					file.WriteString(s);
			
					file.Close();

					last_time=GetTickCount();
				}
	
			}


			//отпустили клавишу
			if (value==0)
			{

				if (file.Open("notes.h", file.modeWrite))
				{
					file.SeekToEnd();


					CString s;
					//записываем длительность нажатия клавиши
					s.Format("{%i, %i},",md.key, md.time-last_time);
					
					file.WriteString(s);
					file.WriteString("\n");
					
					file.Close();

					last_time=GetTickCount();
				}

			}
			
	}

}


int MouseMove=FALSE;

//отработка нажатия левой клавиши мыши
//нужно начать воспроизведение звука
//если курсор попадает в зону пианоролла
void CDTFM_GeneratorDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//Overload=false;

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

		
		//если в момент нажатия клавиши нажата CTRL 
		if (nFlags & MK_CONTROL) Keys[key_real].decrement=0;//звук будет звучать постоянно
		else Keys[key_real].decrement=AMPLITUDE_DECREMENT;
		
		Keys[key_real].t=0;
	}

}


void CDTFM_GeneratorDlg::OnMouseMove(UINT nFlags, CPoint point) 
{

	int oldx, oldy;

	oldx=cCircleSlider->xSliderStart;
	oldy=cCircleSlider->ySliderStart;


	cCircleSlider->OnMouseMove(nFlags, point);
	
	if (cCircleSlider->pSlider->flagPaint == true)
	{
		CDC *dc=GetDC() ;
		cCircleSlider->OnPaint(dc);


		globalVolume=cCircleSlider->GetValue()/100.0;

		m_slider_total_volume.SetPos(int(globalVolume*100));
		

		ReleaseDC(dc);

		if ( (oldx!=cCircleSlider->xSliderStart) || (oldy!=cCircleSlider->ySliderStart))
		{
			
			//Invalidate(false);
			int x=cCircleSlider->xSliderStart,y=cCircleSlider->ySliderStart,d=150;
			RECT rt={x,y,x+d,y+d};
			InvalidateRect(&rt,true);
			//Invalidate(true);
		}
		//?????
	}


	if (nFlags&MK_LBUTTON)
	{
		MouseMove=true;
		OnLButtonDown(nFlags, point);
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CDTFM_GeneratorDlg::OnSetfocusEditModulation() 
{
	GetData;
	m_string_status_text="Если указать ноль, модуляция отключается";
	PutData;
	
}

void CDTFM_GeneratorDlg::OnKillfocusEditStatusText() 
{
	
}

void CDTFM_GeneratorDlg::OnKillfocusEditModulation() 
{
	GetData;
	m_string_status_text="";
	PutData;
}

void CDTFM_GeneratorDlg::OnSetfocusEditScale() 
{
	m_string_status_text="Темперация клавиатуры (на сколько равных частей делится октава). 12 по умолчанию. Можно попробовать 24, например.";	
	PutData;
}

void CDTFM_GeneratorDlg::OnKillfocusEditScale() 
{
	// TODO: Add your control notification handler code here
	GetData;
	m_string_status_text="";
	PutData;
	
}

void CDTFM_GeneratorDlg::OnButtonAsioControlPanel() 
{
	// TODO: Add your control notification handler code here
	BASS_ASIO_ControlPanel();
	
}

void CDTFM_GeneratorDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CDTFM_GeneratorDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	Invalidate(TRUE);
	CDialog::OnRButtonUp(nFlags, point);
}
