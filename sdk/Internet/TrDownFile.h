#pragma once
#include "threadlight.h"
#include "InetDef.h"
#include "LockData.h"
class CInternetHttp;
class CLock;
class CDowningInfoMng;
class CTrDownFile:
    public CThreadLight
{
public:
    typedef ns_down_file::CBDowningInfo CBDowningInfo;

    CTrDownFile(CallBackFun = NULL, void* pAdd= NULL );
    virtual ~CTrDownFile(void);

public:
    bool Init();
    bool UnInit();
    bool StopDown();
    bool ExitDown();
    bool AddDownTask(DownFileInfo dfi);
    bool AddDownTask(DownList dl);
    virtual DWORD DoWork();
    /************************************************************************
        fun:	����ָ��URL���ļ�, ������ʽ
        param:  
        ret:    
        remark: 
	/************************************************************************/
	bool DownFile( DownFileInfo& dInfo );
    void SetDowningInfoCB( CBDowningInfo pFun, void* pAdd );
    bool CanRetry( DownState ds);
    bool GetNextTask();
    void SetProxy( tcpchar szProxyName);
    void GetErrInfo( DownFileInfo& dfi );
    bool ResumeDown();
    bool SetHeader( LPCTSTR param1 );
    bool SetFileSizeLimit(UNLONG nSize);
    DownFileInfo* GetDownInfo(){ return m_pDownInfo; }
    bool IsUsedProxy();
    bool SetHasUseProxy();
    bool IsProxyErr( DownState ds );
    bool SaveErrInfo( DownFileInfo& dInfo, CInternetHttp* m_pInternet );
    bool DealDownFail( DownFileInfo it );
    bool RetryOut();
    bool IsReTryOK();
    bool ClearState();
    virtual bool InitInetObj();
    void DowningInfoMng(CDowningInfoMng* val) { m_pDowningInfoMng = val; }
    bool DealAllOk();
    bool GetAllFileSize(UNLONG& dwSize);
    bool SetShowTotalSize( UNLONG nSize );
    DownList::iterator GetFirstTask();
protected:
    auto_ptr<CInternetHttp>			m_pInternet;

private:
    DownList::iterator*     m_it; //��֤��������ɾ��, �������������쳣

    DownList		m_lstToDown;		//�����б�
    UNLONG			m_dwSingleSizeLimit;	//��һ�ļ����ش�С����
    UNINT           m_ServerCode;           //������״̬��
    bool            m_bQuitDown;        //�Ƿ�ֹͣ����
    CBDowningInfo m_pCBDowningInfoFun;      //��������ʾ����,�ٶȵĻص�����
    auto_ptr<CLock>           m_lockDownList;

    //Ĭ�ϲ���
    void*           m_pDownInfoCBAdd;   //�����лص��������û�����
    DownFileInfo*           m_pDownInfo;
    
    CDowningInfoMng*       m_pDowningInfoMng;
    
    auto_ptr<CEventLight>           m_pEvPause; //��ͣ�����¼�
    int             m_nCurRetryTimes;   //��ǰ���������Դ���
    tstring                 m_strProxyName;
    auto_ptr<CLock>           m_pLockProxy;
    bool        m_bUsedProxy;   //�Ƿ�ʹ�ù����ϴ����õĴ���
};

