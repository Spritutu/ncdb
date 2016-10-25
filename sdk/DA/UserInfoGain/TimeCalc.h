#pragma once

/************************************************************************
    fun:    ʱ�������, �ڲ�ά�� ʱ��� �Ƿ���Ч�ı�ʶ. 
    remark: �������� ��Ҫ ����������ֵ֮�����, �����п��ؿɹر�/���������
************************************************************************/
class CTimeCalc
{
    typedef time_t TimeType;
public:
    CTimeCalc(void);
    ~CTimeCalc(void);
public:
    bool SetInValid();
    //bool AddTime();
    bool SetOriginTime(TimeType t);
    bool SetValid();
    TimeType GetDiff( time_t tTimeMonitor );
    bool IsValid();
    void SetState( TimeType tTime, bool bValid );
private:
    bool                    m_bValid;   
    TimeType                m_tTimePrev;
};

