/**
 * @file DumpHelper.h dump文件创建帮助类
 *
 * 日期        作者        描述
 * 2016/07/20  gxl         create 
 */
#ifndef G_DUMPHELPER_H_
#define G_DUMPHELPER_H_

#ifdef _MSC_VER

#include <string>
using std::string;

#include <windows.h>
#include <tchar.h>
#pragma comment(lib, "dbghelp.lib")

#include <dbghelp.h>
#pragma comment(lib, "user32.lib")

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

typedef BOOL(WINAPI* PFNWRITEDUMP)(HANDLE, DWORD, HANDLE, MINIDUMP_TYPE, PMINIDUMP_EXCEPTION_INFORMATION,
	PMINIDUMP_USER_STREAM_INFORMATION, PMINIDUMP_CALLBACK_INFORMATION);

/**
 * @brief dump文件创建帮助类,用于程度异常时创建dump文件
 *
 * 使用方法：程序启动时，添加如下代码片段
 *
 * @code
 int main(int argc, char* argv[])
 {
     CDumpHelper dumper;
     dumper.SetHandler();

     ::system("pause");
     return 0;
 }
 * @endcode
 */
class CDumpHelper
{
public:
	CDumpHelper() { m_pDump = this; }

	void SetHandler() { ::SetUnhandledExceptionFilter(&CDumpHelper::TopLevelExceptionFilter); }

	static CDumpHelper* m_pDump;

private:
	CDumpHelper(const CDumpHelper&);
	const CDumpHelper& operator=(const CDumpHelper&);

public:
	static CDumpHelper* Get(){ return m_pDump; }

	string GetDumpFile() const
	{
		SYSTEMTIME st;
		::GetLocalTime(&st);
		char dt[11];
		wsprintfA(dt, "%02d%02d%02d%02d%02d", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

		char appPath[MAX_PATH];
		::GetModuleFileNameA(NULL, appPath, MAX_PATH);
		::PathRemoveFileSpecA(appPath);

		string file(appPath);
		file += "\\";
		file += dt;
		file += ".dmp";
		return file;
	}

private:
	static LONG WINAPI TopLevelExceptionFilter(struct _EXCEPTION_POINTERS* ep)
	{
		LONG ret = EXCEPTION_CONTINUE_SEARCH;

		HMODULE module = ::LoadLibraryA("dbghelp.dll");
		if (module == NULL)
		{
			return ret;
		}	

		PFNWRITEDUMP MiniDumpWriteDump = (PFNWRITEDUMP)::GetProcAddress(module, "MiniDumpWriteDump");
		if (MiniDumpWriteDump != NULL)
		{
			string dumpFile = CDumpHelper::Get()->GetDumpFile();
			HANDLE file = ::CreateFileA(dumpFile.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL, NULL);
			if (file == INVALID_HANDLE_VALUE)
			{
				return ret;
			}

			_MINIDUMP_EXCEPTION_INFORMATION mdei;
			mdei.ThreadId = ::GetCurrentThreadId();
			mdei.ExceptionPointers = ep;
			mdei.ClientPointers = NULL;

			if (MiniDumpWriteDump(::GetCurrentProcess(), ::GetCurrentProcessId(), file, MiniDumpNormal, &mdei, NULL, NULL))
			{
				ret = EXCEPTION_EXECUTE_HANDLER;
			}

			CloseHandle(file);
		}
		return ret;
	}
};

CDumpHelper* CDumpHelper::m_pDump = NULL;

#endif // _MSC_VER

#endif // G_DUMPHELPER_H_