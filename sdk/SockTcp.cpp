#include "StdAfx.h"
#include "SockTcp.h"
//#include "MsgHandle.h"
#include "define_gnl.h"
#include <assert.h>
#include <process.h>
#include "SockClientManager.h"
#include "IDataDeal.h"
#include "Lock.h"
#include "Stlmath.h"
#include <sstream>
#include <algorithm>
#include "StlSupply.h"
#include <MSTcpIP.h>
//#include <string>
#include "doString.h"
#include <iostream>
using namespace std;
uintptr_t __stdcall WaitForClientMsgProc	(LPVOID lpPar);
uintptr_t __stdcall WaitForConnectProc		(LPVOID lpPar);

#define SEND_SIZE 1024 * 50
#define RECV_SIZE 1024 * 50

typedef     CSockTcp::CONNECT_RESULT        CONNECT_RESULT;
typedef     CSock::SEND_STATE               SEND_STATE;
typedef     CSock::RECV_STATE               RECV_STATE;

using namespace ns_sock_tcp;

CSockTcp::CSockTcp(SOCKET sock /*= 0*/, void* pAdd /*= 0*/, const SOCK_PARAM* pSP /*= NULL*/)
:CSock(sock, pAdd, pSP)
{
	//����һ�����õĽ������ʼ������
    InitVariable();
}


CSockTcp::CSockTcp(const CSockTcp& tcp)
:CSock(tcp)
{
	//ֻ�������ಿ��
    InitVariable();
	m_pSockClientManager = tcp.m_pSockClientManager;
	if (tcp.m_pDataDeal)
	{
		m_pDataDeal = tcp.m_pDataDeal->Clone();     //����һ���µ����ݴ������
	}

    //����ͻ��˵�ַ��Ip
    m_strClientIp   = tcp.m_strLastClientIp; 
    m_uClientPort   = tcp.m_uClientPort;
    SetSock(tcp.m_sockLastRecv);

}   
void CSockTcp::InitVariable()
{
    m_bCnServer             = false;
    m_bNeedRebind           = false;

    m_pDataDeal             = NULL;
    m_pThreadArgu			= NULL;
    m_hListenThread			= 0;

    m_strServerIp			= "";
    m_pDataLock             = NULL;
    m_pSockClientManager	= NULL;
    m_LastRecvSize          = 0;
    m_uServerPort			= 0;
    m_bCnServer					= false;
    m_bStopClientRecv       = false;

    m_iParam.bServer        = false;
    m_iParam.uPort          = 0;
    m_iParam.bDisFilter     = false;
    m_iParam.bKeepalive     = true;
    m_iParam.nKeepalivetime = NUM_TCP_KEEPALIVE_TIMEOUT;

}
//CSockTcp& CSockTcp::operator =(const CSockTcp& tcp)
//{
//
//}

CSockTcp::~CSockTcp(void)
{
	//��ֹ�����߳�,�Ժ��޸�Ϊ
	//TerminateThread(TerminateThread, 0);
    if (m_iParam.bServer)
    {
        if (m_hListenThread)
        {
            CloseHandle(m_hListenThread);
            m_hListenThread = NULL;
        }
        
        //�ر����пͻ������ӣ� �Լ���Ӧ���߳�
        //m_pSockClientManager->CloseAll();
    }
    else
    {
        //�ͷŸÿͻ�socket from ClientList
        //m_pSockClientManager->Delete(this->GetSock());
    }
	
	
	if (m_pThreadArgu)
	{
		delete m_pThreadArgu;
		m_pThreadArgu = NULL;
	}
	if (m_pDataDeal)
	{
		delete m_pDataDeal;
		m_pDataDeal = NULL;
	}
    if (m_pDataLock)
    {
        delete m_pDataLock;
    }
	//�ر�ÿ������
	//m_pVtClientsSock.
}


