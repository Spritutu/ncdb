#include "StdAfx.h"
#include "OptionNotify.h"
#include "define_gnl.h"

COptionNotify::COptionNotify(void)
{
}


COptionNotify::~COptionNotify(void)
{
}

bool COptionNotify::AddNotify( ENUM_OPTION_PAGE op, WndID wndID )
{
    //һ��ҳ������ж��������, һ�������߿��Լ������ҳ��
    
    LST_MONITOR::iterator itFind = m_lstMonitor.find(op);
    itFind->second.push_back(wndID);

    return true;
}

bool COptionNotify::Notify( ENUM_OPTION_PAGE op )
{
    LST_MONITOR::iterator itFind = m_lstMonitor.find(op);
    FOR_EACH_ITER(LST_WND, itFind->second, it)
    {
        WndID wndID = *it;
        //TODO:���ʹ�����Ϣ,֪ͨ�����Ѹ���
    }
    return true;
}

bool COptionNotify::Init()
{
    LST_WND lstWnd;
    m_lstMonitor.insert(pair<ENUM_OPTION_PAGE, LST_WND>(op_general, lstWnd));
    m_lstMonitor.insert(pair<ENUM_OPTION_PAGE, LST_WND>(op_app, lstWnd));
    m_lstMonitor.insert(pair<ENUM_OPTION_PAGE, LST_WND>(op_update, lstWnd));
    m_lstMonitor.insert(pair<ENUM_OPTION_PAGE, LST_WND>(op_flow, lstWnd));
    return true;
}
