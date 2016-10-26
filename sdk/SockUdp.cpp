#include "stdafx.h"
#include "SockUdp.h"
#include <assert.h>
#include <stdio.h>
const long RECV_SIZE = 1024 * 5 * 10;
const long SEND_SIZE = 1024 * 5 * 10;

const long UDP_SEND_BUF_SIZE = 1024 * 100;		//���ͻ�������С
const long UDP_RECV_BUF_SIZE = 1024 * 1024;		//���ܻ�������С

typedef CSock::RECV_STATE       RECV_STATE;
typedef CSock::SEND_STATE               SEND_STATE;

CSockUdp::CSockUdp( SOCKET sock /*= 0*/)
:CSock(sock)
{
	m_pLastRecvAddr	= NULL;
    m_nSendSizePack = SEND_SIZE;
}

CSockUdp::~CSockUdp(void)
{

}


bool CSockUdp::Init(u_short port /*= 0*/)
{
	m_pLastRecvAddr = new SOCKADDR_IN;
	memset(m_pLastRecvAddr, 0, sizeof(SOCKADDR_IN));

    SOCK_INFO si = {0};
    si.sockType = SOCK_DGRAM;
    SetSockInfo(si);
    if(!CSock::Init())
    {
        SetErrDesc("InitSockLib");
        return false;
    }

	if(!this->Bind(port))
    {
        SetErrDesc("Bind Port");
        return false;
    }
	//this->SetRecvBufSize();
	return true;
}


RECV_STATE CSockUdp::Recv(char* &pBuf)
{
    UNLONG lDataSize = this->RecvDataSize();

	if(lDataSize <= 0)
	{
		return RECV_ER_UNKNOWN;
	}
	DWORD dwRecv = 0;
	pBuf = new char[lDataSize];//new,�ⲿ�ͷ�,�����СΪ0�����
	memset(pBuf, 0, lDataSize);

	UNLONG lSizeRecved = this->RecvData(pBuf, lDataSize);
	if (lSizeRecved != lDataSize)
	{
		//ʵ�ʽ��ܴ�С���������ܵĴ�С��һ��
		return RECV_ER_UNKNOWN;
	}

    assert(0 && "δ֧��, ��֪�������ֽ���");
    return RECV_OK;

}

DWORD CSockUdp::RecvData(char* pBuf, u_long lSize)
{
	//�ְ����ܴ�С

	int iRet = 0;
	u_long dwRecv = 0;
	u_long dwCanRecv = 0;
	char bufOpt[30] = {0};
	int iBufOptSize = sizeof(bufOpt);
	SOCKET sock = this->GetSock();
	getsockopt(sock , SOL_SOCKET, SO_RCVBUF, bufOpt, &iBufOptSize);

	int iRecvBuf = *(int*)bufOpt;
	while(dwRecv < lSize)
	{
		dwCanRecv = min(lSize - dwRecv, RECV_SIZE);
		
		//����ղŷ�����Ϣ���Ŀͻ�
		
		int nLen = sizeof(SOCKADDR_IN);

		iRet = ::recvfrom(sock, (char*)(pBuf + dwRecv), dwCanRecv, 0, (sockaddr*)m_pLastRecvAddr, &nLen);
		if (INVALID_SOCKET == iRet)
		{
			int iErr = WSAGetLastError();
			SetErrCode(iErr);
			/*wchar_t cErr[10] = {0};
			_itow(iErr, cErr, 10);*/
			////DEBUG_ERROR(L"receive_failed! Err = " + cErr);
			return dwRecv;
		}
		dwRecv += iRet;
		/*wchar_t buf[20] = {0};
		wsprintf(buf, L"%d\n",dwRecv);
		OutputDebugStringW(buf);*/
	}

	return dwRecv;
}

