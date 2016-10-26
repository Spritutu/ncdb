#include "stdafx.h"
#include "RFID.h"
#include "TcpRFID.h"
#include "RFID_Data_Server.h"
#include "RFID_Data_ServerDlg.h"
#include "IDataDeal.h"
#include "SingleLog.h"
#include "doString.h"
#include "functional.h"
#include <assert.h>
#include "AutoType.h"
#include "StlMath.h"
#include <sstream>
#include "SockClientManager.h"
#include "TcpDeviceAlarm.h"

static CLogOpr* g_pSingleLog;
extern CTimeLight g_at;

typedef  CTcpRFID::CONNECT_RESULT       CONNECT_RESULT;
typedef CSock::RECV_STATE           RECV_STATE;
CTcpRFID::CTcpRFID(SOCKET sock/* = 0*/, void* pAdd /*= 0*/)
	:CSockTcp(sock, pAdd)
{
    InitParam();
    m_pDlg = static_cast<CRFID_Data_ServerDlg*>(pAdd);
	g_pSingleLog = CSinglePattern<CLogOpr>::GetObj();
}

CTcpRFID::CTcpRFID(const CTcpRFID& tcp)
:CSockTcp(tcp)
{
    InitParam();
    m_pTcpDeviceAlarm = tcp.m_pTcpDeviceAlarm;
    m_pClientManager    = tcp.m_pClientManager;
    //�����ಿ��
    //m_pDlg = tcp.m_pDlg;
}

void CTcpRFID::InitParam()
{
    m_pTcpDeviceAlarm       = NULL;
    m_pDlg                  = NULL;
    m_pClientManager        = NULL;
}

CTcpRFID::~CTcpRFID(void)
{

}


bool CTcpRFID::Init()
{
    if(!CSockTcp::Init())
    {
        return false;
    }

    m_pClientManager        = this->GetClientManager();
    m_pTcpDeviceAlarm       = new CTcpDeviceAlarm(m_pDlg);
    INIT_PARAM iParam;
    iParam.bAutoRecn = false;
    m_pTcpDeviceAlarm->SetInitParam(iParam);
    m_pTcpDeviceAlarm->Init();

#ifndef DEBUG_ALL
    m_pTcpDeviceAlarm->SetRemoteInfo("172.5.1.34", 8836);
#endif

    m_pTcpDeviceAlarm->Connect();
    return true;
}


bool CTcpRFID::Listen()
{
	if(!CSockTcp::Listen(SOMAXCONN))
	{
		m_pDlg->PutLog("����ʧ��");
		return false;
	}
	return true;
}

CONNECT_RESULT CTcpRFID::Accept(const char* ip/* = 0*/, u_short port /*= 0*/)
{
    CONNECT_RESULT cr = CSockTcp::Accept(ip, port);
    
    switch(cr)
    {
    case CN_OK:     //�������Ok,��ֱ�ӷ���
        break;

    case CN_ERROR:
    case CN_FILTER:
    default:
        //���˺ʹ��󶼻����ר�ýӿ�������
        return cr;
    }


    string strIp = this->GetClientIp();
    //log
    ostringstream oss;
    oss<<INFO_NORMAL <<strIp<<" �յ�����";
    m_pDlg->PutLog(oss.str());
    //CSingleLog::WriteLog(oss.str());
    
    this->AddFilter(&CLIENT_ADDRESS(strIp));

    m_pDlg->PutLog(INFO_NORMAL "������, ��������");
    //��������������Ϣ
    if(!m_pTcpDeviceAlarm->TalkDeviceNormal(strIp))
    {
        //�豸����ʧ��
        m_oss.str("");
#ifdef Release_Debug
        m_oss<<INFO_ERROR;
#else
        m_oss<<INFO_WARNING;
#endif
        m_oss<< "device report normal fail:" <<strIp;
        m_pDlg->PutLog(m_oss.str());
    }
    return CN_OK;
}

