#include "StdAfx.h"
#include "PAMonitorPrc.h"
#include "MDHandle.h"

CPAMonitorPrc::CPAMonitorPrc(void)
{
}


CPAMonitorPrc::~CPAMonitorPrc(void)
{
}

void CPAMonitorPrc::InitTask()
{
    AddMonitor(new CMDHandleSai);
    AddMonitor(new CMDHandlePA);
    AddMonitor(new CMDHandlePS);
    //AddMonitor(m_pHDA);
    
}

bool CPAMonitorPrc::UnInit()
{
    //�ͷ���ӵ����м�������ڴ�,delete
    return true;
}
