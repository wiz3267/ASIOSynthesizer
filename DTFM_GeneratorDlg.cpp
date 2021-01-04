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
#include "digIndicatorInput.h"

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
	m_check_saw3 = FALSE;
	m_sample_rate = 0;
	m_rez_min = _T("-0.5");
	m_rez_max = _T("4");
	m_check_filter2 = FALSE;
	m_garmonic_mode = FALSE;
	m_garmonic_base_freq = _T("50");
	m_write_wav = FALSE;
	m_check_filter1 = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CDTFM_GeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDTFM_GeneratorDlg)
	DDX_Control(pDX, IDC_LIST_PRESET, m_list_preset);
	DDX_Control(pDX, IDC_STATIC_SIN_SAW_MODE, m_static_sin_saw_mode);
	DDX_Control(pDX, IDC_STATIC_CSLIDER10, m_static_slider10);
	DDX_Control(pDX, IDC_STATIC_CSLIDER9, m_static_slider9);
	DDX_Control(pDX, IDC_EDIT_GLOBAL_FILTER2, m_global_filter2);
	DDX_Control(pDX, IDC_EDIT_GLOBAL_SS, m_global_ss2);
	DDX_Control(pDX, IDC_EDIT_GLOBAL_REZ2, m_global_rez2);
	DDX_Control(pDX, IDC_STATIC_CSLIDER8, m_static_slider8);
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
	DDX_Text(pDX, IDC_EDIT_SAMPLE_RATE, m_sample_rate);
	DDX_Text(pDX, IDC_EDIT_REZ_MIN, m_rez_min);
	DDX_Text(pDX, IDC_EDIT_REZ_MAX, m_rez_max);
	DDX_Check(pDX, IDC_CHECK_FILTER2, m_check_filter2);
	DDX_Check(pDX, IDC_CHECK_GARMONIC_MODE, m_garmonic_mode);
	DDX_Text(pDX, IDC_EDIT_GARMONIC_BASE_FREQ, m_garmonic_base_freq);
	DDX_Check(pDX, IDC_CHECK_WRITE_WAVDATA, m_write_wav);
	DDX_Check(pDX, IDC_CHECK_FILTER1, m_check_filter1);
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
	ON_BN_CLICKED(IDC_BUTTON_RND_GARMONIC, OnButtonRndGarmonic)
	ON_BN_CLICKED(IDC_BUTTON_PLUS_XSCALE_WAVEGRAPHIC, OnButtonPlusXscaleWavegraphic)
	ON_BN_CLICKED(IDC_BUTTON_MINUS_XSCALE_WAVEGRAPHIC, OnButtonMinusXscaleWavegraphic)
	ON_BN_CLICKED(IDC_CHECK_GARMONIC_MODE, OnCheckGarmonicMode)
	ON_BN_CLICKED(IDC_CHECK_WRITE_WAVDATA, OnCheckWriteWavdata)
	ON_BN_CLICKED(IDC_CHECK_SAW, OnCheckSaw)
	ON_COMMAND(ID_SETTINGS_LOADPRESETS, OnSettingsLoadpresets)
	ON_COMMAND(ID_SETTINGS_SAVEPRESETS, OnSettingsSavepresets)
	ON_LBN_SELCHANGE(IDC_LIST_PRESET, OnSelchangeListPreset)
	ON_LBN_DBLCLK(IDC_LIST_PRESET, OnDblclkListPreset)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_PRESET, OnButtonSavePreset)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_PRESET, OnButtonLoadPreset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDTFM_GeneratorDlg message handlers
int 
	SAMPLE_RATE=44100;
	//SAMPLE_RATE=44100*2;
	//SAMPLE_RATE=48000;

CFile filewav, file;
int badopenwav=0;

// Структура, описывающая заголовок WAV файла.
struct WAVHEADER
{
	WAVHEADER()
	{
		chunkId[0]='R';
		chunkId[1]='I';
		chunkId[2]='F';
		chunkId[3]='F';

		format[0]='W';
		format[1]='A';
		format[2]='V';
		format[3]='E';

		subchunk1Id[0]='f';
		subchunk1Id[1]='m';
		subchunk1Id[2]='t';
		subchunk1Id[3]=' ';

		subchunk1Size=16;
		audioFormat=1; //PCM
		numChannels=2;	//STEREO
		sampleRate=SAMPLE_RATE;
		bitsPerSample=16;

		byteRate=sampleRate * numChannels * bitsPerSample/8;

		blockAlign=numChannels * bitsPerSample/8;

		subchunk2Id[0]='d';
		subchunk2Id[1]='a';
		subchunk2Id[2]='t';
		subchunk2Id[3]='a';
	}
    // WAV-формат начинается с RIFF-заголовка:

    // Содержит символы "RIFF" в ASCII кодировке
    // (0x52494646 в big-endian представлении)
    char chunkId[4];

    // 36 + subchunk2Size, или более точно:
    // 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
    // Это оставшийся размер цепочки, начиная с этой позиции.
    // Иначе говоря, это размер файла - 8, то есть,
    // исключены поля chunkId и chunkSize.
    unsigned long chunkSize;

    // Содержит символы "WAVE"
    // (0x57415645 в big-endian представлении)
    char format[4];

    // Формат "WAVE" состоит из двух подцепочек: "fmt " и "data":
    // Подцепочка "fmt " описывает формат звуковых данных:
    
    // Содержит символы "fmt "
    // (0x666d7420 в big-endian представлении)
    char subchunk1Id[4];

    // 16 для формата PCM.
    // Это оставшийся размер подцепочки, начиная с этой позиции.
    unsigned long subchunk1Size;

    // Аудио формат, полный список можно получить здесь http://audiocoding.ru/wav_formats.txt
    // Для PCM = 1 (то есть, Линейное квантование).
    // Значения, отличающиеся от 1, обозначают некоторый формат сжатия.
    unsigned short audioFormat;

    // Количество каналов. Моно = 1, Стерео = 2 и т.д.
    unsigned short numChannels;

    // Частота дискретизации. 8000 Гц, 44100 Гц и т.д.
    unsigned long sampleRate;

    // sampleRate * numChannels * bitsPerSample/8
    unsigned long byteRate;

    // numChannels * bitsPerSample/8
    // Количество байт для одного сэмпла, включая все каналы.
    unsigned short blockAlign;

    // Так называемая "глубиная" или точность звучания. 8 бит, 16 бит и т.д.
    unsigned short bitsPerSample;

    // Подцепочка "data" содержит аудио-данные и их размер.

    // Содержит символы "data"
    // (0x64617461 в big-endian представлении)
    char subchunk2Id[4];

    // numSamples * numChannels * bitsPerSample/8
    // Количество байт в области данных.
    unsigned long subchunk2Size;

    // Далее следуют непосредственно Wav данные.
} Wavheader ;

double global_fRez2;
double global_ss2;
double global_filter2;
int GarmonicBaseFreq;


