#include "StdAfx.h"
#include "PAOptionUI.h"



/************************************************************************
    �ر�Ӧ�ó���Ĵ���
/************************************************************************/


CPAOptUICloseApp::CPAOptUICloseApp( CPAUserSetting* pSC )
    :CPAOptUIBase(pSC)
{
    SetDataDuty(enDuty);
}


CPAOptUICloseApp::~CPAOptUICloseApp(void)
{
}


bool CPAOptUICloseApp::DoGetSaevData( tstring& strData )
{
    //���ݽ���, ��ȡ��������ַ���
    strData = _T("cCloseApp");
    return true;
}


bool CPAOptUICloseApp::Show()
{
    tstring strData = GetData();
    TRACE(strData.c_str());
    TRACE(_T("\n"));
    return true;

}

CDataSettingBase* CPAOptUICloseApp::CreateOptData()
{
    return new COptDataEnum(NULL, enDuty);
}



/************************************************************************
    �Ƿ���ϵͳ����
/************************************************************************/


CPAOptUILaunchAsBoot::CPAOptUILaunchAsBoot( CPAUserSetting* pSC ) 
    :CPAOptUIBase(pSC)
{
    SetDataDuty(enDuty);
}


CPAOptUILaunchAsBoot::~CPAOptUILaunchAsBoot(void)
{
}


bool CPAOptUILaunchAsBoot::DoGetSaevData( tstring& strData )
{
    //���ݽ���, ��ȡ��������ַ���
    strData = _T("cLaunchAsBoot");
    return true;
}


bool CPAOptUILaunchAsBoot::Show()
{
    tstring strData = GetData();
    TRACE(strData.c_str());
    TRACE(_T("\n"));
    return true;

}

CDataSettingBase* CPAOptUILaunchAsBoot::CreateOptData()
{
    return new COptDataEnum(NULL, enDuty);
}





/************************************************************************
    �Ƿ񱣴�Ӧ�ð�װ��
/************************************************************************/

CPAOptUITask::CPAOptUITask( CPAUserSetting* pSC ) 
    :CPAOptUIBase(pSC)
{
    SetDataDuty(enDuty);
}


CPAOptUITask::~CPAOptUITask(void)
{
}

bool CPAOptUITask::DoGetSaevData( tstring& strData )
{
    //���ݽ���, ��ȡ��������ַ���
    strData = _T("cTask");
    return true;
}


bool CPAOptUITask::Show()
{
    tstring strData = GetData();
    TRACE(strData .c_str());
    TRACE(_T("\n"));
    return true;

}

CDataSettingBase* CPAOptUITask::CreateOptData()
{
    return new COptDataEnum(NULL, enDuty);
}



CPAOptUIAppSaveOpt::CPAOptUIAppSaveOpt( CPAUserSetting* pSC ) 
    :CPAOptUIBase(pSC)
{
    SetDataDuty(enDuty);
}


CPAOptUIAppSaveOpt::~CPAOptUIAppSaveOpt(void)
{
}


bool CPAOptUIAppSaveOpt::DoGetSaevData( tstring& strData )
{
    //���ݽ���, ��ȡ��������ַ���
    strData = _T("cAppSaveOpt");
    return true;
}


bool CPAOptUIAppSaveOpt::Show()
{
    tstring strData = GetData();
    TRACE(strData.c_str());
    TRACE(_T("\n"));
    return true;

}

CDataSettingBase* CPAOptUIAppSaveOpt::CreateOptData()
{
    return new COptDataEnum(NULL, enDuty);

}



/************************************************************************
    �Ƿ񱣴�Ӧ�ð�װ��
/************************************************************************/

CPAOptUIAppSavePath::CPAOptUIAppSavePath( CPAUserSetting* pSC ) 
    :CPAOptUIBase(pSC)
{
    SetDataDuty(enDuty);
}


CPAOptUIAppSavePath::~CPAOptUIAppSavePath(void)
{
}