bool CSockTcp::Init()
{
    SOCK_INFO si = {SOCK_STREAM};
    SetSockInfo(si);	

    if(!CSock::Init())
    {
        SetErrDesc("InitSockLib");
        return false;
    }
    if (m_iParam.bServer)
    {
        //�ͻ�������
        m_pSockClientManager = new CSockClientManager;

        CSockClientManager::INIT_PARAM iParam;
        iParam.bDisFilter   = m_iParam.bDisFilter;

        m_pSockClientManager->SetInitParam(iParam);
        m_pSockClientManager->Init();

        if (!m_pDataLock)
        {
            SetDataLock();
            //[ERROR] || dataLock is null!
        }
        
    }

    if(!Bind(m_iParam.uPort))
    {
        return false;
    }

    
	return true;
}

bool CSockTcp::UnInit()
{
    if(m_iParam.bServer)
    {
        m_pDataLock->Lock();
        m_bStopListen = true;
        m_pDataLock->UnLock();

        if( WAIT_TIMEOUT != WaitForSingleObject(m_hListenThread, 1000) )
        {
            m_pSockClientManager->UnInit();
        }
        else
        {
            ostringstream oss;
            oss<<INFO_WARNING<<"�ȴ������̹߳رճ�ʱ";
            OutputDebugStringA(oss.str().c_str());
        }

        if (m_pSockClientManager)
        {
            delete m_pSockClientManager;
        }

        
    }

	return true;
}


bool CSockTcp::Close()
{
    if(CSock::Close())
    {
        m_bCnServer = false;
    }
    return true;
}


bool CSockTcp::SetInitParam(const INIT_PARAM& iParam)
{
    m_iParam = iParam;
    return true;
}

bool CSockTcp::Bind(u_short port /*= 0*/)
{
    if(!CSock::Bind(port))
	{
        ostringstream           oss;
        oss<<"�󶨶˿� "<<port <<"ʧ��,�������Ϊ"<<GetErrCode();
        SetErrDesc(oss.str());
		return false;
	}

    //����socket ����

	return true;
}

bool CSockTcp::StartListen()
{
    if (!m_iParam.bServer)
    {
        return false;
    }

    if(!WaitConnect())
    {
        return false;
    }
    return true;
}

void CSockTcp::SetDataLock(CLock* pLock /*= NULL*/)
{
    if (!pLock)
    {
        m_pDataLock = new CLock;
    }
}

bool CSockTcp::SetMaxCnCount(DWORD dwCount)
{
	m_dwMaxCnCount = dwCount;
	return true;
}

CSockClientManager* CSockTcp::GetClientManager()
{
    return m_pSockClientManager;
}


bool CSockTcp::WaitConnect()
{
    assert(m_iParam.bServer);
    assert(m_pDataDeal);

    m_bStopListen = false;
	m_hListenThread = (HANDLE)_beginthreadex(
        NULL, 
		0,
		WaitForConnectProc, 
		this,
		0,
		0
	);
	if (NULL == m_hListenThread)
	{
		return false;
	}

	return true;
}

bool CSockTcp::ReConnect()
{
    //�ų���ֹ�����
    if(m_iParam.bServer)
    {
        assert(0 && "server self can't connect to another");
        return false;
    }


    if (m_bCnServer)
    {
        return false;
    }

    if (m_bNeedRebind)
    {
        this->Close();
        CSock::Init();
        if(!this->Bind(m_iParam.uPort)) //����ǰ�Ķ˿�0 �� ָ���˿�����
        {
            return false;
        }
    }
    
    bool bRet = this->Connect();
    
    return bRet;
}

