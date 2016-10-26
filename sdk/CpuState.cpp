#include "StdAfx.h"
#include "CpuState.h"
#include <Windows.h>
#include <time.h>
#include <iostream>
#include "HardwareQuery.h"
#include "Math/mathUnit.h"
using namespace std;
Pi_NameSpace_Using



CCpuState::CCpuState(void)
{
    m_hProcess      = NULL;
    m_fCpuUseSelfProcessPercent = NULL;
    memset(m_timeOldArr, 0, sizeof(m_timeOldArr[0]) * NUMBER_TIME_DATA_TYPE);
}


CCpuState::~CCpuState(void)
{
    UnInit();
}

bool CCpuState::Init()
{
    m_pHardwareQuery = auto_ptr<CHardwareQuery>(new CHardwareQuery);
    m_pHardwareQuery->QueryInfo();

    m_hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId());
    CalcProcessSpendTimeDiff();
    CalcCpuIdleDiff();
    return true;
}

bool CCpuState::UnInit()
{
    if (m_hProcess)
    {
        ::CloseHandle(m_hProcess);
        m_hProcess = NULL;
    }   
    return true;
}

__int64 CCpuState::FileTimeToInt64( const FILETIME& time )
{    
    ULARGE_INTEGER tt;
    tt.LowPart = time.dwLowDateTime;
    tt.HighPart = time.dwHighDateTime;
    return tt.QuadPart;
}

float CCpuState::GetCurrentProcessSpend()
{
    /*TODO: ���ڿ�ʱ��ӿ��ڸ��Ի�ȡ�Ľӿ������, �ᵼ�µڶ�����ʼ�Ľӿ� ʱ�䱻��һ���ӿڸ�������, 
            ���԰Ѹýӿڷ����ⲿͳһ����, ���߷ֱ��ڸ��Խӿ��ﱣ��ʱ���
    */

    time_t nExpend = CalcProcessSpendTimeDiff();
    time_t nSpend = CalcTimePass(m_timeOldArr[pos_process]);

    
    //cout<<"������ʱ��:"<<nSpend<<endl;

    if (nSpend > 0)// ʱ��������Ϊ��ֵ�ż���, ����û�������
    {
        m_fCpuUseSelfProcessPercent = INT_TO_FLOAT(NANOSECOND100_TO_NANOSECOND(nExpend)) 
            / MILLISECOND_TO_NANOSECOND( nSpend) * 100.0;
    }
    
    return m_fCpuUseSelfProcessPercent /m_pHardwareQuery->GetCpuThreadCountTotal();
}

time_t CCpuState::CalcTimePass( time_t& nOld )
{
    //�ܾ���ʱ��
    DWORD dwTime = GetTickCount();
    DWORD tSpend = dwTime - static_cast<DWORD>(nOld);
    nOld = dwTime;
    return tSpend;
}

time_t CCpuState::CalcProcessSpendTimeTotal()
{
    FILETIME ftCreate   = {0};
    FILETIME ftExit     = {0};
    FILETIME ftKernel   = {0};
    FILETIME ftUser     = {0};

    if(!::GetProcessTimes(m_hProcess, &ftCreate, &ftExit, &ftKernel, &ftUser))
    {
        return 0;
    }

    //�����������cpuʱ�� = �ں�ʱ�� + �û�ʱ��
    //�ý���������ʱ��

    __int64 nExpend = FileTimeToInt64(ftKernel) + FileTimeToInt64(ftUser);
    return nExpend;
}

time_t CCpuState::CalcProcessSpendTimeDiff()
{
    time_t nTotal = CalcProcessSpendTimeTotal();
    cout<<"��������ʱ��:" <<nTotal<<endl;
    time_t nDiff = nTotal - m_timeOldArr[pos_process_spend_pre];
    m_timeOldArr[pos_process_spend_pre] = nTotal;
    return nDiff;
}

