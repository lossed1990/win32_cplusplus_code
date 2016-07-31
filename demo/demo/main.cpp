/**
 * @file main.cpp 使用demo
 *
 * 日期        作者        描述
 * 2016/07/20  gxl         create 
 */
#include <iostream>

#include "../../SystemHelper.h"
#include "../../FileHelper.h"
#include "../../StringHelper.h"
#include "../../TimeHelper.h"
#include "../../LogHelper.h"
#include "../../DumpHelper.h"
#include "../../TTSHelper.h"

#define TEST_BEGIN(str) SetColor(10,0);(cout<<"====begin "<<(str)<<endl)
#define TEST_FUNC(str) SetColor(15,0);(cout<<"@function>> "<<(str)<<endl)
#define TEST_RES(str) SetColor(15,0);(cout<<"@result>> "<<(str)<<endl<<endl)

using namespace std;

void testSystemHelper();
void testFileHelper();
void testStringHelper();
void testTimeHelper();
void testLogHelper();
void testDumpHelper();
void testTTSHelper();

void SetColor(unsigned short forecolor = 4, unsigned short backgroudcolor = 0)
{
	//SetColor(14,0); //10-绿 11-蓝 12-红 14-黄 15-白 

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);             //获取缓冲区句柄
	SetConsoleTextAttribute(hCon, forecolor | backgroudcolor); //设置文本及背景色
}

int main(int argc, char* argv[])
{
	testSystemHelper();
	testTTSHelper();
	testFileHelper();
	testStringHelper();
	testTimeHelper();
	testLogHelper();
	testDumpHelper();
	
	cout << "请输入restart，测试重新开启一个程序" <<endl;
	char cParam[32] = { 0 };
	cin >> cParam;
	if (strcmp("restart", cParam) == 0)
	{
		TEST_FUNC("ReStartProcess()");	
		CSystemHelper::ReStartProcess();
		TEST_RES("void");
		exit(0);
	}

	::system("pause");
	return 0;
}

void testSystemHelper()
{
	TEST_BEGIN("testSystemHelper");

	TEST_FUNC("CheckProcessMutex(\"Single.test\")");
	string str = CSystemHelper::CheckProcessMutex("Single.test") ? "本程序已运行" : "本程序未运行";
	TEST_RES(str);

	TEST_FUNC("CheckProcessExist(\"firefox.exe\")");
	str = CSystemHelper::CheckProcessExist("firefox.exe") ? "firefox.exe进程存在" : "firefox.exe进程不存在";
	TEST_RES(str);

	TEST_FUNC("OpenProcess(\"calc\")");
	CSystemHelper::OpenProcess("calc");
	TEST_RES("已尝试打开计算器程序");

	TEST_FUNC("DestoryProcess(\"hh.exe\")");
	CSystemHelper::DestoryProcess("hh.exe");
	TEST_RES("void");

	TEST_FUNC("SetAutoStartup(\"demo\")");
	str = CSystemHelper::SetAutoStartup("demo") ? "设置自启动成功" : "设置自启动失败，请查看是否没有管理员权限";
	TEST_RES(str);

	TEST_FUNC("CancelAutoStartup(\"demo\")");
	str = CSystemHelper::CancelAutoStartup("demo") ? "取消自启动设置成功" : "取消自启动设置失败，请查看是否没有管理员权限";
	TEST_RES(str);
	
	TEST_FUNC("OpenFolder(\"c:\\\")");
	CSystemHelper::OpenFolder("c:\\");
	TEST_RES("已经尝试打开c盘根目录");
	
}

void testFileHelper()
{
	TEST_BEGIN("testFileHelper");

	TEST_FUNC("GetFileVersionString(\"demo.exe\")");
	string cResult = CFileHelper::GetFileVersionString("demo.exe");
	TEST_RES(cResult);

	TEST_FUNC("GetCurrentFileVersionString()");
	cResult = CFileHelper::GetCurrentFileVersionString();
	TEST_RES(cResult);

	TEST_FUNC("GetCurrentFilePath()");
	cResult = CFileHelper::GetCurrentFilePath();
	TEST_RES(cResult);

	TEST_FUNC("GetCurrentFileParentPath()");
	cResult = CFileHelper::GetCurrentFileParentPath(5);
	TEST_RES(cResult);
	
}