double camerton = 110.0;
double fadeOut = 1.00004; // От этого зависит время затухания клавиш пианино.
//double piano_detune = 1.005; // Погрешность настройки струн пианино. Для озвучки фильмов Чарли Чаплина лучше ставить побольше.
//double piano_detune = 1.002; // Погрешность настройки струн пианино. Для озвучки фильмов Чарли Чаплина лучше ставить побольше.
double piano_detune = 1.000;

DWORD FillBufferTickCount=0;

int counter = 0;
int demo[] = {50,-1,-1,-1,53,-1,-1,50,-1,50,55,-1,50,-1,48,-1,50,-1,-1,-1,57,-1,-1,50,-1,50,58,-1,57,-1,53,-1,50,-1,57,-1,62,-1,50,48,-1,48,45,-1,52,-1,50};

CPoint g_last_mouse_point;
CDTFM_GeneratorDlg * g_mainwindow=NULL;

BOOL no_sustain;
double garmonic_5=0;
double garmonic_6=0;
double ADSR_Attack=0;

//double globalVolume=0.5;

CircleSliderIndicator * cCircleSlider_attack=NULL;
CircleSliderIndicator * cCircleSlider_modulation=NULL;
CircleSliderIndicator * cCircleSlider_detune=NULL;
CircleSliderIndicator * cCircleSlider_filterspeed=NULL;
CircleSliderIndicator * cCircleSlider_filterspeed2=NULL;
CircleSliderIndicator * cCircleSlider_6=NULL;
CircleSliderIndicator * cCircleSlider_7=NULL;
CircleSliderIndicator * cCircleSlider_sqr=NULL;

CircleSliderIndicator * cCircleSlider_echo_time=NULL;	//время эха
CircleSliderIndicator * cCircleSlider_echo_decay=NULL;	//затухание эха
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

//CFile file;

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


//double myMin = -0.7;
//double myMax = 0.7;

double myMin = -1;
double myMax = 1;


double rezMin = -0.5;
double rezMax = 4.5;

double filterSpeed = 0;//20000*10;
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

	double pianoamp;
	int		frameCount;
	double resonance;
	double polarity;
	
	double pianostr1;
	double pianostr2;
	double pianostr3;

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

	void SetPianoRand()
	{
		pianostr1 = rand() / 16384.0 - 1.0;
		pianostr2 = rand() / 16384.0 - 1.0;
		pianostr3 = rand() / 16384.0 - 1.0;

	}

	KEY() 
	{ 
		press=0; 
		key_unpress=TRUE;

		decrement=0; Ampl=0; t=0; A=D=S=R=0; A_add=0; 
		
		pianoamp=1.0; frameCount=0; resonance=1.0; polarity=1.0;

		SetPianoRand();
		
		
		midi_key_press=0; 

		ResetFilter();


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


const garm_c=50;
double randarray[garm_c];// =    {3, 7, 17, 22, 23, 27, 29, 37, 43, 47}; // якобы случайные числа
double randarray_amplitude[garm_c];// = { 1, 0.7, 0.5, 0.9, 0.1, 0, 1, 0.9, 0.9, 0.8}; 

//double randarray2[garm_c] =    {1, 3, 7, 17, 22, 23, 27, 29, 37, 43, 47}; // 
//double randarray_amplitude2[garm_c] = { 1, 0.7, 0.5, 0.9, 0.1, 0, 1, 0.9, 0.9, 0.8}; 


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
	double static tmp1,tmp2;

	flag_one=0;

	//if (sl1 && !g_mainwindow->m_check_saw3) {flag_one++;freq_actual=freq;}	//base frequency
	if (sl1) {flag_one++;freq_actual=freq;}	//base frequency
	//if (sl2) {flag_one++;freq_actual=freq*2;}
	if (sl2) {flag_one++;freq_actual=freq;}
	
	//if (sl3) {flag_one++;freq_actual=freq*3;}
	if (sl3) {flag_one++;freq_actual=freq;}

	if (sl4) {flag_one++;freq_actual=freq;}
	
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

	double limit=20500;	//ограничение частоты

	//амплитуда сигнала
	double AMP=Ampl;

	//***^^^*** связано с амплитудной модуляцией
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
			
			//Keys[keyN].sawSource1 += freq * myconst * dt;
			//Keys[keyN].sawSource2 += freq * myconst / dt;

			//8jul2020
			//if(Keys[keyN].sawSource1 >= myMax) Keys[keyN].sawSource1 = myMin - myMax + Keys[keyN].sawSource1;
			//if(Keys[keyN].sawSource2 >= myMax) Keys[keyN].sawSource2 = myMin - myMax + Keys[keyN].sawSource2;
			
			if(Keys[keyN].sawSource1 >= myMax){
				tmp1 = Keys[keyN].sawSource1 - myMax;
				Keys[keyN].sawSource1 = myMin;
			}
			if(Keys[keyN].sawSource2 >= myMax){
				tmp2 = Keys[keyN].sawSource2 - myMax;
				Keys[keyN].sawSource2 = myMin;
			}

			
			//if(Keys[keyN].sawSource1 >= myMax) Keys[keyN].sawSource1 = myMin;
			//if(Keys[keyN].sawSource2 >= myMax) Keys[keyN].sawSource2 = myMin;
			
			double sawSource = Keys[keyN].sawSource1 + Keys[keyN].sawSource2+ tmp1 + tmp2;

			if (g_mainwindow->m_check_filter1 == 0)
			{
				Keys[keyN].filter1=sawSource;
			}

			else
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
				
						
			k += Keys[keyN].filter1 * sl1/100.0; // базовый звук
			
	
			//k *= sl1 / 100.0;
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
		
		f=freq; 
		//floor
		//double val=floor(sin(f*t)+0.1);
		double val=sin(f*t);
		double fix=cCircleSlider_sqr->GetValue()/100.0;
		//double fix=0;

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

			//double out = 0.4 * sin(freq * t); //base freq
			double out = 0;

			for(int i = 0; i < garm_c; i ++) 
			{
				//out += 0.1/(i+1) * sin(freq * randarray[i] * t);
				if (randarray[i])
				{
					double f=freq * i;
					if (f<limit)
					{
						out += randarray_amplitude[i] * sin(f*t);
					}
				}
			}

			 // дальше уже знакомый код фильтра, только на вход подаём переменную out
			filterSpeed = pow(2, 9 + cCircleSlider_filterspeed -> GetValue() / 10.0);
			
			Keys[keyN].fRez2 -= (Keys[keyN].fRez2 - rezMin) / filterSpeed;
		
			/*if ( (Keys[keyN].fRez2-rezMin)<0.5)
			{
				Keys[keyN].ResetFilter();
			}*/

			
			Keys[keyN].ss2 += (out - Keys[keyN].filter2) / pow(4, 6 - Keys[keyN].fRez2);
			//Keys[keyN].ss1 /= 1.02;
			Keys[keyN].ss2 /= 1.01 ;
			Keys[keyN].filter2 += Keys[keyN].ss2;

			global_fRez2=Keys[keyN].fRez2;
			global_ss2=Keys[keyN].ss2;
			global_filter2=Keys[keyN].filter2;


			double filterSpeed3 = pow(2, 9 + cCircleSlider_filterspeed2 -> GetValue() / 10.0);
			
			Keys[keyN].fRez3 -= (Keys[keyN].fRez3 - rezMin) / filterSpeed3;
			Keys[keyN].ss3 += (out - Keys[keyN].filter3) / pow(4, 6 - Keys[keyN].fRez3);
			Keys[keyN].ss3 /= 1.01 ;
			Keys[keyN].filter3 += Keys[keyN].ss3;


			
			int filter_on=g_mainwindow->m_check_filter2;
			if (filter_on)
			{
				//k += Keys[keyN].filter2 * sl3 * 0.01; // добавляем результат в общий поток
				k += 0.5*(Keys[keyN].filter2 + Keys[keyN].filter3)* sl3 * 0.01; // добавляем результат в общий поток
			}
			else
			{
				k += out * sl3 * 0.01;
			}

		}

	
	
	}

	//if (sl4) { f=4*freq; if (f<limit) k+=sl4/100.0*sin(f*t); }
	if (sl4) {

		double str1 = pow(piano_detune, Keys[keyN].pianostr1);
		double str2 = pow(piano_detune, Keys[keyN].pianostr2);
		double str3 = pow(piano_detune, Keys[keyN].pianostr3);
	
		double freq1 = freq / 70;
		
        if(sin(Keys[keyN].frameCount / camerton * freq1) * Keys[keyN].polarity < 0){
		
			Keys[keyN].polarity = -Keys[keyN].polarity;
            Keys[keyN].resonance = 1.0;
			
        }
		
		Keys[keyN].pianoamp /= fadeOut;
		Keys[keyN].resonance /= 1.01;
		
		double fm = 50.0 * sin( Keys[keyN].frameCount / camerton * freq1 * floor(12 / freq1)) * Keys[keyN].resonance;
		
		double fm1 = 50.0 * sin( Keys[keyN].frameCount / camerton * freq1 * floor(12 / freq1) * str1) * Keys[keyN].resonance;
		double fm2 = 50.0 * sin( Keys[keyN].frameCount / camerton * freq1 * floor(12 / freq1) * str2) * Keys[keyN].resonance;
		double fm3 = 50.0 * sin( Keys[keyN].frameCount / camerton * freq1 * floor(12 / freq1) * str3) * Keys[keyN].resonance;
		
		double garmony = (Keys[keyN].frameCount + fm1) / camerton * freq1;
		double k1 = Keys[keyN].pianoamp * (sin(garmony) + sin(garmony * 2.0));
		
		garmony = (Keys[keyN].frameCount + fm2) / camerton * freq1;
		k1 += Keys[keyN].pianoamp * (sin(garmony) + sin(garmony * 2.0));
		
		garmony = (Keys[keyN].frameCount + fm3) / camerton * freq1;
		k1 += Keys[keyN].pianoamp * (sin(garmony) + sin(garmony * 2.0));
		
		k += k1 * sl4 / 100;
		
		Keys[keyN].frameCount ++;

	}
	
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

