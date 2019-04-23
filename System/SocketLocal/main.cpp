#include <stdio.h>

// select
#include <sys/select.h>

// memset
#include <string.h>

// getopt / unlink
#include <unistd.h>

// socket
#include <sys/types.h>
#include <sys/socket.h>

// sockaddr_un
#include <sys/un.h>

// fcntl
#include <fcntl.h>

// timer
#include <sys/timerfd.h>
#include <sys/time.h>

// uint64_t
#include <stdint.h>

// 別のプロセスへファイルディスクリプタを使用して通信する
#define SOCKNAME "/tmp/local_socket_test"

int makeServerSocketFd( int *piServerSocketFD, int *piClientSocketFD) {
	int iServerSocketFd = 0;
	int iClientSocketFd = 0;
	struct sockaddr_un kSocketAddress;
	
	// ソケットを作成する
	// AF_LOCAL			... ローカル通信
	// SOCK_STREAM		... バイトストリーム
	iServerSocketFd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if(iServerSocketFd == -1) {
		perror("socket");
		return -1;
	}
	
	// ソケットの設定
	// O_RDWR		読み書き
	// O_CLOEXEC	close-on-exec
	{
		int iFcntl = 0;
		iFcntl = fcntl(iServerSocketFd, F_GETFL);
		if (iFcntl == -1) {
			perror("fcntl");
			close(iServerSocketFd);
			return -1;
		}
		if (fcntl(iServerSocketFd, F_SETFL, iFcntl | O_RDWR | O_CLOEXEC) == -1) {
			perror("fcntl");
			close(iServerSocketFd);
			return -1;
		}
	}
	
	// ソケットにアドレスを割り当てる（connect できるようになる）
	unlink( SOCKNAME );
	memset( &kSocketAddress, 0, sizeof(kSocketAddress) );
	kSocketAddress.sun_family = AF_LOCAL;
	strcpy(kSocketAddress.sun_path, SOCKNAME);
	if(bind(iServerSocketFd, (struct sockaddr *)&kSocketAddress, sizeof(kSocketAddress)) == -1) {
		perror("bind");
		close(iServerSocketFd);
		return -1;
	}
	
	// 接続要求の受け付け準備(1箇所からのみ)
	if(listen(iServerSocketFd, 1) == -1) {
		perror("listen");
		close(iServerSocketFd);
		return -1;
	}
	
	// 受付可能(ここで connect がくるまで止まります)
	iClientSocketFd = accept( iServerSocketFd, NULL, NULL ) ;
	if(iClientSocketFd == -1) {
		perror("accept");
		close(iServerSocketFd);
		return -1;
	}
	
	// 代入
	*piServerSocketFD = iServerSocketFd;
	*piClientSocketFD = iClientSocketFd;
	
	return 0;
}

int makeClientSocketFd(int *piClientSocketFD) {
	int iClientSocketFd = 0;
	struct sockaddr_un kSocketAddress;
	
	// ソケットを作成する
	// AF_LOCAL			... ローカル通信
	// SOCK_STREAM		... バイトストリーム
	iClientSocketFd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if(iClientSocketFd == -1) {
		perror("socket");
		return -1;
	}
	
	// ソケットの設定
	// O_RDWR		読み書き
	// O_CLOEXEC	close-on-exec
	{
		int iFcntl = 0;
		iFcntl = fcntl(iClientSocketFd, F_GETFL);
		if (iFcntl == -1) {
			perror("fcntl");
			close(iClientSocketFd);
			return -1;
		}
		if (fcntl(iClientSocketFd, F_SETFL, iFcntl | O_RDWR | O_CLOEXEC) == -1) {
			perror("fcntl");
			close(iClientSocketFd);
			return -1;
		}
	}
	
	// ソケットにアドレスを割り当てる（connect できるようになる）
	memset( &kSocketAddress, 0, sizeof(kSocketAddress) );
	kSocketAddress.sun_family = AF_LOCAL;
	strcpy(kSocketAddress.sun_path, SOCKNAME);
	if(connect(iClientSocketFd, (struct sockaddr *)&kSocketAddress, sizeof(kSocketAddress)) == -1) {
		perror("connect");
		close(iClientSocketFd);
		return -1;
	}
	
	*piClientSocketFD = iClientSocketFd;
	
	return 0;
}

int makeTimerFd(void) {
	int iTimerFd = 0;
	struct itimerspec kItimerspec;
	
	// インターバルタイマー（定周期タイマー）を作成する
	memset( &kItimerspec, 0, sizeof(kItimerspec) );
	// 1回目用とインターバル用の両方を設定する
	kItimerspec.it_value.tv_sec = 1;		// 1秒周期
	kItimerspec.it_interval.tv_sec = 1;		// 1秒周期
	
	iTimerFd = timerfd_create( CLOCK_MONOTONIC, 0 );
	if(iTimerFd == -1) {
		perror("timerfd_create");
		return -1;
	}
	
	// flags = 0 により相対タイマーとする
	if(timerfd_settime( iTimerFd, 0, &kItimerspec, NULL ) == -1) {
		perror("timerfd_settime");
		close(iTimerFd);
		return -1;
	}
	
	return iTimerFd;
}

char strMyName[512] = {'\0'};
bool iIsServer = false;
bool iIsCrient = false;

