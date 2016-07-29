/**
 * @file TimeHelper.h 时间处理常用函数整理
 *
 * 日期        作者        描述
 * 2016/07/20  gxl		   create 
 */
#ifndef G_TIMEHELPER_H_
#define G_TIMEHELPER_H_

#include <time.h>

/**
 * @brief 程序运行计时帮助类
 * @code
 int main(int argc, char* argv[])
 {
     CTimeCounter newTimeCounter;
     Sleep(501);
     cout << "运行耗时:" << newTimeCounter.GetExecutionTime() << endl;

     ::system("pause");
     return 0;
 }
 * @endcode
 */
class CTimeCounter
{
public:
	CTimeCounter(void)
	{
		QueryPerformanceFrequency(&m_nFreq);
		QueryPerformanceCounter(&m_nBeginTime);
	}

	virtual ~CTimeCounter(void){}

	__int64 GetExecutionTime()
	{
		LARGE_INTEGER nEndTime;
		__int64 nCalcTime;

		QueryPerformanceCounter(&nEndTime);
		nCalcTime = (nEndTime.QuadPart - m_nBeginTime.QuadPart) *
			1000 / m_nFreq.QuadPart;

		return nCalcTime;
	}

protected:
	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER m_nBeginTime;
};

typedef struct {
	SYSTEMTIME s_BeginTime;
	SYSTEMTIME s_EndTime;
} G_TIMES, *LPG_TIMES;

/**
 * @brief 时间处理常用函数帮助类
 */
class CTimeHelper
{
public:
	CTimeHelper(){}
	~CTimeHelper(){}

public:
	/**
	 * @brief 获取昨日时间区间
	 * 
	 * 推算昨天的年月日，并返回00:00:00至23:59:59的时间区间（包含星期 0-周日 1-周一 以此类推）
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     G_TIMES sTimes;
	     CTimeHelper::Lastday(sTimes);
	  
	     char str[128] = {0};
	     sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
	                         sTimes.s_BeginTime.wYear,sTimes.s_BeginTime.wMonth,sTimes.s_BeginTime.wDay,
	                         sTimes.s_BeginTime.wHour,sTimes.s_BeginTime.wMinute,sTimes.s_BeginTime.wSecond,
	                         sTimes.s_BeginTime.wDayOfWeek,
                             sTimes.s_EndTime.wYear,sTimes.s_EndTime.wMonth,sTimes.s_EndTime.wDay,
                             sTimes.s_EndTime.wHour,sTimes.s_EndTime.wMinute,sTimes.s_EndTime.wSecond,
	                         sTimes.s_EndTime.wDayOfWeek
	     );

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void Lastday(G_TIMES &sTimes)
	{
		time_t time_now;
		time(&time_now);

		time_t time_lastday = time_now - 24 * 60 * 60;
		tm tm_LastDay;
		localtime_s(&tm_LastDay,&time_lastday);

		sTimes.s_BeginTime.wYear = tm_LastDay.tm_year + 1900;
		sTimes.s_BeginTime.wMonth = tm_LastDay.tm_mon + 1;
		sTimes.s_BeginTime.wDay = tm_LastDay.tm_mday;
		sTimes.s_BeginTime.wHour = 0;
		sTimes.s_BeginTime.wMinute = 0;
		sTimes.s_BeginTime.wSecond = 0;
		sTimes.s_BeginTime.wDayOfWeek = tm_LastDay.tm_wday;
		sTimes.s_BeginTime.wMilliseconds = 0;

		sTimes.s_EndTime.wYear = tm_LastDay.tm_year + 1900;
		sTimes.s_EndTime.wMonth = tm_LastDay.tm_mon + 1;
		sTimes.s_EndTime.wDay = tm_LastDay.tm_mday;
		sTimes.s_EndTime.wHour = 23;
		sTimes.s_EndTime.wMinute = 59;
		sTimes.s_EndTime.wSecond = 59;
		sTimes.s_EndTime.wDayOfWeek = tm_LastDay.tm_wday;
		sTimes.s_EndTime.wMilliseconds = 0;
	}
};

#endif // G_TIMEHELPER_H_