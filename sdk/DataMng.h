#pragma once
#include "PiTypeDef.h"
class CDataMng
{
public:
    CDataMng(void);


    virtual ~CDataMng(void);
public:
    /************************************************************************
        fun:	׷���ڴ浽���ݶ�����
        param:  
        ret:    
        remark:  TODO:ÿ��׷�Ӷ�������µ��ڴ�, ������Ҫ�ĳ��Զ��������û���, ����ÿ�η����ڴ������
    /************************************************************************/
    bool Append(void* pMem, UNLONG nDataSize);

    /************************************************************************
        fun:	�����������������
        param:  
        ret:    
        remark: 
    /************************************************************************/
    bool ClearData();

    void* GetData();
    UNLONG GetDataSize();
	void* Alloc( UNINT dwSize );

	operator void*();
	operator tpchar();
private:
    void InitVariable();
private:
    void*       m_pData;
    UNLONG      m_nDataSizeTotal;
};