//>>>>>>>>>
int **blackKeyBufData = NULL;
int blackKeyBufWidth = -1;
int blackKeyBufHeight = -1;

void BlackKeyBuf_Build( int nOct, int whiteKeyW, int whiteKeyH, int blackKeyW, int blackKeyH )
{
	int		i, j, k;
	int		x, y;
	int		realKeyNum;

	blackKeyBufWidth = nOct * whiteKeyW * 7;
	blackKeyBufHeight = whiteKeyH;

	blackKeyBufData = new int* [whiteKeyH];
	
	for( i = 0; i < whiteKeyH; i++ )
	{
		blackKeyBufData[i] = new int [blackKeyBufWidth];
	}

	for( i = 0; i < whiteKeyH; i++ )
	{
		for( j = 0; j < blackKeyBufWidth; j++ )
			blackKeyBufData[i][j] = 0;
	}

	for( i = 0; i < nOct; i++ )
	{
		for( j = 0; j < 5; j++ )
		{
			if (j == 0) k = 1;
			if (j == 1) k = 2;
			if (j == 2) k = 4;
			if (j == 3) k = 5;
			if (j == 4) k = 6;

			realKeyNum = 12 * i;
			
			if (j == 0) realKeyNum += 1;
			if (j == 1) realKeyNum += 3;
			if (j == 2) realKeyNum += 6;
			if (j == 3) realKeyNum += 8;
			if (j == 4) realKeyNum += 10;

			int		xc = whiteKeyW * (7 * i + k);

			int		x1 = xc - blackKeyW / 2;
			int		x2 = xc + blackKeyW / 2;
			int		y1 = 0;
			int		y2 = blackKeyH;

			for( y = y1; y <= y2; y++ )
			{
				for( x = x1; x <= x2; x++ )
				{
					blackKeyBufData[y][x] = realKeyNum + 1;
				}
			}
		}
	}
}

void BlackKeyBuf_Destroy( )
{
	int		i;

	if (blackKeyBufData != NULL)
	{
		for( i = 0; i < blackKeyBufHeight; i++ )
		{
			if (blackKeyBufData[i] != NULL)
			{
				delete [] blackKeyBufData[i];
				blackKeyBufData[i] = NULL;
			}
		}
		blackKeyBufData = NULL;
	}
	
	blackKeyBufWidth = -1;
	blackKeyBufHeight = -1;
}

int BlackKeyBuf_GetInfo( int mouseX, int mouseY )
{
	int		key;
	
	if (mouseX < 0) return -1;
	if (mouseX >= blackKeyBufWidth) return -1;
	if (mouseY < 0) return -1;
	if (mouseY >= blackKeyBufHeight) return -1;

	key = blackKeyBufData[mouseY][mouseX];

	if (key == 0) return 0;
	return key;
}
//>>>>>>>>>


