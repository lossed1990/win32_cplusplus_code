/**
 * @file SystemHelper.h windows系统常用函数整理
 *
 * 日期        作者        描述
 * 2016/07/20  gxl		   create
 */
#ifndef G_SYSTEMHELPER_H_
#define G_SYSTEMHELPER_H_

#include <string>
#include <windows.h>
#include <Tlhelp32.h>

using namespace std;

/**
 * @brief windows系统常用函数帮助类
 */
class CSystemHelper
{
public:
	CSystemHelper(){}
	~CSystemHelper(){}

public:
	/**
	 * @brief 检查当前程序互斥量
	 *
	 * @param cMutexName[in]  互斥量名称
	 *
	 * @return true-已运行 false-未运行
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     bool bRunning = CSystemHelper::CheckProcessMutex("Single.test");
	     if (bRunning){
	         cout << "yes" << endl;
	     } else {
	         cout << "no" << endl;
	     }

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool CheckProcessMutex(const char* cMutexName)
	{
		HANDLE hSingleton = CreateMutexA(NULL, FALSE, cMutexName);
		if ((hSingleton != NULL) && (GetLastError() == ERROR_ALREADY_EXISTS))
		{
			return true;
		}

		return false;
	}	

	/**
	 * @brief 检查进程是否存在
	 *
	 * @param cProcessName[in] 进程名称
	 *
	 * @return true-存在 false-不存在
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     bool bExist = CSystemHelper::CheckProcessExist("demo.exe");
	     if (bExist){
	         cout << "yes" << endl;
	     } else {
	         cout << "no" << endl;
	     }

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool CheckProcessExist(const char* cProcessName)
	{
		bool bRet = false;

		HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			return bRet;
		}

		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);

		BOOL bMore = Process32First(hProcessSnap, &pe32);
		while (bMore)
		{
			if (strcmp(cProcessName, pe32.szExeFile) == 0 &&
				pe32.th32ProcessID != GetCurrentProcessId())
			{
				bRet = true;
			}
			bMore = ::Process32Next(hProcessSnap, &pe32);
		}
		CloseHandle(hProcessSnap);

		return bRet;
	}

	/**
	 * @brief 销毁进程
	 *
	 * @param cProcessName[in] 进程名称
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     CSystemHelper::DestoryProcess("demo.exe");
	     
	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void DestoryProcess(const char* cProcessName)
	{
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(pe32);
		HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			return;
		}

		BOOL bMore = ::Process32First(hProcessSnap, &pe32);
		while (bMore)
		{
			if (strcmp(cProcessName, pe32.szExeFile) == 0 &&
				pe32.th32ProcessID != GetCurrentProcessId())
			{
				HANDLE hHandle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
				if (hHandle)
				{
					::TerminateProcess(hHandle, 0);
					::CloseHandle(hHandle);
				}
			}
			bMore = ::Process32Next(hProcessSnap, &pe32);
		}
		CloseHandle(hProcessSnap);
	}
};

#endif // G_SYSTEMHELPER_H_