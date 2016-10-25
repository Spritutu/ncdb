#pragma once
#include <WinInet.h>
#include <string>
#include "PiTypeDef.h"
#include "InetDef.h"
#include "DowningInfoMng.h"
using std::string;
#define ClearHInternet(a) ::InternetCloseHandle(a); (a) = NULL
#define SaveErrCodeAndRet(a) if(!(a)){ m_dwErrCode = GetLastError(); return false;}
#define SaveErrCodeAndRetEx(nFlag, err) if(!(nFlag)){ m_dwErrCode = GetLastError(); m_dState = err; return false;}

#define SaveNetErrCodeAndRet(a) if(!(a)){ m_dwErrCode = GetLastError(); m_dState = err_net; return false;}

typedef bool (FuncReadData)(void* pObj, void* pData, UNINT nSize);
class CPiBPDown;
class CInternetHttp
{
public:
	CInternetHttp(void);
	virtual ~CInternetHttp(void);
protected:
	virtual bool DealReadData(void* pData, UNINT nSize);

public:
	/************************************************************************
		function��	����ָ����ַ�����ݵ������ļ�
		remark:		Ŀǰֻ֧��httpЭ��
	/************************************************************************/
	bool DownloadFile(tcpchar strUrl);
	/************************************************************************
		function��	ת�����ͣ� ��INTERNET_SCHEME �� INTERNET_SERVICE
		remark:		
	/************************************************************************/
	static int GetServiceType( INTERNET_SCHEME param1 );

	/************************************************************************
		function��	��ȡurl��object����
		remark:		
	/************************************************************************/
    static tstring FindHttpObject(tcpchar szUrl);

	/************************************************************************
		function��	�����ļ��� �������ͬһ����վ�µĶ���ļ�
		remark:		
		param:		������������ļ����ص�ַ�� �� �������ص�ַΪhttp://zhidao.baidu.com/question/189984289.html, 
					����"/question/189984289.html"
	/************************************************************************/
    bool DownloadObject(tcpchar szUrl, tcpchar szSavePath);
	bool DownloadObject( tcpchar szUrl);
	
    bool SetOffset(UNLONG nOffset);
	static bool QueryFileSize(tcpchar szUrl, UNLONG& dwSize);
    UNLONG GetFileSize() const;
    void PauseDown();

    /************************************************************************
        fun:	ֹͣ����, �����غ����˳�
        param:  
        ret:    
        remark: 
	/************************************************************************/
    void QuitDown();
    void ResumeDown();
	bool QueryFileSize(UNLONG& dwSize);

    bool SendCn();

    tstring QueryFileModifyTime();
	bool EnsureQueryOK(HINTERNET hq);

    /************************************************************************
		function��	����֮ǰ�ĳ�ʼ��
		remark:		ֻ����Ҫ����DownloadObject����Ҫ���øýӿ�
		param:		��վ��ַ, ����Ҫ��ϸ������ҳ��
	/************************************************************************/
    bool DownloadInit( tcpchar strUrl, tcpchar szProxyServe = NULL);
    HINTERNET GetConnectHandle();

    DownState		GetErrType();
	UNLONG	GetServerState(){return m_dwServerState; }
	/************************************************************************
		function��	���ض���ļ���ɺ�, ���øýӿڣ� �ͷ���Դ
		remark:		
	/************************************************************************/
	bool DownloadUnInit();
	
    void SetDowningInfoMng(CDowningInfoMng* pR);
    void SetDowningInfoID(ItemID id);
    UNLONG ErrCode() const { return m_dwErrCode; }
    void ErrCode(UNLONG val) { m_dwErrCode = val; }
    bool ClearState();
    bool SetHeader( LPCTSTR param1 );
    ItemID GetShowID() { return m_idDowningInfo;}
    bool AddHeaderOffset( UNLONG m_nOffset );
    static tstring QuestFileModifyTime( tcpchar szUrl);
    tstring Url() const { return m_strUrl; }
    void Url(tstring val) { m_strUrl = val; }
    void BPDown( CPiBPDown* param1 );
    static void Clear(CInternetHttp* pInet);
    UNLONG GetDownSize() { return m_dwDowned; }
    void UpdateData(UNLONG nAddSize, bool bClearSpeed = false);
    bool CanRetryCn();
    bool IsRetryOK();
	void SetHttpsWay();
	static tstring GetCookie( const tstring& strUrl );
	void SetCookie( tcpchar szCookie );
	void SetNoRedirect();
	bool IsNeedRedirect();
	bool CheckSetHttpWay();
	static bool DeleteUrlCache(const tstring& strUrl);
	void SetDownWeb() ;
private:
	void InitVariable();
    bool RetryOut();
	static tstring GetHostName( tcpchar strUrl);
protected:
	tstring         m_strUrl;		//URL·��
    
    bool            m_bQuitDown;        //�Ƿ�ֹͣ����
    
	HINTERNET m_hInet;		//�Ѵ򿪵�������
	HINTERNET m_hCn;			//�����ӵ�������
    HINTERNET m_hQeq;       //�ɽ��в����ľ��

	int m_nServiceType;		//Ҫ���ӵķ�����������(http, ftp��)
	URL_COMPONENTS m_uc;		//url��������������
    UNLONG  m_dwDowned;         //�������ֽ���
    UNLONG  m_dwSizeTotalSrc;      //�ļ��ܴ�С

	UNLONG	m_dwFlag;			//���������ʱ���ӱ�ʶ
	UNLONG	m_dwErrCode;	//�������µĴ�����
    
    UNINT	m_dwServerState;	// ��������״̬��
	DownState	m_dState;
    
    CDowningInfoMng*        m_pDowningInfoMng;
    ItemID              m_idDowningInfo;
    int                 m_nRetryedCount;
    int                 m_nCanRetryCountMax;
    tstring             m_strHeader;
    tcpchar             m_szHeader;
    CPiBPDown*            m_pBPDown;
};

