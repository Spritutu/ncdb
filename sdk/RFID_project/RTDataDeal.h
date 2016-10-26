#pragma once
#include <string>
#include "RFID.h"
#include "GlobalFile.h"
#include "IDataDeal.h"
#include <sstream>

class CADODataBase;
struct TrafficInfo;
struct TrackShow;
class CLogOpr ;
class CShowData;
class CNativeDataDeal;
class CRFID_Data_ServerDlg;

using namespace std;
/************************************************************************/
/* fun: ���ݴ�����,������յ������ݷ��뵽���ݿ���,��SockTcp����ʹ��                                                                     */
/************************************************************************/

/************************************************************************
        fun:    ԭʼ���ݴ�����, ��������������֤, �ŵ������߳�
        param:  
        ret:    
        remark: 
/************************************************************************/
class CRTDataDeal
	:public IDataDeal
{
public:
	CRTDataDeal(void* pAdd = 0);
	CRTDataDeal(CRTDataDeal& dd);
	~CRTDataDeal(void);

public:
	virtual bool Init(void*);
	virtual void SetData(void* pData);
	virtual IDataDeal* Clone();
	virtual bool Work(void*);

	bool WriteDataToLog();
	bool AnalyData();
	/*	fun: �ŵ�ip��Ӧ�Ķ��������� */
	bool PushToList();
	bool SetDevicePos(const char* DeviceIp);

private:
	RECV_DATA_TCP_SET*	        m_pNativeData;
	CLogOpr*			        m_pLog;
	DWORD				        m_dwDevicePos;  //�����Ӧ��ȫ��device���е�Index

    TrackShow*      	        m_pTrackShow;   //<delete>��ʾ������Ľṹ��
	TagInfo*			        m_pTagInfo;     //<delete>
	CNativeDataDeal*	        m_NativeDataDeal;
    ostringstream               m_oss;
    CRFID_Data_ServerDlg*       m_pDlg;
};
