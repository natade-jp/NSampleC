#include <stdio.h>

char strBuffer[256];

char *formatof(void) {
	sprintf(strBuffer, "void");
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

char *formatof(signed short x) {
	sprintf(strBuffer, "signed short[0x%04hx]", x);
	return strBuffer;
}

char *formatof(unsigned short x) {
	sprintf(strBuffer, "unsigned short[0x%04hx]", x);
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

char *formatof(signed long long x) {
	sprintf(strBuffer, "signed long long[0x%016llx]", x);
	return strBuffer;
}

char *formatof(unsigned long long x) {
	sprintf(strBuffer, "unsigned long long[0x%016llx]", x);
	return strBuffer;
}

char *formatof(int x) {
	sprintf(strBuffer, "int[%d]", x);
	return strBuffer;
}

char *formatof(float x) {
	sprintf(strBuffer, "float[%e]", x);
	return strBuffer;
}

char *formatof(double x) {
	sprintf(strBuffer, "double[%e]", x);
	return strBuffer;
}

#define printType(value) printf("%s, size=%d\n", formatof(value), sizeof(value));

int main() {
	printf("* unsigned char\n");
	printType((unsigned char)0xFF);
	printType((unsigned char)0x01 + (unsigned char)0x01);
	printType((unsigned char)((unsigned char)0x01 + (unsigned char)0x01));
	
	printf("\n");
	printf("* signed short\n");
	printType((signed short)0xFFFF);
	printType((signed short)0x0001 + (signed short)0x0001);
	printType((signed short)((signed short)0x0001 + (signed short)0x0001));
	
	printf("\n");
	printf("* signed long\n");
	printType((signed long)0xFFFFFFFF);
	printType((signed long)0x00000001 + (signed long)0x00000001);
	printType((signed long)((signed long)0x00000001 + (signed long)0x00000001));
	
	printf("\n");
	printf("* unsigned long long\n");
	printType((unsigned long long)0xFFFFFFFFFFFFFFFF);
	printType((unsigned long long)0x0000000000000001 + (unsigned long long)0x0000000000000001);
	printType((unsigned long long)((unsigned long long)0x0000000000000001 + (unsigned long long)0x0000000000000001));
	
	printf("\n");
	printf("* float\n");
	printType(1.0f + 1.0f);
	printType(1.4e-45f * 0.0000001f);
	
	printf("\n");
	printf("* double\n");
	printType(1.4e-45 * 0.0000001);
	
	printf("\n");
	printf("* int vs float\n");
	printType(1 + 1.00f);
	printType(1.00f + 1);
	
	printf("\n");
	printf("* float vs double\n");
	printType(1.00 + 1.00f);
	printType(1.00f + 1.00);
	
	return 0;
}

/*
./Overloading 
* unsigned char
unsigned char[0xff], size=1
int[2], size=4
unsigned char[0x02], size=1

* signed short
signed short[0xffff], size=2
int[2], size=4
signed short[0x0002], size=2

* signed long
signed long[0xffffffff], size=4
signed long[0x00000002], size=4
signed long[0x00000002], size=4

* unsigned long long
unsigned long long[0xffffffffffffffff], size=8
unsigned long long[0x0000000000000002], size=8
unsigned long long[0x0000000000000002], size=8

* float
float[2.000000e+00], size=4
float[0.000000e+00], size=4

* double
double[1.400000e-52], size=8

* int vs float
float[2.000000e+00], size=4
float[2.000000e+00], size=4

* float vs double
double[2.000000e+00], size=8
double[2.000000e+00], size=8
*/