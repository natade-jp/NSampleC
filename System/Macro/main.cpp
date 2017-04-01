#include <stdio.h>

// ANSI C
#ifdef __STDC__
#define IS_ANSIC	printf("IS_ANSIC %d\n", __STDC__);
#else
#define IS_ANSIC	printf("IS_ANSIC %d\n", 0);
#endif

// GCC
#ifdef __GNUC__
#define IS_GCC	printf("IS_GCC version %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#else
#define IS_GCC	printf("IS_GCC %d\n", 0);
#endif

// Clang
#ifdef __clang__
#define IS_CLANG	printf("IS_CLANG version %d.%d.%d\n", __clang_major__, __clang_minor__, __clang_patchlevel__);
#else
#define IS_CLANG	printf("IS_CLANG %d\n", 0);
#endif

// Apple
#ifdef __APPLE__
#define IS_APPLE	printf("IS_APPLE version %d\n", __APPLE_CC__);
#else
#define IS_APPLE	printf("IS_APPLE %d\n", 0);
#endif

// Intel
#ifdef __INTEL_COMPILER
#define IS_INTEL	printf("IS_INTEL version %f\n", __INTEL_COMPILER / 100.0 );
#else
#define IS_INTEL	printf("IS_INTEL %d\n", 0);
#endif

// define の前に入れる
#   define	TEST_SPACE	printf("space test\n");
#	define	TEST_TAB	printf("tab test\n");

// 引数
#define X(STR)			printf("%s\n", (STR));

// 文字列化
#define TEXT(NUMBER)	#NUMBER

// トークン連結演算子
#define JOIN(a, b)			a ## b

// 範囲
#define HANI
#undef  HANI
#ifdef  HANI
#define TEST_HANI	printf("HANI_X\n");
#else
#define TEST_HANI	printf("HANI_Y\n");
#endif

// 可変長マクロ（C99）
#define printf2(text, ...)	printf("[" text "]\n", __VA_ARGS__)

int main(void){
	
	// ANSI C( ISO/IEC 9899:1990 )
	printf("filename %s\n", __FILE__);
	printf("line     %d\n", __LINE__);
	printf("compile  %s %s\n", __DATE__, __TIME__);
	printf("update   %s\n", __TIMESTAMP__);
	IS_ANSIC
	
	// 各コンパイラ
	IS_GCC
	IS_CLANG
	IS_APPLE
	IS_INTEL
	
	// define の書き方
	TEST_SPACE
	TEST_TAB
	
	// 引数など
	X("あいうえお");
	
	// 文字列化
	printf("string -> %s\n", TEXT(1234567890));
	printf("string -> %s\n", TEXT(123.456));
	printf("string -> %s\n", TEXT(ABCDEFG));
	
	// トークン連結演算子
	JOIN(print,f)("join!\n");
	
	// 可変長引数
	printf2("test = %d", 100);
	
	// 範囲
	TEST_HANI
	
	return 0;
}

/*
filename main.cpp
line     68
compile  Apr  1 2017 16:01:32
update   Sat Apr  1 16:01:26 2017
IS_ANSIC 1
IS_GCC version 4.9.2
IS_CLANG 0
IS_APPLE 0
IS_INTEL 0
space test
tab test
あいうえお
string -> 1234567890
string -> 123.456
string -> ABCDEFG
join!
[test = 100]
HANI_Y
*/
