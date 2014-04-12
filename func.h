/*************************************************************************
 > File Name: func.h
 > Author: sandy
 > Mail: sandy@luo.bo
 > Created Time: 2014年03月31日 星期一 16时06分10秒
 ************************************************************************/
#ifndef __FUNC_H
#define __FUNC_H
#include<iostream>
#include<iomanip>
#include<cstring>
#include<fstream>
#include<map>
#include<stdlib.h>
#include<cstdlib>
#include<iterator>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/crypto.h>
#include <glib.h>
#include <glib-2.0/glib/gkeyfile.h>

using namespace std;
#ifndef Num
//N 表示将IrisCode分割为N段
#define Num 1280
#endif

//计算集合差时的输入，t表示最大集合差元素个数的门限值
//m表示基于的有限域GF(2^m)，且t<=2^(m-1)
#ifndef T
#define T 2000
#define M 64
#define DIGEST EVP_sha1()
#define DIGEST_NAME "SHA1"
#endif

typedef unsigned char BYTE;

//虹膜特征处理阶段
string chooseIris(const char* ResulTxt);
BYTE* getIrisCode(const string IrisTemplate, int & width, int & height);
int parsIris(BYTE* IrisCode, BYTE** iriset, const int len,
		const unsigned int N);

//产生Iris Sketch阶段，初步使用现有的pinsketch程序
bool genPinSketch(char** iriset, int t, int m);

//密钥处理阶段
int genR(BYTE** r);
unsigned char* ranCode(BYTE* iriscode,const int len, BYTE* r,unsigned char* rancode);
bool genKeySketch(char* iriscode, char key);
int writeConfig(BYTE* r);
#endif
