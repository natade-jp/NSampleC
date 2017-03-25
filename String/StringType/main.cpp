#include <iostream>
#include <string>

using namespace std;

class mystring : public string
{
public:
	mystring() : string() {}
	mystring(const char *str) : string(str) {}
	mystring(const string &s) : string(s) {}
	virtual ~mystring() { cout << "delete" << endl; }
	mystring& operator=(const char *str) {
		string::operator=(str);
		return *this;
	}
	mystring& operator=(const string& s) {
		string::operator=(s);
		return *this;
	}
};

int main(){
	// test 1
	cout << "test1" << endl;
	{
		mystring x;
		{
			mystring text("my object");
			x = text;
			cout << "scope1" << endl;
		}
		cout << "scope2" << endl;
	}
	// test 2 (string型はスカラではない)
	cout << "test2" << endl;
	{
		mystring *x;
		{
			mystring text("my object");
			x = &text;
			cout << "scope1" << endl;
		}
		cout << "scope2" << endl;
	}
	return 0;
}
