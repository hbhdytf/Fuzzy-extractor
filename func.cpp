/*************************************************************************
  > File Name: func.cpp
  > Author: sandy
  > Mail: sandy@luo.bo 
  > Created Time: 2014年03月31日 星期一 16时22分35秒
 ************************************************************************/

#include<iostream>
#include"func.h"

using namespace std;

void string_replace(string&s1,const string&s2,const string&s3)
{
	string::size_type pos=0;
	string::size_type a=s2.size();
	string::size_type b=s3.size();
	while((pos=s1.find(s2,pos))!=string::npos)
	{
		s1.replace(pos,a,s3);
		pos+=b;
	}
}

string chooseIris(const char* ResulTxt)
{
	ifstream infile(ResulTxt);
	if(!infile)
	{
		cerr << "Could not open files!" << endl;
		exit(-1);
	}
	
	//计算每个图像的评分选择最小的那个作为模板
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
	map<string,double>::iterator minit;
    
    //计算最小值
	for(minit=(tempit=mapS.begin());tempit!=mapS.end();tempit++)
	{
	    if(tempit->second<minit->second)
	    {
	        minit=tempit;
	    } 
		//cout<<tempit->first<<"--"<<tempit->second<<endl;
	}
	infile.close();
    cout<<"min:--"<<minit->first<<"--"<<minit->second<<endl;
    //替换
    string name=minit->first;
    string_replace(name,string(".tiff"),string("_code.bmp"));
    return name;
}


