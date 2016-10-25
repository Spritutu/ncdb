#include "StdAfx.h"
#include "MDHandle.h"

/****************************** sai���̼���������� *******************************/

CMDHandleSai::CMDHandleSai(void)
{
}


CMDHandleSai::~CMDHandleSai(void)
{
}


bool CMDHandleSai::InitDataDuty()
{
    AddFieldDuty(f_count, dnh_sai_use_count);
    return true;

}

bool CMDHandleSai::IncreaseTimesDuration( TimeType t )
{
    //������ʹ��ʱ��
    return true;
}

MonitorTask CMDHandleSai::GetMonitorTask()
{
    
    //return _T("sai.exe");
    return _T("gvim.exe");//TODO:test

}

bool CMDHandleSai::HandleTimeDuration( bool , TimeType)
{
    /* ������ʹ��ʱ��*/
    return true;
}




/****************************** PA���̼���������� *******************************/

CMDHandlePA::CMDHandlePA(void)
{
}


CMDHandlePA::~CMDHandlePA(void)
{
}

bool CMDHandlePA::InitDataDuty()
{
    AddFieldDuty(f_count,   dnh_da_use_count);
    AddFieldDuty(f_time,    dnh_da_use_time);
    //SetDataDuty(f_count, dnh_sai_use_count);
    return true;

}

MonitorTask CMDHandlePA::GetMonitorTask()
{
    //return _T("pa.exe");
    return _T("QQ.exe");//TODO:TEST
}







/****************************** ps���̼���������� *******************************/

CMDHandlePS::CMDHandlePS(void)
{
}


CMDHandlePS::~CMDHandlePS(void)
{
}


bool CMDHandlePS::InitDataDuty()
{
    AddFieldDuty(f_count, dnh_ps_use_Count);
    return true;

}

MonitorTask CMDHandlePS::GetMonitorTask()
{
    
    //return _T("photoshop.exe");
    return _T("explorer.exe");//TODO:test

}

bool CMDHandlePS::HandleTimeDuration( bool , TimeType)
{
    /* ������ʹ��ʱ��*/
    return true;
}



/********************************** PA���ݴ��� *************************************/


CMDHPAssist::CMDHPAssist(void)
{
}


CMDHPAssist::~CMDHPAssist(void)
{
}

bool CMDHPAssist::HandleCount()
{
    assert(GetDataDuty() != dnh_unKnown);

    this->IncreaseCount();
    return true;

}

bool CMDHPAssist::SetCountType( ENUM_DATA_DUTY_UH dd)
{
    SetDataDuty(dd);
    return true;

}

bool CMDHPAssist::InitDataDuty()
{
    SetDataDuty(dnh_unKnown);   //���ദ�����ְ�������, ��Ҫ�ⲿSetCountType����ְ������
    return true;
}

MonitorTask CMDHPAssist::GetMonitorTask()
{
    assert(0 && "��ӿ�, Ϊ�˱���ͨ��, �ⲿ�������");
    MonitorTask taskSai = _T("xxx.exe");
    return taskSai;
}



