#include "StdAfx.h"
#include "UploadUserHobby.h"
#include "functional.h"

CUploadUserHobby::CUploadUserHobby(void)
{
    m_strHobbyFileDir   = _T("D:\\test\\DA");
}


CUploadUserHobby::~CUploadUserHobby(void)
{
}

bool CUploadUserHobby::Init()
{
    Create_Auto_Ptr(m_pUploadUtil, CUploadUtil);
    return true;
}

bool CUploadUserHobby::UploadUserHobbyData()
{
    if(!IsCanDo())
    {
        return true;
    }
    UploadAllHobbyData();
    return true;
}

bool CUploadUserHobby::IsCanDo()
{
    return true;

}

bool CUploadUserHobby::IsTimeUp()
{
    return true;

}

bool CUploadUserHobby::UploadAllHobbyData()
{
    //ö��ָ��Ŀ¼������ �ļ������ϸ�ʽ���ļ�
    FileEnumeration(m_strHobbyFileDir.c_str(), false, true, &CUploadUserHobby::DealFileFunc
        , this);
    return true;
    
}

bool CUploadUserHobby::DealFileFunc( tcpchar lpFileOrPath, void* pUserData )
{
    //��ÿ���ļ������ϴ�, ɾ������

    CUploadUserHobby* pHobby = static_cast<CUploadUserHobby*>(pUserData);
    if(pHobby->IsFileHobby(lpFileOrPath))
    {
        pHobby->UploadDataFile(lpFileOrPath);
        pHobby->DeleteFile(lpFileOrPath);
    }
    
    return true;

}

bool CUploadUserHobby::UploadDataFile( tcpchar szFile )
{
    TRACE(_T("UPLOAD--"));
    TRACE(szFile);
    TRACE(_T("\n"));

    //�ϴ�����������ʵ��
        //  m_pUploadUtil->Upload(szFile);

    return true;
    
}

bool CUploadUserHobby::IsFileHobby( tcpchar lpFileOrPath )
{
    tstring strFilePath(lpFileOrPath);
    /* TODO: �ж��ļ��Ƿ�����û�ϰ���ļ����Ĺ���*/    
    if(strFilePath.find(_T("2")) != string::npos 
        && strFilePath.find(_T(".clt")) != string::npos )
    {
        return true;
    }
    return false;
    
}

bool CUploadUserHobby::DeleteFile( tcpchar lpFileOrPath )
{
    TRACE(_T("delete--"));
    TRACE(lpFileOrPath);
    TRACE(_T("\n"));
    return true;
    
}

/**************************************** �ϴ��������ʵ�� ****************************************/

bool CUploadUtil::Upload( tcpchar szFile )
{
    //TODO: ��ȡ���ļ���ʱ��
    return true;

}
