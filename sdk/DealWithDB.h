
//===========================================================================================
//CADODataBase��Ķ����ļ�
//���ڣ�2011-3-2
//���ߣ�Seven
//===========================================================================================

#ifndef __DEALWITHDB_H__
#define __DEALWITHDB_H__

//#include <comdef.h>
//#include <atlbase.h>
#include <string>
using namespace std;
#pragma   warning(disable:4146)
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF"), rename("BOF","adoBOF")

class CADODataBase
{
public:
/*
	enum DBType
	{
		ORACLR_DB = 0,         //����Oracle���ݿ�
		SQL_SERVER_DB,         //����SQL_Server���ݿ�
		ACCESS_DB				//����Access���ݿ�
	};
*/
	_ConnectionPtr   m_pConnection;
	_RecordsetPtr    m_pRecordset;
	_CommandPtr      m_pCommand;
	string         m_strSQL;
	string         m_strConn;

public:
	CADODataBase();
	~CADODataBase();
	BOOL InitDB(void);
	BOOL ConnectionDB(void);
	void CloseDB(void);									//�رնϿ����ݿ�
	BOOL ADOUpdata(const string& strSQL);                  //���²���,�½�,ɾ��,�޸�string strCommand
	_RecordsetPtr ADOSelect(string strSQL);          //���ز�ѯ�����
	BOOL GetLink(void);
	BOOL ReSetCnState(void);
	wstring  GetErrorMsg(void);
	
	_variant_t GetSelectValue(string strSql, const char* pColumn);
	//_variant_t GetSelectValue(string strSql, const char* pColumn, _RecordsetPtr* pRs);
	double GetSelectValueNum(string strSql, const char* pColumn);
	string GetSelectValueStr(string strSql, const char* pColumn);
	
	//���ӵģ���ͨ�á�  **д�ռǵ����ݿ���
	string	m_LogTable;			//��־������֣����Ҫд��־������Ҫ��д
	string m_strLogContent;			//m_strContent����־����
	void MakeDBLog(string strLogContent = "", int logType=0);	//logType����־����(0��������־��1��������־)
	void SetConnectStr(const char* username, const char* pw, const char* source);
protected:
	CRITICAL_SECTION		csDB;

public:
	/*string m_userName;
	string m_pw;
	string m_Source;*/
private:
	BOOL		bOpenDB;
	wstring		m_strErrorMsg;	//������Ϣ
//	DBType   m_dbtype;

};

#endif //__DEALWITHDB_H__