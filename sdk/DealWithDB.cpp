
//===========================================================================================
//CADODataBase���ʵ���ļ�
//���ڣ�2011-3-2
//���ߣ�Seven
//===========================================================================================
#include "stdafx.h"
#include "DealWithDB.h"
//#include "GlobalFile.h"
#include "functional.h"
#include <ATLComTime.h>
#include "RDini.h"
#include "define.h"
#include "doString.h"
#include <string>
#include "SingleLog.h"
using namespace std;

static CLogOpr* g_pSingleLog;
//===========================================================================================
//���캯��
CADODataBase::CADODataBase()
{
	bOpenDB = FALSE;
	
	InitializeCriticalSection(&csDB);

    wstring strConfig = GetCurrentDirIniName();
	CRDIni ini(strConfig.c_str());
	ini.Init();
	wstring username = ini.ReadParam(L"database", L"username");
	wstring password = ini.ReadParam(L"database", L"password");
	wstring source	= ini.ReadParam(L"database", L"source");
	SetConnectStr(ws2s(username).c_str(), ws2s(password).c_str(), ws2s(source).c_str());
	m_strErrorMsg = L"";

	g_pSingleLog = CSinglePattern<CLogOpr>::GetObj();
}

//===========================================================================================
//��������
CADODataBase::~CADODataBase()
{
	if (bOpenDB)
	{
		CloseDB();
	}
	DeleteCriticalSection(&csDB);
}

//===========================================================================================
//��ʼ����ʼ��Com��
BOOL CADODataBase::InitDB(void)
{
	if (bOpenDB)
	{
		return TRUE;
	}
	if ( CoInitialize( NULL ) != 0 )
	{
		return FALSE;
	}
	
	return TRUE;
}

//===========================================================================================
//��ȡ���ݿ��Ƿ��Ѿ�����
BOOL CADODataBase::GetLink(void)
{
	return bOpenDB;
}

