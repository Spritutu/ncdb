#include "StdAfx.h"
#include "PAMsgPush.h"
#include "piTypeDef.h"
#include "PiNetRestful.h"
#include "PARestful.h"
#include "NewsMng.h"
#include "Math/mathUnit.h"
#include "ResCommon.h"
#include "AutoType.h"
#include "functional.h"
#include "PARestNews.h"
#include "PADebug.h"
Pi_NameSpace_Using

CPAMsgPush::CPAMsgPush( HWND hwnd /*= NULL*/ )
{
    m_hwnd = hwnd;
}


CPAMsgPush::~CPAMsgPush(void)
{
}

bool CPAMsgPush::Init()
{
    bool bRet = CThreadLight::Init();
    if ( !bRet )
    {
        return false;
    }
    Create_Auto_Ptr(m_pNewsMng, CNewsMng);
    return Run();
    
}

bool CPAMsgPush::NotifyUI()
{
    if (m_hwnd)
    {
    #ifndef TEST_UNITS
        ::SendMessage(m_hwnd, UM_NEWS_PUSH, (WPARAM)m_pNewsMng.get(), 0);
    #endif
        return true;
    }
    return false;
}

DWORD CPAMsgPush::DoWork()
{
    enum {err = 0, ok = 1};
    int nResult = ok;
    while(1)

    {
        tstring strMsg;
        strMsg = GetSysTime();
        strMsg += _T(" �µ�����");
        PAOut10(strMsg.c_str());

        if( ! GetMsg(msg_news, *m_pNewsMng))
        {//��ȡʧ��
            nResult = err;  
            PAOut11(_T("get msgPush fail"));
        }

        //֪ͨ����
        NotifyUI();
        int nCycle = m_pNewsMng->GetNextCycle();
        ResetQuestCycle(nCycle);

        CThreadLight::WaitTime();

        if ( CThreadLight::IsWillStopThread() )
        {
            PAOut10(_T("�ⲿȡ����ȡ����"));
            break;
        }
    }

    CAutoType at;
    at.SetData((long)nResult);
    
    tstring strMsg(GetSysTime());
    strMsg += _T(" �˳���Ϣ���ͻ�ȡ");
    PAOut10(strMsg.c_str(), at);
    return ok;
}

bool CPAMsgPush::GetMsg( ENUM_MSG_TYPE msgType, CNewsMng& newsMng )
{
    //ͨ��url �Ͳ���, ��ƽ̨�ϻ�ȡ����, ������������, �жϲ������; ����ɹ��󷵻�����
    newsMng.Clear();
    newsMng.SetCircle(NUM_CIRCLE_NEXT);
    //auto_ptr<CPiNetRestful> pRest(GetRestfulObj(msgType));
    CPARestNews pRest;
    //����url �Ͳ���
    if( ! pRest.Send())
    {
        return false;
    }

    //tstring strData;
    //CNewsMng newsMng;
    
    LST_NEWS lstNews;
    if( ! pRest.GetNewsData(newsMng))
    {
        return false;
    }
    
    return true;
}


CPARestNews* CPAMsgPush::GetRestfulObj( ENUM_MSG_TYPE msgType )
{
    CPARestNews* pRest = NULL;
    switch (msgType)
    {
    case msg_normal:
        //pRest = new CPARestfulNews;
        break;
    case msg_news:
        pRest = new CPARestNews;
        break;
    default:
        break;
    }
    return pRest;
}

bool CPAMsgPush::ResetQuestCycle( int nCycle )
{
    CThreadLight::SetDelayMax(nCycle);
    return true;
}

bool CPAMsgPush::UnInit()
{
    return CThreadLight::UnInit();
}
