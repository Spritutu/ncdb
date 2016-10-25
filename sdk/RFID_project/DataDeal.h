#pragma once
#include <string>
class CADODataBase;
struct TrafficInfo;
struct TrackShow;
class CLogOpr ;
class CShowData;
using namespace std;
/************************************************************************/
/* fun: ���ݴ�����,������յ������ݷ��뵽���ݿ���,��SockTcp����ʹ��                                                                     */
/************************************************************************/
class CDataDeal
{
public:
	CDataDeal(void* pAdd = 0, CADODataBase* pDB = 0);
	~CDataDeal(void);

public:
	bool Init();
	bool SetData(TrafficInfo* pData);
    bool SwitchData(int loopID);
	bool WriteLog();
	bool InsertToDB(byte byLoopId);
	bool SetDeviceLaneMap(CShowData*);
    bool ShowToUI();
	string GetDeviceType(const char* cFlag);
	bool DealData();

private:
	CADODataBase*	m_pDB;
	TrafficInfo*	m_pTInfo;
	CLogOpr*		m_pLog;
    void*           m_pAdd;
    TrackShow*      m_pTrackShow;
	bool			m_bPrivateDB;
};
