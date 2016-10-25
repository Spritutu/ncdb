#include "StdAfx.h"
#include "LogSpilit.h"
#include "SingleLog.h"
#include "LogOpr.h"
#include "PiTypeDef.h"
#include "FileStrOp.h"
#include "functional.h"
#include <assert.h>
#include "define_gnl.h"
#include "PiTime.h"
#include "StrCoding.h"
Pi_NameSpace_Using
CLogSpilit::CLogSpilit(void)
{
}

CLogSpilit::~CLogSpilit(void)
{
}

bool CLogSpilit::Init()
{
    return CFileOpr::Init();
}

bool CLogSpilit::UnInit()
{
    return CFileOpr::UnInit();
}

bool CLogSpilit::OpenTodayLog(tcpchar szPath)
{
	m_strDate = CPiTime::GetLocalDate();
    return CLogOpr::OpenTodayLog(szPath);
}


void CLogSpilit::PartLogFile()
{
    //һ���ļ���ౣ��һ�������
    /*if(m_iParam.bSplitEveryDay && m_strDate != CPiTime::GetLocalDate())
    {
        string strDir = CFileStrOp::ExtractFileDir(CLogOpr::GetFileName());//�õ�֮ǰ��logĿ¼
        if(!CLogSpilit::OpenTodayLog(strDir.c_str()))
        {
            //log ��������
            CLogOpr::WriteLogWithDate(CLogOpr::GetErrDesc());
        }
    }
    else if (CLogOpr::GetFileSize() >= m_iParam.nMaxSize)    //���ƴ�С
    {
        string strFileFullPath = CLogOpr::GetFileName();
        string strNewTitle = CFileStrOp::GetNextFileName(strFileFullPath.c_str());

        if(!CLogOpr::Open(CFileStrOp::ExtractFileDir(strFileFullPath) + strNewTitle, "a", _SH_DENYWR))
        {
            assert(INFO_ERROR "����־�ļ���ʧ��");
        }
        else
        {
            this->PartLogFile();
        }
    }*/
}


DWORD CLogSpilit::WriteLog(tcpchar data)
{
    assert(data && "д��־���ַ����ǿ�ֵ");

    //TODO:���ļ�//PartLogFile();
    DWORD dwRet = this->WriteLogWithDate(data);
    return dwRet;
}

DWORD CLogSpilit::WriteLogPure(tcpchar data)
{
    //TODO:���ļ�//PartLogFile();
    DWORD dwRet = CLogOpr::WriteLog(data);
    return dwRet;
}

DWORD CLogSpilit::WriteLogPure(StringCRef data)
{
    return CLogSpilit::WriteLogPure(data.c_str());
}
DWORD CLogSpilit::WriteLog(StringCRef data)
{
    return WriteLog(data.c_str());
}


bool CLogSpilit::SetParam( const INIT_PARAM& iParam )
{
    m_iParam = iParam;
    return true;
}
