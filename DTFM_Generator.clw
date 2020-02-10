; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDialogASIOConnect
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DTFM_Generator.h"

ClassCount=4
Class1=CDTFM_GeneratorApp
Class2=CDTFM_GeneratorDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOG_ASIO_CONNECT
Resource4=IDD_DTFM_GENERATOR_DIALOG
Resource5=IDD_DIALOG_SETTINGS
Class4=CDialogASIOConnect
Resource6=IDD_ABOUTBOX (English (U.S.))

[CLS:CDTFM_GeneratorApp]
Type=0
HeaderFile=DTFM_Generator.h
ImplementationFile=DTFM_Generator.cpp
Filter=N
LastObject=CDTFM_GeneratorApp

[CLS:CDTFM_GeneratorDlg]
Type=0
HeaderFile=DTFM_GeneratorDlg.h
ImplementationFile=DTFM_GeneratorDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT_MODULATION_WHEEL

[CLS:CAboutDlg]
Type=0
HeaderFile=DTFM_GeneratorDlg.h
ImplementationFile=DTFM_GeneratorDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_DTFM_GENERATOR_DIALOG]
Type=1
Class=CDTFM_GeneratorDlg
ControlCount=65
Control1=IDOK,button,1342242817
Control2=IDC_STOP,button,1476460544
Control3=IDC_EDIT_BUFFER_COUNT,edit,1350568064
Control4=IDC_ABORT,button,1342242816
Control5=IDC_AMPLITUDE,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT1,edit,1352728644
Control9=IDC_SLIDER1,msctls_trackbar32,1342242819
Control10=IDC_SLIDER2,msctls_trackbar32,1342242819
Control11=IDC_SLIDER3,msctls_trackbar32,1342242819
Control12=IDC_SLIDER4,msctls_trackbar32,1342242819
Control13=IDC_SLIDERM2,msctls_trackbar32,1342242819
Control14=IDC_STATIC,static,1342308352
Control15=IDC_SLIDERM3,msctls_trackbar32,1342242819
Control16=IDC_SLIDERM4,msctls_trackbar32,1342242819
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_BUTTON_MIDI_OPEN,button,1342242816
Control24=IDC_BUTTON_MIDI_CLOSE,button,1476460544
Control25=IDC_EDIT_MIDI_OPEN,edit,1350631552
Control26=IDC_BUTTON_WRITE,button,1342242816
Control27=IDC_BUTTON_WRITE_STOP,button,1476460544
Control28=IDC_BUTTON_PLAY_WRITEN,button,1342242816
Control29=IDC_BUTTON_RESET,button,1342242816
Control30=IDC_CLOSE,button,1342242816
Control31=IDC_STOP_PLAY,button,1476460544
Control32=IDC_EDIT_STATUS_TEXT,edit,1350633600
Control33=IDC_STATIC,static,1342308352
Control34=IDC_EDIT_FREQ,edit,1350633600
Control35=IDC_HIDE,button,1476460544
Control36=IDC_SLIDER_DECREMENT,msctls_trackbar32,1342242840
Control37=IDC_SLIDER5,msctls_trackbar32,1342242819
Control38=IDC_SLIDER6,msctls_trackbar32,1342242819
Control39=IDC_STATIC,static,1342308352
Control40=IDC_STATIC,static,1342308352
Control41=IDC_SLIDERM5,msctls_trackbar32,1342242819
Control42=IDC_SLIDERM6,msctls_trackbar32,1342242819
Control43=IDC_STATIC,static,1342308352
Control44=IDC_STATIC,static,1342308352
Control45=IDC_EDIT_TOTAL_BUFFER_COUNT,edit,1350566016
Control46=IDC_STATIC,static,1342308352
Control47=IDC_STATIC,static,1342308352
Control48=IDC_EDIT_BUFFER_SIZE,edit,1350566016
Control49=IDC_EDIT_MIDI_NAME2,edit,1350633600
Control50=IDC_EDIT_SLIDER_DECREMENT,edit,1350633600
Control51=IDC_STATIC,static,1342308352
Control52=IDC_EDIT_BASE_A,edit,1350631552
Control53=IDC_STATIC,static,1342308352
Control54=IDC_EDIT_SCALE,edit,1350566016
Control55=IDC_STATIC,static,1342308352
Control56=IDC_STATIC,button,1342177287
Control57=IDC_STATIC,static,1342308352
Control58=IDC_EDIT_WAVE_LEN,edit,1350633600
Control59=IDC_SLIDER_TOTAL_VOLUME,msctls_trackbar32,1342242840
Control60=IDC_EDIT_MODULATION,edit,1350631552
Control61=IDC_STATIC,static,1342308352
Control62=IDC_EDIT_MODULATION_WHEEL,edit,1484849280
Control63=IDC_EDIT_ASIO_DEVICE,edit,1484783744
Control64=IDC_STATIC,static,1342308352
Control65=IDC_CHECK_USE_MODULATION,button,1476460547

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG_SETTINGS]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_ASIO_CONNECT]
Type=1
Class=CDialogASIOConnect
ControlCount=4
Control1=IDOK,button,1342242816
Control2=IDC_BUTTON_BREAK,button,1342242816
Control3=IDC_EDIT_ASIO_DEVICE_INDEX,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:CDialogASIOConnect]
Type=0
HeaderFile=DialogASIOConnect.h
ImplementationFile=DialogASIOConnect.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDialogASIOConnect

