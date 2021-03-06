// 12.27.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "12.27_h.h"
#include <ctime>

int main()
{
	ifstream infine("1.txt");
	TextQuery tq(infine);
	while (true)
	{
		string word;
		cout << "输入想要查询的单词" << endl;
		if (!(cin >> word) || word == "q")
			break;
		print(cout, tq.check(word));
	}

	int secs = 120;                                  //延时120s的程序
	clock_t delay = secs * CLOCKS_PER_SEC;           //总延时
	clock_t start = clock();                         //开始时间
	while (clock() - start < delay);                 //时间差大于总延时 跳出循环

    return 0;
}

