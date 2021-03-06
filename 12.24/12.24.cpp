// 12.24.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <memory>

using namespace std;

int main()
{
	string str;
	cin >> str;

	cout << endl;
    auto str_size = str.size();
	char *ptr2 = new char[str_size+1];
	strcpy_s(ptr2, str_size+1, str.c_str());
	unique_ptr<char[]> ptr1(ptr2);
	
	for (size_t i = 0; i != str_size+1; i++)
	{
		cout << ptr1[i];
	}

	int secs = 120;                                  //延时120s的程序
	clock_t delay = secs * CLOCKS_PER_SEC;           //总延时
	clock_t start = clock();                         //开始时间
	while (clock() - start < delay);                 //时间差大于总延时 跳出循环


    return 0;
}

