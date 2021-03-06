// strblob1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "StrBlob1.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <iterator>
#include <fstream>

using namespace std;

int main()
{
	ifstream in("1.txt");
	string s;
	StrBlob blob;
	while (getline(in, s))
	{
		blob.push_back(s);
	}

	const StrBlob blob1 = blob;
	for (StrBlobPtr pbeg=blob.begin(), pend=blob.end(); pbeg != pend; pbeg.incr())
	{
		cout << pbeg.deref() << std::endl;
	}
	cout << "212" << endl;

	for (StrBlobPtr pbeg = blob1.begin(), pend = blob1.end(); pbeg != pend; pbeg.incr())
	{
		cout << pbeg.deref() << std::endl;
	}

	int secs = 120;                                  //延时120s的程序
	clock_t delay = secs * CLOCKS_PER_SEC;           //总延时
	clock_t start = clock();                         //开始时间
	while (clock() - start < delay);                 //时间差大于总延时 跳出循环

	return 0;
}



