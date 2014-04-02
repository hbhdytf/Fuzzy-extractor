/*************************************************************************
	> File Name: func.h
	> Author: sandy
	> Mail: sandy@luo.bo 
	> Created Time: 2014年03月31日 星期一 16时06分10秒
 ************************************************************************/
#ifndef __FUNC_H
#define __FUNC_H
#include<iostream>
#include<cstring>
#include<fstream>
#include<map>
#include<stdlib.h>
#include<cstdlib>
#include<iterator>
#include "opencv/cv.h"
#include "opencv/highgui.h"

using namespace std;

typedef unsigned char BYTE;

string chooseIris(const char* ResulTxt);
BYTE* getIrisCode(const string IrisTemplate,int & width,int & height);
int parsIris(BYTE* IrisCode,BYTE** iriset,const int len,const unsigned int N);
bool genPinSketch(char** iriset,int t,int m);
char* ranCode(char* iriscode);
bool genKeySketch(char* iriscode,char key);
int writeConfig(int N, string digest);

#endif
