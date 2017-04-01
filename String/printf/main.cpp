#include <stdio.h>

int main(void){
	
	// 切り分け
	printf("hello " "world!" "\n");
	
	// 順序の入れ替え
	printf("%2$s" "%1$s", "world!\n", "hello " );
	
	return 0;
}

