/**
 * @file SystemHelper.h windows系统常用函数整理
 *
 * 日期        作者        描述
 * 2016/07/20  gxl		   create
 */
#pragma once

#include <string>
#include <windows.h>

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
	 * @brief 判断当前程序是否已运行
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
};