/*************************************************************************
  > File Name: recset.cpp
  > Author: sandy
  > Mail: sandy@luo.bo 
  > Created Time: 2014年03月28日 星期五 21时04分04秒
 ************************************************************************/

#include<iostream>
#include<NTL/ZZ.h>
using namespace std;
using namespace NTL;

int main()
{
	ZZ a,b,c;
	cin >> a;
	cin >> b;
	c = ( a + 1 ) * ( b + 1 );
	cout << c << endl;
	return 0;
}
