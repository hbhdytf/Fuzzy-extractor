/*************************************************************************
 > File Name: main.cpp
 > Author: sandy
 > Mail: sandy@luo.bo
 > Created Time: 2014年04月01日 星期二 10时18分42秒
 ************************************************************************/

#include<iostream>
#include"func.h"
using namespace std;
Config config={NULL};

int main(int argc, char *argv[])
{

	config.M=SETM;
	config.T=SETT;
	config.Num=SETNum;
	config.digest=EVP_sha1();
	config.digest_name=string("SHA1");
	config.rlen=256;

	const char* filename =
			"/home/sandy/Iris/IRIS4/scores/list_result_matching_inter.txt";
	string iriscodeds = "/home/sandy/USIT/";
	//const char* filename="/home/sandy/list_result_matching_inter.txt";
	string irisTemplate = chooseIris(filename);
	cout << "irisTemplate:--" << irisTemplate << endl;

	int width, height;
	irisTemplate = "02_03.bmp";
	//获取虹膜数据
	BYTE *data = getIrisCode(iriscodeds + irisTemplate, width, height);
	cout << width << " " << height << endl;
	BYTE** iriset = NULL;
	parsIris(data, iriset, width * height, config, "Template.set");

	BYTE* r = NULL;
	genR(&r,config.rlen);
	cout << "rand:\t" << r << endl;
	config.r=r;
	unsigned char md[SHA_DIGEST_LENGTH];
	unsigned char *digest = ranCode(data, width * height, config.r, md,config);

	FILE *fp;
	fp = popen("./pinsketch/sketch Template.set", "r");
	pclose(fp);
	writeConfig(config);
	free(r);
	free(iriset);
//	free(data);
	return 0;
}

/*
 IplImage *iplImage;
 iplImage = cvCreateImageHeader(cvSize(512,384),IPL_DEPTH_8U,1);
 cvSetData(iplImage,data,512);
 cvSaveImage("test1.bmp",iplImage);
 */