float CCpuState::GetCurrentCpuIdlePercent()
{
    time_t nIdleDiff = CalcCpuIdleDiff();

    //�������ʱ��, ����ʱ��/����ʱ�� = cpu���аٷֱ�

    time_t nUserKernelNow = CalcCpuUserKernelTotal();
    time_t nUserKernelDiff = nUserKernelNow - m_timeOldArr[pos_cpu_userKernel_pre];
    m_timeOldArr[pos_cpu_userKernel_pre] = nUserKernelNow;

    //cout<<"���о���ʱ��2: "<< NANOSECOND100_TO_MILLISECOND(nUserKernelDiff * 1.0)<<endl;

    //cpuʹ����
    if (nUserKernelDiff)
    {
        m_fCpuUsePercent = (INT_TO_FLOAT(nUserKernelDiff) - nIdleDiff)/ nUserKernelDiff * 100;
    }
    cout<< "������:" << m_fCpuUsePercent;

    //cpu������
    if(nUserKernelDiff > 0)
    {
        m_fCpuIdlePercent = INT_TO_FLOAT(NANOSECOND100_TO_NANOSECOND(nIdleDiff)) 
            / NANOSECOND100_TO_NANOSECOND(nUserKernelDiff) * 100;
    }
    return m_fCpuIdlePercent;
    
}

time_t CCpuState::CalcCpuIdleTotal()
{
    enum {err = 0};
    FILETIME ftIdle     = {0};
    FILETIME ftKernel   = {0};
    FILETIME ftUser     = {0};
    if(!::GetSystemTimes(&ftIdle, &ftKernel, &ftUser))
    {
        return err;
    }
    //cout<<"idle"<<FileTimeToInt64(ftIdle) << " kernel+User" <<FileTimeToInt64(ftKernel)
        //+ FileTimeToInt64(ftUser) <<endl;
    __int64 nIdleTotal = FileTimeToInt64(ftIdle);

    return nIdleTotal;
}

time_t CCpuState::CalcCpuIdleDiff()
{
    //���ϴο��жԱ� �ó����ʱ��Ŀ���ʱ��, 
    time_t nIdleTotal = CalcCpuIdleTotal();
    time_t nDiff = nIdleTotal - m_timeOldArr[pos_cpu_idle_pre];
    m_timeOldArr[pos_cpu_idle_pre] = nIdleTotal;
    //cout<<"idle����ʱ��: "<<NANOSECOND100_TO_MILLISECOND(nDiff)<<endl;
    return nDiff;
}

time_t CCpuState::CalcCpuIdleDiff2()
{
    //���ϴο��жԱ� �ó����ʱ��Ŀ���ʱ��, 
    //static time_t nCpuIdleOld = 0;

    time_t nIdleTotal = CalcCpuIdleTotal();
    time_t nDiff = nIdleTotal - m_timeOldArr[pos_cpu2_idle_pre];
    m_timeOldArr[pos_cpu2_idle_pre] = nIdleTotal;
    //cout<<"idle����ʱ��2: "<<NANOSECOND100_TO_MILLISECOND(nDiff)<<endl;
    return nDiff;
}

float CCpuState::GetCurrentCpuIdlePercentBad()
{
    time_t nIdleDiff = CalcCpuIdleDiff2();

    //�������ʱ��, ����ʱ��/����ʱ�� = cpu���аٷֱ�
    time_t nSpendPass = CalcTimePass(m_timeOldArr[pos_cpu]);

    static time_t nKernelPre = 0;
    static time_t nUserPre = 0;

    //cout<<"���о���ʱ��: "<< nSpendPass<<endl;;
    float nPercent = 0;
    if(nSpendPass > 0)
    {
        nPercent = 1.0 * NANOSECOND100_TO_NANOSECOND(nIdleDiff) / MILLISECOND_TO_NANOSECOND(nSpendPass) * 100;
    }
    return nPercent / m_pHardwareQuery->GetCpuThreadCountTotal();
}

time_t CCpuState::CalcCpuUserKernelTotal()
{
    FILETIME ftIdle     = {0};
    FILETIME ftKernel   = {0};
    FILETIME ftUser     = {0};
    if(!::GetSystemTimes(&ftIdle, &ftKernel, &ftUser))
    {
        return 0;
    }
    //cout<<"-2idle:"<<FileTimeToInt64(ftIdle) << " kernel+User:" <<FileTimeToInt64(ftKernel)
    //+ FileTimeToInt64(ftUser) <<endl;
    return FileTimeToInt64(ftKernel) + FileTimeToInt64(ftUser);;
}

float CCpuState::GetCurrentCpuUsePercent()
{
    return NUM_PERCENT_MAX - GetCurrentCpuIdlePercent();   //����ʹ����
}
