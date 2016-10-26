#pragma once
#include "PAOptionUIBase.h"

/************************************************************************
    �ر�Ӧ�ó���Ĵ���
/************************************************************************/

class CPAOptUICloseApp :
    public CPAOptUIBase
{
    static const ENUM_DATA_DUTY enDuty = dn_close_app;
public:
    CPAOptUICloseApp(CPAUserSetting* pSC );
    ~CPAOptUICloseApp(void);
public:
public:
    virtual bool DoGetSaevData(tstring& strData );
    virtual bool Show();
    static CDataSettingBase* CreateOptData();
};




/************************************************************************
    �Ƿ���ϵͳ����
/************************************************************************/

class CPAOptUILaunchAsBoot :
    public CPAOptUIBase
{
public:
    static const ENUM_DATA_DUTY enDuty = dn_launch_as_boot;
    CPAOptUILaunchAsBoot(CPAUserSetting* pSC );
    ~CPAOptUILaunchAsBoot(void);
public:
    virtual bool DoGetSaevData(tstring& strData );
    virtual bool Show();
    static CDataSettingBase* CreateOptData();
};




/************************************************************************
    �Ƿ񱣴�Ӧ�ð�װ��
/************************************************************************/

class CPAOptUIAppSaveOpt :
    public CPAOptUIBase
{
    static const ENUM_DATA_DUTY enDuty = dn_app_save_setting;
public:
    CPAOptUIAppSaveOpt(CPAUserSetting* pSC );
    ~CPAOptUIAppSaveOpt(void);
public:
    virtual bool DoGetSaevData(tstring& strData );
    virtual bool Show();
    static CDataSettingBase* CreateOptData();
};


/************************************************************************
    �Ƿ񱣴�Ӧ�ð�װ��
/************************************************************************/

class CPAOptUIAppSavePath :
    public CPAOptUIBase
{
    static const ENUM_DATA_DUTY enDuty = dn_app_save_dir;

public:
    CPAOptUIAppSavePath(CPAUserSetting* pSC );
    ~CPAOptUIAppSavePath(void);
public:
    virtual bool DoGetSaevData(tstring& strData );
    virtual bool Show();
    static CDataSettingBase* CreateOptData();
};



/************************************************************************
    ����, �Ƿ����滭�������
/************************************************************************/

class CPAOptUITask :
    public CPAOptUIBase
{
    static const ENUM_DATA_DUTY enDuty = dn_task;

public:
    CPAOptUITask(CPAUserSetting* pSC );
    ~CPAOptUITask(void);
public:
    virtual bool DoGetSaevData(tstring& strData );
    virtual bool Show();
    static CDataSettingBase* CreateOptData();
};



/************************************************************************
    ������������,
/************************************************************************/

class CPAOptUIDriverSaveOpt :
    public CPAOptUIBase
{
    static const ENUM_DATA_DUTY enDuty = dn_driver_save_setting;

public:
    CPAOptUIDriverSaveOpt(CPAUserSetting* pSC );
    ~CPAOptUIDriverSaveOpt(void);
public:
    virtual bool DoGetSaevData(tstring& strData );
    virtual bool Show();
    static CDataSettingBase* CreateOptData();
};


/************************************************************************
    ��������Ŀ¼,
/************************************************************************/

class CPAOptUIDriverSavePath :
    public CPAOptUIBase
{
    static const ENUM_DATA_DUTY enDuty = dn_driver_save_dir;

public:
    CPAOptUIDriverSavePath(CPAUserSetting* pSC );
    ~CPAOptUIDriverSavePath(void);
public:
    virtual bool DoGetSaevData(tstring& strData );
    virtual bool Show();
    static CDataSettingBase* CreateOptData();
};



/************************************************************************
    ����¼��Ŀ¼,
/************************************************************************/

class CPAOptUIDesktopRecordPath :
    public CPAOptUIBase
{
public:
    static const ENUM_DATA_DUTY enDuty = dn_desktop_record_path;

    CPAOptUIDesktopRecordPath(CPAUserSetting* pSC );
    ~CPAOptUIDesktopRecordPath(void);
public:
    virtual bool DoGetSaevData(tstring& strData );
    virtual bool Show();
    static CDataSettingBase* CreateOptData();
};


/************************************************************************
    ��Ʒ����Ŀ¼,
/************************************************************************/

class CPAOptUIWorksSavePath:
    public CPAOptUIBase
{
public:
    static const ENUM_DATA_DUTY enDuty = dn_works_save_path;

    CPAOptUIWorksSavePath(CPAUserSetting* pSC );
    ~CPAOptUIWorksSavePath(void);
public:
    virtual bool DoGetSaevData(tstring& strData );
    virtual bool Show();
    static CDataSettingBase* CreateOptData();
};



/************************************************************************
    �ֿⱣ��Ŀ¼,
/************************************************************************/

class CPAOptUIFontLibSavePath:
    public CPAOptUIBase
{
public:
    static const ENUM_DATA_DUTY enDuty = dn_fontLib_save_path;

    CPAOptUIFontLibSavePath(CPAUserSetting* pSC );
    ~CPAOptUIFontLibSavePath(void);
public:
    virtual bool DoGetSaevData(tstring& strData );
    virtual bool Show();
    static CDataSettingBase* CreateOptData();
};



/************************************************************************
    ������ʽ
/************************************************************************/

class CPAOptUIUpdateType:
    public CPAOptUIBase
{
public:
    static const ENUM_DATA_DUTY enDuty = dn_update_type;

    CPAOptUIUpdateType(CPAUserSetting* pSC );
    ~CPAOptUIUpdateType(void);
public:
    virtual bool DoGetSaevData(tstring& strData );
    virtual bool Show();
    static CDataSettingBase* CreateOptData();
};



/************************************************************************
    �������ʱ��������
/************************************************************************/

class CPAOptUIFlowWndAsBoot:
    public CPAOptUIBase
{
public:
    static const ENUM_DATA_DUTY enDuty = dn_flow_auto_open;

    CPAOptUIFlowWndAsBoot(CPAUserSetting* pSC );
    ~CPAOptUIFlowWndAsBoot(void);
public:
    virtual bool DoGetSaevData(tstring& strData );
    virtual bool Show();
    static CDataSettingBase* CreateOptData();
};




/************************************************************************
    ʼ�ձ�������������ǰ��
/************************************************************************/

class CPAOptUIFlowTopWnd:
    public CPAOptUIBase
{
public:
    static const ENUM_DATA_DUTY enDuty = dn_flow_top_wnd;

    CPAOptUIFlowTopWnd(CPAUserSetting* pSC );
    ~CPAOptUIFlowTopWnd(void);
public:
    virtual bool DoGetSaevData(tstring& strData );
    virtual bool Show();
    static CDataSettingBase* CreateOptData();
};