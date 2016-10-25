#pragma once
#include "PiTypeDef.h"
#include <string>
#include <list>
#include "winsock2.h"

#include <vector>
using namespace std;

class CSockTcp;
class CLock;

//����tcp�ͻ��˵�һЩ��Ϣ
class CLIENT_ADDRESS
{
public: 
    

    CLIENT_ADDRESS(string& strIpR, u_short uPortR = 0)
    {
        strIp = strIpR;
        uPort = uPortR;
    }
    bool operator ==(const CLIENT_ADDRESS& caR) const
    {
        return (uPort == caR.uPort && strIp == caR.strIp);
    }
public:
    string strIp;       //�ͻ���ip
    u_short uPort;        //�ͻ��˶˿�
};


class CSockClientManager
{
public:    

    struct INIT_PARAM
    {
        bool    bDisFilter; //���öԿͻ��˽���ɸѡ
    };

    struct CLIENT_DATA
    {
        CSockTcp*   pClientSockTcp;
        //SOCKET sock; 
        HANDLE hThread;
    };
    typedef vector<CLIENT_DATA> ClientInfoList;

public:
	CSockClientManager(void);
	~CSockClientManager(void);

public:
	bool    Init();
	bool    UnInit();
    bool    SetInitParam(const INIT_PARAM& iParam);
    void    InitVariable();
    bool    CloseAll();
    UNLONG  Size();
    /************************************************************************/
    /*  fun: �߳̾��������������ת��������ʽ
    /************************************************************************/
    HANDLE* ToArray();
	bool    Add(CLIENT_DATA&);
	bool    Delete(const CSockTcp* s);

    bool    FindIp(const string& strIp);

    /************************************************************************/
    /*  fun:    �Խ�������֮��Ŀͻ�ip ���й��˺�ɸѡ
        remark: �ȹ���, �ڿ��Ƿ���Ҫɸѡ
        return: false-> ���˵�
    /************************************************************************/
    bool            Filter(const CLIENT_ADDRESS&);


    /************************************************************************/
    /*  fun: ���ӹ���Ԫ��
    /************************************************************************/
    void            AddFilter(const CLIENT_ADDRESS& caR);

    /************************************************************************/
    /*  fun: ȡ��֮ǰ���ù��Ĺ�����
    /************************************************************************/
    bool            WithDrawFilter(const CLIENT_ADDRESS& caR);

    /************************************************************************/
    /*  fun: ����ɸѡԪ��
    /************************************************************************/
    
    void            AddDisFilter(const CLIENT_ADDRESS& caR);

    /************************************************************************/
    /*  fun: ȡ��֮ǰ��ɸѡ
    /************************************************************************/
    bool            WithDrawDisFilter(const CLIENT_ADDRESS& caR);
private:

	ClientInfoList*		    m_pVtClientsSock;
    list<CLIENT_ADDRESS>    m_lstFilterList;    //�����б�
    list<CLIENT_ADDRESS>    m_lstDisFilterList; //ɸѡ�б�
    INIT_PARAM              m_iParam;
	//CRITICAL_SECTION	m_cs;
    CLock*              m_pLock;
    CLock*              m_pLockFilter;
    CLock*              m_pLockDisFilter;
};
