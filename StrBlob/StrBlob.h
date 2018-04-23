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
	StrBlobPtr();             //���캯������curr�趨Ϊ0
	StrBlobPtr(StrBlob &a, size_t sz = 0); //���캯������StrBlob������ָ��������е�weak_ptr��
	string& deref() const;          //������
	StrBlobPtr& incr();             //ǰ׺���������ص���������ö���
	friend bool operator != (StrBlobPtr str1, StrBlobPtr str2);
private:
	shared_ptr<vector<string>> check(size_t i, const string& msg) const;   //��麯��������һ��vector<string>������ָ��
	weak_ptr<vector<string>> wptr;    //����������ָ��
	size_t curr;                      //�����α꣬��ʾ�±�
};

class StrBlob
{
public:
	friend class StrBlobPtr;//����friend
	StrBlob();//Ĭ�Ϲ��캯��
	StrBlob(initializer_list<string> il) :data(make_shared<vector<string>>(il)) {}
	StrBlob(string il) :data(make_shared<vector<string>>(il)) {}//��һ���캯��

	typedef vector<string>::size_type size_type;//�������ͱ���������ʹ��

	size_type size() const { return data->size(); }
	bool empty() { return data->empty(); }                //�ж�vector<string>�Ƿ�Ϊ��
	void pushback(const string &s) { data->push_back(s); }//��vector<string>�м���Ԫ��
	StrBlobPtr begin() { return StrBlobPtr(*this); }
	StrBlobPtr end() { auto ret = StrBlobPtr(*this, data->size()); }

	//���ʺ�����Ӧ���ȵ���check()
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
	shared_ptr<vector<string>> data;                       //ָ��vector<string>������ָ��
	void check(size_type i, const string &msg) const       //������Ԫ�صĴ�С����data��size,���������Ϣ
	{
		if (i > data->size()) throw out_of_range(msg);
	}      //�׳���out_of_range�쳣����ʾ���ڷ�Χ֮��

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
	auto ret = wptr.lock();//�������Ƿ񻹴���
	if (!ret)
	{
		throw runtime_error("δ��");
	}
	if (i >= ret->size())
	{
		throw out_of_range(msg);
	}
	return ret;
}