#pragma once
#include "PiTypeDef.h"
#include "doString.h"
#include "database/DataBase.h"
//#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")
//#import "c:\msado15.dll" no_namespace rename("EOF","adoEOF")

/*  
    date: 2012-9-23 11:38:45
    author: ������
    fun: CDataBase ���ݿ⸨����, ��װ��ȡ�ֶ� �ַ�������ֵ �Ľӿ�,����ֶ�ֵû��ֵ,�򷵻� "" �� 0
    remark: �������һ����¼������,
*/
class CRecordsetAssist
{
public:
    CRecordsetAssist(_RecordsetPtr& rs);
    ~CRecordsetAssist(void);

    /************************************************************************/
    /*  fun: ��ȡ��ǰ��¼��ָ���ֶε��ַ���ֵ
        remark: ����ֶ�ֵ�ǿյ�, �򷵻� ���ַ���""
    /************************************************************************/
    void        SetRecordset(_RecordsetPtr&);
    string      GetString(const string& strField);
    wstring     GetStringW(const string& strField);
    /************************************************************************/
    /*  fun: ��ȡ��ǰ��¼��ָ���ֶε�����ֵ
        remark: ����ֶ�ֵ�ǿյ�, �򷵻� 0
        ret: ���س�������
    /************************************************************************/
    LLONG GetInt(const string& strField);
public:

private:
    _RecordsetPtr&   m_recordset;
};

