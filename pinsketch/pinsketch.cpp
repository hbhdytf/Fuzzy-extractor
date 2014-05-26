/*
 * pinsketch.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: sandy
 */
#include "pinsketch.h"
using namespace std;
int DifferSet(string sketch, string testSet)
{
	cout << "----differ----" << endl;
	int len1, len2; // lengths of argv[1], argv[2], if they exist

	long d; // minimum distance of the code;
			// can handle set difference up to t=(d-1)/2 elements
	// sketches are (d-1)/2 elements long

	long d1, d2;

	long m; // elements of the set and of the sketch are m-bit values

	GF2X irrP; // irreducible polynomial generating GF(2^m)

	vec_GF2E ss1; // sketch of the first set
	vec_GF2E ss2; // sketch of the second set
	vec_GF2E ss; // sketch of the set difference
	bool success;

	bool mode; // 0 if comparing .ss with .ss; 1 if comparing .ss with .set
	const char *differ = "differ.set";
	ifstream infile1(sketch.c_str());
	ifstream infile2(testSet.c_str());

	if (!infile1 || !infile2)
	{
		cerr << "Could not open files!" << endl;
		if (infile1)
			infile1.close();
		if (infile2)
			infile2.close();
		return -1;
	}

	// fix field and error tolerance
	ReadSSParams(m, d1, irrP, infile1);

	// Initialize the field
	GF2E::init(irrP);

	// read in first syndrome
	ReadSS(ss1, infile1, d1);
	infile1.close();

	// the second input is a .set file, i.e., a set
	// params are ignored in .set case and are taken from the .ss file
	long m2;
	ReadSetParams(m2, d2, infile2);
	d = d1;
	// compute second syndrome
	vec_GF2E set;
	ReadSet(set, infile2, m);
	BCHSyndromeCompute(ss2, set, d);

	infile2.close();

	// Compute the syndrome of the set difference
	// By linearity, it is the same as the difference of the syndromes
	// of the two sets
	ss = ss1 - ss2;

	vec_GF2E setDifference;
	// Find the set difference from its syndrome
	// This is the most difficult and interesting part
	success = BCHSyndromeDecode(setDifference, ss, d);
	if (success == false)
	{
		exit(-1);
		cerr << "Set difference too large, greater than " << (d - 1) / 2
				<< " elements.\n"
				<< "Unable to compute from the given sketches.\n";
		return -1;
	}
	string str1=sketch;
	string str2=testSet;
	str1.erase(str1.end()-7,str1.end());
	str2.erase(str2.end()-8,str2.end());
	str1=sketch.substr(sketch.length()-10,3);
	str2=testSet.substr(testSet.length()-11,3);
	string ds=sketch.substr(0,sketch.length()-10);
	//string sdf=iriscodeds.substr((iriscodeds.length()-4),3)+"-"+str1+"-"+str2+"-differ.set";
	string sdf=ds+str1+"-"+str2+"-differ.set";
	cout<<"sdf:"<<sdf<<"\n"<<sketch+testSet<<endl;
	ofstream outfile(sdf.c_str());
	OutputSetDifference(outfile, setDifference);
	cout << "--end differ--" << endl;
	return 0;
}

int RecSet(string differ, string testSet)
{
	int len1, len2;
	long d;
	//  bool i=strcmp(&argv[1][len1-4], ".set");
	//  cout<<i<<endl;
	ifstream infile1(differ.c_str());
	ifstream infile2(testSet.c_str());
	if (!infile1 || !infile2)
	{
		cerr << "Could not open files!" << endl;
		if (infile1)
			infile1.close();
		if (infile2)
			infile2.close();
		return -1;
	}

	cout << "SetSymmetricDifference" << endl;
	SetSymmetricDifference(infile1, infile2);

	return 0;
}
