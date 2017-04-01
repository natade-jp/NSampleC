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
		// malloc ÇÕèâä˙âªÇ≥ÇÍÇƒÇ¢Ç»Ç¢
		
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
		// calloc ÇÕèâä˙âªÇ≥ÇÍÇƒÇ¢ÇÈ
		
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
		// alloca ä÷êîÇ©ÇÁî≤ÇØÇÈÇ∆Ç´Ç…é©ìÆÇ≈âï˙Ç≥ÇÍÇÈ
		
		int *piData = NULL;
		piData = (int *)alloca(iSize); // NULLÇ≈ñﬂÇÈÇ±Ç∆ÇÕÇ»Ç¢
		
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