bool CTcpRFID::DealFilter(const string& strIp, u_short uPort)
{
    m_oss.str("");
    m_oss<<INFO_ERROR<<"filter, ip = "<<strIp<<" port = "<<uPort;
    m_pDlg->PutLog(m_oss.str());
    return true;
}

bool CTcpRFID::DealAcceptError()
{
    m_oss.str("");
    m_oss<<INFO_ERROR<<"server accept fail,errCode:"<<this->GetErrCode();
    m_pDlg->PutLog(m_oss.str());
    return true;
}

bool CTcpRFID::DealAcceptClientError()
{
    m_oss.str("");
    m_oss<<INFO_ERROR<<"accept this client fail,errCode:"<<this->GetErrCode();
    m_pDlg->PutLog(m_oss.str());
    return true;
}

bool CTcpRFID::DealCloseByClient()
{
    m_oss.str("");
    m_oss<<INFO_NORMAL<<"socket already close by client " << this->GetClientIp();
    m_pDlg->PutLog(m_oss.str());
    return true;
}

bool CTcpRFID::DealSelectError(int nErr)
{
    m_oss.str("");
    m_oss.str("");

    m_oss<<INFO_ERROR<<"select sock fail, code:"<<nErr;
    m_pDlg->PutLog(m_oss.str());

    return true;
}

bool CTcpRFID::TalkDeviceNormal(const string& strIp)
{
    //��������������Ϣ
    if(!m_pTcpDeviceAlarm->TalkDeviceNormal(strIp))
    {
        //�豸����ʧ��
        m_oss.str("");
        m_oss<< INFO_ERROR << "device report normal fail:" <<strIp;
        m_pDlg->PutLog(m_oss.str());
        return false;
    }
    return true;
}

bool CTcpRFID::TalkDeviceAbnormal(const string& strIp)
{
    //���������쳣��Ϣ
    if(!m_pTcpDeviceAlarm->TalkDeviceAbnormal(strIp))
    {
        //�豸����ʧ��
        m_oss.str("");
        m_oss<< INFO_ERROR << "device report abnormal fail:" <<strIp;
        m_pDlg->PutLog(m_oss.str());
        return false;
    }
    return true;
}

