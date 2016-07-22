/**
 * @file LogHelper.h 日志记录帮助类
 *
 * 日期        作者        描述
 * 2016/07/20  gxl         create
 */
#ifndef G_LOGHELPER_H_
#define G_LOGHELPER_H_

#include<iostream>

#define GLOG_NO_ABBREVIATED_SEVERITIES

#include "glog/logging.h"
#include "glog/raw_logging.h"

#pragma comment(lib,"glog/libglog.lib")
/**
 * @brief 日志记录帮助类
 * 
 * 本类主要封装谷歌glog日志库的初始化及设置相关操作，简化使用，使用时需包含glog文件夹头文件，运行时需包含libglog.dll
 */
class CLogHelper
{
public:
	/**
	 * @breif 日志帮助类构造函数
	 *
	 * @param program[in] 程序名称，可以不填
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     //使用示例： 实例化一个对象后，即可在程序任何地方使用相关宏进行日志的记录
	     CLogHelper lh("");

	     //此处列举常用的三种日志记录方式，更多使用方法，请查阅相关资料
	     //①跟踪日志
	     LOG(INFO) << "这是跟踪日志";
	     //②警告日志
	     LOG(WARNING) << "这是警告日志";
	     //③警告日志
	     LOG(ERROR) << "这是错误日志";

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	CLogHelper(char* program)
	{
		google::InitGoogleLogging(program);

		//std::cout << 1;            //test,以防日志输出数字时报错，原因暂不明确

		//设置参数
		FLAGS_logbufsecs = 0;      //刷新日志到硬盘的时间，默认是会缓冲的，0表示实时
		FLAGS_max_log_size = 30;   //日志大小大于30M时，创建新的日志
		FLAGS_stop_logging_if_full_disk = true;   //硬盘满时停止记录
		FLAGS_colorlogtostderr = true;            //通过颜色区分控制台不同等级的日志
		FLAGS_alsologtostderr = false;
	}
	~CLogHelper(){ google::ShutdownGoogleLogging(); }

	/**
	 * @breif 设置是否将日志输出到控制台
	 *
	 * 对于普通的应用程序，开启该选项可以在vs的输出中看到日志，或者使用windbg调试时，看到日志；
	 *
	 * @param bOutput[in] true-输出 false-不输出
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     CLogHelper lh("");
		 lh.SetLogToStderr(true);

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	void SetLogToStderr(bool bOutput) { FLAGS_alsologtostderr = bOutput; }

	/**
	 * @breif 设置Info级别的日志输出路径，不设置则不会有文本文件记录
	 *
	 * glog源码如果文件夹不存在，将会把日志记录在系统temp文件夹中；demo中libglog.dll本人修改过，文件夹不存在时，不记录
	 *
	 * @param filepath[in] 输出文件夹的全路径
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     CLogHelper lh("");
	     lh.SetInfoLogDestination("c:/");   //备注：文件夹不存在时，不会创建

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	void SetInfoLogDestination(const char* filepath) { google::SetLogDestination(google::GLOG_INFO, filepath); }

	/**
	 * @breif 设置warning级别的日志输出路径，不设置则不会有文本文件记录
	 *
	 * glog源码如果文件夹不存在，将会把日志记录在系统temp文件夹中；demo中libglog.dll本人修改过，文件夹不存在时，不记录
	 *
	 * @param filepath[in] 输出文件夹的全路径
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     CLogHelper lh("");
	     lh.SetWarnLogDestination("c:/");   //备注：文件夹不存在时，不会创建

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	void SetWarnLogDestination(const char* filepath) { google::SetLogDestination(google::GLOG_WARNING, filepath); }

	/**
	 * @breif 设置error级别的日志输出路径，不设置则不会有文本文件记录
	 *
	 * glog源码如果文件夹不存在，将会把日志记录在系统temp文件夹中；demo中libglog.dll本人修改过，文件夹不存在时，不记录
	 *
	 * @param filepath[in] 输出文件夹的全路径
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     CLogHelper lh("");
	     lh.SetErrorLogDestination("c:/");   //备注：文件夹不存在时，不会创建

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	void SetErrorLogDestination(const char* filepath) { google::SetLogDestination(google::GLOG_ERROR, filepath); }
};

#endif // G_LOGHELPER_H_