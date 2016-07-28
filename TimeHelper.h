/**
 * @file TimeHelper.h 时间处理常用函数整理
 *
 * 日期        作者        描述
 * 2016/07/20  gxl		   create 
 */
#ifndef G_TIMEHELPER_H_
#define G_TIMEHELPER_H_

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

/**
 * @brief 时间处理常用函数帮助类
 */
class CTimeHelper
{
public:
	CTimeHelper(){}
	~CTimeHelper(){}


};

#endif // G_TIMEHELPER_H_