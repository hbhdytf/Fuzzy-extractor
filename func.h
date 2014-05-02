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
#ifndef SETNum
//N 表示将IrisCode分割为N段
#define SETNum 1280
#endif

//计算集合差时的输入，t表示最大集合差元素个数的门限值
//m表示基于的有限域GF(2^m)，且t<=2^(m-1)
#ifndef SETT
#define SETT 2000
#define SETM 64
#define DIGEST EVP_sha1()
#define DIGEST_NAME "SHA1"
#endif


typedef unsigned char BYTE;

//写入配置文件的选项，可扩展，恢复SS所需要的一些参数
typedef struct Config
{
	int Num;
	int T;
	int M;
	const EVP_MD* digest;
	string digest_name;
	BYTE* r;
	int rlen;
	string filename;
}Config;

//虹膜特征处理阶段
string chooseIris(const char* ResulTxt);
BYTE* getIrisCode(const string IrisTemplate, int & width, int & height);
int parsIris(BYTE* IrisCode, BYTE** iriset, const int len, Config config,
		string Setname);

//产生Iris Sketch阶段，初步使用现有的pinsketch程序
bool genPinSketch(char** iriset, int t, int m);

//密钥处理阶段
int genR(BYTE** r,int rlen);	//产生随机字符串
unsigned char* ranCode(BYTE* iriscode, const int len, BYTE* r,
		unsigned char* rancode,Config config);
bool genKeySketch(char* iriscode, char key);

//读写配置文件的函数
int writeConfig(Config wconfig);
int readConfig(string filename, Config &rconfig);

//恢复数据
BYTE* RecData(string setname,Config config);
#endif
