#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// stat
#include <sys/stat.h>

class PathData {
private:
	// ファイルパス
	char strPath[520];
public:
	// 構造体宣言時に初期化する
	PathData(void) {
		memset(strPath, '\0', sizeof(strPath));
	}
	// イコールはコピーと同等とする
	PathData& operator=(const char *strData) {
		strncpy(strPath, strData, sizeof(strPath));
		return *this;
	}
	// charへのキャストが可能とする
	operator char*() {
		return strPath;
	}
} ;

class FileOperation {
private:
	PathData cPath;
	FILE *fp;
	bool isOpen;
public:
	FileOperation(const char* strTarget) {
		cPath	= strTarget;
		fp		= NULL;
		isOpen	= false;
		return;
	}
	~FileOperation(void) {
		return;
	}
	bool isExist(void) {
		struct stat kStat;
		if(stat((char *)cPath, &kStat) != 0) {
			return false;
		}
		return true;
	}
	bool isFile(void) {
		struct stat kStat;
		if(stat((char *)cPath, &kStat) != 0) {
			return false;
		}
		if(S_ISREG(kStat.st_mode)) {
			return true;
		}
		return false;
	}
	bool isDirectory(void) {
		struct stat kStat;
		if(stat((char *)cPath, &kStat) != 0) {
			return false;
		}
		if(S_ISDIR(kStat.st_mode)) {
			return true;
		}
		return false;
	}
	unsigned int getSize(void) {
		struct stat kStat;
		if(stat((char *)cPath, &kStat) != 0) {
			return false;
		}
		return kStat.st_size;
	}
	
	
	operator char*() {
		return cPath;
	}
};

int main(){
	FileOperation *fileop = new FileOperation("File");
	printf("%s\n", (char *)fileop );
	printf("isExist %d\n",		fileop->isExist() );
	printf("isFile %d\n",		fileop->isFile() );
	printf("isDirectory %d\n",	fileop->isDirectory() );
	printf("getSize %d\n",		fileop->getSize() );
	delete fileop;
	return 0;
}
