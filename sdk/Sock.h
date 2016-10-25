#pragma once
#include <WinSock2.h>
#include <string>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;
class CMainFrame;

struct Msg;
const byte DATA_SIZE_DIGIT_NUMBER			= 30;//�ַ�����ʽ�����ݴ�С���֧�ֵ�λ��

struct SOCK_INFO
{ 
    int sockType;
};

//����socket ѡ��ṹ��
class SOCK_PARAM
{
public:
    bool bEnableSendTimeout;
    bool bEnableRecvTimeout;
    bool bSetSendBuf;

    int nSendTimeout;       
    int nRecvTimeout;
    int nSendBuf;
    SOCK_PARAM()
    {
        bEnableSendTimeout  = false;
        bEnableRecvTimeout  = false;
        bSetSendBuf         = false;
        nSendTimeout        = 0;
        nRecvTimeout        = 0;
        nSendBuf            = 10 * 1024;
    }
};

//����Ĵ���Ĳ���
class SOCK_CST_PARAM
{
public:
    SOCKET sock;
    void* pAdd;
    SOCK_PARAM* pSP ;

    SOCK_CST_PARAM()
    {
        sock            = NULL;
        void* pAdd      = 0;
        SOCK_PARAM* pSP = NULL;
    }
};

class CSock
{
public:
	CSock(SOCKET sock = 0, void* pAdd = 0, const SOCK_PARAM* pSP = NULL);
	//�������캯��
	CSock(const CSock& sock);
	virtual ~CSock(void);

public:
    //�������ݵĴ�������
    enum RECV_STATE {RECV_ER_NET, RECV_ER_DATA, RECV_ER_NOCARE, RECV_OK, RECV_ER_UNKNOWN};
    enum SEND_STATE {
        SEND_OK,            //����
        SEND_ER_CLIENT,     //�ð����ݵĴ���, ����Ӱ�쵽���������send����
        SEND_ER_CONNECT,    // ��������������Դ���, ��Ӱ�쵽������ڸ����ӵ�����send����

    };

	bool		    Init();
	static bool		InitSockLib(byte majorVer, byte minorVer);
	bool		    Bind(u_short uPort = 0);
    virtual void    DealSetSockOptFail();

	SOCKET		    GetSock();
	const char*     GetLocalIp();
	u_short		    GetLocalPort();
    SOCK_INFO       SetSockInfo(const SOCK_INFO& si);
	
	virtual         bool Close();

	//bool	Send(Msg*);
    virtual SEND_STATE	Send(const char* data, u_long lSize) = 0;
	//virtual bool	SendDataSize(DWORD dwSize) = 0;

	//��������,������������ʵ��, ����ָ��,���غ�,ָ��ָ���ڲ����������
	virtual RECV_STATE	Recv(char* &pBuf) = 0;
	//virtual DWORD	RecvDataSize() = 0;
    virtual bool    DoDealDataRecv(void* pBuf, DWORD dwRecv) = 0;

	//������ʵ��, �Խ��ܵ������ݽ��д���
	virtual CSock*  Clone() = 0;


    void            SetErrDesc(string strErr);
    const string&   GetErrDesc();

	void            SetErrCode(int nErrCode);
    int             GetErrCode();
    
protected:
    void		    SetSock(SOCKET sock);
public:
	/*һ������ָ��,ͨ������������Ҫ������,�� mfc��������ָ���ڶ��߳��л�ȡ����
		ָ�����������ⲿ�ͷ�
	*/
	void*			m_pAdd; 
private:
    SOCK_PARAM      m_sockParam;        //socket ����socketѡ��

	SOCKET			m_sock;             //������socket
	string			m_strLocalIp;       //����Ip, �ݲ�֧��˫����

	u_short			m_port;             //���ذ󶨵Ķ˿�
    string          m_strErrDesc;
	int             m_nErrCode;         //����������
    SOCK_INFO       m_sockInfo;
};
