#include <stdio.h>

typedef struct {
	int x;
	int y;
} Struct;

int main(){
	{
		// 1�̍\���̂̂݊m�ۂ���ꍇ
		Struct *kTest = NULL;
		kTest = new Struct;
		kTest->y = 999;		// �A���[���Z�q�ɂ����
		printf("Test 1\n");
		printf("[%d]\n", kTest->y);	// �� ������₷���I
		printf("[%d]\n", (*kTest).y);	// �� ������ɂ���
		printf("[%d]\n", kTest[0].y);	// �� ������ɂ���
		delete kTest;
	}
	{
		// �\���̂̔z����m�ۂ���ꍇ
		Struct *kTest = NULL;
		kTest = new Struct[10];
		kTest[9].y = 999;	// �A���[���Z�����z����g�p�����ق����ǂ�
		printf("Test 2\n");
		printf("[%d]\n", (kTest+9)->y);	// �� ������ɂ���
		printf("[%d]\n", (*(kTest+9)).y);	// �� ������ɂ���
		printf("[%d]\n", kTest[9].y);		// �� ������₷���I
		delete kTest;
	}
	return 0;
}
