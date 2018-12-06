#include <stdio.h>

char strBuffer[256];

char *formatof(void) {
	sprintf(strBuffer, "void");
	return strBuffer;
}

char *formatof(void *x) {
	sprintf(strBuffer, "void * [%p]", x);
	return strBuffer;
}

char *formatof(signed char x) {
	sprintf(strBuffer, "signed char[0x%02x]", x);
	return strBuffer;
}

char *formatof(unsigned char x) {
	sprintf(strBuffer, "unsigned char[0x%02x]", x);
	return strBuffer;
}

char *formatof(signed char *x) {
	sprintf(strBuffer, "signed char*[%p]", x);
	return strBuffer;
}

char *formatof(unsigned char *x) {
	sprintf(strBuffer, "unsigned char*[%p]", x);
	return strBuffer;
}

char *formatof(signed short x) {
	sprintf(strBuffer, "signed short[0x%04hx]", x);
	return strBuffer;
}

char *formatof(unsigned short x) {
	sprintf(strBuffer, "unsigned short[0x%04hx]", x);
	return strBuffer;
}

char *formatof(signed short *x) {
	sprintf(strBuffer, "signed short*[%p]", x);
	return strBuffer;
}

char *formatof(unsigned short *x) {
	sprintf(strBuffer, "unsigned short*[%p]", x);
	return strBuffer;
}

char *formatof(signed long x) {
	sprintf(strBuffer, "signed long[0x%08lx]", x);
	return strBuffer;
}

char *formatof(unsigned long x) {
	sprintf(strBuffer, "unsigned long[0x%08lx]", x);
	return strBuffer;
}

char *formatof(signed long *x) {
	sprintf(strBuffer, "signed long*[%p]", x);
	return strBuffer;
}

char *formatof(unsigned long *x) {
	sprintf(strBuffer, "unsigned long*[%p]", x);
	return strBuffer;
}

char *formatof(signed long long x) {
	sprintf(strBuffer, "signed long long[0x%016llx]", x);
	return strBuffer;
}

char *formatof(unsigned long long x) {
	sprintf(strBuffer, "unsigned long long[0x%016llx]", x);
	return strBuffer;
}

char *formatof(signed long long *x) {
	sprintf(strBuffer, "signed long long*[%p]", x);
	return strBuffer;
}

char *formatof(unsigned long long *x) {
	sprintf(strBuffer, "unsigned long long*[%p]", x);
	return strBuffer;
}

char *formatof(char x) {
	sprintf(strBuffer, "char[%d]", x);
	return strBuffer;
}

char *formatof(char *x) {
	sprintf(strBuffer, "char*[%p]", x);
	return strBuffer;
}

char *formatof(const char *x) {
	sprintf(strBuffer, "const char*[%s]", x);
	return strBuffer;
}

char *formatof(int x) {
	sprintf(strBuffer, "int[%d]", x);
	return strBuffer;
}

char *formatof(int *x) {
	sprintf(strBuffer, "int*[%p]", x);
	return strBuffer;
}

char *formatof(float x) {
	sprintf(strBuffer, "float[%e]", x);
	return strBuffer;
}

char *formatof(float *x) {
	sprintf(strBuffer, "float*[%p]", x);
	return strBuffer;
}

char *formatof(double x) {
	sprintf(strBuffer, "double[%e]", x);
	return strBuffer;
}

char *formatof(double *x) {
	sprintf(strBuffer, "double*[%p]", x);
	return strBuffer;
}

#define printType(value) printf("%s, size=%d\n", formatof(value), sizeof(value));

int main() {
	
	// auto は宣言とともに値の代入が必要
	// 途中で型の変更は不可能
	
	printf("* 1\n");
	{
		auto var = 1;
		printType(var);
		var = 2.4;
		printType(var);
	}
	
	printf("\n");
	printf("* 1.0f\n");
	{
		auto var = 1.0f;
		printType(var);
		var = (int)3;
		printType(var);
	}
	
	printf("\n");
	printf("* \"123\"\n");
	{
		auto var = "123";
		printType(var);
		var = "456";
		printType(var);
	}
	
	printf("\n");
	printf("* '1'\n");
	{
		auto var = '1';
		printType(var);
		var = 0xFFFFFFFF;
		printType(var);
	}
	
	return 0;
}

/*
./Auto 
* 1
int[1], size=4
int[2], size=4

* 1.0f
float[1.000000e+00], size=4
float[3.000000e+00], size=4

* "123"
const char*[123], size=4
const char*[456], size=4

* '1'
char[49], size=1
char[-1], size=1
*/