void CDTFM_GeneratorDlg::SetIniValue(char *fname)
{
	srand(GetTickCount()%65535);	//init rnd
	{
		for(int i=0; i<128; i++)
		{
			Keys[i].SetPianoRand();
		}
	}


	for(int i=0; i<garm_c;i++)
	{
		CString s;
		s.Format("Garm%i",i);
			
		ini.QueryDoubleValue(randarray[i], s.GetBuffer(0));
		
		s.Format("GarmAmpl%i",i);
		ini.QueryDoubleValue(randarray_amplitude[i], s.GetBuffer(0));//randarray_amplitude2[i];
	}

	BaseKeyboard=ini.QueryValue("BaseKeyboard");
	if (!BaseKeyboard) BaseKeyboard=59;

	cCircleSlider_echo_time -> SetValue(ini.QueryValue("EchoTime"));
	cCircleSlider_echo_decay -> SetValue(ini.QueryValue("EchoDecay"));
	cCircleSlider_sqr -> SetValue(ini.QueryValue("SqrWaveToSin"));
	cCircleSlider_6	->SetValue(ini.QueryValue("ModulationParam1"));
	cCircleSlider_7	->SetValue(ini.QueryValue("ModulationParam2"));
	cCircleSlider_attack->SetValue(ini.QueryValue("Attack"));
	cCircleSlider_modulation->SetValue(ini.QueryValue("Modulation"));
	cCircleSlider_detune->SetValue(ini.QueryValue("Detune"));
	cCircleSlider_filterspeed->SetValue(ini.QueryValue("FilterSpeed"));
	cCircleSlider_filterspeed2->SetValue(ini.QueryValue("FilterSpeed2"));

	int temp=ini.QueryValue("MidiDevice");
	char buf_midi[8];
	itoa(temp,buf_midi,10);
	m_midi_open_str=buf_midi;

	m_garmonic_5=ini.QueryString("Garmonic5");
	m_garmonic_6=ini.QueryString("Garmonic6");
	

	m_asio_device=global_asio_index;
	m_size_asio_buffer=ASIO_buflen;

	m_sample_rate=SAMPLE_RATE;

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


		m_check_saw3=ini.QueryValue("CheckSaw");
		m_garmonic_mode=ini.QueryValue("GarmonicMode");
		m_use_velocity=ini.QueryValue("UseVelocity");
		m_no_sustain=ini.QueryValue("NoSustain");
		m_piano_mouse_click=ini.QueryValue("PianoMouseClick");
		m_ctrl_key_use=ini.QueryValue("CtrlKeyUse");
		m_check_filter1=ini.QueryValue("CheckFilter1");
		m_check_filter2=ini.QueryValue("CheckFilter2");
		m_string_base_a=ini.QueryString("EditBaseA");

		m_rez_max=ini.QueryString("RezMax2");
		m_rez_min=ini.QueryString("RezMin2");

		PutData;
}

BOOL CDTFM_GeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	menu.LoadMenu(IDR_MENU_MAIN);
	SetMenu(&menu);

	g_mainwindow=this;

	m_list_preset.AddString("default");
	for(int i=1; i<10;i++)
	{
		CString k;
		k.Format("preset%i",i);
		m_list_preset.AddString(k);
	}


	RECT rt, rt2, rt3, rt4, rt5, rt6, rt7,rt8, rt9, rt10;
	m_static_slider1.GetWindowRect(&rt);
	m_static_slider2.GetWindowRect(&rt2);
	m_static_sslider3.GetWindowRect(&rt3);
	m_static_slider4.GetWindowRect(&rt4);
	m_static_slider5.GetWindowRect(&rt5);
	m_static_slider6.GetWindowRect(&rt6);
	m_static_slider7.GetWindowRect(&rt7);
	m_static_slider8.GetWindowRect(&rt8);
	m_static_slider9.GetWindowRect(&rt9);
	m_static_slider10.GetWindowRect(&rt10);
	
	ScreenToClient(&rt);
	ScreenToClient(&rt2);
	ScreenToClient(&rt3);
	ScreenToClient(&rt4);
	ScreenToClient(&rt5);
	ScreenToClient(&rt6);
	ScreenToClient(&rt7);
	ScreenToClient(&rt8);
	ScreenToClient(&rt9);
	ScreenToClient(&rt10);


	int x=rt.left,y=rt.top;

	//>>>>>>>>>>>>>
	BlackKeyBuf_Build( 10, KEY_L, KEY_H, 6, 38 );
	//>>>>>>>>>>>>>

	cCircleSlider_echo_time = new CircleSliderIndicator(rt9.left, rt9.top, CircleSliderIndicator::typeOfElem4, 0,100, 0, true, 3,
											  DigIndicatorValue::signTypeNotShow);


	cCircleSlider_echo_decay = new CircleSliderIndicator(rt10.left, rt10.top, CircleSliderIndicator::typeOfElem4, 0,100, 0, true, 3,
											  DigIndicatorValue::signTypeNotShow);


	cCircleSlider_sqr = new CircleSliderIndicator(rt8.left, rt8.top, CircleSliderIndicator::typeOfElem4, 0,100, 0, true, 3,
											  DigIndicatorValue::signTypeNotShow);


	cCircleSlider_6= new CircleSliderIndicator(rt6.left, rt6.top, CircleSliderIndicator::typeOfElem4, 0,100, 0, true, 3,
											  DigIndicatorValue::signTypeNotShow);


	cCircleSlider_7= new CircleSliderIndicator(rt7.left, rt7.top, CircleSliderIndicator::typeOfElem4, 0,100, 0, true, 3,
											  DigIndicatorValue::signTypeNotShow);


	cCircleSlider_attack = new CircleSliderIndicator(x,y, CircleSliderIndicator::typeOfElem4, 0,127, 0, true, 3,
											  DigIndicatorValue::signTypeNotShow);


	
	cCircleSlider_modulation = new CircleSliderIndicator(rt2.left,rt2.top, 
		CircleSliderIndicator::typeOfElem4, 0,127, 0, true, 3, DigIndicatorValue::signTypeNotShow);



	cCircleSlider_detune = new CircleSliderIndicator(rt3.left,rt3.top, 
		CircleSliderIndicator::typeOfElem4, 0,100, 0, true, 3, DigIndicatorValue::signTypeNotShow);



	cCircleSlider_filterspeed=new CircleSliderIndicator(rt4.left,rt4.top, 
		CircleSliderIndicator::typeOfElem4, 0,100, 0, true, 3, DigIndicatorValue::signTypeNotShow);;

	

	cCircleSlider_filterspeed2 = new CircleSliderIndicator(rt5.left,rt5.top, 
		CircleSliderIndicator::typeOfElem4, 0,100, 0, true, 3, DigIndicatorValue::signTypeNotShow);;


	SetIniValue();
	OnCheckSaw();

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
		//PutData;

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

	
	SetFocus();
	//HANDLE hThread=GetCurrentThread();
	//SetThreadPriority(hThread, THREAD_PRIORITY_HIGHEST);

	//ShowWindow(SW_NORMAL);
	SetForegroundWindow();

