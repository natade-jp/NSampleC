#include <stdio.h>

// sleep
#include <unistd.h>

// queue / mutex / cond
#include <queue>
#include <mutex>
#include <condition_variable>

// thread
#include <thread>

#define MYLOG printf("%s:%d\n", __FILE__, __LINE__);

using namespace std;

// thread sample code
// https://github.com/natade-jp/NSampleC
// パブリックドメイン

class Thread {
private:
	bool				isRun;
	bool				isThreadLoop;
	thread				*pcThread = NULL;
	mutex 				cMyMutex;
	mutex				cCondMutex;
	condition_variable	cCond;
	queue<int>			cQueue;
	
	void vMainLoop() {
		isThreadLoop = true;
		unique_lock<mutex> lock(cCondMutex);
		while(isThreadLoop) {
			// wait 起こされるまで待つ(目覚めが遅い……)
			cCond.wait(lock);
			
			while(!cQueue.empty()) {
				// 取り出して
				int iNumber = cQueue.front();
				// 取り出し終わったので削除
				cQueue.pop();
				// 処理開始
				printf("run[%d]\n", iNumber);
			}
		}
	}
	
	static void* vStartThread(void *pParam) {
		// thread のコンストラクタの第2引数を使用して、パラメータでクラスを渡す。
		// クラスが分かるため、内部のメインループを呼び出せる
		reinterpret_cast<Thread*>(pParam)->vMainLoop();
		return NULL;
	}
	
	int iMakeThread(void) {
		// スレッドを作成する
		// 第1引数は、staticを渡す必要がある
		pcThread = new thread(vStartThread, this);
		return 0;
	}
	
public:
	Thread() {
		isRun			= false;
		isThreadLoop	= false;
		return;
	}
	virtual ~Thread() {
		stop();
		return;
	}
	int run() {
		int iRet = 0;
		
		cMyMutex.lock();
		
		// 動作していなかったら開始する
		if(isRun == false) {
			iRet = iMakeThread();
			if(iRet == 0) {
				isRun	= true;
			}
		}
		
		cMyMutex.unlock();
		
		return iRet;
	}
	int stop() {
		
		cMyMutex.lock();
		
		if(isRun == true) {
			// キャンセル要求を送信
			isThreadLoop = false;
			// スレッドを起こす
			cCond.notify_one();
			// スレッドが終了するまで待つ
			pcThread->join();
			delete pcThread;
			pcThread = NULL;
			isRun = false;
		}
		
		cMyMutex.unlock();
		
		return 0;
	}
	int job(int iNumber) {
		if(!isRun) {
			return -1;
		}
		
		cMyMutex.lock();
		
		if(isRun == true) {
			// 仕事を積む
			cQueue.push(iNumber);
			
			// wake / notify スレッドを起こす
			cCond.notify_one();
		}
		
		cMyMutex.unlock();
		
		return 0;
	}
	
};


int main(void){
	
	{
		Thread thread;
		
		printf("start thread\n");
		thread.run();
		{
			printf("仕事の指示を開始\n");
			thread.job(100);
			sleep(1);
			thread.job(200);
			sleep(1);
			thread.job(300);
			sleep(1);
			thread.job(400);
			sleep(1);
			printf("仕事の指示を終了\n");
		}
		usleep(1000*500);
		
		printf("stop thread\n");
		thread.stop();
	}
	
	return 0;
}

/*
# ./Thread
start thread
仕事の指示を開始
run[100]
run[200]
run[300]
run[400]
仕事の指示を終了
stop thread
*/
