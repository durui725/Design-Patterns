#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Entry
{
public:
	Entry(string name) : m_strCompname(name){}
	Entry(string name, int size) : m_strCompname(name), m_sizeCompname(size){}
	virtual ~Entry(){}
	virtual void Operation() = 0;
	virtual void Add(Entry *) = 0;
	virtual void Remove(Entry *) = 0;
	virtual Entry *GetChild(int) = 0;
	virtual string GetName()
	{
		return m_strCompname;
	}
	virtual int GetSize()
	{
		return m_sizeCompname;
	}
	virtual void Print() = 0;
protected:
	string m_strCompname;
	int m_sizeCompname = 0;
};
class File : public Entry
{
public:
	File(string name, int size) : Entry(name, size)
	{}
	void Operation(){}
	void Add(Entry *pEntry){}
	void Remove(Entry *pEntry){}
	Entry *GetChild(int index)
	{
		return NULL;
	}
	void Print(){}
};
class Directory : public Entry
{
public:
	Directory(string name) : Entry(name)
	{}
	~Directory()
	{
		vector<Entry *>::iterator it = m_vecComp.begin();
		while (it != m_vecComp.end())
		{
			if (*it != NULL)
			{
				delete *it;
				*it = NULL;
			}
			m_vecComp.erase(it);
			it = m_vecComp.begin();
		}
	}
	void Operation(){}
	void Add(Entry *pEntry)
	{
		m_vecComp.push_back(pEntry);
	}
	void Remove(Entry *pEntry)
	{
		for (vector<Entry *>::iterator it = m_vecComp.begin(); it != m_vecComp.end(); ++it)
		{
			if ((*it)->GetName() == pEntry->GetName())
			{
				if (*it != NULL)
				{
					delete *it;
					*it = NULL;
				}
				m_vecComp.erase(it);
				break;
			}
		}
	}
	Entry *GetChild(int index)
	{
		if (index > m_vecComp.size())
		{
			return NULL;
		}
		return m_vecComp[index - 1];
	}
	void Print()
	{
		for (vector<Entry *>::iterator it = m_vecComp.begin(); it != m_vecComp.end(); ++it)
		{
			cout << (*it)->GetName() << endl;
		}
	}
private:
	vector<Entry *> m_vecComp;		//使用vector来存储数据。
};