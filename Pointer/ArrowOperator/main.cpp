#include <stdio.h>

typedef struct {
	int x;
	int y;
} Struct;

int main(){
	{
		// 1つの構造体のみ確保する場合
		Struct *kTest = NULL;
		kTest = new Struct;
		kTest->y = 999;		// アロー演算子による代入
		printf("Test 1\n");
		printf("[%d]\n", kTest->y);	// ← 分かりやすい！
		printf("[%d]\n", (*kTest).y);	// ← 分かりにくい
		printf("[%d]\n", kTest[0].y);	// ← 分かりにくい
		delete kTest;
	}
	{
		// 構造体の配列を確保する場合
		Struct *kTest = NULL;
		kTest = new Struct[10];
		kTest[9].y = 999;	// アロー演算しより配列を使用したほうが良い
		printf("Test 2\n");
		printf("[%d]\n", (kTest+9)->y);	// ← 分かりにくい
		printf("[%d]\n", (*(kTest+9)).y);	// ← 分かりにくい
		printf("[%d]\n", kTest[9].y);		// ← 分かりやすい！
		delete kTest;
	}
	return 0;
}

/*
# ./ArrowOperator
Test 1
[999]
[999]
[999]
Test 2
[999]
[999]
[999]
*/