bool CSockTcp::Connect(const char* ip /*= ""*/, u_short port /*= 0*/)
{

    SetNonBlockMode(true);

	SOCKET sock = CSock::GetSock();
	if (m_bCnServer)
	{
        this->Close();
		//DEBUG_INFO(L"already connect,new connect is undo");
		return true;
	}

	if (!strlen(ip))
	{
		ip = m_strServerIp.c_str();
	}
	port = (port == 0 ? m_uServerPort : port);

	SOCKADDR_IN addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(ip);

    bool bCnSuccess     = true;
	if(SOCKET_ERROR == ::connect(sock, (sockaddr*)&addr, sizeof(SOCKADDR_IN)))
	{
        int nErr = WSAGetLastError();
        this->SetErrCode(nErr);

        m_bNeedRebind   = false;    //����ʧ�ܲ���Ҫ���°󶨶˿�

        switch(nErr)
        {
        case WSAEWOULDBLOCK:
            //�жϳ�ʱ�Ƿ���
            
            if(SelectWrite(sock, m_iParam.nCnTimeout))
            {
                //��������
                int i = 0;
            }
            else
            {
                /************************************************************************/
                /* ��ʱ, ����ʧ��, �Ȳ��ر�socket,  ���˵�����ϵ��ǿ�, �պ÷�����ʱ, 
                    �ǿ�����Ҫ�ر�socket, ��Ȼ�´��ٽ�������, �����һ���������ϵ�socket�� �ٴ�connect
                /************************************************************************/
                this->SetErrCode(err_connect_timeout);
                //int idfdf = WSAGetLastError();
                bCnSuccess  = false;
            }
            break;
        case WSAEISCONN:
            //����֮ǰ��ʱ, ��֮���Ѿ���������
            break;

        //�������ó�ʱ, ���ӳ�ʱ���غ�,�ٴε���connect, ��֮ǰ�����ӻ�û�����
        case WSAEALREADY:
        case WSAEINVAL:
            this->SetErrCode(err_connect_last_no_completion);
        default:
            bCnSuccess = false;
        }
	}

    SetNonBlockMode(false);
    //û�����Ͼ�ֱ�ӷ���
    if (!bCnSuccess)
    {
        m_bCnServer     = false;
        return bCnSuccess;
    }



	int iAddrSize = sizeof(SOCKADDR_IN);
	memset(&addr, 0, iAddrSize);
	if(getsockname(
		sock , 
		(sockaddr*)&addr,
		&iAddrSize)
		)
	{
		int iErr = WSAGetLastError();
		//DEBUG_ERROR(getsockname + _itow(iErr,))
	}
	char* pLocalIp = inet_ntoa(addr.sin_addr);
	;
	u_short uPort = ntohs(addr.sin_port);
	wchar_t Buf[50] = {0};

	m_bCnServer           = true;
	return true;
}


CONNECT_RESULT CSockTcp::Accept(const char* ip /*= 0*/, u_short port /*= 0*/)
{
	SOCKET sock = CSock::GetSock();
	SOCKADDR_IN addrClient = {0};
	int nLen = sizeof(SOCKADDR_IN);

	memset(&addrClient, 0, sizeof(SOCKADDR_IN));
	nLen = sizeof(SOCKADDR_IN);
	SOCKET sockClient = ::accept(sock, (sockaddr*)&addrClient, &nLen);
	if (INVALID_SOCKET == sockClient)
	{
		int iErr = WSAGetLastError();
        this->SetErrCode(iErr);
        //throw(string("accept failed!"));            //<<throw>>
        return CN_ERROR;
		
	}

	//��ȡ��Դ�ĵ�ַ��Ϣ
	m_strLastClientIp	= GetClientIp(sockClient);
	m_uLastClientPort   = GetClientPort(sockClient);
	m_sockLastRecv      = sockClient;
    //���˺�ɸѡ�ͻ�������
    
    if (!m_pSockClientManager->Filter(CLIENT_ADDRESS(m_strLastClientIp, m_uLastClientPort) ))
	{
        //���ù��˽ӿ�
        DealFilter(m_strLastClientIp, m_uLastClientPort);
		closesocket(sockClient);
		return CN_FILTER;
	}
	else
	{
        m_strClientIp   = m_strLastClientIp;
        m_uClientPort   = m_uLastClientPort;
	}

    if (m_iParam.bKeepalive)
    {
        tcp_keepalive tcpKA;
        tcpKA.keepaliveinterval = 1 * 1000; 
        tcpKA.keepalivetime     = m_iParam.nKeepalivetime;
        tcpKA.onoff             = 1;

        char cBuf[300] = {0};
        DWORD dwRet = 0;

        if(SOCKET_ERROR == WSAIoctl(sockClient, SIO_KEEPALIVE_VALS, &tcpKA, sizeof(tcp_keepalive), cBuf, sizeof(cBuf), 
            &dwRet, NULL, NULL))
        {
            SetErrCode(WSAGetLastError());
            return CN_ERR_CLIENT;
        }
    }
	return CN_OK;
	//���յ���������
}

