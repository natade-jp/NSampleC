#include "stdio.h"
#include <signal.h>
#include <math.h>
#include <fenv.h>
#include <float.h>

int testcase1() {
	float x;
	x = powf(2.0f, 0.5f);
	printf("powf[%e]\n", x);
	x = FLT_MAX * 100000.0f;
	printf("powf[%e]\n", x);
	x = FLT_MIN * 0.00000001f;
	printf("powf[%e]\n", x);
	return 0;
}

int testcase2() {
	feenableexcept(FE_UNDERFLOW);
	float x = 1.0f;
//	x = powf(2.0f, 0.5f);
//	printf("powf[%e]\n", x);
//	x = FLT_MAX * 100000.0f;
//	printf("powf[%e]\n", x);
	x = FLT_MIN * 0.00000001f;
	printf("powf[%e]\n", x);
	fedisableexcept(FE_UNDERFLOW);
	return 0;
}


int main() {
	// Ç§Ç‹Ç≠Ç¢Ç©Ç»Ç¢ÅEÅEÅE
	/*
	feenableexcept(FE_ALL_EXCEPT);
	feenableexcept(FE_DIVBYZERO);
	feenableexcept(FE_INEXACT);
	feenableexcept(FE_INVALID);
	feenableexcept(FE_OVERFLOW);
	feenableexcept(FE_UNDERFLOW);
	*/
	testcase1();
	testcase2();
	return 0;
}