RECV_STATE CTcpRFID::Recv(char* &pBuf)
{	
    static vector<time_t> vtHistoryTime;
    CTimeLight timeTotal;
    timeTotal.Init();
    ostringstream oss;
    CAutoType at;

	RECV_DATA_TCP_SET* pNativeData = new RECV_DATA_TCP_SET;
	memset(pNativeData, 0, sizeof(RECV_DATA_TCP_SET));
	char* pOffset = (char*)pNativeData;
    auto_ptr<RECV_DATA_TCP_SET> apNative(pNativeData);//auto_ptr
	//���ǽ���ʧ�ܵ����    


    bool bIsBigEndian = IsBigEndian();
    if (bIsBigEndian)
    {
        //�����Ǵ�˱����,��¼��
    }


	UINT dwTotalSize = 0;
    UINT dwOffset = 0;
    char pTemp[FRONT_FIX_DATA_SIZE] = {0};
    
	//���̶ܹ���������
	dwTotalSize += this->RecvData(pTemp, FRONT_FIX_DATA_SIZE);
	timeTotal.Start();

	
    const void* pLenOffset = pTemp + 7;
    short& iLen = *((short*)(pLenOffset));//��ǩ�����ܳ���
    
    ///******** test
    if(!bIsBigEndian)
    {
        iLen = ntohs(*((short*)pLenOffset));
    }
    if(iLen <= 0)
    {
        if(dwTotalSize <= 0)
        {
            oss.str("");
            oss<<INFO_WARNING<<m_strClientIp<<" û���յ�����,�������:"<< this->GetErrCode();
            m_pDlg->PutLog(oss.str());
            return RECV_ER_NET;
        }
        //����������
        assert(0 && "��ǩ���ݳ���Ϊ0");
        //delete pNativeData;
        return RECV_ER_DATA;
    }
	//****test***/

    

	char* pTagData = new char[iLen]; //���б�ǩ������, �������<<delete>>
	memset(pTagData , 0, iLen);
    auto_ptr<char> apTagData(pTagData);//auto_ptr

    //����ʣ���ȫ������
	dwTotalSize += this->RecvData(pTagData, iLen);
    g_at.Init();
    g_at.Start();
    time_t tSpend = time(NULL) * 1000;

    static DWORD dwTickPrevious = 0;
    
    //at.SetData((byte)*(pTemp + NUM_MSG_TYPE_POS));
    //DEBUG_WARN((char*)at);
    
    const PCSTR pStrInfo= "[TYPE] ";
    //ɸѡʵʱ��ǩ����
    byte byMsgType = *(pTemp + NUM_MSG_TYPE_POS);

    /*oss.str("");
    oss<<pStrInfo<<(int)byMsgType;
    m_pDlg->PutLog(oss.str());*/
    if (MSG_TYPE_RTDATA != byMsgType)
    {
        
        return RECV_ER_NOCARE;
    }
    else
    {    
    }

    if(dwTotalSize <= 0 )
    {
        assert(0 && "�ղ�����ǩ����");
        //delete [] pTagData;
        //delete pNativeData;
        return RECV_ER_DATA;
    }
    

    pOffset = pTagData;
    pNativeData->pTAG_DATA = pTagData;
    
    /************* ���ձ�ǩ���� **********************/	
    
    pNativeData->tagData.byTagCount = *(byte*)pOffset;
    pNativeData->tagData.pTddArr = new TAG_DATA_DESC[*(byte*)pOffset];//<<delete>>
    pOffset += 1;
    //string sttTime = GetLocalDateTime();
    byte& byTagCount = pNativeData->tagData.byTagCount;
	//��������
    at.SetData(byTagCount);
    oss.str("");
    oss<<"Total Lane = "<<(PCSTR)at<<"recv time ";
    at.SetData(GetTickCount());
    oss<<(PCSTR)at;

 	for (byte i = 0;i < byTagCount;++i)
 	{
        pNativeData->tagData.pTddArr[i].byEpcLen = *(byte*)pOffset;
        pOffset += 1;
        pNativeData->tagData.pTddArr[i].pEpc = pOffset;//EPC����

        if (0 == pNativeData->tagData.pTddArr[i].byEpcLen)
        {
            oss.str("");
            oss<<INFO_ERROR<<m_strClientIp<<" epcLen �ֶ� = 0";
            m_pDlg->PutLog(oss.str());
            return RECV_ER_DATA;
        }

        pOffset += pNativeData->tagData.pTddArr[i].byEpcLen;

        pNativeData->tagData.pTddArr[i].byTagMemDataLen = *(byte*)pOffset;
        pOffset += 1;
        pNativeData->tagData.pTddArr[i].pTagMemData = pOffset;//��ǩ�ڴ�����
        pOffset += pNativeData->tagData.pTddArr[i].byTagMemDataLen;

        memcpy(&pNativeData->tagData.pTddArr[i].byAntennaID, pOffset, TAG_DATA_REMAIN_SIZE);//ʣ�µ�21���ֽ�����
        pOffset += TAG_DATA_REMAIN_SIZE;


        static UINT iLastLogSpend = 0;
        char cLog[500] = {0};
        string strEpc = MemToHex((byte*)pNativeData->tagData.pTddArr[i].pEpc, pNativeData->tagData.pTddArr[i].byEpcLen);

        string strTimeStamp;
        MemToString(strTimeStamp, pNativeData->tagData.pTddArr[i].szTimeStamp, sizeof(pNativeData->tagData.pTddArr[i].szTimeStamp));
        
        oss.str("");
        oss<<INFO_NORMAL<<"IP = "<<m_strClientIp<<", lane = "<<(int)pNativeData->tagData.pTddArr[i].byAntennaID<<", EPC = "
            <<strEpc;

#ifdef BOOL_OUTPUT_NATIVE_TIMESTAMP
        time_t tTimeStamp = TimestampToMilSecond1970(strTimeStamp.c_str());
        oss<<" timestamp: "<<tTimeStamp;
#endif

        CTimeLight timeLog;
        timeLog.Init();
        timeLog.Start();
        m_pDlg->PutLog(oss.str());
        //CSingleLog::WriteLog(oss.str());
        timeLog.Stop();

        iLastLogSpend = timeLog.GetPass();
        oss.str("");
        /*oss<<"����log ��������ʱ��"<<iLastLogSpend;
        m_pDlg->PutLog(oss.str());*/

        if(iLastLogSpend > 30)
        {
            int a = 0;
        }
 	}//������������б�ǩ

    DWORD dwPreviousDiff = GetTickCount() - dwTickPrevious;
    dwTickPrevious = GetTickCount();

#ifdef BOOL_OUTPUT_TWO_TIMES_SPEND
    char cLog[500] = {0};
    sprintf_s(cLog, sizeof(cLog), INFO_NORMAL "%s ���ϴε�ʱ���Ϊ %d",  m_strClientIp.c_str(), dwPreviousDiff);
    m_pDlg->PutLog(cLog);
#else
    m_pDlg->PutLog(string(INFO_NORMAL "end circle"));
#endif
    
	/************* ���ձ�ǩ���� **********************/

	/************* Reader *********/
    pNativeData->tagData.ReaderNameLen = *(byte*)pOffset;
    pOffset += 1;
    pNativeData->tagData.ReaderName = pOffset;

	/************* Reader *********/

    pBuf = (char*)pNativeData;

    string strTemp;
    strTemp.resize(18, 0);
    memcpy(&strTemp.at(0), pNativeData->tagData.pTddArr[0].szTimeStamp, 17);
    timeTotal.Stop();
    
    /*at.SetData(timeTotal.GetPass());
    wstring strLog2(L"���� ���ܵ�����ʱ�� = ");
    strLog2 += s2ws(at);
    strLog2 += L"\r";
    OutputDebugString(strLog2.c_str());*/
    
    /*time_t tBegin = GetTickCount();
    time_t tDelay = max(tSpend - tBegin, 0);*/

    apTagData.release();
    apNative.release();

    m_LastRecvSize = dwTotalSize;
 	return RECV_OK;
}

