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
Config config={1280};
int main(int argc, char *argv[])
{
	//config.M=64;
	//config.T=2000;
	//config.Num=1280;
	readConfig("config.ini",config);
	int width, height;
	string iriscodeds = "/home/sandy/USIT/";
	string testTemplate = "02_02.bmp";
	BYTE *data = getIrisCode(iriscodeds + testTemplate, width, height);
	BYTE** iriset = NULL;
	parsIris(data, iriset, width * height, config, "Test.set");

	DifferSet("Template.ss","Test.set");
	RecSet("differ.set","Test.set");
	RecData("rec.set",config);

	return 0;
}






