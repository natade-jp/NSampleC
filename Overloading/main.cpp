#include "stdio.h"

void Func(void) {
	printf("void\n");
}

void Func(unsigned char x) {
	printf("unsigned char[0x%02X]\n", x);
}

void Func(int x) {
	printf("int[0x%08X]\n", x);
}

void Func(unsigned long long x) {
	printf("unsigned long long[0x%llx]\n", x);
}

void Func(float x) {
	printf("float[%e]\n", x);
}

void Func(double x) {
	printf("double[%e]\n", x);
}

int main() {
	printf("* unsigned char *\n");
	Func((unsigned char)0xFF);
	Func((unsigned char)0x01 + (unsigned char)0x01);
	Func((unsigned char)((unsigned char)0x01 + (unsigned char)0x01));
	
	printf("* unsigned long long *\n");
	Func((unsigned long long)0xFF);
	Func((unsigned long long)0x01 + (unsigned long long)0x01);
	Func((unsigned long long)((unsigned long long)0x01 + (unsigned long long)0x01));
	
	printf("* float *\n");
	Func(1.0f + 1.0f);
	Func(1.4e-45f * 0.0000001f);
	
	printf("* double *\n");
	Func(1.4e-45 * 0.0000001);
	return 0;
}

/*
./Overloading 
* unsigned char *
unsigned char[0xFF]
int[0x00000002]
unsigned char[0x02]
* unsigned long long *
unsigned long long[0xff]
unsigned long long[0x2]
unsigned long long[0x2]
* float *
float[2.000000e+00]
float[0.000000e+00]
* double *
double[1.400000e-52]
*/