void testStringHelper()
{
	TEST_BEGIN("testStringHelper");

	TEST_FUNC("GetSubStringBySingleSeparator(\"$123$第三方$fdff$233$\",'$',m_StrList)");
	vector<string> m_StrList;
	CStringHelper::GetSubStringBySingleSeparator("$123$第三方$fdff$233$",'$',m_StrList);

	string str("");
	for (auto item : m_StrList){
		str += item + "; ";
	}
	 
	TEST_RES(str);

	TEST_FUNC("IsNumberString(\"123\")");
	str = CStringHelper::IsNumberString(" 123") ? "全为数字" : "不全为数字";
	TEST_RES(str);

	TEST_FUNC("IsEmailString(\"931047642@qq.com\")");
	str = CStringHelper::IsEmailString("931047642@qq.com") ? "合法邮箱地址" : "非法邮箱地址";
	TEST_RES(str);

	TEST_FUNC("IsFixedNumberString(\"0513-12345678\")");
	str = CStringHelper::IsFixedNumberString("0513-12345678") ? "合法固定电话号码" : "非法固定电话号码";
	TEST_RES(str);

	TEST_FUNC("IsMobileNumberString(\"13588881234\")");
	str = CStringHelper::IsMobileNumberString("13588881234") ? "合法手机电话号码" : "非法手机电话号码";
	TEST_RES(str);

	TEST_FUNC("IsLongTimeString(\"2016-07-25 10:00:00\")");
	str = CStringHelper::IsLongTimeString("2016-07-25 10:00:00") ? "合法长时间格式" : "非法长时间格式";
	TEST_RES(str);

	TEST_FUNC("IsIPString(\"127.0.0.1\")");
	str = CStringHelper::IsIPString("127.0.0.1") ? "合法IP地址" : "非法IP地址";
	TEST_RES(str);	

	TEST_FUNC("Md5String(\"abc\")");
	str = CStringHelper::Md5String("abc");
	TEST_RES(str);	
}