bool CSockTcp::DealAcceptError()
{
    DEBUG_INFO("accept fail!");
    return true;
}

bool CSockTcp::DealCloseByClient()
{
    return true;
}

bool CSockTcp::DealSelectError(int nErr)
{
    return true;
}

void CSockTcp::AddFilter(const CLIENT_ADDRESS* pCaR)
{
    m_pSockClientManager->AddFilter(*pCaR);
}

void CSockTcp::AddDisFilter(const CLIENT_ADDRESS* pCaR)
{
    m_pSockClientManager->AddDisFilter(*pCaR);
}

bool CSockTcp::DealFilter(const string&, u_short uPort)
{
    return true;
}

RECV_STATE CSockTcp::Recv(char* &pBuf)
{
	//�ְ����ܴ�С

	//�Ƚ������ݴ�С,�ڽ��ܾ��������
	DWORD dwDataSize = this->RecvDataSize();
	if(dwDataSize <= 0)
	{
		return RECV_ER_UNKNOWN;
	}
	DWORD dwRecv = 0;
	pBuf = new char[dwDataSize];//new,�ⲿ�ͷ�,�����СΪ0�����
	memset(pBuf, 0, dwDataSize);
	dwRecv = this->RecvData(pBuf, dwDataSize);
	if (dwRecv != dwDataSize)
	{
		//������Ľ�, Ҳ�п����ǻ���������,�޷�����̫������
		return RECV_ER_UNKNOWN;
	}
	m_LastRecvSize = dwDataSize;
	return RECV_OK;
}

DWORD CSockTcp::RecvData(const char* pBuf, u_long lSize)
{
	SOCKET sock = CSock::GetSock();
	int iRet = 0;
	u_long dwRecv = 0;
	u_long dwCanRecv = 0;
	while(dwRecv < lSize)
	{
		dwCanRecv = min(lSize - dwRecv, RECV_SIZE);
		iRet = ::recv(sock , (char*)(pBuf + dwRecv), dwCanRecv, 0);
		if (INVALID_SOCKET == iRet)
		{
            //�쳣�ر�

			int iErr = WSAGetLastError();
			this->SetErrCode(iErr);
            switch(iErr)
            {
            case WSAECONNABORTED: //�����Ѿ��ر��˸�socket
                this->Close();
                return 0;
            default:
                break;
            }
            return 0;
			//return dwRecv;
		}
        else if (0 == iRet )
		{
            //socket�Եȶ˱������ر���
            this->DealCloseByClient();

            //�����Ҳ�رյ�
            this->Close();

			if(dwRecv < lSize)
			{
				return 0;
			}
			else
			{
				return dwRecv;
			}

            
		}

		dwRecv += iRet;
	}

	return dwRecv;
}

DWORD CSockTcp::RecvDataOneTime(char* pBuf, u_long lMaxSize)
{
	assert(lMaxSize <= RECV_SIZE);

	SOCKET sock = CSock::GetSock();
	int iRet = 0;
	iRet = ::recv(sock , (char*)pBuf, lMaxSize, 0);
	if (INVALID_SOCKET == iRet)
	{
		int iErr = WSAGetLastError();
		wchar_t cErr[10] = {0};
		_itow(iErr, cErr, 10);

		//DEBUG_ERROR(L"receive_failed! Err = " + cErr);
		return 0;
	}
	if (0 == iRet )
	{
		//�Է��ر���socket
		return 0;
	}
	return iRet;
}

