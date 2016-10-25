#pragma once
#include "BackEndCollectDef.h"
#include "PAXmlUserHobbyDef.h"
#include <memory>
class CThreadDetection;
class CUserInfoGain;

class CDataConvert;
class CMDHPAssist;
class CUploadUserHobby;

using namespace std;

class CBackEndWorker
{
public:
    CBackEndWorker(void);
    ~CBackEndWorker(void);
public:
    bool Init();
    /************************************************************************
        fun:    ��ȡ�û�����ϵͳ��һЩ��Ϣ, ��ϵͳ�汾�� ���ϴ���ƽ̨
        param: 
        remark: 
    ************************************************************************/
    bool GetLocalInfoAndUpload();
    bool UploadUserHobby();
        
    bool AddUseTimes(ENUM_DATA_DUTY_UH dDuty);
    bool StartMonitor();
    bool StopMonitor();

private:
    bool CountBtnUse();
    bool CountSoftUse();
private:
    auto_ptr<CThreadDetection>           m_pThreadMonitor;
    //CThreadDetection*               m_pThreadMonitor;
    //CUploadUserHobby*                   m_pUploadHobby;
    auto_ptr<CUploadUserHobby>           m_pUploadHobby;
    //CUserInfoGain*            m_pUserInfo;
    //CUserInfoGain*              m_pUserInfo;
    auto_ptr<CUserInfoGain>     m_pUserInfo;
    //CMDHPAssist*                m_pHPA;
    auto_ptr<CMDHPAssist>       m_pHPA;
};

