#pragma once
#include "MonitorSystemDef.h"
class CMonitorSystemBase
{
public:
    CMonitorSystemBase(void);
    virtual ~CMonitorSystemBase(void);
public:
    virtual UseStatus GetUseStatus() = 0;

    bool Init();
    bool AddNotifyWnd(WndID wndID);
    bool Notify();
    bool IsDataValid();

    bool SetDataValid(bool bValid);

    /**************************************** ���� ****************************************/
protected:
    void SetType(ENUM_MONITOR_DATA_TYPE dt);

private:
    virtual bool InitChild();
    /**************************************** ���� ****************************************/
protected:
    //UseStatus               m_UseStatus;
    void*                   m_pMonitorResultData;
    bool                            m_bDataValid;   //�����Ƿ���Ч, ��Ч�򲻷��ͳ�ȥ

private:
    WndID       m_WndNotify;
    ENUM_MONITOR_DATA_TYPE          m_enDataType;
};

