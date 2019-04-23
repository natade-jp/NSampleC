#include <iostream>
#include <string>

using namespace std;

class Class {
public:
	Class() { cout << "コンストラクタ" << endl; }
	virtual ~Class() { cout << "デストラクタ" << endl; }
	void func(const char *text) { cout << text << endl; }
};

struct Struct {
	Struct() { cout << "コンストラクタ" << endl; }
	virtual ~Struct() { cout << "デストラクタ" << endl; }
	void func(const char *text) { cout << text << endl; }
};

int main(){
	{
		Class *sc = new Class();
		sc->func("クラス");
		delete sc;
	}
	{
		Struct *sc = new Struct();
		sc->func("構造体");
		delete sc;
	}
	return 0;
}

/*
# ./StructSample
コンストラクタ
クラス
デストラクタ
コンストラクタ
構造体
デストラクタ
*/