#include <iostream>
#include <string>
#include <memory>

using namespace std;

class MyClass {
private:
	string name;
	MyClass *class1;
public:
	MyClass(string name) { this->name = name; }
	~MyClass() { cout << "end " << this->name << endl; }
	void func() { cout << "func " << this->name << endl; }
};

void func() {
	{
		MyClass *mc = new MyClass("test1");
		mc->func();
		delete mc;
	}
	{
		MyClass *mc = new MyClass("test2");
		mc->func();
	}
	{
		MyClass mc("test3");
		mc.func();
	}
	{
		shared_ptr<MyClass> mc(new MyClass("test4"));
		mc->func();
	}
	{
		shared_ptr<MyClass> mc = shared_ptr<MyClass>(new MyClass("test5"));
		mc->func();
	}
	{
		shared_ptr<MyClass> mc1 = shared_ptr<MyClass>(new MyClass("test6"));
		{
			shared_ptr<MyClass> mc2 = shared_ptr<MyClass>(new MyClass("test7"));
			mc1 = mc2;
		}
		mc1->func();
	}
	{
		shared_ptr<MyClass> mc = make_shared<MyClass>("test8");;
		mc->func();
	}
	{
		shared_ptr<MyClass> mc = NULL;
		{
			mc = make_shared<MyClass>("test9");
			mc->func();
			cout << "point 1" << endl;
		}
		cout << "point 2" << endl;
	}
}

int main(){
	func();
	return 0;
}
