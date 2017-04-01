#include <stdio.h>
#include <syslog.h>

int main(void){
	
	// LOG_ERR / LOG_WARNING / LOG_INFO / LOG_DEBUG
	syslog(LOG_DEBUG,"logtest debug 1");
	
	// プログラム名も指定できる
	openlog("MyProcess", LOG_PID, LOG_USER);
	syslog(LOG_DEBUG,"logtest debug 2");
	closelog(); // closelog は必須ではない
	
	// NULL の場合はプログラム名が設定される
	openlog(NULL, LOG_PID, LOG_USER);
	syslog(LOG_DEBUG,"logtest debug 3");
	closelog(); // closelog は必須ではない
	
	
	// syslog の設定ファイルの場所は、次のうちのどちらか
	// /etc/syslog.conf, /etc/rsyslog.conf
	
	// レベルによって書き込まれる場所を変えたりもできる
	// 設定ファイルは 
	// /var/log/debug
	
	return 0;
}

/*

Apr  1 12:25:59 raspberrypi SyslogC: logtest debug 1
Apr  1 12:25:59 raspberrypi MyProcess[12354]: logtest debug 2
Apr  1 12:25:59 raspberrypi SyslogC[12354]: logtest debug 3

*/
