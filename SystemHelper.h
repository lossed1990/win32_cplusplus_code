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

	/**
	 * @brief 开机自运行本程序
	 *
	 * @param cProcessName[in] 程序名称
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     CSystemHelper::SetAutoStartup("demo");

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool SetAutoStartup(const char* cProcessName)
	{
		char filename[MAX_PATH];
		GetModuleFileName(NULL, filename, MAX_PATH);

		//判断环境是否为WOW64  
		BOOL isWOW64;
		REGSAM samDesired;
		IsWow64Process(GetCurrentProcess(), &isWOW64);
		samDesired = isWOW64 ? KEY_WRITE | KEY_WOW64_64KEY : KEY_WRITE;
		
		HKEY hKey;
		LONG lRet = RegCreateKeyEx(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, NULL, 0, samDesired, NULL, &hKey, NULL);
		if (lRet != ERROR_SUCCESS)
		{
            return false;
		}

		lRet = RegSetValueEx(hKey, cProcessName, 0, REG_SZ, (BYTE*)filename, MAX_PATH);
		if (lRet != ERROR_SUCCESS)
		{
			return false;
		}

		RegCloseKey(hKey);
		return true;
	}

	/**
	 * @brief 取消开机自运行本程序
	 *
	 * @param cProcessName[in] 程序名称
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     CSystemHelper::CancelAutoStartup("测试程序");

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool CancelAutoStartup(const char* cProcessName)
	{
		//判断环境是否为WOW64  
		BOOL isWOW64;
		REGSAM samDesired;
		IsWow64Process(GetCurrentProcess(), &isWOW64);
		samDesired = isWOW64 ? KEY_WRITE | KEY_WOW64_64KEY : KEY_WRITE;

		HKEY hKey;
		LONG lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, samDesired, &hKey);
		if (lRet == ERROR_SUCCESS)
		{
			RegDeleteValue(hKey, cProcessName);
			RegCloseKey(hKey);
			return true;
		}

		return false;
	}

	/**
	 * @brief 重新运行一个本程序实例
	 *
	 * 可在异常退出时，重启本程序时使用。
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     CSystemHelper::ReStartProcess();

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void ReStartProcess()
	{
		char szPath[MAX_PATH] = {0};
		GetModuleFileName(NULL, szPath, MAX_PATH);

		STARTUPINFO startupInfo;
		PROCESS_INFORMATION procInfo;
		memset(&startupInfo, 0x00, sizeof(STARTUPINFO));
		startupInfo.cb = sizeof(STARTUPINFO);
		::CreateProcess(szPath, NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &procInfo);
	}
};

#endif // G_SYSTEMHELPER_H_