//	ShowGarmonics();

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
		cCircleSlider_filterspeed2->OnPaint(dc);

		cCircleSlider_6->OnPaint(dc);
		cCircleSlider_7->OnPaint(dc);

		cCircleSlider_sqr->OnPaint(dc);

		cCircleSlider_echo_decay->OnPaint(dc);
		cCircleSlider_echo_time->OnPaint(dc);
		

		ShowGarmonics();
		ChangeGarmonicMouse(0, 0, TRUE);
		
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
		bool	enterPressed[10];		
		
		//>>>>
		enterPressed[0] = cCircleSlider_attack->HandleKey( nChar );
		enterPressed[1] = cCircleSlider_modulation->HandleKey( nChar );		
		enterPressed[2] = cCircleSlider_detune->HandleKey( nChar );
		enterPressed[3] = cCircleSlider_filterspeed->HandleKey( nChar );		
		enterPressed[4] = cCircleSlider_filterspeed2->HandleKey( nChar );
		enterPressed[5] = cCircleSlider_6->HandleKey( nChar );		
		enterPressed[6] = cCircleSlider_7->HandleKey( nChar );
		enterPressed[7] = cCircleSlider_sqr->HandleKey( nChar );		
		enterPressed[8] = cCircleSlider_echo_time->HandleKey( nChar );
		enterPressed[9] = cCircleSlider_echo_decay->HandleKey( nChar );		

		bool	isCaptured = false;

		if (cCircleSlider_attack->IsTextInputCaptured( )) isCaptured = true;
		if (cCircleSlider_modulation->IsTextInputCaptured( )) isCaptured = true;
		if (cCircleSlider_detune->IsTextInputCaptured( )) isCaptured = true;
		if (cCircleSlider_filterspeed->IsTextInputCaptured( )) isCaptured = true;
		if (cCircleSlider_filterspeed2->IsTextInputCaptured( )) isCaptured = true;
		if (cCircleSlider_6->IsTextInputCaptured( )) isCaptured = true;
		if (cCircleSlider_7->IsTextInputCaptured( )) isCaptured = true;
		if (cCircleSlider_sqr->IsTextInputCaptured( )) isCaptured = true;
		if (cCircleSlider_echo_time->IsTextInputCaptured( )) isCaptured = true;
		if (cCircleSlider_echo_decay->IsTextInputCaptured( )) isCaptured = true;

		if (nChar == VK_RETURN)
		{
			CDC	*pDC = GetDC();
			
			if (enterPressed[0]) cCircleSlider_attack->OnPaint( pDC );
			if (enterPressed[1]) cCircleSlider_modulation->OnPaint( pDC );
			if (enterPressed[2]) cCircleSlider_detune->OnPaint( pDC );
			if (enterPressed[3]) cCircleSlider_filterspeed->OnPaint( pDC );
			if (enterPressed[4]) cCircleSlider_filterspeed2->OnPaint( pDC );
			if (enterPressed[5]) cCircleSlider_6->OnPaint( pDC );
			if (enterPressed[6]) cCircleSlider_7->OnPaint( pDC );
			if (enterPressed[7]) cCircleSlider_sqr->OnPaint( pDC );
			if (enterPressed[8]) cCircleSlider_echo_time->OnPaint( pDC );
			if (enterPressed[9]) cCircleSlider_echo_decay->OnPaint( pDC );

			if (enterPressed[0]) cCircleSlider_attack->OnClearArea( pDC );
			if (enterPressed[1]) cCircleSlider_modulation->OnClearArea( pDC );
			if (enterPressed[2]) cCircleSlider_detune->OnClearArea( pDC );
			if (enterPressed[3]) cCircleSlider_filterspeed->OnClearArea( pDC );
			if (enterPressed[4]) cCircleSlider_filterspeed2->OnClearArea( pDC );
			if (enterPressed[5]) cCircleSlider_6->OnClearArea( pDC );
			if (enterPressed[6]) cCircleSlider_7->OnClearArea( pDC );
			if (enterPressed[7]) cCircleSlider_sqr->OnClearArea( pDC );
			if (enterPressed[8]) cCircleSlider_echo_time->OnClearArea( pDC );
			if (enterPressed[9]) cCircleSlider_echo_decay->OnClearArea( pDC );
		
			ReleaseDC( pDC );

			for( int i = 0; i < 10; i++ )
			{
				if (enterPressed[i]) nChar = -1;
			}
		}

		if (isCaptured) nChar = -1;

		//>>>>

		if (nChar==VK_LEFT)
		{

			if (BaseKeyboard>11) BaseKeyboard--;
		
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


	//return CDialog::PreTranslateMessage(pMsg);

	return 0;
}

double freq_1=0;
int freq_1_count=0;

const COPYBUFFER_SIZE=16384;
short int CopyBuffer[COPYBUFFER_SIZE];

const int MaxDelayBufferSize=2048*50;

int DelayBufferSize=2048*5;
int DelayBufferWritePosition=0;
int DelayBufferReadPosition=0;
int delay_buffer_full=1;

short int DelayBuffer[MaxDelayBufferSize]={0};

int numSamples=0;	//сколько записано в файл

//самая важная функция - заполнение буфера звуковыми сгенерированными данными
//size размер буфера в байтах, size/2 - число выборок, т.к. одна выборка имеет тип WORD (16bit)
void FillBuffer(short *plbuf, int size, int samplerate)
{
	//if (DelayBuffer[0]==255)
	//{
	//	memset(DelayBuffer,0,DelayBufferSize);
	//}

	LARGE_INTEGER la1, la2;

	QueryPerformanceCounter(&la1);

	freq_1 = 0;
	freq_1_count = 0;
	static int last_z =	0;
	int	delta =	0;
	
	double	m =	0;

	int OverloadCount=0;	//сколько раз был клиппинг (за пределы -32768...32767)

	//на сколько частей делится круг в соответствии с частотой дискретизации
	double	K =	2*PI/samplerate;	
	//static double	t =	0;//_time_*K;
	//for(int i=0; i<size/2; i++, _time_++)
	for(int i=0; i<size/2; i+=2, _time_++)
	{


		m=0;

		//***^^^*** связано с модуляцией
		g_modulation_t	+=	g_step_modulation;

		//проходимся по массиву клавиш MIDI-клавиатуры
		for(int k=0; k<128; k++) 
		{
			if (Keys[k].press) 
			{
				//считаем частоту базовой гармоники для нажатой клавиши
				double		freq	=	BASE_A * pow(scale, k-60+3 - 12);

				if (g_mainwindow)
				if (g_mainwindow->m_garmonic_mode)
				{
					freq = GarmonicBaseFreq * (k-12+1);
				}
				
				//сколько чистых гармоник было в сигнале
				int			flag_one=	0;

				//частота сигнала, если была только одна гармоника
				double		freq_actual=0;
				
				static double phase;

				K=2*PI/samplerate;

				if (cCircleSlider_6 && cCircleSlider_7)
				{
					double fmodulation_f = cCircleSlider_6->GetValue(); // частота частотной модуляции
					double fmodulation_d = cCircleSlider_7->GetValue(); // глубина частотной модуляции
					//double fmodulation = 1 + (1 - pow(1.001, fmodulation_d)) * sin(Keys[k].t * pow(1.015, fmodulation_f));
					double fmodulation = 1 + (1 - pow(1.001, fmodulation_d)) * sin(Keys[k].t * pow(1.015+0.01, fmodulation_f));

					K *= fmodulation;
				}

				
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

					
					Keys[k].frameCount = 0;
					Keys[k].pianoamp = 1.0;

				}

				if (flag_one==1)
				{
					if (Keys[k].Ampl)
					{
						freq_1=freq_actual;
						freq_1_count++;
					}

				}
				else
				{
					
					//Keys[k].frameCount = 0;
					//Keys[k].pianoamp = 1.0;
				}
			}
			
		}
		
		//t+=K;

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

		plbuf[i]  =z; //left(or right) channel
		plbuf[i+1]=z; //right(or left) channel
		
		if (!delay_buffer_full)
		{
			DelayBuffer[i+DelayBufferWritePosition]=z;
			DelayBuffer[i+1+DelayBufferWritePosition]=z;
		

			DelayBufferWritePosition+=2;
			if (DelayBufferWritePosition>=DelayBufferSize)
			{	
				DelayBufferWritePosition=0;
				delay_buffer_full=1;
			}

		}
	}

	if (OverloadCount==0) Overload++;


	//QueryPerformanceFrequency(&la3);


	//FillBufferTickCount=la2.QuadPart;




	if (delay_buffer_full)// && (DelayBufferWritePosition>size))
	{
		for(int j=0; j<size/2;j++)
		{
			int delay=0;//DelayBufferReadPosition;
			int k=0;
			
			if (cCircleSlider_echo_time)
			{
			 
				DelayBufferSize=int(MaxDelayBufferSize*(cCircleSlider_echo_time->GetValue())/100.0);
				if (!DelayBufferSize) DelayBufferSize=1;

				 if (DelayBufferSize>MaxDelayBufferSize)
				 {
					DelayBufferSize=MaxDelayBufferSize;
				 }
			 
				k=DelayBufferReadPosition;
			}

			double km=0.3;
			if (cCircleSlider_echo_decay)
			{
				km=cCircleSlider_echo_decay->GetValue()*0.01;
			
			}
			
			plbuf[j]+=int(DelayBuffer[k]*km);
			//int delay2=50;
			//if (k>=delay2)
			//{
			//	plbuf[j]+=DelayBuffer[k-delay2]*km*0.1;
			//}

			if (abs(plbuf[j]) > MaxSound) MaxSound=abs(int(plbuf[j]));	//округляем double в int. все рассчеты ведутся в double, а здесь округление
			
			DelayBuffer[k]=plbuf[j];

			DelayBufferReadPosition++;

			if (DelayBufferReadPosition>=DelayBufferSize)
			{
				DelayBufferReadPosition=0;
			}

			
		}
		
	}

	if (size<COPYBUFFER_SIZE)
	{
		memcpy(CopyBuffer, plbuf, size);
	}

	//запись в файл 
	if (g_mainwindow)
		if (g_mainwindow->m_write_wav)
	{
		if (!badopenwav)
		{
			//file.SeekToEnd();
			filewav.Write(plbuf,size);
			numSamples+=size/4;
		}
	}


	QueryPerformanceCounter(&la2);


	FillBufferTickCount=DWORD((la2.QuadPart-la1.QuadPart)/1000.0);

	//freq_1/=2;
}