bool CPAOptUIAppSavePath::DoGetSaevData( tstring& strData )
{
    //���ݽ���, ��ȡ��������ַ���
    strData = _T("cAppSavePath");
    return true;
}


bool CPAOptUIAppSavePath::Show()
{
    tstring strData = GetData();
    TRACE(strData.c_str());
    TRACE(_T("\n"));
    return true;

}

CDataSettingBase* CPAOptUIAppSavePath::CreateOptData()
{
    return new COptDataPath(NULL, enDuty);
}



/************************************************************************
    ����, �Ƿ����滭�������
/************************************************************************/

/************************************************************************
    ������������,
/************************************************************************/

CPAOptUIDriverSaveOpt::CPAOptUIDriverSaveOpt( CPAUserSetting* pSC ) 
    :CPAOptUIBase(pSC)
{
    SetDataDuty(enDuty);
}


CPAOptUIDriverSaveOpt::~CPAOptUIDriverSaveOpt(void)
{
}

bool CPAOptUIDriverSaveOpt::DoGetSaevData( tstring& strData )
{
    //���ݽ���, ��ȡ��������ַ���
    strData = _T("cDriverSaveOpt");
    return true;
}


bool CPAOptUIDriverSaveOpt::Show()
{
    tstring strData = GetData();
    TRACE(strData.c_str());
    TRACE(_T("\n"));
    return true;

}

CDataSettingBase* CPAOptUIDriverSaveOpt::CreateOptData()
{
    return new COptDataEnum(NULL, enDuty);
}




/************************************************************************
    ��������Ŀ¼,
/************************************************************************/

CPAOptUIDriverSavePath::CPAOptUIDriverSavePath( CPAUserSetting* pSC ) 
    :CPAOptUIBase(pSC)
{
    SetDataDuty(enDuty);
}

CPAOptUIDriverSavePath::~CPAOptUIDriverSavePath(void)
{
}

bool CPAOptUIDriverSavePath::DoGetSaevData( tstring& strData )
{
    //���ݽ���, ��ȡ��������ַ���
    strData = _T("cDriverSavePath");
    return true;
}

bool CPAOptUIDriverSavePath::Show()
{
    tstring strData = GetData();
    TRACE(strData.c_str());
    TRACE(_T("\n"));
    return true;

}

CDataSettingBase* CPAOptUIDriverSavePath::CreateOptData()
{
    return new COptDataPath(NULL, enDuty);
}



/************************************************************************
    ����¼��Ŀ¼,
/************************************************************************/

CPAOptUIDesktopRecordPath::CPAOptUIDesktopRecordPath( CPAUserSetting* pSC ) 
    :CPAOptUIBase(pSC)
{
    SetDataDuty(enDuty);
}

CPAOptUIDesktopRecordPath::~CPAOptUIDesktopRecordPath(void)
{
}

bool CPAOptUIDesktopRecordPath::DoGetSaevData( tstring& strData )
{
    //���ݽ���, ��ȡ��������ַ���
    strData = _T("cDesktopRecordPath");
    return true;
}

bool CPAOptUIDesktopRecordPath::Show()
{
    tstring strData = GetData();
    TRACE(strData.c_str());
    TRACE(_T("\n"));
    return true;

}

CDataSettingBase* CPAOptUIDesktopRecordPath::CreateOptData()
{
    return new COptDataPath(NULL, enDuty);
}


/************************************************************************
    ��Ʒ����Ŀ¼,
/************************************************************************/

CPAOptUIWorksSavePath::CPAOptUIWorksSavePath( CPAUserSetting* pSC ) 
    :CPAOptUIBase(pSC)
{
    SetDataDuty(enDuty);
}

CPAOptUIWorksSavePath::~CPAOptUIWorksSavePath(void)
{
}

bool CPAOptUIWorksSavePath::DoGetSaevData( tstring& strData )
{
    //���ݽ���, ��ȡ��������ַ���
    strData = _T("cWorksSavePath");
    return true;
}

