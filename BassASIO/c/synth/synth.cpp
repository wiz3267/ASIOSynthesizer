/*
	USE: ASIO version of BASS simple synth
	Copyright (c) 2001-2013 Un4seen Developments Ltd.
*/

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "bassasio.h"
#include "bass.h"

void Msg(char *);

extern int SAMPLE_RATE;
int ASIO_buflen;
// display error messages
void Error(const char *text) 
{
	char txt[128];
	wsprintf(txt,"Error(%d/%d): %s\n",BASS_ErrorGetCode(),BASS_ASIO_ErrorGetCode(),text);
	Msg(txt);
	BASS_ASIO_Free();
	BASS_Free();
}

int samrate;
DWORD ASIO_PROC_BUFLEN=0;

// ASIO function
DWORD CALLBACK AsioProc(BOOL input, DWORD channel, void *buffer, DWORD length, void *user)
{
	DWORD c=BASS_ChannelGetData((DWORD)user,buffer,length);
	ASIO_PROC_BUFLEN=length;
	if (c==-1) c=0; // an error, no data
	return c;
}

void FillBuffer(short *plbuf, int size, int samplerate);

// stream writer
DWORD CALLBACK WriteStream(HSTREAM handle, short *buffer, DWORD length, void *user)
{
	memset(buffer,0,length);

	//здесь происходит заполнени€ буфера дл€ записи
	FillBuffer(buffer,length,SAMPLE_RATE);


	return length;
}

int main(int asio_index, char **)
{
	BASS_ASIO_INFO info;

	HSTREAM str;
	
	const char *fxname[9]={"CHORUS","COMPRESSOR","DISTORTION","ECHO",
		"FLANGER","GARGLE","I3DL2REVERB","PARAMEQ","REVERB"};
	
	HFX fx[9]={0}; // effect handles
	

	//Error("Test BASS Error");
	//return 0;

	// check the correct BASS was loaded
	if (HIWORD(BASS_GetVersion())!=BASSVERSION) 
	{
		Error("An incorrect version of BASS was loaded");
		return 0;
	}

	// not playing anything via BASS, so don't need an update thread
	if (!BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD,0))
	{
		Error("BASS_SetConfig BASS_CONFIG_UPDATEPERIOD error");
		return 0;
	}

	// setup BASS - "no sound" device
	if (!BASS_Init(0,SAMPLE_RATE,0,0,NULL))
	{
		Error("BASS_Init SAMPLE_RATE error");
		return 0;
	}

	// setup ASIO - first device
	if (!BASS_ASIO_Init(asio_index,BASS_ASIO_THREAD))
	{
		Error("BASS_ASIO_Init asio_index BASS_ASIO_THREAD");
		return 0;
	}

	// start device info for buffer size range, begin with default
	BASS_ASIO_GetInfo(&info);
	ASIO_buflen=info.bufpref;

	if (info.outputs==0)
	{
		Msg("Error - No avialable outputs channels");
		return 0;

	}
	//BASS_ASIO_SetInfo(&info);

	BASS_ASIO_SetRate(48000);

	samrate=(int)BASS_ASIO_GetRate();

	SAMPLE_RATE=int(samrate);

	// create a stream, stereo so that effects sound nice
	str=BASS_StreamCreate(samrate,2,BASS_STREAM_DECODE,(STREAMPROC*)WriteStream,0);

	if(!BASS_ASIO_ChannelEnable(0,0,&AsioProc,(void*)str)) // enable 1st output channel...
	{
		Error("BASS_ASIO_ChannelEnable AsioProc error");
		return 0;
	}
	
	if(!BASS_ASIO_ChannelJoin(0,1,0)) // and join the next channel to it (stereo)
	{
		Error("BASS_ASIO_ChannelJoin error");
		return 0;
	}

	if(!BASS_ASIO_ChannelSetFormat(0,0,BASS_ASIO_FORMAT_16BIT)) // set the source format (16-bit)
	{
		Error("BASS_ASIO_ChannelSetFormat BASS_ASIO_FORMAT_16BIT error");
		return 0;
	}

	// start the ASIO device
	if (!BASS_ASIO_Start(ASIO_buflen,0))
	{
		Error("Can't start ASIO device");
		return 0;
	}

	//BASS_ASIO_Free();
	//BASS_Free();
	return 1;
}

void StopAsio()
{
	BASS_ASIO_Free();
	BASS_Free();
}
