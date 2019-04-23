#include <iostream>
#include <string>
using namespace std;

class Class1 {
private:
	string name;
public:
	Class1(string name) { this->name = name; }
	~Class1() { cout << "class1" << this->name << endl; }
};

class Class2 {
private:
	string name;
	Class1 *class1;	// これをdeleteしないとメモリリーク
public:
	Class2(string name) { this->name = name; this->class1 = new Class1("test1"); }
	~Class2() { cout << "class2" << this->name << endl; }
};

void func() {
	{ Class2 *cl = new Class2("test1"); delete cl; }
	{ Class2 *cl = new Class2("test2"); }	// delete忘れでメモリリーク
	{ Class2 cl("test3"); }
}

int main(){
	func();
	return 0;
}

/*
# make
g++ -std=c++0x -O0 -Wall -o Destructor main.cpp
main.cpp: In function 'void func()':
main.cpp:24:12: warning: unused variable 'cl' [-Wunused-variable]
  { Class2 *cl = new Class2("test2"); } // delete忘れでメモリリーク
            ^

# ./Destructor
class2test1
class2test3

*/