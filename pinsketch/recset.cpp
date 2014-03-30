#include <stdio.h>  
#include <string.h>  
#include <algorithm>  
#include <vector>  
#include <iostream>  
#include <string>  
#include <NTL/ZZ.h>
  
using namespace std;
using namespace NTL;  
   
void ExampleSetSymmetricDifference()  
{  
    vector<ZZ> i1;  
    vector<ZZ> i2;  
    std::vector<ZZ>::iterator it;  
    i1.push_back(ZZ(1));  
    i1.push_back(2);  
    i1.push_back(5);  
    i1.push_back(8);  
  
    i2.push_back(0);  
    i2.push_back(1);  
    i2.push_back(2);  
    i2.push_back(3);  
    i2.push_back(4);  
    i2.push_back(5);  
    i2.push_back(6);  
    i2.push_back(6);  
    i2.push_back(7);  
  
    sort(i1.begin(),i1.end());  
    sort(i2.begin(),i2.end());  
  
    vector<ZZ> res(i2.size()+i1.size());  
    //对称差  
    it = set_symmetric_difference(i1.begin(),i1.end(),i2.begin(),i2.end(),res.begin());  
  
    res.resize(it-res.begin());  
    size_t size = res.size();  
      
    printf("size %d\n",size);  
    for (it=res.begin(); it!=res.end(); ++it)  
    {  
        std::cout << ' ' << *it;  
    }  
    std::cout << std::endl;  
}  
 

int main(int argc, char *argv[])  
{  
    std::cout << "SetSymmetricDifference" << endl;  
    ExampleSetSymmetricDifference();  
  
    return 0;  
}  
