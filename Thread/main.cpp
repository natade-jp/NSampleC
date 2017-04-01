#include <stdio.h>

// usleep
#include <unistd.h>

// thread
#include <pthread.h>

#define MYLOG printf("%s:%d\n", __FILE__, __LINE__);

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
	
	void vMainLoop() {
		while(true) {
			// 起こされるまで待つ
			// pthread_cond_timedwait を使用する場合は、第3引数は絶対時刻なので注意
			// pthread_cond_wait は pthread_testcancel 代わりにもなる
			pthread_cond_wait(&kCond, &kCondMutex);
			printf("run\n");
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
	int wake() {
		if(pthread_mutex_lock(&kMyMutex) != 0) {
			perror("pthread_mutex_lock()");
			return -1;
		}
		
		if(isRun == true) {
			// スレッドを起こす
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
		thread.run();
		printf("ok1\n");
		thread.wake();
		sleep(1);
		thread.stop();
		printf("ok2\n");
	}
	
	return 0;
}

