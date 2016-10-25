#ifndef __HTTP_CURL_H__
#define __HTTP_CURL_H__
#include "curl/curlHeader.h"
#include "stdHeader.h"
#include "PiTypeDef.h"


class HttpClient
{
public:
	HttpClient(void);
	~HttpClient(void);

public:
	/**
	* @brief HTTP POST����
	* @param strUrl �������,�����Url��ַ,��:http://www.baidu.com
	* @param strPost �������,ʹ�����¸�ʽpara1=val1?2=val2&��
	* @param strResponse �������,���ص�����
	* @return �����Ƿ�Post�ɹ�
	*/
	int Post(const std::string & strUrl, const std::string & strPost, std::string & strResponse);

	/**
	* @brief HTTP GET����
	* @param strUrl �������,�����Url��ַ,��:http://www.baidu.com
	* @param strResponse �������,���ص�����
	* @return �����Ƿ�Post�ɹ�
	*/
	int Get(StringCRef strUrl, tcpchar strParam, tstring& strResponse, bool bUtf8 = false);
	int Get(StringCRef strUrl, tcpchar strParam, string& strResponse);
	

	/**
	* @brief HTTPS POST����,��֤��汾
	* @param strUrl �������,�����Url��ַ,��:https://www.alipay.com
	* @param strPost �������,ʹ�����¸�ʽpara1=val1?2=val2&��
	* @param strResponse �������,���ص�����
	* @param pCaPath �������,ΪCA֤���·��.�������ΪNULL,����֤��������֤�����Ч��.
	* @return �����Ƿ�Post�ɹ�
	*/
	int Posts(const std::string & strUrl, const std::string & strPost, std::string & strResponse, const char * pCaPath = NULL);

	/**
	* @brief HTTPS GET����,��֤��汾
	* @param strUrl �������,�����Url��ַ,��:https://www.alipay.com
	* @param strResponse �������,���ص�����
	* @param pCaPath �������,ΪCA֤���·��.�������ΪNULL,����֤��������֤�����Ч��.
	* @return �����Ƿ�Post�ɹ�
	*/
	int Gets(const std::string & strUrl, std::string & strResponse, const char * pCaPath = NULL);

	void RequestTimeout(int val) { m_nRequestTimeout = val; }

public:
	void SetDebug(bool bDebug);

private:
	bool m_bDebug;
	int			m_nRequestTimeout;	//��ʱʱ��, ��
	
};

#endif
