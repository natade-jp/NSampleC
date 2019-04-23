#include <stdlib.h>
#include <string.h>

// errno
#include  <errno.h>

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
		strncpy(strPath, strData, sizeof(strPath) - 1);
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
	int fwriteFile(const void *vTarget, int iByteSize, unsigned int uiOffset) {
		FILE *fp		= NULL;
		int iWriteSize	= 0;
		int iRet		= 0;
		
		// ファイルを開く
		if(isExist()) {
			// 既に存在していれば、「ストリームはファイルの先頭」で開く
			fp = fopen((char *)cPath, "r+" );
		}
		else {
			// ファイルを作成して、「ストリームはファイルの先頭」で開く
			fp = fopen((char *)cPath, "w" );
		}
		if(fp == NULL) {
			printf("ERROR(%d) %s\n", errno, strerror(errno));
			return -1;
		}
		
		// 先頭からシークさせる。
		iRet = fseek(fp, uiOffset, SEEK_SET);
		if(iRet == -1) {
			printf("ERROR(%d) %s\n", errno, strerror(errno));
			fclose(fp);
			return -1;
		}
		
		// ファイルを書き込む
		iWriteSize = fwrite(vTarget, 1, iByteSize, fp); 
		
		fclose(fp);
		return iWriteSize;
	}
	int freadFile(void *vTarget, int iByteSize, unsigned int uiOffset) {
		FILE *fp		= NULL;
		int iReadSize	= 0;
		int iRet		= 0;
		
		// ファイルを開く
		fp = fopen((char *)cPath, "r" );
		if(fp == NULL) {
			printf("ERROR(%d) %s\n", errno, strerror(errno));
			return -1;
		}
		
		// 先頭からシークさせる。
		iRet = fseek(fp, uiOffset, SEEK_SET);
		if(iRet == -1) {
			printf("ERROR(%d) %s\n", errno, strerror(errno));
			fclose(fp);
			return -1;
		}
		
		// ファイルを読み込む
		iReadSize = fread(vTarget, 1, iByteSize, fp); 
		
		fclose(fp);
		return iReadSize;
	}
	int writeFile(const void *vTarget, int iByteSize, unsigned int uiOffset) {
		int fd			= 0;
		int iWriteSize	= 0;
		int iRet		= 0;
		
		// 書き込みモードでファイルを開く
		// (ファイルが存在しなかった場合は作成し、権限を 0700 とする。
		fd = open((char *)cPath, O_WRONLY | O_CREAT, S_IRWXU );
		if(fd == -1) {
			printf("ERROR(%d) %s\n", errno, strerror(errno));
			return -1;
		}
		
		// 先頭からシークさせる。
		iRet = lseek(fd, uiOffset, SEEK_SET);
		if(iRet == -1) {
			printf("ERROR(%d) %s\n", errno, strerror(errno));
			close(fd);
			return -1;
		}
		
		// ファイルを書き込む
		iWriteSize = write(fd, vTarget, iByteSize); 
		
		close(fd);
		return iWriteSize;
	}
	int readFile(void *vTarget, int iByteSize, unsigned int uiOffset) {
		int fd			= 0;
		int iReadSize	= 0;
		int iRet		= 0;
		
		// 読み込みモードでファイルを開く
		fd = open((char *)cPath, O_RDONLY );
		if(fd == -1) {
			printf("ERROR(%d) %s\n", errno, strerror(errno));
			return -1;
		}
		
		// 先頭からシークさせる。
		iRet = lseek(fd, uiOffset, SEEK_SET);
		if(iRet == -1) {
			printf("ERROR(%d) %s\n", errno, strerror(errno));
			close(fd);
			return -1;
		}
		
		// ファイルを読み込む
		iReadSize = read(fd, vTarget, iByteSize); 
		
		close(fd);
		return iReadSize;
	}
	
	
	int deleteFile(void) {
		return unlink((char *)cPath);
	}
	operator char*() {
		return cPath;
	}
};

int main(){
	// directory
	{
		FileOperation fileop("TestDirectory");
		printf("%s\n", (char *)fileop );
		fileop.makeDirectory();
		printf("isExist %d\n",		fileop.isExist() );
		printf("isFile %d\n",		fileop.isFile() );
		printf("isDirectory %d\n",	fileop.isDirectory() );
		fileop.deleteDirectory();
		printf("isExist %d\n",		fileop.isExist() );
	}
	// fopen / fread
	{
		char strWrite[512] = { '\0' };
		char strRead[512] = { '\0' };
		FileOperation fileop("test.txt");
		snprintf(strWrite, sizeof(strWrite) - 1, "ABCDEFG");
		fileop.fwriteFile(strWrite, strlen(strWrite), 1);
		printf("fwrite %s\n",		strWrite );
		fileop.freadFile(strRead, 5, 1);
		printf("fread %s\n",		strRead );
		fileop.deleteFile();
	}
	// open / read
	{
		char strWrite[512] = { '\0' };
		char strRead[512] = { '\0' };
		FileOperation fileop("test.txt");
		snprintf(strWrite, sizeof(strWrite) - 1, "ABCDEFG");
		fileop.writeFile(strWrite, strlen(strWrite), 1);
		printf("write %s\n",		strWrite );
		fileop.readFile(strRead, 5, 1);
		printf("read %s\n",			strRead );
		fileop.deleteFile();
	}
	return 0;
}

/*
# ./File
TestDirectory
isExist 1
isFile 0
isDirectory 1
isExist 0
fwrite ABCDEFG
fread ABCDE
write ABCDEFG
read ABCDE
*/
