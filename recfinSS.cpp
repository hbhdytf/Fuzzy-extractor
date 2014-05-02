/*
 * recfinSS.cpp
 *
 *  Created on: May 2, 2014
 *      Author: sandy
 */

#include<iostream>
#include"func.h"
#include"./pinsketch/pinsketch.h"
using namespace std;

//需要初始化全局变量config，否则不分配空间;当指定初始化小于结构体内容时，初始部分
//
Config config={1280};
int main(int argc, char *argv[])
{
	//config.M=64;
	//config.T=2000;
	//config.Num=1280;
	string sketch(argv[1]);
	readConfig(string(sketch+".ini"),config);
	string fingercodeds = "/home/sandy/Dataset/FP/feature/";
	//测试使用的特征
	//string testTemplate = "02_02.bmp";
	string testTemplate(argv[2]);
	BYTE *data = getFingerCode(fingercodeds + testTemplate);
	BYTE** fingerset = NULL;

	//在此处定义测试特征分割的特征集，之后代码可以修改为不写入磁盘该集合
	parsIris(data, fingerset, config.Num, config, testTemplate+".set");


	//输入模板和测试特征集合，如果成功恢复 则产生不空differ.set 否则differ.set为空
	DifferSet(sketch+".ss",testTemplate+".set");

	//TODO 下阶段同样不生成中间文件
	RecSet("differ.set",testTemplate+".set");
	BYTE *rdata = RecData("rec.set",config);
	//cout<<"rdata:\t"<<rdata<<endl;
	//恢复的数据在Eclipse下调试使用数组展示时Eclipse 显示不正确
	unsigned char md[SHA_DIGEST_LENGTH];
	unsigned char *digest = ranCode(rdata,config.Num, config.r, md,config);

	//保存到s1.key
	string savekey(argv[3]);
	ofstream savefile(savekey.c_str());
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
			savefile << hex << setw(2) << setfill('0') << (int) digest[i];
	return 0;
}


