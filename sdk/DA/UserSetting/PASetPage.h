#pragma once
#include "PASettingDef.h"
#include <list>
#include "SettingParam.h"
using namespace std;



class CPAOptUIBase;
class CPAXmlUserConfig;
class CPAUserSetting;
class COptionNotify;

typedef list<CPAOptUIBase*> LST_OPT_UI;

class CPAOptUIPageBase
{
public:
    CPAOptUIPageBase(COptionNotify* pNotify, CPAUserSetting* pUserSet );
    ~CPAOptUIPageBase(void);
public:
    bool Init();
    bool Notify();
    bool SaveAllSetting();
    bool ShowNewest();
    bool Show();
    void ModifySetting();
    bool AddOpt( CPAOptUIBase* pOptUI );
    ENUM_OPTION_PAGE GetPageFlag();
    virtual bool ReadAllSetting();
    virtual bool WriteAllSetting(void* pData);
protected:
    //virtual bool InitLayout() = 0;
    virtual bool InitSetItem() = 0;
    void SaveAllConfig();
protected:
    CPAUserSetting*         m_pSettingCol;
    ENUM_OPTION_PAGE        m_PageFlag;
private:
    LST_OPT_UI              m_lstOptUI;
    COptionNotify*          m_pOptNotify;

};



/************************************************************************
    ����ҳ��1, ��������
/************************************************************************/
class CPAOptUIPageGeneral
    :public CPAOptUIPageBase
{
public:
    CPAOptUIPageGeneral(COptionNotify* pNotify, CPAUserSetting* pUserSet );
    ~CPAOptUIPageGeneral(void);
public:
    virtual bool ReadAllSetting(void* pData);
    virtual bool WriteAllSetting(void* pData );
protected:
    virtual bool InitSetItem();
private:
    CSettingGeneralParam        m_SetParam;
//     CDASetUIBase*           m_dsLaunchAsBoot;
//     CDASetUIBase*           m_dsCloseApp;
};




/************************************************************************
    ����ҳ��2, Ӧ������
/************************************************************************/
class CPAOptUIPageApp
    :public CPAOptUIPageBase
{
public:
    CPAOptUIPageApp(COptionNotify* pNotify, CPAUserSetting* pUserSet );
    ~CPAOptUIPageApp(void);
public:

protected:
    virtual bool InitSetItem();
private:
    CSettingAppParam        m_paramApp;
};



/************************************************************************
    ����ҳ��3, ��������ҳ��
/************************************************************************/
class CPAOptUIPageUpdate
    :public CPAOptUIPageBase
{
public:
    CPAOptUIPageUpdate(COptionNotify* pNotify, CPAUserSetting* pUserSet );
    ~CPAOptUIPageUpdate(void);
public:

protected:
    virtual bool InitSetItem();
private:
};



/************************************************************************
    ����ҳ��4, ��������ҳ��
/************************************************************************/
class CPAOptUIPageFlow
    :public CPAOptUIPageBase
{
public:
    CPAOptUIPageFlow(COptionNotify* pNotify, CPAUserSetting* pUserSet );
    ~CPAOptUIPageFlow(void);
public:

protected:
    virtual bool InitSetItem();
private:
};