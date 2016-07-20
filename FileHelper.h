/**
 * @file FileHelper.h 文件常用处理函数整理
 *
 * 日期        作者        描述
 * 2016/07/20  gxl         create
 */
#pragma once

#include <string>

#include <windows.h>
#include <dbghelp.h> 

#pragma comment(lib, "version.lib")

/**
 * @brief 文件处理常用函数帮助类
 */
class CFileHelper
{
public:
	CFileHelper(){}
	~CFileHelper(){}

public:
	/**
	 * @brief 获取文件版本描述，输出示例：v1.0.0.1
	 *
	 * @param cFileName[in]  文件路径
	 *
	 * @return 版本描述字符
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     string cVersion = CFileHelper::GetFileVersionString("D:\\WorkSpace\\ZCMsgService\\Release\\ZCMsgService.exe");
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
					sprintf_s(szVer, 64, "v%d.%d.%d.%d", HIWORD(pVI->dwFileVersionMS), LOWORD(pVI->dwFileVersionMS),
						HIWORD(pVI->dwFileVersionLS), LOWORD(pVI->dwFileVersionLS));
					verString = szVer;
				}
			}
			delete[] pBuffer;
		}

		return verString;
	}

	/**
	 * @brief 获取当前应用程序版本描述，输出示例：v1.0.0.1
	 *
	 * @return 版本描述字符
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     string cVersion = CFileHelper::GetCurrentFileVersionString();
	     cout << cVersion << endl;

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static string GetCurrentFileVersionString()
	{
		char fileName[MAX_PATH] = { 0 };
		GetModuleFileNameA(NULL, fileName, sizeof(fileName));

		return GetFileVersionString(fileName);
	}
};