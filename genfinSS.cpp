/*
 * genfinSS.cpp
 *
 *  Created on: May 2, 2014
 *      Author: sandy
 */
#include<iostream>
#include"func.h"
using namespace std;

//初始化不指定，但是必须写NULL
Config config={NULL};


int main(int argc, char *argv[])
{

	//写入配置参数
	config.M=SETM;
	config.T=600;
	config.Num=1280;
	config.digest=EVP_sha1();
	config.digest_name=string("SHA1");
	config.rlen=256;
	config.filename=string(argv[1]);

	string fingercodeds = "/home/sandy/Dataset/FP/feature/";
	//const char* filename="/home/sandy/list_result_matching_inter.txt";
	string fingerTemplate;

	int width, height;
	//irisTemplate = "02_03.bmp";
	fingerTemplate = string(argv[1]);
	//获取虹膜数据
	BYTE *data = getFingerCode(fingercodeds + fingerTemplate);
	//cout<<"data:\t"<<data<<endl;
	BYTE** fingerset = NULL;
	parsIris(data, fingerset, config.Num, config, fingerTemplate+".set");

	BYTE* r = NULL;
	genR(&r,config.rlen);
	cout << "rand:\t" << r << endl;
	config.r=r;
	unsigned char md[SHA_DIGEST_LENGTH];
	unsigned char *digest = ranCode(data, config.Num, config.r, md,config);

	//启动进程sketch生成模板popen读入程序返回的值
	FILE *fp;
	fp = popen(string("./pinsketch/sketch "+fingerTemplate+".set").c_str(), "r");
	pclose(fp);

	//记录配置文件，恢复时需要
	writeConfig(config);
	free(r);
	free(fingerset);
//	free(data);
	return 0;
}



