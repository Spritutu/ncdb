#pragma once
#include "parestful.h"


//����


class CMarkup;
class CNewsMng;

class CPARestNews :
    public CPARestful
{
public:
    CPARestNews(void);
    ~CPARestNews(void);

//self
public:
    /************************************************************************
        fun:    ��ȡ��������, ����Ƕ�ʱ��Ϣ, �������б�Ϊ��
        remark:
        ret:   
    ************************************************************************/
    virtual bool GetNewsData( CNewsMng& lstNews );
    bool GetNewsItem(tagDATA_NEWS &strData);


//inherit
public:
    virtual tstring GetUrl();
protected:
    virtual MAP_STRING GetParam();
};


