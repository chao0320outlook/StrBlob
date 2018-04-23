#pragma once
#include <memory>
#include <vector>
#include <string>

class StrBlob;

class StrBlobPtr
{
public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr(StrBlob &a, size_t sz = 0);    //这个一定要放在定义文件中去定义，不然会出现 “error C2027: 使用了未定义类型“StrBlob”错误和。
	StrBlobPtr(const StrBlob &a,size_t sz = 0);
	std::string& deref() const;               //返回curr位置上的元素值。
	StrBlobPtr& incr();                       //功能类似于++curr，返回递增了迭代器的 StrBlobPtr对象。
	friend bool operator != (StrBlobPtr str1, StrBlobPtr str2);

private:
	std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr;
};

class StrBlob
{
public:
	friend class StrBlobPtr;
	using size_type = std::vector<std::string>::size_type; 

	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	//添加和删除元素
	void push_back(const std::string &t) { data->push_back(t); }
	void pop_back();
	//元素访问
	std::string& front();
	std::string& back();

	StrBlobPtr begin() const { return StrBlobPtr(*this,0); }
	StrBlobPtr end() const 
	{
		auto ret = StrBlobPtr(*this, data->size());
		return ret;
	}

private:
	std::shared_ptr<std::vector<std::string>> data;
	//如果data[i]不合法，抛出一个异常。
	void check(size_type i, const std::string &msg) const;
};
