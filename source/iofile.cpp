#include "pch.h"
#include <string>
#include <fstream>
#include <io.h>
#include "iofile.h"
using namespace std;

int getnumber(string address)
{
	address += ".ini";
	ifstream  fp(address, ios::in);
	int i = 0;
	char data[80] = {};
	for (i = 0;!fp.eof();i++)
	{
		fp.getline(data, 80);
	}
	i--;
	return i;
}
void getlist(string list[], string address)
{
	address += ".ini";
	ifstream  fp(address, ios::in);
	int i = 0;
	char data[80] = {};
	for (i = 0;!fp.eof();i++)
	{
		fp.getline(data, 80);
		list[i] = data;
	}
	fp.close();
}
int findlist(string list, string address)
{
	string List[50] = {};
	getlist(List, address);
	int i = getnumber(address);
	for (;i >= 0;i--)
	{
		if (List[i] == list)
		{
			return i;
		}
	}
	return -1;
}
int creatlist(string address, string list)
{
	address += ".ini";
	ofstream  fp(address, ios::app);
	if (list != "")
	{
		fp << list << endl;
	}
	fp.close();
	return 1;
}
int deletelist(string address, string music, int n)
{
	int i = getnumber(address);
	string* List = new string[i + 1];
	getlist(List, address);
	address += ".ini";
	ofstream  fp(address, ios::out);
	for (int j = 0;j < i;j++)
	{
		if (j != n)
		{
			fp << List[j] << endl;
		}
	}
	delete[]List;
	fp.close();
	return 1;
}
int deletelist(string address, int n)
{
	int i = getnumber("musiclist");
	string* List = new string[i + 1];

	getlist(List, "musiclist");
	ofstream  fp("musiclist.ini", ios::out);
	int j = 0;
	for (j = 0;j < i;j++)
	{
		if (j != n)
		{
			fp << List[j] << endl;
		}
	}
	delete[]List;
	fp.close();
	remove((address + ".ini").c_str());

	return 1;
}
bool findfile(string name)
{
	fstream fp(name);
	if (fp)
	{
		fp.close();
		return true;
	}
	fp.close();
	return false;

}
