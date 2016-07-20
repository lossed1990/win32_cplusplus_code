#pragma once

#include <string>

#include <windows.h>
#include <dbghelp.h> 
using namespace std;

#pragma comment(lib, "version.lib")

class CSystemHelper
{
public:
	CSystemHelper(){}
	~CSystemHelper(){}

public:
	/**
	 * @breif 判断当前程序是否已运行
	 *
	 * @param cMutexName[in]  互斥量名称
	 *
	 * @return true-已运行 false-未运行
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     bool bRunning = CSystemHelper::IsRunning("Single.test");
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
	static bool IsRunning(const char* cMutexName)
	{
		HANDLE hSingleton = CreateMutexA(NULL, FALSE, cMutexName);
		if ((hSingleton != NULL) && (GetLastError() == ERROR_ALREADY_EXISTS))
		{
			return true;
		}

		return false;
	}

	/**
	 * @breif 获取文件版本描述，输出示例：v1.0.0.1
     * 
     * @param cFileName[in]  文件路径
	 *
	 * @return 版本描述字符
     *
     * @code
       int main(int argc, char* argv[])
        {
		    string cVersion = CSystemHelper::GetFileVersionString("D:\\WorkSpace\\ZCMsgService\\Release\\ZCMsgService.exe");
		    cout << cVersion << endl;

            ::system("pause");
            return 0;
        }
     * @endcode
	 */
	static string GetFileVersionString(char* cFileName)
	{
		string verString("unknown");

		DWORD dwHandle;
		int size = GetFileVersionInfoSizeA(cFileName, &dwHandle);
		if (size > 0)
		{
			byte *pBuffer = new byte[size];
			if (GetFileVersionInfoA(cFileName, dwHandle, size, pBuffer))
			{
				VS_FIXEDFILEINFO *pVI = NULL;
				if (VerQueryValue(pBuffer, (LPCWSTR)"\\", (LPVOID*)&pVI, (PUINT)&size))
				{
					char szVer[64] = { 0 };
					sprintf_s(szVer,64, "v%d.%d.%d.%d", HIWORD(pVI->dwFileVersionMS), LOWORD(pVI->dwFileVersionMS),
						HIWORD(pVI->dwFileVersionLS), LOWORD(pVI->dwFileVersionLS));
					verString = szVer;
				}
			}
			delete[] pBuffer;
		}

		return verString;
	} 

	/**
	 * @breif 获取当前应用程序版本描述，输出示例：v1.0.0.1
	 *
	 * @return 版本描述字符
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     string cVersion = CSystemHelper::GetCurrentFileVersionString();
		 cout << cVersion << endl;

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static string GetCurrentFileVersionString()
	{
		char fileName[MAX_PATH] = {0};
		GetModuleFileNameA(NULL, fileName, sizeof(fileName));

		return GetFileVersionString(fileName);
	}
};