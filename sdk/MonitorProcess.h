#pragma once
#include "PiTypeDef.h"
#include <list>

class CMonitorDataHandleBase;

using namespace std;
typedef list<CMonitorDataHandleBase*>   LST_MD_HANDLE;

class CMonitorProcess
{

public:
    CMonitorProcess(void);
    ~CMonitorProcess(void);
public:
    bool Init();
    bool UnInit();
    
    
    /************************************************************************
        fun: �������Ӽ�����Ľӿ�, ͨ������ AddMonitor ����Ҫ���ӵ�����
        param: 
        remark: 
    ************************************************************************/
    virtual void InitTask() = 0;

    bool AddMonitor(CMonitorDataHandleBase* pHandle);
    bool Notify(time_t tDeleteTime, bool bExist);
    bool DetectAllProcess();
    bool DetectProcess( tcpchar szProcessName, bool& bExist );


private:
    LST_MD_HANDLE               m_mdHandle;
    CMonitorDataHandleBase*         m_pCurrentDetectHandle; //���ö���
    
};

