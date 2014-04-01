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
	//const char* filename="/home/sandy/list_result_matching_inter.txt";
	string irisTemplate=chooseIris(filename);
    cout<<"irisTemplate:--"<<irisTemplate<<endl;
	return 0;
}
