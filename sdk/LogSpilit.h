#pragma once
#include "define_gnl.h"
#include "PiTypeDef.h"
#include "Stlmath.h"
#include "Math/mathUnit.h"
#include "logopr.h"

/************************************************************************
    fun: ��־��, ���Ը��ݴ�С��ʱ������� �Զ��ֳɶ���ļ�
    remark: 
    author: liwanliang
    create time: 2013-7-31 20:13
    modify time: 2013-7-31 20:13
************************************************************************/
Pi_NameSpace_Begin
class CLogSpilit :
    public CLogOpr
{
public:
    struct INIT_PARAM
    {
        bool bSplitEveryDay;    //�Ƿ�һ��һ��log
        UNLONG nMaxSize;        //һ���ļ���С����
        INIT_PARAM()
        {
            bSplitEveryDay = true;
            nMaxSize        = NUM_FILE_SIZE_1M * 30;   //30M
        }
    };

public:
    CLogSpilit(void);
    ~CLogSpilit(void);
public:
    bool         Init();
    bool         UnInit();
    bool        SetParam(const INIT_PARAM& iParam);
	bool		OpenTodayLog(tcpchar szPath );

    /************************************************************************/
    /*  fun: дlog, �ַ���֮ǰ�����ʱ��ǰ׺
    /************************************************************************/
    DWORD	    WriteLog(tcpchar data);
    DWORD       WriteLog(StringCRef data);
    /************************************************************************/
    /*  fun: дlog, �����ʱ��ǰ׺
    /************************************************************************/
    DWORD       WriteLogPure(tcpchar data);
    DWORD       WriteLogPure(StringCRef data);
protected:
    void        PartLogFile();

private:
    CLogSpilit(CLogSpilit&);
    tstring			m_strDate;//����date, �����ж��Ƿ�Ҫ����һ���µ�Log
    INIT_PARAM      m_iParam;
};


Pi_NameSpace_End
