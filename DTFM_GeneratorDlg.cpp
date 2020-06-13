// DTFM_GeneratorDlg.cpp : implementation file
#include "stdafx.h"
#include "DTFM_Generator.h"
#include "DTFM_GeneratorDlg.h"
#include "dialogasioconnect.h"

#include "BASSASIO\c\synth\bassasio.h"
#include "BASSASIO\c\synth\bass.h"

#include <atlbase.h>
#include <math.h>
#include "inifile.h"

#include "circleSlider.h"
#include "circleSliderIndicator.h"
#include "digIndicator.h"
#include "digIndicatorValue.h"

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
	m_asio_device = -1;
	m_edit_scale = _T("12");
	m_string_base_a = _T("440");
	m_modulation_amplitude = _T("10000");
	m_string_status_text = _T("");
	m_size_asio_buffer = 0;
	m_garmonic_5 = _T("1.25992");
	m_garmonic_6 = _T("1.49830");
	m_attack = _T("5");
	m_edit_modulation_wheel = _T("");
	m_use_velocity = TRUE;
	m_no_sustain = FALSE;
	m_piano_mouse_click = TRUE;
	m_ctrl_key_use = FALSE;
	m_check_saw3 = TRUE;
	m_filter_off = TRUE;
	m_write_rawdata_pcm = FALSE;
	m_sample_rate = 0;
	m_rez_min = _T("-0.5");
	m_rez_max = _T("4");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CDTFM_GeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDTFM_GeneratorDlg)
	DDX_Control(pDX, IDC_STATIC_CSLIDER7, m_static_slider7);
	DDX_Control(pDX, IDC_STATIC_CSLIDER6, m_static_slider6);
	DDX_Control(pDX, IDC_EDIT_FILL_BUFFER_TICKCOUNT, m_tick_count_fill_buffer);
	DDX_Control(pDX, IDC_STATIC_CSLIDER5, m_static_slider5);
	DDX_Control(pDX, IDC_STATIC_CSLIDER4, m_static_slider4);
	DDX_Control(pDX, IDC_STATIC_CSLIDER3, m_static_sslider3);
	DDX_Control(pDX, IDC_STATIC_CSLIDER2, m_static_slider2);
	DDX_Control(pDX, IDC_STATIC_CSLIDER1, m_static_slider1);
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
	DDX_Text(pDX, IDC_EDIT_ASIO_DEVICE, m_asio_device);
	DDX_Text(pDX, IDC_EDIT_SCALE, m_edit_scale);
	DDX_Text(pDX, IDC_EDIT_BASE_A, m_string_base_a);
	DDX_Text(pDX, IDC_EDIT_MODULATION_FREQ, m_modulation_amplitude);
	DDX_Text(pDX, IDC_EDIT_STATUS_TEXT, m_string_status_text);
	DDX_Text(pDX, IDC_EDIT_SIZE_ASIO_BUFFER, m_size_asio_buffer);
	DDX_Text(pDX, IDC_EDIT_GARMONIC_5, m_garmonic_5);
	DDX_Text(pDX, IDC_EDIT_GARMONIC_6, m_garmonic_6);
	DDX_Text(pDX, IDC_EDIT_MODULATION_WHEEL, m_edit_modulation_wheel);
	DDX_Check(pDX, IDC_CHECK_USE_VELOCITY, m_use_velocity);
	DDX_Check(pDX, IDC_CHECK_NO_SUSTAIN, m_no_sustain);
	DDX_Check(pDX, IDC_CHECK_PIANO_MOUSE_CLICK, m_piano_mouse_click);
	DDX_Check(pDX, IDC_CHECK_CTRL_KEY, m_ctrl_key_use);
	DDX_Check(pDX, IDC_CHECK_SAW, m_check_saw3);
	DDX_Check(pDX, IDC_CHECK_FILTER_OFF, m_filter_off);
	DDX_Check(pDX, IDC_CHECK_WRITE_RAWDATA_PCM, m_write_rawdata_pcm);
	DDX_Text(pDX, IDC_EDIT_SAMPLE_RATE, m_sample_rate);
	DDX_Text(pDX, IDC_EDIT_REZ_MIN, m_rez_min);
	DDX_Text(pDX, IDC_EDIT_REZ_MAX, m_rez_max);
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
	ON_COMMAND(ID_SETTINGS_SETASIODEVICE, OnSettingsSetasiodevice)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_BN_CLICKED(IDC_BUTTON_DEMO, OnButtonDemo)
	ON_COMMAND(ID_KEYBOARD_KEYS_MENU, OnKeyboardKeysMenu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDTFM_GeneratorDlg message handlers

DWORD FillBufferTickCount=0;

int counter = 0;
int demo[] = {50,-1,-1,-1,53,-1,-1,50,-1,50,55,-1,50,-1,48,-1,50,-1,-1,-1,57,-1,-1,50,-1,50,58,-1,57,-1,53,-1,50,-1,57,-1,62,-1,50,48,-1,48,45,-1,52,-1,50};

CPoint g_last_mouse_point;
CDTFM_GeneratorDlg * g_mainwindow=NULL;

BOOL no_sustain;
double garmonic_5=0;
double garmonic_6=0;
double ADSR_Attack=0;

double globalVolume=0.5;

CircleSliderIndicator * cCircleSlider_attack=NULL;
CircleSliderIndicator * cCircleSlider_modulation=NULL;
CircleSliderIndicator * cCircleSlider_detune=NULL;
CircleSliderIndicator * cCircleSlider_filterspeed=NULL;
CircleSliderIndicator * cCircleSlider_echo=NULL;
CircleSliderIndicator * cCircleSlider_6=NULL;
CircleSliderIndicator * cCircleSlider_7=NULL;

//CircleSliderIndicator * cCircleSlider_detune=NULL;

int global_asio_index=0;

const double PI=3.1415926;

int NeedUpdateMidiEvent=1;	//обновлять Midi сообщения
int NeedUpdateBaseFreq=0;	//менять базовую частоту при изменения слайдера

int NeedUpdateModulation=1;	////***^^^*** реагировать на слайдер модуляции	
double g_modulation_t=0;	//***^^^***
double g_step_modulation=0;	////***^^^*** скорость модуляции 
double g_ModulationWheel=0;	//***^^^***
int g_modulation_wheel_2=0;	////***^^^***значения колеса модуляции
int g_modulation_amplitude_value;//***^^^***

CString g_edit_list_midi;

double scale;//=pow(2.0,1.0/12.0);

CString g_amplitude_global="";

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

static int _time_;

double	AMPLITUDE_DECREMENT;//5/2048.0;

int IdMidiOpen=-1;

int 
	SAMPLE_RATE=0;
	//SAMPLE_RATE=44100*2;
	//SAMPLE_RATE=48000;

//double myMin = -0.7;
//double myMax = 0.7;

double myMin = -1;
double myMax = 1;


double rezMin = -0.5;
double rezMax = 4.5;

double filterSpeed = 20000*10;
//double filterSpeed = 1000;

double deTune = 1.000;

struct KEY
{
	UINT press;	//клавиша нажата (активна)
	BYTE midi_key_press;	//была нажата миди клавиша
	BYTE key_unpress;	//была отпущена клавиша на клавиатуре
	double decrement;
	double Ampl;

	double t;	//время(в условных единицах) сигнала
	double A,D,S,R;	//блок констант ADSR (Attack-Decay-Sustain-Release)
	double A_add;	//скорость увеличения A (атака)

//	double sawSource;
	double sawSource1;
	double sawSource2;
	
	double filter1 ;
	double filter2 ;
	double filter3 ;

	double fRez1;
	double fRez2;
	double fRez3;

	double ss1;
	double ss2;
	double ss3;

	void ResetFilter()
	{
		sawSource1=0;
		sawSource2=0;
		
		filter1=0;
		filter2=0;
		filter3=0;
		fRez1 = rezMax;
		fRez2 = rezMax;
		fRez3 = rezMax;
		ss1=0;
		ss2=0;
		ss3=0;

	}

	KEY() 
	{ 
		press=0; 
		key_unpress=TRUE;

		decrement=0; Ampl=0; t=0; A=D=S=R=0; A_add=0;
		
		midi_key_press=0; 

		sawSource1=0;
		sawSource2=0;
		
		filter1=0;
		filter2=0;
		filter3=0;
		fRez1 = rezMax;
		fRez2 = rezMax;
		fRez3 = rezMax;
		ss1=0;
		ss2=0;
		ss3=0;
	}

} Keys[128];

double Piano(int keyN, double Ampl, double freq, double t, double phase);

KEY KeysOld[128];

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

int sl1, sl2, sl3, sl4, sl5, sl6;
int slm2, slm3, slm4, slm5, slm6;
int slvolume;


const garm_c=10;
double randarray[garm_c] = {3, 7, 17, 22, 23, 27, 29, 37, 43, 47}; // якобы случайные числа


//функция Piano используется для генерации звука

//сигнал в соответствии с эквалайзером в графическом интерфейсе программы
//Ampl амплитуда
//freq базовая частота сигнала
//flag_one число используемых и вычисленных гармоник

//freq_actual записывается последняя вычисленная частота
//если flag_one==1, значит была использована только одна гармоника,
//а остальные слайдеры опущены вниз
double Piano(int keyN,double Ampl, double freq, double t, double phase, int & flag_one, double & freq_actual)
{

	flag_one=0;

	if (sl1 && !g_mainwindow->m_check_saw3) {flag_one++;freq_actual=freq;}	//base frequency
	//if (sl2) {flag_one++;freq_actual=freq*2;}
	if (sl2) {flag_one++;freq_actual=freq;}
	
	//if (sl3) {flag_one++;freq_actual=freq*3;}
	if (sl3) {flag_one++;freq_actual=freq;}

	if (sl4) {flag_one++;freq_actual=freq*4;}
	
	//if (sl5) {flag_one++;freq_actual=freq*5;}
	if (sl5) {flag_one++;freq_actual=freq*garmonic_5;}
	
	//if (sl6) {flag_one++;freq_actual=freq*6;}
	if (sl6) {flag_one++; freq_actual=freq*garmonic_6;}

	if (slm2) {flag_one++;freq_actual=freq/2;}
	if (slm3) {flag_one++;freq_actual=freq/3;}
	if (slm4) {flag_one++;freq_actual=freq/4;}
	if (slm5) {flag_one++;freq_actual=freq/5;}
	if (slm6) {flag_one++;freq_actual=freq/6;}

	double k=0;	//итоговая вычисленная сумма 

	double limit=20000;	//ограничение частоты

	//амплитуда сигнала
	double AMP=Ampl;

	//***^^^*** свяазано с модуляцией
	AMP+=
		g_modulation_amplitude_value//глубина модуляции
		*sin(g_modulation_t);

	double f;	//частота отдельной синусоиды
	//freq базовая синусоида

	//если поднят первый слайдер (базовая гармоника)
	if (sl1) {

		if (g_mainwindow->m_check_saw3)
		{
			double dt=1 + cCircleSlider_detune->GetValue()/5000.0;
			//double dt=1 + 1.0/pow(2, cCircleSlider_detune->GetValue()/10.0);


			double myconst = (myMax - myMin) / SAMPLE_RATE;

			//Keys[keyN].sawSource1 += freq * 0.000032 * dt;
			//Keys[keyN].sawSource2 += freq * 0.000032 / dt;
			
			//Keys[keyN].sawSource1 += freq * myconst * dt;
			//Keys[keyN].sawSource2 += freq * myconst / dt;

			//int fmodulation_f = 50; // частота частотной модуляции
			//int fmodulation_d = 50; // глубина частотной модуляции

			double fmodulation_f = cCircleSlider_6->GetValue(); // частота частотной модуляции
			double fmodulation_d = cCircleSlider_7->GetValue(); // глубина частотной модуляции



			double fmodulation = 1 + (1 - pow(1.001, fmodulation_d)) * sin(t * pow(1.015, fmodulation_f));
            
			Keys[keyN].sawSource1 += freq * myconst * dt * fmodulation;
			Keys[keyN].sawSource2 += freq * myconst / dt * fmodulation;


			if(Keys[keyN].sawSource1 >= myMax) Keys[keyN].sawSource1 = myMin - myMax + Keys[keyN].sawSource1;
			if(Keys[keyN].sawSource2 >= myMax) Keys[keyN].sawSource2 = myMin - myMax + Keys[keyN].sawSource2;

			
			//if(Keys[keyN].sawSource1 >= myMax) Keys[keyN].sawSource1 = myMin;
			//if(Keys[keyN].sawSource2 >= myMax) Keys[keyN].sawSource2 = myMin;
			
			double sawSource = Keys[keyN].sawSource1 + Keys[keyN].sawSource2;

			if (g_mainwindow->m_filter_off)
			{
				Keys[keyN].filter1=sawSource;
			}

			if (g_mainwindow->m_filter_off == false)
			{
				filterSpeed = //500 * (cCircleSlider_filterspeed->GetValue()+1);

				//pow(2, 9 + cCircleSlider_filterspeed -> GetValue() / 15.0);
				pow(2, 9 + cCircleSlider_filterspeed -> GetValue() / 10.0);

				Keys[keyN].fRez1 -= (Keys[keyN].fRez1 - rezMin) / filterSpeed;
				//Keys[keyN].ss1 += (sawSource - Keys[keyN].filter1) / pow(2, rezMax - Keys[keyN].fRez1 + 4);
				Keys[keyN].ss1 += (sawSource - Keys[keyN].filter1) / pow(4, 6 - Keys[keyN].fRez1);

				//Keys[keyN].ss1 /= 1.02;
				Keys[keyN].ss1 /= 1.01;
				Keys[keyN].filter1 += Keys[keyN].ss1;
			}
				

			double echo=cCircleSlider_echo->GetValue();

			
			if (echo>0 && !g_mainwindow->m_filter_off)
			{
				if(t > echo)
				{
				
					Keys[keyN].fRez2 -= (Keys[keyN].fRez2 - rezMin) / filterSpeed;
					//Keys[keyN].ss2 += (sawSource - Keys[keyN].filter2) / pow(2, rezMax - Keys[keyN].fRez2 + 4);
					Keys[keyN].ss2 += (sawSource - Keys[keyN].filter2) / pow(4, 6 - Keys[keyN].fRez2 );
					Keys[keyN].ss2 /= 1.02;
					Keys[keyN].filter2 += Keys[keyN].ss2;
				
				}
				
				if(t > 2*(echo))
				{
				
					Keys[keyN].fRez3 -= (Keys[keyN].fRez3 - rezMin) / filterSpeed;
					//Keys[keyN].ss3 += (sawSource - Keys[keyN].filter3) / pow(2, rezMax - Keys[keyN].fRez3 + 4);
					Keys[keyN].ss3 += (sawSource - Keys[keyN].filter3) / pow(4, 6 - Keys[keyN].fRez3);
					Keys[keyN].ss3 /= 1.02;
					Keys[keyN].filter3 += Keys[keyN].ss3;
				
				}
			}
						
			k += Keys[keyN].filter1; // базовый звук
			
			if (echo>0 && !g_mainwindow->m_filter_off) 
			{
				k += Keys[keyN].filter2 * 0.5; // первое повторение эхо
				k += Keys[keyN].filter3 * 0.25; // второе повторение эхо
			}
			
			k *= sl1 / 100.0;
		}
		else
		{
			f=freq; 
			
			if (f<limit) k+=sl1/100.0*sin(f*t);
		}
		
	}

	//если поднят второй слайдер 
	if (sl2) 
	{
		//f=2*freq; 
		//????????????????
		f=freq; 
		//floor
		//double val=floor(sin(f*t)+0.1);
		double val=sin(f*t);
		//double fix=cCircleSlider_filterspeed->GetValue()/100.0;
		double fix=0;

		if (val>=fix) val=1;
		if (val<-fix) val=-1;
		

		if (f<limit) k+=sl2/100.0*val; 
	}

	if (sl3) 
	{
		
		///f=3*freq; 
		////if (f<limit) k+=sl3/100.0*sin(f*t); 

		bool randgarmony = true; // разрешение выполнять функцию ниже
		if(randgarmony == true)
		{

			static int cnt_xxx;
			cnt_xxx++;

			if (cnt_xxx>400000)
			{
				for(int z=0; z<garm_c; z++)
				{
					randarray[z]=rand()%50;//+(rand()%1000)/1000.0;
				}
				cnt_xxx=0;
			}
			
			double out = 0.4 * sin(freq * t); //base freq
			//double out = 0;

			for(int i = 0; i < garm_c; i ++) 
			{
				//out += 0.1/(i+1) * sin(freq * randarray[i] * t);
				out += 0.4 * sin(freq * randarray[i] * t);
			}

			 // дальше уже знакомый код фильтра, только на вход подаём переменную out
			filterSpeed = pow(2, 9 + cCircleSlider_filterspeed -> GetValue() / 10.0);
			Keys[keyN].fRez1 -= (Keys[keyN].fRez1 - rezMin) / filterSpeed;
			Keys[keyN].ss1 += (out - Keys[keyN].filter1) / pow(4, 6 - Keys[keyN].fRez1);
			//Keys[keyN].ss1 /= 1.02;
			Keys[keyN].ss1 /= 1.02 ;
			Keys[keyN].filter1 += Keys[keyN].ss1;
			
			k += Keys[keyN].filter1; // добавляем результат в общий поток
			k *= sl3/100.0;

			//k += out * sl3/100.0;

		}

	
	
	}
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

	//***^^^*** свяазано с модуляцией
	if (g_modulation_amplitude_value)
	{
		return k *  (slvolume/100.0) * AMP  ;
	}
	else
	{
		return k *  (slvolume/100.0);
	}
}

extern int ASIO_buflen;

CMenu menu;

BOOL CDTFM_GeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

		
	menu.LoadMenu(IDR_MENU_MAIN);
	SetMenu(&menu);

	g_mainwindow=this;

	BaseKeyboard=ini.QueryValue("BaseKeyboard");
	if (!BaseKeyboard) BaseKeyboard=59;

	m_check_saw=ini.QueryValue("CheckSaw");


	RECT rt, rt2, rt3, rt4, rt5, rt6, rt7;
	m_static_slider1.GetWindowRect(&rt);
	m_static_slider2.GetWindowRect(&rt2);
	m_static_sslider3.GetWindowRect(&rt3);
	m_static_slider4.GetWindowRect(&rt4);
	m_static_slider5.GetWindowRect(&rt5);
	m_static_slider6.GetWindowRect(&rt6);
	m_static_slider7.GetWindowRect(&rt7);
	ScreenToClient(&rt);
	ScreenToClient(&rt2);
	ScreenToClient(&rt3);
	ScreenToClient(&rt4);
	ScreenToClient(&rt5);
	ScreenToClient(&rt6);
	ScreenToClient(&rt7);


	int x=rt.left,y=rt.top;

	cCircleSlider_6= new CircleSliderIndicator(rt6.left, rt6.top, CircleSliderIndicator::typeOfElem4, 0,100, 0, true, 3,
											  DigIndicatorValue::signTypeNotShow);

	cCircleSlider_6	->SetValue(ini.QueryValue("ModulationParam1"));


	cCircleSlider_7= new CircleSliderIndicator(rt7.left, rt7.top, CircleSliderIndicator::typeOfElem4, 0,100, 0, true, 3,
											  DigIndicatorValue::signTypeNotShow);

	cCircleSlider_7	->SetValue(ini.QueryValue("ModulationParam2"));


	cCircleSlider_attack = new CircleSliderIndicator(x,y, CircleSliderIndicator::typeOfElem4, 0,127, 0, true, 3,
											  DigIndicatorValue::signTypeNotShow);

	cCircleSlider_attack->SetValue(ini.QueryValue("Attack"));
	
	cCircleSlider_modulation = new CircleSliderIndicator(rt2.left,rt2.top, 
		CircleSliderIndicator::typeOfElem4, 0,127, 0, true, 3, DigIndicatorValue::signTypeNotShow);

	cCircleSlider_modulation->SetValue(ini.QueryValue("Modulation"));

	cCircleSlider_detune = new CircleSliderIndicator(rt3.left,rt3.top, 
		CircleSliderIndicator::typeOfElem4, 0,100, 0, true, 3, DigIndicatorValue::signTypeNotShow);

		cCircleSlider_detune->SetValue(ini.QueryValue("Detune"));

	cCircleSlider_filterspeed=new CircleSliderIndicator(rt4.left,rt4.top, 
		CircleSliderIndicator::typeOfElem4, 0,100, 0, true, 3, DigIndicatorValue::signTypeNotShow);;

	cCircleSlider_filterspeed->SetValue(ini.QueryValue("FilterSpeed"));

	cCircleSlider_echo = new CircleSliderIndicator(rt5.left,rt5.top, 
		CircleSliderIndicator::typeOfElem4, 0,10, 0, true, 3, DigIndicatorValue::signTypeNotShow);;

	cCircleSlider_echo->SetValue(ini.QueryValue("Echo")+0.1);

	
	//bool isSmallInd=1;
	//BYTE c=0xf0;
	//dInd1 = new DigIndicatorValue( 360, 85, RGB(c, c,c), RGB(0x00, 0x00, 0x00), isSmallInd );		
	//dInd1->SetIntValue( 35,  4, 0, 0 );

	int temp=ini.QueryValue("MidiDevice");
	char buf_midi[8];
	itoa(temp,buf_midi,10);
	m_midi_open_str=buf_midi;

	m_garmonic_5=ini.QueryString("Garmonic5");
	m_garmonic_6=ini.QueryString("Garmonic6");
	

	m_asio_device=global_asio_index;
	m_size_asio_buffer=ASIO_buflen;

	m_sample_rate=SAMPLE_RATE;

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

		PutData;

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

		m_garmonic_5="1.25";
		m_garmonic_6="1.49";


	}
	

	SetTimer(0,100,NULL);	//для обновления отрисовки клавиш
	//SetTimer(1,100,NULL);	//для обновления отрисовки клавиш

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

