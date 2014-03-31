/*************************************************************************
	> File Name: func.cpp
	> Author: sandy
	> Mail: sandy@luo.bo 
	> Created Time: 2014年03月31日 星期一 16时22分35秒
 ************************************************************************/

#include<iostream>
#include<func.h>
using namespace std;

string chooseIris(char* ResulTxt)
{
    
}

int main(int argc,char *argv[])
{
    char* filename="/home/sandy/Iris/IRIS4/scores/list_result_matching_inter.txt";
    ifstream infile(filename);
    if(!infile)
    {
        cerr << "Could not open files!" << endl;
        return -1;
    }
    string line;
    while(infile>>line)
    {
        cout<<line<<endl;
    }
    infile.close();

    return 0;
}