extern int ASIO_buflen;
extern DWORD ASIO_PROC_BUFLEN;


void CDTFM_GeneratorDlg::OnClose() 
{
	OnButtonMidiClose();
	DigIndicator::Free();
	DigIndicatorValue::Free();


	GetData;
	if (m_write_wav==1)
	{
		m_write_wav=0;
		PutData;
		OnCheckWriteWavdata();
	}

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


//сохраняет все настройки
int CDTFM_GeneratorDlg::SavePresets(char *fname)
{
	GetData;

	//save data to .ini file
	for(int i=0; i<garm_c;i++)
	{

			CString s;
			s.Format("Garm%i",i);
			
			ini.SetDoubleValue(randarray[i],s.GetBuffer(0));
			
			s.Format("GarmAmpl%i",i);
			ini.SetDoubleValue(randarray_amplitude[i],s.GetBuffer(0));//randarray_amplitude2[i];
	}


	ini.SetDoubleValue(atof(m_garmonic_5),"Garmonic5");
	ini.SetDoubleValue(atof(m_garmonic_6),"Garmonic6");
	ini.SetValue(m_check_saw,"CheckSaw");
	ini.SetValue(BaseKeyboard,"BaseKeyboard");
	ini.SetValue((int)cCircleSlider_filterspeed->GetValue(), "FilterSpeed");
	ini.SetValue((int)cCircleSlider_attack->GetValue(), "Attack");
	ini.SetValue((int)cCircleSlider_modulation->GetValue(), "Modulation");
	ini.SetValue((int)cCircleSlider_detune->GetValue(), "Detune");
	ini.SetValue((int)cCircleSlider_filterspeed2->GetValue(), "FilterSpeed2");
	ini.SetValue((int)cCircleSlider_6->GetValue(), "ModulationParam1");
	ini.SetValue((int)cCircleSlider_7->GetValue(), "ModulationParam2");
	ini.SetValue((int)cCircleSlider_sqr->GetValue(), "SqrWaveToSin");
	ini.SetValue((int)cCircleSlider_echo_time->GetValue(), "EchoTime");
	ini.SetValue((int)cCircleSlider_echo_decay->GetValue(), "EchoDecay");
	

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


	ini.SetValue(m_check_saw3,"CheckSaw");

		ini.SetValue(m_garmonic_mode,"GarmonicMode");
		ini.SetValue(m_use_velocity,"UseVelocity");
		ini.SetValue(m_no_sustain, "NoSustain");
		ini.SetValue(m_piano_mouse_click,"PianoMouseClick");
		ini.SetValue(m_ctrl_key_use, "CtrlKeyUse");
		ini.SetValue(m_check_filter1, "CheckFilter1");
		ini.SetValue(m_check_filter2,"CheckFilter2");
		ini.SetString(m_string_base_a, "EditBaseA");

		ini.SetString(m_rez_max, "RezMax2");
		ini.SetString(m_rez_min, "RezMin2");
				


	return TRUE;
}

void CDTFM_GeneratorDlg::ExitDialog()
{
	GetData;

	SavePresets();
	
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

			if ( RR==(BaseKeyboard+1))
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
			if ((scale != pow(2,1/12.0)) || g_mainwindow->m_garmonic_mode) 
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

				Keys[k].ResetFilter();

				Keys[k].press=TRUE;
				Keys[k].Ampl=atoi(g_amplitude_global);
				Keys[k].decrement=AMPLITUDE_DECREMENT;
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


	GarmonicBaseFreq=atoi(m_garmonic_base_freq.GetBuffer(0));
	
	CString s2;
	s2.Format("%f", global_fRez2);


	m_global_rez2.SetWindowText(s2);

	s2.Format("%f", global_ss2);
	m_global_ss2.SetWindowText(s2);

	s2.Format("%f", global_filter2);
	m_global_filter2.SetWindowText(s2);
	


	char buf1[32];
	
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

	m_edit_freq=freq_1;
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

	//>>>>
	{
		CDC	*dc = GetDC();
		
		cCircleSlider_attack->OnPaintDigInput( dc );
		cCircleSlider_modulation->OnPaintDigInput( dc );		
		cCircleSlider_detune->OnPaintDigInput( dc );
		cCircleSlider_filterspeed->OnPaintDigInput( dc );		
		cCircleSlider_filterspeed2->OnPaintDigInput( dc );
		cCircleSlider_6->OnPaintDigInput( dc );		
		cCircleSlider_7->OnPaintDigInput( dc );
		cCircleSlider_sqr->OnPaintDigInput( dc );		
		cCircleSlider_echo_time->OnPaintDigInput( dc );
		cCircleSlider_echo_decay->OnPaintDigInput( dc );		
		
		ReleaseDC(dc);
	}
	//>>>>

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

		BYTE type=mm.b[0]&15;
		if (mm.b[0] != 254)
		{
			if (NeedUpdateMidiEvent)
			{
				CString s;
				s.Format("%i,%i\t%i\t%i\t%i",mm.b[0]>>4,type,mm.b[1],mm.b[2],mm.b[3]);

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

			//установка громкости
			if (z==11 && nChar==7 && type==0)
			{
				//??????
				g_mainwindow->m_slider_total_volume.SetPos(int(Volume/127.0*100));
				int a=3;
				a++;
			}

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

		//??????????????
		Keys[key].A=Keys[key].Ampl;

		Keys[key].pianoamp=1;
		Keys[key].frameCount=0;


		
		
		//Keys[key].A_add=ADSR_Attack;//0.6;

		//атака
		double d=cCircleSlider_attack->GetValue();
		Keys[key].A_add=40.0/(d+1);

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


//возвращает "1" если точка pt находится в области rt)
int PointInBox(CRect rt, CPoint pt)
{
	return rt.PtInRect(pt);
}

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

	//???????
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

	CString str;
	str.Format("%i %i %i %i",key, key_real, point.x, point.y);
	SetWindowText(str);

	//>>>>>>
	int blackKeyIndex;
	int mouseX = point.x - KEY_X;
	int mouseY = point.y - KEY_Y;

	blackKeyIndex = BlackKeyBuf_GetInfo( mouseX, mouseY );
	
	if (blackKeyIndex > 0)
		key_real = 12 + blackKeyIndex-1;
	//>>>>>>

	if (key_real>=128) return;
	
	if (gMouseMove && Keys[key_real].press==TRUE) 
	{
		gMouseMove=FALSE;
		return;
	}


	Keys[key_real].ResetFilter();
	Keys[key_real].press=TRUE;
	Keys[key_real].Ampl=atoi(g_amplitude_global);
	Keys[key_real].decrement=0;//звук будет звучать постоянно
	Keys[key_real].t=0;
	Keys[key_real].frameCount = 0;
	Keys[key_real].pianoamp = 1.0;

	
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
	cCircleSlider_filterspeed2->OnMouseMove(nFlags, point);

	cCircleSlider_6->OnMouseMove(nFlags, point);
	cCircleSlider_7->OnMouseMove(nFlags, point);
	cCircleSlider_sqr->OnMouseMove(nFlags, point);

	cCircleSlider_echo_time->OnMouseMove(nFlags, point);
	cCircleSlider_echo_decay->OnMouseMove(nFlags, point);

	if (cCircleSlider_echo_decay->pSlider->flagPaint == true)
	{
		CDC *dc=GetDC();
		cCircleSlider_echo_decay->OnPaint(dc);
		ReleaseDC(dc);
	}


	if (cCircleSlider_echo_time->pSlider->flagPaint == true)
	{
		CDC *dc=GetDC();
		cCircleSlider_echo_time->OnPaint(dc);
		ReleaseDC(dc);
	}


	if (cCircleSlider_sqr->pSlider->flagPaint == true)
	{
		CDC *dc=GetDC();
		cCircleSlider_sqr->OnPaint(dc);
		ReleaseDC(dc);
	}


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



	if (cCircleSlider_filterspeed2->pSlider->flagPaint == true)
	{
		CDC *dc=GetDC();
		cCircleSlider_filterspeed2->OnPaint(dc);
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

		/*if ( (oldx!=cCircleSlider_attack->xSliderStart) || (oldy!=cCircleSlider_attack->ySliderStart))
		{
			
			//Invalidate(false);
			int x=cCircleSlider_attack->xSliderStart,y=cCircleSlider_attack->ySliderStart,d=150;
			RECT rt={x,y,x+d,y+d};
			InvalidateRect(&rt,true);
			//Invalidate(true);
		}*/
	}


	//если нажата левакя кнопка мыши
	if (nFlags&MK_LBUTTON)
	{
		//???????????
		gMouseMove=TRUE;
		OnLButtonDown(nFlags, point);
	}

	ChangeGarmonicMouse(nFlags, point, FALSE);

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

	//>>>>>>>>
	int blackKeyIndex;
	int mouseX = point.x - KEY_X;
	int mouseY = point.y - KEY_Y;

	blackKeyIndex = BlackKeyBuf_GetInfo( mouseX, mouseY );

	if (blackKeyIndex > 0)
		key_real = 12 + blackKeyIndex-1;
	//>>>>>>>>>

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
	cCircleSlider_attack->OnRButtonUp( nFlags, point );
	cCircleSlider_modulation->OnRButtonUp( nFlags, point );
	cCircleSlider_detune->OnRButtonUp( nFlags, point );
	cCircleSlider_filterspeed->OnRButtonUp( nFlags, point );
	cCircleSlider_filterspeed2->OnRButtonUp( nFlags, point );
	cCircleSlider_6->OnRButtonUp( nFlags, point );
	cCircleSlider_7->OnRButtonUp( nFlags, point );
	cCircleSlider_sqr->OnRButtonUp( nFlags, point );
	cCircleSlider_echo_time->OnRButtonUp( nFlags, point );
	cCircleSlider_echo_decay->OnRButtonUp( nFlags, point );
	
	// TODO: Add your message handler code here and/or call default
	//Invalidate(TRUE);
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


void swap(double& a, double& b)
{
	double tmp=a;
	a=b;
	b=tmp;
}

void CDTFM_GeneratorDlg::OnButtonRndGarmonic() 
{

	CString res,a;

	for(int z=0; z<garm_c; z++)
	{
		//randarray[z]=rand()%40+(rand()%100)/100.0;
		randarray[z]=0;
		randarray_amplitude[z]=0;
		if ( (rand()%10) > 5)
		{

			randarray[z]=1;//rand()%50;
			randarray_amplitude[z]=0.1+(rand()%10)/10.0;
			//randarray_amplitude[z]=0.5;//+(rand()%10)/10.0;
		}

	}

	randarray[1]=1;
	randarray_amplitude[1]=0.5;


	ShowGarmonics();

	ChangeGarmonicMouse(0,0, TRUE);
	
}

double scalex_wave_grapchic=1;


int CDTFM_GeneratorDlg::ChangeGarmonicMouse(UINT nFlags, CPoint point, bool ShowGraphic)
{

	int x1=point.x;
	int y1=point.y;

	int x=500,y=350;

	int HEI=50, LEN=8;

	CPen pen;
	pen.CreatePen(0,1,RGB(0,255,0));

	CPen pen_null;

	pen_null.CreatePen(0,0,RGB(255,255,255));

	
	CPen pen_block;
	pen_block.CreatePen(0,1,RGB(200,200,200));

	CPen pen_black;
	pen_black.CreatePen(0,1,RGB(0,0,0));

	
	CDC *dc=GetDC();

	
	for(int i=0; i<garm_c; i++)
	{

		if (
			(x1>=(x+i*LEN) && x1<=(x+i*LEN+LEN)) &&
		 (y1>=y && y1<=(y+HEI))
		 )
		{

			if (nFlags&MK_LBUTTON)
			{
				randarray[i]=1;

				randarray_amplitude[i]=(HEI-(y1-y))*1.0/HEI;

				if (randarray_amplitude[i]<0.15) 
				{
					randarray[i]=0;
					randarray_amplitude[i]=0;
				}

				ShowGraphic=1;

			

			int dt=0;
			double ampl=randarray_amplitude[i];
			//dc->Rectangle(int(x+LEN*i+dt),y+HEI-1, int(x+ LEN*i+LEN+dt), y + HEI-int(HEI *ampl ) + 1 );
			dc->SelectObject(pen_null);
			dc->Rectangle(int(x+LEN*i+dt),y+1, int(x+ LEN*i+LEN+dt), y + HEI-1);
			
			dc->SelectObject(pen_black);
			dc->Rectangle(int(x+LEN*i+dt),y+HEI-1, int(x+ LEN*i+LEN+dt), y + HEI-int(HEI *ampl ) + 1 );
			}
		}

	}

	if (ShowGraphic)
	{
	int freq=440;

	dc->Rectangle(x,y+HEI, x+ LEN*garm_c, y + HEI*2);	
	dc->MoveTo(x,y+HEI+HEI/2);
	dc->SelectObject(pen_black);
	double t=0;
	for(int x2=0; x2<LEN*garm_c;x2++)
	{
		double sum=0;
		for(int i=1; i<garm_c; i++)
		{
			if (randarray[i])
			{
				sum+=randarray_amplitude[i]*sin(freq*i*t);
			}
		}

		int y2=int(HEI*sum*0.1);
		if (y2>HEI/2) y2=HEI/2;
		if (y2<-HEI/2) y2=-HEI/2;
		dc->LineTo(x+x2, y + HEI + HEI/2+ y2);
		t+=0.00005*scalex_wave_grapchic;

	}

	ShowGarmonicStatus(0);
	}

	ReleaseDC(dc);
	

	return 0;
}

void CDTFM_GeneratorDlg::ShowGarmonics()
{
	CDC *dc=GetDC();

	int x=500,y=350;

	int HEI=50, LEN=8;


	dc->Rectangle(x,y, x+ LEN*garm_c, y + int(HEI *1 ) );

	for(int i=0; i<garm_c; i++)
	{
		if (randarray[i] == 0) continue;

		double ampl=randarray_amplitude[i];


		//if (ampl==0) ampl=1;

		double dt=randarray[i]-int(randarray[i]);
		dt*=LEN;

		if (ampl!=0)
		dc->Rectangle(int(x+LEN*i+dt),y+HEI-1, int(x+ LEN*i+LEN+dt), y + HEI-int(HEI *ampl ) + 1 );
	}

	ReleaseDC(dc);
	ShowGarmonicStatus(0);
}

void CDTFM_GeneratorDlg::ShowGarmonicStatus(int param)
{

	CString a,res;
	for(int z=0; z<garm_c; z++)
	{
		if (randarray[z] == 0 ) continue;

		a.Format("%i",z);

		res+=a;

		a.Format("(%i)",int(randarray_amplitude[z]*100));

		res+=a;
		res+=" ";
	}
		m_status_text.SetWindowText("Garmonic: "+res);

}


void CDTFM_GeneratorDlg::OnButtonPlusXscaleWavegraphic() 
{
	scalex_wave_grapchic*=2;	
	ChangeGarmonicMouse(0,0,TRUE);
	
}

void CDTFM_GeneratorDlg::OnButtonMinusXscaleWavegraphic() 
{
	scalex_wave_grapchic*=0.5;
	ChangeGarmonicMouse(0,0,TRUE);
}

void CDTFM_GeneratorDlg::OnCheckGarmonicMode() 
{

	GetData;
	Invalidate(FALSE);
	UpdateWindow();
	m_status_text.SetFocus();
}

void CDTFM_GeneratorDlg::OnCheckWriteWavdata() 
{
	// TODO: Add your control notification handler code here
	GetData;

	//если нажали опции write wav
	if (m_write_wav)
	{
		numSamples=0;

		//если не смогли открыть (например файл открыт в звуковом редакторе)
		if (!filewav.Open("rawdata.wav", file.modeWrite|file.modeCreate|file.typeBinary))
		{
			
			badopenwav=1;

			//галочку сбрасываем (как бы не даем нажать)
			m_write_wav=0;
			PutData;
		}
		else
		{
			badopenwav=0;


			filewav.SeekToBegin();
			filewav.Write(&Wavheader,sizeof(Wavheader));
		}

	}
	else
	{

		filewav.SeekToBegin();
	    Wavheader.subchunk2Size=numSamples * Wavheader.numChannels * Wavheader.bitsPerSample/8;
			
		// 36 + subchunk2Size, или более точно:
		// 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
		// Это оставшийся размер цепочки, начиная с этой позиции.
		// Иначе говоря, это размер файла - 8, то есть,
		// исключены поля chunkId и chunkSize.
		Wavheader.chunkSize=36 + Wavheader.subchunk2Size;

		filewav.Write(&Wavheader,sizeof(Wavheader));

		filewav.SeekToEnd();
		filewav.Close();

		numSamples=0;
	}
	
}

void CDTFM_GeneratorDlg::OnCheckSaw() 
{
	// TODO: Add your control notification handler code here
	GetData;
	if (m_check_saw3)
	{
		m_static_sin_saw_mode.SetWindowText("saw");
	}
	else
	{
		m_static_sin_saw_mode.SetWindowText("sin");
	}
	
}

void CDTFM_GeneratorDlg::OnSettingsLoadpresets() 
{
	// TODO: Add your command handler code here

	
}

void CDTFM_GeneratorDlg::OnSettingsSavepresets() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(false,"*.ini");
	
	dlg.DoModal();
	
}





void CDTFM_GeneratorDlg::OnSelchangeListPreset() 
{
}

//двойной клик по лисnбоксу - загрузить пресет
void CDTFM_GeneratorDlg::OnDblclkListPreset() 
{
	OnButtonLoadPreset();
}

void CDTFM_GeneratorDlg::OnButtonSavePreset() 
{
	// TODO: Add your control notification handler code here
	int n=m_list_preset.GetCurSel();
	if (n==0) return;

	CString str;
	str.Format("preset%i.ini",n);
	

	HANDLE hfile=CreateFile("Presets\\"+str,                // name of the write
                       GENERIC_WRITE,          // open for writing
                       0,                      // do not share
                       NULL,                   // default security
                       CREATE_NEW,             // create new file only
                       FILE_ATTRIBUTE_NORMAL,  // normal file
                       NULL);            
	//CreateFile("Presets\\"+str,0,0,0,0,0,0);
	CloseHandle(hfile);
	
	ini.SetFileName(str);
	SavePresets();
}

void CDTFM_GeneratorDlg::OnButtonLoadPreset() 
{
	int n=m_list_preset.GetCurSel();
	CString str;
	if (n==0) str="MidiInPiano.ini"; //по умолчанию
	else str.Format("preset%i.ini",n);
	ini.SetFileName(str);
	SetIniValue();

	InvalidateRect(NULL, FALSE);
	UpdateWindow();
	
}
