#ifndef MUSIC_H
#define MUSIC_H


#include <mciapi.h>
#include "iofile.h"


class MUSIC
{
	string name;
	static CHAR szReturn[256];
	static int volume;
	static int number[2];
	static char state;
	static char mode;
public:
	static INT getnumber(int i = 0);//获取音乐总数或当前播放的位置 Get the number of music or the number of music whice is playing
	static INT setnumber(int n, int i = 0);//设置音乐总数或当前播放的位置 Set the number of music or the number of music whice is playing

	static CHAR getmode();//获取播放模式Get the mode of playing
	static VOID setmode(char m);//设置播放模式 Set the mode of playing
	static CHAR getstate();//获取状态 Get the state
	static VOID setstate(char s);//设置状态 Set the state

	VOID set(string c);//设置歌曲名字 Set the name of music
	string getname();//获取歌曲名字 Get the name of music
	int get(string command);//获取音量和进度 Get the volume and position of music
	static int getvolume();//获取静态变量“volume” Get the Static variables "volume"
	//Operations on music
	BOOL close();//关闭设备
	BOOL open();//打开
	BOOL stop();//停止
	BOOL play();//播放
	BOOL pause();//暂停
	BOOL resume();//继续
	BOOL setvolume(int v);//设置声音
	BOOL setposition(int s);//设置进度
	
	INT showposition();//获取滑块应该在的位置 Get where the progress slider should be

	void jump(); //文件丢失时发出信息 Messages are sent when files are missing
};


void getmusic(MUSIC music[], string Music[], string address);//导入到MUSIC数组
MUSIC* changelist(MUSIC music[], string address);//更新

#endif


