#pragma once

#include <string>
#include <vector>
using namespace std;

class CStringHelper
{
public:
	CStringHelper(){}
	~CStringHelper(){}

public:
	/**
	 * @breif 根据单个分隔符，分离字符串
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
};