#include "StdAfx.h"
#include "OPTengXun.h"


COPTengXun::COPTengXun(void)
{
}


COPTengXun::~COPTengXun(void)
{
}

bool COPTengXun::AddParamGeneral()
{
    //��������������ÿ������������
    std::string c_strTokenKey	= TXWeibo::Param::strTokenKey;
    std::string c_strOpenid		= TXWeibo::Param::strOpenid;

    m_oParam.AddParam(c_strTokenKey.c_str(), m_strTokenKey.c_str());
    m_oParam.AddParam(c_strOpenid.c_str(),m_strOpenid.c_str());
    m_oParam.AddParam("oauth_consumer_key", m_opAppInfo.m_strAppID.c_str());
    m_oParam.AddParam("oauth_version", "2.a");
    m_oParam.AddParam("scope", "all");

    //"&oauth_consumer_key=%s&access_token=%s&openid=%s&oauth_version=2.a&scope=all"
    return true;
}

