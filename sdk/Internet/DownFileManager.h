#pragma once
#include "threadlight.h"
#include "InetDef.h"
#include <memory>

#include "PiTypeDef.h"
#include "PiThreadDef.h"

#include "DowningInfoMng.h"
#include "LockData.h"
using namespace std;

class CLock;
class CProxyPC;
class CDownFileManager :
	public CThreadLight
{
public:
	CDownFileManager(CallBackFun = NULL, void* pAdd = NULL);
	virtual ~CDownFileManager(void);
public:
	virtual bool Init();
protected:
	/************************************************************************
		new���µ����ض���CTrDownFile�����
	************************************************************************/
	virtual bool DoNewDown( CTrDownFile* pDown );
	virtual bool InitData();
	virtual bool DoRunBegin();
	virtual DWORD DoWork();
	virtual CTrDownFile* CreateDownFileObj();
	virtual bool DealDownFail( CTrDownFile* pTrDown );

public:
	bool UnInit();

	bool AddDownItemTask(DownFileInfo& dInfo);
    bool AddDownItemTask( tcpchar szUrl);
    bool AddDownItemTask( tcpchar szUrl, tcpchar szSavePath);
    bool AddDownItemTask(DownList& lstDown);
    
    void SetDowningInfoCB(CBDowningInfo pFun, void* pAdd);
    /************************************************************************
        fun:	���������߳� ��ʼ����
        param:  
        ret:    
        remark: 
	/************************************************************************/
    bool StartDown();
	/************************************************************************
        fun:	���Ƶ�һ�ļ������ش�С�����ֵ
        param:  
        ret:    
        remark: 
	/************************************************************************/
	void SetSingleFileMaxLimit(UNLONG dwSize);
	
    /************************************************************************
        fun:	�˳�����
        param:  
        ret:    
        remark: 
	/************************************************************************/
    void QuitDownFile();
    bool StopAllDown();
    bool ExitAllDown();
    void SetDefaultSavePath(tcpchar szPath);
    /************************************************************************
        fun:	��������б�
        param:  
        ret:    
        remark: 
	/************************************************************************/
	void ClearAllDownItem();
    /************************************************************************
        fun:	�б������������, ��ȡ��һ������
        param:  
        ret:    
        remark: 
    /************************************************************************/
    static bool CB_GetNextDownTask(CDownFileManager* pMng, CTrDownFile* pDown);
    bool GetNextTask(DownList::iterator& itL);
    UNINT GetDownThreadCount() const;
    bool StopRunNewTask();
    bool StartRunNewTask();
    bool SetShowDownInfo(bool bShow, void* Obj, CBDowningInfo func, UNINT nShowCircle = 500);
    UNINT GetDownCount();
    bool AsWhole() const { return m_bAsWhole; }
    void AsWhole(bool val) { m_bAsWhole = val; }
	UINT MaxDownObjAsync() const { return m_nMaxDownObjAsync; }
	void MaxDownObjAsync(UINT val) { m_nMaxDownObjAsync = val; }

protected:
    bool AddDownItem(DownFileInfo& dInfo);
    
    /************************************************************************
        fun:	��������̶߳��������ļ�
        param:  
        ret:    
        remark: 
    /************************************************************************/
    bool CreateMultiDownThread();

    

    bool DownFile( tcpchar szUrl);
    
    bool InitVariable();

    

    /************************************************************************
        fun:	�ײ�������ɺ�, ���øýӿ�֪ͨ�ϲ������
        param:  
        ret:    
        remark: 
    /************************************************************************/
    static void CB_DownNotify(CDownFileManager* pMng, NotifyObj* pNo );

    //bool CanRetry( DownState );
    CDownFileManager* Clone();
    bool MoveToDone( DownList::iterator it );
    bool MoveToDone( ItemID nID);
    bool NewThreadDown();
    void ClearTaskState( DownFileInfo& dfi );
    ns_down_file::ItemID MakeTaskID();
    int CanCreateThreadCount();
    void AddDownObj( CTrDownFile* pDown );
    bool SetProxyServerList(const LST_STRING& lstProxy) ;
    bool SetAllDownProxy();
    bool StartAllDown();
    bool DealDownRet();
    bool DistributeTask( CTrDownFile* pDown );
    DownList GetTask( int param1 );
protected:
    DownList		m_lstToDown;		//�����б�
	DownList		m_lstDowned;		//�������б�
	
 	UNLONG			m_dwSingleSizeLimit;	//��һ�ļ����ش�С����
    bool            m_bQuitDown;        //�Ƿ�ֹͣ����
    auto_ptr<CLock>           m_lockDownList;
    auto_ptr<CLock>           m_lockDownObjList;
    auto_ptr<CLock>           m_lockID;

    auto_ptr<CDowningInfoMng>               m_pDownInfoMng;
    CBDowningInfo m_pCBDowningInfoFun;      //��������ʾ����,�ٶȵĻص�����
    
    //Ĭ�ϲ���
    void*           m_pDownInfoCBAdd;   //�����лص��������û�����
    tstring         m_strSavePathDefault;   //Ĭ�ϵı���·��
    static CLockData<int> nThreadCount;
    DownObjList             m_lstDownObj;
    LST_STRING      m_lstProxyServer;
    //CProxyPC*               m_proxyUse; //����
    bool                    m_bStopDown;
    bool                    m_bAsWhole; //�����������Ƿ���Ϊһ������
    UINT					m_nMaxDownObjAsync;	//���ͬʱ���ض���
	
};