int actMainLoop(void) {
	fd_set rfds;
	int nfds			= 0;
	int iSelectRet		= 0;
	struct timeval kTimeOut;
	int iTimerFd		= -1;
	int iClientSocketFd	= -1;
	int iServerSocketFd	= -1;
	int iMyTime		= 0;
	
	iTimerFd = makeTimerFd();
	
	if(iIsServer) {
		makeServerSocketFd(&iServerSocketFd, &iClientSocketFd);
	}
	
	while(true) {
		iMyTime ++;
		
		// 初期化
		FD_ZERO(&rfds);
		nfds = 0;
		
		// 監視するFDを追加していく
		if(iTimerFd != -1) {
			FD_SET(iTimerFd, &rfds);
			nfds = (nfds < iTimerFd) ? iTimerFd : nfds;
		}
		if(iClientSocketFd != -1) {
			FD_SET(iClientSocketFd, &rfds);
			nfds = (nfds < iClientSocketFd) ? iClientSocketFd : nfds;
		}
		
		// タイムアウト値を設定
		kTimeOut.tv_sec  = 10;
		kTimeOut.tv_usec = 0;
		iSelectRet = select(nfds + 1, &rfds, NULL, NULL, &kTimeOut);
		
		// エラー／タイムアウトチェック
		if(iSelectRet == -1) {
			perror("select");
			break;
		}
		else if(iSelectRet == 0) {
			// timeout
			printf("select timeout\n");
			continue;
		}
		
		// 1秒インターバルタイマー
		if(FD_ISSET(iTimerFd, &rfds)) {
			uint64_t read_cnt;
			if(read( iTimerFd, &read_cnt, sizeof( read_cnt )) == -1) {
				perror("read");
				break;
			}
			printf("[%s] timer [%d]\n", strMyName, iMyTime );
			
			// 1秒ごとにしたい処理をここに書く
			
			// 接続済みならデータを送ってみる
			if((iClientSocketFd != -1)) {
				char strData[512]	= { '\0' };
				int iSize			= 0;
				snprintf(strData, sizeof(strData), "Hello! I'm %s. My count is %d.", strMyName, iMyTime);
				iSize = strlen( strData );
				if(iIsServer && (iMyTime % 2 == 0)) {
					if(write( iClientSocketFd, strData, strlen( strData ) ) == -1) {
						perror("write");
						break;
					}
					printf("[%s] socket send [%s][%d]\n", strMyName, strData, iSize );
				}
				if(iIsCrient && (iMyTime % 2 == 1)) {
					if(write( iClientSocketFd, strData, iSize ) == -1) {
						perror("write");
						break;
					}
					printf("[%s] socket send [%s][%d]\n", strMyName, strData, iSize );
				}
			}
			
			// クライアントならソケットを接続しに行く
			if(iIsCrient && (iClientSocketFd == -1)) {
				makeClientSocketFd(&iClientSocketFd);
			}
		}
		
		// ソケット受信
		if(FD_ISSET(iClientSocketFd, &rfds)) {
			char strData[4096]	= { '\0' };
			int iSize			= 0;
			iSize = read( iClientSocketFd, strData, sizeof( strData ) - 1 );
			if(iSize == -1) {
				perror("read");
				break;
			}
			else if(iSize > 0) {
				printf("[%s] socket receive [%s][%d]\n", strMyName, strData, iSize );
			}
		}
	}
	
	if(iTimerFd != -1) {
		close(iTimerFd);
	}
	if(iClientSocketFd != -1) {
		close(iClientSocketFd);
	}
	if(iServerSocketFd != -1) {
		close(iServerSocketFd);
	}
	
	return 0;
}



int main(int argc, char* argv[]){
	
	{
		// getopt の戻り値は int型なので注意
		int iOption = 0;
		while(true) {
			iOption = getopt(argc, argv, "sc");
			if(iOption == -1) {
				break;
			}
			switch(iOption) {
			case 's':
				iIsServer = true;
				break;
			case 'c':
				iIsCrient = true;
				break;
			}
		}
	}
	
	if(iIsServer) {
		snprintf(strMyName, sizeof(strMyName), "Server");
	}
	else {
		snprintf(strMyName, sizeof(strMyName), "Client");
	}
	
	actMainLoop();
	
	return 0;
}

/*
# ./sh_StartTestProgram.sh
unlink: cannot unlink '/tmp/local_socket_test': No such file or directory
Enterキーを入力するとテストが始まります。
※テストが終わるまでCtrl+C 入力禁止

サーバーを起動させます
クライアントを起動させます
Enterキーを入力すると終了します。
[Client] timer [1]
[Server] timer [1]
[Server] timer [2]
[Client] timer [2]
[Server] socket send [Hello! I'm Server. My count is 2.][33]
[Client] socket receive [Hello! I'm Server. My count is 2.][33]
[Server] timer [3]
[Client] timer [4]
[Server] timer [4]
[Client] timer [5]
[Client] socket send [Hello! I'm Client. My count is 5.][33]
[Server] socket send [Hello! I'm Server. My count is 4.][33]
[Server] socket receive [Hello! I'm Client. My count is 5.][33]
[Client] socket receive [Hello! I'm Server. My count is 4.][33]
[Server] timer [6]
[Client] timer [7]
[Client] socket send [Hello! I'm Client. My count is 7.][33]
[Server] socket send [Hello! I'm Server. My count is 6.][33]
[Server] socket receive [Hello! I'm Client. My count is 7.][33]
[Client] socket receive [Hello! I'm Server. My count is 6.][33]
[Server] timer [8]
[Client] timer [9]
*/


