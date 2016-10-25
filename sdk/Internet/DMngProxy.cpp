#include "StdAfx.h"
#include "DMngProxy.h"
#include "..\UPDate\Common\Internet\DownFileManager.h"
#include <ProxyPC.h>
#include <TrDownFile.h>
#include <RAIILock.h>
#include "..\..\..\..\..\svn\sdk\functional.h"


CDMngProxy::CDMngProxy(void)
{
}


CDMngProxy::~CDMngProxy(void)
{
}

bool CDMngProxy::Init()
{
    CDownFileManager::Init();
    m_proxyUse = CProxyPC::GetInst();
    return true;    
}

bool CDMngProxy::DoNewDown( CTrDownFile* pDown )
{
    pDown->SetProxy(m_proxyUse->GetProxy().c_str());
    return true;
}


bool CDMngProxy::DealDownFail( CTrDownFile* pTrDown )
{
    if (pTrDown->IsUsedProxy()/*����ip�Ѿ��ù�, */)
    {
        m_proxyUse->GetNextProxy();
    }
    DownFileInfo dfi = *(pTrDown->GetDownInfo());
    dfi.dState = err_user_stop;

    pTrDown->SetProxy(m_proxyUse->GetProxy().c_str());
    pTrDown->AddDownTask(dfi);
    //AddDownItemTask();

    //ֹͣ��������
    StopAllDown();
    //Ϊ�������ض��������µĴ���
    SetAllDownProxy();
    //������������
    StartAllDown();

    this->Run();
    return true;
}

bool CDMngProxy::SetAllDownProxy()
{
    CRAIILock raii(m_lockDownObjList->Lock());    
    FOR_EACH_ITER(DownObjList, m_lstDownObj, it)
    {
        CTrDownFile* pDown = *it;
        if (! pDown->IsUsedProxy())
        {
            pDown->SetProxy(m_proxyUse->GetProxy().c_str());
        }
        else
        {
            OutInfo(_T("��ʹ�ô���Ip"));
        }
    }
    return true;
}