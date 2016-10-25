#include "stdafx.h"
#include "TcpDB.h"
#include "DataDeal.h"
#include "define.h"
#include "SingleLog.h"
#include "StlSupply.h"
#include "RecvData.h"
#include "SockClientManager.h"

static CLogOpr* g_pSingleLog;

CTcpDB::CTcpDB(SOCKET sock/* = 0*/, void* pAdd /*= 0*/)
:CSockTcp(sock, pAdd)
{
	g_pSingleLog = CSingleLog::GetObj();
}

CTcpDB::~CTcpDB(void)
{
}

bool CTcpDB::Listen()
{
    if(!CSockTcp::Listen(SOMAXCONN))
    {
        g_pSingleLog->WriteLog("����ʧ��");
        return false;
    }
    return true;
}

SOCKET CTcpDB::Accept(const char* ip /* = 0 */, u_short port /* = 0 */)
{
	SOCKET s = CSockTcp::Accept();
	if (s)
	{

		g_pSingleLog->WriteLog("�յ�������");
	}
	else
	{
		string strTemp("�յ��������쳣");
	}
	return s;

}

DWORD CTcpDB::Recv(char* &pBuf)
{
	DWORD dwSize = sizeof(TrafficInfo);
	pBuf = new char[dwSize];
	memset(pBuf, 0, dwSize);
	dwSize = RecvData(pBuf, dwSize);
	if (dwSize)
	{
		g_pSingleLog->WriteLog("�յ�  ����");
	}
	return dwSize;
}

bool CTcpDB::DoDealDataRecv(void* pBuf, DWORD dwRecv)
{
	//OutputDebugString(L"recved data from client!!");
	try
	{
		CRecvData* pRD = (CRecvData*)m_pAdd;
		CDataDeal dataDeal(pRD->m_pAdd, pRD->m_pDB);
		dataDeal.Init();
		//CDataDeal* pDataDeal = (CDataDeal*)(this->m_pAdd);
		dataDeal.SetData((TrafficInfo*)pBuf);
		dataDeal.DealData();
		//pDataDeal->ShowToUI();
		//ɾ��Ԫ�� �Ӽ���socket ���յ��ͻ����ӵ��б�
		m_pSockClientManager->Delete(GetSock());
		
		this->Close();
	}
	catch(string& err)
	{
		g_pSingleLog->WriteLog(err.c_str());
	}
	catch(...)
	{
		g_pSingleLog->WriteLog("����δ֪�Ĵ���");
	}
	
	return true;
}

CSock* CTcpDB::Clone()
{
	return new CTcpDB(*this);
	
}