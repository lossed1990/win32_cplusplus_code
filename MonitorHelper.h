/**
 * @file MonitorHelper.h 显示器操作帮助类
 *
 * 日期        作者        描述
 * 2016/08/03  gxl         create 
 */
#ifndef G_MONITORHELPER_H_
#define G_MONITORHELPER_H_

#include <vector>

typedef struct {
	HMONITOR hMonitor;  ///< 显示器句柄
	HDC hdcMonitor;     ///< 显示器DC句柄
	RECT rcMonitor;     ///< 显示器坐标范围
} G_Monitor_Info, *LPG_Monitor_Info;

/**
 * @brief 显示器操作帮助类
 *
 * @note 1、单例类，便于全局使用；
 * @note 2、构造时枚举所有显示器，方便操作；
 */
class MonitorHelper
{
private:
	static MonitorHelper* m_pMonitorInst;
	MonitorHelper(void)
	{
		//读取硬件显示器个数
		int nCount = ::GetSystemMetrics(SM_CMONITORS);

		//枚举显示器，获取位置
		::EnumDisplayMonitors(NULL, NULL, EnumMonitorCallBack, (LPARAM)this);

		//等待枚举完成
		while (1) 
		{
			if (m_vecMonitorInfo.size() >= nCount)
			{
				break;
			}

			Sleep(10);
		}
	}

public:
	/**
	 * @brief 获取全局唯一操作对象
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     MonitorHelper* pMonitorHelper = MonitorHelper::Instance();

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static MonitorHelper* Instance(){ return (m_pMonitorInst == NULL ? m_pMonitorInst = new MonitorHelper() : m_pMonitorInst); }

	/**
	 * @brief 释放资源
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     MonitorHelper::FreeInstance();

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void FreeInstance()
	{
		if (m_pMonitorInst)
		{
			delete m_pMonitorInst;
			m_pMonitorInst = NULL;
		}
	}

public:
	/**
	 * @brief 获取系统显示器个数
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     MonitorHelper::Instance()->GetMonitorCount();

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	int GetMonitorCount()
	{
		return m_vecMonitorInfo.size();  //也可以通过::GetSystemMetrics(SM_CMONITORS)系统函数获取
	}

public:
	static BOOL CALLBACK EnumMonitorCallBack(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
	{
		MonitorHelper* pUnit = (MonitorHelper*)dwData;

		G_Monitor_Info newInfo = { 0 };
		newInfo.hdcMonitor = hdcMonitor;
		newInfo.hMonitor = hMonitor;
		memcpy_s(&newInfo.rcMonitor, sizeof(RECT), lprcMonitor, sizeof(RECT));
		pUnit->m_vecMonitorInfo.push_back(newInfo);
		return TRUE;
	}

public:
	vector<G_Monitor_Info> m_vecMonitorInfo;  ///< 系统显示器详细信息
};

MonitorHelper* MonitorHelper::m_pMonitorInst = NULL;

#endif // G_MONITORHELPER_H_ 