SEND_STATE CSockTcp::Send(const char* data, u_long lSize)
{
	//�ֶη������ݹ�ȥ
	//�ȷ������ݴ�С,�ڷ�������
    SEND_STATE ss = this->SendDataSize(lSize);
	if(SEND_OK != ss)
	{
		return ss;
	}
	return this->SendData(data, lSize);
	
}

SEND_STATE CSockTcp::SendData(const char* data, u_long lSize)
{
    if(!m_bCnServer)
    {
        return SEND_ER_CONNECT;
    }

	//char cSendBuf[200] = "dfdf";
	int iRet = 0;
	u_long dwSended = 0;
	u_long dwCanSend = 0;

	while(dwSended < lSize)
	{
		dwCanSend = min(lSize - dwSended, SEND_SIZE);
		iRet = ::send(CSock::GetSock(), data + dwSended, dwCanSend , 0);
        if(SOCKET_ERROR == iRet)
        {
            iRet = WSAGetLastError();
            SetErrCode(iRet);

            SEND_STATE ss;
            switch(iRet)
            {
                /************************************************************************/
                /*  �ð����ݵĴ���, ����Ӱ�쵽���������send����
                /************************************************************************/
            case WSAEMSGSIZE:
            case WSAEHOSTUNREACH:
                ss = SEND_ER_CLIENT;
                break;
            

                /************************************************************************/
                /*  �����Դ���, ��Ӱ�쵽���������send����
                /************************************************************************/

            case WSAETIMEDOUT:      //����ʱ��Ҫ���°󶨶˿�
                m_bNeedRebind   = true;
            default:
                m_bCnServer     = false;
                ss = SEND_ER_CONNECT;
                break;
            }
            m_bNeedRebind       = true;
            return ss;
        }
        

        //û������
		dwSended += iRet;
	}

	return SEND_OK;
}

SEND_STATE CSockTcp::SendDataSize(DWORD dwSize)
{
	char cBuf[DATA_SIZE_DIGIT_NUMBER] = {0};//�����͵����ݴ�С,��������ն˵Ĵ�Сһ��
	//���ʹ�С
	ultoa(dwSize, cBuf, 10);
	return this->SendData(cBuf, sizeof(cBuf));
}

DWORD CSockTcp::RecvDataSize()
{
	char cBuf[DATA_SIZE_DIGIT_NUMBER] = {0};//�����ܵ����ݴ�С,��������Ͷ˵Ĵ�Сһ��
	if(this->RecvData(cBuf, sizeof(cBuf)))
    {
        return atol(cBuf);
    }
	//���ʹ�С
	return 0;
}

bool CSockTcp::SetRemoteInfo(const char* ip, u_short port)
{
	m_strServerIp = ip;
	m_uServerPort = port;
	return true;
}

void CSockTcp::SetDeal(IDataDeal* pDeal)
{
	m_pDataDeal = pDeal;
}

bool CSockTcp::InitAdditionArgu()
{
	m_pThreadArgu = new THREAD_ADDITION_ARGU;
	memset(m_pThreadArgu, 0, sizeof(THREAD_ADDITION_ARGU));
	
	return true;
}

bool CSockTcp::DoDealDataRecv(void* pBuf, DWORD dwRecv)
{
	//ÿ���յ����ݺ�Ĵ���
	//OutputDebugString(L"CSockTcp::DoDealDataRecv!!");

    if (m_pDataDeal)
    {
        m_pDataDeal->SetData(pBuf);
        m_pDataDeal->Work(this);
    }
    else
    {
        
    }
	

	return true;
}

CSock* CSockTcp::Clone()
{
	CSockTcp* pTcp		= new CSockTcp(*this);
	return pTcp;
}


bool CSockTcp::Listen()
{
	return Listen(2);
}

bool CSockTcp::IsStopListen()
{
    m_pDataLock->Lock();
    bool bRet = m_bStopListen;
    m_pDataLock->UnLock();
    return bRet;
}

bool CSockTcp::IsStopClientRecv()
{
    bool bRet = m_bStopClientRecv;
    return bRet;
}

