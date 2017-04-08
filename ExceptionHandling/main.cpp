#include "stdio.h"

// signal
#include <signal.h>

int error1() {
	throw "exception";
	return 0;
}

int testcase1() {
	printf("テスト1\n");
	try {
		printf("ここは実行される\n");
		error1();
		printf("ここは実行されない\n");
	}
	catch (const char *strErrorText) {
		printf("エラーが発生[%s]\n", strErrorText);
	}
	printf("テスト1の終了\n");
	return 0;
}

// どの例外を返すか伝えることができる
int error2(int errortype) throw(int, const char*) {
	if(errortype == 0) {
		throw 123;
	}
	else {
		throw "abc";
	}
	return 0;
}

int testcase2() {
	printf("テスト2\n");
	
	// int型例外
	try {
		error2(0);
	}
	catch (int iErrorNumber) {
		printf("例外A int[%d]\n", iErrorNumber);
	}
	catch (const char *strErrorText) {
		printf("例外A const char[%s]\n", strErrorText);
	}
	// char型例外
	try {
		error2(1);
	}
	catch (int iErrorNumber) {
		printf("例外B int[%d]\n", iErrorNumber);
	}
	catch (const char *strErrorText) {
		printf("例外B const char[%s]\n", strErrorText);
	}
	// int型例外
	try {
		error2(0);
	}
	catch ( ... ) {
		// 「...」と書くことで全ての例外を捕獲できる。
		printf("例外C\n");
	}
	printf("テスト2の終了\n");
	return 0;
}

// シグナルが発生して、キャッチできない例外もある。
// SIGFPE 8 浮動小数点例外 が発生する。
static void vSignalHandler(int iSigNum) {
	printf("例外[%d]\n", iSigNum);
	// POSIX では SIGFPE を無視した場合の動作は未定義...
	return;
}
int testcase3() {
	printf("テスト3\n");
	
	// try catch では捕まえられないものを補足
	if (signal(SIGFPE, vSignalHandler) == SIG_ERR) {
		return 1;
	}
	try {
		int x = 0 / 0;
		// catch も入らない
	}
	catch ( ... ) {
		printf("ここは実行されない\n");
	}
	printf("テスト3の終了\n");
	return 0;
}

int testcase4() {
	printf("テスト4\n");
	
	// int型例外 捕獲漏れ
	//  これをすると、SIGABRT シグナルが発生してプログラムがストップしてしまう。
	//  terminate called after throwing an instance of 'int' Aborted.
	//  他のC++では、set_terminateで補足が可能
	// try catch では捕まえられないものを補足
	if (signal(SIGABRT, vSignalHandler) == SIG_ERR) {
		return 1;
	}
	try {
		error2(0);
	}
	catch (const char *strErrorText) {
		printf("ここは実行されない\n");
	}
	
	printf("テスト4の終了\n");
	return 0;
}


// gcc の場合は、コンパイルオプションによって例外の扱いも変わる
// -fexceptions		例外有効化。C++ではデフォルトで有効となる。C++とCを混在させる場合は、これを付けたほうが良い場合がある。
// -fcheck-new 		new を使用して作成できなかった場合に例外を発生させる。
// -funwind-tables	C言語でC++のモジュールを使用したときに、C++の例外でクラッシュしないようにする。

int main() {
	
	printf("テスト開始\n");
	testcase1();
	testcase2();
	testcase3();
	testcase4();
	printf("テスト終了\n");
	return 0;
}

/*
pi@raspberrypi:~/git/NSampleC/ExceptionHandling $ make
g++ -std=c++0x -O0 -Wall -o ExceptionHandling main.cpp
main.cpp: In function ‘int testcase3()’:
main.cpp:86:13: warning: division by zero [-Wdiv-by-zero]
   int x = 0 / 0;
             ^
main.cpp:86:7: warning: unused variable ‘x’ [-Wunused-variable]
   int x = 0 / 0;
       ^
pi@raspberrypi:~/git/NSampleC/ExceptionHandling $ ./ExceptionHandling
テスト開始
テスト1
ここは実行される
エラーが発生[exception]
テスト1の終了
テスト2
例外A int[123]
例外B const char[abc]
例外C
テスト2の終了
テスト3
例外[8]
テスト3の終了
テスト4
terminate called after throwing an instance of 'int'
例外[6]
中止
*/