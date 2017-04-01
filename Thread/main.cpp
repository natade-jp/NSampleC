#include <stdio.h>

// sleep
#include <unistd.h>

// queue
#include <queue>

// thread
#include <pthread.h>

#define MYLOG printf("%s:%d\n", __FILE__, __LINE__);

using namespace std;

// thread sample code
// https://github.com/natade-jp/NSampleC
// パブリックドメイン

class Thread {
private:
	bool				isRun;
	pthread_t			kThread;
	pthread_mutex_t		kMyMutex;
	pthread_mutex_t		kCondMutex;
	pthread_cond_t		kCond;
	queue<int>			kQueue;
	
	void vMainLoop() {
		while(true) {
			// wait 起こされるまで待つ
			// pthread_cond_timedwait を使用する場合は、第3引数は絶対時刻なので注意
			// pthread_cond_wait は pthread_testcancel 代わりにもなる
			pthread_cond_wait(&kCond, &kCondMutex);
			
			while(!kQueue.empty()) {
				// 取り出して
				int iNumber = kQueue.front();
				// 取り出し終わったので削除
				kQueue.pop();
				// 処理開始
				printf("run[%d]\n", iNumber);
			}
		}
	}
	
	static void* vStartThread(void *pParam) {
		// pthread_create の第4引数を使用して、パラメータでクラスを渡す。
		// クラスが分かるため、内部のメインループを呼び出せる
		reinterpret_cast<Thread*>(pParam)->vMainLoop();
		return NULL;
	}
	
	int iMakeThread(void) {
		int iRet = 0;
		// スレッドを作成する
		// 第3引数は、staticを渡す必要がある
		iRet = pthread_create(&kThread, NULL, vStartThread, this);
		if(iRet != 0) {
			perror("pthread_create()");
			return -1;
		}
		return 0;
	}
	
public:
	Thread() {
		isRun	= false;
		pthread_mutex_init(&kMyMutex, NULL);
		pthread_mutex_init(&kCondMutex, NULL);
		pthread_cond_init(&kCond, NULL);
		return;
	}
	virtual ~Thread() {
		stop();
		pthread_mutex_destroy(&kMyMutex);
		pthread_mutex_destroy(&kCondMutex);
		pthread_cond_destroy(&kCond);
		return;
	}
	int run() {
		int iRet = 0;
		
		if(pthread_mutex_lock(&kMyMutex) != 0) {
			perror("pthread_mutex_lock()");
			return -1;
		}
		
		// 動作していなかったら開始する
		if(isRun == false) {
			iRet = iMakeThread();
			if(iRet == 0) {
				isRun	= true;
			}
		}
		
		if(pthread_mutex_unlock(&kMyMutex) != 0) {
			perror("pthread_mutex_unlock()");
			return -1;
		}
		
		return iRet;
	}
	int stop() {
		if(pthread_mutex_lock(&kMyMutex) != 0) {
			perror("pthread_mutex_lock()");
			return -1;
		}
		
		if(isRun == true) {
			// キャンセル要求を送信
			pthread_cancel(kThread);
			// スレッドを起こす
			pthread_cond_signal(&kCond);
			// スレッドが終了するまで待つ
			pthread_join(kThread, NULL);
			isRun = false;
		}
		
		if(pthread_mutex_unlock(&kMyMutex) != 0) {
			perror("pthread_mutex_unlock()");
			return -1;
		}
		return 0;
	}
	int job(int iNumber) {
		if(!isRun) {
			return -1;
		}
		
		if(pthread_mutex_lock(&kMyMutex) != 0) {
			perror("pthread_mutex_lock()");
			return -1;
		}
		
		if(isRun == true) {
			// 仕事を積む
			kQueue.push(iNumber);
			
			// wake / notify スレッドを起こす
			pthread_cond_signal(&kCond);
		}
		
		if(pthread_mutex_unlock(&kMyMutex) != 0) {
			perror("pthread_mutex_unlock()");
			return -1;
		}
		
		return 0;
	}
	
};


int main(void){
	
	{
		Thread thread;
		
		// スレッド開始
		printf("start thread\n");
		thread.run();
		{
			printf("仕事の支持を開始\n");
			// この100の処理はスレッドが処理をする
			thread.job(100);
			thread.job(200);
			thread.job(300);
			thread.job(400);
			printf("仕事の指示を終了\n");
		}
		usleep(1000*100);
		
		printf("stop thread\n");
		thread.stop();
	}
	
	return 0;
}

