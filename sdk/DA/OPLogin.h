#pragma once
#include "PARestful.h"
#include "OpenPlatformDef.h"
#include "PAOPDef.h"
class COPLogin :public CPARestful
{
public:
    
    COPLogin(ENUM_OP_LOGIN_TYPE loginType);
    ~COPLogin(void);

//inherit
public:
    virtual tstring GetUrl();
    virtual bool DoParam();

protected:
    virtual MAP_STRING GetParam();
//self
public:
    /************************************************************************
        fun:    �������������Ȩ��ַ, ���ؽ������url
        remark:
        ret:   
    ************************************************************************/
    
    static tstring QueryUrlAuth( ENUM_OP_LOGIN_TYPE lType );
protected:
    /************************************************************************
        fun:    ��ȡƽ̨���صĵ�¼��Ȩurl
        remark:
        ret:   
    ************************************************************************/
    tstring ExtractRetUrl();
protected:
    ENUM_OP_LOGIN_TYPE          m_login_type;
};