DWORD CSockUdp::RecvDataSize()
{
	char cBuf[DATA_SIZE_DIGIT_NUMBER] = {0};
	//���ʹ�С
	int iSize = sizeof(SOCKADDR_IN);//����ܱ��泤��Ϊ int(4 byte)�����ֵ :4G
	if(SOCKET_ERROR == ::recvfrom(this->GetSock(), cBuf, sizeof(cBuf), 0, (sockaddr*)m_pLastRecvAddr, &iSize))
	{
		return -1;
	}
	return atol(cBuf);
}

void CSockUdp::SetRemoteAddress( const char* ip,u_short port)
{
	SOCKADDR_IN addr = {0};

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(ip);

	*m_pLastRecvAddr = addr;
}

SEND_STATE CSockUdp::Send(const char* data, u_long lSize)
{
	//�ȷ������ݴ�С, ���ַ�������ʽ
    SEND_STATE ss = this->SendDataSize(lSize);
	if(SEND_OK != ss)
	{
		return ss;
	}

	//��������
	return this->SendData(data, lSize);
}

SEND_STATE CSockUdp::SendData(const char* data, u_long lSize)
{
	//һ�ε���Ϣ���ܳ���Ԥ��ֵ ��SO_MAX_MSG_SIZE

	//�ֶη������ݹ�ȥ

	//char cSendBuf[200] = "dfdf";
	int iRet = 0;
	u_long dwSended = 0;
	u_long dwCanSend = 0;
	SOCKET sock = this->GetSock();
	while(dwSended < lSize)
	{
		dwCanSend = min(lSize - dwSended, m_nSendSizePack);
		iRet = ::sendto(sock, data + dwSended, dwCanSend , 0, (sockaddr*)m_pLastRecvAddr, sizeof(SOCKADDR_IN));
		if(SOCKET_ERROR == iRet)
		{
			int iErr = WSAGetLastError();
			SetErrCode(iErr);
			////DEBUG_ERROR(L"Send failed!");
			return SEND_ER_CONNECT;         //ֱ�ӷ��ظ߼�����
		}
		dwSended += iRet;
	}
	return SEND_OK;
}

SEND_STATE CSockUdp::SendDataSize(DWORD dwSize)
{
	char cBuf[DATA_SIZE_DIGIT_NUMBER] = {0};
	//���ʹ�С
	ultoa(dwSize, cBuf, 10);
	return this->SendData(cBuf, strlen(cBuf) + 1);
}

bool CSockUdp::DoDealDataRecv(void* pBuf, DWORD dwRecv)
{
    return true;
}

CSock* CSockUdp::Clone()
{
	assert(0 && "�ݲ�֧�ֿ�¡");
    CSockUdp* pUdp = new CSockUdp(*this);
    return pUdp;
}

bool CSockUdp::SetRecvBufSize()
{
	return SetSocketBuf(SO_RCVBUF, UDP_RECV_BUF_SIZE);
}

bool CSockUdp::SetSendBufSize(UNINT nSendSizePack)
{
    assert("��δ���");
	SetSocketBuf(SO_SNDBUF, nSendSizePack);
    m_nSendSizePack = nSendSizePack;
    return true;
    //��Ҫ��ȡ��ϵͳֵ�� ��ȷ�������óɹ���
}

bool CSockUdp::SetSocketBuf(int optname, int value)
{
	
	//char* pRecvBuf = (char*)&iRecvBuf;
	char RecvBuf[10] = {0};
	*(int*)RecvBuf = value;
	//���ͻ�������������ʱ�����⣬����Ƿ�ȷʵ������ֵ
	if(SOCKET_ERROR == setsockopt(this->GetSock(), SOL_SOCKET, optname, RecvBuf, 4))
	{	
		int iErr = WSAGetLastError();
		return false;
	}
	/*int iBufSize = sizeof(RecvBuf);
	memset(RecvBuf, 0, iBufSize);
	getsockopt(m_sock, SOL_SOCKET, optname, RecvBuf, &iBufSize);*/
	return true;
}