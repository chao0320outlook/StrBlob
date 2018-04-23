#pragma once

#include <vector>
#include <list>
#include <string>
#include <memory>

using namespace std;
class StrBlob;

class StrBlobPtr
{
public:
	friend class StrBlob;
	StrBlobPtr();             //构造函数，将curr设定为0
	StrBlobPtr(StrBlob &a, size_t sz = 0); //构造函数，将StrBlob的智能指针与此类中的weak_ptr绑定
	string& deref() const;          //解引用
	StrBlobPtr& incr();             //前缀递增，返回递增后的引用对象
	friend bool operator != (StrBlobPtr str1, StrBlobPtr str2);
private:
	shared_ptr<vector<string>> check(size_t i, const string& msg) const;   //检查函数，返回一个vector<string>的智能指针
	weak_ptr<vector<string>> wptr;    //定义弱智能指针
	size_t curr;                      //设立游标，表示下标
};

class StrBlob
{
public:
	friend class StrBlobPtr;//声明friend
	StrBlob();//默认构造函数
	StrBlob(initializer_list<string> il) :data(make_shared<vector<string>>(il)) {}
	StrBlob(string il) :data(make_shared<vector<string>>(il)) {}//另一构造函数

	typedef vector<string>::size_type size_type;//定义类型别名，方便使用

	size_type size() const { return data->size(); }
	bool empty() { return data->empty(); }                //判断vector<string>是否为空
	void pushback(const string &s) { data->push_back(s); }//向vector<string>中加入元素
	StrBlobPtr begin() { return StrBlobPtr(*this); }
	StrBlobPtr end() { auto ret = StrBlobPtr(*this, data->size()); }

	//访问函数，应首先调用check()
	string& front()
	{
		check(0, "front on empty StrBlob");
		return data->front();
	}
	string& back()
	{
		check(0, "back on empty StrBlob");
		return data->back();
	}
	void popback()
	{
		check(0, "pop_back on empty StrBlob");
		data->pop_back();
	}

private:
	shared_ptr<vector<string>> data;                       //指向vector<string>的智能指针
	void check(size_type i, const string &msg) const       //若访问元素的大小大于data的size,输出错误信息
	{
		if (i > data->size()) throw out_of_range(msg);
	}      //抛出该out_of_range异常，表示不在范围之内

};

StrBlobPtr::StrBlobPtr()
{
	curr = 0;
}

StrBlobPtr::StrBlobPtr(StrBlob &a, size_t sz)
{
	wptr = a.data;
	curr = sz;
}

bool operator!=(StrBlobPtr str1, StrBlobPtr str2)
{
	str1.curr == str2.curr ? true : false;
}

 string& StrBlobPtr::deref() const
{
	auto p = check(curr, "deference past end");
	return (*p)[curr];
}

 StrBlobPtr& StrBlobPtr::incr()
{
	auto p = check(curr, "deference past end");
	++curr;
	return *this;
}

shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string & msg) const
{
	auto ret = wptr.lock();//检查对象是否还存在
	if (!ret)
	{
		throw runtime_error("未绑定");
	}
	if (i >= ret->size())
	{
		throw out_of_range(msg);
	}
	return ret;
}