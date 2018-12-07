#include <stdio.h>

using namespace std;

class StaticClass {
private:
	int value = 0;
public:
	static void func1(void) {
		func2();
		return;
	}
	static void func2(void) {
		static int counter = 0;
		// this, &value を使用するとコンパイルエラーで通らない
		printf("StaticClass[%d]\n", counter++);
	}
};

class NullClass {
private:
	int value = 0;
public:
	void func1(void) {
		func2();
		return;
	}
	void func2(void) {
		static int counter = 0;
		// this, &value を使用してもコンパイルエラーは出ない
		printf("StaticClass[%d][%p][%p]\n", counter++, this, &value);
	}
};

int main(){
	printf("クラス内部の静的メソッドを呼ぶ\n");
	StaticClass::func1();
	StaticClass::func1();
	
	printf("\nクラス内部のメソッドを静的メソッドとして呼ぶ\n");
	((NullClass *)0)->func1();
	((NullClass *)NULL)->func1();
	((NullClass *)nullptr)->func1();
	
	// 下の記述方法は、「C++の設計と進化 | Bjarne Stroustrup」の366ページで解説があり、
	// 静的メソッドの概念が仕様に盛り込まれる前に使われた方法とのこと。
	//参考 
	// C++でのNULLオブジェクトへのメソッド呼び出しって？
	// http://blog.livedoor.jp/hal_can/archives/52223642.html
	
	return 0;
}

/*

$ ./StaticSample 
クラス内部の静的メソッドを呼ぶ
StaticClass[0]
StaticClass[1]

クラス内部のメソッドを静的メソッドとして呼ぶ
StaticClass[0][(nil)][(nil)]
StaticClass[1][(nil)][(nil)]
StaticClass[2][(nil)][(nil)]

*/
