/**
 * @file TTSHelper.h 文本语音转换帮助类
 *
 * 日期        作者        描述
 * 2016/07/26  gxl         create 
 */
#ifndef G_TTSHELPER_H_
#define G_TTSHELPER_H_

#include <sapi.h>
#pragma comment(lib,"sapi.lib")

/**
 * @brief 文本语音转换帮助类 
 *
 * @note 1、单例类，便于全局使用；
 * @note 2、异步播报，以防阻塞；
 * @note 3、目前只封装了播放、停止两个接口，设置速度（SetRate）、设置音量（SetVolume）暂时省略
 */
class TTSHelper
{
private:
	static TTSHelper* m_pTTSInst;
	TTSHelper(void) : m_bInit(false)
	{
		if (!m_bInit)
		{
			::CoInitialize(NULL);
			HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
			m_bInit = (SUCCEEDED(hr)) ? true : false;
		}
	}

	ISpVoice* pVoice = NULL;
	bool m_bInit;

public:
	~TTSHelper(void)
	{
		if (m_bInit && pVoice)
		{
			pVoice->Speak(NULL, SPF_PURGEBEFORESPEAK, 0);
			pVoice->Release();
			CoUninitialize();
		}	
	}

	/**
	 * @brief 获取全局唯一操作对象
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     TTSHelper* pTTSHelper = TTSHelper::Instance();

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static TTSHelper* Instance(){ return (m_pTTSInst == NULL ? m_pTTSInst = new TTSHelper() : m_pTTSInst); }

	/**
	 * @brief 释放资源
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     TTSHelper::FreeInstance();

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void FreeInstance()
	{
		if (m_pTTSInst)
		{
			delete m_pTTSInst;
			m_pTTSInst = NULL;
		}
	}

public:
	/**
	 * @brief 播放文字
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     TTSHelper::Instance()->Speak();

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	bool Speak(const char* chStr)
	{
		if (m_bInit && pVoice)
		{
			int nLen = strlen(chStr);
			int nwLen = MultiByteToWideChar(CP_ACP, 0, chStr, -1, NULL, 0);
			WCHAR* pwStr = new WCHAR[nwLen];
			MultiByteToWideChar(CP_ACP, 0, chStr, -1, pwStr, nwLen);
			pwStr[nwLen - 1] = '\0';

			//char ch[64] = "你已经3454352345234";
			HRESULT	ret = pVoice->Speak(pwStr, SPF_ASYNC, 0);  //异步方式
			if (SUCCEEDED(ret))
			{
				return true;
			}

			delete[] pwStr;
		}

		return false;
	}

	/**
	 * @brief 停止播放
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     TTSHelper::Instance()->Stop();

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	void Stop()
	{
		if (m_bInit && pVoice)
		{
			pVoice->Speak(NULL, SPF_PURGEBEFORESPEAK, 0);
		}
	}
};

TTSHelper* TTSHelper::m_pTTSInst = NULL;

#endif // G_TTSHELPER_H_ 