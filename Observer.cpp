#include <iostream>
#include <string>
#include <list>

using namespace std;

class Subject;

class Observer              //观察者接口  
{
public:
	Observer(){}
	~Observer(){}
	virtual void Update(Subject*) = 0;
private:
};

class Subject            //被观察者接口  
{
public:
	Subject(){}
	~Subject(){}
	virtual void Notify();
	virtual void Attach(Observer*);
	virtual void Detach(Observer*);
	virtual int GetState();
	virtual void SetState(int state);
private:
	int Tem;
	list<Observer*> m_lst;
};

void Subject::Attach(Observer* pO)
{
	this->m_lst.push_back(pO);
	cout << "链接一个观察者" << endl;
}

void Subject::Detach(Observer* pO)
{
	list<Observer*>::iterator iter;
	iter = find(m_lst.begin(), m_lst.end(), pO);
	if (iter != m_lst.end())
	{
		m_lst.erase(iter);
	}
	cout << "断开一个观测者" << endl;
}

void Subject::Notify()
{
	list<Observer*>::iterator iter = this->m_lst.begin();
	for (; iter != m_lst.end(); iter++)
	{
		(*iter)->Update(this);
	}
}

int Subject::GetState()
{
	return this->Tem;
}

void Subject::SetState(int state)
{
	this->Tem = state;
}

class Heater : public Subject
{
private:
	int Temperature;
public:
	int getTemperature()
	{
		return Temperature;
	}
	void setTemperature(int tem)
	{
		Temperature = tem;
	}
	void boil(){
		for (int i = 90; i < 100; i++)
		{
			Temperature = i;
			this->SetState(90);
			this->Notify();
		}
	}
};

class Display : public Observer
{
private:
	string Status = "未开";
	int Tem;
public:
	void setStatus(string sta)
	{
		Status = sta;
	}
	void dispalyTemperature(int tem)
	{
		if (tem > 95)
		{
			setStatus("水开了");

		}
		cout << "状态：" << Status << endl << "现在温度：" << tem << endl;
	}
	virtual void Update(Subject*);
};

void Display::Update(Subject* pSubject)
{
	this->Tem = pSubject->GetState();
	this->dispalyTemperature(Tem);
}

class Alarm : public Observer{
public:
	void makeAlarm() 
	{
		if (Tem > 95)
		{
			cout << "嘀嘀嘀...水已经烧开 " << endl;
		}
		/*else{
			cout << "报警器：水还没有烧开 " << endl;
		}*/
	}
	virtual void Update(Subject*);
private:
	int Tem;
};

void Alarm::Update(Subject* pSubject)
{
	this->Tem = pSubject->GetState();
	this->makeAlarm();
}

int main()
{
	Observer* p1 = new Display();
	Observer* p2 = new Alarm();

	Subject* pSubject = new Heater();
	pSubject->Attach(p1);
	pSubject->Attach(p2);

	cout << endl;

	for (int i = 90; i < 100; i++)
	{
		pSubject->SetState(i);
		pSubject->Notify();
	}

	cout << endl;

	pSubject->Detach(p2);

	for (int i = 90; i < 100; i++)
	{
		pSubject->SetState(i);
		pSubject->Notify();
	}


	system("pause");
	return 0;
}