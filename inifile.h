
#ifndef __C_REG_KEY_ADV__
#define __C_REG_KEY_ADV__

#include "stdafx.h"

static CString inifilename="MidiInPiano.ini";

class CINIFiles 
{
	CString fileName;
	CString appName;

public:

	void Close(){}

	bool IsExist()
	{
		CFile file;
		if (!file.Open(fileName,file.modeRead))
		{
			return false;
		}
		else 
		{
			file.Close();
			return true;
		}
	}

	void SetValue(const DWORD &val, const char *key)
	{
		char buf[64];
		itoa(val,buf,10);
		SetString(CString(buf), key);
	}

	bool QueryValue(DWORD &val, char *key)
	{
		CString m=QueryString(key);
		val=atoi(m);
		return true;
	}

	DWORD QueryValue(char *key)
	{
		CString m=QueryString(key);
		DWORD val=atoi(m);
		return val;
	}


	void Create(DWORD,char* RegistryBase) {}

	CINIFiles() 
	{
		char buf[2048];
		GetCurrentDirectory(2048, buf);
		fileName=CString(buf)+"\\"+inifilename;
		appName="MidiInPiano";
	}
	//void Create
	CString QueryString(const CString & valuename)
	{
		char buf[256];
		GetPrivateProfileString(appName, valuename,"", buf,256, fileName);
		return buf;
	}
	void SetString(CString& value, const char * keyname)
	{
		//char buf[255]={0};
		//DWORD count=sizeof(buf);
		WritePrivateProfileString(appName, keyname, value, fileName);
		//CString m=buf;
		//return m;
		return;
	}


};



/*
class CRegKeyAdv : public CRegKey
{
public:
	CString QueryString(const CString & valuename)
	{
		char buf[255]={0};
		DWORD count=sizeof(buf);
		QueryValue(buf, valuename, &count);
		CString m=buf;
		return m;

	}
	void SetString(CString& value, const char * keyname)
	{
		//char buf[255]={0};
		//DWORD count=sizeof(buf);
		SetValue(value.GetBuffer(0), keyname);
		//CString m=buf;
		//return m;
		return;
	}

};
*/

#endif