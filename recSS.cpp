/*
 * recSS.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: sandy
 */
#include<iostream>
#include"func.h"
#include"./pinsketch/pinsketch.h"
using namespace std;
string iriscodeds;
//需要初始化全局变量config，否则不分配空间;当指定初始化小于结构体内容时，初始部分
//
Config config={1280};
int main(int argc, char *argv[])
{
	iriscodeds = string(argv[1]);
	string testTemplate(argv[3]);
	//config.M=64;
	//config.T=2000;
	//config.Num=1280;
	string sketch(argv[2]);
	readConfig(string(iriscodeds+sketch+".ini"),config);
	int width, height;

	//测试使用的特征
	//string testTemplate = "02_02.bmp";

	BYTE *data = getIrisCode(iriscodeds + testTemplate, width, height);
	BYTE** iriset = NULL;

	//在此处定义测试特征分割的特征集，之后代码可以修改为不写入磁盘该集合
	parsIris(data, iriset, width * height, config,iriscodeds+ testTemplate+".set");
	
	cout<<sketch<<" "<<testTemplate<<endl;
	//输入模板和测试特征集合，如果成功恢复 则产生不空differ.set 否则differ.set为空
	DifferSet(iriscodeds+sketch+".ss",iriscodeds+testTemplate+".set");
	string str1=sketch;
	string str2=testTemplate;
	str1.erase(str1.end()-4,str1.end());
	str2.erase(str2.end()-4,str2.end());
	//string sdf=iriscodeds.substr((iriscodeds.length()-4),3)+"-"+str1+"-"+str2+"-differ.set";
	string sdf=iriscodeds+str1+"-"+str2+"-differ.set";
	cout<<sdf<<endl;
	//TODO 下阶段同样不生成中间文件
	RecSet(sdf,iriscodeds+testTemplate+".set");
	BYTE *rdata = RecData("rec.set",config);
	
	//恢复的数据在Eclipse下调试使用数组展示时Eclipse 显示不正确
	unsigned char md[SHA_DIGEST_LENGTH];
	unsigned char *digest = ranCode(rdata, width * height, config.r, md,config);

	//保存到s1.key
	string savekey(argv[4]);
	ofstream savefile(savekey.c_str());
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
			savefile << hex << setw(2) << setfill('0') << (int) digest[i];
	return 0;
}






