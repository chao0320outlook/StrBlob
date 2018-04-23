#pragma once
#include <memory>
#include <vector>
#include <string>

class StrBlob;

class StrBlobPtr
{
public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr(StrBlob &a, size_t sz = 0);    //���һ��Ҫ���ڶ����ļ���ȥ���壬��Ȼ����� ��error C2027: ʹ����δ�������͡�StrBlob������͡�
	StrBlobPtr(const StrBlob &a,size_t sz = 0);
	std::string& deref() const;               //����currλ���ϵ�Ԫ��ֵ��
	StrBlobPtr& incr();                       //����������++curr�����ص����˵������� StrBlobPtr����
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
	//��Ӻ�ɾ��Ԫ��
	void push_back(const std::string &t) { data->push_back(t); }
	void pop_back();
	//Ԫ�ط���
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
	//���data[i]���Ϸ����׳�һ���쳣��
	void check(size_type i, const std::string &msg) const;
};
