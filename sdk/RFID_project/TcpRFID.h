#pragma once


const byte NUM_MSG_TYPE_POS            = 2;
#include "SockTcp.h"
#include <sstream>

class CRFID_Data_ServerDlg;
class CTcpDeviceAlarm;

class CTcpRFID :
	public CSockTcp
{
public:
    
	CTcpRFID(SOCKET sock = 0, void* pAdd = 0);
	~CTcpRFID(void);
    CTcpRFID(const CTcpRFID& tcp);

    bool    Init();
    void            InitParam();

    bool            TalkDeviceNormal(const string& strIp);
    bool            TalkDeviceAbnormal(const string& strIp);

    bool            DealFilter(const string&, u_short uPort);

	bool			Listen();
	virtual CONNECT_RESULT	Accept(const char* ip = 0, u_short port = 0);
    virtual bool    DealAcceptError();
    virtual bool    DealAcceptClientError();
    virtual bool    DealSelectError(int nErr);
    virtual bool    DealCloseByClient();
    //��ʼ�����ݴ������
	virtual bool			InitAdditionArgu();
	virtual RECV_STATE	Recv(char* &pBuf);
	//������ʵ��, �Խ��ܵ������ݽ��д���
//	virtual bool	DoDealDataRecv(void* pBuf, DWORD dwRecv);
	virtual CSock*	Clone();
	
    virtual bool	ExitWaitForConnectThread(void* cInfo = NULL);
    virtual bool	ExitRecvMsgThread(void* cInfo = NULL);


private:
	string m_strClientIp;       //������֮���ӵĿͻ��˵�ip
    CRFID_Data_ServerDlg*   m_pDlg;
    ostringstream           m_oss;
    CTcpDeviceAlarm*        m_pTcpDeviceAlarm;
    CSockClientManager*     m_pClientManager;
};
