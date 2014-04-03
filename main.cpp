/*************************************************************************
	> File Name: main.cpp
	> Author: sandy
	> Mail: sandy@luo.bo 
	> Created Time: 2014年04月01日 星期二 10时18分42秒
 ************************************************************************/

#include<iostream>
#include"func.h"
using namespace std;

int main(int argc,char *argv[])
{
	const char* filename="/home/sandy/Iris/IRIS4/scores/list_result_matching_inter.txt";
	string iriscodeds="/home/sandy/Iris/out/IrisCodes/";
	//const char* filename="/home/sandy/list_result_matching_inter.txt";
	string irisTemplate=chooseIris(filename);
    cout<<"irisTemplate:--"<<irisTemplate<<endl;
    
    int width,height;
    //irisTemplate="S1001L06_code.bmp";
    BYTE *data = getIrisCode(iriscodeds+irisTemplate,width,height);
    cout<<width<<" "<<height<<endl;
    BYTE** iriset=NULL;
    parsIris(data,iriset,width*height,Num);
	return 0;
}



/*
    IplImage *iplImage;
	iplImage = cvCreateImageHeader(cvSize(512,384),IPL_DEPTH_8U,1);
	cvSetData(iplImage,data,512);
	cvSaveImage("test1.bmp",iplImage);
	*/