BOOL CADODataBase::ReSetCnState(void)
{
	BOOL bTemp = bOpenDB;
	bOpenDB = FALSE;
	return bTemp;

}
//===========================================================================================
//�������ݿ�
BOOL CADODataBase::ConnectionDB(void)
{
	if (bOpenDB)
	{
		return TRUE;
	}
	try
	{	
		//����һ
		//m_pConnection.CreateInstance( __uuidof(Connection) );
		//������

		m_pConnection.CreateInstance("ADODB.Connection");
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pCommand.CreateInstance("ADODB.Command");

		m_pConnection->ConnectionString = (_bstr_t)m_strConn.c_str();
		
		HRESULT hr = m_pConnection->Open( (""), (""), (""), NULL ); //adConnectUnspecified
		if ( SUCCEEDED( hr ) )
		{
			m_pCommand->ActiveConnection = m_pConnection;
			bOpenDB = TRUE;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	catch(_com_error &ce)
	{
        wchar_t cTemp[500] = {0};

        wsprintf(cTemp, L"���ݿ����Ӵ���: mearning = %s;Code = %08lx;Description=%s", (wchar_t*)ce.ErrorMessage(), ce.Error(), (wchar_t*)ce.Description());
        //g_Log.Erro("���ݿ����Ӵ���!%s", strLogErr);
        m_strErrorMsg = cTemp;
        g_pSingleLog->WriteLog(m_strConn.c_str());
        g_pSingleLog->WriteLog(string(ws2s(m_strErrorMsg)).c_str());
		//string strLogErr;
		//strLogErr.Format(L"mearning = %s;Code = %08lx;Description=%s", e.ErrorMessage(), e.Error(), (TCHAR*)e.Description());

		return FALSE;
	}
}

//===========================================================================================
//�Ͽ����ݿ������
void CADODataBase::CloseDB(void)
{
	if (bOpenDB)
	{
		m_pConnection->Close();
		m_pConnection.Release();
		if ( m_pRecordset )
			m_pRecordset.Release();
		m_pCommand.Release();
	}
	bOpenDB = FALSE;
	
	CoUninitialize();
}

//===========================================================================================
//���²���,�½�,ɾ��,�޸�
BOOL CADODataBase::ADOUpdata(const string& strSQL)
{
	if (!bOpenDB)
	{    
		return FALSE;
	}

	_CommandPtr		tmpCommand;
	BOOL	bRet = FALSE;

	EnterCriticalSection(&csDB);
	try
	{
		tmpCommand = m_pCommand;
		tmpCommand->CommandText = (_bstr_t)strSQL.c_str();
		tmpCommand->Execute(NULL,NULL,adCmdText);          //ִ�в���
		bRet = TRUE;
	}
	catch (_com_error &ce)
	{
		wchar_t cTemp[500] = {0};

		wsprintf(cTemp, L"mearning = %s;Code = %08lx;Description=%s", (wchar_t*)ce.ErrorMessage(), ce.Error(), (wchar_t*)ce.Description());
		//g_Log.Erro("���ݿ���´���!%s", strLogErr);
		m_strErrorMsg = cTemp;
		bRet = FALSE;
        LeaveCriticalSection(&csDB);
		throw(string(ws2s(m_strErrorMsg)));
	}
	LeaveCriticalSection(&csDB);

	return bRet;
}


void CADODataBase::SetConnectStr(const char* username, const char* pw, const char* source)
{
	char cTemp[200] = {0};
	sprintf_s(cTemp,sizeof(cTemp),"Provider=OraOLEDB.Oracle.1;Persist Security Info=True;User ID=%s;Password = %s;Data Source=%s",
		username, pw, source);
	m_strConn = cTemp;
}
//===========================================================================================
//���ز�ѯ�����
_RecordsetPtr CADODataBase::ADOSelect(string strSQL)
{
	if (!bOpenDB)
	{
		return NULL;
	}

	_RecordsetPtr		tmpRecordset;
	_CommandPtr			tmpCommand;

	EnterCriticalSection(&csDB);
	try
	{
		tmpCommand = m_pCommand;
		tmpCommand->CommandText = (_bstr_t)strSQL.c_str();
		tmpRecordset = tmpCommand->Execute(NULL,NULL,adCmdText);
	}
	catch (_com_error &ce)
	{
		//string strLogErr;
		//strLogErr.Format(L"mearning = %s;Code = %08lx;Description=%s", ce.ErrorMessage(), ce.Error(), (TCHAR*)ce.Description());
		////g_Log.Erro("���ݿ��ѯ����!%s", strLogErr);
		//m_strErrorMsg = strLogErr;
	}
	LeaveCriticalSection(&csDB);

	return tmpRecordset;
}

_variant_t CADODataBase::GetSelectValue(string strSql,const char* pColumn)
{
	_RecordsetPtr rs = ADOSelect(strSql);
	
	_variant_t vrtDeviceType;
	_variant_t vrtDZ;
	vrtDeviceType = rs->GetCollect(pColumn);
	/*if (pRs)
	{
		*pRs = rs;
	}*/
	
	return vrtDeviceType;
}


double CADODataBase::GetSelectValueNum(string strSql, const char* pColumn)
{
	_variant_t vrtRet = GetSelectValue(strSql, pColumn);
	return vrtRet.dblVal;
}

string CADODataBase::GetSelectValueStr(string strSql,const  char* pColumn)
{
	_variant_t vrtRet = GetSelectValue(strSql, pColumn);
	return (char*)vrtRet.bstrVal;
}

//===========================================================================================
//д�ռǵ����ݿ⣬��������һ���ռǼ�¼
//CarNumber�����ƺ��룬strPlace���ص㣬strContent������
void CADODataBase::MakeDBLog(string strLogContent, int logType)
{
	if(bOpenDB)
	{
		try
		{
			/*COleDateTime cur;
			cur = COleDateTime::GetCurrentTime();*/
			
			//string strTime = cur.Format(_T("%Y-%m-%d %H:%M:%S"));
			string strLogSQL;

			string strTime = GetLocalDateTime();

			/*strLogSQL.Format(_T("INSERT INTO %s (LogID, LogTime, LogType, LogContent) \
								VALUES (LOGID.NEXTVAL, to_date('%s','yyyy-mm-dd hh24:mi:ss'), \
								%d,	'%s')"), m_LogTable, strTime.c_str(), logType, strLogContent.c_str() );*/
			ADOUpdata(strLogSQL);  //����һ����¼
		}
		catch (_com_error *e)
		{
			return;
		}
	}
}

//===========================================================================================
//���ش�����Ϣ
wstring CADODataBase::GetErrorMsg(void)
{
	return m_strErrorMsg;
}