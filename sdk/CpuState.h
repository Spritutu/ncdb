#pragma once
#include <Windows.h>
#include <memory>
#define NUMBER_TIME_DATA_TYPE           7           //�м�����Ҫ��������ʱ�����ݵ����
class CHardwareQuery;
using namespace std;

class CCpuState
{
    enum TimeDataPos
    {
        pos_process = 0,
        pos_process_spend_pre,      //�����ϴ�ռ�õ�ʱ��
        pos_cpu,
        pos_cpu_idle_pre,       //cpu�ϴο��е�ʱ����, //�����㷨
        pos_cpu2_idle_pre,    
        pos_tick_count_pre,     //�ϴμ����ʱ����Ƶʱ���
        pos_cpu_userKernel_pre,     //�ϴε� sum(user+kernel) ��ʱ��
    };
public:
    CCpuState(void);
    ~CCpuState(void);

public:
    /************************************************************************
        fun: ��ʼ������
        parent: 
        remark: 
    ************************************************************************/
    bool Init();
    bool UnInit();
    /************************************************************************
        fun: ��ȡ��ǰ����ռ��cpu �İٷֱ�
        remark: ��һ�ε��û᷵��0. ռ����Ϊ����ʱ�����ڵ�Cpuռ����,  ȡ���ڵ��øýӿڵ�Ƶ��
    ************************************************************************/
    
    float GetCurrentProcessSpend();

    
     /************************************************************************
        fun:    ��ȡ��ǰcpu ���еİٷֱ�
        parent: 
        remark: 
    ************************************************************************/
    float GetCurrentCpuIdlePercent();
    float GetCurrentCpuUsePercent();

     /************************************************************************
        fun:    ��ȡcpu���аٷֱ�
        parent: 
        remark: ���Ϊ�ϴε��øýӿڵ�Ŀǰ���ʱ��������Ľ��
    ************************************************************************/
    float GetCurrentCpuIdlePercentBad();
private:
     /************************************************************************
        fun:    ��ȡ�����ϴε�ʱ��Ƭ����, cpu�Ŀ���ʱ����
        parent: 
        remark: 
    ************************************************************************/
    time_t CalcCpuIdleDiff();

    //��һ�����ݿ�
    time_t CalcCpuIdleDiff2();
    __int64 FileTimeToInt64(const FILETIME& time);
    time_t CalcProcessSpendTimeTotal();

     /************************************************************************
        fun:    ������̵�ǰռ��ʱ����ϴεĲ� ����������ռ��ʱ��
        parent: 
        remark: 
    ************************************************************************/
    time_t CalcProcessSpendTimeDiff();
    time_t CalcCpuIdleTotal();
    time_t CalcCpuUserKernelTotal();
    /************************************************************************
        fun: ���غ��ϴε�ʱ��� ����¼�µ�ǰʱ��
        parent: 
        remark: 
    ************************************************************************/
    time_t CalcTimePass(time_t& nOld);
private:
    time_t          m_timeOldArr[NUMBER_TIME_DATA_TYPE];
    HANDLE          m_hProcess;

    float           m_fCpuUsePercent;               //���һ�μ����cpuʹ����
    float           m_fCpuUseSelfProcessPercent;    //���һ�μ���� �����̵�cpuʹ����
    float           m_fCpuIdlePercent;               //���һ�μ����cpu������

    auto_ptr<CHardwareQuery>    m_pHardwareQuery;
};

