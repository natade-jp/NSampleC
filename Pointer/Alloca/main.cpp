#include <stdio.h>

// malloc, calloc
#include <stdlib.h>

// Unix
#include <alloca.h>

int main(void){
	int i		= 0;
	int iLength	= 4;
	int iSize	= sizeof(int) * iLength;
	
	{
		// malloc は初期化されていない
		
		int *piData = NULL;
		piData = (int *)malloc(iSize);
		if(piData == NULL) {
			return 1;
		}
		
		printf("malloc\n");
		for(i = 0; i < iLength; i++) {
			printf("[%d][%d]\n", i, piData[i]);
		}
		
		free(piData);
	}
	
	{
		// calloc は初期化されている
		
		int *piData = NULL;
		piData = (int *)calloc(iSize, 1);
		if(piData == NULL) {
			return 1;
		}
		
		printf("calloc\n");
		for(i = 0; i < iLength; i++) {
			printf("[%d][%d]\n", i, piData[i]);
		}
		
		free(piData);
	}
	
	{
		// alloca 関数から抜けるときに自動で解放される
		
		int *piData = NULL;
		piData = (int *)alloca(iSize); // NULLで戻ることはない
		
		printf("alloca\n");
		for(i = 0; i < iLength; i++) {
			piData[i] = i * i;
		}
		for(i = 0; i < iLength; i++) {
			printf("[%d][%d]\n", i, piData[i]);
		}
	}
	
	return 0;
}

/*
# ./Alloca
malloc
[0][0]
[1][0]
[2][0]
[3][0]
calloc
[0][0]
[1][0]
[2][0]
[3][0]
alloca
[0][0]
[1][1]
[2][4]
[3][9]
*/
