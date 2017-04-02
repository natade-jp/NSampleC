#include <stdio.h>

// system
#include <stdlib.h>


int main(){
	int iStatus = 0;
	
	// 3秒待って、10を返すスクリプトを呼ぶ
	iStatus = system("./sh_Script.sh 3 10");
	
	// 終了ステータスの戻り値($?)は、WEXITSTATUSで取得が可能
	printf("[%d]\n", WEXITSTATUS(iStatus));
	
	return 0;
}

/*
./System
[10]
*/