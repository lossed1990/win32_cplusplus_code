/**
 * @file StringHelper.h 字符处理常用函数整理
 *
 * 日期        作者        描述
 * 2016/07/20  gxl		   create 
 */
#ifndef G_STRINGHELPER_H_
#define G_STRINGHELPER_H_

#include <sstream>
#include <string>
#include <vector>
#include <regex>

#include "hashtool/hi_md5.h"
using namespace std;

/**
 * @brief 字符处理常用函数帮助类
 */
class CStringHelper
{
public:
	CStringHelper(){}
	~CStringHelper(){}

public:
	/**
	 * @brief 根据单个分隔符，分离字符串
     * 
     * @param chStr[in]      待分割的字符串
     * @param cSeparator[in] 分割符
     * @param strList[out]   返回的结果集
     *
     * @code
       int main(int argc, char* argv[])
        {
            vector<string> m_StrList;
            CStringHelper::GetSubStringBySingleSeparator("$123$发的第三方$fdff$233",'$',m_StrList);

            for(auto str : m_StrList)
            {
                cout << str << endl;
            }

            ::system("pause");
            return 0;
        }
     * @endcode
	 */
	static void GetSubStringBySingleSeparator(char* chStr, char cSeparator, vector<string> &strList)
	{
		strList.clear();

		string cWaitAnalyStr = chStr;

		string::size_type nLen = cWaitAnalyStr.length();
		string::size_type nEndPos = cWaitAnalyStr.find(cSeparator);

		while (nLen != 0 && nEndPos != -1)
		{
			string cSubStr = cWaitAnalyStr.substr(0, nEndPos);
			cWaitAnalyStr = cWaitAnalyStr.substr(nEndPos + 1, nLen - nEndPos - 1);

			strList.push_back(cSubStr);

			nLen -= nEndPos + 1;
			nEndPos = cWaitAnalyStr.find(cSeparator);
		}
	}    

