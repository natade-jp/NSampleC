#include <stdio.h>

// Unix / Linux
#include <unistd.h>

int main(int argc, char* argv[]){
	
	{
		int i = 0;
		printf("実行ファイル名[%s]\n", argv[0]);
		printf("引数の合計[%d]\n", argc - 1);
		for(i = 1; i < argc; i++) {
			printf("引数[%d][%s]\n", i, argv[i]);
		}
	}
	
	{
		int i = 0;
		// getopt の戻り値は int型なので注意
		int iOption = 0;
		for(i = 0; i < 100; i++) {
			
			// :  引数の入力が可能となる。引数は必須
			// :: 引数の入力が可能となる。引数は任意
			iOption = getopt(argc, argv, "abcd:e::");
			if(iOption == -1) {
				break;
			}
			switch(iOption) {
			case 'a':
			case 'b':
			case 'c':
				printf("[%c]\n", iOption);
				break;
			case 'd':
			case 'e':
				printf("[%c][%s]\n", iOption, optarg);
				break;
			default:
				printf("[%c] ERROR\n", iOption);
				break;
			}
		}
	}
	
	return 0;
}

/*
	pi@raspberrypi:~/git/NSampleC/System/Getopt $ ./Getopt -ab -c -d "OK" -e -f
	実行ファイル名[./Getopt]
	引数の合計[6]
	引数[1][-ab]
	引数[2][-c]
	引数[3][-d]
	引数[4][OK]
	引数[5][-e]
	引数[6][-f]
	[a]
	[b]
	[c]
	[d][OK]
	[e][(null)]
	./Getopt: invalid option -- 'f'
	[?] ERROR
*/