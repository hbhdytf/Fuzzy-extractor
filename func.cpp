/*************************************************************************
 > File Name: func.cpp
 > Author: sandy
 > Mail: sandy@luo.bo
 > Created Time: 2014年03月31日 星期一 16时22分35秒
 ************************************************************************/

#include<iostream>
#include"func.h"

using namespace std;

void string_replace(string&s1, const string&s2, const string&s3)
{
	string::size_type pos = 0;
	string::size_type a = s2.size();
	string::size_type b = s3.size();
	while ((pos = s1.find(s2, pos)) != string::npos)
	{
		s1.replace(pos, a, s3);
		pos += b;
	}
}

string chooseIris(const char* ResulTxt)
{
	ifstream infile(ResulTxt);
	if (!infile)
	{
		cerr << "Could not open files!" << endl;
		exit(-1);
	}

	//计算每个图像的评分选择最小的那个作为模板
	string file1, file2, score;
	map<string, double> mapS;
	map<string, double>::iterator iter;
	double temp;
	while (infile >> file1 >> file2 >> score)
	{
		//find element
		iter = mapS.find(file1);
		if (iter != mapS.end())
		{
			temp = mapS[file1];
			mapS[file1] = temp + atof(score.c_str());
		}
		else
		{
			mapS.insert(make_pair(file1, atof(score.c_str())));
		}
		//cout<<file1<<" "<<file2<<" "<<score<<endl;
	}
	map<string, double>::iterator tempit;
	map<string, double>::iterator minit;

	//计算最小值
	for (minit = (tempit = mapS.begin()); tempit != mapS.end(); tempit++)
	{
		if (tempit->second < minit->second)
		{
			minit = tempit;
		}
		//cout<<tempit->first<<"--"<<tempit->second<<endl;
	}
	infile.close();
	cout << "min:--" << minit->first << "--" << minit->second << endl;
	//替换
	string name = minit->first;
	string_replace(name, string(".tiff"), string("_code.bmp"));
	return name;
}

void SaveToFile(unsigned char* buffer, int len)
{
	ofstream ofs("byte.bin", ios::out | ios::binary);
	copy(buffer, buffer + len, ostream_iterator<char>(ofs));
	ofs.close();
}

BYTE*
getIrisCode(const string IrisTemplate, int & width, int & height)
{
	IplImage *pImage = cvLoadImage(IrisTemplate.c_str(), 0);
	if (!pImage)
	{
		cout << "Cannot load image : " << IrisTemplate << endl;
		exit(-1);
	}
	//提取图像数据
	BYTE* data = (BYTE*) pImage->imageData;
	width = pImage->width;
	height = pImage->height;
	//cout<<pImage->depth<<IPL_DEPTH_8U<<endl;
	/*//just for test
	 cout<<pImage->width<<" "<<pImage->height<<endl;
	 cout<<pImage->widthStep<<endl;
	 for(int i=0;i<pImage->height;i++)
	 for(int j=0;j<pImage->width;j++)
	 data[i*pImage->widthStep+j]=255-data[i*pImage->widthStep+j];
	 //cvSaveImage("test.bmp",pImage);
	 IplImage *iplImage;
	 iplImage = cvCreateImageHeader(cvSize(pImage->width,pImage->height),IPL_DEPTH_8U,1);
	 cvSetData(iplImage,data,pImage->widthStep);
	 cvSaveImage("test1.bmp",iplImage);*/
	return data;
}
string itos(unsigned char data)
{
	string str = "";
	// 二进制表示

	char a[9] =
	{ '\0' };
	for (int i = 0; i < 8; i++)
	{
		a[7 - i] = '0' + (char) (data & 0x01);
		data = data >> 1;
	}
	str = string(a);
	return str;
	// FF-->1 00-->0 的转化方式
	/*
	 if(data)
	 return str+"1";
	 else
	 return str+"0";
	 */
}

string ByteToStr(BYTE *data, int setlen)
{
	string s = "";
	stringstream ss;
	for (int i = 0; i < setlen; i++)
	{
		s = itos(data[i]) + s;
	}
	cout << s << endl;
	return s;
}

int parsIris(BYTE* IrisCode, BYTE** iriset, const int len, const unsigned int N)
{
	int setlen = len % N == 0 ? len / N : (int) len / N + 1;
	BYTE* data = (BYTE*) malloc(sizeof(BYTE) * (setlen * N));
	memset(data, '\0', (setlen * N));
	memcpy(data, IrisCode, len);

	iriset = new BYTE*[N];
	for (int i = 0; i < N; i++)
	{
		iriset[i] = (BYTE*) malloc(sizeof(BYTE) * setlen);
		memset(iriset[i], '\0', setlen);
		memcpy(iriset[i], data + i * setlen, setlen);
	}
	//现阶段打算和pinSketch分开进行，故将集合写入集合文件 A.set
	ofstream wriSet("Iris.set");
	wriSet << "t=" << T << endl;
	wriSet << "m=" << M << endl << endl;
	wriSet << "[" << endl;
	for (int i = 0; i < N; i++)
	{
		wriSet << i + 1 << ByteToStr(iriset[i], setlen) << endl;
	}
	wriSet << "]" << endl;
	wriSet.close();

	//释放数据
	for (int i = 0; i < N; i++)
		free(iriset[i]);
	free(data);
	delete iriset;
	return 1;

}