	/**
	 * @brief 判断字符串是否全为数字组成
	 *
	 * 由于使用c++11新特性，所以请确保编译器支持（如果你的编译器是GCC-4.9.0或者VS2013以下版本，请升级后，再使用）
	 *
	 * @param chStr[in]      待校验的字符串
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {    
	     bool bRet = CStringHelper::IsNumberString("123");

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool IsNumberString(const char* chStr)
	{
		regex pattern("^[0-9]*$");
		return regex_match(chStr, pattern);
	}

	/**
	 * @brief 判断字符串是否为合法的e_mail地址
	 *
	 * 由于使用c++11新特性，所以请确保编译器支持（如果你的编译器是GCC-4.9.0或者VS2013以下版本，请升级后，再使用）
	 *
	 * @param chStr[in]      待校验的字符串
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     bool bRet = CStringHelper::IsEmailString("931047642@qq.com");

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool IsEmailString(const char* chStr)
	{
		regex pattern("^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$");
		return regex_match(chStr, pattern);
	}

	/**
	 * @brief 判断字符串是否为合法的固定电话号码
	 *
	 * 由于使用c++11新特性，所以请确保编译器支持（如果你的编译器是GCC-4.9.0或者VS2013以下版本，请升级后，再使用）
	 *
	 * @param chStr[in]      待校验的字符串
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     bool bRet = CStringHelper::IsFixedNumberString("0513-12345678");

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool IsFixedNumberString(const char* chStr)
	{
		regex pattern("^(\\d{3}-\\d{8}|\\d{4}-\\d{7}|\\d{4}-\\d{8})$");
		return regex_match(chStr, pattern);
	}

	/**
	 * @brief 判断字符串是否为合法手机号码
	 *
	 * 由于使用c++11新特性，所以请确保编译器支持（如果你的编译器是GCC-4.9.0或者VS2013以下版本，请升级后，再使用）
	 *
	 * @param chStr[in]      待校验的字符串
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     bool bRet = CStringHelper::IsMobileNumberString("13588881234");

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool IsMobileNumberString(const char* chStr)
	{
		regex pattern("^(13[0-9]|14[5|7]|15[0|1|2|3|5|6|7|8|9]|18[0|1|2|3|5|6|7|8|9])\\d{8}$");
		return regex_match(chStr, pattern);
	}

	/**
	 * @brief 判断字符串是否为长时间字符格式(yyyy-mm-dd hh:mm:ss)
	 *
	 * 由于使用c++11新特性，所以请确保编译器支持（如果你的编译器是GCC-4.9.0或者VS2013以下版本，请升级后，再使用）
	 *
	 * @param chStr[in]      待校验的字符串
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     bool bRet = CStringHelper::IsLongTimeString("2016-07-25 10:00:00");

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool IsLongTimeString(const char* chStr)
	{
		regex pattern("^\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}$");
		return regex_match(chStr, pattern);
	}

	/**
	 * @brief 判断字符串是否为合法IP地址
	 *
	 * 由于使用c++11新特性，所以请确保编译器支持（如果你的编译器是GCC-4.9.0或者VS2013以下版本，请升级后，再使用）
	 *
	 * @param chStr[in]      待校验的字符串
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     bool bRet = CStringHelper::IsIPString("127.0.0.1");

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool IsIPString(const char* chStr)
	{
		regex pattern("^((?:(?:25[0-5]|2[0-4]\\d|[01]?\\d?\\d)\\.){3}(?:25[0-5]|2[0-4]\\d|[01]?\\d?\\d))$");
		return regex_match(chStr, pattern);
	}

	/**
	 * @brief 使用MD5算法转换字符串
	 *
	 * @param chStr[in]  待转换的字符串
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     string str = CStringHelper::Md5String("abc");

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static string Md5String(const char* chStr)
	{
		HL_MD5_CTX ctx;
		MD5 md5;
		md5.MD5Init(&ctx);
		md5.MD5Update(&ctx, (unsigned char*)chStr, strlen(chStr));

		unsigned char buff[16] = "";
		md5.MD5Final((unsigned char*)buff, &ctx);

		std::ostringstream os;
		for (int i = 0; i < 16; ++i)
		{
			os.width(2);
			os.fill('0');
			os << std::hex << static_cast<unsigned int>(buff[i]);
		}

		return os.str();
	}

	/**
	 * @brief 去除字符串左边的特殊字符
	 *
	 * @param chStr[in] 原始字符串
	 * @param ch[in]    特殊字符
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     string str = "###a#bc###";
	     CStringHelper::TrimLeft(str,'#');
		 cout << str << endl;

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static string& TrimLeft(string& str, char ch)
	{
		int pos = 0;
		for (pos = 0; pos < (int)str.size(); pos++)
		{
			if (str.at(pos) != ch) break;
		}

		str = str.substr(pos);
		return str;
	}

	/**
	 * @brief 去除字符串右边的特殊字符
	 *
	 * @param chStr[in] 原始字符串
	 * @param ch[in]    特殊字符
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     string str = "###a#bc###";
	     CStringHelper::TrimRight(str,'#');
	     cout << str << endl;

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static string& TrimRight(string& str, char ch)
	{
		vector<char> chs;
		int pos = str.size() - 1;
		for (pos; pos >= 0; pos--)
		{
			if (str.at(pos) != ch) break;
		}

		str.resize(pos + 1);
		return str;
	}

	/**
	 * @brief 去除字符串两侧的特殊字符
	 *
	 * @param chStr[in] 原始字符串
	 * @param ch[in]    特殊字符
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     string str = "###a#bc###";
	     CStringHelper::Trim(str,'#');
	     cout << str << endl;

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static string& Trim(string& str, char ch)
	{
		return TrimLeft(TrimRight(str, ch), ch);
	}

	/**
	 * @brief Utf转成Unicode
	 *
	 * @param utf8[in]        转换前字符串
	 * @param unicode[out]    转换后字符串
	 *
	 * @return true-成功 false-失败
	 */
	static bool Utf2Unicode(string& utf8, wstring& unicode)
	{
		int wideSize = ::MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
		if (wideSize == ERROR_NO_UNICODE_TRANSLATION)
		{
			return false;
		}

		if (wideSize == 0)
		{
			return false;
		}

		vector<wchar_t> resultString(wideSize);
		int convResult = ::MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &resultString[0], wideSize);
		if (convResult != wideSize)
		{
			return false;
		}

