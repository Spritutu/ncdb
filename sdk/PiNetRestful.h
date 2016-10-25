#pragma once
#include "PiNetRestfulDef.h"
#include <wininet.h>
#include "piTypeDef.h"
class CPiNetRestful
{
    
public:
    CPiNetRestful(void);
    ~CPiNetRestful(void);

//--self---------------------------------------------------------------------
public:
    virtual bool GetDistWebData( tstring& strData );

protected:
    /************************************************************************
        fun:    �Է���ǰ�Ĳ����ַ���������
        remark:
        ret:   
    ************************************************************************/
    virtual bool SwitchSendParam( tstring& strParam );
    /************************************************************************
        fun:    ����ɶ����ݽ�������ת��
        remark:
        ret:   
    ************************************************************************/
    virtual tstring GetUrl();
    /************************************************************************
        fun:    ��ȡ�˲���map�б�, ���ԶԲ����б���д���
        remark:
        ret:   
    ************************************************************************/
    virtual bool DoParam();
public:
    bool Send();
    static tstring MakeParam( MAP_STRING mapString );
    static string MakeParam( MAP_STRINGA mapString );
    static bool SendSync( StringCRef strUrl, StringCRef strParam, ENUM_RESTFUL_TYPE nType, tstring& strDataWebRet);

protected:
    bool SendHttpQuest( tstring strUrl, string strParam, ENUM_RESTFUL_TYPE nType);
    bool SendHttps(tstring strUrl, tstring strParam);
    bool EnsureQueryOk(HINTERNET hInet);

    const tstring& GetWebData();

    bool Send( ENUM_RESTFUL_TYPE nType );

    bool AppendUrlParam(ENUM_RESTFUL_TYPE nType);
    //bool SendHttpQuest( tstring strUrl, tstring strParam, ENUM_RESTFUL_TYPE nType );
protected:
    virtual MAP_STRING GetParam();
protected:
    ENUM_RESTFUL_TYPE           m_SendType;
    tstring                     m_strWebData;
    tstring                     m_strUrl;
    tstring                     m_strParam;
    MAP_STRING                  m_MapParam;
};

