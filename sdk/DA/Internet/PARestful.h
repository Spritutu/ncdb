#pragma once
#include "pinetrestful.h"
#include "PARestfulDef.h"
#include "ResCommon.h"

class CMarkup;
class CPARestful:
    public CPiNetRestful
{
public:
    CPARestful(void);
    virtual ~CPARestful(void);

//inherit
public:
    /************************************************************************
        fun:    �����ݽ���UTF8תUNICODE
        remark:
        ret:   
    ************************************************************************/
    virtual bool GetDistWebData( tstring& strData );

    /************************************************************************
        fun:    �����в���ֵ���� base64����
        remark:
        ret:   
    ************************************************************************/
    virtual bool DoParam();
protected:
    auto_ptr<CMarkup>            m_pXML;
    
};