bool CSockTcp::Listen(DWORD backlog )
{
	SOCKET sock = CSock::GetSock();
	if(0 != listen(sock, backlog))
	{
		//DEBUG_ERROR(L"listen failed");
		return false;
	}
	return true;
}

string CSockTcp::GetClientIp(SOCKET sock)
{
	SOCKADDR_IN addrClient = {0};
	int iAddrSize = sizeof(SOCKADDR_IN);

	if(getpeername(
		sock, 
		(sockaddr*)&addrClient,
		&iAddrSize)
		)
	{
		int iErr = WSAGetLastError();
		////DEBUG_ERROR(_itow(iErr,))
		//AfxMessageBox(L"getsockname");
	}
	return inet_ntoa(addrClient.sin_addr);
}

string CSockTcp::GetClientIp()
{
    return m_strClientIp;
}

u_short CSockTcp::GetClientPort(SOCKET sock)
{
	SOCKADDR_IN addrClient = {0};
	int iAddrSize = sizeof(SOCKADDR_IN);

	if(getpeername(
		sock, 
		(sockaddr*)&addrClient,
		&iAddrSize)
		)
	{
		int iErr = WSAGetLastError();
		WCHAR cTemp[30] = {0};
		_itow(iErr, cTemp, 10);
		//DEBUG_ERROR(wstring(L"getpeername:" ) + cTemp);
		//AfxMessageBox(L"getsockname");
	}

	u_short uPort = ntohs(addrClient.sin_port);
	return uPort;
}

bool CSockTcp::ExitRecvMsgThread(void* cInfo /*= NULL*/)
{
    DEBUG_INFO("Exit Thread: ClientMsgProcThread");
    return true;
}

bool CSockTcp::ExitWaitForConnectThread(void* cInfo /*= NULL*/)
{
    DEBUG_INFO("Exit Thread: WaitForConnectProc");
    return true;
}

bool CSockTcp::DealAcceptClientError()
{
    DEBUG_INFO("DealAcceptClientError");
    return true;
}

bool CSockTcp::AcceptSleep()
{
    Sleep(20);
    return true;
}

bool CSockTcp::IsConnect()
{
    return m_bCnServer;
}

bool CSockTcp::CanRecn()
{
    if( !(!m_bCnServer && m_iParam.bAutoRecn) )
    {
        return false;
    }
    int iCode = GetErrCode();
    /*switch(iCode)
    {
    case WSAETIMEDOUT:
        
        return true;

    default:
        return false;
        break;
    }*/
    return true;
}

UNINT CSockTcp::ReConnectSome(list<CSockTcp*>& lstTcp)
{
    UNINT nRecnSuccessCount = 0;
    for (LIST_TCP::iterator it = lstTcp.begin(); it != lstTcp.end();)
    {
        
        if( !(*it)->CanRecn())
        {
            ++it;
            continue;
        }


        if((*it)->ReConnect())
        {
            //�����ɹ���, �Ƴ��б�
            ++nRecnSuccessCount;
            //it = lstTcp.erase(it);
        }
        else
        {
            (*it)->DealReConnectFail();
            ++it;
        }
    }
    
    return nRecnSuccessCount;
}

bool CSockTcp::SetNonBlockMode(bool bBlock)
{
    SOCKET s = GetSock();
    //�������ӳ�ʱ
    u_long nParam = (u_long)bBlock;
    if(SOCKET_ERROR == ioctlsocket(s, FIONBIO, &nParam))
    {
        int i = WSAGetLastError();
        return false;
    }
    return true;
}

void CSockTcp::DealReConnectFail()
{
    
}

string CSockTcp::GetServerIp()
{
    return m_strServerIp;
}

u_short CSockTcp::GetServerPort()
{
    return m_uServerPort;
}

bool CSockTcp::DealSendFail()
{
    return true;
}


