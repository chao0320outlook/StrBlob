#include "stdafx.h"
#include "strblob1.h"

using namespace std;


//定义构造函数
StrBlob::StrBlob() :data(make_shared<vector<string>>())
{

}

StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il))
{

}

void StrBlob::check(size_type i, const string &msg) const
{
	if (i >= data->size())
		throw out_of_range(msg);
}

string& StrBlob::front()
{
	check(0, "front on empty StrBlob");
	return data->front();
}

string& StrBlob::back()
{
	check(0, "back on empty StrBlob");
	return data->back();
}

void StrBlob::pop_back()
{
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}

StrBlobPtr::StrBlobPtr(StrBlob &a, size_t sz) :wptr(a.data), curr(sz)
{
}

StrBlobPtr::StrBlobPtr(const StrBlob &a, size_t sz) : wptr(a.data), curr(sz)
{
}

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i, const std::string &msg) const
{
	auto ret = wptr.lock();
	if (!ret)
		throw std::out_of_range(msg);
	return ret;
}

std::string& StrBlobPtr::deref() const
{
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}

bool operator!=(StrBlobPtr str1, StrBlobPtr str2)
{
	return str1.curr == str2.curr ? false : true;
}

