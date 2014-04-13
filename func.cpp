/*************************************************************************
 > File Name: func.cpp
 > Author: sandy
 > Mail: sandy@luo.bo
 > Created Time: 2014年03月31日 星期一 16时22分35秒
 ************************************************************************/

#include<iostream>
#include"func.h"

using namespace std;

#ifndef RLEN
//随机的r的长度
#define RLEN 256
#endif

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

//将char字符转为string类型
string ctos(unsigned char data)
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

//将byte* 转为二进制字符串
string ByteToStr(BYTE *data, int setlen)
{
	string s = "";
	stringstream ss;
	for (int i = 0; i < setlen; i++)
	{
		s = ctos(data[i]) + s;
	}
	//cout << s << endl;
	return s;
}

int parsIris(BYTE* IrisCode, BYTE** iriset, const int len, Config config,
		string setName)
{
	int N = config.Num;
	//计算分段后每段的大小
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
	ofstream wriSet(setName.c_str());
	wriSet << "t=" << config.T << endl;
	wriSet << "m=" << config.M << endl << endl;
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

int genR(BYTE** r, int rlen)
{
	const int LEN = 62; //26+26+10
	//char* charset=new char[LEN];//{'0','1','2','3','4','5','6','7','8','9',ABCDEFGHIGKLMNOPQ}
	//memset(charset,'\0',LEN);
	BYTE charset[] =
			"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	*r = (BYTE*) malloc(sizeof(BYTE) * rlen);
	memset(*r, '\0', rlen + 1);
	srand((unsigned) time(0));
	for (int i = 0; i < rlen; i++)
	{
		(*r)[i] = charset[(rand() % LEN)];
	}
	//cout << "genR" << *r << endl;
	return 0;
}

unsigned char* ranCode(BYTE* iriscode, const int len, BYTE* r,
		unsigned char* rancode, Config config)
{
	static unsigned char m[SHA_DIGEST_LENGTH];
	if (rancode == NULL)
		rancode = m;
	//OPENSSL evp文件夹下的实现计算两段数据和起来的SHA1值
	EVP_MD_CTX c;
	EVP_MD_CTX_init(&c);
	//EVP_Digest(iriscode,len,rancode,NULL,EVP_sha1(),NULL);
	EVP_DigestInit_ex(&c, config.digest, NULL);
	EVP_DigestUpdate(&c, iriscode, len);
	EVP_DigestUpdate(&c, r, config.rlen);
	EVP_DigestFinal_ex(&c, rancode, NULL);

	//两种打印SHA-1的方法
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
		printf("%02x", rancode[i]);
	cout << endl;
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
		cout << hex << setw(2) << setfill('0') << (int) rancode[i];
	cout << endl;

	EVP_MD_CTX_cleanup(&c);
	return rancode;
}

//int genPinSketch(const string filename)
int writeConfig(Config wconfig)
{
	//使用glib中GKeyFile的方法写入配置文件 需要指定编译的库gtk+-2.0
	GKeyFile* config = g_key_file_new();
	unsigned int length = 0;
	g_key_file_set_integer(config, "IRIS", "NUM", wconfig.Num);
	g_key_file_set_integer(config, "IRIS", "T", wconfig.T);
	g_key_file_set_integer(config, "IRIS", "M", wconfig.M);
	g_key_file_set_string(config, "IRIS", "DIGEST",
			(gchar*) wconfig.digest_name.c_str());
	g_key_file_set_integer(config, "IRIS", "RLEN", wconfig.rlen);
	const char* ran = (char*) wconfig.r;
	g_key_file_set_string(config, "IRIS", "R", ran);
	gchar* content = (gchar *) g_key_file_to_data(config, &length, NULL);
	g_print("%s\n", content);
	
	//记录
	FILE* fp = fopen("config.ini", "w");
	if (fp == NULL)
		return -1;
	fwrite((const void*) content, 1, (unsigned int) length, fp);
	fclose(fp);
	g_key_file_free(config);
	return 0;

}
int readConfig(string filename, Config &rconfig)
{
	GKeyFile* config = g_key_file_new();
	g_key_file_load_from_file(config, (const gchar*) filename.c_str(),
			(GKeyFileFlags) (G_KEY_FILE_KEEP_COMMENTS
					| G_KEY_FILE_KEEP_TRANSLATIONS), NULL);

	gint num = g_key_file_get_integer(config, "IRIS", "NUM", NULL);
	g_print("NUM=%d\n", num);

	gint t = g_key_file_get_integer(config, "IRIS", "T", NULL);
	g_print("T=%d\n", t);

	gint m = g_key_file_get_integer(config, "IRIS", "M", NULL);
	g_print("M=%d\n", m);

	gchar* digest = g_key_file_get_string(config, "IRIS", "DIGEST", NULL);
	g_print("DIGEST=%s\n", digest);

	gint rlen = g_key_file_get_integer(config, "IRIS", "RLEN", NULL);
	g_print("RLEN=%d\n", rlen);

	gchar* r = g_key_file_get_string(config, "IRIS", "R", NULL);
	g_print("R=%s\n", r);

	rconfig.Num = num;
	rconfig.M = m;
	rconfig.T = t;
	rconfig.digest_name = string(digest);
	rconfig.rlen = rlen;
	rconfig.r = (BYTE*) r;
	rconfig.digest = EVP_sha1();

	g_key_file_free(config);
	return 0;
}

string itoa(int i)
{
	//Linux下或者说标准C中没有itoa函数，使用sprintf代替
	char str[25];
	sprintf(str, "%d", i); //换成这一句吧^_^
	//printf("integer = %d string = %s\n", i, str);
	return string(str);
}

//将string 类型和根据setlen恢复BYTE* ，其实setlen 可以根据data.length()计算
BYTE* StrToByte(string data, int setlen)
{
	BYTE* rdata = (BYTE*) malloc(sizeof(BYTE) * setlen);

	for (int i = 0; i < setlen; i++)
	{
		BYTE temp = (BYTE) 0;
		for (int j = 0; j < sizeof(BYTE) * 8; j++)
		{
			if (data.at(i * 8 + j) == '1')
				temp += 1 << (7 - j);
		}
		rdata[i] = temp;
	}
	return rdata;
}
BYTE* RecData(string setname, Config config)
{
	ifstream infile(setname.c_str());
	if (!infile)
	{
		cerr << "Could not open files!" << endl;
		return NULL;
	}
	string line;
	string data;
	int setlen = 0;
	BYTE* rdata = NULL;
	BYTE* temp ;
	BYTE** iriset = NULL;
	for (int i = 1; i <= config.Num; i++)
	{
		*temp=0x00;
		infile >> line;
		if (i == 1)
		{
			if (line.at(0) != '1')
			{
				cerr << "Read Error !" << endl;
				return NULL;
			}
			setlen = (line.size() - 1) / 8;
			int len = config.Num * setlen;
			rdata = (BYTE*) malloc(sizeof(BYTE) * len);	//定义返回的二进制数据大小
			memset(rdata, '\0', len);
		}
		data = line.substr(line.find(itoa(i)) + itoa(i).length());
		if (data.length() / 8 != setlen)
		{
			cerr << "Read Error !" << endl;
			return NULL;
		}
		temp = StrToByte(data, setlen);
		//strcat((char *)rdata,(char *)temp);
		//Eclipse在此处数组显示有问题
		memcpy(rdata+(i-1)*setlen,temp,setlen);
		//cout<<"i:"<<i<<"\t data:"<<data<<endl;

	}
	return rdata;
}
