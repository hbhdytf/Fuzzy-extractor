#include <stdio.h>  
#include <string.h>  
#include <algorithm>  
#include <vector>  
#include <iostream>  
#include <string>  
#include <NTL/ZZ.h>
#include <fstream>
  
using namespace std;
using namespace NTL;  

//从集合差中读取数据   
int ReadDiffer(std::vector<ZZ> *set ,ifstream& infile )
{
    if(set == NULL)
    {
        cerr <<  "invalid set" <<endl;
        return -1;
    }
    else
    {
        ZZ temp;
        string line;
        while(infile>>line)
        {
            // getline(infile,line);
            conv(temp,line.c_str());
            (*set).push_back(temp);
            // cout<<temp<<endl;
        }
        infile.close();
        return 1;
    }
    //exit(-1);
}

//从集合中读取数据
int ReadSet(std::vector<ZZ> *set, ifstream& infile )
{
    if(set == NULL)
    {
        cerr <<  "invalid set" <<endl;
        return -1;
    }
    else
    {
        ZZ temp;
        string line;
        while(infile>>line)
        {
        	//判断是否为数字
            if(line[0]>'9'||line[0]<'0')
            	continue;
            // getline(infile,line);
            conv(temp,line.c_str());
            (*set).push_back(temp);
            // cout<<temp<<endl;
        }
        infile.close();
        return 1;
    }
}
void SetSymmetricDifference(ifstream& infile1,ifstream& infile2)  
{  
    vector<ZZ> i1;  
    vector<ZZ> i2;  
    std::vector<ZZ>::iterator it;  
    ZZ temp;
    //输入集合数据
	ReadDiffer(&i1,infile1);
	ReadSet(&i2,infile2); 

    sort(i1.begin(),i1.end());  
    sort(i2.begin(),i2.end());  
  
    vector<ZZ> res(i2.size()+i1.size());  
    //对称差  
    it = set_symmetric_difference(i1.begin(),i1.end(),i2.begin(),i2.end(),res.begin());  
    res.resize(it-res.begin());  
    size_t size = res.size();  
    //输出集合差  
    printf("size %d\n",size);  
    ofstream outfile("rec.set");
    for (it=res.begin(); it!=res.end(); ++it)  
    {  
        cout << '\n' << *it;  
        outfile << *it <<endl;
    }  

    cout << endl;  
    outfile.close();
}  
 

int main(int argc, char *argv[])  
{  
    int len1,len2;
    long d;
  //  bool i=strcmp(&argv[1][len1-4], ".set");
  //  cout<<i<<endl; 
    if (argc != 3 || 
	    (len1=strlen(argv[1])) < 4 || (len2=strlen(argv[2])) < 4 ||
	    strcmp(&argv[1][len1-4], ".set") ||
	    (strcmp(&argv[2][len2-3], ".ss") && strcmp (&argv[2][len2-4], ".set")))
	{	
		cerr << "Usage:\ndiffer A.ss B.ss\nOR\ndiffer A.ss B.set\n";
		if (argc == 3)
			cerr << "(first file must be named `*.ss`, second can be either `*.ss' or `*.set')" << endl;
		return -1;
	}
		
	bool mode; // 0 if comparing .ss with .ss; 1 if comparing .ss with .set
	mode = (strcmp (&argv[2][len2-4], ".set")==0);

	ifstream infile1(argv[1]);
	ifstream infile2(argv[2]);
        if (!infile1 || !infile2) {
           cerr << "Could not open files!" << endl;
           if (infile1) infile1.close();
           if (infile2) infile2.close();
           return -1;
        }

    cout << "SetSymmetricDifference" << endl;  
    SetSymmetricDifference(infile1,infile2);  
  
    return 0;  
}  
