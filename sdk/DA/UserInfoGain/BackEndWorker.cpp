#include "StdAfx.h"
#include "BackEndWorker.h"
#include "ThreadDetection.h"
#include "UserInfoGain.h"
//#include "DataConvert.h"
#include "MDHandle.h"
#include "UploadUserHobby.h"
#include "ResCommon.h"
CBackEndWorker::CBackEndWorker(void)
{
}


CBackEndWorker::~CBackEndWorker(void)
{
    TRACE(_T("END"));
}

bool CBackEndWorker::Init()
{
    Create_Auto_Ptr(m_pUserInfo, CUserInfoGain);
    //m_pUserInfo = new CUserInfoGain;
    m_pUserInfo->Init();


    Create_Auto_Ptr(m_pHPA, CMDHPAssist);
    //m_pHPA = new CMDHPAssist;
    m_pHPA->Init();


    Create_Auto_Ptr(m_pThreadMonitor, CThreadDetection);
    //m_pThreadMonitor = new CThreadDetection;
    m_pThreadMonitor->Init();

    Create_Auto_Ptr(m_pUploadHobby, CUploadUserHobby);
    //m_pUploadHobby = new CUploadUserHobby;
    m_pUploadHobby->Init();

    //�ϴ������û���Ϣ
    GetLocalInfoAndUpload();
    this->UploadUserHobby();          // �ϴ��û����ʹ��ϰ��, �ڲ��ж�ʱ����ϴ�����

    this->StartMonitor();             //��ʼ������ʹ��ʱ���ʱ��
    return true;

}

bool CBackEndWorker::GetLocalInfoAndUpload()
{
    
    //���������ϸĽӿ�
    
    return true;

}

bool CBackEndWorker::CountBtnUse()
{
    return true;

}

bool CBackEndWorker::CountSoftUse()
{
    return true;

}

bool CBackEndWorker::StartMonitor()
{
    m_pThreadMonitor->Start();
    
    return true;
    
}

bool CBackEndWorker::AddUseTimes( ENUM_DATA_DUTY_UH dDuty )
{
    m_pHPA->SetCountType(dDuty);
    m_pHPA->HandleCount();

    return true;

}

bool CBackEndWorker::UploadUserHobby()
{
    m_pUploadHobby->UploadUserHobbyData();
    return true;
}

bool CBackEndWorker::StopMonitor()
{
    m_pThreadMonitor->Stop();
    return true;
    
}
