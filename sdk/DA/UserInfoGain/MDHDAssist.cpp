#include "StdAfx.h"
#include "MDHDAssist.h"
#include "MonitorDataHandleBase.h"
#include <assert.h>
//#include "DBData.h"


CMDHDAssist::CMDHDAssist(void)
{
}


CMDHDAssist::~CMDHDAssist(void)
{
}

bool CMDHDAssist::HandleCount()
{
    assert(GetDataDuty() != dnh_unKnown);

    this->IncreaseCount();
    return true;

}

bool CMDHDAssist::SetCountType( ENUM_DATA_DUTY_UH dd)
{
    SetDataDuty(dd);
    return true;

}

bool CMDHDAssist::InitDataDuty()
{
    SetDataDuty(dnh_unKnown);   //���ദ�����ְ�������, ��Ҫ�ⲿSetCountType����ְ������
    return true;
}

