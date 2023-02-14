#ifndef IOFILE_H
#define IOFILE_H


int getnumber(string address);
void getlist(string list[], string address);
int findlist(string list, string address);
int creatlist(string address, string list = "");
int deletelist(string address, string music, int n);
int deletelist(string address, int n);
bool findfile(string name);

#endif
