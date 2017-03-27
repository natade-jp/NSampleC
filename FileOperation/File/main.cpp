#include <stdlib.h>
#include <string.h>

// open
#include <fcntl.h>

// remove
#include <stdio.h>

// rmdir / unlink
#include <unistd.h>

// stat / mkdir
#include <sys/stat.h>
#include <sys/types.h>

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
public:
	FileOperation(const char* strTarget) {
		cPath	= strTarget;
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
	int makeDirectory(void) {
		if(isExist()) {
			return -1;
		}
		{
			int ret = mkdir((char *)cPath, S_IRWXU | S_IRWXG);
			return ret;
		}
	}
	int deleteDirectory(void) {
		return rmdir((char *)cPath);
	}
	int writeFile(const void *vTarget, int iByteSize, unsigned int uiOffset) {
		int fd			= 0;
		int iWriteSize	= 0;
		int iRet		= 0;
		
		// ファイルを開く
		fd = open((char *)cPath, O_WRONLY | O_CREAT );
		if(fd == -1) {
			return -1;
		}
		
		// 先頭からシークさせる。
		iRet = lseek(fd, uiOffset, SEEK_SET);
		if(iRet == -1) {
			return -1;
		}
		
		// ファイルを書き込む
		iWriteSize = write(fd, vTarget, iByteSize); 
		
		close(fd);
		return iWriteSize;
	}
	
	int deleteFile(void) {
		return unlink((char *)cPath);
	}
	operator char*() {
		return cPath;
	}
};

int main(){
	{
		FileOperation fileop("TestDirectory");
		printf("%s\n", (char *)fileop );
		fileop.makeDirectory();
		sleep(1);
		printf("isExist %d\n",		fileop.isExist() );
		printf("isFile %d\n",		fileop.isFile() );
		printf("isDirectory %d\n",	fileop.isDirectory() );
		printf("getSize %d\n",		fileop.getSize() );
		fileop.deleteDirectory();
		sleep(1);
		printf("isExist %d\n",		fileop.isExist() );
	}
	{
		char strWrite[512] = { '\0' };
		char strRead[512] = { '\0' };
		FileOperation fileop("test.txt");
		
		snprintf(strWrite, sizeof(strWrite), "あいうえお");
				
		fileop.writeFile(strWrite, strlen(strWrite), 0);
		sleep(1);
	}
	return 0;
}
