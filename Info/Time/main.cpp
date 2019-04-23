#include <stdio.h>
#include <time.h>

int showDate(void) {
	time_t timer;
	struct tm *local = NULL;
	
	// 現在時刻を取得
	if(time(&timer) == (time_t)-1) {
		return 1;
	}
	
	// 内部に持っている変数のため free は不要
	local = localtime(&timer);
	
	{
		int iYear   = local->tm_year + 1900;
		int iMonth  = local->tm_mon  + 1;
		int iDay    = local->tm_mday;
		int iHour   = local->tm_hour;
		int iMinute = local->tm_min;
		int iSecond = local->tm_sec;
		
		printf("%04d/%02d/%02d %02d:%02d:%02d\n",
			iYear, iMonth, iDay, iHour, iMinute, iSecond );
	}
	
	return 0;
}

int main(void){
	showDate();
	return 0;
}

/*
# ./Time
2019/04/24 00:00:00
*/
