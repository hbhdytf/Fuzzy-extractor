#include "pinsketch.h"

  
using namespace std;
using namespace NTL;  

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