unsigned  __stdcall WaitForConnectProc(LPVOID lpPar)
{
    typedef CSockTcp::CONNECT_RESULT    CONNECT_RESULT;

	CSockTcp* pCn = (CSockTcp*)(lpPar);
	if(!pCn->Listen())//������Լ�����������
	{
		return 0;
	}

    ostringstream oss;
	SOCKADDR_IN addrClient = {0};
	int nLen = sizeof(SOCKADDR_IN);

    bool bStop = false;
    int nSelect = 0;

    try
    {
	    while(!bStop)
	    {
            nSelect = SelectRead(pCn->GetSock());
            bStop = pCn->IsStopListen();

            if (nSelect > 0)
            {
		        SOCKET sockClient = NULL;
                CONNECT_RESULT cr;
			    cr = pCn->Accept();

                switch(cr)
                {
                
                case CSockTcp::CN_ERROR:
                    //����ʧ��,�׽���������,ֹͣ����
                    pCn->DealAcceptError();
                    throw(string("accept fail!"));

                case CSockTcp::CN_ERR_CLIENT:
                    pCn->DealAcceptClientError();
                    continue;
                case CSockTcp::CN_FILTER:
    
                    //����֮ǰ�Ѿ����ô���ӿ���
                    continue;

                case CSockTcp::CN_OK:
                    //����������
                    break;

                default:
                    continue;
                }

		        CSockTcp* pSock = dynamic_cast<CSockTcp*>(pCn->Clone()); //�����Ѹ���ָ�봫����ȥ
		        if(!pSock->InitAdditionArgu())
                {
                    //����������
                    delete pSock;
                    continue;
                }

		        HANDLE hThreadClient = (HANDLE)_beginthreadex(
                    NULL, 
			        0, 
			        WaitForClientMsgProc, 
			        pSock, 
			        0,
			        NULL
			        );
		        if (!hThreadClient)
		        {
			        //DEBUG_ERROR(L"create client thread failed");
			        break;
		        }
                CSockClientManager::CLIENT_DATA ci = {0};
                ci.hThread          = hThreadClient;
                ci.pClientSockTcp   = pSock;

                pSock->m_pSockClientManager->Add(ci);
            }
            else if(nSelect < 0)
            {
                pCn->DealSelectError(GetSelectError());
                //select ��������
                break;
                //OutputDebugString(L"�������ӵ���");
            }

            pCn->AcceptSleep(); //�Ժ��Ϊ��������������
    	
        }
    }
    catch(const string& strErr)
    {
        //���մ���, ���׳��쳣֮ǰ�����˴���
    }
	pCn->ExitWaitForConnectThread();
    _endthreadex(1);
	return 1;
}

unsigned  __stdcall WaitForClientMsgProc(LPVOID lpPar)
{
	//TwoPoint* pTwoPoint = (TwoPoint*)lpPar;
	//Sleep(5000);

	CSockTcp* pSock = (CSockTcp*)lpPar;//<delete> �߳̽������ͷ�
	/*char cBuf[100] = {0};
	memset(cBuf, 0, sizeof(cBuf));*/

    int nSelect = 0;
	while(1)
	{
        nSelect = SelectRead(pSock->GetSock(), 1);
        if ( nSelect == 0)
        {
            continue;
        }
        else if ( nSelect < 0)
        {
            //select ����, ֹͣ����
            break;
        }

		char* pBuf = NULL;//����ĵط������ͷ�
		DWORD dwRecv = 0;
		dwRecv = pSock->Recv((char*)pBuf);

        switch(dwRecv)
        {
        case CSockTcp::RECV_ER_UNKNOWN:
        case CSockTcp::RECV_ER_NET:    //���ճ���, ��������
        case CSockTcp::RECV_ER_DATA:    //���ճ���, ��������
                goto lbEndRecv;

        case CSockTcp::RECV_ER_NOCARE:     //��������յ�������
                continue;
                break;

            default:
                break;
        }

		//�����ദ���յ�������
		pSock->DoDealDataRecv(pBuf, dwRecv);

		/*delete [] pBuf;
		pBuf = NULL;*/
	}

lbEndRecv:
    pSock->m_pSockClientManager->Delete(pSock);

	pSock->ExitRecvMsgThread();
    delete pSock;
    _endthreadex(1);
	return 1;
}


