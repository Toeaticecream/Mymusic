#include "pch.h"
#include "MUSIC.h"
INT MUSIC::getnumber(int i)
{
	return number[i];
}
INT MUSIC::setnumber(int n, int i)
{
	number[i] = n;
	return number[i];
}

CHAR MUSIC::getmode()
{
	return mode;
}
VOID MUSIC::setmode(char m)
{
	mode = m;
}
CHAR MUSIC::getstate()
{
	return state;
}
VOID MUSIC::setstate(char s)
{
	state = s;
}

VOID MUSIC::set(string c)
{
	name = c;
}
string MUSIC::getname()
{
	return name;
}
int MUSIC::get(string command)
{
	int r = -1;
	command = "status music\\" + name + ".mp3 " + command;
	r = mciSendString(command.c_str(), szReturn, 256, NULL);
	r = atoi(szReturn);
	return r;
}
int MUSIC::getvolume()
{
	return volume;
}
BOOL MUSIC::close()
{
	if (mciSendString(("close music\\" + name + ".mp3").c_str(), NULL, 0, NULL) == 0)
	{
		state = 0;
		return true;
	}
	return false;
}
BOOL MUSIC::open()
{
	if (mciSendString(("open music\\" + name + ".mp3").c_str(), NULL, 0, NULL) == 0)
	{
		state = 1;
		return true;
	}
	return false;
}
BOOL MUSIC::stop()
{
	if (mciSendString(("stop music\\" + name + ".mp3").c_str(), NULL, 0, NULL) == 0)
	{
		state = 2;
		return true;
	}
	return false;
}
BOOL MUSIC::play()
{
	if (mciSendString(("play music\\" + name + ".mp3 notify").c_str(), NULL, 0, AfxGetMainWnd()->m_hWnd) == 0)
	{
		state = 3;
		return true;
	}
	return false;
}
BOOL MUSIC::pause()
{
	if (mciSendString(("pause music\\" + name + ".mp3").c_str(), NULL, 0, NULL) == 0)
	{
		state = 4;
		return true;
	}
	return false;
}
BOOL MUSIC::resume()
{
	if (mciSendString(("resume music\\" + name + ".mp3").c_str(), NULL, 0, NULL) == 0)
	{
		state = 5;
		return true;
	}
	return false;
}
BOOL MUSIC::setvolume(int v)
{
	string w = to_string(v);
	string command = "setaudio music\\" + name + ".mp3 volume to " + to_string(v);
	if (mciSendString(command.c_str(), NULL, 0, NULL) == 0)
	{
		volume = v;
		return 1;
	}
	return 0;
}
BOOL MUSIC::setposition(int s)
{
	string command = "play music\\" + name + ".mp3 from " + to_string(s);
	if (mciSendString(command.c_str(), NULL, 0, NULL) == 0)
	{
		return 1;
	}
	return 0;
}
INT MUSIC::showposition()
{
	if (state)
	{
		mciSendString(("status music\\" + name + ".mp3 position").c_str(), szReturn, 256, NULL);
		double p = atoi(szReturn);
		mciSendString(("status music\\" + name + ".mp3 length").c_str(), szReturn, 256, NULL);
		int l = atoi(szReturn);
		return p * 511 / l;
	}
	return -1;
}
void MUSIC::jump()
{
	SendMessage(AfxGetMainWnd()->m_hWnd, MM_MCINOTIFY, 1, 0);
}

MUSIC* music = NULL;
string* musiclist = NULL;
int NUMBER_LIST = 0;
int number_list = 0;


TCHAR MUSIC::szReturn[] = {};
int MUSIC::volume = 300;
INT MUSIC::number[2] = { 0,0 };
char MUSIC::state = 0;
char MUSIC::mode = 0;

void getmusic(MUSIC music[], string Music[], string address)
{
	int i = getnumber(address) - 1;
	for (;i >= 0;i--)
	{
		music[i].set(Music[i]);
	}
}
MUSIC* changelist(MUSIC music[], string address)
{
	MUSIC::setnumber(getnumber(address), 1);
	music = new MUSIC[MUSIC::getnumber(1) + 1];
	string* music1 = new string[MUSIC::getnumber(1) + 1];
	getlist(music1, address);
	getmusic(music, music1, address);
	delete[]music1;
	MUSIC::setnumber(0);
	return music;
}