#pragma once
#include "PiTypeDef.h"
//#include <WinSock2.h>
#include "Sock.h"
//#pragma comment(lib, "Ws2_32.lib")

class CMainFrame;
struct Msg;

class CSockUdp
    :public CSock
{
	enum BUF_TYPE{a = 1000 * 1000};
public:
	CSockUdp( SOCKET sock = 0);
	~CSockUdp(void);
public:
	bool            Init(u_short port = 0);

	void			SetRemoteAddress( const char* ip,u_short port);
	DWORD           RecvData(char* pBuf, u_long lSize);
	virtual RECV_STATE	Recv(char* &pBuf);

	virtual SEND_STATE    Send(const char* data, u_long lSize);
	SEND_STATE            SendData(const char* data, u_long lSize);
	SEND_STATE            SendDataSize(DWORD dwSize);
    
    virtual bool    DoDealDataRecv(void* pBuf, DWORD dwRecv);
	virtual DWORD	RecvDataSize();
	bool            SetRecvBufSize();
	bool            SetSendBufSize(UNINT nSendSizePack);
	bool            SetSocketBuf(int optname, int value);
	virtual CSock*  Clone();
private:
	CMainFrame*		m_pWnd;//�������߳��п�����Ҫ�õ��������ָ�룬�߳��л�ȡ����
	SOCKADDR_IN*	m_pLastRecvAddr;
    UNINT           m_nSendSizePack;//һ����෢�͵İ���С,�����Ļ��ֶ�η���
};
