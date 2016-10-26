#include "StdAfx.h"
#include "MonitorCPU.h"
#include "CpuState.h"
CMonitorCPU::CMonitorCPU(void)
{
    ::memset(&m_data, 0, sizeof(MONITOR_CPU_DATA));
}


CMonitorCPU::~CMonitorCPU(void)
{
}

UseStatus CMonitorCPU::GetUseStatus()
{
    //��ȡ
    UseStatus us = 0;
    m_data.fPercent = m_pCPU->GetCurrentCpuUsePercent();
    m_pMonitorResultData = &m_data;

    SetDataValid(true);
    return us;
}

bool CMonitorCPU::InitChild()
{
    m_pCPU = new CCpuState;
    m_pCPU->Init();

    //cpu ��һ�λ�ȡ������ ����ʱ�������ǲ�׼ȷ��, �ڶ��ο�ʼ�Ĳ��ǶԵ�
    SetDataValid(false);
    SetType(mdt_cpu);
    return true;
    
}

