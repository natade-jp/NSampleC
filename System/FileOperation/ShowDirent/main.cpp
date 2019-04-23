#include <stdio.h>
#include <string.h>
#include <dirent.h>

// NAME_MAX を使用するために利用
#include <linux/limits.h>

// cout, string , vector, sort 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ファイルパスを格納する構造体
typedef struct pathdata {
	
	// ファイルパス
	char strPath[NAME_MAX];
	
	// 構造体宣言時に初期化する
	pathdata() {
		memset(strPath, '\0', NAME_MAX);
	}
	
	// sortを使用するため
	bool operator<( const pathdata right ) const {
		return strcmp(strPath, right.strPath) < 0;
	}
} PATHDATA;

class FileOperation {
private:
	PATHDATA kTarget;
public:
	FileOperation(const char* strTarget) {
		strncpy(kTarget.strPath, strTarget, NAME_MAX);
		return;
	}
	~FileOperation() {
		return;
	}
	int showDirectory() {
		DIR *dir = NULL;
		struct dirent *dent = NULL;
		vector<PATHDATA> cPathVector;
		vector<PATHDATA>::iterator itr;
		
		// フォルダを開く
		dir = opendir(kTarget.strPath);
		if (dir == NULL) {
			return 1;
		}
		
		// ファイルを取得
		while(true) {
			dent = readdir(dir);
			if(dent == NULL) {
				break;
			}
			
			// ディレクトリ
			if(dent->d_type == DT_DIR) {
				PATHDATA kPath;
				strncpy(kPath.strPath,  dent->d_name, NAME_MAX);
				cPathVector.push_back(kPath);
			}
		}
		
		// フォルダを閉じる
		closedir(dir);
		
		// 昇順ソートして表示
		sort(cPathVector.begin(), cPathVector.end());
		for(itr = cPathVector.begin(); itr != cPathVector.end(); itr++) {
			cout << "フォルダ " << itr->strPath << endl;
		}
		
		return 0;
	}
	
};

int main(){
	FileOperation *fileop = new FileOperation("./");
	fileop->showDirectory();
	delete fileop;
	return 0;
}

/*
# ./ShowDirent
フォルダ .
フォルダ ..
フォルダ 1
フォルダ 2
フォルダ 3
*/
