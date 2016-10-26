#pragma once
#include "parestful.h"
#include "PAOPDef.h"
#include "OpenPlatformDef.h"
class CPAOPShare :
    public CPARestful
{
public:
    CPAOPShare(ENUM_OP_SHARE_TYPE type);
    ~CPAOPShare(void);
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
    
    static tagOP_APP_INFO QueryAppInfo( ENUM_OP_SHARE_TYPE lType );
protected:
    /************************************************************************
        fun:    ��ȡƽ̨���صĵ�¼��Ȩurl
        remark:
        ret:   
    ************************************************************************/
    bool ParseOPAppInfo();
protected:
    ENUM_OP_SHARE_TYPE          m_pl_type;
    tagOP_APP_INFO              m_OpAppInfo;
};

