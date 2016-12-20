#include"Composite.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
	cout << "Making root entries" << endl;
	Entry *rootdir = new Directory("root");
	Entry *bindir = new Directory("bin");
	Entry *tmpdir = new Directory("tmp");
	Entry *usrdir = new Directory("usr");
	rootdir->Add(bindir);
	rootdir->Add(tmpdir);
	rootdir->Add(usrdir);
	bindir->Add(new File("vi", 10000));
	bindir->Add(new File("latex", 20000));
	rootdir->Print();

	cout << " " << endl << "Making root entries" << endl;
	Entry *yuki = new Directory("yuki");
	Entry *hanako = new Directory("hanako");
	Entry *tomyra = new Directory("tomyra");
	usrdir->Add(yuki);
	usrdir->Add(hanako);
	usrdir->Add(tomyra);
	yuki->Add(new File("diary.html", 100));
	yuki->Add(new File("Composite.java", 200));
	hanako->Add(new File("meno.tex", 300));
	tomyra->Add(new File("game.doc", 400));
	tomyra->Add(new File("junk.mail", 500));
	rootdir->Print();

	system("pause");
	return 0;
}