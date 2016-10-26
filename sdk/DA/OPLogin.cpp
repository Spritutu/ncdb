#include "StdAfx.h"
#include "OPLogin.h"
#include "OPParamMng.h"
#include "Markup.h"
#include "XmlUtil.h"
#include "StrCoding.h"


COPLogin::COPLogin(ENUM_OP_LOGIN_TYPE loginType)
{
    m_login_type = loginType;
    m_SendType = Restful_Get;
}


COPLogin::~COPLogin(void)
{
}

tstring COPLogin::GetUrl()
{
    return COPParamMng::GetUrlLoginAuth();
}

MAP_STRING COPLogin::GetParam()
{
    return COPParamMng::GetParamLoginAuth(m_login_type);
}

tstring COPLogin::ExtractRetUrl()
{
    //��ȡurl
    tstring strUrl;
    tstring strWebData;
    CPARestful::GetDistWebData(strWebData);

    if( ! CXmlUtil::GetChildElemData(strWebData.c_str(), _T("url"), strUrl))
    {
        return strUrl;
    }
    
    //url����
    strUrl = CStrCoding::DecodeBase64Str_T(strUrl.c_str());
   // strUrl = CStrCoding::UrlDecode(strUrl); // modify:xuemingzhi [2014/04/22]:����Ҫ�ⲿ����
    return strUrl;
}

bool COPLogin::DoParam()
{
    /* ��д, ���θ���ļ��ܲ���*/
    return true;
}

tstring COPLogin::QueryUrlAuth( ENUM_OP_LOGIN_TYPE lType )
{    
    COPLogin opLogin(lType);
    if( ! opLogin.Send())
    {
        return _T("");
    }
    return opLogin.ExtractRetUrl();
}
