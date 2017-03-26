#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

class Stopwatch {
private:
	struct timespec ts_time_start;
	struct timespec ts_time_end;
	struct timespec ts_cpu_start;
	struct timespec ts_cpu_end;
	struct timespec ts_cpu_diff;
	struct timespec ts_time_diff;
	
	// timespec 構造体での差分を取得する
	void timespec_diff(timespec *start, timespec *end, timespec *diff) {
		if ((end->tv_nsec - start->tv_nsec) < 0) {
			diff->tv_sec  = end->tv_sec  - start->tv_sec  - 1;
			diff->tv_nsec = end->tv_nsec - start->tv_nsec + 1000000000;
		} else {
			diff->tv_sec  = end->tv_sec  - start->tv_sec;
			diff->tv_nsec = end->tv_nsec - start->tv_nsec;
		}
	}
	
	// timespec 構造体での差分をミリ秒で取得する
	double getDiffMSEC(timespec *start, timespec *end) {
		struct timespec ts_diff;
		timespec_diff(start, end, &ts_diff);
		return (double)ts_diff.tv_nsec / 1000000.0 + (double)ts_diff.tv_sec * 1000.0;
	}
	
public:
	void start(void) {
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_cpu_start);
		clock_gettime(CLOCK_MONOTONIC, &ts_time_start);
		return;
	}
	void stop(void) {
		clock_gettime(CLOCK_MONOTONIC, &ts_time_end);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_cpu_end);
		return;
	}
	void show(void) {
		double cpu_time = getDiffMSEC(&ts_cpu_start, &ts_cpu_end);
		double my_time  = getDiffMSEC(&ts_time_start, &ts_time_end);
		printf("実時間 %f ms\tCPU時間 %f ms\tCPU使用率 %1.1f %%\n",
			my_time,
			cpu_time,
			100.0 * cpu_time / my_time
		);
		return;
	}
	
};

int test(void) {
	Stopwatch sw;
	struct timespec tm = {0, 0};
	
	// 様々な sleep
	tm.tv_nsec=1;sw.start();nanosleep(&tm, NULL);sw.stop();sw.show();
	tm.tv_nsec=10;sw.start();nanosleep(&tm, NULL);sw.stop();sw.show();
	tm.tv_nsec=100;sw.start();nanosleep(&tm, NULL);sw.stop();sw.show();
	sw.start();usleep(1);sw.stop();sw.show();
	sw.start();usleep(10);sw.stop();sw.show();
	sw.start();usleep(100);sw.stop();sw.show();
	sw.start();usleep(1000);sw.stop();sw.show();
	sw.start();usleep(10000);sw.stop();sw.show();
	sw.start();usleep(100000);sw.stop();sw.show();
	sw.start();sleep(1);sw.stop();sw.show();
	
	/*
		おそらく細かい時間は、sleep自体を何回か連続で呼び出して、
		平均を出さないと時間の性能自体が正しく測れないと思われます。
		まあ参考程度な感じで見てください。
		「Raspberry Pi 2」で「Raspbian OS」で動作した場合です。
		
		pi@raspberrypi: $ ./Sleep
		実時間 0.152499 ms      CPU時間 0.103489 ms     CPU使用率 67.9 %
		実時間 0.079531 ms      CPU時間 0.025207 ms     CPU使用率 31.7 %
		実時間 0.075208 ms      CPU時間 0.023646 ms     CPU使用率 31.4 %
		実時間 0.084323 ms      CPU時間 0.032969 ms     CPU使用率 39.1 %
		実時間 0.081302 ms      CPU時間 0.022032 ms     CPU使用率 27.1 %
		実時間 0.170155 ms      CPU時間 0.022188 ms     CPU使用率 13.0 %
		実時間 1.070309 ms      CPU時間 0.022395 ms     CPU使用率 2.1 %
		実時間 10.071323 ms     CPU時間 0.022396 ms     CPU使用率 0.2 %
		実時間 100.096305 ms    CPU時間 0.040520 ms     CPU使用率 0.0 %
		実時間 1000.130244 ms   CPU時間 0.077188 ms     CPU使用率 0.0 %
	*/
	
	return 0;
}

int main(void){
	test();
	return 0;
}
