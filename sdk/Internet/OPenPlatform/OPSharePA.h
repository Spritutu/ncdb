#pragma once
#include "opsharebase.h"

/************************************************************************
    ˵��:COPSharePA, PA������
        ��ȡ��Ȩurlʱ, �ӷ�������ȡappӦ����Ϣ, 
        �������ӷ�������ȡ, ֱ�Ӵ�COPShareBase����
************************************************************************/
class COPSharePA :
    public COPShareBase
{
public:
    COPSharePA(void);
    ~COPSharePA(void);
public:
    virtual string GetRequestCodeUrl();
    bool ParseAppInfo( const tstring& strWeb, tagOP_APP_INFO& ai);
protected:
    tagOP_APP_INFO QueryAppInfo();
};