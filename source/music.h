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
	static INT getnumber(int i = 0);//��ȡ����������ǰ���ŵ�λ�� Get the number of music or the number of music whice is playing
	static INT setnumber(int n, int i = 0);//��������������ǰ���ŵ�λ�� Set the number of music or the number of music whice is playing

	static CHAR getmode();//��ȡ����ģʽGet the mode of playing
	static VOID setmode(char m);//���ò���ģʽ Set the mode of playing
	static CHAR getstate();//��ȡ״̬ Get the state
	static VOID setstate(char s);//����״̬ Set the state

	VOID set(string c);//���ø������� Set the name of music
	string getname();//��ȡ�������� Get the name of music
	int get(string command);//��ȡ�����ͽ��� Get the volume and position of music
	static int getvolume();//��ȡ��̬������volume�� Get the Static variables "volume"
	//Operations on music
	BOOL close();//�ر��豸
	BOOL open();//��
	BOOL stop();//ֹͣ
	BOOL play();//����
	BOOL pause();//��ͣ
	BOOL resume();//����
	BOOL setvolume(int v);//��������
	BOOL setposition(int s);//���ý���
	
	INT showposition();//��ȡ����Ӧ���ڵ�λ�� Get where the progress slider should be

	void jump(); //�ļ���ʧʱ������Ϣ Messages are sent when files are missing
};


void getmusic(MUSIC music[], string Music[], string address);//���뵽MUSIC����
MUSIC* changelist(MUSIC music[], string address);//����

#endif


