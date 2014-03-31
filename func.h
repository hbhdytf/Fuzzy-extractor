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

using namespace std;

string chooseIris(char* ResulTxt);
char* getIrisCode(char* IrisTemplate);
char* parsIris(char* IrisCode,const unsigned int N);
bool genPinSketch(char** iriset,int t,int m);
char* ranCode(char* iriscode);
bool genKeySketch(char* iriscode,char key);
int writeConfig(int N, string digest);

#endif
