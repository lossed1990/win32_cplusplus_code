/**
 * @file FileHelper.h 文件常用处理函数整理
 *
 * 日期        作者        描述
 * 2016/07/20  gxl         create
 */
#ifndef G_FILEHELPER_H_
#define G_FILEHELPER_H_

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
		int size = GetFileVersionInfoSize(cFileName, &dwHandle);
		if (size > 0)
		{
			byte *pBuffer = new byte[size];
			if (GetFileVersionInfo(cFileName, dwHandle, size, pBuffer))
			{
				VS_FIXEDFILEINFO *pVI = NULL;
				if (VerQueryValue(pBuffer, "\\", (LPVOID*)&pVI, (PUINT)&size))
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
		GetModuleFileName(NULL, fileName, sizeof(fileName));

		return GetFileVersionString(fileName);
	}

	/**
	 * @brief 获取当前应用程序路径
	 *
	 * @return 路径字符串
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     string cPath = CFileHelper::GetCurrentFilePath();
	     cout << cPath << endl;

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static string GetCurrentFilePath()
	{
		char exeFullPath[MAX_PATH] = {0};
		GetModuleFileName(NULL, exeFullPath, MAX_PATH);

		char *p = strrchr(exeFullPath, '\\');
		if (p)
		{
			*p = '\0';
		}
		string strPath = exeFullPath;
		return strPath;
	}	

	/**
	 * @brief 获取当前应用程序上层目录
	 *
	 * @param nDeep[in] 上级层数 0-文件路径（包含文件名称） 1-当前目录 2-上层目录 3-上层目录的上层目录 超范围时返回磁盘根目录
	 *
	 * @return 路径字符串
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     string cPath = CFileHelper::GetCurrentFileParentPath(1);
	     cout << cPath << endl;

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static string GetCurrentFileParentPath(int nDeep)
	{
		char exeFullPath[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, exeFullPath, MAX_PATH);

		for (int deep = 0; deep < nDeep; ++deep)
		{
			char *p = strrchr(exeFullPath, '\\');
			if (p)
			{
				*p = '\0';
			}
		}

		string strPath = exeFullPath;
		return strPath;
	}
};

#endif // G_FILEHELPER_H_