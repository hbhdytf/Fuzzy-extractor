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

//需要初始化全局变量config，否则不分配空间;当指定初始化小于结构体内容时，初始部分
//
Config config={1280};
int main(int argc, char *argv[])
{
	//config.M=64;
	//config.T=2000;
	//config.Num=1280;
	readConfig("config.ini",config);
	int width, height;
	string iriscodeds = "/home/sandy/USIT/";
	//测试使用的特征
	string testTemplate = "02_02.bmp";
	
	BYTE *data = getIrisCode(iriscodeds + testTemplate, width, height);
	BYTE** iriset = NULL;

	//在此处定义测试特征分割的特征集，之后代码可以修改为不写入磁盘该集合
	parsIris(data, iriset, width * height, config, "Test.set");
	
	//输入模板和测试特征集合，如果成功恢复 则产生不空differ.set 否则differ.set为空
	DifferSet("Template.ss","Test.set");

	//TODO 下阶段同样不生成中间文件
	RecSet("differ.set","Test.set");
	BYTE *rdata = RecData("rec.set",config);
	
	//恢复的数据在Eclipse下调试使用数组展示时Eclipse 显示不正确
	unsigned char md[SHA_DIGEST_LENGTH];
	unsigned char *digest = ranCode(rdata, width * height, config.r, md,config);
	return 0;
}






