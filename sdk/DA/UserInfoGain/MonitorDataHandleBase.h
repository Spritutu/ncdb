#pragma once
#include "PiTypeDef.h"
#include "BackEndCollectDef.h"
#include "PAXmlUserHobbyDef.h"
#include <string>

//���̼�����ɴ�������
enum ENUM_FIELD
{
    f_count = 0,        //����
    f_time              //ʱ�����
};

typedef map<ENUM_FIELD, ENUM_DATA_DUTY_UH> LST_FIELD_DUTY;

using namespace std;

class CPAXmlUserHobby;
class CTimeCalc;
typedef tstring MonitorTask;

class CMonitorDataHandleBase
{
public:
    CMonitorDataHandleBase(void);
    virtual ~CMonitorDataHandleBase(void);
public:
    
    bool Init();
    virtual bool HandleDetectResult( TimeType tTimeMonitor, bool bExist );
    virtual bool HandleCount( bool bExist );

    /************************************************************************
        fun:    �߼��ϲ㴦��: ����ʱ��
        param: 
        remark: 
    ************************************************************************/
    virtual bool HandleTimeDuration( bool bExist, TimeType tTimeMonitor );
    virtual MonitorTask GetMonitorTask() = 0;

    /************************************************************************
        fun:    ʵ������ָ����ʱ��(s)�����ݿ���
        param: 
        remark: 
    ************************************************************************/
    virtual bool IncreaseTimesDuration(TimeType t );
    virtual bool InitDataDuty() = 0;
    virtual bool IncreaseCount();

    void SetDataDuty(ENUM_DATA_DUTY_UH duty);
    ENUM_DATA_DUTY_UH GetDataDuty();
    
    virtual tstring GetNewTimeStr( TimeType tAdd );
    bool AddFieldDuty( ENUM_FIELD enF, ENUM_DATA_DUTY_UH dd );

private:
    bool IsProcessNewCreate( bool bExist );
    void SaveDetectResult( bool bExist );
    bool BeginDealTimeDuration();
    bool BeginDealCount();

    bool SetDataDuty(ENUM_FIELD c);
    void TestTimeTransStr();
    
    bool IsCanIncreaseTime( bool bExist );
    void TestTimeCalc();
protected:
    CPAXmlUserHobby*                    m_pDB;
private:
    bool                        m_bExistPrev;
    ENUM_DATA_DUTY_UH           m_udDuty;
    auto_ptr<CTimeCalc>         m_pTimeCalc;
    LST_FIELD_DUTY              m_lstFieldDuty; //�����Ӧ��ְ��
};

