#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Str
{
private:
	string mstring;
public:
	Str(const string &str){ mstring = str; }
	~Str(){}
	void print()
	{
		cout << "当前字符串为：" << mstring << endl;
	}
};

class  UndoRedo
{
private:
	stack< Str* > mUndo;
	stack< Str* > mRedo;
public:
	UndoRedo(Str* str){ mUndo.push(str); }
	~UndoRedo()
	{
		while (mUndo.empty() == false)
		{
			delete mUndo.top();
			mUndo.pop();
		}
		while (mRedo.empty() == false)
		{
			delete mRedo.top();
			mRedo.pop();
		}
	}

	void Add(Str* str)
	{
		str->print();
		mUndo.push(str);
		while (mRedo.empty() == false)
		{
			delete mRedo.top();
			mRedo.pop();
		}
	}

	void undo(){
		if (mUndo.size() <= 2)
		{
			cout << "撤销失败" << endl;
			return;
		}
		auto str = mUndo.top();
		mRedo.push(str);
		mUndo.pop();
		str = mUndo.top();
		str->print();
	}

	void redo()
	{
		if (mRedo.empty())
		{
			cout << "重做失败" << endl;
			return;
		}
		auto str = mRedo.top();
		str->print();
		mRedo.pop();
		mUndo.push(str);
	}
	//void Print()
	//{
	//	auto str1 = mUndo;
	//	stack< command* >str2;
	//	while (str1.size()>=2)
	//	{
	//		str2.push(str1.top());
	//		str1.pop();
	//	}
	//	while (str2.size()>=1)
	//	{
	//		cout << str2.top();
	//		str1.pop();
	//	}
	//}
};

void help()
{
	cout << "---------------------------------" << endl;
	cout << "\"add + 字符串\"		输入字符" << endl;
	cout << "\"undo\"				撤销" << endl;
	cout << "\"redo\"				重做" << endl;
	cout << "\"quit\"				退出程序" << endl;
	cout << "---------------------------------" << endl;
}

int main()
{
	UndoRedo* p = new UndoRedo(new Str("empty"));
	string str1, str2;
	while (1)
	{
		cout << "请输入指令：" << endl;
		cin >> str1;
		if (str1 == "help"){ help(); }
		if (str1 == "add"){
			cin >> str2;
			p->Add(new Str(str2));
		}
		if (str1 == "undo"){
			p->undo();
		}
		if (str1 == "redo"){
			p->redo();
		}
		if (str1 == "quit"){ break; }
		cout << endl;
	}

	system("pause");
	return 0;
}