/*	CDC *dc=GetDC();
	dc->Rectangle(x,y,x+5,y+5);
	ReleaseDC(dc);*/

	//ShowWindow(SW_NORMAL);
	SetForegroundWindow();


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


		cCircleSlider_attack->OnPaint(dc);
		cCircleSlider_modulation->OnPaint(dc);
		cCircleSlider_detune->OnPaint(dc);
		cCircleSlider_filterspeed->OnPaint(dc);
		cCircleSlider_echo->OnPaint(dc);

		cCircleSlider_6->OnPaint(dc);
		cCircleSlider_7->OnPaint(dc);
		
		
		ReleaseDC(dc);

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

	//клавиша нажата
	//нужно учитывать, что после первого нажатия начинают поступать
	//повторные сообщения от клавиатуры

	/*CWnd * win=GetFocus();
	if (win)
	{
		

		CString str;
		win->GetWindowText(str);
		if (str.GetLength()!=0) return 0;
	}*/

	if (pMsg->message == WM_KEYDOWN)
	{

		if (nChar==VK_LEFT)
		{

			if (BaseKeyboard>12) BaseKeyboard--;
		
			change=true;

		}

		if (nChar==VK_RIGHT)
		{

			if (BaseKeyboard<127) BaseKeyboard++;

			change=true;
		}

		for(int i=0; i<128; i++)
		{
			if (Keysa[i].code==0) break;


			if (Keysa[i].code==nChar)
			{
				int r=i+BaseKeyboard;

				//Keys[r].key_unpress=FALSE;
				//if (Keys[r].key_unpress==FALSE)
				//{
					if (Keys[r].Ampl==0 || Keys[r].key_unpress==TRUE)
					{
						MidiKeyPress(r,127);
						Keys[r].key_unpress=FALSE;
					}
				//	Keys[r].key_unpress=TRUE;

				//}

			}

		}

		return 0;
	}

	//клавиша отпущена
	if (pMsg->message == WM_KEYUP) 
	{
		for(int i=0; i<128; i++)
		{
			if (Keysa[i].code==0) break;
			if (Keysa[i].code==nChar)
			{
				int r=i+BaseKeyboard;

				Keys[r].key_unpress=TRUE;
				MidiKeyPress(r,0);
				
			}

		}

		return 0;
	}


	return CDialog::PreTranslateMessage(pMsg);

	//return 0;
}