void testTimeHelper()
{
	TEST_BEGIN("testTimeHelper");

	TEST_FUNC("CTimeHelper::ThisDay()");
	G_TIMES sTimes;
	CTimeHelper::ThisDay(sTimes);
	char str[128] = { 0 };
	sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
		sTimes.s_BeginTime.wYear, sTimes.s_BeginTime.wMonth, sTimes.s_BeginTime.wDay,
		sTimes.s_BeginTime.wHour, sTimes.s_BeginTime.wMinute, sTimes.s_BeginTime.wSecond,
		sTimes.s_BeginTime.wDayOfWeek,
		sTimes.s_EndTime.wYear, sTimes.s_EndTime.wMonth, sTimes.s_EndTime.wDay,
		sTimes.s_EndTime.wHour, sTimes.s_EndTime.wMinute, sTimes.s_EndTime.wSecond,
		sTimes.s_EndTime.wDayOfWeek
		);
	TEST_RES(str);

	TEST_FUNC("CTimeHelper::LastDay()");
	CTimeHelper::LastDay(sTimes);
	sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
		                sTimes.s_BeginTime.wYear,sTimes.s_BeginTime.wMonth,sTimes.s_BeginTime.wDay,
		                sTimes.s_BeginTime.wHour,sTimes.s_BeginTime.wMinute,sTimes.s_BeginTime.wSecond,
		                sTimes.s_BeginTime.wDayOfWeek,
		                sTimes.s_EndTime.wYear,sTimes.s_EndTime.wMonth,sTimes.s_EndTime.wDay,
		                sTimes.s_EndTime.wHour,sTimes.s_EndTime.wMinute,sTimes.s_EndTime.wSecond,
		                sTimes.s_EndTime.wDayOfWeek
	);
	TEST_RES(str);

	TEST_FUNC("CTimeHelper::LastDays(sTimes,3)");
	CTimeHelper::LastDays(sTimes,3);
	sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
		sTimes.s_BeginTime.wYear, sTimes.s_BeginTime.wMonth, sTimes.s_BeginTime.wDay,
		sTimes.s_BeginTime.wHour, sTimes.s_BeginTime.wMinute, sTimes.s_BeginTime.wSecond,
		sTimes.s_BeginTime.wDayOfWeek,
		sTimes.s_EndTime.wYear, sTimes.s_EndTime.wMonth, sTimes.s_EndTime.wDay,
		sTimes.s_EndTime.wHour, sTimes.s_EndTime.wMinute, sTimes.s_EndTime.wSecond,
		sTimes.s_EndTime.wDayOfWeek
		);
	TEST_RES(str);

	TEST_FUNC("CTimeHelper::ThisWeek()");
	CTimeHelper::ThisWeek(sTimes);
	sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
		sTimes.s_BeginTime.wYear, sTimes.s_BeginTime.wMonth, sTimes.s_BeginTime.wDay,
		sTimes.s_BeginTime.wHour, sTimes.s_BeginTime.wMinute, sTimes.s_BeginTime.wSecond,
		sTimes.s_BeginTime.wDayOfWeek,
		sTimes.s_EndTime.wYear, sTimes.s_EndTime.wMonth, sTimes.s_EndTime.wDay,
		sTimes.s_EndTime.wHour, sTimes.s_EndTime.wMinute, sTimes.s_EndTime.wSecond,
		sTimes.s_EndTime.wDayOfWeek
		);
	TEST_RES(str);

	TEST_FUNC("CTimeHelper::LastWeek()");
	CTimeHelper::LastWeek(sTimes);
	sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
		sTimes.s_BeginTime.wYear, sTimes.s_BeginTime.wMonth, sTimes.s_BeginTime.wDay,
		sTimes.s_BeginTime.wHour, sTimes.s_BeginTime.wMinute, sTimes.s_BeginTime.wSecond,
		sTimes.s_BeginTime.wDayOfWeek,
		sTimes.s_EndTime.wYear, sTimes.s_EndTime.wMonth, sTimes.s_EndTime.wDay,
		sTimes.s_EndTime.wHour, sTimes.s_EndTime.wMinute, sTimes.s_EndTime.wSecond,
		sTimes.s_EndTime.wDayOfWeek
		);
	TEST_RES(str);

	TEST_FUNC("CTimeHelper::ThisMonth()");
	CTimeHelper::ThisMonth(sTimes);
	sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
		sTimes.s_BeginTime.wYear, sTimes.s_BeginTime.wMonth, sTimes.s_BeginTime.wDay,
		sTimes.s_BeginTime.wHour, sTimes.s_BeginTime.wMinute, sTimes.s_BeginTime.wSecond,
		sTimes.s_BeginTime.wDayOfWeek,
		sTimes.s_EndTime.wYear, sTimes.s_EndTime.wMonth, sTimes.s_EndTime.wDay,
		sTimes.s_EndTime.wHour, sTimes.s_EndTime.wMinute, sTimes.s_EndTime.wSecond,
		sTimes.s_EndTime.wDayOfWeek
		);
	TEST_RES(str);

	TEST_FUNC("CTimeHelper::LastMonth()");
	CTimeHelper::LastMonth(sTimes);
	sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
		sTimes.s_BeginTime.wYear, sTimes.s_BeginTime.wMonth, sTimes.s_BeginTime.wDay,
		sTimes.s_BeginTime.wHour, sTimes.s_BeginTime.wMinute, sTimes.s_BeginTime.wSecond,
		sTimes.s_BeginTime.wDayOfWeek,
		sTimes.s_EndTime.wYear, sTimes.s_EndTime.wMonth, sTimes.s_EndTime.wDay,
		sTimes.s_EndTime.wHour, sTimes.s_EndTime.wMinute, sTimes.s_EndTime.wSecond,
		sTimes.s_EndTime.wDayOfWeek
		);
	TEST_RES(str);
	
	TEST_BEGIN("CTimeCounter");
	TEST_FUNC("CTimeCounter::GetExecutionTime()");
	CTimeCounter newTimeCounter;
	Sleep(501);
	cout << "@result>> " << "运行耗时:" << newTimeCounter.GetExecutionTime() << endl << endl;
}

void testLogHelper()
{
	TEST_BEGIN("testLogHelper");
	SetColor(15, 0);

	CLogHelper g_LogHelper("");
	g_LogHelper.SetLogToStderr(true);

	//此处列举常用的三种日志记录方式，更多使用方法，请查阅相关资料
	//①跟踪日志
	LOG(INFO) << "这是跟踪日志";
	//②警告日志
	LOG(WARNING) << "这是警告日志";
	//③警告日志
	LOG(ERROR) << "这是错误日志";

	TEST_RES("更多使用方法，请参考网上资料");
}

void testDumpHelper()
{
	TEST_BEGIN("testDumpHelper");

	CDumpHelper dumper;
	dumper.SetHandler();

	TEST_RES("请修改demo代码，测试dump的生成");
	//添加以下内容，运行demo时将生成一个dump文件
	//int* i = NULL;
	//*i = 0;
}

void testTTSHelper()
{
	TEST_BEGIN("testTTSHelper");

	TEST_FUNC("TTSHelper::Instance()->Speak(\"hello world\")");
	TTSHelper::Instance()->Speak("hello world");
	TEST_RES("程序结束时，请注意调用TTSHelper::FreeInstance()释放资源");
}