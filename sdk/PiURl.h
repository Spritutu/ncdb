#pragma once
#include "piTypeDef.h"
class CPiURl
{
public:
    CPiURl(tcpchar szUrl);
    CPiURl(const tstring& szUrl);
    ~CPiURl(void);
public:
    tstring GetParamValue(int nCount);
    /************************************************************************
        fun:    ��ȡָ���������Ĳ���ֵ, ֧��url����& ��#, �Լ�ֱ�Ӳ����ַ��������
        remark:
        ret:   
    ************************************************************************/
    tstring GetParamValue(tcpchar szParam);
    bool AppendParam( tcpchar szParam, tcpchar szValue );
    tstring GetUrl(){ return m_strUrl; }
	/************************************************************************
		fun:	��·������url����Ĳ������ִ�utf8���봦��
		param:	
		memo:	�Ƚ���urlDecode�� �ٲ������ֵ�utf8
	************************************************************************/
	tstring DecodeParam();
private:
    tstring             m_strUrl;
};

