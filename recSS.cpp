/*
 * recSS.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: sandy
 */
#include<iostream>
#include"func.h"
using namespace std;

int main(int argc, char *argv[])
{
	int width, height;
	string iriscodeds = "/home/sandy/USIT/";
	string testTemplate = "02_02.bmp";
	BYTE *data = getIrisCode(iriscodeds + testTemplate, width, height);
	BYTE** iriset = NULL;
	parsIris(data, iriset, width * height, Num, "Test.set");
	FILE *fp;
	fp = popen("./pinsketch/differ Template.ss Test.set", "r");
	pclose(fp);
	fp = popen("./pinsketch/recset differ.set Test.set", "r");
	pclose(fp);
	return 0;
}