//������ʵ��, �Խ��յ������ݽ��д���
/*
bool CTcpRFID::DoDealDataRecv(void* pBuf, DWORD dwRecv)
{
	//���͵������߳�������
	
	return true;
}*/


bool CTcpRFID::InitAdditionArgu()
{
    m_pDlg = static_cast<CRFID_Data_ServerDlg*>(m_pAdd);
    m_strClientIp = this->GetClientIp();
    return m_pDataDeal->Init(this);
}

 
CSock* CTcpRFID::Clone()
{
	CTcpRFID* pNew      = new CTcpRFID(*this);
    return pNew;
}

bool CTcpRFID::ExitRecvMsgThread(void* cInfo /*= NULL*/)
{
    string strIp = this->GetClientIp();
    m_oss.str("");
    m_oss<<INFO_NORMAL<< "Exit RecvMsg: " << strIp;
    m_pDlg->PutLog(m_oss.str());
    //CSingleLog::WriteLog(m_oss.str());

    m_pClientManager->WithDrawFilter(CLIENT_ADDRESS(strIp));
    //���������쳣��Ϣ
    if(!m_pTcpDeviceAlarm->TalkDeviceAbnormal(strIp))
    {
        //�豸����ʧ��
        m_oss.str("");
        m_oss<< "device report Abnormal fail:" <<strIp;
        m_pDlg->PutLog(m_oss.str());
    }
    
    return true;
}

bool CTcpRFID::ExitWaitForConnectThread(void* cInfo /*= NULL*/)
{
    m_oss.str("");
    m_oss<<INFO_WARNING<< "Exit Thread: WaitForConnectProc. "<< "There are "<< m_pClientManager->Size()<<" connect has establish";
    //m_pDlg->PutLog(m_oss.str());
    CSingleLog::WriteLog(m_oss.str());
    return true;
}


