/*************************************************************************
	> File Name: func.cpp
	> Author: sandy
	> Mail: sandy@luo.bo 
	> Created Time: 2014年03月31日 星期一 16时22分35秒
 ************************************************************************/

#include<iostream>
#include"func.h"
#include<map>
#include<cstdlib>
using namespace std;

string chooseIris(char* ResulTxt)
{
    
}

int main(int argc,char *argv[])
{
//    char* filename="/home/sandy/Iris/IRIS4/scores/list_result_matching_inter.txt";
	const char* filename="/home/sandy/list_result_matching_inter.txt";
    ifstream infile(filename);
    if(!infile)
    {
        cerr << "Could not open files!" << endl;
        return -1;
    }
    string file1,file2,score;
	map < string, double > mapS; 
	map < string, double >::iterator iter;
	double temp;
    while(infile>>file1>>file2>>score)
    {
		//find element
		iter = mapS.find(file1);
		if(iter != mapS.end())
		{
			temp = mapS[file1];
			mapS[file1]=temp+atof(score.c_str());
		}
		else
		{
			mapS.insert(make_pair(file1,atof(score.c_str())));
		}
        //cout<<file1<<" "<<file2<<" "<<score<<endl;
    }
	map<string,double>::iterator tempit;
	for(tempit=mapS.begin();tempit!=mapS.end();tempit++)
	{
		cout<<tempit->first<<"--"<<tempit->second<<endl;
	}
    infile.close();

    return 0;
}