double freq_1=0;
int freq_1_count=0;

const COPYBUFFER_SIZE=16384;
short CopyBuffer[COPYBUFFER_SIZE];

//самая важная функция - заполнение буфера звуковыми сгенерированными данными
void FillBuffer(short *plbuf, int size, int samplerate)
{
	LARGE_INTEGER la1, la2;

	QueryPerformanceCounter(&la1);

	freq_1 = 0;
	freq_1_count = 0;
	static int last_z =	0;
	int	delta =	0;

	//на сколько частей делится круг в соответствии с частотой дискретизации
	double	K =	2*PI/samplerate;

	double	t =	_time_*K;
	
	double	m =	0;

	int OverloadCount=0;	//сколько раз был клиппинг (за пределы -32768...32767)
	
	//for(int i=0; i<size/2; i++, _time_++)
	for(int i=0; i<size/2; i+=2, _time_++)
	{
		m=0;

		//***^^^*** свяазано с модуляцией
		g_modulation_t	+=	g_step_modulation;

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

				m			+=Piano(k,Keys[k].Ampl,freq,Keys[k].t,phase, flag_one, freq_actual);
				
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
					Keys[k].midi_key_press=0;
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
		//диапазон от -32768 до +32767

		//если выходит за пределы
		if (m>32767) 
		{
			m=32767;		//установка максимального значения
			Overload=-10;	//установка флага перегрузки
			OverloadCount++;
			//CorrectAmplitude-=0.01;
		}

		//если выходит за пределы минимума
		else if (m < -32768) 
		{
			m = -32768;		//установка минимального значения
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

		plbuf[i]  =z; //left channel
		plbuf[i+1]=z; //right channel
	}

	if (OverloadCount==0) Overload++;

	//запись в файл
	//??????
	if (g_mainwindow)
	if (g_mainwindow->m_write_rawdata_pcm)
	{
		CFile file;
		if (file.Open("rawdata.pcm", file.modeWrite))
		{
			file.SeekToEnd();
			file.Write(plbuf,size);
			file.Close();
		}
	}


	QueryPerformanceCounter(&la2);

	//QueryPerformanceFrequency(&la3);


	//FillBufferTickCount=la2.QuadPart;

	if (size<COPYBUFFER_SIZE)
	{
		memcpy(CopyBuffer, plbuf, size);
	}

	FillBufferTickCount=DWORD((la2.QuadPart-la1.QuadPart)/1000.0);

	freq_1/=2;
}

extern int ASIO_buflen;
extern DWORD ASIO_PROC_BUFLEN;


void CDTFM_GeneratorDlg::OnClose() 
{
	OnButtonMidiClose();
	DigIndicator::Free();
	DigIndicatorValue::Free();
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

	ini.SetDoubleValue(atof(m_garmonic_5),"Garmonic5");
	ini.SetDoubleValue(atof(m_garmonic_6),"Garmonic6");
	ini.SetValue(m_check_saw,"CheckSaw");
	ini.SetValue(BaseKeyboard,"BaseKeyboard");
	ini.SetValue((int)cCircleSlider_filterspeed->GetValue(), "FilterSpeed");
	ini.SetValue((int)cCircleSlider_attack->GetValue(), "Attack");
	ini.SetValue((int)cCircleSlider_modulation->GetValue(), "Modulation");
	ini.SetValue((int)cCircleSlider_detune->GetValue(), "Detune");
	ini.SetValue((int)cCircleSlider_echo->GetValue(), "Echo");
	ini.SetValue((int)cCircleSlider_6->GetValue(), "ModulationParam1");
	ini.SetValue((int)cCircleSlider_7->GetValue(), "ModulationParam2");

	ini.SetValue(atoi(m_midi_open_str.GetBuffer(0)),"MidiDevice");

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

	if (nIDEvent==100)
	{
			
		if(demo[counter] > -1){
			
			int k=demo[counter];
			if (k!=-1)
			{
				ZeroMemory(&Keys[k],sizeof(KEY));

				Keys[k].fRez1 = rezMax;
				Keys[k].fRez2 = rezMax;
				Keys[k].fRez3 = rezMax;

			
			
				Keys[k].press=TRUE;
				Keys[k].Ampl=atoi(g_amplitude_global);
				Keys[k].decrement=0.3;
				Keys[k].t = 0;
			}
		
		}
		
		counter ++;
		
		if(counter >= 47){
			
			counter = 0;
			KillTimer(100);
			
		}
		
		return;
		
	}
	
	GetData;

	char buf1[32];
	//????
	ltoa(FillBufferTickCount,buf1,10);
	m_tick_count_fill_buffer.SetWindowText(buf1);

	if (nIDEvent==1)
	{
/*		RECT rt_main,rt;

	
		m_static_slider1.GetWindowRect(&rt);
		ScreenToClient(&rt);

		GetWindowRect(&rt_main);




		CString g;
		g.Format("%i:%i KEY_X=%i KEY_Y=%i win.x=%i win.y=%i rt.x=%i rt.y=%i", g_last_mouse_point.x, g_last_mouse_point.y, KEY_X,KEY_Y, rt_main.left, rt_main.top, rt.left, rt.top);
	
		//m_string_status_text.SetWindowText(g.GetBuffer(0));
		m_string_status_text=g;//.SetWindowText(g.GetBuffer(0));
		//m_status_text.InvalidateRect(NULL);
		PutData;
		*/
		return;
	}

	//???????????
	rezMin = strtod(m_rez_min.GetBuffer(0),NULL);
	rezMax = strtod(m_rez_max.GetBuffer(0),NULL);;


	no_sustain=m_no_sustain;

	CString s = m_garmonic_5;
	garmonic_5=strtod(s.GetBuffer(0),NULL);

	s = m_garmonic_6;
	garmonic_6=strtod(s.GetBuffer(0),NULL);

	s = m_attack;
	ADSR_Attack = strtod(s.GetBuffer(0),NULL);

	double m_scale = atoi(m_edit_scale.GetBuffer(0));
	if (m_scale<2 || m_scale>48) m_scale = 12;
	scale = pow(2.0,1.0/m_scale);

	double m_base_a	= atoi(m_string_base_a.GetBuffer(0));
	BASE_A = m_base_a;


	//________________________________________________________
	//***^^^*** свяазано с модуляцией
	g_modulation_amplitude_value = atoi(m_modulation_amplitude.GetBuffer(0));
	s =	m_edit_modilation;

	g_ModulationWheel	= strtod(s.GetBuffer(0),NULL);
	int Volume=int(cCircleSlider_modulation->GetValue());

	g_step_modulation=g_ModulationWheel * Volume/127.0/ASIO_buflen;

	char str[16];
	itoa(g_modulation_wheel_2,str,10);
	m_edit_modulation_wheel=str;

	if (NeedUpdateMidiEvent)
	{
		//обновляем если есть изменения
		if (m_edit!=g_edit_list_midi)
		{
			m_edit=g_edit_list_midi;
		}
	}

	g_amplitude_global=m_amplitude;

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


	AMPLITUDE_DECREMENT=(m_slider_decrement.GetPos()*20+10)/128.0;

	m_slider_decrement_double=AMPLITUDE_DECREMENT;

	m_edit_freq=freq_1*2;
	if (freq_1 != 0) m_wave_len = 330/m_edit_freq;
	else	m_wave_len = 0;

	PutData;

	
	RECT rt;
	m_pianoroll.GetWindowRect(&rt);
	ScreenToClient(&rt);

	
	KEY_X=rt.left;
	KEY_Y=rt.top;
	
	//перересовка пианоролла
	
	CDC *pdc=m_pianoroll.GetDC();
	//DrawPiannoRoll(pdc, &m_level_control, pianoroll_x-x, 0, 60);
	DrawPiannoRoll(pdc, &m_level_control, 0, 0, 60);
	ReleaseDC(pdc);


	if (cCircleSlider_attack->redraw)
	{
		cCircleSlider_attack->redraw=0;
		CDC *dc=GetDC();
		cCircleSlider_attack->OnPaint(dc);
		ReleaseDC(dc);

	}

	MaxSound=0;
	//Overload=0;
	CDC *dc=GetDC();

	int y=400;

	int HEI=50;
	int LEN=200;
	dc->Rectangle(0,y-HEI,LEN,y+HEI);

	int j=0;
	for(int i=0; i<0;i++)
	{
		if (abs(CopyBuffer[i])<5) { j=i; break;}
	}

	int z=0;
	for(; i<j+LEN;i++)
	{

		//???????
		short val=short(CopyBuffer[i]/32768.0*HEI);
		if (val>=HEI) val=HEI-1;
		if (val<=-HEI) val=-HEI+1;
		dc->LineTo(z++, y+val);
	}

	ReleaseDC(dc);

	CDialog::OnTimer(nIDEvent);

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

	//если режим записи
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
					g_edit_list_midi="";
				}

				g_edit_list_midi += s+ENDL;
			}

			BYTE nChar=mm.b[1]; //номер контрола
			BYTE Volume=mm.b[2]; //значение

			int z=mm.b[0]>>4;	//номер№2 контролла

			if (z==11 && nChar==9)
			{
				cCircleSlider_attack->SetValue(Volume);
				cCircleSlider_attack->redraw=1;
			}

			if (NeedUpdateModulation)
			{
				//если подвинули колесо модуляции
				if (z==11 && nChar==1)
				{
					//step_modulation=ModulationWheel * Volume/127.0/2048.0;
					//step_modulation=ModulationWheel * Volume/127.0/512;
					
					g_step_modulation=g_ModulationWheel * Volume/127.0/ASIO_buflen;
					
					g_modulation_wheel_2=Volume;
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
				if (g_mainwindow->m_use_velocity && (Volume!=0))
				{
					MidiKeyPress2(nChar, 127);
				}
				else
				{
					MidiKeyPress2(nChar, Volume);
				}
				//MidiKeyPress(nChar, Volume);
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
		//MessageBox("File is busy");
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
		if (nChar>=32 && nChar<128)
		{
			if (md[j].status>0)
			{

				Keys[nChar].press=1;
				
				if (g_mainwindow->m_use_velocity == TRUE)
				{
					//???????
					Keys[nChar].Ampl=atoi(g_amplitude_global);
				}
				else
				{
					Keys[nChar].Ampl=md[j].status*CurrentAmplitude/127;
				}
				
				Keys[nChar].ResetFilter();
				Keys[nChar].decrement=0;
				Keys[nChar].midi_key_press=1;
			}
			else
			{
				Keys[nChar].decrement=AMPLITUDE_DECREMENT;
			}


			
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
	for(int i=0; i<128; i++)
	{
		Keys[i].Ampl=0;
		Keys[i].press=0;
		Keys[i].t=0;
	}
}

void CDTFM_GeneratorDlg::OnMove(int x, int y) 
{
	//????

	
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
		//если клавиша еще не отпущена возврат
		if (Keys[key].key_unpress==FALSE) return;
		//if (Keys[key].press==true) return;

		//if (Keys[key].press==1) return;

		//?????????
		Keys[key].fRez1 = rezMax;
		Keys[key].fRez2 = rezMax;
		Keys[key].fRez3 = rezMax;



		Keys[key].press=true;
		Keys[key].midi_key_press=1;

		Keys[key].Ampl=atoi(g_amplitude_global)*value/127.0;

		//????
		Keys[key].A=Keys[key].Ampl;
		
		//Keys[key].A_add=ADSR_Attack;//0.6;

		//??????????????????????????
		//атака
		double d=cCircleSlider_attack->GetValue();
		Keys[key].A_add=40/(d+1);

		Keys[key].Ampl=0;

		//если равно 0, то клавиша будет играть бесконечно
		Keys[key].decrement=0;
		
		//после нажатия клавиша сразу будет "отпущена"
		//это такие инструменты как пианино, струнные
		if (no_sustain)
		{
			Keys[key].decrement=AMPLITUDE_DECREMENT;
		}


		Keys[key].t=0;	//время функции sin
		
	}
	else 
	{
		Keys[key].decrement=AMPLITUDE_DECREMENT;
		Keys[key].key_unpress=TRUE;
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


int gMouseMove=FALSE;

//отработка нажатия левой клавиши мыши
//нужно начать воспроизведение звука
//если курсор попадает в зону пианоролла
void CDTFM_GeneratorDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	
	
	//Overload=false;
	GetData;

	CDialog::OnLButtonDown(nFlags, point);

	//если указатель мыши за пределами пианноролла - возврат
	int flag_out_pianoroll=0;
	if (point.y<KEY_Y) flag_out_pianoroll=1;
	if (point.y> (KEY_Y+KEY_H)) flag_out_pianoroll=1;
	if (point.x<KEY_X) flag_out_pianoroll=1;

	//if (flag_out_pianoroll) return;

	if (flag_out_pianoroll)
	{
		for(int i=0; i<128; i++)
		{
			if (!Keys[i].midi_key_press)
			{
				Keys[i].decrement=AMPLITUDE_DECREMENT;
			}
			
		}
		return;
	}



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

	if (key_real>=128) return;
	
	if (gMouseMove && Keys[key_real].press==TRUE) 
	{
		gMouseMove=FALSE;
		return;
	}


	Keys[key_real].fRez1 = rezMax;
	Keys[key_real].fRez2 = rezMax;
	Keys[key_real].fRez3 = rezMax;
	Keys[key_real].press=TRUE;
	Keys[key_real].Ampl=atoi(g_amplitude_global);
	Keys[key_real].decrement=0;//звук будет звучать постоянно
	
	//если в момент нажатия клавиши нажата CTRL 
	if ((nFlags & MK_CONTROL) && m_ctrl_key_use) 
	{
		Keys[key_real].decrement=0;//звук будет звучать постоянно
		Keys[key_real].midi_key_press=1; //редактирование слайдеров не заглушит звук
	}
	else 
	{
		if (m_piano_mouse_click==0)
		{
			Keys[key_real].decrement=AMPLITUDE_DECREMENT;
		}
		else
		{
			Keys[key_real].decrement=0;
			for(int i=0; i<128;i++)
			{
				if (i==key_real) continue;
				//Keys[i].press=FALSE;
				Keys[i].decrement=AMPLITUDE_DECREMENT;
			}
		}
	}
	
	Keys[key_real].t=0;
	

}


void CDTFM_GeneratorDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	g_last_mouse_point=point;

/*	RECT rt_m,rt;
	GetWindowRect(&rt_m);
	m_static_slider1.GetWindowRect(&rt);

	CString g;
	g.Format("%i:%i KEY_X=%i KEY_Y=%i win.x=%i win.y=%i",point.x,point.y,KEY_X,KEY_Y, rt_m.left,rt_m.top, rt.left,rt.top);
	m_status_text.SetWindowText(g.GetBuffer(0));
*/

	int oldx, oldy;

	oldx=cCircleSlider_attack->xSliderStart;
	oldy=cCircleSlider_attack->ySliderStart;


	cCircleSlider_attack->OnMouseMove(nFlags, point);
	cCircleSlider_modulation->OnMouseMove(nFlags, point);
	cCircleSlider_detune->OnMouseMove(nFlags, point);
	cCircleSlider_filterspeed->OnMouseMove(nFlags, point);
	cCircleSlider_echo->OnMouseMove(nFlags, point);

	cCircleSlider_6->OnMouseMove(nFlags, point);
	cCircleSlider_7->OnMouseMove(nFlags, point);

	if (cCircleSlider_6->pSlider->flagPaint == true)
	{
		CDC *dc=GetDC();
		cCircleSlider_6->OnPaint(dc);
		ReleaseDC(dc);
	}

	if (cCircleSlider_7->pSlider->flagPaint == true)
	{
		CDC *dc=GetDC();
		cCircleSlider_7->OnPaint(dc);
		ReleaseDC(dc);
	}



	if (cCircleSlider_echo->pSlider->flagPaint == true)
	{
		CDC *dc=GetDC();
		cCircleSlider_echo->OnPaint(dc);
		ReleaseDC(dc);
	}


	if (cCircleSlider_filterspeed->pSlider->flagPaint == true)
	{
		CDC *dc=GetDC();
		cCircleSlider_filterspeed->OnPaint(dc);
		ReleaseDC(dc);
	}


	if (cCircleSlider_detune->pSlider->flagPaint == true)
	{
		CDC *dc=GetDC();
		cCircleSlider_detune->OnPaint(dc);
		ReleaseDC(dc);
	}


	if (cCircleSlider_modulation->pSlider->flagPaint == true)
	{
		CDC *dc=GetDC();
		cCircleSlider_modulation->OnPaint(dc);
		ReleaseDC(dc);
	}

	if (cCircleSlider_attack->pSlider->flagPaint == true)
	{
		CDC *dc=GetDC() ;
		cCircleSlider_attack->OnPaint(dc);
		ReleaseDC(dc);

		if ( (oldx!=cCircleSlider_attack->xSliderStart) || (oldy!=cCircleSlider_attack->ySliderStart))
		{
			
			//Invalidate(false);
			int x=cCircleSlider_attack->xSliderStart,y=cCircleSlider_attack->ySliderStart,d=150;
			RECT rt={x,y,x+d,y+d};
			InvalidateRect(&rt,true);
			//Invalidate(true);
		}
	}


	//если нажата левакя кнопка мыши
	if (nFlags&MK_LBUTTON)
	{
		//???????????
		gMouseMove=TRUE;
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
	GetData;
	m_string_status_text="";
	PutData;
	
}

void CDTFM_GeneratorDlg::OnButtonAsioControlPanel() 
{
	BASS_ASIO_ControlPanel();

}

void CDTFM_GeneratorDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	GetData;

	CDialog::OnLButtonUp(nFlags, point);

	if (m_ctrl_key_use) return;

	if (point.y<KEY_Y) return;
	if (point.y>(KEY_Y+KEY_H)) return;
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

	if (key_real>=0 && key_real<=128)// && Keys[key_real].press==FALSE) 
	{
		if (gMouseMove && Keys[key_real].press==TRUE) 
		{
			gMouseMove=FALSE;
			return;
		}

		//Keys[key_real].press=false;
		Keys[key_real].decrement=AMPLITUDE_DECREMENT;

		//Keys[key_real].Ampl=atoi(g_amplitude_global);

		
		//если в момент нажатия клавиши нажата CTRL 
		if ((nFlags & MK_CONTROL)&& m_ctrl_key_use) Keys[key_real].decrement=0;//звук будет звучать постоянно
		else 
		{
			if (m_piano_mouse_click==0)
			{
				Keys[key_real].decrement=AMPLITUDE_DECREMENT;
			}
			else
			{
				Keys[key_real].decrement=AMPLITUDE_DECREMENT;
			}
		}
		
		//Keys[key_real].t=0;
	}
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CDTFM_GeneratorDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	Invalidate(TRUE);
	CDialog::OnRButtonUp(nFlags, point);
}

void CDTFM_GeneratorDlg::OnSettingsSetasiodevice() 
{
	// TODO: Add your command handler code here
//	int a=3;
	CDialogASIOConnect d;
	d.m_remember=0;
	
	int old_asio=global_asio_index;

	int res=d.DoModal();
	ini.SetValue(d.m_remember, "RememberASIOIndex");

	if (res!=FALSE)
	{
		//AfxMessageBox("ASIO Init Error. Programm can not to be continue",MB_OK,0);
		if (old_asio != d.m_asio_index)
		{
			AfxMessageBox("ASIO device change. Please restart programm!");
		}
		return;
	}

}

void CDTFM_GeneratorDlg::OnFileExit() 
{
	// TODO: Add your command handler code here
	ExitDialog();	
	
}

void CDTFM_GeneratorDlg::OnButtonDemo() 
{
	SetTimer(100,100,0);
	
}

void CDTFM_GeneratorDlg::OnKeyboardKeysMenu() 
{
	char msg[]="Use keys for play: q,w,e,r,t,y,u,i,o,p and dies(#) keys 2,3,5,6,7,9,0\r\n"
	"Use cursor key <LEFT> and <RIGHT> to change base of keyboard";	
	;

	AfxMessageBox(msg,MB_OK,0);
}