bool CPAOptUIWorksSavePath::Show()
{
    tstring strData = GetData();
    TRACE(strData.c_str());
    TRACE(_T("\n"));
    return true;

}

CDataSettingBase* CPAOptUIWorksSavePath::CreateOptData()
{
    return new COptDataPath(NULL, enDuty);
}



/************************************************************************
    ��Ʒ����Ŀ¼,
/************************************************************************/

CPAOptUIFontLibSavePath::CPAOptUIFontLibSavePath( CPAUserSetting* pSC ) 
    :CPAOptUIBase(pSC)
{
    SetDataDuty(enDuty);
}

CPAOptUIFontLibSavePath::~CPAOptUIFontLibSavePath(void)
{
}

bool CPAOptUIFontLibSavePath::DoGetSaevData( tstring& strData )
{
    //���ݽ���, ��ȡ��������ַ���
    strData = _T("cFontLibSavePath");
    return true;
}

bool CPAOptUIFontLibSavePath::Show()
{
    tstring strData = GetData();
    TRACE(strData.c_str());
    TRACE(_T("\n"));
    return true;

}

CDataSettingBase* CPAOptUIFontLibSavePath::CreateOptData()
{
    return new COptDataPath(NULL, enDuty);
}




/************************************************************************
    ������ʽ
/************************************************************************/

CPAOptUIUpdateType::CPAOptUIUpdateType( CPAUserSetting* pSC ) 
    :CPAOptUIBase(pSC)
{
    SetDataDuty(enDuty);
}

CPAOptUIUpdateType::~CPAOptUIUpdateType(void)
{
}

bool CPAOptUIUpdateType::DoGetSaevData( tstring& strData )
{
    //���ݽ���, ��ȡ��������ַ���
    strData = _T("cUpdateType");
    return true;
}

bool CPAOptUIUpdateType::Show()
{
    tstring strData = GetData();
    TRACE(strData.c_str());
    TRACE(_T("\n"));
    return true;

}

CDataSettingBase* CPAOptUIUpdateType::CreateOptData()
{
    return new COptDataEnum(NULL, enDuty);
}




/************************************************************************
    �������ʱ��������
/************************************************************************/

CPAOptUIFlowWndAsBoot::CPAOptUIFlowWndAsBoot( CPAUserSetting* pSC ) 
    :CPAOptUIBase(pSC)
{
    SetDataDuty(enDuty);
}

CPAOptUIFlowWndAsBoot::~CPAOptUIFlowWndAsBoot(void)
{
}

bool CPAOptUIFlowWndAsBoot::DoGetSaevData( tstring& strData )
{
    //���ݽ���, ��ȡ��������ַ���
    strData = _T("cFlowWndAsBoot");
    return true;
}

bool CPAOptUIFlowWndAsBoot::Show()
{
    tstring strData = GetData();
    TRACE(strData.c_str());
    TRACE(_T("\n"));
    return true;

}

CDataSettingBase* CPAOptUIFlowWndAsBoot::CreateOptData()
{
    return new COptDataEnum(NULL, enDuty);
}



/************************************************************************
    �������ʱ��������
/************************************************************************/

CPAOptUIFlowTopWnd::CPAOptUIFlowTopWnd( CPAUserSetting* pSC ) 
    :CPAOptUIBase(pSC)
{
    SetDataDuty(enDuty);
}

CPAOptUIFlowTopWnd::~CPAOptUIFlowTopWnd(void)
{
}

bool CPAOptUIFlowTopWnd::DoGetSaevData( tstring& strData )
{
    //���ݽ���, ��ȡ��������ַ���
    strData = _T("cFlowTopWnd");
    return true;
}

bool CPAOptUIFlowTopWnd::Show()
{
    tstring strData = GetData();
    TRACE(strData.c_str());
    TRACE(_T("\n"));
    return true;

}

CDataSettingBase* CPAOptUIFlowTopWnd::CreateOptData()
{
    return new COptDataEnum(NULL, enDuty);
}