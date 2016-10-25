#pragma once
#include "DataSettingBase.h"

class CPAUserSetting;

/************************************************************************
    fun:    UI����ѡ��Ļ���
    remark: �����������Ľ���, ���������Ķ������Ԫ��
************************************************************************/
class CPAOptUIBase
{
public:
    CPAOptUIBase(CPAUserSetting* pSC);
    virtual ~CPAOptUIBase(void);
public:

    /************************************************************************
        fun: �ӽ����ȡ����, �������ò�д���ļ�
        param: 
        remark:  
    ************************************************************************/
    bool SaveSetting();

    /************************************************************************
        fun: �ӽ����ȡ����, ��������,
        param: 
        remark:  ��д���ļ�
    ************************************************************************/
    bool SetConfig();

    virtual bool ReadData();
    tstring GetData();

     /************************************************************************
        fun: ��ʾ�ļ�������ݵ�����ѡ����
        parent: 
        remark: 
    ************************************************************************/
    bool ShowDB();

    bool InitData();
    virtual bool Show() = 0;
     /************************************************************************
        fun:    ���ݽ���ѡ��, ��ȡ��Ӧ���ַ���
        param: strData, �������ַ���, Ҫ�����ѡ������
        remark: 
    ************************************************************************/
    virtual bool DoGetSaevData(tstring& strData) = 0;
    

    bool SetSetting(CDataSettingBase* pSetting);
    bool SetSetting(ENUM_DATA_DUTY dd);
    
    CDataSettingBase* GetSetting(ENUM_DATA_DUTY dDuty);
protected:
    
    bool SaveData(const tstring& strData);
    bool SetData(const tstring& strData);
    ENUM_DATA_DUTY          m_dataDuty;
    void SetDataDuty(ENUM_DATA_DUTY dd);
private:
    tstring                 m_strData;
    CDataSettingBase*       m_SetData;
    CPAUserSetting*         m_pSettingCol;  //����
};


