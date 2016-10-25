/*
1. ��������������⣬ �����ip������, ���ݿ��������� 
    1. ��д�����ʧ��
    2. ʧȥ��ϵ 
    �Ĵ��� ��������� ���������Щ���� ����������
*/
#pragma once
//#define MSADO15 "c:\msado15.dll"
#define MSADO15 "c:\program files\common files\system\ado\msado15.dll"
//#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")
#import MSADO15 no_namespace rename("EOF","adoEOF")
//using namespace ADODB;
//class _RecordsetPtr;
//class _CommandPtr;
//#include <string>
#include <vector>
#include "ResCommon.h"
#include "PiTypeDef.h"
using namespace std;
#define _WIN32_DCOM
#define ERROR_LENGTH 500
class CLock;

namespace ns_pi_common
{
	typedef void (*FunSaveErrorInfo)(StringCRef );
class CDBReConnect
{
public:
    CDBReConnect(int nCodeR, tstring strErr)
	{
		m_strErrDesc = strErr;
		m_nCode = nCodeR;
	};
public:
    tstring m_strErrDesc;
	int		m_nCode;
};

typedef list<CDBReConnect>	LST_RE_CONNECT;

struct DB_Param
{
    bool    bReCn;
    long*   plErrorCode;
    byte    byCodeCount;
};

class CDataBase
{
public:
    enum DB_EXECUTE_STATE{
        DB_OK = 0, 
        DB_ERR_NET, 
        //DB_ERR_ALRROW,  //�����С���󣬿��Ժ���
        DB_ERR_UNKNOW   //δ֪����
    };

public:
    CDataBase(void);
    ~CDataBase(void);

public:
	bool Init(void);

	

	bool                    UnInit(void);


    //void                    SetParam(const DB_Param& dbParam);//����һЩ����
    

    bool                    Close();
	DB_EXECUTE_STATE ConnectToDB(const tstring& strTemp);
    DB_EXECUTE_STATE        ReConnect();

    void                    DealDBError(_com_error e);

    /************************************************************************/
    /*  fun: ִ��Sql,���Ϊ��ǰ�����
    /************************************************************************/
    DB_EXECUTE_STATE    ExecuteSelf();

    /************************************************************************/
    /*  fun: ִ��:SQL, ֻ����ִ��״̬, 
    /************************************************************************/
    DB_EXECUTE_STATE    ExecuteSql(const tstring& strSQL);
    //DB_EXECUTE_STATE    ExecuteSql(const wstring& strSQL);

    /************************************************************************/
    /*  fun: ִ��SQL, ����ִ�н��, ��ѯ��������ڳ�Ա������
    /************************************************************************/
    DB_EXECUTE_STATE    Select(const tstring& strSQL);

    bool                ExecuteRoutineSQL(std::vector<tstring> vtrSQL);
    tstring              GetErrorString();

    _RecordsetPtr           GetRecordset();
    const _RecordsetPtr&    GetRecordsetRf();
    long                    GetErrCode();
    bool                    CanAttemptReCn();   //�ж��Ƿ���Գ����������ݿ�
	tstring LastSql() const { return m_strLastSql; }
	bool AddReCnCode();
	ns_pi_common::FunSaveErrorInfo FuncSaveError() const { return m_FuncSaveError; }
	void FuncSaveError(ns_pi_common::FunSaveErrorInfo val) { m_FuncSaveError = val; }
	void SaveErrorInfo(StringCRef strError);
protected:
	bool _Init();		//�����ڲ�ʹ�ó�ʼ���ӿ�
	bool _UnInit();

private:
    _CommandPtr         m_pCommand;	            //SQL����
    _ConnectionPtr      m_pConnection;          //���ݿ�����
    _RecordsetPtr       m_pRs;                  //�����ѯ�����
    bool                m_bReCnNeed;            //��Ҫʱ���Ƿ���Ҫ����

    //CRITICAL_SECTION		csDB;
	auto_ptr<CLock>			m_pLock;
    tstring              m_strErr;               //���������Ϣ
    long                m_lErrCode;             //����������
    tstring              m_strErrDesc;           //��������

    tstring              m_strCnStr;             //���������ַ���
    tstring              m_strLastSql;           //�������һ�ε�SQL���

    /*long*               m_plErrorCodeReCn;     //���� ��Щ���������������ݿ�
    byte                m_byCodeCount;          //�������Ĵ������ĸ���*/

	LST_RE_CONNECT		m_lstReCn;			//�������Ĵ������
	FunSaveErrorInfo		m_FuncSaveError;
	
};

}