		unicode = wstring(&resultString[0]);
		return true;
	}

	/**
	 * @brief Unicode转成Ascii
	 *
	 * @param unicode[in]        转换前字符串
	 * @param ascii[out]         转换后字符串
	 *
	 * @return true-成功 false-失败
	 */
	static bool Unicode2Ascii(wstring& unicode, string& ascii)
	{
		int asciiSize = ::WideCharToMultiByte(CP_OEMCP, 0, unicode.c_str(), -1, NULL, 0, NULL, NULL);
		if (asciiSize == ERROR_NO_UNICODE_TRANSLATION)
		{
			return false;
		}
			
		if (asciiSize == 0)
		{
			return false;
		}

		vector<char> resultString(asciiSize);
		int convResult = ::WideCharToMultiByte(CP_OEMCP, 0, unicode.c_str(), -1, &resultString[0], asciiSize, NULL, NULL);
		if (convResult != asciiSize) 
		{
			return false;
		}

		ascii = string(&resultString[0]);
		return true;
	}

	/**
	 * @brief Utf转成Ascii
	 *
	 * @param utf[in]        转换前字符串
	 * @param ascii[out]     转换后字符串
	 *
	 * @return true-成功 false-失败
	 */
	static bool Utf2Ascii(string &utf, string &ascii)
	{
		wstring wstr;
		bool res = Utf2Unicode(utf, wstr);
		if (!res)
		{
			return false;
		}

		res = Unicode2Ascii(wstr, ascii);
		if (!res)
		{
			return false;
		}
		return true;
	}

	/**
	 * @brief Ascii转成Unicode
	 *
	 * @param ascii[in]        转换前字符串
	 * @param unicode[out]     转换后字符串
	 *
	 * @return true-成功 false-失败
	 */
	static bool Ascii2Unicode(string& ascii, wstring& unicode)
	{
		int wideSize = MultiByteToWideChar(CP_ACP, 0, (char *)ascii.c_str(), -1, NULL, 0);
		if (wideSize == ERROR_NO_UNICODE_TRANSLATION)
		{
			return false;
		}
			
		if (wideSize == 0)
		{
			return false;
		}		

		vector<wchar_t> resultString(wideSize);
		int conResult = MultiByteToWideChar(CP_ACP, 0, (char *)ascii.c_str(), -1, &resultString[0], wideSize);
		if (conResult != wideSize)
		{
			return false;
		}
			
		unicode = wstring(&resultString[0]);
		return true;
	}

	/**
	 * @brief Unicode转成Utf
	 *
	 * @param unicode[in]        转换前字符串
	 * @param utf[out]           转换后字符串
	 *
	 * @return true-成功 false-失败
	 */
	static bool Unicode2Utf(wstring &unicode, string &utf)
	{
		int utfSize = WideCharToMultiByte(CP_UTF8, 0, unicode.c_str(), -1, NULL, 0, NULL, NULL);
		if (utfSize == 0)
		{
			return false;
		}
			
		vector<char> resultString(utfSize);
		int conResult = WideCharToMultiByte(CP_UTF8, 0, unicode.c_str(), -1, &resultString[0], utfSize, NULL, NULL);
		if (conResult == utfSize)
		{
			return false;
		}
			
		utf = string(&resultString[0]);
		return true;
	}

	/**
	 * @brief Ascii转成Utf
	 *
	 * @param ascii[in]        转换前字符串
	 * @param utf[out]         转换后字符串
	 *
	 * @return true-成功 false-失败
	 */
	static bool Ascii2Utf(string &ascii, string &utf)
	{
		wstring unicode;
		bool res = Ascii2Unicode(ascii, unicode);
		if (res == false)
		{
			return false;
		}

		res = Unicode2Utf(unicode, utf);
		if (res == false)
		{
			return false;
		}

		return true;
	}
};

#endif // G_STRINGHELPER_H_