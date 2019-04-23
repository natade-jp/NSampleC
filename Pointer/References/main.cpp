#include <stdio.h>

// アドレス渡し
void test1(int *x) {
	printf("pointer\n");
	printf("address[%p]\n", x);
	printf("entity[%d]\n", *x);
	*x = 300;
}

// 参照渡し
void test2(int &x) {
	printf("pointer\n");
	printf("address[%p]\n", &x);
	printf("entity[%d]\n", x);
	x = 500;
}

int main(void){
	int a = 100;
	
	test1(&a);
	printf("return[%d]\n", a);
	
	test2(a);
	printf("return[%d]\n", a);
	
	return 0;
}

/**
[root@centos-rpi3 References]# ./References
pointer
address[0x7ea6566c]
entity[100]
return[300]
pointer
address[0x7ea6566c]
entity[300]
return[500]
[root@centos-rpi3 References]#
*/
