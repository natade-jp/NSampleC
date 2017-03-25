#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

class Stopwatch {
private:
	struct timespec ts1_time;
	struct timespec ts2_time;
	struct timespec ts1_cpu;
	struct timespec ts2_cpu;
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
		printf("計測スタート\n");
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts1_cpu);
		clock_gettime(CLOCK_MONOTONIC, &ts1_time);
		return;
	}
	void stop(void) {
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts2_cpu);
		clock_gettime(CLOCK_MONOTONIC, &ts2_time);
		printf("計測ストップ\n");
		return;
	}
	void show(void) {
		double cpu_time, my_time;
		cpu_time = getDiffMSEC(&ts1_cpu, &ts2_cpu);
		my_time  = getDiffMSEC(&ts1_time, &ts2_time);
		
		printf("実時間 %f.6 ms\nCPU時間 %f.6 ms\nCPU使用率 %1.1f %%\n",
			my_time,
			cpu_time,
			100.0 * cpu_time / my_time
		);
		
		return;
	}
	
};

int test(void) {
	Stopwatch sw;
	
	sw.start();
	usleep(1000 * 1000 * 1);
	sw.stop();
	
	sw.show();
	
	return 0;
}

int main(void){
	test();
	return 0;
}
