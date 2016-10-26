#pragma once
#include "PiTypeDef.h"
#include "ResCommon.h"
#include "database/DBOperator.h"
#include "ThreadLight.h"
#define MSADO15 "c:\program files\common files\system\ado\msado15.dll"
#import MSADO15 no_namespace rename("EOF","adoEOF")

class CSql;
class CLock;
class CSignal;
typedef list<CSql*>		LST_SQL;
//class CDatabase;
class CSql
{
public:	
	CSql()
	{
		m_nIndex++;
	}
	/*CSql(const CSql& sql)
	{
		
	}*/
public:
	tstring		m_strSql;
	_RecordsetPtr       m_pRsP;                  //�����ѯ�����
	static UNINT			m_nIndex;		//����
};
class CDBThread : public CThreadLight
{
public:
	typedef ns_pi_common::CDataBase CDataBase;
	CDBThread(void);
	~CDBThread(void);
public:
	bool Init();
	bool UnInit();
	bool SetConnectSql(tcpchar szSql);
	/*	fun: ��Ӳ�ѯ��䵽��ִ�ж���*/
	bool AddQuery(CSql& sql);
	bool Query( CSql& sql ) ;

	/*	fun: ��Ӳ�ѯ��䵽��ִ�ж���*/
	bool AddExecute(CSql& sql);
	bool Execute(CSql& sql);
	bool AddSql( CSql& sql );
	void SetNoDB(bool val) { m_bNoDB = val; }
private:
	virtual DWORD DoWork() ;
private:
	LST_SQL						m_lstSqlNeedRun;
	auto_ptr<CDataBase>			m_pDB;
	auto_ptr<CLock>				m_pLockSql;
	auto_ptr<CLock>			m_pLockDB;
	auto_ptr<CSignal>			m_Sign;

	tstring						m_strSqlConnect;
	bool						m_bNoDB;		//�Ƿ�������ݿ����
	
};

void SaveError(StringCRef strErr);